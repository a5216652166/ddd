/*=============================================================================
* @brief                                                                      *
* ��ϣ��(��ϣ�㷨Ϊtime33)                                                    *
*                                                                             *
*                                                                             *
*                                         @����:hyb      @date 2013/04/10     *
==============================================================================*/

#ifndef __LIBBASE_HASH_H__
#define __LIBBASE_HASH_H__

typedef struct h_hash_st h_hash_st;

/**
 * �ͷŹ�ϣ����data�ֶεĺ�������
 * �ͷź�����Ӧ�öԵ�ǰhash������ɾ�������������ֲ���Ҫ������
 * \param data ����ָ��
 */
typedef void (*hash_data_free_func_t)(void *data);

/** 
 * ��ϣ��������
 * \param key ��ϣ���key
 * \param klen key�ĳ���
 */
typedef unsigned int (*hash_key_func_t)(const void *key, int klen);

/**
 * ȡ�ù�ϣ������
 */
unsigned int h_hash_count(h_hash_st *ht);

/**
 * ����һ����ϣ��
 * ʹ��hash_destroy�ͷŴ����Ĺ�ϣ��
 * \param del �ͷ�data�Ļص�������data�ͷŽ��ڹ�ϣ�����ٻ�key���滻ʱִ�У�����Ϊ�գ�Ĭ�ϲ��ͷţ�
 * \param keyf ʹ���Զ���Ĺ�ϣ����������Ϊ�գ�Ĭ��ʹ��time33���ֽڽ��м��㣩
 * \param soltnum ��ϣ��Ĺ�ϣͰ����, ��ϣͰ����Ϊ0ʱ��ϣͰ�ᶯ̬��������ϣͰ������������2��n�η���
 * \retval NULL ����ʧ��
 * \retval !NULL ��ϣ��ṹָ��
 * ע�⣺
 *     �ڴ���slotnum == 0��ģʽ�½������Ų����ڴ����ͣ����Ҳ�������Ԫ��ɾ����������������destory�������١�
 */
h_hash_st *h_hash_create(hash_data_free_func_t del, hash_key_func_t keyf, unsigned int slotnum);

/**
 * ��ϣ�����
 * \note ��������key���ڣ��µ�val���滻�Ѵ��ڵ����ݣ����滻�����ݽ����ù�ϣ��data�ͷŻص������ͷ�
 * \param ht ��ϣ��ṹ
 * \param key key�ֶ�
 * \param klen key�ĳ���
 * \param val ���������
 * \retval 0 ����ɹ�
 * \retval !0 ����ʧ�ܣ��ڴ���䲻���ȵ�ԭ��
 */
int h_hash_insert(h_hash_st *ht, const void *key, int klen, void *val);

/**
 * ��ϣ�����
 * \param ht ��ϣ��ṹ
 * \param key key�ֶ�
 * \param klen key�ĳ���
 * \param [out] val ��������ָ��
 * \retval 0 �ɹ�����
 * \retval !0 �޷��ҵ�
 */
int h_hash_search(h_hash_st *ht, const void *key, int klen, void **val);

/**
 * ��ϣ��ɾ����
 * \note ɾ�������ݽ�����data�ͷŻص������ͷ�
 * \param ht ��ϣ��ṹ
 * \param key key�ֶ�
 * \param len key�ĳ���
 * \retval 0 �ɹ�ɾ��
 * \retval !0 �޷��ҵ���ֵ
 */
int h_hash_delete(h_hash_st *ht, const void *key, int len);

/**
 * ��ϣ���ͷ�
 * \note �������ݽ�����data�ͷŻص������ͷ�
 * \param ht ��ϣ��ṹ
 */
void h_hash_destroy(h_hash_st *ht);

/**
 * ��ϣ������������ͣ�����ʱ����ÿ��key-value�ϵ��øú���
 * \param key �����ֶ�
 * \param klen �����ֶγ���
 * \param val ֵָ��
 * \param data �Զ�������
 * \return �������뷵��0���������������������ظ�ֵ
 */
typedef int (*hash_walk_func_t)(const void *key, int klen, void *val, void *data);

/**
 * ��ϣ������������еļ�ֵ�Ե���fn�ص�
 * \param ht ��ϣ��ṹ
 * \param data �û��ص�����
 * \param fn ��ÿ����ֵ�Ե��øûص�������ص����ط�0ֵ��������������������ֵ����
 * \retval 0 �ɹ����б�������
 * \retval !0 �ص������˷�0ֵ
 */
int h_hash_walk(h_hash_st *ht, void *data, hash_walk_func_t fn);

/**
 * ��ϣ���ֱ������м�״̬�ṹ
 */
typedef struct h_hcookie_st h_hcookie_st;

/**
 * ����һ������cookie
 * \param percent Ҫ�����İٷֱ�(0-1)
 * \return �ɹ�����һ��cookie������ΪNULL
 */
h_hcookie_st *h_hash_cookie_create(float percent);

/**
 * �ͷ�cookie
 * \param cookie �Ϸ���cookie
 */
void h_hash_cookie_destroy(h_hcookie_st *cookie);

/**
 * �������ñ����İٷֱ�
 * \param cookie �Ϸ���cookie
 * \param percent Ҫ�����İٷֱ�(0-1)
 */
void h_hash_cookie_set_percent(h_hcookie_st *cookie, float percent);

/**
 * ��ϣ���ֱ�������cookieָ���ٷֱȣ�����¼��ǰλ��
 * \note �ٷֱȽ���������Ŀ��������׼ȷ��Ŀ����wns_hash_walk��ͬ���ǣ��ú����������ص��ķ���ֵ
 * \param ht ��ϣ��ṹ
 * \param cookie cookie���ƽṹ
 * \param data �û�����
 * \param fn �ص�����
 */
void h_hash_walk_partial(h_hash_st *ht, h_hcookie_st *cookie, void *data, hash_walk_func_t fn);

void h_hash_slotinfo(h_hash_st *ht, int *counts, int ncount);



/** \} */
#endif /* __LIBBASE_HASH_H__ */
