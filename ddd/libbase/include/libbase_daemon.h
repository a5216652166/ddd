#ifndef __LIBWNS_DAEMON_H__
#define __LIBWNS_DAEMON_H__

/**
 * wns_init_daemon - �����̱���ػ�����
 *     �����ն�
 *     �رձ�׼�����������׼����
 *     ����ǰ����Ŀ¼�л���@path
 *     �ı�Ĭ���ļ�����Ȩ��maskΪ0
 *
 * @param path Ҫ�л����ĵ�ǰ����Ŀ¼������ΪNULL���л���/tmp
 *
 * @return 0 �ɹ�
 *        -1 forkʧ��
 *        -2 �ı䵱ǰĿ¼ʧ��
 *
 * @note ����ʧ��ʱ����׼�����������ر�
 **/

int wns_init_daemon(char *path);

#endif /* __ __LIBWNS_DAEMON_H__ */
