#pragma once 
#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>


static inline int trace_init()
{
    static int trace_marker_fd = -2;

    if(trace_marker_fd != -2)
        return trace_marker_fd;

    trace_marker_fd = open("/sys/kernel/debug/tracing/trace_marker", O_WRONLY);
    if (trace_marker_fd == -1) {
        printf("Error opening trace file: %s (%d)\n", strerror(errno), errno);
        exit(-1);
    }   
    else
        return trace_marker_fd;
}

#define TRACE_MESSAGE_LENGTH 256
//#define TRACE_BEGIN() trace_begin(__PRETTY_FUNCTION__)
#define TRACE_BEGIN() trace_begin(__FUNCTION__)
#define TRACE_END() trace_end()
static inline void trace_begin(const char* name)
{
    char buf[TRACE_MESSAGE_LENGTH];
    size_t len;

    if(trace_init() == -1)
    {
        printf("trace_begin: trace_marker doesn't open\n");
        return ;
    }
    len = snprintf(buf, TRACE_MESSAGE_LENGTH, "B|%d|%s", getpid(), name);
    size_t ret = write(trace_init(), buf, len);
#ifdef TRACE_DEBUG
    if(ret != len)
    {
        printf("trace_marker failed to write %s(len=%d ret=%d)(%d: %s)\n", buf, len, ret, errno, strerror(errno));
    }
#endif
}

static inline void trace_begin(const std::string& name)
{
    trace_begin(name.c_str());
}

static inline void trace_end()
{
    if(trace_init() == -1)
    {
        //printf("trace_end: trace_marker doesn't open\n");
        return ;
    }

    char c = 'E';
    write(trace_init(), &c, 1);
}

class ScopedTrace {
public:
    inline ScopedTrace(const char *name)
    {
        trace_begin(name);
    }

    inline ScopedTrace(const std::string& name)
    {
        trace_begin(name);
    }

    inline ~ScopedTrace()
    {
        trace_end();
    }

};
