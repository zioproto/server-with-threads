/*
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h> 
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>
#include <errno.h>
#include <sys/stat.h>

#include <syslog.h>
#include <assert.h>

#define __BACKLOG__     5
#define __MAX_THREADS__ 10

extern int debug;
extern int sleep_time;
extern pthread_mutex_t thread_number_mutex;

extern int thread_number;
extern int max_threads;

extern int dropped_requests;

