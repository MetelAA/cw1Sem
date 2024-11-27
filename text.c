#include "text.h"

#define STANDARD_TEXT_LEN 10
#define STANDARD_SENT_LEN 100

struct text init_text();
int add_sent_size(struct sentence *sent, int sent_max_size);
int add_text_size(struct text *text, int text_max_size);

struct text* read_text(){
    int text_max_size = STANDARD_TEXT_LEN;
    struct text text = init_text();
    int text_size = 0;

    wchar_t buffer;
    while(1){
        int sent_size = 0;
        int sent_max_size = STANDARD_SENT_LEN;
        struct sentence *sent = &text.sents[text_size]; //при такой релизации мы работаем напрямую с структурой в текст (не копируя её)
        while(1){
            buffer = getwchar();
            if (sent_size == 0 && (buffer == L' ' || buffer == L'\t')) {
                continue;
            }
            if((sent_size+2) >= sent_max_size){ //плюс два чтобы точно осталалось место на \0
                sent_max_size = add_sent_size(sent, sent_max_size);
            }
            sent->words[sent_size] = buffer;
            sent_size++;

            if(buffer == L'.'){
                sent_size++;
                sent->words[sent_size] = L'\0';
                break;
            }
        }
        if((text_size+1) >= text_max_size){
            text_max_size = add_text_size(&text, text_max_size);
        }
        text_size++;
        text.num_sent++;
        break;

    }
}

struct text init_text(){
    struct sentence *sents = malloc(sizeof(struct sentence) * STANDARD_TEXT_LEN);
    struct text text = {.sents = sents, .num_sent = STANDARD_TEXT_LEN};
    for (int i = 0; i < STANDARD_TEXT_LEN; ++i) {
        wchar_t *words = malloc(sizeof(wchar_t) * STANDARD_SENT_LEN);
        struct sentence sent = {.words = words};
        text.sents[i] = sent;
    }
    return text;
}

int add_sent_size(struct sentence *sent, int sent_max_size){
    sent_max_size = sent_max_size * 3 / 2;
    wchar_t *new_words_place = realloc(sent->words, sent_max_size);
    if(new_words_place == NULL){
        printf("Error: error when realloc memory for sentence \n");
        return 0;
    }
    sent->words = new_words_place;
    return sent_max_size;
}

int add_text_size(struct text *text, int text_max_size){
    text_max_size = text_max_size * 3 / 2;
    struct sentence *sents = realloc(text->sents, text_max_size);
    if(sents == NULL){
        printf("Error: error when realloc memory for text \n");
    }
    text->sents = sents;
    return text_max_size;


}