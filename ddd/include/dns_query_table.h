#ifndef __DNS_QUERY_TABLE_H__
#define __DNS_QUERY_TABLE_H__

#include <netinet/in.h>
#include <netinet/ether.h>
#include <libbase.h>

typedef struct st_query_node 
{
    struct list_head    list;
	unsigned short		qid;
	unsigned short		qtype;
	struct sockaddr_in	srcip;
	unsigned short		clientid;
	int					view_id;
	time_t         		w_time;
    int                 dstip;
    int                 ethnum;
    struct ether_addr   smac;
    int                 bg_req;
    

   
    pthread_mutex_t     q_lock;
    time_t              del_time;
    
}st_query_node;

typedef struct st_query_key st_query_key;

/**
* @brief   ���ɲ�ѯ���ϣ��ֵ
* @param   domain       ��ѯ����
* @param   qid          query id
*
* @return  ��Ϊʧ��
* @remark null
* @see     
* @author hyb      @date 2013/07/24
**/
st_query_key *dns_query_table_getkey(char *domain, unsigned short qid,ushort port);



/**
* @brief   ���ٲ�ѯ���ϣ��ֵ
* @param   key          ��ѯ���ϣ��ֵ
*
* @return 
* @remark null
* @see     
* @author hyb      @date 2013/07/24
**/

void dns_query_table_delkey(st_query_key *key);



/**
* @brief  DNS��ѯ��Ӧ�б��ʼ��
* @return ��0ʧ��
* @remark null
* @see     
* @author hyb      @date 2013/07/24
**/
int dns_query_table_init();



/**
* @brief  DNS��ѯ��Ӧ�б�����
* @return 
* @remark null
* @see     
* @author hyb      @date 2013/07/24
**/

void dns_query_table_destroy();



/**
* @brief   �ѿͻ��������Ϣ���뵽��ѯ����
* @param   req_buf      �ͻ������
* @param   domain       ����
* @param   view_id      ��ͼ����
* @param   q_type       ���������
* @param   from         �ͻ�ip
*
* @return -1ʧ�ܣ��ɹ������µ����quiry id
* @remark null
* @see     
* @author hyb      @date 2013/07/24
**/

unsigned short dns_query_table_insert(char *req_buf, char *domain, int view_id,
        ushort q_type, ushort port,struct sockaddr *from, int dip ,struct ether_addr smac,int ethnum,int bg_req);



/**
* @brief   ͨ����ϣ��Ѱ�Ҳ�ѯ���ж�Ӧ�ͻ��������Ϣ
* @param   key      ��ѯ���ϣ��ֵ
*
* @return ��Ϊʧ��
* @remark null
* @see     
* @author hyb      @date 2013/07/24
**/
st_query_node *dns_query_table_find(st_query_key *key);



/**
* @brief   ͨ����ϣ��ɾ����ѯ���ж�Ӧ�ͻ��������Ϣ
* @param   key      ��ѯ���ϣ��ֵ
*
* @return 
* @remark null
* @see     
* @author hyb      @date 2013/07/24
**/
void dns_query_table_remove(st_query_node *node);



/**
* @brief  ��ȡ��ѯ���м�¼����
* @return ��¼����ֵ
* @remark null
* @see     
* @author hyb      @date 2013/07/24
**/
int dns_query_table_count();



/**
* @brief  �������ɾ������Ҫ�ļ�¼
* @return 
* @remark null
* @see     
* @author hyb      @date 2013/08/26
**/
void dns_query_table_check();


/**
* @brief 
* @return ��ʱ�ͷ�ɾ�������е���Դ
* @remark null
* @see     
* @author hyb      @date 2013/11/21
**/
void dns_query_table_clear();


#endif
