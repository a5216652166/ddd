/**
 * ���ݱ����ݽṹ
 * �����������ݼ�¼������
 * ���ԶԼ�¼�Ķ������������ͨ�����������������������
 * ֧�ֽ����ݱ��ݵ��ļ����Լ����ļ��ָ����ݱ�һ��Ҫ��ͬһ��ϵ�ṹ��
 * ��һ���õ����ݱ���������ݻָ������ڽṹ���С����С�˵�ԭ��
 *
 * usage:
 *     ��һ���� �������ݱ�
 *     �ڶ����� ����������
 *     �������� ��ɾ�Ĳ���ֲ���
 *     ���Ĳ��� ����ݻ�
 *     so easy;
 *
 * ���ߣ�hyb
 * 2012/10/30
 *
 **/
#ifndef __LIBWNS_DATA_TABLE_H__
#define __LIBWNS_DATA_TABLE_H__

/* ֧������������ */
#define DT_MAX_INDEX_FIELD  (8)

/* int�����룬����int������ĺ������� *! �� �Ĵ����� */
typedef enum {
    DT_ERR_MALLOC = 1,
    DT_ERR_INPUT,       /* ������������������NULL */
    DT_ERR_LOGIC,       /* ����ĵ����߼� */
    DT_ERR_FULL,        /* ������ */
    DT_ERR_EXITE,       /* �������Ѿ����ڣ����ͻ */
    DT_ERR_NO_EXITE,    /* �����ļ�¼������ */
    DT_ERR_FILE,        /* �ļ�����ʧ�� */
} dt_error_type_t;

/**
 * @brief ���ݱ�  ��ʽ�ٶ�˵����
 *   һ�����뱣֤��ID = 0�Ͻ���������֮���ڽ�����ɾ�Ĳ飬��Ȼ��Ϊ��ȷ��
 *   �������������������Ψһ�Բ��ɿⱣ֤��������ɾ��ʱ����ͬkeyֻ���ɾ��һ��
 *   ���������ݱ������������޸ģ�Ҫ��remove�ĺ���insert
 *
 **/

typedef struct h_dt_memory_allocer_st{
    void *(*malloc)(size_t size);
    void (*free)(void *);
    void *(*calloc)(size_t nmemb, size_t size);
} h_dt_memory_allocer_st;

typedef struct h_data_table_st *h_data_table_t;

/**
 * @breif ��¼�ͷŻص�
 *        ����ɾ����¼����destory���ݱ��ʱ���ͷŲ���ļ�¼�ڴ���
 **/
typedef
void (*h_data_table_free_cb_t)(void *data);

/**
 * @breif   �������ݱ�
 * @param free        �ͷż�¼�Ļص�������������ļ�¼�����ݽṹ����malloc��
 *                    ƽ���ڴ�ṹ������ֱ�����׼���free�Ϳ����ˣ�
 * @param record_size ÿ����¼�Ĵ�С
 * @param max_record  ���ܴ�ŵ����ļ�¼���������Ƕ��ı�����
 * @param allocer     �����ڲ��ڴ��������ΪNULL����malloc��free��calloc
 *
 * @return
 *     ���ݱ�ľ��
 *     NULLʧ��
 *
 **/
h_data_table_t h_data_table_create(h_data_table_free_cb_t free,
        unsigned int record_size, unsigned int max_record,
        h_dt_memory_allocer_st *allocer);


/**
 * @breif   �Ӽ�¼����ȡkey�Ļص�����
 *          ��ʹ�����ṩ�Ӽ�¼�У��ҵ�ָ���������
 *          ������Ľṹ����
 *          struct temp{
 *              int a;
 *              int b;
 *          };
 *          ȡa��Ļص����Զ���Ϊ
 *          return (void *)&((struct temp *)record)->a;
 * @param [IN]  record;
 * @return
 *     ���� ���ָ��
 **/
typedef
void* (*h_data_table_get_field_cb_t)(void *record);

/* �����ص������ĸ����꣬�������ٶ���һ����ȡkey�Ļص����� */
#define GEN_GET_FIELD_FUN(fun_name, str_type, member) \
static void * fun_name(void *record) { \
    return (void*)&((str_type *)record)->member; }


/**
 * @breif   ���һ��������
 *          ʹ��search���������������������
 * @param tab        ���ݱ�ľ��
 * @param field_id   ��¼�����Ψһ�ı�ʶ
 * @param field_size ������ռ���ڴ��С����sizeof(temp->a)��
 * @param ��ȡ������Ļص�
 *
 * @note    ���ݱ��û����뱣֤ ��add��field_id = 0�����������
 *          0 ����ID�����������������ݱ����Ϊ��ȷ��         XXX
 * @return
 *     0�ɹ�
 *     ��0ʧ��
 *
 **/

int h_data_table_add_index(h_data_table_t tab, unsigned int field_id,
        unsigned int field_size, h_data_table_get_field_cb_t get_field);

