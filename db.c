/*
 * Author: liyangguang <liyangguang@software.ict.ac.cn>
 * http://www.yaronspace.cn/blog
 *
 * File: db.c
 * Create Date: 2011-11-08 17:21:24
 *
 */


#include "db.h"
#include "log.h"
#include <stdio.h>
#ifndef true
#define true 1
#endif
#ifndef false
#define false 1
#endif

static MYSQL s_conn;

int init_db(const char *host, unsigned int port, 
            const char *username, const char *pwd, const char *database)
{
    mysql_init(&s_conn);
    my_bool reconnect = true;
    mysql_options(&s_conn, MYSQL_OPT_RECONNECT, &reconnect);
    if (!mysql_real_connect(&s_conn, host, username, pwd, database, port, NULL, 0)) {
        LOG_ERR("connect mysql failed.[host:%s] [user:%s] [pwd:%s] [db:%s] [error:%s]",
                host, username, pwd, database, mysql_error(&s_conn)); 
        return -1; 
    }   
    LOG_INFO("connect mysql success.");
    return 0;
}


int check_user(const char *username, const char *pwd)
{
    if (username == NULL || pwd == NULL)
    {
        return -1;
    }

    char str[1024];
    snprintf(str, 1024, "SELECT UID FROM tbl_user_info WHERE UName='%s' AND Password='%s'", username, pwd);
    LOG_INFO("Execute the SQL.[sql:%s]", str);
    int ret = mysql_query(&s_conn, str);
    if (ret == 0) {
        MYSQL_RES *res = mysql_store_result(&s_conn);
        my_ulonglong cnt = 0;
        if (res != NULL && (cnt = mysql_num_rows(res) > 0 )) {
            LOG_INFO("User And Password Matched.[user:%s] [pwd:%s]", username, pwd);
            return 0;
        }
        else {
            LOG_INFO("User And Password Not Matched.[user:%s] [pwd:%s]", username, pwd);
            return -1;
        }
    }
    else {
        LOG_ERR("exec sql failed.[sql:%s]", str);
        return -1;
    }
}

int 
close_db()
{
    mysql_close(&s_conn);
    LOG_INFO("MYSQL CLose.");
    return 0;
}
/* vim: set ts=4 sw=4: */

