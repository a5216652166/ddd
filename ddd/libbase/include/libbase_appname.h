/*!
 * \file libbase_appname.h
 * \brief ͨ��/proc/%d/status��ȡӦ�ó���ִ��ʱ������
 * mips�ܹ���û�ж���__progname�������, ����ͨ�������ʽ��ȡӦ�ó�����
 *
 * \author Adam Xiao (iefcu), iefcuxy@gmail.com
 * \date 2012-11-07 08:53:30
 */

#ifndef _LIBWNS_APPNAME_H_
#define _LIBWNS_APPNAME_H_

#include <sys/types.h>

__BEGIN_DECLS

/**
 * ��ȡ��ǰ�����appname
 */
const char* wns_current_appname(void);

__END_DECLS

#endif /* end of include guard: _LIBWNS_APPNAME_ */
