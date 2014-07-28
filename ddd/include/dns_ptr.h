#include <netinet/in.h>

#ifndef __DNS_PTR_H__
#define __DNS_PTR_H__

#ifndef MAX_DOMAIN_LEN
#define MAX_DOMAIN_LEN	    (255)
#endif

#ifndef MAX_VIEM_NUM
#define MAX_VIEM_NUM        (100)
#endif

#ifndef MAX_IP_LEN
#define MAX_IP_LEN			(16)
#endif

#ifndef MAX_PACKET_LEN
#define MAX_PACKET_LEN      (1024)
#endif


/**
* @brief    ����ptr�Ļظ���
* @param   packet         ���������������ظ���
* @param   len        packet����
* @remark packet_len
* @see     
* @author hezuoxiang      @date 2013/07/22
**/
int make_ptr_answer(char*packet,int len,char*domain,int domainlen);

/**
* @brief    �ж�Ŀ���ַ�뷴��������ѯ�Ĺ�ϵ
* @param   	domain		��������
* @param   	domain_len	���������ĳ���
* @remark 	dip			����Ŀ��IP
* @see     
* @return	0:match;1:unmatch;-1:error
* @author hezuoxiang      @date 2014/01/02
**/
int check_ptr_address(char*domain,int domain_len,int dip);

#endif



