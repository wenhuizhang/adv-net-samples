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
clock_t start_t, end_t, acc_lock_t, acc_atomic_t;




/* thread_lock: thread function for multi-thread generation */
void thread_lock()
{
    start_t = clock();
    for ( int i = 0; i < 100; i++){
        pthread_mutex_lock(&count_mutex);
    
        ctr = ctr + 1;
        //printf("%d \n", ctr);
    
        pthread_mutex_unlock(&count_mutex);
    }
    end_t = clock();
    acc_lock_t = acc_lock_t + (end_t - start_t);
}


/* thread_atomic: thread function for multi-thread generation */
void thread_atomic()
{
    start_t = clock();
    for ( int i = 0; i < 100; i++){
    __sync_add_and_fetch(&ctr, 1);
    //printf("%d \n", ctr);
    }
    end_t = clock();
    acc_atomic_t = acc_atomic_t + (end_t - start_t);
    
}


/* compare_and_swap: thread function for multi-thread generation */
/*
 void compare_and_swap()
 {
 
 pthread_mutex_lock(&count_mutex);
 
 int oldvalue = 3;
 int newvalue = 4;
 int *ptr = &newvalue;
 int temp = *ptr;
 if(*ptr == oldvalue)
 *ptr = newvalue;
 
 pthread_mutex_unlock(&count_mutex);
 
 }
 */




int atomic_comp(int num_threads)
{
    acc_lock_t = 0;
    acc_atomic_t = 0;
    
    printf("Start of %d thread calculating...\n", num_threads);
    double total_t_lock, total_t_unlock; //time counter
    int rc;
    int tnum; //counter for threads
    pthread_mutex_init(&count_mutex, NULL); //initialize mutex
    
    
    pthread_t  thread_info[num_threads];	// thread identifier
    
    /* Test for thread_incr_lock */
    
    start_t = clock();
    
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
    
    
    
    total_t_lock = (double)(acc_lock_t / (double)CLOCKS_PER_SEC);
    printf("Total time cost by running %d threads for increase function with lock implementation: %f\n sec", num_threads, total_t_lock);
    
    
    
    /* Test for thread_atomic */
    
    ctr = 0;
    
    
    start_t = clock();
    for (tnum = 0; tnum < num_threads; tnum++){
        //printf("create thread %d\n", tnum);
        
        rc = pthread_create(&thread_info[tnum], NULL, (void*)&thread_atomic, NULL);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(1);
        }
    }
    
    
    for (tnum = 0; tnum < num_threads; tnum++){
        pthread_join(thread_info[tnum], NULL);
    }
    
    
    total_t_unlock = (double)(acc_atomic_t / (double)CLOCKS_PER_SEC);
    printf("Total time cost by running %d threads for increase function with atomic: %f sec\n", num_threads, total_t_unlock);
    
    
    
    printf("Mutex Time Cost Against Atomic by running %d threads for increase function: %f sec\n", num_threads, total_t_lock - total_t_unlock);
    
    
    printf("Per thread Mutex Time Cost Against Atomic by running %d threads for increase function: %f sec\n", num_threads, (total_t_lock - total_t_unlock)/(double)num_threads);
    
    printf("End of %d thread calculating...\n", num_threads);
    
    return 0;
}



int main(void)
{
    printf("------------------------\n");
    atomic_comp(20);
    printf("------------------------\n");
    atomic_comp(1);
    printf("------------------------\n");
    atomic_comp(1000);
    
    return 0;
    
}
