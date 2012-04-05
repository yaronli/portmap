/**
 * portmap store the mapped addr+port
 *
 * store.c
 *
 * author: liyangguang (liyangguang@software.ict.ac.cn)
 *
 * date: 2011-01-21 10:30:20
 *
 * changes
 *
 */

#include "store.h"
#include "log.h"
#include "config.h"
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>

static FILE* s_store_file;
static char s_store_file_path[50];
pthread_mutex_t s_file_mutex;


int
init_store(const char *store_file)
{
    assert(store_file != NULL); 
    char err_buf[ERR_BUF_SIZE] = {0};
    s_store_file = fopen(store_file, "a+");

    if (s_store_file == NULL) {
        strerror_r(errno, err_buf, ERR_BUF_SIZE); 
        LOG_ERR("open store_file error.[store_file:%s] [error:%s]", store_file, err_buf);
        return -1;
    }
    strncpy(s_store_file_path, store_file, 50);
    pthread_mutex_init(&s_file_mutex, NULL);
    return 0;
}

void
close_store()
{
    if (s_store_file != NULL) {
    
        fclose(s_store_file);
        pthread_mutex_destroy(&s_file_mutex);
    }
}

int
write_record(const char *src_addr, unsigned int src_port,
        const char *mapped_addr, unsigned int mapped_port)
{
    LOG_INFO("write_record.%s:%u-%s:%u", src_addr, src_port, mapped_addr, mapped_port);
    pthread_mutex_lock(&s_file_mutex);
    fseek(s_store_file, 0, SEEK_END);
    fprintf(s_store_file, "%s %u %s %u\n", src_addr, src_port, mapped_addr, mapped_port);
    fflush(s_store_file);
    pthread_mutex_unlock(&s_file_mutex);
    return 0;
}

int
delete_record(const char *src_addr, unsigned int src_port)
{
    char t_sf_name[] = "mapped_data.tmp";
    FILE *t_sf = NULL;
    char t_src_addr[INET_ADDRSTRLEN], t_mapped_addr[INET_ADDRSTRLEN], err_buf[ERR_BUF_SIZE];
    unsigned int t_src_port, t_mapped_port;
    int ret = 0;;
    pthread_mutex_lock(&s_file_mutex);
    t_sf = fopen(t_sf_name, "w+");
    fseek(s_store_file, 0, SEEK_SET);
    while (fscanf(s_store_file, "%s %u %s %u\n", t_src_addr, &t_src_port, t_mapped_addr, &t_mapped_port) != EOF) {
    
        if (strncmp(t_src_addr, src_addr, INET_ADDRSTRLEN) == 0 && t_src_port == src_port) {
            LOG_INFO("delete the record.%s:%u-%s:%u", t_src_addr, t_src_port, 
                    t_mapped_addr, t_mapped_port);
            continue;
        }
        fprintf(t_sf, "%s %u %s %u\n", t_src_addr, t_src_port, t_mapped_addr, t_mapped_port);
    }
    fflush(t_sf);
    fclose(t_sf);
    fclose(s_store_file);
    ret = rename(t_sf_name, s_store_file_path);
    if (ret < 0) {
        strerror_r(errno, err_buf, ERR_BUF_SIZE); 
        LOG_ERR("rename error.[s_store_file_path:%s] [t_sf_name:%s] [error:%s]", 
                s_store_file_path, t_sf_name, err_buf);
        ret = -1;
        goto out;
    }

out:
    //reopen
    s_store_file = NULL;
    s_store_file = fopen(s_store_file_path, "a+");
    if (s_store_file == NULL) {
        strerror_r(errno, err_buf, ERR_BUF_SIZE); 
        LOG_ERR("open store_file error.[s_store_file_path:%s] [error:%s]", s_store_file_path, err_buf);
        return -1;
    }
    LOG_INFO("delete record finish.");
    pthread_mutex_unlock(&s_file_mutex);
    return ret; 
}



int 
read_record(char *src_addr, unsigned int *src_port,
        char *mapped_addr, unsigned int *mapped_port)
{
    assert(s_store_file != NULL);
    pthread_mutex_lock(&s_file_mutex);
    int ret = fscanf(s_store_file, "%s %u %s %u\n", src_addr, src_port, mapped_addr, mapped_port);
    pthread_mutex_unlock(&s_file_mutex);
    return ret;
}

int
start_read()
{
    assert(s_store_file != NULL);
    LOG_INFO("fseek SEEK_SET:0");
    pthread_mutex_lock(&s_file_mutex);
    int ret = fseek(s_store_file, 0, SEEK_SET);
    pthread_mutex_unlock(&s_file_mutex);
    return ret;

}
