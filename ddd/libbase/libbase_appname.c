/*!
 * \file libbase_appname.c
 * \brief ͨ��/proc/%d/status��ȡӦ�ó���ִ��ʱ������
 * mips�ܹ���û�ж���__progname�������, ����ͨ�������ʽ��ȡӦ�ó�����
 *
 * \author Adam Xiao (iefcu), iefcuxy@gmail.com
 * \date 2012-11-07 08:57:09
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>

#include "libbase_appname.h"
#include "libbase_strutils.h"
#include "libbase_memory.h"
#include "libbase_config.h"
#include "libbase_type.h"

#ifdef SF_ARCH_MIPS_32//mips û��__progname��
static char* __progname = NULL; /// ��������ʱ����
#else
extern char* __progname;
#endif

//�õ������̵�����, �ӱ��е�appid.c���ڳ����Ľӿ�
#ifdef SF_ARCH_MIPS_32 //mips û��__progname��
static char* getprogname(char** progname)
{
    assert(progname);
#define SF_PROGNAME_MAX_LEN  (256) /// ����������󳤶�
    FILE * proc_file = NULL;
    static char* s_progname = NULL;
    if(!s_progname) {
        s_progname = (char*)h_malloc(SF_PROGNAME_MAX_LEN);
        if(!s_progname) {
            goto GET_PROGNAME_RET;
        }
        memset(s_progname, 0, SF_PROGNAME_MAX_LEN);
    }
    if(strlen(s_progname) == 0) {
        char str[SF_PROGNAME_MAX_LEN+16] = {0};
        pid_t app_pid = getpid();
        sprintf_n(str, sizeof(str) - 1, "/proc/%d/status", app_pid);
        proc_file = fopen(str, "r");
        if(proc_file == NULL)
        {
            perror("fopen error");
            goto GET_PROGNAME_RET;
        }
        do {
            memset(str, 0, sizeof(str));
            if(fgets(str, sizeof(str) - 1, proc_file) == NULL)
            {
                perror("fgets error");
                goto GET_PROGNAME_RET;
            }
            if(!strncmp(str,"Name:",strlen("Name:"))) {
                sscanf(str, "Name:   %255s", s_progname);
                goto GET_PROGNAME_RET;
            }
        }while(!feof(proc_file));
    }
GET_PROGNAME_RET:
    if(proc_file) {
        fclose(proc_file);
    }
    if(!s_progname || strlen(s_progname) == 0) {
        return NULL;
    }
    if(progname) {
        *progname = s_progname;
    }
    return s_progname;
}
#endif

/**
 * ��ȡ��ǰ�����appname
 */
const char* wns_current_appname(void)
{
#ifdef SF_ARCH_MIPS_32//mips û��__progname��
    if (__progname == NULL) {
        (void)getprogname(&__progname);
    }
#endif
    return __progname;
}

//����ʱ��ɳ�ʼ��
__attribute ((constructor))  static void init(void)
{
#ifdef SF_ARCH_MIPS_32 //mips û��__progname��
    if(getprogname(&__progname) == NULL) {
        fprintf(stderr, "mips set __progname fail! errno=%d %s\n",
                errno, strerror(errno));
    }
#endif
}


