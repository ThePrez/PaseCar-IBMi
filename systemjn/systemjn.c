
#include <stdio.h>
#include <stdlib.h>
#include <qp0wpid.h>
#include <string.h>
#include <spawn.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <qp0wpid.h>
#include <stddef.h>

extern void QCMDEXC(char *, int);
#pragma convert(37)

void copy_and_trim(char *_dest, char *_src, size_t _len)
{
    for (int i = 0; 1; ++i)
    {
        if (_len == i)
        {
            _dest[i] = '\0';
            return;
        }
        char c = _src[i];
        _dest[i] = c;
        if ('\0' == c)
        {
            return;
        }
        if (' ' == c)
        {
            _dest[i] = '\0';
            return;
        }
    }
}
int main(int _argc, char *_argv[])
{
    char *cmd = getenv("CLCOMMAND");
    if (NULL == cmd)
    {
        if (_argc != 2)
        {
            fprintf(stderr, "Incorrect usage");
            exit(52);
        }
        cmd = _argv[1];
    }
    else if (_argc != 1)
    {
        fprintf(stderr, "Incorrect usage. Command cannot be specified alongside $CLCOMMAND");
        exit(53);
    }
    pid_t my_pid = Qp0wGetPid();
    // printf("pid: %d\n",(int)my_pid);
    QP0W_Job_ID_T job;
    memset(&job, 0x00, sizeof(job));
    Qp0wGetJobID(my_pid, &job);
    char job_name[11];
    copy_and_trim(job_name, job.jobname, 10);
    char job_user[11];
    copy_and_trim(job_user, job.username, 10);
    char job_no[7];
    copy_and_trim(job_no, job.jobnumber, 6);
    printf("job: %s/%s/%s\n", job_name, job_user, job_no);
    char cmd2[1024];
    sprintf(cmd2, "CALL PGM(QSYS/QCMDEXC) PARM('%s' %d)", cmd, strlen(cmd));
    printf(">%s<\n", cmd);
    fflush(stdout);
    int ttt= system(cmd);
    printf("rc=%d, '%s'\n",ttt,_EXCP_MSGID);
    return ttt;
}