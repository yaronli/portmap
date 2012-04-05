/*
 * Author: liyangguang <liyangguang@software.ict.ac.cn>
 * http://www.yaronspace.cn/blog
 *
 * File: db.h
 * Create Date: 2011-11-08 17:14:17
 *
 * mysql 
 */

#ifndef _PORTMAP_DB_H
#define _PORTMAP_DB_H

#include <mysql/mysql.h>


int init_db(const char *host, unsigned int port, 
            const char *username, const char *pwd, const char *database);

int check_user(const char *username, const char *pwd);

int close_db();

#endif
/* vim: set ts=4 sw=4: */

