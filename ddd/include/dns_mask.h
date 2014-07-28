#ifndef __DNS_MASK_H__
#define __DNS_MASK_H__

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
typedef unsigned long	ulong;


/**
* @brief    ��ʼ��mask��
* @return 
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/22
**/
int dns_mask_init();

/**
* @brief    ͬ��mysql���ڴ�
* @return 
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/22
**/
void dns_mask_syn();

/**
* @brief    ����mask��
* @return 
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/22
**/
void dns_mask_destroy();

/**
* @brief   �½�mask
* @param   ipaddr           ������ʼ��ַ
* @param   mask       		����λ��
* @param   view_id          ��ͼid
*
* @return 0 - �ɹ�  /  -1 - ʧ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/22
**/
int dns_mask_insert(char ipaddr[MAX_IP_LEN],int mask,ushort view_id);

/**
* @brief   ɾ��mask
* @param   ipaddr           ������ʼ��ַ
* @param   mask       		����λ��
*
* @return 0 - �ɹ�  /  -1 - ʧ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/22
**/
int dns_mask_remove(char ipaddr[MAX_IP_LEN],int mask);

/**
* @brief   ��������mask��view
* @param   ipaddr           ������ʼ��ַ
* @param   mask       		����λ��
* @param   view_id          ��ͼid
*
* @return 0 - �ɹ�  /  -1 - ʧ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/22
**/
int dns_mask_set(char ipaddr[MAX_IP_LEN],int mask,ushort view_id);

/**
* @brief   ˢ�¸��µ����ṹ
* @param   ��
*
* @return 0 - �ɹ�  /  -1 - ʧ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/29
**/
int dns_mask_fresh_view_to_control();


/**
* @brief   ˢ�¸��µ����ṹ-nowait
* @param   ��
*
* @return 0 - �ɹ�  /  -1 - ʧ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/29
**/
int dns_mask_fresh_view_to_control_nowait();


/**
* @brief   ��ȡip��Ӧ��view
* @param   ipaddr           ����
*
* @return  �ɹ���ȡ����view_id��-1Ϊʧ��
* @remark view id
* @see     
* @author hezuoxiang      @date 2013/07/22
**/
ushort dns_mask_get_view(struct in_addr * addr);

/**
* @brief   �����ڴ�������mask_view��Ϣ������node��Ŀ
* @return node ��Ŀ
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/22
**/
int dns_mask_view_node_count();

/**
* @brief   �����ڴ�������mask_control��Ϣ������node��Ŀ
* @return node ��Ŀ
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/22
**/
int dns_mask_control_node_count();

/**
* @brief   �����ڴ�������mask_view��Ϣ�������ڴ�״̬���
* @return 0 - �ɹ�  /  -1 - ʧ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/22
**/
int dns_mask_view_node_display(char*output,int max_len);

/**
* @brief   �����ڴ�������mask_control��Ϣ�������ڴ�״̬���
* @return 0 - �ɹ�  /  -1 - ʧ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/22
**/
int dns_mask_control_node_display(char*output,int max_len);

/**
* @brief    ��ջ�������
* @return 
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/22
**/
void dns_mask_clear();


#endif