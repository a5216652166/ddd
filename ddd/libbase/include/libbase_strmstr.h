/**
 * \file strmstr.h
 * \author hyb
 * \defgroup base ����������
 * \{
 * \note ��ø�����ٵĶ�ģʽ����: ���-DMSTR_COMPILER ��������strmstr.c��õ�һ��״̬�������������ʹ��tools/inline-mstr-dfa���ߣ������ɵ�״̬ת��Ϊc���룬���Ի������ٵĶ�ģʽ������̬���롣
 */

#ifndef __LIBWNS_STRMSTR_H__
#define __LIBWNS_STRMSTR_H__

struct mstr_ctrl_st;

/**
 * ���ִ��������ƽṹ
 */
typedef struct mstr_ctrl_st mstr_ctrl_st;

/**
 * ����״̬
 */
typedef unsigned int mstr_state_st;

/**
 * �������ִ����ƽṹʱ���Դ�Сдѡ��
 */
#define MSTR_OPT_IGNORE_CASE	0x1

/**
 * ��ʹ����չ��ʹ����չ��Ĭ��ѡ���չ��ʹ��DFA���룬���ִ����������±���Ч�ʻ��Ϊ����
 */
#define MSTR_OPT_NO_EXTEND		0x2

/**
 * ����һ�����ִ����ƽṹ���ýṹ����ƥ���ִ�
 * \param option ѡ�MSTR_OPT_*��
 * \return ���ƽṹ
 */
mstr_ctrl_st *mstr_ctrl_create(unsigned int option);

/**
 * Ϊ���ƽṹ���һ��������
 * \param mc δ������Ŀ��ƽṹ
 * \param str Ҫ��ӵ�ģʽ��
 * \param len ���ģʽ���ĳ���
 * \param sid �������ص�ʱʹ�õ�ģʽ����ʶ
 * \return 0�ɹ�������ʧ�ܣ��ظ���ӻ��Ѿ����뽫�᷵��ʧ�ܣ�
 */
int mstr_ctrl_add_pattern(mstr_ctrl_st *mc, const unsigned char *str, unsigned int len, void *sid);

/**
 * ������ƽṹ������󷽿�����ƥ�䣬�޷�������ִ�
 * \param mc δ����Ŀ��ƽṹ
 */
void mstr_ctrl_compile(mstr_ctrl_st *mc);

/**
 * �ͷſ��ƽṹ
 * \param mc �Ϸ��Ŀ��ƽṹ
 */
void mstr_ctrl_destroy(mstr_ctrl_st *mc);

/**
 * ģʽ�����ص��������ͣ��ú�������Ϊ�������ݸ�mstr_search����ÿ�ѵ�һ���Ӵ�������һ��
 * ���ط�0ֵ����������������mstr_search�������ֵ
 * \param sid ƥ����Ӵ�sid(��add_patternʱָ��)
 * \param at �Ӵ����ֵ����������Դ����λ�ã����Ϊ���������ʾ�ô�������һ�������ĵ���λ��
 * \param userdata �û�����
 * \return ����0������������������ֵ������search�˳�
 */
typedef int (*mstr_func_t)(void *sid, int at, void *userdata);

/**
 * ����һ��״̬
 * \param ms ״̬
 */
void mstr_state_reset(mstr_state_st *ms);

/**
 * ִ���������������ʹ��ͬһ��δ��reset��״̬ʱ����Ϊ��Щsrc�������ŵġ�
 * \code
 mstr_state_st ms;

 mstr_state_reset(&ms);

 mstr_search(mc, &ms, "abcde", 5, NULL, match);		// 1
 mstr_search(mc, &ms, "fghij", 5, NULL, match);		// 2

 //������������ͬ��
 mstr_search(mc, &ms, "abcdefghij", 10, NULL, match);	// 3

 //����mc�а���defghģʽ������ִ�����2ʱ������match��at����Ϊ-2
 //��3�����at����Ϊ3

 * \endcode
 * \param mc ����Ŀ��ƽṹ
 * \param ms ״̬
 * \param src Ҫִ���������ִ�Ƭ��
 * \param len src�ĳ���
 * \param userdata ִ��callback���û�����
 * \param callback �������Ӵ��Ļص�
 * \return ���δָ��callback�������Ƿ��������Ӵ������򷵻�callback�ķ���ֵ
 */
int mstr_search(const mstr_ctrl_st *mc, mstr_state_st *ms,
				const unsigned char *src, unsigned int len,
				void *userdata,
				mstr_func_t callback);


/** \} */

#endif /* __LIBWNS_STRMSTR_H__ */
