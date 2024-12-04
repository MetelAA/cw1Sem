#include "process_text.h"


void reverse_sentence(struct text *text) {

}

void sort_by_first_word(struct text *text){

}

void del_less_then_four_symbol_word_sent(struct text *test){

}

void get_metadata(struct text *text){
    for(int i = 0; i < text->num_sent; i++){
        int max_word_len = 0;
        int words_sum = 0;
        int word_len = 0;
        struct sentence *sent = &text->sents[i];
        for(int j = 0; j < wcslen(sent->words); j++){
            wprintf(L"LOG simb in proc - %lc\n", sent->words[j]);
            if(sent->words[j] != L' ' && sent->words[j] != L',' && sent->words[j] != L'.' && sent->words[j] != L'\n'){
                word_len++;
            }else if(word_len != 0){
                max_word_len = MAX_AB(word_len, max_word_len);
                word_len = 0;
                words_sum++;
            }
        }
        sent->words_sum = words_sum;
        sent->max_word_len = max_word_len;
        sent->simb_sum = (int) wcslen(sent->words);
    }
}