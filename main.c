#include "main.h"


int main() {
    setlocale(LC_ALL, "");
    wprintf(L"Course work for option 5.8, created by Artem Metelskii.\n");
    int n = 0;
    wscanf(L"%d", &n);
    struct text text;
    switch(n){
        case 0:
            text = read_text();
            show_text(&text);
            free_mem(&text);
        break;
        case 1:
            text = read_text();
            get_metadata(&text);
            show_metadata(&text);
            free_mem(&text);
        break;
        case 2:
            text = read_text();
            reverse_sentence(&text);
            show_text(&text);
            free_mem(&text);
        break;
        case 3:
            text = read_text();
            sort_by_first_word(&text);
            show_text(&text);
            free_mem(&text);
        break;
        case 4:
            text = read_text();
            delete_less_then_four_symbol_word_sent(&text);
            show_text(&text);
            free_mem(&text);
        break;
        case 5:
            show_help();
        break;
        default:
            wprintf(L"Error: unknown option\n");
        break;
    }
    return 0;
}