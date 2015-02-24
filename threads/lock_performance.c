/*
 * measures the performance cost by time of using locks in multi-thread program
 * Measure the overhead of calling lock and unlock depending on the level of contention
 * by utilizing clock(), in time.h
 * Author: Wenhui Zhang， Hu Yang, Pradeep
 */



#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>



int ctr;
pthread_mutex_t count_mutex;
clock_t start_t, end_t, acc_lock_t, acc_no_lock_t;



/* thread_lock: thread function for multi-thread generation */
void thread_lock()
{
    start_t = clock();
    pthread_mutex_lock(&count_mutex);
    ctr = ctr + 1;
    //printf("%d \n", ctr);
    
    pthread_mutex_unlock(&count_mutex);
    end_t = clock();
    acc_lock_t = acc_lock_t + (end_t - start_t);
    
}


/* thread_no_lock: thread function for multi-thread generation */
void thread_no_lock()
{
    start_t = clock();
    ctr = ctr + 1;
    //printf("%d \n", ctr);
    end_t = clock();
    acc_no_lock_t = acc_no_lock_t + (end_t - start_t);
    
}





int lock_performance(int num_threads)
{
    
    acc_lock_t = 0;
    acc_no_lock_t = 0;
    double total_t_lock, total_t_unlock; //time counter
    int rc;
    int tnum; //counter for threads
    pthread_mutex_init(&count_mutex, NULL); //initialize mutex
    
    
    
    pthread_t  thread_info[num_threads];	// thread identifier
    
    /* Test for thread_incr_lock */
    
    
    
    
    for (tnum = 0; tnum < num_threads; tnum++){
        //printf("create thread %d\n", tnum);
        
        rc = pthread_create(&thread_info[tnum], NULL, (void*)&thread_lock, NULL);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(1);
        }
    }
    
    
    for (tnum = 0; tnum < num_threads; tnum++){
        pthread_join(thread_info[tnum], NULL);
    }
    
    
    total_t_lock = (double)((acc_lock_t) / (double)CLOCKS_PER_SEC);
    printf("Total time cost by running %d threads for increase function with lock implementation: %f\n sec", num_threads, total_t_lock);
    
    
    
    /* Test for thread_incr_unlock */
    
    ctr = 0;
    
    printf("Starting of the program, start_t = %ld\n", start_t);
    
    start_t = clock();
    for (tnum = 0; tnum < num_threads; tnum++){
        //printf("create thread %d\n", tnum);
        
        rc = pthread_create(&thread_info[tnum], NULL, (void*)&thread_no_lock, NULL);
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
    total_t_unlock = (double)((acc_no_lock_t) / (double)CLOCKS_PER_SEC);
    printf("Total time cost by running %d threads for increase function without lock implementation: %f sec\n", num_threads, total_t_unlock);
    
    
    
    
    printf("Mutex Time Cost by running %d threads for increase function: %f sec\n", num_threads, total_t_lock - total_t_unlock);
    printf("Per thread Mutex Time Cost by running %d threads for increase function: %f sec\n ", num_threads,(total_t_lock - total_t_unlock)/(double)num_threads);
    
    printf("Exiting of the program...\n");
    
    return 0;
}


int main(void)
{
    printf("-----------------------------\n");
    printf("lock performance for 1 thread\n");
    
    lock_performance(1);
    printf("-----------------------------\n");
    printf("lock performance for 10000 thread\n");
    
    lock_performance(10000);
    return 0;
}







