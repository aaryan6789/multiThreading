/*
 * multi_thread_print_even_odd.c
 *
 *  Created on: Mar 27, 2018
 *      Author: hsahu
 */

#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"
#include "multithread.h"

// MUTEX for Locking Synchronization
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;

// Condition Variable for Ordering
pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;
static void *functionCount1();
static void *functionCount2();
static int count = 0;
#define COUNT_DONE 200

// Thread 1 : Print odd numbers
static void *functionCount1() {
  for(;;) {
   // Lock mutex and then wait for signal to release mutex
   pthread_mutex_lock(&count_mutex);

   if ( count % 2 != 0 ) {
     pthread_cond_wait( &condition_var, &count_mutex );
   }
   printf("Counter value functionCount1: %d\n",count);
   count++;

   pthread_cond_signal( &condition_var );

   if ( count >= COUNT_DONE ) {
     pthread_mutex_unlock( &count_mutex );
     return(NULL);
   }

   pthread_mutex_unlock( &count_mutex );
 }
}

// Thread 2: print even numbers
static void *functionCount2() {
  for(;;) {
  // Lock mutex and then wait for signal to relase mutex
  pthread_mutex_lock( &count_mutex );

  if ( count % 2 == 0 ) {
    pthread_cond_wait( &condition_var, &count_mutex );
  }
  printf("Counter value functionCount2: %d\n",count);
  count++;


  pthread_cond_signal( &condition_var );
  if( count >= COUNT_DONE ) {
    pthread_mutex_unlock( &count_mutex );
    return(NULL);
  }
  pthread_mutex_unlock( &count_mutex );
 }
}


void main_even_odd()
{
 pthread_t thread1, thread2;
 pthread_create( &thread1, NULL, &functionCount1, NULL);
 pthread_create( &thread2, NULL, &functionCount2, NULL);
 pthread_join( thread1, NULL);
 pthread_join( thread2, NULL);
 return;
 //exit(0);
}
