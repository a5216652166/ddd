/*!
 * \file libbase_bmh.c
 * \brief ��ģʽƥ���㷨
 *
 * \author Adam Xiao (iefcu), iefcuxy@gmail.com
 * \date 10/08/2012 10:50:17 AM
 */

#ifndef BMH_H_2010_5_22
#define BMH_H_2010_5_22

#include <stdint.h>
#include <sys/cdefs.h>

typedef intptr_t bmh_handle;

__BEGIN_DECLS
/* __bmh_chr
 * ��buf��ʼ��nlen���ֽ�������bmhָ���Ĺؼ���
 * ����ֵָ��buf�еĹؼ��ֿ�ʼλ�ã����δƥ�䷵��NULL
 */
const unsigned char * bmh_chr(bmh_handle bmh,
        const unsigned char * buf, int len);
const unsigned char * bmh_chrlower(bmh_handle bmh,
        const unsigned char * buf, int len);
bmh_handle bmh_init(const unsigned char * patt, int len);
void bmh_uninit(bmh_handle bmh);

__END_DECLS

#endif
