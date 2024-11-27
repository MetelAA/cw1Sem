#ifndef text_h_hF
#define text_h_hF

#include <wchar.h>

struct sentence {
    wchar_t *sent;
    int num_word, max_word_len, simb_num, first_word_len, is_len_3;
};

struct text {
    wchar_t **word;
    int num_sent;
};

void read_text(struct text *text);


#endif
