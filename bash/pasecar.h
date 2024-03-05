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
    ////////////////////////////////////////////////////////////////////////////
    // API set 1: utility functions
    ////////////////////////////////////////////////////////////////////////////

    /**
     * Execute a PASE command, with custom callbacks, given an array of arguments
     *
     * parameters:
     *  - (out) int*:    pointer to an integer for the PASE exit code
     *  - (out) pid_t*:  pointer to an integer for the PASE Process ID (pid)
     *  - (in)  boolean: whether to run the command asynchronously
     *  - (in)  boolean: whether to process data as binary
     *  - (in)  int:     The number of arguments sent to the PASE program
     *  - (in)  char*:   The arguments to send to the PASE program
     *  - (out) line_cb: A callback for receiving standard error output as it happens
     *  - (out) line_cb: A callback for receiving standard output events as it happens
     *  - (in)  void*:   Arguments to pass along to the callback
     * returns: 0 on success
     **/
    int runpasev_cb(int *rc, pid_t *_pid, boolean _async, boolean _binary, int argc, char *argv[], line_cb _stderr, line_cb _stdout, void *_cb_arg);
    

    /**
     * Execute a PASE command, given an array of arguments
     *
     * parameters:
     *  - (out) int*:    pointer to an integer for the PASE exit code
     *  - (out) pid_t*:  pointer to an integer for the PASE Process ID (pid)
     *  - (in)  boolean: whether to run the command asynchronously
     *  - (in)  int:     The number of arguments sent to the PASE program
     *  - (in)  char*:   The arguments to send to the PASE program
     * returns: 0 on success
     **/
    int runpasev_nd(int *_rc, pid_t *_pid, boolean _async, int _argc, char *_argv[]);
    

    /**
     * Execute a PASE command, given a command line string
     *
     * parameters:
     *  - (out) int*:    pointer to an integer for the PASE exit code
     *  - (out) pid_t*:  pointer to an integer for the PASE Process ID (pid)
     *  - (in)  boolean: whether to run the command asynchronously
     *  - (in)  char*:   The PASE command line
     * returns: 0 on success
     **/
    int runpase_nd(int *_rc, pid_t *_pid, boolean _async, const char *_cmd);
    

    /**
     * Execute a PASE command asynchronously, with custom callbacks, given a command line string
     *
     * parameters:
     *  - (out) int*:    pointer to an integer for the PASE exit code
     *  - (out) pid_t*:  pointer to an integer for the PASE Process ID (pid)
     *  - (in)  boolean: whether to process data as binary
     *  - (in)  char*:   The PASE command line
     *  - (out) line_cb: A callback for receiving standard error output as it happens
     *  - (out) line_cb: A callback for receiving standard output events as it happens
     *  - (in)  void*:   Arguments to pass along to the callback
     * returns: 0 on success
     **/
    int runpase_cb(int *_rc, pid_t *_pid, boolean _async, boolean _binary, const char *_cmd, line_cb _stderr, line_cb _stdout, void *_cb_arg);
    
    
    /**
     * Execute a PASE command synchronously, logging its output to the job log. Returns
     * only the PASE exit code to the caller
     *
     * parameters:
     *  - (in)  char*:   The PASE command line
     * returns: The PASE exit code
     **/
    int runpase_rconly_log(char *_cmd);
    

    /**
     * Execute a PASE command synchronously, logging its output to the job log and standard
     * output. Returns only the PASE exit code to the caller
     *
     * parameters:
     *  - (in)  char*:   The PASE command line
     * returns: The PASE exit code
     **/
    int runpase_rconly_logandprint(char *_cmd);

    
    
    /**
     * Execute a PASE command synchronously. Returns
     * only the PASE exit code to the caller
     *
     * parameters:
     *  - (in)  char*:   The PASE command line
     * returns: The PASE exit code
     **/
    int runpase_rconly(char *_cmd);   

    
    /**
     * Execute a PASE command synchronously. Returns
     * only the PASE exit code to the caller
     *
     * parameters:
     *  - (in)  char*:   The PASE command line
     * returns: The PASE exit code
     **/
    int runpase_rconly_nd(char *_cmd);
    
    
    /**
     * Execute a PASE command synchronously, given an array of arguments to the PASE program, 
     * logging its output to the job log. 
     * Returns only the PASE exit code to the caller
     *
     * parameters:
     *  - (in)  int:     The number of arguments for the PASE program
     *  - (in)  char*:   arguments for the PASE program
     * returns: The PASE exit code
     **/
    int runpasev_rconly_log(int _argc, char *_cmd[]);


    /**
     * Execute a PASE command synchronously, given an array of arguments to the PASE program, 
     * logging its output to the job log and standard output.
     * Returns only the PASE exit code to the caller
     *
     * parameters:
     *  - (in)  int:     The number of arguments for the PASE program
     *  - (in)  char*:   arguments for the PASE program
     * returns: The PASE exit code
     **/
    int runpasev_rconly_logandprint(int _argc, char *_cmd[]);

    /**
     * Execute a PASE command synchronously, given an array of arguments to the PASE program. Returns
     * only the PASE exit code to the caller
     *
     * parameters:
     *  - (in)  int:     The number of arguments for the PASE program
     *  - (in)  char*:   arguments for the PASE program
     * returns: The PASE exit code
     **/
    int runpasev_rconly(int _argc, char *_cmd[]);

    
    /**
     * Execute a PASE command synchronously, given an array of arguments to the PASE program. Returns
     * only the PASE exit code to the caller
     *
     * parameters:
     *  - (in)  int:     The number of arguments for the PASE program
     *  - (in)  char*:   arguments for the PASE program
     * returns: The PASE exit code
     **/
    int runpasev_rconly_nd(int _argc, char *_cmd[]);

    ////////////////////////////////////////////////////////////////////////////
    // API set 2: handle-based functions
    ////////////////////////////////////////////////////////////////////////////

    /**
     * Initialize a call to PASE
     *
     * returns: a handle to be used for subsequent API calls in this API set
     **/
    void *PASE_init();


    /**
     * Execute a PASE command synchronously
     *
     * parameters:
     *  - a handle, as returned from PASE_init()
     *  - whether or not to process data as binary
     *  - the PASE command to run
     *
     * returns: the PASE exit code
     **/
    int PASE_execute(void *, boolean _binary, const char *);


    /**
     * Execute a PASE command asynchronously
     *
     * parameters:
     *  - a handle, as returned from PASE_init()
     *  - whether or not to process data as binary
     *  - the PASE command to run
     *
     * returns: the PASE exit code
     **/
    int PASE_execute_async(void *_handle, boolean _binary, const char *_cmd);


    /**
     * Kill the PASE command
     *
     * parameters:
     *  - a handle, as returned from PASE_init()
     *
     * returns: 0 if successful
     **/
    int PASE_kill(void *_handle);


    /**
     * Retrieve the contents of the standard output stream
     *
     * parameters:
     *  - a handle, as returned from PASE_init()
     *
     * returns: the stdout contents
     **/
    const char *PASE_stdout(void *);


    /**
     * Retrieve the contents of the standard error stream
     *
     * parameters:
     *  - a handle, as returned from PASE_init()
     *
     * returns: the stdout contents
     **/
    const char *PASE_stderr(void *);


    /**
     * Retrieve the PASE exit code
     *
     * parameters:
     *  - a handle, as returned from PASE_init()
     *
     * returns: the PASE exit code
     **/
    int PASE_exitCode(void *);


    /**
     * Clean up resources related to this PASE call
     *
     * parameters:
     *  - a handle, as returned from PASE_init()
     **/
    void PASE_dispose(void *);
#ifdef __cplusplus
}
#endif

#endif