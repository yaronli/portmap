/**
 *
 * supervisor 
 *
 * author: liyangguang (liyangguang@software.ict.ac.cn)
 *
 * date: 2011-01-21 21:04:01
 *
 * changes
 * 1, execl to execv
 */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>

int
main(int argc, char **argv)
{
    int ret, i, status;
    char *child_argv[100] = {0};
    pid_t pid;
    if (argc < 2) {
    
        fprintf(stderr, "Usage:%s <exe_path> <args...>\n", argv[0]);
        return -1;
    }
    for (i = 1; i < argc; ++i) {
        child_argv[i-1] = (char *)malloc(strlen(argv[i])+1);
        strncpy(child_argv[i-1], argv[i], strlen(argv[i]));
        child_argv[i-1][strlen(argv[i])] = '\0';
    }
    while(1){
    
        pid = fork(); 
        if (pid == -1) {
            fprintf(stderr, "fork() error.errno:%d error:%s\n", errno, strerror(errno));
            break;
        }
        if (pid == 0) {
            int fd1 = open("/dev/null", O_RDWR);
            int fd2 = open("/dev/null", O_RDWR);
            int fd3 = open("/dev/null", O_RDWR);
            dup2(0, fd1);
            dup2(1, fd2);
            dup2(2, fd3);
            ret = execv(child_argv[0], (char **)child_argv);
            //ret = execl(child_argv[0], "portmap", NULL, 0);
            if (ret < 0) {
                fprintf(stderr, "execv ret:%d errno:%d error:%s\n", ret, errno, strerror(errno));
                continue;
            }
            exit(0);
        }

        if (pid > 0) {
            pid = wait(&status);
            
            fprintf(stdout, "wait return");
        }
    
    }


    return 0;
}
