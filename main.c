#include "main.h"
#include <stdio.h>


int main() {
    setlocale(LC_CTYPE, "ru");
    //printf("Course work for option 5.8, created by Artem Metelskii.\n");
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

        break;
        case 3:

        break;
        case 4:

        break;
        case 5:

        break;
        default:
            printf("Error: unknown option\n");
        break;
    }
    return 0;
}
//1
//Lorem ipsum. RepEaTs SEnT. dolor sit amet, consectetur.
//adipiscing elit.
//Предложение на русском. Repeats Sent.
//end sent
//

//Lorem ipsum. RepEaTs SEnT. dolor sit amet, consectetur.
//adipiscing elit.
//Предложение на русском. Repeats Sent.
//end sent

//1
//Hyi. Русский текст епта бля
//
