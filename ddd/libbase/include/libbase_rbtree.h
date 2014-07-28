/**
 * \file rbtree.h
 * �����ʵ��
 * \author hyb
 * \defgroup base ����������
 * \{
 */

#ifndef __LIBBASE_RBTREE_H__
#define __LIBBASE_RBTREE_H__

#include <stdint.h>

/**
 * ��������ͽṹ
 */
struct h_rbtree_st;
typedef struct h_rbtree_st h_rbtree_st;

/**
 * ������ڵ�ȽϺ��������ڴ�С�����˳�򣬵�key1����key2������·������������򷵻ظ���
 * \param key1 �Ƚϵ�key1
 * \param ksize1 key1�ĳ���
 * \param key2 �Ƚϵ�key2
 * \param ksize2 key2�ĳ���
 * \return ����һ�������Ծ��������������˳��
 */
typedef int (*rbtree_cmp_func_t)(const void *key1, uint32_t ksize1,
        const void *key2, uint32_t ksize2);

/**
 * �������������ݵ��ͷź���
 * \param data ����
 */
typedef void (*rbtree_data_free_func_t)(void *data);

/**
 * �������������
 * \param data_free �������ݵ��ͷź��������ں�������ٻ�ڵ㱻�滻ʱ�Զ������ͷŸ�����
 * \param cmp �ڵ�key�ȽϺ���
 * \return �����
 */
h_rbtree_st *h_rbtree_create(rbtree_data_free_func_t data_free, rbtree_cmp_func_t cmp);

/**
 * �ͷź����
 * \param rb �����
 */
void h_rbtree_destroy(h_rbtree_st *rb);

/**
 * ȡ�ú�����еĽڵ���
 * \param rb �����
 * \return �ڵ���
 */
uint32_t h_rbtree_count(h_rbtree_st *rb);

/**
 * ������������ṹ��ʹ�øù��ȡ�������ǰ��Ԫ��(������iterator����)
 */
struct h_rb_cursor_st;
typedef struct h_rb_cursor_st h_rb_cursor_st;

/**
 * ȡ�õ�һ��Ԫ�أ���������ȫ���⣬����Ե�ǰcursor��key����ɾ����������ǰcursor����ʧЧ������������next/prev��Ϊ����
 * �������������Ҫ��ȡ����һ��Ԫ�أ��ٽ���Ԫ�ؽ���ɾ��
 * \param rb �����
 * \return �������ص�һ��Ԫ�صĹ�꣬û��Ԫ�ط���NULL
 */
const h_rb_cursor_st *h_rbtree_first(const h_rbtree_st *rb);

/**
 * ȡ�����һ��Ԫ��
 * \param rb �����
 * \return �����������һ��Ԫ�صĹ�꣬û��Ԫ�ط���NULL
 */
const h_rb_cursor_st *h_rbtree_last(const h_rbtree_st *rb);

/**
 * ȡ�õ�ǰ������һ��Ԫ��
 * \param itor ��ǰ���
 * \return ����������һ��Ԫ�صĹ�꣬û��Ԫ�ط���NULL
 */
const h_rb_cursor_st *h_rbtree_next(const h_rb_cursor_st *itor);

/**
 * ȡ�õ�ǰ������һ��Ԫ��
 * \param itor ��ǰ���
 * \return ����������һ��Ԫ�صĹ�꣬û��Ԫ�ط���NULL
 */
const h_rb_cursor_st *h_rbtree_prev(const h_rb_cursor_st *itor);

/**
 * ȡ�ù����ָԪ�ص�key
 * \param itor ��ǰ���
 * \return ����key��ָ��
 */
void *h_rb_cursor_get_key(const h_rb_cursor_st *itor);

/**
 * ȡ�ù����ָԪ�ص�key size
 * \param itor ��ǰ���
 * \return ����key��size
 */
uint32_t h_rb_cursor_get_ksize(const h_rb_cursor_st *itor);

/**
 * ȡ�ù����ָԪ�ص�val
 * \param itor ��ǰ���
 * \return ����Ԫ�ص�ֵ
 */
void *h_rb_cursor_get_val(const h_rb_cursor_st *itor);

/**
 * ����key��Ӧ��ֵ����rbtree_get_cursor��ͬ
 * \param rb �����
 * \param key key
 * \param ksize key�ĳ���
 * \param val [out] ����ǿգ���Ӹ�λ�÷��ض�Ӧ��ֵ
 * \return �ҵ�Ԫ�ط���0�����򷵻�-1
 */
int h_rbtree_search(const h_rbtree_st *rb, const void *key, uint32_t ksize, void **val);

/**
 * ����key��Ӧ�Ĺ�꣬��rbtree_search���ƣ������ع������ڱ���
 * \param rb �����
 * \param key key
 * \param ksize key�ĳ���
 * \return �ҵ�Ԫ�ط��ع�꣬���򷵻�NULL
 */
const h_rb_cursor_st *h_rbtree_get_cursor(const h_rbtree_st *rb, const void *key, uint32_t ksize);

/**
 * �������ڵ���key��һ��Ԫ�ع��(�߼��ϣ�ȡ���ں�����ԱȺ���)
 * \param rb �����
 * \param key key
 * \param ksize key�ĳ���
 * \return �ҵ�Ԫ�ط��ع�꣬���򷵻�NULL
 */
const h_rb_cursor_st *h_rbtree_lower_bound(const h_rbtree_st *rb, const void *key, uint32_t ksize);

/**
 * ����С�ڵ���key��һ��Ԫ�ع��(�߼��ϣ�ȡ���ں�����ԱȺ���)
 * \param rb �����
 * \param key key
 * \param ksize key�ĳ���
 * \return �ҵ�Ԫ�ط��ع�꣬���򷵻�NULL
 */
const h_rb_cursor_st *h_rbtree_upper_bound(const h_rbtree_st *rb, const void *key, uint32_t ksize);

/**
 * ����һ��Ԫ�أ����key���ڣ����滻����Ӧ��ֵ�����滻�ľ�ֵ�Զ�ʹ��createʱ������������������ͷ�
 * \param rb �����
 * \param key key
 * \param ksize key�ĳ���
 * \param val ��Ӧ��ֵ����ֵ���Զ�ʹ��createʱ������������������ͷ�
 * \return 0�ɹ�����0ʧ�ܡ�
 */
int h_rbtree_insert(h_rbtree_st *rb, const void *key, uint32_t ksize, void *val);

/**
 * ɾ��һ��Ԫ�أ����key���ڣ���Ӧ��ֵ���Զ�ʹ��createʱ������������������ͷ�
 * \param rb �����
 * \param key key
 * \param ksize key�ĳ���
 * \return 0�ɹ�����0û�����key
 */
int h_rbtree_delete(h_rbtree_st *rb, const void *key, uint32_t ksize);

/**
 * ����������������ͣ�ͨ�����������ĺ�����rbtree_walk��Ϊ��������
 * \param key ��
 * \param ksize ���ĳ���
 * \param val ֵ
 * \param userdata �û�����
 * \return ���ط�0ֵ��������������rbtree_walk�з��ظ�ֵ
 */
typedef int (*rbtree_walk_func_t)(const void *key, int ksize, void *val, void *userdata);

/**
 * ���������
 * \param rb �����
 * \param userdata ���ݸ����������û�����
 * \param fn ÿ����ֵ�ԵĴ�����
 * \return ��������0��������������ط�0ֵ�������������������̲����ظ�ֵ
 */
int h_rbtree_walk(h_rbtree_st *rb, void *userdata, rbtree_walk_func_t fn);

/** \} */

#endif /* __LIBBASE_RBTREE_H__ */
