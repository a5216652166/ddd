/**
 * \file crc.h
 * crc����
 * \author hyb
 * \defgroup base ����������
 * \{
 */
#ifndef __LIBWNS_CRC_H__
#define __LIBWNS_CRC_H__

#include "libbase_type.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * crc32����
 * \param str Ҫ���������ָ��
 * \param len ���ݵĳ���
 * \param crc crc�ĳ�ʼֵ��Ҳ�������ϴ�û�������crc�������Ϳ��Բ��ð�����һ����ȫ�������ڴ����档
 *
 * \return crc32ֵ���޷���32λ����
 */
uint32_t h_crc32(const uint8_t *buf, size_t len, uint32_t crc);

/**
 * crc����
 * \param str Ҫ���������ָ��
 * \param len ���ݵĳ���
 * \param crc crc�ĳ�ʼֵ��Ҳ�������ϴ�û�������crc�������Ϳ��Բ��ð�����һ����ȫ�������ڴ����档
 *
 * \return crc64ֵ���޷���64λ����
 */
uint64_t h_crc64(const uint8_t *buf, size_t len, uint64_t crc);

#ifdef __cplusplus
}
#endif

/** \} */
#endif /* __LIBWNS_CRC_H__ */
