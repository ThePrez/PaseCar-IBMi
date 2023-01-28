// Copyright (c) 2021 Jesse Gorzinski
// Derived work of "generic server" of OSSILE project, Copyright (c) 2018 Kevin Adler
// https://github.com/OSSILE/OSSILE/blob/master/main/c_generic_server/generic_tcp.c
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <pwd.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>
#include <iconv.h>
#include <qtqiconv.h>
#include <qp0ztrc.h>
#include <qusrjobi.h>
#include <spawn.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include "pasecar.h"

#pragma convert(37)

#define WARN_MSG(e)         \
    {                       \
        fprintf(stderr, e); \
        Qp0zLprintf(e);     \
    }
#define FATAL_MSG(e, c)     \
    {                       \
        fprintf(stderr, e); \
        Qp0zLprintf(e);     \
        exit(c);            \
    }
#define FATAL_MSG_1ARG(e, a, c) \
    {                           \
        fprintf(stderr, e, a);  \
        Qp0zLprintf(e, a);      \
        exit(c);                \
    }

typedef struct handle_stream_args
{
    int fd;
    line_cb cb;
    pid_t pid;
    int is_err;
} handle_stream_args;
static void *handle_stream(void *__args)
{
    handle_stream_args *_args = (handle_stream_args *)__args;
    // Now, let's read the output from the child process and print it here.
    char line[1024 * 4];
    memset(line, 0, sizeof(line));
    int bytesRead = -1;
    char *linePtr = line;
    int rc = -1;
    while ((rc = read(_args->fd, linePtr, 1)) > 0)
    {
        int pos = linePtr - line;
        if (*linePtr == '\n' || pos >= (sizeof(line) - 1))
        {
            *linePtr = '\0';
            int is_abort = _args->cb(line, _args->pid, _args->is_err);
            linePtr = line;
            memset(line, 0, sizeof(line));
        }
        else
        {
            linePtr++;
        }
    }
    if (0 != line[0])
    {
        _args->cb(line, _args->pid, _args->is_err);
    }

    // Close out the descriptor now that data from the pipe is fully consumed
    close(_args->fd);
    return NULL;
}
int is_executable(const char *_file)
{
    struct stat sb;
    return (stat(_file, &sb) == 0 && sb.st_mode & S_IXUSR);
}

int is_bash_there()
{
    return is_executable("/QOpenSys/pkgs/bin/bash");
}
int runpase_main(int argc, char *argv[], line_cb _stderr, line_cb _stdout)
{
    if (argc < 2)
    {
        FATAL_MSG_1ARG("Usage: %s <command>\n", argv[0], 2);
    }
    int rc;
    // First things first, we need an arguments array set up...
    int numArgs = argc + 4;
    char *child_argv[numArgs];
    child_argv[0] = "/QSYS.LIB/QP2SHELL.PGM"; // Note that "/QOpenSys/pkgs/bin/bash" won't work because PASE executables are not allowed
    if (2 == argc)
    {
        int is_bash = is_bash_there();
        child_argv[1] = is_bash ? "/QOpenSys/pkgs/bin/bash" : "/QOpenSys/usr/bin/sh";
        child_argv[2] = is_bash ? "-lc" : "-c";
        child_argv[3] = argv[1];
        child_argv[4] = NULL;
    }
    else
    {
        struct stat sb;
        if (!is_executable(argv[1]))
        {
            FATAL_MSG_1ARG("Error: %s is not executable\n", argv[1], 8);
        }
        for (int i = 1; i < argc; i++)
        {
            child_argv[i] = argv[i];
        }
        child_argv[argc] = NULL;
    }

    // ...and an environment for the child process...
    char *envp[10];
    envp[0] = "QIBM_MULTI_THREADED=Y";
    envp[1] = "QIBM_USE_DESCRIPTOR_STDIO=Y";
    envp[2] = "PASE_STDIO_ISATTY=N";
    struct passwd *pd;
    char logname[20];
    if (NULL != (pd = getpwuid(getuid())))
    {
        sprintf(logname, "LOGNAME=%s", pd->pw_name);
    }
    else
    {
        sprintf(logname, "LOGNAME=%s", getenv("LOGNAME"));
    }
    envp[3] = logname;
    envp[4] = (char *)NULL;
    // envp[4] = "QIBM_PASE_DESCRIPTOR_STDIO=B";
    envp[5] = (char *)NULL;

    // ...and we need to set up the pipes...
    int stdoutFds[2];
    if (pipe(stdoutFds) != 0)
    {
        FATAL_MSG("failure on stdout pipe", 9);
        return 1;
    }
    int stderrFds[2];
    if (pipe(stderrFds) != 0)
    {
        FATAL_MSG("failure on stderr pipe", 10);
    }

    int fd_map[3];
    fd_map[0] = open("/dev/null", O_RDONLY);
    fd_map[1] = stdoutFds[1];
    fd_map[2] = stderrFds[1];

    // ...and we want to spawn a multithread-capable job...
    struct inheritance inherit;
    memset(&inherit, 0, sizeof(inherit));
    inherit.flags = SPAWN_SETTHREAD_NP;

    // ...and we can FINALLY run our command!
    pid_t child_pid = spawnp(child_argv[0], // executable
                             3,             // fd_count
                             fd_map,        // fd_map[]
                             &inherit,      // inherit
                             child_argv,    // argv
                             envp);         // envp
    if (child_pid == -1)
    {
        FATAL_MSG_1ARG("Error spawning child process: %s\n", strerror(errno), -1);
    }
    close(stdoutFds[1]);
    close(stderrFds[1]);

    // Now time to read from the child
    pthread_t stderr_thread;
    handle_stream_args stderr_reader_args;
    stderr_reader_args.cb = _stderr;
    stderr_reader_args.fd = stderrFds[0];
    stderr_reader_args.pid = child_pid;
    stderr_reader_args.is_err = 1;
    int pthread_rc = pthread_create(
        &stderr_thread,     // pthread_t (result)
        NULL,               // attr
        handle_stream,      // function
        &stderr_reader_args // args
    );
    if (0 != pthread_rc)
    {
        WARN_MSG("Unable to create thread. Standard error will be out of sequence.\n");
    }
    handle_stream_args stdout_reader_args;
    stdout_reader_args.cb = _stdout;
    stdout_reader_args.fd = stdoutFds[0];
    stdout_reader_args.pid = child_pid;
    stdout_reader_args.is_err = 0;
    handle_stream(&stdout_reader_args);

    if (0 == pthread_rc)
    {
        pthread_join(stderr_thread, NULL);
    }
    else
    {
        handle_stream(&stderr_reader_args);
    }
    // Close out the descriptors now that data from the pipe is fully consumed
    close(stdoutFds[0]);
    close(stderrFds[0]);

    // Wait for the child process to finish (should be already done since the pipe is closed)
    waitpid(child_pid, &rc, 0);

    return rc;
}