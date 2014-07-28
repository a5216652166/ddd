#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/param.h>
#include "libbase_daemon.h"

int wns_init_daemon(char *path)
{
    int pid;
    if ((pid = fork()) > 0)
        exit(0); /* �Ǹ����̣����������� */
    else if (pid < 0)
        return -1; /* forkʧ�� */

    /* �ǵ�һ�ӽ��̣���̨����ִ�� */
    setsid(); /* ��һ�ӽ��̳�Ϊ�µĻỰ�鳤�ͽ����鳤 */
    /* ��������ն˷��� */

    if ((pid = fork()) > 0)
        exit(0); /* �ǵ�һ�ӽ��̣�������һ�ӽ��� */
    else if (pid < 0)
        return -1; /* forkʧ�� */

    /* �ǵڶ��ӽ��̣����� */
    /* �ڶ��ӽ��̲����ǻỰ�鳤 */

    /* �ı乤��Ŀ¼��/tmp */
    if (chdir(path ? path : "/tmp") != 0)
        return -2;

    /* parasoft suppress item BD-RES-INVFREE-1 */
    /* �رձ�׼�����������׼������ļ������� */
    close(STDIN_FILENO); /* parasoft-suppress BD-RES-INVFREE-1 */
    close(STDOUT_FILENO); /* parasoft-suppress BD-RES-INVFREE-1 */
    close(STDERR_FILENO); /* parasoft-suppress BD-RES-INVFREE-1 */
    /* parasoft unsuppress item BD-RES-INVFREE-1 */

    umask(0); /* �����ļ�������ģ */

    return 0;
}
