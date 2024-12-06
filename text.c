#include "text.h"

#define STANDARD_TEXT_LEN 3
#define STANDARD_SENT_LEN 100

struct text init_text();

int add_sent_size(struct sentence *sent, int sent_max_size);

int add_text_size(struct text *text, int text_max_size);

void delete_repeat_sentences(struct text *text);

struct sentence init_sentence();

//посимвольно читаем текст
struct text read_text() {
    int text_max_size = STANDARD_TEXT_LEN;
    struct text text = init_text();
    int text_size = 0;

    wchar_t buffer;
    wchar_t old_buffer_state;
    while (1) {
        int sent_size = 0;
        int is_text_end = 0;
        int sent_max_size = STANDARD_SENT_LEN;
        struct sentence *sent = &text.sents[text_size]; //при такой релизации мы работаем напрямую с структурой в текст (не копируя её)
        old_buffer_state = L'\0';
        while (1) {
            buffer = getwchar();
            if (old_buffer_state == L'\n' && buffer == L'\n') {
                is_text_end = 1;
                break;
            }
            old_buffer_state = buffer;
            if (sent_size == 0 && (buffer == L' ' || buffer == L'\t' ||
                                   buffer == L'\n')) { // пропускаем лишние символы между предложениями
                continue;
            }
            if ((sent_size + 2) >= sent_max_size) { //плюс два чтобы точно осталалось место на \0
                sent_max_size = add_sent_size(sent, sent_max_size);
            }
            sent->words[sent_size] = buffer;
            sent_size++;

            if (buffer == L'.') {
                sent->words[sent_size] = L'\0';
                break;
            }
        }
        if (is_text_end) {
            //закончить предложение. В приницпе вся нестандартная логика обработки последнего предложения связана с
            //неопределённостью кончается ли оно точкой перед двуся /n (я подвёл под единое условие и дальшнейшееся ветевление)
            if (sent_size > 1) {
                text.num_sent++;
                sent->words[sent_size - 1] = L'.';
                sent->words[sent_size] = L'\0';
            }
            break;
        }
        if ((text_size + 1) >= text_max_size) {
            text_max_size = add_text_size(&text, text_max_size);
        }
        text_size++;
        text.num_sent++;
    }

    delete_repeat_sentences(&text);

    return text;
}

//удаляем все повторновстречающиеся преложения
void delete_repeat_sentences(struct text *text) {
    for (int i = 0; i < text->num_sent; i++) {
        for (int j = i + 1; j < text->num_sent; j++) {
            size_t s1_len = wcslen(text->sents[i].words) + 1;
            wchar_t *s1 = malloc(sizeof(wchar_t) * s1_len);
            for (size_t k = 0; k < s1_len; k++) {
                s1[k] = towlower(text->sents[i].words[k]);
            }
            size_t s2_len = wcslen(text->sents[j].words) + 1;
            wchar_t *s2 = malloc(sizeof(wchar_t) * s2_len);
            for (size_t k = 0; k < s2_len; k++) {
                s2[k] = towlower(text->sents[j].words[k]);
            }
            if (wcscmp(s1, s2) == 0) {
                delete_sent(text, j);
                j--;
            }
            free(s1);
            free(s2);
        }
    }
}

//иницализация текста (для красоты)
struct text init_text() {
    struct sentence *sents = malloc(sizeof(struct sentence) * STANDARD_TEXT_LEN);
    struct text text = {.sents = sents, .num_sent = 0};
    for (int i = 0; i < STANDARD_TEXT_LEN; ++i) {
        text.sents[i] = init_sentence();
    }
    return text;
}

//инициализация sentence (используется при добавлении места в тексте)
struct sentence init_sentence() {
    wchar_t *words = malloc(sizeof(wchar_t) * STANDARD_SENT_LEN);
    struct sentence sent = {.words = words};
    return sent;
}

//расщирение места в предложение
int add_sent_size(struct sentence *sent, int sent_max_size) {
    sent_max_size = sent_max_size * 3 / 2;
    wchar_t *new_words_place = realloc(sent->words, sizeof(struct sentence) * sent_max_size);
    if (new_words_place == NULL) {
        wprintf(L"Error: error when realloc memory for sentence \n");
        return 0;
    }
    sent->words = new_words_place;
    return sent_max_size;
}

//расшиерения кол-ва sentence в тексте
int add_text_size(struct text *text, int text_max_size) {
    int new_max_size = text_max_size * 3 / 2;
    struct sentence *new_sents = malloc(sizeof(struct sentence) * new_max_size);
    if (new_sents == NULL) {
        wprintf(L"Error: error when realloc memory for text \n");
        return 0;
    }
    for (int i = 0; i < new_max_size; i++) {
        if (i < text_max_size) {
            new_sents[i] = text->sents[i];
        } else {
            new_sents[i] = init_sentence();
        }
    }
    text->sents = new_sents;
    return new_max_size;
}

//удаление лишнего предлодения со сдвиганием указателей
void delete_sent(struct text *text, int sent_number) {
    free(text->sents[sent_number].words);
    for (int i = sent_number; i < text->num_sent - 1; i++) {
        text->sents[i].words = text->sents[i + 1].words;
    }
    text->num_sent--;
}