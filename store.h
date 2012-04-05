/**
 * portmap store the mapped addr+port
 *
 * store.h
 *
 * author:liyangguang (liyangguang@software.ict.ac.cn)
 *
 * date: 2011-01-21 10:20:01
 * 
 * changes
 */
#ifndef _PORTMAP_STORE_H
#define _PORTMAP_STORE_H



int init_store(const char *store_file);

int start_read();

int write_record(const char *src_addr, unsigned int src_port, 
        const char *mapped_addr, unsigned int mapped_port);
int delete_record(const char *src_addr, unsigned int src_port);

int read_record(char *src_addr, unsigned int *src_port,
        char *mapped_addr, unsigned int *mapped_port);

void close_store();


#endif /* _PORTMAP_STORE_H */
