/**
 * \file wns_chunk_ring.h
 * �����ݻ��λ�����ʵ�֣�������rte_ring
 * \defgroup wns_chunk_ring �����ݻ��λ�����
 * \{
 */

#ifndef __LIBWNS_CHUNK_RING_H__
#define __LIBWNS_CHUNK_RING_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <stdint.h>

#include "libbase_config.h"

#include "libbase_atomic.h"

#define CHUNK_RING_NAMESIZE 32 ///

typedef struct h_chunk_ring_st h_chunk_ring_st;

/**
 * ��ָ���ڴ��ϴ������λ�����
 * \param name ����������
 * \param size ���������ȣ�����Ϊ2��N�η���ÿһ��Ԫ����Ҫһ������ṹ����˻������Ĵ�С���Ǽ򵥵�Ԫ�ش�С����Ԫ�ظ����������Դ�
 * \param flags ����
 *     Ϊ�˺�wns_ring�Ľӿ�ͳһ
 * \return �����������mem�����򷵻�NULL��size����2��N�η���
 *
 * chunk_ring �Ƕ������߶��������̰߳�ȫ��
 */
h_chunk_ring_st *h_chunk_ring_create(const char *name, uint32_t size, uint32_t flags);

/**
 * ����һ����״����
 *
 * ���뱣֤��û�г�����ӵĲ���ʱ����
 *
 * @param ring  ��״����ָ��
 *
 */
void h_chunk_ring_destroy(h_chunk_ring_st *r);

/**
 * ���һ��chunk
 * \param r ���λ�����
 * \param chunk ������ָ��
 * \param chunk_size �����ݳ���
 * \return
 *   - 0: �ɹ�
 *   - -EINVAL: ���С����ring����(max_chunkָ��)
 *   - -ENOBUFS: �ռ䲻��
 */
int32_t h_chunk_ring_enqueue(h_chunk_ring_st *r, const char *chunk, uint32_t chunk_size);

/**
 * ��ȡһ�����Գ��ӵ�chunk, ���ǲ�����������
 * ע����ӻ���Ҫ�ܹ���������һ��chunk
 * \param r ���λ�����
 * \param chunk �����ݻ�����ָ��
 * \param chunk_size [in/out] ���봫��chunk�������Ĵ�С��������Գ��ӵ�chunk���ʵ�ʳ���
 * \return
 *   - 0: �ɹ�
 *   - -ENOENT:  ���пգ�û�г���
 *   - -ENOBUFS: �������ռ䲻��
 */
int32_t h_chunk_ring_peek(h_chunk_ring_st *r, char *chunk, uint32_t *chunk_size);

/**
 * ����һ��chunk��ע����ӻ���Ҫ�ܹ���������һ��chunk
 * \param r ���λ�����
 * \param chunk �����ݻ�����ָ��
 * \param chunk_size [in/out] ���봫��chunk�������Ĵ�С��������ӵ�chunk���ʵ�ʳ���
 * \return
 *   - 0: �ɹ�
 *   - -ENOENT:  ���пգ�û�г���
 *   - -ENOBUFS: �������ռ䲻��
 */
int32_t h_chunk_ring_dequeue(h_chunk_ring_st *r, char *chunk, uint32_t *chunk_size);

/**
 * ���λ������Ƿ�Ϊ��
 * \param r ���λ�����
 * \return 1Ϊ�գ�0�ǿ�
 */
int32_t h_chunk_ring_empty(const h_chunk_ring_st *r);

/**
 * ȡ�û��λ��������пռ䣨�Ծ����ܷ����chunk��
 * \param r ���λ�����
 * \param ���пռ���
 */
uint32_t h_chunk_ring_free_space(const h_chunk_ring_st *r);

/**
 * ����д�����������жϸû��λ�����û����д��
 * \param r ���λ�����
 * \return ���Ӻ��д����Ŀ
 */
int32_t h_chunk_ring_inc_writter(h_chunk_ring_st *r);

/**
 * ����д�룬������д��ȫ������д��󣬻���������Ϊ�յ�����£��ܻ�ȡ��0�ֽڵ����ݣ���ʾ�û���������������д��
 * \param r ���λ�����
 */
void h_chunk_ring_done_enqueue(h_chunk_ring_st *r);

/**
 * �Ƿ����д��
 * @return 1:���д��
 * @return 0:û�����д��, ����û���κ�д��
 */
int32_t h_chunk_ring_is_done(h_chunk_ring_st *r);

#ifdef DEBUG_CHUNK_RING
/**
 * ��ӡ���λ�������Ϣ
 * \param r ���λ�����
 */
void h_chunk_ring_dump(const h_chunk_ring_st *r);
#endif

/** \} */

#endif /* __LIBWNS_CHUNK_RING_H__ */


/* copyright see rte_atomic.h */
