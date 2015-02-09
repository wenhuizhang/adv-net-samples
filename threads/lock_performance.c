/*
 * measures the performance cost by time of using locks in multi-thread program
 * Measure the overhead of calling lock and unlock depending on the level of contention
 * by utilizing clock(), in time.h
 * Author: Wenhui Zhang， Hu Yang
 */



#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>


int n;
/* thread_incr: thread function for multi-thread generation */
void thread_incr()
{
    pthread_mutex_t count_mutex;
    pthread_mutex_lock(&count_mutex);
    
    n = n + 1;
    printf("%d \n", n);
    
    pthread_mutex_unlock(&count_mutex);
    
}


/* compare_and_swap: thread function for multi-thread generation */
void compare_and_swap()
{
    pthread_mutex_t count_mutex;
    pthread_mutex_lock(&count_mutex);
    
    int oldvalue = 3;
    int newvalue = 4;
    int *ptr = &newvalue;
    int temp = *ptr;
    if(*ptr == oldvalue)
        *ptr = newvalue;
    
    pthread_mutex_unlock(&count_mutex);
    
}




int main(void)
{
    clock_t start_t, end_t;
    double total_t; //time counter
    int rc;
    int num_threads; // number of threads
    int tnum; //counter for threads
    
    
    num_threads = 10;
    
    pthread_t  thread_info[num_threads];	// thread identifier
    
    /* Test for thread_incr */
    start_t = clock();
    printf("Starting of the program, start_t = %ld\n", start_t);
    
    
    for (tnum = 0; tnum < num_threads; tnum++){
        printf("create thread %d\n", tnum);
        
        rc = pthread_create(&thread_info[tnum], NULL, (void*)&thread_incr, &tnum);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(1);
        }
    }
    
    
    for (tnum = 0; tnum < num_threads; tnum++){
        pthread_join(thread_info[tnum], NULL);
    }
    
    
    end_t = clock();
    printf("End of the process end_t = %ld\n", end_t);
    total_t = (double)((end_t - start_t) / (double)CLOCKS_PER_SEC);
    printf("Total time cost by running %d of threads for increase function: %f\n", num_threads, total_t);
    
    
    
    /* Test for thread compare and swap */
    
    
    start_t = clock();
    printf("Starting of the program, start_t = %ld\n", start_t);
    
    
    for (tnum = 0; tnum < num_threads; tnum++){
        printf("create thread %d\n", tnum);
        
        rc = pthread_create(&thread_info[tnum], NULL, (void*)&compare_and_swap, &tnum);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(1);
        }
    }
    
    
    for (tnum = 0; tnum < num_threads; tnum++){
        pthread_join(thread_info[tnum], NULL);
    }
    
    
    end_t = clock();
    printf("End of the process end_t = %ld\n", end_t);
    total_t = (double)((end_t - start_t) / (double)CLOCKS_PER_SEC);
    printf("Total time cost by running %d of threads for compare and swap function: %f\n", num_threads, total_t);
    
    
    
    
    printf("Exiting of the program...\n");
    
    return 0;
}
