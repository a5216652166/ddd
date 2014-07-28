#ifndef __DNS_EXTCHE_H__
#define __DNS_EXTCHE_H__

#ifndef MAX_DOMAIN_LEN
#define MAX_DOMAIN_LEN	    (255)
#endif

#ifndef MAX_VIEM_NUM
#define MAX_VIEM_NUM        (100)
#endif

#ifndef MAX_IP_LEN
#define MAX_IP_LEN			(16)
#endif


typedef unsigned short	ushort;



/**
* @brief    ��ʼ��������
* @return 
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/22
**/
int dns_ext_cache_init();


/**
* @brief    ����������
* @return 
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/22
**/
void dns_ext_cache_destroy();

/**
* @brief   �½������ٳ�
* @param   domain           ����
* @param   domain_len       ��������
* @param   view_id          ��ͼid
*
* @return 0 - �ɹ�  /  -1 - ʧ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/22
**/
int dns_ext_cache_set(char *domain,int domain_len,ushort view_id,char *pkt,
        int pkt_len,unsigned short type);

/**
* @brief   ɾ�������ٳ�
* @param   domain           ����
* @param   domain_len       ��������
* @param   view_id          ��ͼid
*
* @return 0 - �ɹ�  /  -1 - ʧ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/22
**/
int dns_ext_cache_drop(char *domain,int domain_len,ushort view_id,unsigned short type);

/**
* @brief   ɾ�������ٳ�
* @param   domain           ����
* @param   domain_len       ��������
*
* @return 0 - �ɹ�  /  -1 - ʧ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/22
**/
int dns_ext_cache_del(char *domain,int domain_len,unsigned short type);


/**
* @brief   ��ȡ������Ӧ��
* @param   domain           ����
* @param   domain_len       �������� 
* @param   view_id          ��ͼID
*
* @return  �ɹ���ȡ���ֽ�����0Ϊʧ��
* @remark null
* @see     
* @author hyb      @date 2013/07/22
**/
int dns_ext_cache_get(char *pkt,char *domain,int domain_len,ushort view_id,unsigned short type);


/**
* @brief    ��ջ�������
* @return 
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/22
**/
void dns_ext_cache_clear();


#endif