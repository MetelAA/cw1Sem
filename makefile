all: comp

comp: main.o process_text.o text.o show_text.o
	gcc main.o process_text.o text.o show_text.o -o cw

main.o: main.c main.h text.h show_text.h process_text.h
	gcc -c main.c

process_text.o: process_text.c process_text.h text.h
	gcc -c process_text.c

text.o: text.c text.h
	gcc -c text.c

show_text.o: show_text.c show_text.h text.h
	gcc -c show_text.c

