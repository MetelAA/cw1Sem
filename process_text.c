#include "process_text.h"

int is_end_word(wchar_t wchar);
int sentence_comparator(struct sentence *sent1, struct sentence *sent2);



void reverse_sentence(struct text *text) {
    for(int i = 0; i < text->num_sent; i++){
        struct sentence *sent = &text->sents[i];
        wchar_t *new_words = malloc(sizeof(wchar_t) * (wcslen(sent->words)+1));
        new_words[wcslen(sent->words)] = L'\0';
        new_words[wcslen(sent->words) - 1] = L'.';
        int new_words_p = 0;
        int ind_word_start = 0;
        for(int j = (int) wcslen(sent->words)-2; j >= 0; j--){
            if(ind_word_start == 0 && is_end_word(sent->words[j])){
                ind_word_start = j;
            }else if(!is_end_word(sent->words[j]) && ind_word_start != 0){
                for(int k = j+1; k <= ind_word_start; k++){
                    new_words[new_words_p] = sent->words[k];
                    new_words_p++;
                }
                ind_word_start = j;
                while(!is_end_word(sent->words[j])){
                    j--;
                }
                j++;
                for(int k = j; k <= ind_word_start; k++){
                    new_words[new_words_p] = sent->words[k];
                    new_words_p++;
                }
                ind_word_start = 0;
            }else if(j == 0){
                for(int k = j; k <= ind_word_start; k++){
                    new_words[new_words_p] = sent->words[k];
                    new_words_p++;
                }
            }
        }
        sent->words = new_words;
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