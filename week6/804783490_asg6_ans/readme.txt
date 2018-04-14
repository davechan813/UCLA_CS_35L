1. 
change Makefile
lin19: LDLIBS = -pthread -lm

2. 
change main.c

  1. #include <pthread.h>

  2. comment the if statement exiting the program if it is

  3. create all threads one by one
    for (index = 0; index < nthreads; ++index) {
        
        threads_id[index] = index;

        // printf("In main: creating thread %d\n", index);

        result_code = pthread_create(&threads[index], NULL, thread_func, &threads_id[index]);
        assert(!result_code);
    }

  4. wait and join threads    
    for (index = 0; index < nthreads; ++index) {
        // block until thread 'index' completes
        result_code = pthread_join(threads[index], NULL);
        assert(!result_code);
        // printf("In main: thread %d has completed\n", index);
    }

  5. extract the nested for-loops as well as declaration and initialization above the for-loops into thread_func function 

  6. declare scene and nthreads as a global variable to use both in thread_func and main functions.

  7. to avoid race condition in printing, declare an extra 3-D array to store all the data to print, and print this array 
     after all the threads terminates.

3. 
Test output correctness
$ ./srt 1 > output.ppm     ---->    This is the original version
$ ./srt 1 > output1.ppm
$ ./srt 2 > output2.ppm
$ ./srt 4 > output4.ppm
$ ./srt 8 > output8.ppm

$ diff output.txt output1.ppm
$ diff output.txt output2.ppm
$ diff output.txt output4.ppm
$ diff output.txt output8.ppm

All commands output nothing

4. 
Test time efficiency
$ time -p ./srt 1
real 52.43
user 44.27
sys 0.61

$ time -p ./srt 2
real 20.57
user 40.11
sys 0.21

$ time -p ./srt 4
real 18.72
user 67.45
sys 0.33

$ time -p ./srt 8
real 10.17
user 62.04
sys 0.35


























