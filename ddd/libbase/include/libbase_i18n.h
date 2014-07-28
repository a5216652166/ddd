/**
 * \file i18n.h
 * ���ʻ�����
 * \author hyb
 * \defgroup base ����������
 * \{
 */
#ifndef __LIBWNS_I18N_H__
#define __LIBWNS_I18N_H__

/**
 * ���ʻ��ִ�ת��
 */
#define _T(x) wns_i18n_gettext(x)

/**
 * ���ʻ��ִ�ת��
 * \param ori_str �����ļ��е�id
 * \return �����ļ���ָ���ķ���
 */
const char *wns_i18n_gettext(const char *ori_str);

int wns_i18n_load_resource(const char *lang_id, const char *file);

/** \} */

/**
 * \defgroup i18n ���ʻ�
 * <h1>���ʻ�howto</h1>
 * ������ʻ���ϸ���ѱ�����������ڼ��ز��ʱ���Զ�������Ӧ����Դ�ļ�������ٸ����Ӳ�˵�����ʹ���֧�ֹ��ʻ���
 * \par dissector_datatype�е�����
 * <p>dissector_datatypeΪ�����Ψһ���֣���ô����Ӧ�����%config_root%/i18n/dissector_datatype.ini��Ϊ��Դ�ļ���
 * ���ģ����ļ������Ǳ���ģ������������������Ի�����ص��ִ��������ò��Ÿ��ļ���</p>
 * <p>һ���ṩ���ļ�����ô���뱣֤���ļ�ʹ�����µĸ�ʽ��д��
 * \code
 [1]
 Other = ����

 [3]
 Other = Other
 * \endcode
 * [1]��[3]Ϊ�ִ�������䣬���Ľ�ʹ��1�Σ�Ӣ��ʹ��3�Σ���webuisetting�����ã���"Other"Ϊ�����ִ���"����"Ϊ�����ִ������ļ�������������
 * "Other"����Ϊ"����"</p>
 *
 * <p>�����ԭ����IDS������ֻ�������ڵ�IDSֱ��ʹ����һ��ini�Ϸ��ִ���������define��ͷ�ļ��С�</p>
 * \par ���ڷ���
 * ����i18n_gettext���������з��룬(ʹ���»���`_'�������д)
 * ���еķ��붼������ͬһ���ط������Լ��ض����������ļ����������ͻ��
 * Ŀǰ��׼������ȥ������ֳ�ͻ���������д����ʱ��ñ�֤key��Ψһ�ġ�
 * \see i18n_gettext
 * \note һ���õ�ϰ���Ǳ���ʱ��Ҫ�ٶ���ǰ��ϵͳ���ԡ�ʹ��system_get_languageȡ�õ�ǰ���ԣ���ǰ���Զ���Ĳ����ʲô�ã���
 */

#endif /* __LIBWNS_I18N_H__ */
