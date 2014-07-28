/*=============================================================================
* @brief                                                                      *
* �ڴ��������ӿڣ������ڴ���Ϣ����                                          *
*                                                                             *
*                                                                             *
*                                         @����:hyb      @date 2013/04/10     *
==============================================================================*/

#ifndef __LIBWNS_MEMORY_H__
#define __LIBWNS_MEMORY_H__

#include "libbase_comm.h"
#include "libbase_type.h"
#include "libbase_config.h"

/* �ο���protobuf-c��ʵ�ִ��� */
/* --- memory management --- */
typedef struct _WnsAllocator WnsAllocator;
struct _WnsAllocator
{
    void *(*alloc)(void *allocator_data, size_t size);
    void (*free)(void *allocator_data, void *pointer);
    void *allocator_data;
};

/*
 * This is the default system allocator, meaning it uses malloc() and free().
 */
extern WnsAllocator wns_default_alloctor;

/*!
 * �����Զ����ڴ������ڴ��ͷź���
 * @allocator �ڴ������ͷź���ָ��
 */
void h_set_alloctor(WnsAllocator *allocator);

/**
 * h_malloc - ��C��mallocһ��������һ�δ�СΪ @size���ڴ�
 * ������
 * @size: Ҫ������ڴ�Ĵ�С
 * ����ֵ:
 *     ������ڴ���׵�ַ - �ɹ�
 *     NULL - ʧ��
 * ע�⣺
 *     �̰߳�ȫ
 */
void *h_malloc(size_t size);

/**
 * h_realloc - ��C��reallocһ�����ı������ڴ���С
 * ������
 * @ptr:  �Ѿ�������ڴ��ָ��
 * @size: Ҫ������ڴ�Ĵ�С
 * ����ֵ:
 *     ������ڴ���׵�ַ - �ɹ�
 *     NULL - ʧ��
 * ע�⣺
 *     �̰߳�ȫ
 *     ��@ptr==NULL�൱�ڵ�����wns_malloc
 *     ��@size==0�൱�ڵ�����wns_free��������NULL
 */
void *h_realloc(void *ptr, size_t size);

/**
 * h_calloc - ��C��callocһ��������@nmemb����СΪ@size�������ڴ��
 * ������
 * @nmemb:  ��Ա��
 * @size:   ��Ա��С
 * ����ֵ:
 *     ������ڴ���׵�ַ - �ɹ�
 *     NULL - ʧ��
 * ע�⣺
 *     calloc��Է�����ڴ�����
 *     �̰߳�ȫ
 */
void *h_calloc(size_t nmemb, size_t size);

/**
 * h_free - ��C��freeһ�����ͷŷ�����ڴ�
 * ������
 * @ptr:  ������ڴ���׵�ַ
 * ����ֵ:
 *     ��
 * ע�⣺
 *     �̰߳�ȫ
 */
void h_free(void *ptr);

/**
 * zero_alloc - ����һ���ڴ棬�����ڴ���������
 * ������
 * @size:  Ҫ������ڴ��С
 * ����ֵ:
 *     ������ڴ���׵�ַ - �ɹ�
 * ע�⣺
 *     Σ�սӿڡ�
 *     �˽ӿ��ڴ����ʧ�ܻ�ֱ�Ӵ�ӡOut of memory ��ҵ�����������Ϊ�˱��ּ����ԡ�����ʹ��wns_callocȻ���жϷ���ֵ��
 *     ��Ϊ��ǰ����ô��Ƶģ��������ౣ�ּ����ԡ�
 */
void *zero_alloc(size_t size);

/**
 * h_mem_get_alloc_count - ��ȡwns_�������ڴ������ô���
 * ������
 *     ��
 * ����ֵ��
 *     �����ڴ������ô���
 * ע�⣺
 *     �̰߳�ȫ
 */
uint32_t h_mem_get_alloc_count();

