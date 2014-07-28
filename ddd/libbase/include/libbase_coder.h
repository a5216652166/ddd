/*!
 * \file libbase_coder.h
 * \brief ���������
 * ��ֲ�Ĵ���
 *
 * \author Adam Xiao (iefcu), iefcuxy@gmail.com
 * \date 2012-11-14 11:47:08
 */

#ifndef _LIBWNS_CODER_
#define _LIBWNS_CODER_

#include "libbase_type.h"

__BEGIN_DECLS

/* Do base-64 encoding on a hunk of bytes.   Return the actual number of
 ** bytes generated.  Base-64 encoding takes up 4/3 the space of the original,
 ** plus a bit for end-padding.  3/2+5 gives a safe margin.
 */
/**
 * ����������:base64����
 * @param [IN]  inbuf   Ҫ������ַ���
 * @param [IN]  inlen   ������ַ����ĳ���
 * @param [OUT] outbuf  �������ַ���
 * @param [IN]  outlen����Ŀռ�ĳ���
 * @return ���ر������ַ�������,ʧ�ܷ��أ�1
 */
int h_base64_encode(const uint8_t *inbuf, int inlen,
        uint8_t *outbuf, int outlen);

/* Do base-64 decoding on a string.  Ignore any non-base64 bytes.
 ** Return the actual number of bytes generated.  The decoded size will
 ** be at most 3/4 the size of the encoded, and may be smaller if there
 ** are padding characters (blanks, newlines).
 */
/**
 * ����������:base64�����ѹ��
 * @param [IN]  inbuf   Ҫ������ַ���
 * @param [IN]  inlen   ������ַ����ĳ���
 * @param [OUT] outbuf  �������ַ���
 * @param [IN]  outlen����Ŀռ�ĳ���
 * @return ���ؽ������ַ�������,ʧ�ܷ��أ�1
 */
int h_base64_decode(const uint8_t *inbuf, int inlen,
        uint8_t *outbuf, int outlen);

__END_DECLS

#endif /* end of include guard: _LIBWNS_CODER_ */
