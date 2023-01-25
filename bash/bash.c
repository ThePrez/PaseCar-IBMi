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
#pragma convert(37)

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        exit(8);
    }
    int rc;
    // First things first, we need an arguments array set up...
    int numArgs = argc + 4;
    char *child_argv[numArgs];
    child_argv[0] = "/QSYS.LIB/QP2SHELL.PGM"; // Note that "/QOpenSys/pkgs/bin/bash" won't work because PASE executables are not allowed
    if (2 == argc)
    {
#ifdef DO_BASH
        child_argv[1] = "/QOpenSys/pkgs/bin/bash";
#else
        child_argv[1] = "/QOpenSys/pkgs/bin/bash";
#endif
        child_argv[2] = "-l";
        child_argv[3] = "-c";
        child_argv[4] = argv[1];
        child_argv[5] = NULL;
    }
    else
    {
        struct stat sb;
        if (!(stat(argv[1], &sb) == 0 && sb.st_mode & S_IXUSR))
        {
            fprintf(stderr, "Error: %s is not executable\n", argv[1]);
            Qp0zLprintf("Error: %s is not executable\n", argv[1]);
            exit(8);
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
    else {
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
        fprintf(stderr, "failure on pipe\n");
        return 1;
    }
    int fd_map[3];
    fd_map[0] = open("/dev/null", O_RDONLY);
    fd_map[1] = stdoutFds[1];
    fd_map[2] = stdoutFds[1];

    // ...and we want to spawn a multithread-capable job...
    struct inheritance inherit;
    memset(&inherit, 0, sizeof(inherit));
    inherit.flags = SPAWN_SETTHREAD_NP;

    // ...and we can FINALLY run our command!
    pid_t child_pid = spawnp(child_argv[0], //executable
                             3,             // fd_count
                             fd_map,        //fd_map[]
                             &inherit,      //inherit
                             child_argv,    //argv
                             envp);         //envp
    if (child_pid == -1)
    {
        fprintf(stderr, "Error spawning child process: %s\n", strerror(errno));
        Qp0zLprintf("Error spawning child process: %s\n", strerror(errno));
        return -1;
    }
    // We don't need to talk to the child's stdin, so let's close it.
    close(stdoutFds[1]);

    // Now, let's read the output from the child process and print it here.
    char line[1024 * 4];
    memset(line, 0, sizeof(line));
    int bytesRead = -1;
    char *linePtr = line;
    while ((rc = read(stdoutFds[0], linePtr, 1)) > 0)
    {
        int pos = linePtr - line;
        if (*linePtr == '\n' || pos >= (sizeof(line) - 1))
        {
            *linePtr = '\0';
            Qp0zLprintf("%s\n", line);
            printf("%s\n", line);
            linePtr = line;
            memset(line, 0, sizeof(line));
        }
        else
        {
            linePtr++;
        }
    }
    Qp0zLprintf("%s\n", line);
    printf("%s\n", line);

    // Close out the descriptor now that data from the pipe is fully consumed
    close(stdoutFds[0]);

    // Wait for the child process to finish (should be already done since the pipe is closed)
    waitpid(child_pid, &rc, 0);
    //printf("done waiting. rc=%d\n",rc);
    return rc;
}