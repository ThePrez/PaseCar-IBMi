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
int myhandler(char *_line, pid_t _pid, int _is_err)
{
    fprintf(_is_err?stderr:stdout,  "%s: %s\n", _is_err ? "stderr" : "stdout", _line);
    fflush(stdout);
    Qp0zLprintf("%s%s\n", _is_err ? "ERROR: " : "", _line);
    return 0;
}
int main(int argc, char *argv[])
{
    return runpase_main(argc, argv, &myhandler, &myhandler);
}