/**
 * h_mem_clear_alloc_count - ����alloc������
 * ������
 *     ��
 * ����ֵ��
 *     ��
 * ע�⣺
 *     �̰߳�ȫ
 */
void h_mem_clear_alloc_count();

/**
 * h_mem_get_free_count - ��ȡwns_�������ڴ��ͷŵ��ô���
 * ������
 *     ��
 * ����ֵ��
 *     �����ڴ��ͷŵ��ô���
 * ע�⣺
 *     �̰߳�ȫ
 */
uint32_t h_mem_get_free_count();

/**
 * h_mem_clear_free_count - ����free������
 * ������
 *     ��
 * ����ֵ��
 *     ��
 * ע�⣺
 *     �̰߳�ȫ
 */
void h_mem_clear_free_count();

/**
 * h_mem_get_alloc_size_count - ��ȡ�ڴ����Ĵ�С��ͳ��
 * ������
 *     ��
 * ����ֵ��
 *     �����ڴ��ͷŵ��ô���
 * ע�⣺
 *     �̰߳�ȫ
 */
uint32_t h_mem_get_alloc_size_count();

/**
 * h_mem_clear_alloc_size_count - ����alloc_size������
 * ������
 *     ��
 * ����ֵ��
 *     ��
 * ע�⣺
 *     �̰߳�ȫ
 */
void h_mem_clear_alloc_size_count();



typedef struct h_mem_pool h_mem_pool_st;

/**
 * h_mem_pool_create - ����һ���ڴ��
 * ����:
 * @name:   �ڴ�ص�����
 * @nmemb:  �ڴ�������е��ڴ������
 * @size:   �ڴ��ÿ���ڴ��Ĵ�С
 * @flags:  �ڴ�ص�����
 *     ��ʱ�������Ժ���ܼ�������������
 * ����ֵ��
 *     �����ڴ�ص���������ָ�룩
 * ע�⣺
 *     ���̰߳�ȫ��Ϊ���ڴ�صķ���Ч�ʣ�����ÿ��cpu���Լ����ڴ�ء�
 */
h_mem_pool_st *h_mem_pool_create(const char *name, uint32_t nmemb, uint32_t size, uint32_t flags);

/**
 * h_mem_pool_destroy - �ݻ�һ���ڴ��
 * ����:
 * @mpd:   �ڴ��������
 * ����ֵ��
 *     ��
 * ע�⣺
 *     ���̰߳�ȫ��Ϊ���ڴ�صķ���Ч�ʣ�����ÿ��cpu���Լ����ڴ�ء�
 */
void h_mem_pool_destroy(h_mem_pool_st *mpd);

/**
 * h_mem_pool_get - ���ڴ��ȡ��һ���ڴ��
 * ����:
 * @mpd:   �ڴ��������
 * ����ֵ��
 *     �����ڴ����׵�ַ
 * ע�⣺
 *     ���̰߳�ȫ��Ϊ���ڴ�صķ���Ч�ʣ�����ÿ��cpu���Լ����ڴ�ء�
 */
void *h_mem_pool_get(h_mem_pool_st *mpd);

/**
 * h_mem_pool_put - �Ѵ��ڴ��ȡ�����ڴ�����·Ż��ڴ��
 * ����:
 * @mpd:   �ڴ��������
 * @ptr:   Ҫ�ͷŵ��ڴ���׵�ַ������������Ϸ��ԣ������߱��뱣֤�������ĵ�ַ��wns_mem_pool_get�õ��ġ�
 * ����ֵ��
 *     �����ڴ����׵�ַ
 * ע�⣺
 *     ���̰߳�ȫ��Ϊ���ڴ�صķ���Ч�ʣ�����ÿ��cpu���Լ����ڴ�ء�
 */
void h_mem_pool_put(h_mem_pool_st *mpd, void *ptr,int id);

#endif /* __LIBWNS_MEMORY_H__ */
