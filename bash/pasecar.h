#ifndef _PASECAR_H_
#define _PASECAR_H_

#include <sys/types.h>

typedef int (*line_cb)(char *_line, pid_t _pid, int _is_err, void *_arg);
typedef int boolean;
#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    int runpasev_cb(int *rc,pid_t* _pid, boolean _async, boolean _binary, int argc, char *argv[], line_cb _stderr, line_cb _stdout, void *_cb_arg);

    int runpase_cb(int *_rc,pid_t* _pid, boolean _async,boolean _binary,  const char *_cmd, line_cb _stderr, line_cb _stdout, void *_cb_arg);
    int runpase_rconly_log(char *_cmd);
    int runpase_rconly_logandprint(char *_cmd);
    int runpase_rconly(char *_cmd);
    int runpasev_rconly_log(int _argc, char *_cmd[]);
    int runpasev_rconly_logandprint(int _argc, char *_cmd[]);
    int runpasev_rconly(int _argc, char *_cmd[]);
    void *PASE_init();
    int PASE_execute(void *, boolean _binary, const char *);
    int PASE_execute_async(void *_handle, boolean _binary, const char *_cmd);
    int PASE_kill(void* _handle);
    const char *PASE_stdout(void *);
    const char *PASE_stderr(void *);
    int PASE_exitCode(void *);
    void PASE_dispose(void *);
#ifdef __cplusplus
}
#endif

#endif