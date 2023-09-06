cmake_minimum_required(VERSION 3.26)
project(SO_Project C)

set(CMAKE_C_STANDARD 23)

add_executable(SO_Project main.c
        utilities_algoritmi.c
        utilities_algoritmi.h
        processi.h
        cJSON.c
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

#gcc -o eseguibile main.c utilities.c utilities_algoritmi.c cJSON.c algoritmo_RR.c algoritmo_FCFS.c algoritmo_SJF.c algoritmo_SRTF.c -lm