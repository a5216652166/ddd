#include "rdkafka.h"  /* for Kafka driver */
#include "rd.h"
#include "rdtime.h"

#define SAMPLE_BROKERS "10.11.255.248:9092,10.11.255.249:9092,10.11.255.250:9092,10.11.255.251:9092,10.11.255.252:9092,10.11.255.254:9092"
#define	SAMPLE_TOPIC	"test"

#define	QUEUE_BUF_MAX_MSG	"100000"
#define	QUEUE_BUF_MAX_MSG_INT	(100000)

/***********************************************/
//function:				kafka_log_init
//description:			��ʼ��kafka client
//arguments:
//		brokers:		kafka�����������ӵ�ַ
//
//return:
//						�ɹ���rd_kafka_tָ��
//						ʧ�ܣ�NULLָ��
/***********************************************/
rd_kafka_t * kafka_log_init(char *brokers);



/***********************************************/
//function:				kafka_log_set_topic
//description:			������־���͵�topic
//arguments:
//		rk:		��kafka_log_init���ص�ָ��
//		topic:	topic������
//
//return:
//						�ɹ���rd_kafka_topic_tָ��
//						ʧ�ܣ�NULLָ��
/***********************************************/
rd_kafka_topic_t * kafka_log_set_topic(rd_kafka_t * rk,char*topic);


/***********************************************/
//function:				kafka_log_send
//description:			����һ����־
//arguments:
//		rkt:	��kafka_log_set_topic���ص�ָ��
//		msg:	��־����
//		msglen:	��־���ݳ���
//
//return:
//						�ɹ���0
//						ʧ�ܣ�-1
/***********************************************/
int kafka_log_send(rd_kafka_topic_t *rkt,char*msg,uint msglen);
