#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <sys/types.h>  
#include <pthread.h>  
#include <assert.h>  
  
typedef struct worker  
{  
    void *(*process) (void *arg);  
    void *arg;  
    struct worker *next;  
} CThread_worker;  
  
typedef struct  
{  
    pthread_mutex_t queue_lock;  
    pthread_cond_t queue_ready;  
    CThread_worker *queue_head;  
    int shutdown;  
    pthread_t *threadid;  
    int max_thread_num;  
    int cur_queue_size;  
} CThread_pool;  
  
void pool_init (int max_thread_num);
int pool_destroy ();
int pool_add_worker (void *(*process) (void *arg), void*arg);  
void *thread_routine (void *arg);  
static CThread_pool *pool = NULL; 
