/**
 * \file iniparser.h
 * �ṩini�ļ���ȡ����
 * \author hyb
 * \defgroup base ����������
 * \{
 */
#ifndef __LIBWNS_INIPARSER_H__
#define __LIBWNS_INIPARSER_H__

#include "libbase_hash.h"

typedef struct h_ini_file_st h_ini_file_st;

/**
 * ����ini�ļ�
 * ʹ��ini_file_free�����ͷ�
 * \param filename ��ȡ��ini�ļ�·��
 * \retval NULL ����ʧ��
 * \retval !NULL ���سɹ�������ini_file_st�ṹ
 */
h_ini_file_st *h_ini_file_load(const char *filename);

/**
 * ���ini�ֶ�ֵ
 * \param ini ini�����ṹ
 * \param section_name ��������
 * \param key ��ֵ
 * \retval NULL ��ֵδ�ҵ�
 * \retval !NULL ��ֵȡֵ
 */
const char *h_ini_file_get(h_ini_file_st *ini, const char *section_name, const char *key);

/**
 * ini��������ص�
 * \param section_name ��������(ini_file_section_foreach��section_name����)
 * \param key ����
 * \param value ֵ
 * \param userdata �û��Զ�������(ini_file_section_foreach�е�userdata����)
 * \return ���ط�0ֵ���ᵼ��ini_file_section_foreach�������ظ�ֵ
 */
typedef int (*ini_section_traval_func_t)(const char *section_name,
        const char *key, const char *value,
        void *userdata);

/**
 * ini�������
 * \param ini ���õ�ini_file_st���
 * \param section_name ������
 * \param userdata �û�����
 * \param callback ÿ����ֵ�ϵĻص�����
 * \retval 0 ��������
 * \retval !0 ������callback���ص�ֵ
 */
int h_ini_file_section_foreach(h_ini_file_st *ini, const char *section_name, void *userdata,
        ini_section_traval_func_t callback);

/**
 * ini���ж������
 * \param ini ���õ�ini_file_st���
 * \param userdata �û�����
 * \param callback ÿ����ֵ�ϵĻص�����
 * \retval 0 ��������
 * \retval !0 ������callback���ص�ֵ
 */
int h_ini_file_foreach(h_ini_file_st *ini,void *userdata,
        ini_section_traval_func_t callback);

/**
 * �ͷ�ini�����ṹ
 * \param ini ini�����ṹ
 */
void h_ini_file_free(h_ini_file_st *ini);

/** \} */
#endif /* __LIBWNS_INIPARSER_H__ */
