#ifndef __DNS_PACK_H__
#define __DNS_PACK_H__

int dns_pack_head(char*result,char*domain,int domain_len);

int dns_pack_answer(char*result,int total_len,void *ip,unsigned short ttl);

void dns_pack_destroy(char *msg);

char *dns_pack_init();

void dns_edit_ttl(char* result, int total_len, unsigned short ttl);

void dns_edit_anum(char*result, unsigned short awnser_num);

void dns_edit_logo(char*result, unsigned short logo);




/**
* @brief   ����DNS��ѯ����
* @param   result   
* @param   domain   
* @param   domain_len   
* @param   type             DNS����
*
* @return  0 -ʧ�ܣ��ɹ����ذ�����
* @remark null
* @see     
* @author hyb      @date 2014/05/08
**/
int dns_pack_query(char*result,char*domain,int domain_len, int view, int type);



#endif