/**
 * @breif   �����ݱ����һ����¼
 * @param tab     ���ݱ�ľ��
 * @param record  Ҫ����ļ�¼��ָ��
 *
 * @return
 *     0�ɹ�
 *     ��0ʧ��
 *
 **/
int h_data_table_insert(h_data_table_t tab, void *record);

/**
 * @breif   ͨ��ָ��������������
 * @param field_id ��ʼadd_index��ʱ��������Ψһ��ʶ
 * @param key   Ŀ������
 *
 * @return
 *     ��¼��ָ��
 *     NULLʧ�ܣ�û�ҵ�
 *
 **/
void*
h_data_table_search(h_data_table_t tab, unsigned int field_id, void *key);

/**
 * @breif ɾ����¼
 *
 * @param tab   ���ݱ�ľ��
 * @param record   Ŀ������
 *
 * @return
 *     0�ɹ�
 *     ��0ʧ��
 *
 **/
int
h_data_table_delete(h_data_table_t tab, void* record);

/**
 * @breif ��ȡ��¼
 *        ��������������free_cbȥ�ͷż�¼��
 *        wns_data_table_delete�����free_cbȥ�ͷż�¼
 *
 * @param tab   ���ݱ�ľ��
 * @param record   Ŀ������
 *
 * @return
 *     0�ɹ�
 *     ��0ʧ��
 *
 **/
int
h_data_table_remove(h_data_table_t tab, void* record);

/**
 * @breif ɾ��ָ����ļ�¼
 *
 * @param tab   ���ݱ�ľ��
 * @param field_id ��ʼadd_index��ʱ��������Ψһ��ʶ
 * @param key   Ŀ������
 *
 * @return
 *     0�ɹ�
 *     ��0ʧ��
 *
 **/
int
h_data_table_del_by_field(h_data_table_t tab, unsigned int field_id,
        void *key);

/**
 * @breif ��ָ�������ȡ��¼
 *        ��������������free_cbȥ�ͷż�¼��
 *        wns_data_table_del_by_field �����free_cbȥ�ͷż�¼
 *
 * @param tab   ���ݱ�ľ��
 * @param field_id ��ʼadd_index��ʱ��������Ψһ��ʶ
 * @param key   Ŀ������
 *
 * @return
 *     0�ɹ�
 *     ��0ʧ��
 *
 **/
int
h_data_table_rmv_by_field(h_data_table_t tab, unsigned int field_id,
        void *key);

/**
 * @breif �������ݱ�
 *
 * @param tab   ���ݱ�ľ��
 *
 * @return
 *     ��
 *
 **/
void h_data_table_destory(h_data_table_t tab);

/**
 * @breif �����ݱ���ݵ��ļ� ��ͬ��API��
 *
 * @param tab   ���ݱ�ľ��
 * @param path  �ļ���·��
 *
 * @return
 *        �ɹ�����0
 *        ��0ʧ��
 **/
int h_data_table_to_file(h_data_table_t tab, const char *path);

/**
 * @breif ���ļ��ָ����ݱ�ֻ�ָ����ݣ����ָ����������ã������������
 *        ��¼���ȵȣ�������ʱ��Ҫ��֤�����ݱ�����������Ѿ���ʼ�����
 *        ���ͱ����ʱ����ȫһ�¡� ��ͬ��API��
 *
 * @param tab   ���ݱ�ľ��
 * @param path  �ļ���·��
 *
 * @return
 *        �ɹ�����0
 *        ��0ʧ��
 **/
int h_data_table_from_file(h_data_table_t tab, const char *path);

/**
 * @breif �����ص�
 * @param record ��ӵļ�¼
 * @param data   walk������data
 *
 * @return
 *        0��������
 *        ����ֹͣ����
 **/
typedef int (*h_data_table_walk_cb_t)(void *record, void *data);

/**
 * @breif �����������ݱ�
 * @param tab      ���ݱ�ľ��
 * @param walk_cb  �����Ļص�
 * @param data     �����ص���ָ��
 *
 * @return
 *       0�ɹ�
 *       ���ػص����ص�ֵ
 *
 **/

int h_data_table_walk(h_data_table_t tab,
        h_data_table_walk_cb_t walk_cb, void *data);

/**
 * @breif �������ݱ��һ��������Ԫ
 * @param tab      ���ݱ�ľ��
 * @param unit_id  ������Ԫid
 * @param walk_cb  �����Ļص�
 * @param data     �����ص���ָ��
 *
 * @return
 *       0�ɹ�
 *       ���ػص����ص�ֵ
 *
 **/
int h_data_table_unit_walk(h_data_table_t tab, unsigned int unit_id,
        h_data_table_walk_cb_t walk_cb, void *data);

/* @breif �������ݱ�ı�����Ԫ�� */
unsigned int h_data_table_get_foreach_unit_num(h_data_table_t table);

/* @breif �������ݱ��ִ�ļ�¼�� */
unsigned int h_data_table_get_record_num(h_data_table_t tab);



#ifdef HH_DEBUG
void h_data_table_state_show(h_data_table_t table);
#endif

#endif /* __DATA_TABLE_H__ */
