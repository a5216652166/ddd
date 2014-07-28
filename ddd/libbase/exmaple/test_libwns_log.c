#include <unistd.h>
#include "libhs.h"

int main(int argc, char *argv[])
{
    // ��Ҫ������־ģ��Ĳ�������ļ� "/wns/etc/sysconfig/log/test_libhs_log.ini"
    // (����test_libhs_logΪ��������ʱ������)
    // ����Ҳ���, ��ʹ��Ĭ�������ļ� "/wns/etc/sysconfig/log/xtest_run.ini"
    //
    // �����ļ��ο� libhs/log_plugins/xtest_run.ini

    int i;
    for (i = 0; ; i++) {
        sleep(1);

        // ���������־
        WNS_LOG_DEBUG(ET_DEBUG_LEVEL2, "test_<debug2-all>-%d", i);

        // ���������־
        WNS_LOG_WARN("test_<warn-all>-%d", i);

        // ���������־
        WNS_LOG_FATAL("test_<fatal-all>-%d", i);

        // �����ͨ��־
        WNS_LOG_INFO("test_<info-all>-%d", i);

        // �����ȫ��־
        WNS_LOG_SAFE("test_<safe-all>-%d", i);

        // ���������־��telnet
        WNS_WRITE_LOG(TO_TELNET, ET_FATAL, 0, "test_<fatal-telnet>-%d", i);

        // ���������־���ն�
        WNS_WRITE_LOG(TO_TERM, ET_DEBUG, ET_DEBUG_LEVEL6, "test_<debug6-term>-%d", i);

        // ���������־��logs
        WNS_WRITE_LOG(TO_LOGS, ET_DEBUG, ET_DEBUG_LEVEL4, "test_<debug4-logs>-%d", i);

        // ���������־���ļ�
        WNS_WRITE_LOG(TO_FILE, ET_DEBUG, ET_DEBUG_LEVEL8, "test_<debug8-file>-%d", i);
    }

    return 0;
}

