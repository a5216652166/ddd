/**
 * \file heap.h
 * �����ݽṹ������ӿ�
 * \author hyb
 * \defgroup base ����������
 * \{
 */
 
#ifndef __LIBWNS_HEAP_H__
#define __LIBWNS_HEAP_H__

/**
 * �ѽṹ
 */
typedef struct heap_st h_heap_st;

/**
 * �ѽڵ�ȽϺ���
 * �践��һ���ڵ�ȽϽ����һ����˵����һ���ԱȲ�ֵ��������qsort��
 * ����a-b��ֵ����γ�С��(Сֵ�ȳ�)������b-a���γɴ��
 * \param a �Ƚϵ�һ��ֵ
 * \param b �Ƚϵڶ���ֵ
 * \return a��b�Ĳ�ֵ
 */
typedef intptr_t (*heap_comp_func_t)(void *a, void *b);



/**
 * ����һ����
 * \param cmp �Զ���ıȽϺ����������ָ������Ĭ�ϱȽϵ���pushʱ��ָ��
 * \param fixed_size �̶����ȣ������0��ָ���̶����ȣ�����������ȵĶ�pushʱ��ʧ�ܡ�Ϊ0��ʾ��̬������
 * \return �ɹ�����һ���´����Ķ�
 */
h_heap_st *h_heap_create(heap_comp_func_t cmp, uint32_t fixed_size);

/**
 * ����һ����
 * \param hp �Ϸ��Ķ�
 */
void h_heap_destroy(h_heap_st *hp);

/**
 * ���ضѵ���Ŀ
 */
uint32_t h_heap_count(h_heap_st *hp);

/**
 * ȡ�أ�����ɾ�����Ѷ������/��СԪ�أ�
 * \note ��pushʱ������NULL�����������޷��ж���ȡ��NULL����û��Ԫ�أ�������heap_countȡ��Ԫ�ظ���
 */
void * h_heap_gettop_simple(h_heap_st *hp);

/**
 * ȡ�ã�����ɾ�����Ѷ�
 * \note ����ǲ���ȫ�汾����Ҫ����ȷ��heap_count����0
 */
void * h_heap_gettop_unsafe(h_heap_st * hp);

/**
 * �����ѹ��һ��Ԫ��
 * \param hp �Ϸ��Ķ�
 * \param data �û����ݣ���ʹ�ô�����ʱ�ıȽϺ�����
 * \return �����ָ����fixed_size�����ڶ���ʱ���ط�0���������������0
 */
int h_heap_push(h_heap_st *hp, void *data);

/**
 * ȡ����ɾ���Ѷ�
 * \param hp �Ϸ��Ķ�
 * \param ret �Ѷ�����λ��
 * \return �ɹ�����0�����򷵻ط�0
 */
int h_heap_pop(h_heap_st *hp, void **ret);

/** \} */

#endif /* __LIBWNS_HEAP_H__ */
