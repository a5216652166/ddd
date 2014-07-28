#ifndef __DNS_PKTLOG_H__
#define __DNS_PKTLOG_H__


/****   port   ****/

#define CACHE_PORT  (0x1630)  //cache������־���ն˿�
#define RECORD_PORT (0x1730)  //�ٳ�������־���ն˿�
#define ANSWER_PORT (0x1830)  //Ӧ��������־���ն˿�
#define ERRDST_PORT (0x1930)  //�����ض���������־���ն˿�
#define RARP_PORT   (0x2030)  //�������������־���ն˿�


/******************/


#include "fio_context.h"


/*

int dns_pktlog_init(char *dstip, uint16_t port,int pnum,int limit);


void dns_pktlog_uninit();


int dns_pktlog_cache(struct fio_nic *dst, int sip,unsigned short view, 
    char *domain,unsigned short domainlen,unsigned short pid,unsigned short sport);


int dns_pktlog_record(struct fio_nic *dst, int sip,unsigned short view, 
    char *domain,unsigned short domainlen,unsigned short pid,unsigned short sport);

int dns_pktlog_errdst(struct fio_nic *dst, int sip, unsigned short view, 
    char *domain,unsigned short domainlen,unsigned short pid,unsigned short sport);


int dns_pktlog_answer(struct fio_nic *dst, int sip,int svrip,unsigned short view, 
    char *domain,unsigned short domainlen,unsigned short pid,unsigned short sport,unsigned short rs_num);

int dns_pktlog_answer_rsadd(unsigned short type,unsigned int ttl,int ip,int pid);

int dns_pktlog_answer_cnameadd(unsigned short type,unsigned int ttl,char *domain,unsigned short domainlen,int pid);

int dns_pktlog_rarp(struct fio_nic *dst, int sip, unsigned short view, 
    char *domain,unsigned short domainlen,unsigned short pid,unsigned short sport);

void dns_pktlog_set(int new_ip);
*/

#endif