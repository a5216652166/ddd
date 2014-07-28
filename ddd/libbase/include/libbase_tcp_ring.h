/**
 * \file wns_tcp_ring.h
 * �����ݻ��λ�����ʵ�֣�������wns_chunk_ring
 * \defgroup wns_tcp_ring �����ݻ��λ�����
 * \{
 
 * \section ʹ������--α����
 
#define MAX_RCV_LEN 64KB
char m_pTmpRcvBuff[MAX_RCV_LEN];

wns_tcp_ring_st *pRcvBuffer;

void OnRead(int nSessionIndex)
{
    int nLoopCount = 0;
    int nHaveRcvLen = 0;
    int nNeedRcvLen = 0;
    int nFreeLen = wns_tcp_ring_freecount(pRcvBuffer);
    if (nFreeLen <= 0)
    {
        TRACE("[TcpNode::OnRead] find the rcvBuff's  freecount <= 0\r\n");
        ManageRcvData(nSessionIndex);
        return;
    }

    do
    {
        nNeedRcvLen = min(MAX_RCV_LEN,nFreeLen);

        nHaveRcvLen = 0;
        nHaveRcvLen = recv(nsocket,m_pTmpRcvBuff,nNeedRcvLen,0);
        TRACE("----------->TcpNode onRead len = %d ------------->\r\n",nHaveRcvLen);
        if (nHaveRcvLen < 0)
        {
            if (errno != EWOULDBLOCK && errno != EINTR)
            {
                .....
            }

            return;
        }

        if (nHaveRcvLen == 0)
        {
            OnClose(nSessionIndex);
            return;
        }
        //����޶ȵؽ������ݷŵ�ѭ������
        wns_tcp_ring_enqueue(pRcvBuffer, m_pTmpRcvBuff,nHaveRcvLen);
        //����ѭ�����������
        ManageRcvData(nSessionIndex);

        nFreeLen = wns_tcp_ring_freecount(pRcvBuffer);

        nLoopCount++;
    }
    while ((nFreeLen>0) && (nHaveRcvLen==nNeedRcvLen) && nLoopCount<=100);

}

void ManageRcvData()
{
    int nDataLen =  wns_tcp_ring_datacount(pRcvBuffer);

    //��ȡһ���̶����ȵ�ͷ
    while (nDataLen >= SINFOR_PACK_HEAD_LEN)
    {
        // 1.Get a sinfor packet header
        wns_tcp_ring_peek(pRcvBuffer, m_pTmpRcvBuff,SINFOR_PACK_HEAD_LEN);
        
        stSinforPacketHead *pSinforPacket = (stSinforPacketHead*)m_pTmpRcvBuff;

        // 2.Check if recv all sinfor packet data
        int nPacketLen = SINFOR_PACK_HEAD_LEN+pSinforPacket->wDataLen;
        if (nDataLen < nPacketLen)
        {
            return;
        }

        //�յ�һ�����������ݰ�
        wns_tcp_ring_dequeue(pRcvBuffer, m_pTmpRcvBuff,nPacketLen);

        ����m_pTmpRcvBuff
        ......
        
        nDataLen =  wns_tcp_ring_datacount(pRcvBuffer);
    }
}
*/

#ifndef __LIBWNS_TCP_RING_H__
#define __LIBWNS_TCP_RING_H__

#include "libbase_type.h"
#include "libbase_config.h"

typedef struct h_tcp_ring_st h_tcp_ring_st;

/**
 * ��ָ���ڴ��ϴ������λ�����
 * \param name ����������
 * \param size ���������ȣ�����Ϊ2��N�η���ÿһ��Ԫ����Ҫһ������ṹ����˻������Ĵ�С���Ǽ򵥵�Ԫ�ش�С����Ԫ�ظ����������Դ�
 * \return �����������mem�����򷵻�NULL��size����2��N�η���
 *
 * chunk_ring �Ƕ������߶��������̰߳�ȫ��
 */
h_tcp_ring_st *h_tcp_ring_create(const char *name, size_t size);

/**
 * ����һ����״����
 *
 * ���뱣֤��û�г�����ӵĲ���ʱ����
 *
 * @param ring  ��״����ָ��
 *
 */
void h_tcp_ring_destroy(h_tcp_ring_st *r);

/**
 * ���һ��chunk
 * \param r ���λ�����
 * \param buffer ������ָ��
 * \param n �����ݳ���
 * \return
 *   - 0: �ɹ�
 *   - -ENOBUFS: �ռ䲻��
 */
int h_tcp_ring_enqueue(h_tcp_ring_st *r, const int8_t *buffer, size_t n);

/**
 * ��ȡһ�����Գ��ӵ�chunk, ���ǲ�����������
 * ע����ӻ���Ҫ�ܹ���������һ��chunk
 * \param r ���λ�����
 * \param buffer �����ݻ�����ָ��
 * \param n ���봫��chunk�������Ĵ�С
 * \return
 *   - 0: �ɹ�
 *   - -ENOENT:  û���㹻�Ŀռ������
 */
int h_tcp_ring_peek(h_tcp_ring_st *r, int8_t *buffer, size_t n);

/**
 * ����һ��chunk��ע����ӻ���Ҫ�ܹ���������һ��chunk
 * \param r ���λ�����
 * \param buffer �����ݻ�����ָ��
 * \param n ���봫��chunk�������Ĵ�С
 * \return
 *   - 0: �ɹ�
 *   - -ENOENT:  û���㹻�Ŀռ������
 */
int h_tcp_ring_dequeue(h_tcp_ring_st *r, int8_t *buffer, size_t n);



/**
* @brief ���ָ����С������
* @param   r   ���λ�����
* @param   n   ���ݴ�С
*
* @return 
* @remark null
* @see     
* @author lwj      @date 2012/11/12
**/
void h_tcp_ring_erase(h_tcp_ring_st *r, size_t n);

/**
* @brief ���ػ��λ����С
* @param   r   ���λ�����
*
* @return ���λ����С
* @remark null
* @see     
* @author lwj      @date 2012/11/12
**/
size_t h_tcp_ring_count(const h_tcp_ring_st *r);

/**
* @brief ���ػ��λ�����л����С
* @param   r   ���λ�����
*
* @return ���λ�����д�С
* @remark null
* @see     
* @author lwj      @date 2012/11/12
**/
size_t h_tcp_ring_freecount(const h_tcp_ring_st *r);

/**
* @brief ���ػ��λ�����ʹ�ÿռ��С
* @param   r   ���λ�����
*
* @return ���λ�����ʹ�ÿռ��С
* @remark null
* @see     
* @author lwj      @date 2012/11/12
**/
size_t h_tcp_ring_datacount(const h_tcp_ring_st *r);

/** \} */

#endif /* __LIBWNS_CHUNK_RING_H__ */


/* copyright see rte_atomic.h */
