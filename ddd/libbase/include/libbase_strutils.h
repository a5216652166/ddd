/**
 * \file strutils.h
 * �ִ���������
 * \author hyb
 * \defgroup base ����������
 * \{
 */

#ifndef __LIBWNS_STRUTILS_H__
#define __LIBWNS_STRUTILS_H__

#include "libbase_comm.h"
#include <stdarg.h>

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#ifdef SANGFOR_DEBUG
    #define    STRSAFE_ASSERT(expression) do{ \
            if (!(expression)) { \
                fprintf(stderr, \
                    "assertion \"%s\" failed: file \"%s\", line %d\n", \
                    #expression, \
                    __FILE__, __LINE__); \
                abort(); \
            } \
        }while(0)
#else  /* Release version */
    #define    STRSAFE_ASSERT(expression)   do{}while(0)
#endif

/**
 * �ַ����Ӵ����Һ���
 * \param str Դ�ִ�
 * \param slen Դ�ִ�����
 * \param match Ҫ���ҵ����ִ�
 * \param mlen �Ӵ��ĳ���
 * \param start ���ҵ����
 * \return �Ӵ���Դ�ִ��е���ʼƫ�ƣ��Ҳ����Ӵ��򷵻�-1
 */
int str_find(const char *str, unsigned int slen,
        const char *match, unsigned int mlen,
        unsigned int start);

/**
 * ����ϵͳstrstr���Ӵ����Һ���
 * \param str Դ�ִ�
 * \param len Դ�ִ�����
 * \param match Ҫ���ҵ����ִ�
 * \param mlen �Ӵ��ĳ���
 * \return �Ӵ���Դ������ʼָ�룬�Ҳ����Ӵ�����NULL
 */
const char *str_nstr(const char *str, unsigned int len, const char *match, unsigned int mlen);

/**
 * ����ϵͳstrchr���������ַ����ִ��������\0�ַ�
 * \param str Դ�ִ�
 * \param len Դ�ִ�����
 * \param c Ҫ���ҵ��ַ�
 * \return �ַ����ֵ���ʼָ�룬�Ҳ����򳬳����ȷ���NULL
 */
const char *str_nchr(const char *str, unsigned int len, int c);


#define SANGFOR_TRUNC ((size_t)-1)

/**
 *    �ַ������ӡ�ʱ�临�Ӷ�O(m + n), m��n�ֱ�ΪĿ�Ĵ���Դ������
 *    strcat_n��֤���������ַ�����0��β������size == 0
 *    @dst:     Ŀ���ַ�����ַ
 *    @size:    Ŀ���ַ����������ܳ���
 *    @src:     Դ�ַ�����ַ
 *    @return    < 0 ʱ��ʾ���������Ȳ����ã������ضϴ���
 */
int strcat_n(char *dst, size_t size, const char *src);

/**
 *    �ַ������ӣ����ضϰ汾��ʱ�临�Ӷ�O(m + 2n), m��n�ֱ�ΪĿ�Ĵ���Դ������
 *    strcat_ns��֤���������ַ�����0��β������size == 0
 *    @dst:     Ŀ���ַ�����ַ
 *    @size:    Ŀ���ַ����������ܳ���
 *    @src:     Դ�ַ�����ַ
 *    @count:   �������count���ַ���Ŀ�Ĵ���countΪSANGFOR_TRUNC�������ֵ��ʾ���������Ȳ���ʱ���Խض�
 *    @return    < 0 ʱ��ʾ���������Ȳ����ã�countΪSANGFOR_TRUNCʱ�ضϣ�����Ŀ�Ĵ������κ��޸�
 */
int strcat_ns(char *dst, size_t size, const char *src, size_t count);

/**
 *    �ַ�������
 *    strcpy_n��֤���������ַ�����0��β������ size == 0
 *    @dst:     Ŀ���ַ�����ַ
 *    @size:    Ŀ���ַ����������ܳ���
 *    @src:     Դ�ַ�����ַ
 *    @return    < 0 ʱ��ʾ���������Ȳ����ã������ضϴ���
 */
int strcpy_n(char *dst, size_t size, const char *src);

/**
 *    �ַ������������ضϰ汾
 *    strcpy_ns��֤���������ַ�����0��β������ size == 0
 *    @dst:     Ŀ���ַ�����ַ
 *    @size:    Ŀ���ַ����������ܳ���
 *    @src:     Դ�ַ�����ַ
 *    @count:   ��࿽��count���ַ���Ŀ�Ĵ���countΪSANGFOR_TRUNC�������ֵ��ʾ���������Ȳ���ʱ���Խض�
 *    @return    < 0 ʱ��ʾ���������Ȳ����ã�countΪSANGFOR_TRUNCʱ�ضϣ�����Ŀ�Ļ����������κ��޸�
 */
int strcpy_ns(char *dst, size_t size, const char *src, size_t count);

/**
 *    ��ʽ��������ַ���������
 *    vsprintf_n��֤���������ַ�����0��β������ size == 0
 *    @buf:     �����������ַ
 *    @size:    ����������ܳ���
 *    @fmt:     �����ʽ�����ַ���
 *    @ap:      �ɱ�����б�
 *    @return    < 0 ʱ��ʾ���������Ȳ����ã��ѽضϴ������򷵻�ʵ��������ַ�����
 */
