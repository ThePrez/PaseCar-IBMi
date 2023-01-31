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

#include <stdio.h>
#include <qp0ztrc.h>

#include "pasecar.h"

#pragma convert(37)

typedef struct ignore_handler_arg
{
    int do_print;
    int do_joblog;
} ignore_handler_arg;
int ignoreHandler(char *_line, pid_t _pid, int _is_err, void *_arg)
{
    if (NULL == _arg)
    {
        return 0;
    }
    ignore_handler_arg *arg = (ignore_handler_arg *)_arg;
    if (arg->do_joblog)
    {
        Qp0zLprintf("%s%s\n", _is_err ? "ERROR: " : "", _line);
    }
    if (arg->do_print)
    {
        FILE *dest = _is_err ? stderr : stdout;
        fprintf(dest, "%s: %s\n", _line);
        fflush(dest);
    }
    return 0;
}
int runpase_rconly(char *_cmd)
{
    int rc = -1;
    pid_t pid;
    runpase_cb(&rc, &pid, false, false, _cmd, ignoreHandler, ignoreHandler, NULL);
    return rc;
}
int runpase_rconly_nd(char *_cmd)
{
    int rc = -1;
    pid_t pid;
    runpase_nd(&rc, &pid, false, _cmd);
    return rc;
}
int runpase_rconly_log(char *_cmd)
{
    int rc = -1;
    pid_t pid;
    ignore_handler_arg handler_arg;
    handler_arg.do_joblog = 1;
    handler_arg.do_print = 0;
    runpase_cb(&rc, &pid, false, false, _cmd, ignoreHandler, ignoreHandler, &handler_arg);
    return rc;
}
int runpase_rconly_logandprint(char *_cmd)
{
    int rc = -1;
    pid_t pid;
    ignore_handler_arg handler_arg;
    handler_arg.do_joblog = 1;
    handler_arg.do_print = 1;
    runpase_cb(&rc, &pid, false, false, _cmd, ignoreHandler, ignoreHandler, &handler_arg);
    return rc;
}

int runpasev_rconly_log(int _argc, char *_cmd[])
{
    int rc = -1;
    pid_t pid;
    ignore_handler_arg handler_arg;
    handler_arg.do_joblog = 1;
    handler_arg.do_print = 0;
    runpasev_cb(&rc, &pid, false, false,_argc,  _cmd, ignoreHandler, ignoreHandler, &handler_arg);
    return rc;
}

int runpasev_rconly_logandprint(int _argc, char *_cmd[])
{
    int rc = -1;
    pid_t pid;
    ignore_handler_arg handler_arg;
    handler_arg.do_joblog = 1;
    handler_arg.do_print = 1;
    runpasev_cb(&rc, &pid,false, false, _argc,  _cmd, ignoreHandler, ignoreHandler, &handler_arg);
    return rc;
}
int runpasev_rconly(int _argc, char *_cmd[])
{
    int rc = -1;
    pid_t pid;
    runpasev_cb(&rc, &pid, false, true, _argc, _cmd, ignoreHandler, ignoreHandler, NULL);
    return rc;
}
int runpasev_rconly_nd(int _argc, char *_cmd[])
{
    int rc = -1;
    pid_t pid;
    runpasev_nd(&rc, &pid, false, _argc, _cmd);
    return rc;
}