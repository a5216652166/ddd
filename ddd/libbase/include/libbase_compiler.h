#ifndef __LIBWNS_COMPILER__H__
#define __LIBWNS_COMPILER__H__

#include "libbase_config.h"
/**
 * ���������š� �磺��̬���ɶ��.c�ļ���ɣ���.c�ṩ�ڲ��ӿڣ��������static�ɻᵼ���ڲ��Ҳ�������
 * �������static�ɻ�Ѹú������ŵ��������ܵ���ʹ�øö�̬��ĳ�����ų�ͻ
 * ʹ�÷�������.h��������ǰ���ϣ�����
 * LOCAL_API void xxx_func();
 */
#if __GNUC__ >= 4

#define LOCAL_API  __attribute__ ((visibility("hidden")))

#else

#define LOCAL_API

#endif

#ifdef __cplusplus

#define EXPORT_API extern "C" 

#else

#define EXPORT_API extern 

#endif



#endif /* __LIBWNS__COMPILER__H__ */

