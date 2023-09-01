cmake_minimum_required(VERSION 3.26)
project(SO_Project C)

set(CMAKE_C_STANDARD 23)

add_executable(SO_Project main.c
        selezione_algoritmi.c
        selezione_algoritmi.h
        processi.h
        cJSON.c
        usa_file_JSON.c
        usa_file_JSON.h
        algoritmo_FCFS.c
        algoritmo_FCFS.h
        algoritmo_SJF.c
        algoritmo_SJF.h
        algoritmo_RR.c
        algoritmo_RR.h
        algoritmo_SRTF.c
        algoritmo_SRTF.h
        utilities.c
        utilities.h
)
target_link_libraries(SO_Project PRIVATE m)
