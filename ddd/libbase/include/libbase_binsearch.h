/**
 * \file binsearch.h
 * ���ַ�����
 * \author hyb
 * \defgroup base ����������
 * \{
 */
#ifndef __LIBWNS_BINSEARCH_H__
#define __LIBWNS_BINSEARCH_H__

#include "libbase_type.h"
/**
 * ���ַ����ұȽϺ�������
 * \param elem ����Ԫ��ָ��
 * \param key ��binsearch�����key����
 * \return ���elem > keyӦ�÷���һ�����������elem < key���򷵻ظ���������򷵻�0
 */
typedef int32_t (*h_binsearch_cmp_func_t)(const void *elem, const void *key);

/**
 * ����������ִ�����ַ�����
 * \param base ������ʼ��ַ
 * \param nelem ����Ԫ�ظ���
 * \param esize ����Ԫ�ش�С
 * \param key ����Ŀ��key
 * \param compar �ȽϺ���
 * \return ����Ԫ���±꣬-1Ϊδ�ҵ�
 */
int32_t h_binsearch(void *base, uint32_t nelem, uint32_t esize, void *key,
        h_binsearch_cmp_func_t compar);


/**
 * ȡ����ӽ�key����С�ڵ���key��Ԫ��
 * \param base ������ʼ��ַ
 * \param nelem ����Ԫ�ظ���
 * \param esize ����Ԫ�ش�С
 * \param key ����Ŀ��key
 * \param compar �ȽϺ���
 * \return ����Ԫ���±꣬-1Ϊδ�ҵ�
 */
int32_t h_binsearch_lower_bound(void *base, uint32_t nelem, uint32_t esize, void *key,
        h_binsearch_cmp_func_t compar);

/** \} */

#endif /* __LIBWNS_BINSEARCH_H__ */
