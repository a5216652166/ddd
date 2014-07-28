#ifndef _LIBWNS_UTILS_
#define _LIBWNS_UTILS_

#include <stdint.h>

/*!
 * �ҵ�����ĳ�����ֵ���С��2��N�η�
 */
static inline uint32_t wns_power_of_2(uint32_t size)
{
    size--;
    size |= size >> 1;
    size |= size >> 2;
    size |= size >> 4;
    size |= size >> 8;
    size |= size >> 16;
    size++;

    return size;
}

#endif /* end of include guard: _LIBWNS_UTILS_ */
