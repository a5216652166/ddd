/************************************************************************************
 * @author:     hyb
 * @date:       2011-03-04
 * @brief:      C�ӿ��ļ���
 * 1. �����Ĺ���Ϊflock_init->flock_wrlock/flock_rdlock->flock_unlock->flock_destroy. 
 * 2. flock_wrlock_repeat/flock_rdlock_repeat������Ҫ�ظ������ĵط����÷���
 *    flock_wrlock/flock_rdlock��ͬ
 * 3. ��������lockָ�������һ��ʵ�壬ʹ�õ�ʱ�������������ʽ��ʵ��
 *                       struct flock_st lock;
 *                       flock_init(&lock,files,nr);
 * 4. ����ʱ�����������ļ���·�����ļ����ᱻ����Ŀ¼����һ����.lock��׺�����ļ� 
 *************************************************************************************/
#ifndef __C_FILE_LOCK_H__
#define __C_FILE_LOCK_H__

#ifndef __KERNEL__

#ifdef __cplusplus
extern "C"{
#endif


/**
 *       @brief: �ļ����ṹ�������洢�ļ������
 */
typedef struct flock_st
{
        int        nr; //��ǰ���ļ���Ŀ
        int       *fd; //��������ļ����ľ��
}flock_st;

/**
 * @brief: ��ʼ��������f1������ڴ� ���ļ��б���ȡ��Ӧ�ľ��
 * @param: files - �ļ������б�
           nr -  �ļ���Ŀ
           lock - �ļ�������
 * @return: ����ɹ�����0��ʧ�ܷ���-1
 */
extern int 
flock_init(struct flock_st *lock, const char *files[], int nr);

/**
 * @brief: �ļ�д����
 * @param: lock - �ļ�������
 * @return: ����ɹ�����0��ʧ�ܷ���-1
 */
extern int 
flock_wrlock(const struct flock_st *lock);


/**
 * @brief: �������ʧ�ܣ����ظ����μ���
 * @param: lock      - �ļ�������
           times     - �ظ����Ĵ���
           interval  - ÿ��ʧ�ܺ���Ϣ��ʱ��,��λ,us��1s = 1,000,000us
 * @return: ����ɹ�����0��ʧ�ܷ���-1
 */
extern int 
flock_wrlock_repeat(const struct flock_st *lock, int times, int interval);

/**
 * @brief: �ļ�����
 * @param: lock - �ļ�������
 * @return: ����ɹ�����0��ʧ�ܷ���-1
 */
extern int 
flock_rdlock(const struct flock_st *lock);


/**
 * @brief: �������ʧ�ܣ����ظ����μ���
 * @param: lock      - �ļ�������
           times     - �ظ����Ĵ���
           interval  - ÿ��ʧ�ܺ���Ϣ��ʱ��,��λ,us��1s = 1,000,000us
 * @return: ����ɹ�����0��ʧ�ܷ���-1
 */
extern int 
flock_rdlock_repeat(const struct flock_st *lock, int times, int interval);

/**
 * @brief: �ͷ��ļ���
 * @param: lock - �ļ�������
 * @return: �ɹ�����0��ʧ�ܷ���-1
 */
extern int 
flock_unlock(const struct flock_st *lock);

/**
 * @brief: �ر��ļ����
 *         �ͷŵ��ڴ� 
 * @param: lock - �ļ�������
 * @return: �ɹ�����0��ʧ�ܷ���-1
 */
extern int 
flock_destroy(struct flock_st *lock);

#ifdef __cplusplus
}
#endif

#endif

#endif

