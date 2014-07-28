/*=============================================================================
* @brief                                                                      *
* �¼�ģ��ƽ̨                                                                *
*                                                                             *
*                                                                             *
*                                         @����:���ܲ�      @date 2013/05/08  *
==============================================================================*/

#ifndef __EFLY__EV__H__2013_5_8__
#define __EFLY__EV__H__2013_5_8__


typedef struct ev_timer ev_timer;

typedef struct efly_ipc_svr efly_ipc_svr;



/**
* @brief   ��ʱ���ص�����
* @param   event_loop_callback_fun   
* @param   user_data   �û��������
*
* @return  ��
* @remark null
* @see     
* @author hyb      @date 2013/05/08
**/
typedef void (*event_timer_callback_fun)(void *user_data);



/**
* @brief   ipc��Ϣ�ص�����
* @param   event_ipc_callback_fun   
* @param   buf   ��Ϣ����
* @param   len   ��Ϣ����
* @param   src   ��ϢԴ(�Է�ipcע��ͻ���ʱ��������)
*
* @return 
* @remark null
* @see     
* @author hyb      @date 2013/05/08
**/
typedef void (*event_ipc_callback_fun)(void *buf, int32_t len, char *src, char *answer);



/**
* @brief    ��ʼ���¼�ģ�ͻ���
* @return   ��0ʧ��
* @remark null
* @see     
* @author hyb      @date 2013/05/08
**/
int efly_event_init();



/**
* @brief    �����¼���ѯ
* @return   -1ʧ�ܣ�����ɹ�
* @remark null
* @see     
* @author hyb      @date 2013/05/08
**/
int32_t efly_event_loop();



/**
* @brief    �����¼���ѯ(ֻ����һ��)
* @return   -1ʧ�� ����ɹ�
* @remark null
* @see     
* @author hyb      @date 2013/05/08
**/
int32_t efly_event_loop_once();


/**
* @brief   ���ö�ʱ��
* @param   f_timeout   ��һ�λص�ʱ��(����Ϊ��λ����Ϊ0�����̻ص�)
* @param   timeout     �ص����(����Ϊ��λ����������Ϊ0)
* @param   cb          �ص�����
* @param   arg         �û�����
*
* @return              ʧ�ܷ��ؿ�
* @remark null
* @see     
* @author hyb      @date 2013/05/08
**/
ev_timer * efly_timer_set(int32_t f_timeout, int32_t timeout, 
        event_timer_callback_fun cb, void *arg);



/**
* @brief   �ݻ�ָ����ʱ��
* @param   ev_timer   ��ʱ������
*
* @return 
* @remark null
* @see     
* @author hyb      @date 2013/05/08
**/
void efly_timer_unset(ev_timer *ev_timer);


/**
* @brief   ������ж�ʱ��
* @param  
*
* @return 
* @remark null
* @see     
* @author hyb      @date 2013/05/08
**/

void efly_timer_clear();


/**
* @brief   ע��ipc��Ϣ�ͻ���
* @param   pname   
*
* @return  ʧ�ܷ��ؿ�
* @remark null
* @see     
* @author hyb      @date 2013/05/08
**/
efly_ipc_svr *efly_ipc_init(char *pname);


/**
* @brief   ע��ipc��Ϣ�ͻ���
* @param   pname   
*
* @return  
* @remark null
* @see     
* @author hyb      @date 2013/05/08
**/
void efly_ipc_destroy(efly_ipc_svr *svr);


/**
* @brief   ע��ipc��ϢӦ����
* @param   svr   �ͻ��˶���
* @param   id    �ص�����id
* @param   cb    �ص���������
*
* @return  -1ʧ�ܣ�0�ɹ�
* @remark null
* @see     
* @author hyb      @date 2013/05/08
**/
int32_t efly_ipc_reg_func(efly_ipc_svr *svr, unsigned short id, 
        event_ipc_callback_fun cb);

#endif
