#ifndef _PASECAR_H_
#define _PASECAR_H_

#include <sys/types.h>

typedef int (*line_cb)(char* _line, pid_t _pid, int _is_err);

int runpase_main(int argc, char *argv[], line_cb _stderr, line_cb _stdout);

// typedef struct runpase_results {
//     char* stdout;
//     char* stderr;
// } runpase_results;

// int runpase_results(int _argc, char* argv[], runpase_results* _res);

#endif