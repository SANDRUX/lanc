#include "thread.h"

int main(int argc, char * argv[])
{
    int insert_status_array[2];
    int vectorSize;

    parse_arguments((argc - 1), argv, insert_status_array);

    vectorSize = insert_status_array[0];
    numberOfThreads = insert_status_array[1];

    vector = (int *)malloc(sizeof(int) * vectorSize);

    memset(vector, 0, vectorSize);

    sig_data = vectorSize;

    if (signal(SIGINT, siginit_handler) == SIG_ERR)
    {
        printf("SIGINIT failed!");
        exit(EXIT_FAILURE);
    }
    if (signal(SIGUSR1, sigusr1_handler) == SIG_ERR)
    {
        printf("SIGUSR1 failed!");
        exit(EXIT_FAILURE);
    }
    if (signal(SIGQUIT, sigquit_handler) == SIG_ERR)
    {
        printf("SIGQUIT failed!");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    threadID = (pthread_t *)malloc(sizeof(pthread_t) * numberOfThreads);

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
    }

    while(1)
    {
        for (int i = 0; i < vectorSize; i++)
        {
            printf("vector[%d] = %d\n", i, vector[i]);
        }
        delay();
    }

    return 0;
}

static
void delay()
{
    struct timespec tim;

    tim.tv_sec = 0;
    tim.tv_nsec = 500000000L;

    //printf("something\n");

    if (nanosleep(&tim, NULL) != 0)
    {
        perror("");
        exit(EXIT_FAILURE);
    }
    //printf("2nd something");
}

static
void parse_arguments(int numCommands, char ** commands, int * statusArray)
{
    if (numCommands != 4)
    {
        printf("Wrong number of arguments!");
        exit(EXIT_FAILURE);
    }
    else if (strcmp(commands[1], "-n") == 0 && strcmp(commands[3], "-t") == 0)
    {
        statusArray[0] = atoi(commands[2]);
        statusArray[1] = atoi(commands[4]);

        if (statusArray[0] == 0 || statusArray[1] == 0)
        {
            printf("Invalid type of argument");
            exit(EXIT_FAILURE);
        }
    }
    else if (strcmp(commands[3], "-n") == 0 && strcmp(commands[1], "-t") == 0)
    {
        statusArray[0] = atoi(commands[4]);
        statusArray[1] = atoi(commands[2]);

        if (statusArray[0] == 0 || statusArray[1] == 0)
        {
            printf("Invalid type of argument");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        printf("Invalid arguments!");
        exit(EXIT_FAILURE);
    }

}

static
void * thread_func(void * arg)
{

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

        pair * threadPair = (pair *)arg;
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

static
void siginit_handler()
{
    int randPosition = rand() % sig_data;
    int randValue = (rand() % 255 ) + 1;

    pthread_mutex_lock(&vecMtx);

    vector[randPosition] = randValue;

    pthread_mutex_unlock(&vecMtx);
}

static
void sigusr1_handler()
{
    pthread_mutex_lock(&gsdMtx);

    printf("Guessed is:  %d\n", guessedValue);

    pthread_mutex_unlock(&gsdMtx);

    int index;

    do
    {
        index = rand() % numberOfThreads;
    }
    while (threadID[index] == (pthread_t)-1);

    pthread_cancel(threadID[index]);
}

static
void sigquit_handler()
{
    exit(EXIT_SUCCESS);
}
