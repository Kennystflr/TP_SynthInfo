cmake_minimum_required(VERSION 3.30)
project(TP_SynthInfo C)

set(CMAKE_C_STANDARD 11)

add_executable(TP_SynthInfo main.c
        utils.h
        command.c
        printing.c
        tftp.c
        tftp.h)
