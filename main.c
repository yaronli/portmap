/**
 * portmap main func 
 *
 * author liyangguang (liyangguang@software.ict.ac.cn)
 *
 * date: 2011-01-17 16:21:00
 *
 * changes
 */
#include "net.h"
#include "event.h"
#include "log.h"
#include "worker.h"
#include "store.h"
#include "config.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <signal.h>


int g_started = 0;

void sig_handler(int signo)
{
    g_started = 0;
    close_store();
    log_close();
}

int 
main(int argc, char **argv)
{
    int ret = 0;
    unsigned int port = DEFAULT_LISTEN_PORT; 
    const char *log_file = DEFAULT_LOG_FILE;
    const char *store_file = DEFAULT_STORE_FILE;
    int timeout = DEFAULT_TIMEOUT;

    if (argc == 2) {
        port = (unsigned int)atoi(argv[1]); 
        assert(port > 0); 
    }
    else if (argc >= 3) {
        port = (unsigned int)atoi(argv[1]); 
        assert(port > 0); 
        
        log_file = argv[2];
    }
    signal(SIGINT, sig_handler);

    ret = log_init(log_file);

    if (ret < 0) {
    
        fprintf(stderr, "init_log error.");
        return -1;
    }

    ret = init_event();

    if (ret < 0) {
        
        fprintf(stderr, "init_event error.");
        return -1;
    
    }

    g_started = 1;

    ret = init_local_server(port, DEFAULT_MAPPED_LOWER_PORT, DEFAULT_MAPPED_HIGH_PORT);

    if (ret < 0) {
    
        fprintf(stderr, "init_local_server error.");
        return -1;
    }
    
    ret = init_store(store_file); 

    if (ret < 0) {
        fprintf(stderr, "init_store error.");
        return -1;
    }

    recover_mapped_pair();
    ret = init_worker(DEFAULT_THREAD_NUM);
    if (ret < 0) {
        fprintf(stderr, "init_worker error.");
        return -1;
    }

    loop_event(timeout);
    
    return 0;
}
