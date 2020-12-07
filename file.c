#define _POSIX_C_SOURCE 199309
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

int *vector;

typedef struct
{
    int *vec;
    int size;
} pair;

pthread_mutex_t vecMtx = PTHREAD_MUTEX_INITIALIZER, gsdMtx = PTHREAD_MUTEX_INITIALIZER;

int sig_data;
int numberOfThreads;

pthread_t *threadID;
int *ThreadActive;

int guessedValue = 0;

void delay();

void parse_arguments(int, char **, int *);

void *thread_func(void *);

void siginit_handler();

void sigusr1_handler();

void sigquit_handler();

#define ERR(source) (fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), \
                     perror(source), kill(0, SIGKILL),               \
                     exit(EXIT_FAILURE))

void sethandler(void (*f)(int), int sigNo)
{
    struct sigaction act;
    memset(&act, 0, sizeof(struct sigaction));
    act.sa_handler = f;
    if (-1 == sigaction(sigNo, &act, NULL))
        ERR("sigaction");
}

int main(int argc, char *argv[])
{
    int vectorSize;

    if (argc != 3)
    {
        printf("Invalid number of argument!\n");
        exit(EXIT_FAILURE);
    }

    vectorSize = atoi(argv[1]);
    numberOfThreads = atoi(argv[2]);

    vector = (int *)malloc(sizeof(int) * vectorSize);

    memset(vector, 0, vectorSize);

    sig_data = vectorSize;

    //sethandler(SIGINT, siginit_handler);

    sethandler(siginit_handler, SIGINT);
    sethandler(sigusr1_handler, SIGUSR1);
    sethandler(sigquit_handler, SIGQUIT);

    srand(time(NULL));

    /*sigset_t mask;

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGQUIT);

    pthread_sigmask(SIG_BLOCK, &mask, NULL);*/

    threadID = (pthread_t *)malloc(sizeof(pthread_t) * numberOfThreads);
    ThreadActive = (int *)malloc(sizeof(int) * numberOfThreads);

    pair data;

    data.size = vectorSize;
    data.vec = vector;

    for (int i = 0; i < numberOfThreads; i++)
    {

        if (pthread_create(&threadID[i], NULL, thread_func, &data) != 0)
        {
            printf("Couldnt create a thread");
            exit(EXIT_FAILURE);
        }
        ThreadActive[i] = 1;
    }

    while (1)
    {
        for (int i = 0; i < vectorSize; i++)
        {
            printf("vector[%d] = %d\n", i, vector[i]);
        }
        delay();
    }

    return 0;
}

void delay()
{
    struct timespec tim;
    struct timespec res;

    tim.tv_sec = 0;
    tim.tv_nsec = 500000000L;

    //printf("something\n");
    //printf("2nd something");

    for (int er = nanosleep(&tim, &res); er != 0; er = nanosleep(&res, &res))
    {
    }
}

void *thread_func(void *arg)
{

    //pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    //pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    pthread_t thisID = pthread_self();

    //pthread_cleanup_push(cleanup_handler, &thisID);
    //pthread_cleanup_pop(1);

    sigset_t mask;

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGQUIT);

    pthread_sigmask(SIG_BLOCK, &mask, NULL);

    int index;

    while (1)
    {
        sleep(1);

        pair *threadPair = (pair *)arg;
        index = rand() % threadPair->size;

        pthread_mutex_lock(&vecMtx);

        if (vector[index] == 0)
        {
            pthread_mutex_unlock(&vecMtx);
            continue;
        }
        else
        {
            pthread_mutex_lock(&gsdMtx);

            if (vector[index] == guessedValue)
            {
                pthread_mutex_unlock(&vecMtx);
                pthread_mutex_unlock(&gsdMtx);

                kill(getpid(), SIGUSR1);
            }
            else
            {
                guessedValue = vector[index];

                pthread_mutex_unlock(&vecMtx);
                pthread_mutex_unlock(&gsdMtx);
            }
        }
    }
}

void siginit_handler()
{
    //printf("test");

    int randPosition = rand() % sig_data;
    int randValue = (rand() % 255) + 1;

    pthread_mutex_lock(&vecMtx);

    vector[randPosition] = randValue;

    pthread_mutex_unlock(&vecMtx);
}

void sigusr1_handler()
{

    pthread_mutex_lock(&gsdMtx);

    printf("Guessed is:  %d\n", guessedValue);

    pthread_mutex_unlock(&gsdMtx);

    int index;

    do
    {
        index = rand() % numberOfThreads;
    } while (ThreadActive[index] == 0);

    pthread_cancel(threadID[index]);

    ThreadActive[index] = 0;
}

void sigquit_handler()
{
    for (int index = 0; index < numberOfThreads; index++)
    {
        pthread_cancel(threadID[index]);
    }
    printf("SigQuit\n");
    exit(EXIT_SUCCESS);
}
