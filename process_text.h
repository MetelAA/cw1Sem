#ifndef process_text_hF
#define process_text_hF
#include "text.h"
#include <stdlib.h>
#include <wchar.h>
#include <stdio.h>

void reverse_sentence(struct text *text);
void sort_by_first_word(struct text *text);
void del_less_then_four_symbol_word_sent(struct text *test);
void get_metadata(struct text *text);

#endif
