/*=============================================================================
* @brief                                                                      *
* ������״����                                                                *
*                                                                             *
*                                                                             *
*                                         @����:hyb      @date 2013/04/10     *
==============================================================================*/


#ifndef __LIBBASE_RING_H__
#define __LIBBASE_RING_H__

struct h_ring;
typedef struct h_ring h_ring_st;

/* @flags of wns_ring_create define as follow, OR */
#define WNS_RING_F_SP_EN (1 << 0) /* "single-producer" ��������ʹ�� */
#define WNS_RING_F_SC_EN (1 << 1) /* "single-consumer" ��������ʹ�� */

#define WNS_RING_F_MORE_CORE (1 << 2) /* ���������־����ʾcpu��������������/�����߶࣬*/
									  /* ���߱�ʾ������/�����߱�cpu�������ࡣ�˱�־�Ե������ߵ���������Ч */

/**
 * ����һ����״����
 *
 * ��flagsָ���������ߺͶ������ߵ�ģʽ�£��������Ҳ���̰߳�ȫ��
 *
 * @param name  ��״���е�����
 * @param count ��״���еĴ�С�����ɵ�Ԫ�ظ���������Ϊ2��N�η�������0��ʵ��ring��ֻ��count-1�����ÿռ䡣
 * @param flags �������ߺ͵������߱�ʶ
 *     ������ WNS_RING_F_SP_EN ��������ʹ��
 *     WNS_RING_F_SC_EN ��������ʹ��
 *     ����������ȡ�� WNS_RING_F_SP_EN | WNS_RING_F_SC_EN
 *     Ĭ���Ƕ������߶�������
 *
 * @return
 *     �ɹ�����һ���´����Ļ�״���У����ɹ�����NULL
 */
h_ring_st * h_ring_create(const char *name, uint32_t count, uint32_t flags);

/**
 * ����һ����״����
 * 
 * ���뱣֤��û�г�����ӵĲ���ʱ����
 *
 * @param ring  ��״����ָ��
 *
 */
void h_ring_destroy(h_ring_st *ring);

/**
 * �ӻ�״�����г���
 *
 * ��������ܲ����̰߳�ȫ�������ڴ���ring�Ǵ����flags
 *
 * @param ring  ��״����ָ��
 * @param obj_p ��ų������ݵı����ĵ�ַ
 * 
 * @return
 *     0:  �ɹ���Ԫ�س���
 *   ��0:  ʧ�ܣ�����û��Ԫ�س��ӣ�����Ϊ��
 */
int32_t h_ring_dequeue(h_ring_st *ring, void **obj_p);

/**
 * ��״�������
 *
 * ��������ܲ����̰߳�ȫ�������ڴ���ring�Ǵ����flags
 *
 * @param ring  ��״����ָ��
 * @param obj   ��ӵ�����
 * 
 * @return
 *     0:  �ɹ�
 *   ��0:  ʧ��
 */
int32_t h_ring_enqueue(h_ring_st *ring, void *obj);

/**
 * һ�γ��Ӷ��Ԫ�أ��������Ϊһ�γ���һ���ڴ�
 *
 * ��������ܲ����̰߳�ȫ�������ڴ���ring�Ǵ����flags
 *
 * @param ring  ��״����ָ��
 * @param obj_table һ��ָ��ָ��void *��Ԫ�أ����ָ��
 * @param n  ��Ҫ���Ӵ���Ԫ�ر��еĳ���Ԫ�صĸ���
 *
 * @return
 *     0:  �ɹ�
 *   ��0:  ʧ��
 */
int32_t h_ring_dequeue_bulk(h_ring_st *ring, void **obj_table, uint32_t n);

/**
 * һ����Ӷ��Ԫ�أ��������Ϊһ�����һ���ڴ�
 * 
 * ��������ܲ����̰߳�ȫ�������ڴ���ring�Ǵ����flags
 * 
 * @param ring  ��״����ָ��
 * @param obj_table һ��ָ��ָ��void *��Ԫ�أ����ָ��
 * @param n  ��Ҫ���Ӵ���Ԫ�ر��еĳ���Ԫ�صĸ���
 *
 * @return
 *     0:  �ɹ�
 *   ��0:  ʧ��
 */
int32_t h_ring_enqueue_bulk(h_ring_st *ring, void * const *obj_table, uint32_t n);


/**
 * �����Ƿ�Ϊ��
 *
 * ���̰߳�ȫ���ڶ��̵߳�ʱ�򣬲�һ����ʵʱ��ӳ��ring��״̬
 *
 * @param ring  ��״����ָ��
 * 
 * @return
 *     0: �ǿ�
 *   ��0: ��
 */
int32_t h_ring_empty(const h_ring_st *ring);

/**
 * �����Ƿ�Ϊ��
 *
 * ���̰߳�ȫ���ڶ��̵߳�ʱ�򣬲�һ����ʵʱ��ӳ��ring��״̬
 *
 * @param ring  ��״����ָ��
 * 
 * @return
 *     0: ����
 *   ��0: ��
 */
int32_t h_ring_full(const h_ring_st *ring);

/**
 * �����Ѿ�����Ԫ�ظ���
 *
 * ���̰߳�ȫ���ڶ��̵߳�ʱ�򣬲�һ����ʵʱ��ӳ��ring��״̬
 *
 * @param ring  ��״����ָ��
 * 
 * @return
 *     ����
 */
uint32_t h_ring_count(const h_ring_st *ring);

/**
 * ���п���Ԫ�ظ���
 *
 * ���̰߳�ȫ���ڶ��̵߳�ʱ�򣬲�һ����ʵʱ��ӳ��ring��״̬
 *
 * @param ring  ��״����ָ��
 * 
 * @return
 *     ����
 */
uint32_t h_ring_free_count(const h_ring_st *ring);

#endif /* __LIBBASE_RING_H__ */