int vsprintf_n(char* buf, size_t size, const char* fmt, va_list ap);

/**
 *    ��ʽ��������ַ��������������ضϰ汾
 *    vsprintf_ns��֤���������ַ�����0��β������ size == 0
 *    @buf:     �����������ַ
 *    @size:    ����������ܳ���
 *    @count:   ������count���ַ���Ŀ�Ļ�������countΪSANGFOR_TRUNC�������ֵ��ʾ���������Ȳ���ʱ���Խض�
 *    @fmt:     �����ʽ�����ַ���
 *    @ap:      �ɱ�����б�
 *    @return    <  0 ʱ��ʾ���������Ȳ����ã�countΪSANGFOR_TRUNCʱ�ضϣ����򷵻ؿմ�
 *                 >= 0 ʱ��ʾʵ��������ַ�����
 */
int vsprintf_ns(char* buf, size_t size, size_t count, const char* fmt, va_list ap);

/**
 *    ��ʽ��������ַ���������
 *    sprintf_n��֤���������ַ�����0��β������ size == 0
 *    @buf:     �����������ַ
 *    @size:    ����������ܳ���
 *    @fmt:     �����ʽ�����ַ���
 *    @...:     �ɱ����
 *    @return    < 0 ʱ��ʾ���������Ȳ����ã��ѽضϴ������򷵻�ʵ��������ַ�����
 */
int sprintf_n(char* buf, size_t size, const char* fmt, ...) __attribute__((format(printf, 3, 4)));

/**
 *    ��ʽ��������ַ���������
 *    sprintf_ns��֤���������ַ�����0��β������ size == 0
 *    @buf:     �����������ַ
 *    @size:    ����������ܳ���
 *    @count:   ������count���ַ���Ŀ�Ļ�������countΪSANGFOR_TRUNC�������ֵ��ʾ���������Ȳ���ʱ���Խض�
 *    @fmt:     �����ʽ�����ַ���
 *    @...:     �ɱ����
 *    @return    <  0 ʱ��ʾ���������Ȳ����ã�countΪSANGFOR_TRUNCʱ�ضϣ����򷵻ؿմ�
 *                 >= 0 ʱ��ʾʵ��������ַ�����
 */
int sprintf_ns(char* buf, size_t size, size_t count, const char* fmt, ...) __attribute__((format(printf, 4, 5)));

/**
 *    �Ӹ�ʽ������н�����ȡ���������ضϰ汾
 *    ����%c��%s���븽�Ӳ���ָ�����������ȣ����Ȳ���ʱ��ֹ������%s�����'/0'����%c�������
 *    ���磺 sscanf_ns("%d, %s", &i, buf, 5);
 *    @buf:      �����ַ���
 *    @fmt:      ��ʽ�ַ�
 *    @...:      �������
 *    @return  �ɹ������Ĳ�������
 */
int sscanf_ns(const char *buf, const char *fmt, ...);

/**
 *    �Ӹ�ʽ������н�����ȡ����
 *    ����%c��%s���븽�Ӳ���ָ�����������ȣ����Ȳ���ʱ�ضϡ�%s�����'/0'����%c�������
 *    ���磺 sscanf_n("%d, %s", &i, buf, 5);
 *    @buf:     �����ַ���
 *    @fmt:     ��ʽ�ַ�
 *    @...:     �������
 *    @return   �ɹ������Ĳ�������
 */
int sscanf_n(const char *buf, const char *fmt, ...);

/**
 *    �Ӹ�ʽ���ļ��н�����ȡ��������������stdin
 *    ����%c��%s���븽�Ӳ���ָ�����������ȣ����Ȳ���ʱ�ضϡ�%s�����'/0'����%c�������
 *    ���磺 fscanf_n(fp, "%d, %s", &i, buf, 5);
 *    @fmt:     ��ʽ�ַ�
 *    @...:     �������
 *    @return   �ɹ������Ĳ�������
 */
int fscanf_n(FILE *stream, const char *fmt, ...);

/**
 * memcpy �İ�ȫ�汾
 * ��׼���memcpy���ܴ���dest��src���ص����ڴ�����
 * ����汾���԰�ȫ�����κ����
 *
 *  @dest:    Ŀ�ĵ�ַ
 *  @src:     Դ��ַ
 *  @return   ����dest��ַ
 */
void *memcpy_s(void *dest, const void *src, size_t n);

/**
 * strdup ���ڴ��ذ汾
 * strdup_s ��ʹ��wns_malloc���з��䣬��wns_free�ͷŷ�����ڴ�
 *
 */
char *strdup_s(const char *s);

/**
 * strndup ���ڴ��ذ汾
 * strndup_s ��ʹ��wns_malloc���з��䣬��wns_free�ͷŷ�����ڴ�
 *
 */
char *strndup_s(const char *s, size_t n);


/** \} */
#endif /* __LIBWNS_STRUTILS_H__ */
