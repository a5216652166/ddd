/**
* @filename   	dns_tool.h
* @brief  		һЩ���õķ���
* @author hezuoxiang      @date 2013/07/23
**/



/**
* @brief   ��ȫ�ڴ濽��
* @param   dst           	Ŀ��
* @param   dst_len       	Ŀ�껺�峤��
* @param   src				Դ
* @param   src_len          Ҫ�����ĳ���
*
* @return  0 �ɹ���-1 ʧ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/23
**/
int memcpy_safe(void*dst,int dst_len,void * src,int src_len);

/**
* @brief   ��ȫ�ڴ濽��
* @param   filename           	�ļ���
* @param   content       		Ҫд�������
* @param   maxlen				���ݵ���󳤶�
*
* @return  0 �ɹ���-1 ʧ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/23
**/
int write_file(char*filename,char*content,int maxlen);

