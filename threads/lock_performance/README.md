Threading Examples
=======
wenhui-2:threads WenhuiZhang$ ./lock_performance
-----------------------------
lock performance for 1 thread with 10000 loops
Total time cost by running 1 threads for increase function with lock implementation: 0.000686
secStarting of the program, start_t = 2327
End of the process end_t = 3138
Total time cost by running 1 threads for increase function without lock implementation: 0.000092 sec
Mutex Time Cost by running 1 threads for increase function: 0.000594 sec
Per thread Mutex Time Cost by running 1 threads for increase function: 0.000594 sec
-----------------------------
lock performance for 2 thread with 10000 loops
Total time cost by running 2 threads for increase function with lock implementation: 0.048873
secStarting of the program, start_t = 3170
End of the process end_t = 52294
Total time cost by running 2 threads for increase function without lock implementation: 0.000227 sec
Mutex Time Cost by running 2 threads for increase function: 0.048646 sec
Per thread Mutex Time Cost by running 2 threads for increase function: 0.024323 sec
-----------------------------
lock performance for 4 thread with 10000 loops
Total time cost by running 4 threads for increase function with lock implementation: 0.173181
secStarting of the program, start_t = 52315
End of the process end_t = 225927
Total time cost by running 4 threads for increase function without lock implementation: 0.000407 sec
Mutex Time Cost by running 4 threads for increase function: 0.172774 sec
Per thread Mutex Time Cost by running 4 threads for increase function: 0.043194 sec
-----------------------------
-----------------------------
lock performance for 16 thread with 10000 loops
Total time cost by running 16 threads for increase function with lock implementation: 0.664478
secStarting of the program, start_t = 225953
End of the process end_t = 892292
Total time cost by running 16 threads for increase function without lock implementation: 0.001840 sec
Mutex Time Cost by running 16 threads for increase function: 0.662638 sec
Per thread Mutex Time Cost by running 16 threads for increase function: 0.041415 sec
-----------------------------