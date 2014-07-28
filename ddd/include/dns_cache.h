#ifndef __DNS_CACHE_H__
#define __DNS_CACHE_H__

#define MAX_DOMAIN_LEN	    (255)
#define MAX_VIEM_NUM        (1024)

#include "dns_unpack.h"



/**
* @brief ��ȡ�����¼����
* @return 
* @remark null
* @see     
* @author hyb      @date 2013/08/21
**/
int dns_cache_count();


/**
* @brief    ��ʼ�������
* @return 
* @remark null
* @see     
* @author hyb      @date 2013/07/10
**/
int dns_cache_init();



/**
* @brief    �������
* @return 
* @remark null
* @see     
* @author hyb      @date 2013/07/10
**/
void dns_cache_destroy();

/**
* @brief   ����dns����
* @param   domain           ����
* @param   domain_len       ��������
* @param   view_id          ��ͼid
* @param   answer           �ظ���
* @param   answer_len       �ظ�������
*
* @return 0 - �ɹ�  /  -1 - ʧ��
* @remark null
* @see     
* @author hyb      @date 2013/07/09
**/
int dns_cache_set(char *domain,int domain_len,unsigned int view_id,char* answer,
        int answer_len,unsigned short type);


/**
* @brief   ��ȡdns����
* @param   domain           ����
* @param   domain_len       �������� 
* @param   view_id          ��ͼID
* @param   answer           �ظ���
*
* @return  �ɹ���ȡ���ֽ�����0Ϊʧ��
* @remark null
* @see     
* @author hyb      @date 2013/07/10
**/
int dns_cache_get(char* answer,char* domain,int domain_len,int view_id,
    unsigned short type);


/**
* @brief   ������Ϣȥ��
* @param   domain   
* @param   domain_len   
* @param   view_id   
* @param   type   
*
* @return 
* @remark null
* @see     
* @author hyb      @date 2014/05/21
**/
int dns_cache_delete(char *domain,int domain_len,unsigned int view_id,
    unsigned short type);


/**
* @brief   �����ڴ������л�����Ϣ�����ڵĻ����¼���ӽ���������
* @return 
* @remark null
* @see     
* @author hyb      @date 2013/07/10
**/

void dns_cache_check();



/**
* @brief    ��ջ�������
* @return 
* @remark null
* @see     
* @author hyb      @date 2013/07/10
**/
void dns_cache_clear();


/**
* @brief  �鿴������Ŀ�洢���
* @return 
* @remark null
* @see     
* @author hyb      @date 2014/05/13
**/
int dns_cache_info();

#endif