#include "text.h"

#define STANDARD_TEXT_LEN 10
#define STANDARD_SENT_LEN 100

struct text init_text();

int add_sent_size(struct sentence *sent, int sent_max_size);

int add_text_size(struct text *text, int text_max_size);

int check_end(struct sentence *sent);

void delete_repeat_sentences(struct text *text);

void delete_sent(struct text *text, int sent_number);

struct text read_text() {
    int text_max_size = STANDARD_TEXT_LEN;
    struct text text = init_text();
    int text_size = 0;

    wchar_t buffer;
    while (1) {
        int sent_size = 0;
        int sent_max_size = STANDARD_SENT_LEN;
        struct sentence *sent = &text.sents[text_size]; //при такой релизации мы работаем напрямую с структурой в текст (не копируя её)
        while (1) {
            buffer = getwchar();
            if (sent_size == 0 && (buffer == L' ' || buffer == L'\t' || buffer == L'\n')) {
                continue;
            }
            if ((sent_size + 2) >= sent_max_size) { //плюс два чтобы точно осталалось место на \0
                sent_max_size = add_sent_size(sent, sent_max_size);
            }
            sent->words[sent_size] = buffer;
            sent_size++;

            if (buffer == L'.' || (sent_size > 1 && sent->words[sent_size - 1] == L'\n' && sent->words[sent_size - 2] == L'\n')) { //вторая часть - коррекьтировка на то что последнее прелодение может оказаться без точки
                sent->words[sent_size] = L'\0';
                break;
            }
        }
        if ((text_size + 1) >= text_max_size) {
            text_max_size = add_text_size(&text, text_max_size);
        }
        text_size++;
        text.num_sent++;
        if (text_size > 1 && check_end(sent)) {
            break;
        }

    }

    delete_repeat_sentences(&text);

    return text;
}

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
            }
//            int k = 0;
//            int flag = 1;
//            while(s1[k] && s2[k]){
//                if(s1[k] != s2[k]){
//                    flag = 0;
//                    break;
//                }
//                k++;
//            }
//            wprintf(L"cmp to sents\n sent1 - %ls \n sent2 - %ls\n res - %d\n\n", s1, s2, flag);
//            if(flag){
//                delete_sent(text, j);
//            }
            free(s1);
            free(s2);
        }
    }
}

void delete_sent(struct text *text, int sent_number) {
    free(text->sents[sent_number].words);
    for (int i = sent_number; i < text->num_sent - 1; i++) {
        text->sents[i].words = text->sents[i + 1].words;
    }
    text->num_sent--;
}

int check_end(struct sentence *sent) {
    if (wcsstr(sent->words, L"\n\n") != NULL) {
        wchar_t *a = wcspbrk(sent->words, L"\n\n");
//        wprintf(L"LOG check_end - %ls\n", a);
        return 1;
    }
    return 0;
}

struct text init_text() {
    struct sentence *sents = malloc(sizeof(struct sentence) * STANDARD_TEXT_LEN);
    struct text text = {.sents = sents, .num_sent = 0};
    for (int i = 0; i < STANDARD_TEXT_LEN; ++i) {
        wchar_t *words = malloc(sizeof(wchar_t) * STANDARD_SENT_LEN);
        struct sentence sent = {.words = words};
        text.sents[i] = sent;
    }
    return text;
}

int add_sent_size(struct sentence *sent, int sent_max_size) {
    sent_max_size = sent_max_size * 3 / 2;
    wchar_t *new_words_place = realloc(sent->words, sent_max_size);
    if (new_words_place == NULL) {
        printf("Error: error when realloc memory for sentence \n");
        return 0;
    }
    sent->words = new_words_place;
    return sent_max_size;
}

int add_text_size(struct text *text, int text_max_size) {
    text_max_size = text_max_size * 3 / 2;
    struct sentence *sents = realloc(text->sents, text_max_size);
    if (sents == NULL) {
        printf("Error: error when realloc memory for text \n");
    }
    text->sents = sents;
    return text_max_size;


}