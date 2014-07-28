/**
 * ջ�ṹ�������ӿ�
 * LIFO �ṹ
 *
 */

#ifndef __LIBWNS_STACK_H__
#define __LIBWNS_STACK_H__

#include "libbase_type.h"

/**
 * ջ�ṹ
 */
typedef struct stack_st h_stack_st;

/**
 * ����һ��ջ
 * \param name       ջ������
 * \param fixed_size �̶����ȣ������0��ָ���̶����ȣ�����������ȵ�ջpushʱ��ʧ�ܣ�Ϊ0ʱ��̬����
 * \param flags ���Ա�ʶ
 *     ��ʱ�������Ժ���ܼ�����������
 * \return �ɹ�����һ���´�����ջ
 */
h_stack_st *h_stack_create(const char *name, uint32_t fixed_size, uint32_t flags);

/**
 * ����һ��ջ
 * \param st �Ϸ���ջ
 */
void h_stack_destroy(h_stack_st *st);

/**
 * ��ջ��ѹ��һ��Ԫ��
 * \param st �Ϸ���ջ
 * \param data �û�����
 * \return ���ջָ����fixed_size������ջ��ʱ���ط�0���������������0��
 *         ����Ƕ�̬�����ģ����ڴ����ʧ�ܵ�ʱ�򷵻ط��㡣
 */
int h_stack_push(h_stack_st *st, void *data);

/**
 * ��ջ�ϵ���һ������
 * \param st �Ϸ���ջ
 * \param ret �������ݴ�ŵ�ַ
 * \return �ɹ�����0�����򷵻ط�0
 */
int h_stack_pop(h_stack_st *st, void **ret);

#endif /* __LIBWNS_STACK_H__ */
