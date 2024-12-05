#include "main.h"
#include <stdio.h>


int main() {
    setlocale(LC_CTYPE, "ru");
    printf("Course work for option 5.8, created by Artem Metelskii.\n");
    int n = 0;
    scanf("%d", &n);
    struct text text = read_text();
    switch(n){
        case 0:
            show_text(&text);
        break;
        case 1:
            get_metadata(&text);
            show_metadata(&text);
        break;
        case 2:
            reverse_sentence(&text);
            show_text(&text);
        break;
        case 3:
            sort_by_first_word(&text);
            show_text(&text);
        break;
        case 4:
            delete_less_then_four_symbol_word_sent(&text);
            show_text(&text);
        break;
        case 5:
            printf("spravka haha\n");
        break;
        default:
            printf("Error: unknown option\n");
        break;
    }
    return 0;
}
//4
//Lorem ipsum. RepEaTs SEnT. dolor sit amet, consectetur.
//adipiscing elit. tri sim snt.
//Предложение на русском. Repeats Sent. gggggggggggggggg hiplet.
//end sent

//0
//Lorem ipsum. RepEaTs SEnT. dolor sit amet, consectetur.
//adipiscing elit.
//Предложение на русском. Repeats Sent.
//end sent

//4
//Hyi. tri sim snt. Русский текст епта бля
//
//2
//hello, my best , cw. test

