#ifndef __DNS_EXTEND_H__
#define __DNS_EXTEND_H__

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

typedef unsigned short	ushort;



/**
* @brief    ��ʼ��������
* @return 
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/22
**/
int dns_extend_init();

/**
* @brief    ͬ��mysql���ڴ�
* @return 
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/22
**/
void dns_extend_syn();

/**
* @brief    ����������
* @return 
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/22
**/
void dns_extend_destroy();

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
int dns_extend_create(char *domain,int domain_len,ushort view_id);

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
int dns_extend_drop(char *domain,int domain_len,ushort view_id);

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
int dns_extend_del(char *domain,int domain_len);

/**
* @brief   Ϊ��������IP
* @param   domain           ����
* @param   domain_len       ��������
* @param   view_id          ��ͼid
*
* @return 0 - �ɹ�  /  -1 - ʧ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/22
**/
int dns_extend_insert(char *domain,int domain_len,ushort view_id,char ipaddr[MAX_IP_LEN]);

/**
* @brief   Ϊ����ɾ��IP
* @param   domain           ����
* @param   domain_len       ��������
* @param   view_id          ��ͼid
*
* @return 0 - �ɹ�  /  -1 - ʧ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/22
**/
int dns_extend_remove(char *domain,int domain_len,ushort view_id,char ipaddr[MAX_IP_LEN]);


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
int dns_extend_get(char packet[MAX_PACKET_LEN],char *domain,int domain_len,ushort view_id);

/**
* @brief   �����ڴ�������������Ϣ������node��Ŀ
* @return node ��Ŀ
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/22
**/

int dns_extend_node_count();

/**
* @brief   �����ڴ�������������Ϣ�������ڴ�״̬���
* @return 0 - �ɹ�  /  -1 - ʧ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/22
**/
int dns_extend_node_display(char*output,int max_len);



/**
* @brief    ��ջ�������
* @return 
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/22
**/
void dns_extend_clear();


#endif