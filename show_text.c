#include "show_text.h"



void show_text(struct text *text){
    //printf("sents num - %d\n", text->num_sent);
    for(int i = 0; i < text->num_sent; i++){
       // printf("sentLen - %d\n", wcslen(text->sents[i].words));
        wprintf(L"%ls\n", text->sents[i].words);
    }
}

void show_metadata(struct text *text){
    get_metadata(text);
}
