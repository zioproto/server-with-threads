/*
*/

#include <server-with-threads.h>
#include <client_manager.h>
 
/* -------------------------------------------------------------------------
 * Function   : ClientManager
 * Description: Serves a TCP connection
 * Input      : socket descriptor
 * Output     : none
 * Return     : 0 OK, -1 Error
 * Data Used  : none
 * ------------------------------------------------------------------------- */
int ClientManager(void * acceptsd)
{
	if (debug) printf("Hello, I'm the thread %u client manager\n\n",(int)pthread_self());
	
	int mysd; //my socket descriptor
	int ret;
	
	mysd = *((int *)acceptsd);
	
	if (debug) printf("Socket descriptor %d\n\nWaiting fo data..\n",mysd);

	//SERVE YOUR CLIENT HERE
	
	//Set return code
	ret = 0;

if (debug) printf("Goodbye, I'm the thread %u client manager\n\n",(int)pthread_self());
pthread_mutex_lock(&thread_number_mutex);
thread_number--;
pthread_mutex_unlock(&thread_number_mutex);
return(ret);
}
	
