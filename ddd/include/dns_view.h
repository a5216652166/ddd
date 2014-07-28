#ifndef __DNS_VIEW_H__
#define __DNS_VIEW_H__

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

#ifndef MAX_ACTION_SIZE
#define MAX_ACTION_SIZE      (4)
#endif

typedef unsigned short	ushort;
typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;


/**
* @brief    ��ʼ����ͼ
* @return 
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/25
**/
int dns_view_init();

/**
* @brief    ͬ��mysql���ڴ�
* @return 
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/22
**/
void dns_view_syn();

/**
* @brief    ������ͼ
* @return 
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/25
**/
void dns_view_destroy();

/**
* @brief   �½���ͼ
* @param   view_id          ��ͼid
*
* @return 0 - �ɹ�  /  -1 - ʧ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/25
**/
int dns_view_create(ushort view_id);

/**
* @brief   ɾ�������ٳ�
* @param   view_id          ��ͼid
*
* @return 0 - �ɹ�  /  -1 - ʧ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/25
**/
int dns_view_drop(ushort view_id);

/**
* @brief   Ϊ��ͼ����IP
* @param   view_id          ��ͼid
* @param   ipaddr           ip��ַ
*
* @return 0 - �ɹ�  /  -1 - ʧ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/25
**/
int dns_view_insert(ushort view_id,char ipaddr[MAX_IP_LEN]);

/**
* @brief   Ϊ��ͼɾ��IP
* @param   view_id          ��ͼid
* @param   ipaddr           ip��ַ
*
*
* @return 0 - �ɹ�  /  -1 - ʧ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/25
**/
int dns_view_remove(ushort view_id,char ipaddr[MAX_IP_LEN]);


/**
* @brief   ��ȡ��ͼip��ַ
* @param   view_id          ��ͼID
* @param   ipaddr         	ip��ַ
*
* @return  �ɹ���ȡ���ֽ�����0Ϊʧ��
* @remark null
* @see     
* @author hyb      @date 2013/07/25
**/
int dns_view_get_sockaddr(ushort view_id,sockaddr * ipaddrs[MAX_ACTION_SIZE]);

/**
* @brief   �����ڴ���������ͼ��Ϣ��������Ч��ͼ��Ŀ
* @return node ��Ŀ
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/25
**/

int dns_view_node_count();

/**
* @brief   �����ڴ���������ͼ��Ϣ�������ڴ�״̬���
* @return 0 - �ɹ�  /  -1 - ʧ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/25
**/

int dns_view_display(char*output,int max_len);



/**
* @brief    ��ջ�������
* @return 
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/25
**/
void dns_view_clear();



/**
* @brief   Ϊ��ͼ���ô����ض���IP
* @param   view_id          ��ͼid
* @param   ipaddr           ip��ַ
*
* @return 0 - �ɹ�  /  -1 - ʧ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/11/25
**/
int dns_view_err_set(ushort view_id,char ipaddr[MAX_IP_LEN]);


/**
* @brief   Ϊ��ͼ��մ����ض���IP
* @param   view_id          ��ͼid
*
*
* @return 0 - �ɹ�  /  -1 - ʧ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/25
**/
int dns_view_err_unset(ushort view_id);

/**
* @brief   ��ȡ��ͼ�����ض���IP��ַ
* @param   view_id          ��ͼID
* @param   ipaddr         	ip��ַ
*
* @return  �ɹ���ȡ���ֽ�����0Ϊʧ��
* @remark null
* @see     
* @author hyb      @date 2013/07/25
**/
int dns_view_err_get_sockaddr(ushort view_id,struct in_addr * ipaddr);


/**
* @brief   Ϊ��ͼ���÷�DNS����ָ��IP
* @param   view_id          ��ͼid
* @param   ipaddr           ip��ַ
*
* @return 0 - �ɹ�  /  -1 - ʧ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/11/25
**/
int dns_view_non_set(ushort view_id,char ipaddr[MAX_IP_LEN]);

/**
* @brief   Ϊ��ͼ��շ�DNS����ָ��IP
* @param   view_id          ��ͼid
*
*
* @return 0 - �ɹ�  /  -1 - ʧ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/25
**/
int dns_view_non_unset(ushort view_id);


/**
* @brief   ��ȡ��ͼ��DNS����ָ��IP
* @param   view_id          ��ͼID
* @param   ipaddr         	ip��ַ
*
* @return  �ɹ���ȡ���ֽ�����0Ϊʧ��
* @remark null
* @see     
* @author hyb      @date 2013/07/25
**/
int dns_view_non_get_sockaddr(ushort view_id,sockaddr * ipaddr);


/**
* @brief   ����DNS������ȫ������
*
* @return �ɹ���0	ʧ�ܣ�-1
* @remark null
* @see     
* @author hezuoxiang      @date 2013/11/26
**/
int dns_view_server_all_on();

/**
* @brief   �ر�DNS������ȫ������
*
* @return ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/11/26
**/
void dns_view_server_all_off();


/**
* @brief   ��������DNS����ȫ������
*
* @return ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/11/26
**/
void dns_view_err_all_on();

/**
* @brief   �رմ���DNS����ȫ������
*
* @return ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/11/26
**/
void dns_view_err_all_off();


/**
* @brief   ������DNS����ȫ������
*
* @return ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/11/26
**/
void dns_view_non_all_on();

/**
* @brief   �رշ�DNS����ȫ������
*
* @return ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/11/26
**/
void dns_view_non_all_off();

#endif