cmake_minimum_required(VERSION 3.16)
project(pr1 C)

set(CMAKE_C_STANDARD 11)

add_executable(pr1 main.c text.c text.h process_text.c process_text.h main.h show_text.c show_text.h)