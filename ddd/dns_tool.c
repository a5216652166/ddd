#include "dns_tool.h"
#include <string.h>
#include <stdio.h>



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

int memcpy_safe(void*dst,int dst_len,void * src,int src_len)
{
	if(dst_len<src_len)
	{
		return -1;
	}
	memcpy(dst,src,src_len);
	return 0;
}

/**
* @brief   ��ȫ�ڴ濽��
* @param   filename           	�ļ���
* @param   content       		Ҫд�������
* @param   len					���ݳ���
*
* @return  0 �ɹ���-1 ʧ��
* @remark null
* @see     
* @author hezuoxiang      @date 2013/07/23
**/
int write_file(char*filename,char*content,int len)
{
	FILE*file = fopen(filename, "w");
	if(file == NULL)
	{
		return -1;
	}
	
	fwrite(content, len, 1, file); 
	
	fclose(file);
	return 0;
}
