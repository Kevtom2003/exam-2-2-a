#include "main.h"

int main()
{
    int i, nthreads = NUM_THREADS;
    double pi = 0.0, sum[NUM_THREADS][PAD];
    double start1, end1, start2, end2;

    step = 1.0 / (double)num_steps;

    start1 = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();
    // ##### START OF SECTION 1 #####
    // create a vector of n threads
    vector<thread> thread_vec;
    vector<thread> pithread_vec;
    // create n threads
    for(i =0;i<nthreads;i++){
        thread_vec.push_back(thread(single_sum_thread,i,nthreads,sum));
    }
    // join the threads with the main thread
    for(int j=0;j<nthreads;++j){
        thread_vec.at(j).join();
    }
    // ##### END OF SECTION 1 #####
    end1 = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();

    start2 = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();
    // ##### START OF SECTION 2 #####
    for (int j = 0; j < nthreads; j++){
        pithread_vec.push_back(thread(pi_sum_thread, j, sum,std::ref(pi)));
    }
    // join the threads with the main thread
    for (int j = 0; j < nthreads; ++j){
        pithread_vec.at(j).join();
    }
    // for (i = 0, pi = 0.0; i < nthreads; i++)
    // {
    //     pi += sum[i][0] * step;
    //     sleep(1); // simulate a long running task
    // }

    // ##### END OF SECTION 2 #####
    end2 = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();
    

    printf("Number of threads: %i\nCache padding for coherency: %i bytes\n---\n", nthreads, PAD * 8);
    printf("Pi approximation: %f\nTime to complete part 1: %f seconds\nTime to complete part 2: %f seconds\n", pi, (end1 - start1) * 1e-9, (end2 - start2) * 1e-9);
    return 0;
}
