#include <server-with-threads.h>
#include <server.h>
#include <client_manager.h>
 
 

void server(int portNumber)
{
int 					listensd, //socket descriptors
						acceptsd;
						
int						sin_size = sizeof(struct sockaddr_in);

struct 	sockaddr_in 	serverAddress;
struct 	sockaddr_in 	clientAddress;	

pthread_t 				threadClientManager; 

/* Creo il socket di listening */

if ((listensd = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
    if (debug) perror("Error in listening socket creation\n");
    exit(1);
  }
if (debug) printf("Listening socket %d succesfully created \n\n",listensd);

memset((char *)&serverAddress, 0, sizeof(serverAddress));    // inizializzazione struct
serverAddress.sin_family = AF_INET;
serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
serverAddress.sin_port = htons(portNumber); 

/* eseguo il binding */

  if ((bind(listensd, (struct sockaddr *)&serverAddress, sizeof(serverAddress))) < 0) {
    if (debug) perror("Socket binding error");
    exit(1);
  }
if (debug) printf("Socket binding OK\n\n");
/* mi metto in listening */

  if (listen(listensd, __BACKLOG__) < 0 ) {
    if (debug) perror("Socket listening error\n");
    exit(1);
  }
if (debug) printf("Listening OK\n");

while(1)
	{
		if (debug) printf("I'm waiting for a connection\n\n");

		if ( (acceptsd = accept(listensd,(struct sockaddr *)&clientAddress,&sin_size)) 	< 0) {
			if (debug) perror("Socket accept error\n");
			exit(1);
		}

		else
  		{
			
			//if (thread_number < __MAX_THREADS__) {
			if (thread_number < max_threads) {
				pthread_mutex_lock(&thread_number_mutex);
				thread_number++;
				pthread_mutex_unlock(&thread_number_mutex);
				pthread_create(&threadClientManager,NULL,ClientManager,&acceptsd);
	   			pthread_detach(threadClientManager);
				//if (debug) printf("There are %d active threads\n",thread_number);
				
				openlog("server-with-threads", LOG_WARNING || LOG_PID, LOG_DAEMON);
				syslog(LOG_WARNING,"There are %d active threads\n",thread_number);
				closelog();
				
			}
			else {
				dropped_requests++;
			    if (debug) printf("Active threads: %d\t Drops %d\n",thread_number,dropped_requests);
				//char local[500];
				//memset(local,0,sizeof(local));
				//sprintf(local,"Active threads: %d\t Drops %d\n\n",thread_number,dropped_requests);
				
				//append_log("LOG1.txt", local);
				
				openlog("server-with-threads", LOG_WARNING || LOG_PID, LOG_DAEMON);
				syslog(LOG_WARNING,"Active threads: %d\t Drops %d\n",thread_number,dropped_requests);
				closelog();
				
				close(acceptsd);
			}
		}
 	}

	close(listensd);
}

