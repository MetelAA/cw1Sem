#include "process_text.h"

int is_end_word(wchar_t wchar);
int sentence_comparator(struct sentence *sent1, struct sentence *sent2);



void reverse_sentence(struct text *text) {
    for(int i = 0; i < text->num_sent; i++){
        struct sentence *sent = &text->sents[i];
        int ind_word_start = 0;
        for(int j = 0; j < wcslen(sent->words); j++){
            if (ind_word_start == 0 && is_end_word(sent->words[j])){
                ind_word_start = j;
            }
            
        }
    }

}

void sort_by_first_word(struct text *text){
    for(int i = 0; i < text->num_sent; i++){
        struct sentence *sent = &text->sents[i];
        sent->first_word_len = 0;
        while(is_end_word(sent->words[sent->first_word_len])){
            sent->first_word_len++;
        }
    }
//    for(int k = 0; k < text->num_sent; k++){
//        printf("firstWORDsentLEN - %d\n", text->sents[k].first_word_len);
//        wprintf(L"%ls\n", text->sents[k].words);
//    }
    qsort(text->sents, text->num_sent, sizeof(struct sentence), (int (*)(const void *, const void *)) sentence_comparator);
}

void delete_less_then_four_symbol_word_sent(struct text *text){
    for(int i = 0; i < text->num_sent; i++){
        struct sentence *sent = &text->sents[i];
        int j = 0;
        int word_len = 0;
        sent->is_len_3 = 1;
        while(sent->words[j]){
            if(is_end_word(sent->words[j])){
                word_len++;
            }else if(word_len != 0){
                sent->is_len_3 = (word_len <= 3) * sent->is_len_3;
                word_len = 0;
            }
            j++;
        }
        if(sent->is_len_3){
            delete_sent(text, i);
            i--;
        }

    }
}

void get_metadata(struct text *text){
    for(int i = 0; i < text->num_sent; i++){
        int max_word_len = 0;
        int words_sum = 0;
        int word_len = 0;
        struct sentence *sent = &text->sents[i];
        int j = 0;
        while(sent->words[j]){
            wprintf(L"LOG simb in proc - %lc\n", sent->words[j]);
            if(is_end_word(sent->words[j])){
                word_len++;
            }else if(word_len != 0){
                max_word_len = MAX_AB(word_len, max_word_len);
                word_len = 0;
                words_sum++;
            }
            j++;
        }
        sent->words_sum = words_sum;
        sent->max_word_len = max_word_len;
        sent->simb_sum = (int) wcslen(sent->words);
    }
}

int is_end_word(wchar_t wchar){
    if(wchar != L' ' && wchar != L',' && wchar != L'.' && wchar != L'\n'){
        return 1;
    }
    return 0;
}

int sentence_comparator(struct sentence *sent1, struct sentence *sent2){
    if(sent1->first_word_len > sent2->first_word_len){
        return 1;
    }else if(sent1->first_word_len < sent2->first_word_len){
        return -1;
    }
    return 1;
}