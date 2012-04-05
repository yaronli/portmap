/**
 * portmap config header
 *
 * config.h
 *
 * author:liyangguang (liyangguang@software.ict.ac.cn)
 *
 * date: 2011-01-21 10:48:00
 *
 * changes
 */

#ifndef _PORTMAP_CONFIG_H
#define _PORTMAP_CONFIG_H

#define DEFAULT_LISTEN_PORT 5900
#define DEFAULT_MAPPED_LOWER_PORT 5901
#define DEFAULT_MAPPED_HIGH_PORT 65535

#define DEFAULT_LOG_FILE "portmap.log"
#define DEFAULT_STORE_FILE "mapped_data"

#define DEFAULT_TIMEOUT  -1

#define DEFAULT_THREAD_NUM 4

#define ERR_BUF_SIZE 100


#define EPOLL_SIZE 65535

#define TASK_QUEUE_SIZE 65535
#define ERR_BUF_SIZE 100
#define MAX_THREAD_NUM 100


#define MAX_PORT_NUM 65536
#define MAX_REQ_SIZE 1024
#define MAX_DATA_LEN 65536

#endif /* _PORTMAP_CONFIG_H */
