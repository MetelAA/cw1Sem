#ifndef text_h_hF
#define text_h_hF

#include <wchar.h>
#include <stdlib.h>
#include <stdio.h>

struct sentence {
    wchar_t *words;
    int max_word_len, simb_num, first_word_len, is_len_3;
};

struct text {
    struct sentence *sents;
    int num_sent;
};

struct text* read_text();


#endif
