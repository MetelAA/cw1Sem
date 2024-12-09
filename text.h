#ifndef text_h_hF
#define text_h_hF

#define STANDARD_TEXT_LEN 3
#define STANDARD_SENT_LEN 100

#include <wchar.h>
#include <stdlib.h>
#include <wctype.h>

struct sentence {
    wchar_t *words;
    int max_word_len, simb_sum, first_word_len, is_len_3, words_sum;
};

struct text {
    struct sentence *sents;
    int num_sent;
};

struct text read_text();
void delete_sent(struct text *text, int sent_number);
void free_mem(struct text *text);

#endif