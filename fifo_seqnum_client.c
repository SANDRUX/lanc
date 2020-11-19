#include "fifo_seqnum.h"

static char clientFifo[CLIENT_FIFO_NAME_LEN];

static void
removeFifo(void)
{
unlink(clientFifo);
}

int 
main(int argc, char *argv[])
{
    int serverFd, clientFd;
    struct request req;
    struct response resp;

    if (argc > 1 && strcmp(argv[1], "--help") == 0)
        usageErr("%s [seq-len...]\n", argv[0]);

    umask(0);
    snprintf(clientFifo, CLIENT_FIFO_NAME_LEN, CLIENT_FIFO_TEMPLATE, (long) getpid());

    if (mkfifo(clientFifo, S_IRUSR | S_IWUSR | S_IWGRP) == -1 && errno != EEXIST)
        errExit("mkfifo %s", clientFifo);
    
    if (atexit(removeFifo) != 0)
        errExit("atexit");

    req.pid = getpid();
    req.seqLen = (argc > 1) ? getInt(argv[1], GN_GT_0, "seq-len") : 1;

    serverFd = open(SERVER_FIFO, O_WRONLY);
    if (serverFd == -1)
        errExit("open %s", SERVER_FIFO);

    if (write(serverFd, &req, sizeof(struct request)) != sizeof(struct request))
        fatal("Can't write to server");

    clientFd = open(clientFifo, O_RDONLY);
    if (clientFd == -1)
        errExit("open %s", clientFifo);

    if (read(clientFd, &resp, sizeof(struct response)) != sizeof(struct response))
        fatal("Can't read response from server");

    printf("%d\n", resp.seqNum);
    exit(EXIT_SUCCESS);
}
