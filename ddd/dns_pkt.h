#ifndef __DNS_PKT_H__
#define __DNS_PKT_H__



/**
* @brief   Main�����У���DNS�������core
* @param   domain   
* @param   type   
* @param   view   
*
* @return 
* @remark null
* @see     
* @author hyb      @date 2014/05/20
**/
void request_to_core(char *domain,int type,int view);


/**
* @brief   Main�����У��ظ���Ϣ��Mgr
* @param   nameclass   
* @param   type   
* @param   view   
* @param   data   
* @param   result   
*
* @return 
* @remark null
* @see     
* @author hyb      @date 2014/05/22
**/
void answer_to_mgr(char *nameclass,int opt,int type,int view,char *data, int result);


#endif