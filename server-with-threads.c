/*
Server with threads

*/

#include <server-with-threads.h>
#include <client_manager.h>
#include <server.h>



int debug=1;							//global variable for debug level

int thread_number=0;
int max_threads=__MAX_THREADS__;

pthread_mutex_t thread_number_mutex = PTHREAD_MUTEX_INITIALIZER;	//mutex for thread number

pthread_mutex_t token_mutex = PTHREAD_MUTEX_INITIALIZER; 	//mutex for the token value
pthread_mutex_t serial_mutex = PTHREAD_MUTEX_INITIALIZER;	//mutex for the serial file

int request_counter=0;
int dropped_requests=0;

int sleep_time;							//crl management thread sleeping time 


int main(int argc , char **argv){

int port;

if (argc < 4) {
	
	printf("Usage: server-with-threads portNumber debugLevel MaxThreads\n");
	exit (1);
}

max_threads = atoi(argv[3]);
debug = atoi(argv[2]);
port = atoi(argv[1]);
	
if (debug>2) printf("port %d\t debug%d\t max_threads %d",port,debug,max_threads);

server(port);	


return 0;
}



