/**
 * \file backtrace.h
 * ��ջ��˷
 * \author hyb
 * \defgroup base ����������
 * \{
 */
#ifndef __LIBWNS_BACKTRACE_H__
#define __LIBWNS_BACKTRACE_H__

/**
 * ����ǰ���ö�ջ��Ϣд���ļ������Խӿ�
 * \param fd ��д�򿪵��ļ�������
 * \par ʾ��
 * \code
	backtrace_dump(2);		//�����ö�ջд����׼����
 * \endcode
 */
void h_backtrace_dump(int fd);

/** \} */
#endif /* __LIBWNS_BACKTRACE_H__ */
