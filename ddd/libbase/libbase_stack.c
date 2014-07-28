/**
 * author hyb
 */
#include <string.h>
#include <stdio.h>
#include "libbase_stack.h"

#include "libbase_type.h"
#include "libbase_memory.h"

/**
 * ջ�ṹ
 */

#define DEFAULT_STACK_SIZE 8

struct stack_st {
    void **base;
    volatile uint32_t sp; /* ջ��index ָ��ջ����һ�����õ�Ԫ�� */
    uint32_t size;
    uint32_t __fixed;
};

/**
 * ����һ��ջ
 * \param name       ջ������
 * \param fixed_size �̶����ȣ������0��ָ���̶����ȣ�����������ȵ�ջpushʱ��ʧ��
 * \param flags ���Ա�ʶ
 *     ��ʱ�������Ժ���ܼ�����������
 * \return �ɹ�����һ���´����Ķ�
 */
h_stack_st *h_stack_create(const char *name, uint32_t fixed_size,
        uint32_t flags)
{
    h_stack_st *stack;
    if ((stack = h_malloc(sizeof(*stack))) == NULL)
        return NULL;

    bzero(stack, sizeof(*stack));

    stack->sp = 0;
    if (fixed_size != 0) {
        if ((stack->base = h_malloc(sizeof(void *) * fixed_size)) == NULL)
            goto err;
        stack->size = fixed_size;
        stack->__fixed = 1;
    } else {
        stack->base = h_malloc(sizeof(void *) * DEFAULT_STACK_SIZE);
        if (stack->base == NULL)
            goto err;
        stack->size = DEFAULT_STACK_SIZE;
        stack->__fixed = 0;
    }

    return stack;

err:
    h_free(stack);
    return NULL;
}

/**
 * ����һ��ջ
 * \param st �Ϸ���ջ
 */
void h_stack_destroy(h_stack_st *stack)
{
    h_free(stack->base);
    h_free(stack);
}

/**
 * ��ջ��ѹ��һ��Ԫ��
 * \param st �Ϸ��Ķ�
 * \param data �û�����
 * \return �����ָ����fixed_size�����ڶ���ʱ���ط�0���������������0��
 *         ����Ƕ�̬�����ģ����ڴ����ʧ�ܵ�ʱ�򷵻ط��㡣
 */
int h_stack_push(h_stack_st *stack, void *data)
{
    void *tmp;

    if (stack->sp == stack->size)
    {
        printf("--------- stack->sp:%d stack->size:%d! -----------\n",stack->sp,stack->size);
    }
    
    /* ��ջ���Ǵ����쳣�Ͷ�̬���� */
    if (stack->sp > stack->size) {
        
        if (stack->__fixed)
        {
            printf("stack->sp:%d stack->size:%d!\n",stack->sp,stack->size);
            return -1;
        }
        
        printf("enlarge!!\n");
        stack->size = stack->size << 1;
        tmp = h_realloc(stack->base, stack->size * sizeof(void *));
        if (!tmp) {
            printf("die there!\n");
            return -1;
        }
        stack->base = tmp;
    }
    stack->base[stack->sp] = data;
    stack->sp++;
    return 0;
}

/**
 * ��ջ�ϵ���һ������
 * \param st �Ϸ��Ķ�
 * \param ret �������ݴ�ŵ�ַ
 * \return �ɹ�����0�����򷵻ط�0
 */
int h_stack_pop(h_stack_st *stack, void **ret)
{
    void *tmp;
    unsigned int ssize, size;

    if (stack->sp == 0)
        return -1;
    //stack->sp--;
    int temp = --stack->sp;

    if (!stack->__fixed) {
        ssize = stack->size >> 2; /* ���������Ĵ�С�������ǵ��ķ�֮һ��ʱ������ */
        size = stack->size >> 1;  /* ����֮��Ĵ�С,������������ԭ��Сһ�� */
        if (temp < ssize && size >= DEFAULT_STACK_SIZE) {
            tmp = h_realloc(stack->base, size * sizeof(void *));
            if (tmp != NULL) {
                stack->size = size;
                stack->base = tmp;
            }
        }
    }
    *ret = stack->base[temp];
    return 0;
}
