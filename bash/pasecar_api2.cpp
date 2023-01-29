#include <stdlib.h>
#include <string>
#include "pasecar.h"
typedef struct runpase_results
{
    std::string *stdout;
    std::string *stderr;
    int exit_code;
} runpase_results;
int myhandler(char *_line, pid_t _pid, int _is_err, void *_arg)
{
    runpase_results *obj = (runpase_results *)_arg;
    if (_is_err)
    {
        obj->stderr->append(_line);
        obj->stderr->append("\n");
    }
    else
    {
        obj->stdout->append(_line);
        obj->stdout->append("\n");
    }
    return 0;
}
void *PASE_init()
{
    size_t sz = sizeof(runpase_results);
    runpase_results *handle = (runpase_results *)malloc(sz);
    handle->stdout = new std::string();
    handle->stderr = new std::string();
    handle->exit_code = -1;
    return (void *)handle;
}

int PASE_execute(void *_handle, const char *_cmd)
{
    runpase_results *obj = (runpase_results *)_handle;
    return runpase_cb(&obj->exit_code, _cmd, myhandler, myhandler, _handle);
}

const char *PASE_stdout(void *_handle)
{
    runpase_results *obj = (runpase_results *)_handle;
    return obj->stdout->c_str();
}
const char *PASE_stderr(void *_handle)
{
    runpase_results *obj = (runpase_results *)_handle;
    return obj->stdout->c_str();
}
int PASE_exitCode(void *_handle)
{

    runpase_results *obj = (runpase_results *)_handle;
    return obj->exit_code;
}
void PASE_dispose(void *_handle)
{
    runpase_results *obj = (runpase_results *)_handle;
    delete obj->stderr;
    delete obj->stdout;
    free(_handle);
}