#include <time.h>
#include "eventTrace.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <boost/date_time.hpp>
#include <iostream>
#include <linux/getcpu.h>
#include <sched.h>
#include <sys/syscall.h>
#include <thread>
#include <mutex>
#include <iostream>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <boost/shared_ptr.hpp>
#include <memory>
#include <thread>
#include <atomic>
 
std::atomic<long long> data;

int set_cpu(int i)  
{  
    cpu_set_t mask;  
    CPU_ZERO(&mask);  
  
    CPU_SET(i,&mask);  
  
    printf("thread %u, i = %d\n", pthread_self(), i);  
    if(-1 == pthread_setaffinity_np(pthread_self() ,sizeof(mask),&mask))  
    {  
        fprintf(stderr, "pthread_setaffinity_np erro\n");  
        return -1;  
    }  
    return 0;  
}  

void usleep(long long us)
{
    struct timespec req;
    struct timespec left;
    req.tv_sec=0;
    req.tv_nsec=us*1000;

    nanosleep(&req, &left);

};

#define PREPARETOMEASUREBY_TSCP unsigned aux
//rdtscp can avoid of Out-Of-Order
#define READ_TSCP(low, high) do {\
    asm volatile ( "rdtscp\n" : "=a" (low), "=d" (high), "=c" (aux) : : );\
} while(false)

#define READ_TSC(low, high) do {\
    asm volatile("rdtsc" : "=a"(low), "=d"(high) );\
} while(false)
struct TSC{
       unsigned int low; 
       unsigned int high;
};

union TSC_UNION {
    TSC t;
    unsigned long long count;
};

const size_t Loop = 20;
int main()
{
    set_cpu(3);

    auto seq = 0;
    while(1)
    {
        seq++;
        {
            trace_begin("Trace-"+std::to_string(seq));
            volatile int i=0;
            while(i++ < 1*1024*1024);
            trace_end();
        }
    }
}
