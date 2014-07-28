/*******************************************************************************
 *                                �ļ���C�ӿڵ�ʵ��
 *******************************************************************************/
#include <sys/file.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>         //for macro PATH_MAX

#include "libbase_cflock.h"

#define LOCK_FILE_SURFIX    ".lock"

#define MAX_PATH_LEN        PATH_MAX


/**
 * @brief:  �����ļ�����ԭ���ļ����ĺ��棬�ټ�һ��.lock��׺
 * @param:  file - �ļ�·��
 * @return: ����ɹ����ش򿪺��ļ��ľ��fd,���ʧ�ܷ��� -1
 */
static int
open_lock_file(const char *file)
{
    unsigned int len;

    if (file == NULL
            || *file == '\0')
        return -1;

    //����ļ���̫������ֱ�ӷ��ؼ���ʧ��
    if (strlen(file) > MAX_PATH_LEN - sizeof(LOCK_FILE_SURFIX))
        return -1;

    char lock_file[MAX_PATH_LEN] = {0};
    strncpy(lock_file, file, sizeof(lock_file));
    len = strlen(lock_file);
    strncat(lock_file, LOCK_FILE_SURFIX, MAX_PATH_LEN-len);

    return open(lock_file, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP);
}

/**
 * @brief: ��ʼ��������f1������ڴ� ���ļ��б���ȡ��Ӧ�ľ��
 * @param: files - �ļ������б�
           nr -  �ļ���Ŀ
           lock - �ļ�������
 * @return: ����ɹ�����0��ʧ�ܷ���-1
 */
int
flock_init(struct flock_st *lock, const char *files[], int nr)
{
    int i;

    if (lock == NULL)
        return -1;

    lock->nr = 0;

    ///! ��ʼ��fd����
    lock->fd = (int*)malloc(nr * sizeof(int));
    if (lock->fd == NULL)
        return -1;
    for (i = 0; i < nr; i++)
        lock->fd[i] = -1;


    ///! �����е����ļ�
    for (i = 0; i < nr; i++)
    {
        int fd = open_lock_file(files[i]);

        if (fd == -1)
        {
            flock_destroy(lock);
            return -1;
        }

        lock->fd[i] = fd;
        //�����ȸ�ֵ����ĳ���ļ��򲻿���ʱ��õ���flock_clear
        lock->nr++;
    }


    return 0;
}


/**
 * @brief: �ļ�д����
 * @param: lock - �ļ�������
 * @return: ����ɹ�����0��ʧ�ܷ���-1
 */
int
flock_wrlock(const struct flock_st *lock)
{
    if (lock == NULL)
        return -1;

    int i;
    for (i = 0; i < lock->nr; i++)
    {
        if (flock(lock->fd[i],LOCK_EX|LOCK_NB) == -1)
        {
            //�ͷ�ǰ���Ѿ��򿪵ľ��
            flock_unlock(lock);
            return -1;
        }
    }


    return 0;
}


/**
 * @brief: �������ʧ�ܣ����ظ����μ���
 * @param: lock      - �ļ�������
           times     - �ظ����Ĵ���
           interval  - ÿ��ʧ�ܺ���Ϣ��ʱ��,��λ,us��1s = 1,000,000us
 * @return: ����ɹ�����0��ʧ�ܷ���-1
 */
int
flock_wrlock_repeat(const struct flock_st *lock, int times, int interval)
{
    if (lock == NULL)
        return -1;

    int i;
    int lock_suc = 0;
    int try_times = 0;

    for (i = 0; i < lock->nr; i++)
    {
        while (try_times <= times)
        {
            lock_suc = 0;
            if (flock(lock->fd[i], LOCK_EX|LOCK_NB) == -1)
            {
                if (++try_times > times)
                    break;

                if (interval > 0)
                    usleep(interval);
            }
            else
            {
                lock_suc = 1;
                break;
            }

        }

        if(!lock_suc)
            break;
    }

    if (!lock_suc)
    {
        flock_unlock(lock);
        return -1;
    }


    return 0;
}


/**
 * @brief: �ļ�����
 * @param: lock - �ļ�������

 * @return: ����ɹ�����0��ʧ�ܷ���-1
 */
int
flock_rdlock(const struct flock_st *lock)
{
    if (lock == NULL)
        return -1;

    int i;
    for (i = 0; i < lock->nr; i++)
    {
        if (flock(lock->fd[i], LOCK_SH|LOCK_NB) == -1)
        {
            flock_unlock(lock);
            return -1;
        }
    }


    return 0;
}


/**
 * @brief: �������ʧ�ܣ����ظ����μ���
 * @param: lock      - �ļ�������
           times     - �ظ����Ĵ���
           interval  - ÿ��ʧ�ܺ���Ϣ��ʱ��,��λ,us��1s = 1,000,000us
 * @return: ����ɹ�����0��ʧ�ܷ���-1
 */
int
flock_rdlock_repeat(const struct flock_st *lock, int times, int interval)
{
    if (lock == NULL)
        return -1;

    int i;
    int lock_suc = 0;
    int try_times = 0;

    for (i = 0; i < lock->nr; i++)
    {
        while (try_times <= times)
        {
            lock_suc = 0;
            if (flock(lock->fd[i],LOCK_SH|LOCK_NB) == -1)
            {
                if (++try_times > times)
                    break;

                if (interval > 0)
                    usleep(interval);
            }
            else
            {
                lock_suc = 1;
                break;
            }

        }

        if(!lock_suc)
            break;
    }

    if (!lock_suc)
    {
        flock_unlock(lock);
        return -1;
    }


    return 0;
}


/**
 * @brief: �ͷ��ļ���
 * @param: lock - �ļ�������
 * @return: �ɹ�����0��ʧ�ܷ���-1
 */
int
flock_unlock(const struct flock_st *lock)
{
    if (lock == NULL)
        return -1;

    int i;
    for (i = 0; i < lock->nr; i++)
    {
        if(lock->fd[i] != -1)
            flock(lock->fd[i], LOCK_UN);
    }


    return 0;
}


/**
 * @brief: �ر��ļ����
           �ͷŵ��ڴ�
 * @param: lock - �ļ�������
 * @return: �ɹ�����0��ʧ�ܷ���-1
 */
int
flock_destroy(struct flock_st *lock)
{
    if (lock == NULL)
        return -1;

    int i;
    for (i = 0; i < lock->nr; i++)
    {
        if(lock->fd[i] != -1)
            close(lock->fd[i]);

        lock->fd[i] = -1;
    }

    lock->nr = 0;
    free(lock->fd);
    lock->fd = NULL;


    return 0;
}

