#include "show_text.h"



void show_text(struct text *text){
    //printf("sents num - %d\n", text->num_sent);
    for(int i = 0; i < text->num_sent; i++){
       // printf("sentLen - %d\n", wcslen(text->sents[i].words));
        wprintf(L"%ls\n", text->sents[i].words);
    }
}

void show_metadata(struct text *text){
    for(int i = 0; i < text->num_sent; i++){
        wprintf(L"%ls", text->sents[i].words);
        printf("|| sentLen - %d\n", wcslen(text->sents[i].words));
        wprintf(L"Kolichestvo slov - %d, Max len slova - %d, Kol-vo simb - %d\n", text->sents[i].words_sum, text->sents[i].max_word_len, text->sents[i].simb_sum);
    }
}
