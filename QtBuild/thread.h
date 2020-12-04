#pragma once

#define _POSIX_C_SOURCE 199309
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

int * vector;

typedef struct
{
    int * vec;
    int size;
}pair;

pthread_mutex_t vecMtx = PTHREAD_MUTEX_INITIALIZER, gsdMtx = PTHREAD_MUTEX_INITIALIZER;

int sig_data;
int numberOfThreads;

pthread_t * threadID;

int guessedValue = 0;

static
void delay();

static
void parse_arguments(int , char ** , int * );

static
void * thread_func(void * );

static
void siginit_handler();

static
void sigusr1_handler();

static
void sigquit_handler();
