/******************************************************************************
 * @author:     hyb
 * @date:       2011-03-05
 * @brief:      IPv4/IPv6 compatible interfaces.
 ******************************************************************************/

#ifndef __LIBWNS_IP_COMPATIBLE_H__
#define __LIBWNS_IP_COMPATIBLE_H__

#ifdef __KERNEL__ /* KERNEL COMPILE */

#include <linux/in.h>
#include <linux/in6.h>
#include <linux/types.h>
#include <linux/module.h>
#include <net/ipv6.h>

#else  /* APPLICATION COMPILE */

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "libbase_config.h"

typedef uint16_t __be16;
typedef uint32_t __be32;

#define __force

/**
 * ffz - find first zero bit in word
 * @word: The word to search
 *
 * Undefined if no zero exists, so code should check against ~0UL first.
 */
#if defined(SF_ARCH_I686) || defined(SF_ARCH_X86_64)
#ifdef SF_ARCH_I686
static inline unsigned long ffz(unsigned long word)
{
    asm("bsf %1,%0"
        : "=r" (word)
        : "r" (~word));
    return word;
}
#endif
#ifdef SF_ARCH_X86_64
# define ia64_popcnt(x)     __builtin_popcountl(x)
static inline unsigned long
ffz (unsigned long x)
{
    unsigned long result;

    result = ia64_popcnt(x & (~x - 1));
    return result;
}
#endif
#else
static inline unsigned long __ffs(unsigned long word)
{
    int num = 0;

    if (sizeof(word) == 8) {
        if ((word & 0xffffffff) == 0) {
            num += 32;
            word >>= num; /* 32, for no warm on 32bit word */
        }
    }
    if ((word & 0xffff) == 0) {
        num += 16;
        word >>= 16;
    }
    if ((word & 0xff) == 0) {
        num += 8;
        word >>= 8;
    }
    if ((word & 0xf) == 0) {
        num += 4;
        word >>= 4;
    }
    if ((word & 0x3) == 0) {
        num += 2;
        word >>= 2;
    }
    if ((word & 0x1) == 0)
        num += 1;
    return num;
}
#define ffz(x)  __ffs(~(x))
#endif


#endif /* END COMPILE COMPATIBLE */

#define HW_MACADDR_LEN          6

#define __ARRAY_SIZE(array) (sizeof((array))/sizeof((array)[0]))

#define MAX_IPV4_TEXTBUF_LEN    sizeof("255.255.255.255")

#define MAX_IPV6_TEXTBUF_LEN \
    sizeof("ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255")

#define MAX_RANGE_STRING_BUFF   128

#define MAX_IP_AND_MASK_LEN \
    (sizeof("ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255/ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff"))


#ifdef __cplusplus
extern "C"
{
#endif

#define __JHASH_GOLDEN_RATIO    0x9e3779b9

#define l3_jhash_mix(a, b, c) \
    { \
        a -= b; a -= c; a ^= (c>>13); \
        b -= c; b -= a; b ^= (a<<8); \
        c -= a; c -= b; c ^= (b>>13); \
        a -= b; a -= c; a ^= (c>>12);  \
        b -= c; b -= a; b ^= (a<<16); \
        c -= a; c -= b; c ^= (b>>5); \
        a -= b; a -= c; a ^= (c>>3);  \
        b -= c; b -= a; b ^= (a<<10); \
        c -= a; c -= b; c ^= (b>>15); \
    }

enum
{
    L3_IPV4_TYPE = AF_INET,
    L3_IPV6_TYPE = AF_INET6,
    L3_UNKNOWN_TYPE
};

/* Layer 3 ��ַ��ʽ����
 */
union __l3_addr
{
    uint32_t        all[4];
    __be32          ip6[4];

    struct in6_addr in6;
};

struct l3_addr_st
{
    union __l3_addr addr;
};


#define addr_all addr.all
#define addr_ip  addr.ip6[3]
#define addr_ip6 addr.ip6

#define addr_in  addr.in6.s6_addr32[3]
#define addr_in6 addr.in6


//��ipv6��ַ��ʽ�������MYSQL�� wzg
#ifndef NIPV6TOMYSQL
#define NIPV6TOMYSQL(ip)                \
    ntohl(ip.addr_all[0]),              \
    ntohl(ip.addr_all[1]),              \
    ntohl(ip.addr_all[2]),              \
    ntohl(ip.addr_all[3])
#endif


/* Layer 3��ַ��Χ�ṹ����
 *      ���ṹ����һ��IP��Χ������ "[,]"
*/
struct l3_range_st
{
    struct l3_addr_st start;
    struct l3_addr_st end;
};

/* MAC��ַ��ʽ����
*/
struct mac_addr_st
{
    uint8_t         ha[HW_MACADDR_LEN];
};


/* Bob Jenkins's��ϣ�㷨,v2.
*/
static __inline uint32_t
l3_jhash2(const uint32_t *k, uint32_t length, uint32_t initval)
{
    uint32_t a, b, c, len;

    a = b = __JHASH_GOLDEN_RATIO;
    c = initval;
    len = length;

    while (len >= 3)
    {
            a += k[0];
            b += k[1];
            c += k[2];
            l3_jhash_mix(a, b, c);
            k += 3;
            len -= 3;
    }

    c += length * 4;

    switch (len)
    {
    case 2 : b += k[1];
            /* fall through */
    case 1 : a += k[0];
            /* fall through */
    };

    l3_jhash_mix(a,b,c);

    return c;
}


/*
* A special ultra-optimized versions that knows they are hashing exactly
* 3, 2 or 1 word(s).
*/
static __inline uint32_t
l3_jhash_3words(uint32_t a, uint32_t b, uint32_t c, uint32_t initval)
{
    a += __JHASH_GOLDEN_RATIO;
    b += __JHASH_GOLDEN_RATIO;
    c += initval;

    l3_jhash_mix(a, b, c);

    return c;
}


static __inline uint32_t
l3_jhash_2words(uint32_t a, uint32_t b, uint32_t initval)
{
    return l3_jhash_3words(a, b, 0, initval);
}


static __inline uint32_t
l3_jhash_1word(uint32_t a, uint32_t initval)
{
    return l3_jhash_3words(a, 0, 0, initval);
}


#define L3_IPV4_MASK        (0xFFFF0000)
#define L3_IPV4_MARK        (0xFFBF0000)

/* ���ܣ����һ��Layer 3��ַ���������
 * ������
 *      @l3_addr: Layer 3��ַ����ĵ�ַ
 * ����ֵ��
 *      L3_IPV4_TYPE - IPv4
 *      L3_IPV6_TYPE - IPv6
 * ע��: ����rfc3513�涨����16λΪ0xFFBF0000�ĵ�ַΪ�Ƿ���ַ��
 *       �ֲ������ַ��������ipv4��ַ������


    An IPv6 multicast address is an identifier for a group of interfaces
    (typically on different nodes).  An interface may belong to any
    number of multicast groups.  Multicast addresses have the following
    format:

    |   8    |  4 |  4 |                  112 bits                   |
    +------ -+----+----+---------------------------------------------+
    |11111111|flgs|scop|                  group ID                   |
    +--------+----+----+---------------------------------------------+

    binary 11111111 at the start of the address identifies the
    address as being a multicast address.

                                    +-+-+-+-+
    flgs is a set of 4 flags:       |0|0|0|T|
                                    +-+-+-+-+

    The high-order 3 flags are reserved, and must be initialized
    to 0.

    T = 0 indicates a permanently-assigned ("well-known")
    multicast address, assigned by the Internet Assigned Number
    Authority (IANA).

    T = 1 indicates a non-permanently-assigned ("transient")
    multicast address.

    scop is a 4-bit multicast scope value used to limit the scope
    of the multicast group.  The values are:

    0  reserved
    1  interface-local scope
    2  link-local scope
    3  reserved
    4  admin-local scope
    5  site-local scope
    6  (unassigned)
    7  (unassigned)
    8  organization-local scope
    9  (unassigned)
    A  (unassigned)
    B  (unassigned)
    C  (unassigned)
    D  (unassigned)
    E  global scope
    F  reserved
*/

static __inline uint8_t
l3_addr_type(const struct l3_addr_st *l3_addr)
{
    __be32 st = l3_addr->addr_ip6[0];

    if ((st & htonl(L3_IPV4_MASK)) == htonl(L3_IPV4_MARK))
        return L3_IPV4_TYPE;
    else
        return L3_IPV6_TYPE;
}



/* ���ܣ����һ��Layer 3�����ַ���������
 * ������
 *      @l3_mask: Layer 3�����ַ����ĵ�ַ
 * ����ֵ��
 *      L3_IPV4_TYPE - IPv4
 *      L3_IPV6_TYPE - IPv6
*/
static __inline uint8_t
l3_mask_type(const struct l3_addr_st *l3_mask)
{
    return l3_addr_type(l3_mask);
}



/* ���ܣ��ж�һ��Lay 3��ַ�����Ƿ���IPv4����
 * ������
 *      @l3_addr: Lay 3��ַ����ĵ�ַ
 * ����ֵ����0 - ��IPv4����; 0 - ����IPv4����
*/
static __inline int
is_ipv4_addr(const struct l3_addr_st *l3_addr)
{
    return l3_addr_type(l3_addr) == L3_IPV4_TYPE;
}



/* ���ܣ��ж�һ��Layer 3��ַ�����Ƿ���IPv6����
 * ������
 *      @l3_addr: Layer 3��ַ����ĵ�ַ
 * ����ֵ����0 - ��IPv6����; 0 - ����IPv6����
*/
static __inline int
is_ipv6_addr(const struct l3_addr_st *l3_addr)
{
    return l3_addr_type(l3_addr) == L3_IPV6_TYPE;
}



/* ���ܣ���һ��Layer 3��ַ��������IPv4��ֵַ
 * ������
 *      @l3_addr: Layer 3��ַ����ĵ�ַ
 *      @addr: IPv4��ֵַ
 * ����ֵ��0 - �ɹ�; ��0 - ʧ��
*/
static __inline int
set_ipv4_addr(struct l3_addr_st *l3_addr, uint32_t addr)
{
    l3_addr->addr_in = addr;
    l3_addr->addr_ip6[0] = htonl(L3_IPV4_MARK);
    return 0;
}



/* ���ܣ���һ��Layer 3��ַ��������IPv4��ֵַ
 * ������
 *      @l3_addr: Layer 3��ַ����ĵ�ַ
 *      @in: IPv4��ַ����ĵ�ַ
 * ����ֵ��0 - �ɹ�; ��0 - ʧ��
 * ע��: ���ｫIPv4��ַ����ǿ��ת����__be32�����struct in_addr����ı�
 *       �����޸�����Ĵ���
*/
static __inline int
set_ipv4_addr2(struct l3_addr_st *l3_addr, const struct in_addr *in)
{
    l3_addr->addr_in = *(__be32 *)in;
    l3_addr->addr_ip6[0] = htonl(L3_IPV4_MARK);
    return 0;
}



/* ���ܣ��ж�һ��in6_addr�Ƿ�Ϸ������ܷ�תΪl3_addr_st
 * ������
 *      @in6: IPv6��ַ����ĵ�ַ
 * ����ֵ��0 - �Ƿ���1 - �Ϸ�
*/
static __inline int
is_in6_addr_valid(const struct in6_addr *in6)
{
    if ((in6->s6_addr32[0] & htonl(L3_IPV4_MASK)) == htonl(L3_IPV4_MARK))
        return 0;

    return 1;
}



/* ���ܣ���һ��Layer 3��ַ��������IPv6��ֵַ
 * ������
 *      @l3_addr: Layer 3��ַ����ĵ�ַ
 *      @in6: IPv6��ַ����ĵ�ַ
 * ����ֵ��0 - �ɹ�����0 - ʧ��
*/
static __inline int
set_ipv6_addr(struct l3_addr_st *l3_addr, const struct in6_addr *in6)
{
    if (!is_in6_addr_valid(in6))
        return -1;

    l3_addr->addr_in6 = *in6;
    return 0;
}


/* ����: ��in6_addr��ָ��ת��Ϊl3_addrָ��
 * ����:
 *      @in6: IPv6��ַ����ĵ�ַ
 * ����ֵ: l3_addrָ��
 */
static __inline struct l3_addr_st*
in6_addr_to_l3_addr(struct in6_addr *in6)
{
    if (!is_in6_addr_valid(in6))
        return NULL;

    return (struct l3_addr_st*)in6;
}



/* ���ܣ��ж�����IPv4��ַ�����Ƿ����
 * ������
 *      @a1: ָ��IPv4��ַ����֮һ
 *      @a2: ָ��IPv4��ַ����֮��
 * ����ֵ����0 - ���; 0 - �����
*/
static __inline int
l3_ipv4_addr_equal(const __be32 *a1, const __be32 *a2)
{
    return *a1 == *a2;
}



/* ���ܣ��ж�����IPv6��ַ�����Ƿ����
 * ������
 *      @a1: ָ��IPv6��ַ����֮һ
 *      @a2: ָ��IPv6��ַ����֮��
 * ����ֵ����0 - ���; 0 - �����
*/
static __inline int
l3_ipv6_addr_equal(const struct in6_addr *a1, const struct in6_addr *a2)
{
    return (((a1->s6_addr32[0] ^ a2->s6_addr32[0]) |
                (a1->s6_addr32[1] ^ a2->s6_addr32[1]) |
                (a1->s6_addr32[2] ^ a2->s6_addr32[2]) |
                (a1->s6_addr32[3] ^ a2->s6_addr32[3])) == 0);
}



/* ���ܣ��ж�����Layer 3��ַ�����Ƿ����
 * ������
 *      @l3_addr1: ָ��Layer 3��ַ����֮һ
 *      @l3_addr2: ָ��Layer 3��ַ����֮��
 * ����ֵ����0 - ���; 0 - �����
*/
static __inline int
l3_addr_equal(const struct l3_addr_st *l3_addr1,
    const struct l3_addr_st *l3_addr2)
{
    if (l3_addr_type(l3_addr1) != l3_addr_type(l3_addr2))
            return 0;

    switch(l3_addr_type(l3_addr1))
    {
    case L3_IPV4_TYPE:
            return l3_ipv4_addr_equal(&l3_addr1->addr_in,
                    &l3_addr2->addr_in);

    case L3_IPV6_TYPE:
            return l3_ipv6_addr_equal(&l3_addr1->addr_in6,
                    &l3_addr2->addr_in6);

    default:
            return 0;
    }
}



/* ���ܣ�����Layer 3��ַ�������һ����ϣ��ֵ
 * ������
 *      @l3_addr: ָ��Layer 3��ַ����
 *      @rnd�������
 * ����ֵ��32λ��ֵ
*/
static __inline uint32_t
l3_addr_hash(const struct l3_addr_st *l3_addr, uint32_t rnd)
{
    uint32_t n;

    if (is_ipv6_addr(l3_addr))
    {
        n = sizeof(struct in6_addr);
        return l3_jhash2((uint32_t*)l3_addr->addr_ip6, n/sizeof(uint32_t), rnd);
    }

    n = sizeof(struct in_addr);
    return l3_jhash2((uint32_t*)&l3_addr->addr_ip, n/sizeof(uint32_t), rnd);
}



/* ���ܣ�����Layer 3��ַ����Ͷ˿ڲ���һ����ϣ��ֵ
 * ������
 *      @l3_addr: ָ��Layer 3��ַ����
 *      @port: �˿ں�
 *      @rnd�������
 * ����ֵ��32λ��ֵ
*/
static __inline uint32_t
l3_hash_2tuple(const struct l3_addr_st *l3_addr,
    uint16_t port, uint32_t rnd)
{
    uint32_t n;

    if (is_ipv6_addr(l3_addr))
    {
        n = sizeof(struct in6_addr);
        return l3_jhash_2words(
            l3_jhash2((uint32_t*)l3_addr->addr_ip6, n/sizeof(uint32_t), rnd),
            (__force uint32_t)port, rnd);
    }

    return l3_jhash_2words((__force uint32_t)l3_addr->addr_ip,
        (__force uint32_t)port, rnd);
}



/* ���ܣ�����Layer 3��ַ����Ͷ˿ں�4��Э��Ų���һ����ϣ��ֵ
 * ������
 *      @l3_addr: ָ��Layer 3��ַ����
 *      @port: �˿ں�
 *      @proto: 4��Э���
 *      @rnd�������
 * ����ֵ��32λ��ֵ
*/
static __inline uint32_t
l3_hash_3tuple(const struct l3_addr_st *l3_addr,
    uint16_t port, uint8_t proto, uint32_t rnd)
{
    uint32_t n;

    if (is_ipv6_addr(l3_addr))
    {
        n = sizeof(struct in6_addr);
        return l3_jhash_3words(
            l3_jhash2((uint32_t*)l3_addr->addr_ip6, n/sizeof(uint32_t), rnd),
            (__force uint32_t)port, (__force uint32_t)proto, rnd);
    }

    return l3_jhash_3words((__force uint32_t)l3_addr->addr_ip,
        (__force uint32_t)port, (__force uint32_t)proto, rnd);
}



/* ���ܣ�������Ԫ�����һ����ϣ��ֵ
 * ������
 *      @l3_saddr: ָ��Layer 3Դ��ַ����
 *      @l3_daddr: ָ��Layer 3Ŀ���ַ����
 *      @sport: Դ�˿ں�
 *      @dport: Ŀ�Ķ˿ں�
 *      @rnd�������
 * ����ֵ��32λ��ֵ
*/
static __inline uint32_t
l3_hash_4tuple(const struct l3_addr_st *l3_saddr,
    const struct l3_addr_st *l3_daddr, uint16_t sport,
    uint16_t dport, uint32_t rnd)
{
    uint8_t t1, t2;
    uint32_t n;

    t1 = l3_addr_type(l3_saddr);
    t2 = l3_addr_type(l3_daddr);

    if (t1 != t2)
        return 0;

    if (L3_IPV6_TYPE == t1)
    {
        n = sizeof(struct in6_addr);
        return l3_jhash_3words(
            l3_jhash2((uint32_t*)l3_saddr->addr_ip6, n/sizeof(uint32_t), rnd),
            l3_jhash2((uint32_t*)l3_daddr->addr_ip6, n/sizeof(uint32_t), rnd),
            ((sport) << 16) | dport, rnd);
    }

    return l3_jhash_3words((__force uint32_t)l3_saddr->addr_ip,
        (__force uint32_t)l3_daddr->addr_ip,
        ((sport) << 16) | dport, rnd);
}



/* ���ܣ�������Ԫ�����һ����ϣ��ֵ
 * ������
 *      @l3_saddr: ָ��Layer 3Դ��ַ����
 *      @l3_daddr: ָ��Layer 3Ŀ���ַ����
 *      @sport: Դ�˿ں�
 *      @dport: Ŀ�Ķ˿ں�
 *      @proto: 4��Э���
 *      @rnd�������
 * ����ֵ��32λ��ֵ
*/
static __inline uint32_t
l3_hash_5tuple(const struct l3_addr_st *l3_saddr,
    const struct l3_addr_st *l3_daddr, uint16_t sport,
    uint16_t dport, uint8_t proto, uint32_t rnd)
{
    uint8_t t1, t2;
    uint32_t n;

    t1 = l3_addr_type(l3_saddr);
    t2 = l3_addr_type(l3_daddr);

    if (t1 != t2)
        return 0;

    if (L3_IPV6_TYPE == t1)
    {
        n = sizeof(struct in6_addr);
        return l3_jhash_3words(
            l3_jhash2((uint32_t*)l3_saddr->addr_ip6, n/sizeof(uint32_t), rnd),
            l3_jhash2((uint32_t*)l3_daddr->addr_ip6, n/sizeof(uint32_t), rnd),
            ((sport) << 16) | dport, rnd ^ proto);
    }

    return l3_jhash_3words((__force uint32_t)l3_saddr->addr_ip,
        (__force uint32_t)l3_daddr->addr_ip,
        ((sport) << 16) | dport, rnd ^ proto);
}



/* ���ܣ�����IPv4��ַ�������һ��in_addr
 * ������
 *      @l3_addr: ָ��Layer 3��ַ����
 * ����ֵ��32λ��ֵ
*/
static __inline struct in_addr*
ipv4_to_in_addr(const struct l3_addr_st *l3_addr)
{
    if (!is_ipv4_addr(l3_addr))
        return NULL;

    return (struct in_addr*)(&l3_addr->addr_ip);
}



/* ���ܣ�����IPv6��ַ�������һ��in6_addr
 * ������
 *      @l3_addr: ָ��Layer 3��ַ����
 * ����ֵ��32λ��ֵ
*/
static __inline struct in6_addr*
ipv6_to_in6_addr(const struct l3_addr_st *l3_addr)
{
    if (!is_ipv6_addr(l3_addr))
        return NULL;

    return (struct in6_addr*)(l3_addr->addr_ip6);
}



/* ���ܣ��Ƚ�����Layer 3��ַ��ǰ׺�����Ƿ����
 * ������
 *      @l3_addr1: ָ��Layer 3��ַ����
 *      @l3_addr2: ָ��Layer 3��ַ����
 *      @prefix_len��ǰԵλ��
 * ����ֵ����0 - ��ȣ�0 - �����
*/
extern int
l3_addr_prefix_equal(const struct l3_addr_st *l3_addr1,
    const struct l3_addr_st *l3_addr2, uint32_t prefix_len);



/* ���ܣ��Ƚ�����IPv4����Layer 3��ַ��������Ƿ����
 * ������
 *      @ipv4_addr1: ָ��IPv4����Layer 3��ַ����
 *      @ipv4_addr2: ָ��IPv4����Layer 3��ַ����
 *      @netmask���������������Layer 3��ַ����
 * ����ֵ����0 - ���; 0 - ����Ȼ��д���
*/
extern int
ipv4_addr_mask_equal(const struct l3_addr_st *ipv4_addr1,
    const struct l3_addr_st *ipv4_addr2, const struct l3_addr_st *netmask);



/* ���ܣ��Ƚ�����Layer 3��ַ�Ĵ�С
 * ������
 *      @l3_addr1: ָ��Layer 3��ַ����
 *      @l3_addr2: ָ��Layer 3��ַ����
 * ����ֵ��0 - ���; -1 - С��; 1 - ����; -2 - ��ַ���ʹ���;
 *          3 - l3_addr1��ipv6��l3_addr2��ipv4����
 *          -3 - l3_addr1��ipv4��l3_addr2��ipv6����
*/
extern int
l3_addr_cmp(const struct l3_addr_st *l3_addr1, const struct l3_addr_st *l3_addr2);



/* ��Layer 3��ַ�������ֽ���ת�������ֽ���
 * ����:
 *      @l3_net_addr: �����ֽ����Layer 3��ַ
 *      @l3_host_addr: ���ز����������ֽ����Layer 3��ַ
 * ����ֵ: 0 - ת���ɹ�
 *          -1 - û�пռ�洢���ز���
 *          -2 - �Ƿ��ĵ�ַ����
 *          -3 - ����ת���ɺϷ���IPv6��ַ
 */
extern int
l3_addr_ntoh(const struct l3_addr_st *l3_net_addr, struct l3_addr_st *l3_host_addr);



/* ��Layer 3��ַ�������ֽ���ת�������ֽ���
 * ����:
 *      @l3_addr: ��Ҫ����ת����Layer 3��ַ,����ת���Ľ��
 * ����ֵ: 0 - ת���ɹ�
 *          -1 - û�пռ�洢���ز���
 *          -2 - �Ƿ��ĵ�ַ����
 *          -3 - ����ת���ɺϷ���IPv6��ַ
 */
extern int
l3_addr_ntoh2(struct l3_addr_st *l3_addr);


#if 0
/* ���ܣ��Ƚ������������Layer 3��ַ�Ĵ�С
 * ������
 *      @l3_addr1: ָ��Layer 3�������ַ����
 *      @l3_addr2: ָ��Layer 3�������ַ����
 * ����ֵ��0 - ���; -1 - С��; 1 - ����; -2 - ��ַ���ʹ���;
 *          3 - l3_addr1��ipv6��l3_addr2��ipv4����
 *          -3 - l3_addr1��ipv4��l3_addr2��ipv6����
*/
extern int
l3_host_addr_cmp(const struct l3_addr_st *l3_host_addr1,
    const struct l3_addr_st *l3_host_addr2);



typedef int (*addr_cmp_fn)(const struct l3_addr_st *,
    const struct l3_addr_st *);
#endif


/* ���ܣ���һ������ĵ�ַ��Χ�����н��ж��ַ�����
 *      �жϸ����ĵ�ַ�Ƿ��ڵ�ַ��Χ��
 *      ����������ȽϽ��в���
 * ������
 *      @l3_addr: ָ��Layer 3�������ַ����
 *      @l3_range_ary: ��ַ��Χ������
 * ����ֵ��0 ���ڷ�Χ�ڣ�1 �ڷ�Χ��
*/
extern int
l3_addr_binary_search(const struct l3_addr_st *l3_addr,
    const struct l3_range_st l3_range_ary[],
    unsigned int size);



/* ���ܣ���һ������ĵ�ַ��Χ�����н��ж��ַ�����
 *      �жϸ����ĵ�ַ�Ƿ��ڵ�ַ��Χ��
 *      ����������ȽϽ��в���
 * ������
 *      @l3_addr: ָ��Layer 3�������ַ����
 *      @l3_range_ary: ��ַ��Χ������
 * ����ֵ��0 ���ڷ�Χ�ڣ�1 �ڷ�Χ��
*/
extern int
l3_net_addr_binary_search(const struct l3_addr_st *l3_addr,
    const struct l3_range_st l3_range_ary[],
    unsigned int size);



/* ���ܣ���һ��IPv4���͵�ַת��ΪIPv6֮IPv4ӳ���ַ
 * ������
 *      @l3_addr: ָ��Ҫת����Layer 3��ַ����
 * ����ֵ��0 - �ɹ�; <0 - ʧ�ܣ�ԭ��ַ������IPv4����
*/
extern int
ipv4_to_ipv6_mapping(struct l3_addr_st *l3_addr);



/* ���ܣ��ж�һ��Layer 3��ַ�Ƿ���IPv6֮IPv4ӳ���ַ
 * ������
 *      @l3_addr: ָ��Ҫ�жϵ�Layer 3��ַ����
 * ����ֵ����0 - ��ӳ���ַ; 0 - ����ӳ���ַ
*/
extern int
is_ipv6_addr_mapping(struct l3_addr_st *l3_addr);



/* ���ܣ���һ��IPv4���͵�ַת��ΪIPv6֮IPv4���ݵ�ַ
 * ������
 *      @l3_addr: ָ��Ҫת����Layer 3��ַ����
 * ����ֵ��0 - �ɹ�; <0 - ʧ�ܣ�ԭ��ַ������IPv4����
*/
extern int
ipv4_to_ipv6_compatible(struct l3_addr_st *l3_addr);



/* ���ܣ��ж�һ��Layer 3��ַ�Ƿ���IPv6֮IPv4���ݵ�ַ
 * ������
 *      @l3_addr: ָ��Ҫ�жϵ�Layer 3��ַ����
 * ����ֵ����0 - �Ǽ��ݵ�ַ; 0 - ���Ǽ��ݵ�ַ
*/
extern int
is_ipv6_addr_compatible(struct l3_addr_st *l3_addr);



/* ����: �ж�һ��Layer 3��ַ�Ƿ��Ƕಥ��ַ
 * ������
 *      @l3_addr: ָ��Ҫ�жϵ�Layer 3��ַ����
 * ����ֵ����0 - �Ƕಥ��ַ; 0 - ���Ƕಥ��ַ
*/
static __inline int
is_l3_addr_multicast(struct l3_addr_st *l3_addr)
{
    if (is_ipv6_addr(l3_addr))
        return (l3_addr->addr_ip6[0] & htonl(0xFF000000)) == htonl(0xFF000000);
    else if (is_ipv4_addr(l3_addr))
        return (l3_addr->addr_ip & htonl(0xF0000000)) == htonl(0xE0000000);

    return 0;
}



/* ����: �ж�һ��Layer 3��ַ�Ƿ��ǻ��ص�ַ
 * ������
 *      @l3_addr: ָ��Ҫ�жϵ�Layer 3��ַ����
 * ����ֵ����0 - �ǻ��ص�ַ; 0 - ���ǻ��ص�ַ
*/
static __inline int
is_l3_addr_loopback(struct l3_addr_st *l3_addr)
{
    if (is_ipv6_addr(l3_addr))
        return ((l3_addr->addr_ip6[0] | l3_addr->addr_ip6[1] |
            l3_addr->addr_ip6[2] | (l3_addr->addr_ip6[3] ^ htonl(1))) == 0);
    else if (is_ipv4_addr(l3_addr))
        return (l3_addr->addr_ip & htonl(0xFF000000)) == htonl(0x7F000000);

    return 0;
}


/* ����: �ж�һ��IPv6��ַ�Ƿ���Link Local��ַ
 * ������
 *      @l3_addr: ָ��Ҫ�жϵ�Layer 3��ַ����
 * ����ֵ����0 - ��Link Local��ַ; 0 - ����Link Local��ַ
*/
static __inline int
is_link_local_ipv6_addr(struct l3_addr_st *l3_addr)
{
    if (is_ipv6_addr(l3_addr) &&
        (l3_addr->addr_ip6[0] == htonl(0xFE800000)) &&
        (l3_addr->addr_ip6[1] == htonl(0x0)))
        return 1;
    return 0;
}



/* ���ܣ���һ��IPv6���͵�IPv4 ����/ӳ���ַת��Ϊ��Ӧ��IPv4��ַ
 * ������
 *      @l3_addr: ָ��Ҫת����Layer 3��ַ����
 * ����ֵ��0 - ת���ɹ�; <0 - ʧ�ܣ�ԭ��ַ���Ǽ���/ӳ���ַ
*/
extern int
ipv6_to_ipv4_special(struct l3_addr_st *l3_addr);



/* ���ܣ��ж�һ��l3��ַ�Ƿ�ȫ0
 * ������
 *      @l3_addr: ָ��Ҫ�жϵ�Layer 3��ַ����
 * ����ֵ��0 ����ȫ0��ַ; ��0 ��ȫ0��ַ;
*/
extern int
is_l3_addr_zero(const struct l3_addr_st *l3_addr);



/* ���ܣ��ж�һ��l3��ַ�Ƿ�ȫ1
 * ������
 *      @l3_addr: ָ��Ҫ�жϵ�Layer 3��ַ����
 * ����ֵ��0 ����ȫ1��ַ; ��0 ��ȫ1��ַ;
*/
extern int
is_l3_addr_all_set(const struct l3_addr_st *l3_addr);



/* ���ܣ��ж�һ��l3��ַ�Ƿ�ȫ0
 * ������
 *      @l3_addr: ָ��Ҫ�жϵ�Layer 3��ַ����
 * ����ֵ��0 ����ȫ0��ַ; ��0 ��ȫ0��ַ;
*/
static __inline const char*
l3_addr_to_binary(const struct l3_addr_st *l3_addr)
{
    if (!l3_addr)
        return NULL;

    if (is_ipv4_addr(l3_addr))
        return (const char*)(&l3_addr->addr_ip);

    if (is_ipv6_addr(l3_addr))
        return (const char*)(l3_addr->addr_ip6);

    return NULL;
}



/* ���ܣ��ж�һ��Layer 3��ַ�Ƿ���ĳ����Χ֮��
 * ������
 *      @l3_addr: ָ��Ҫ�жϵ�Layer 3��ַ����
 *      @l3_range: ָ�����Χ�Ķ���
 * ����ֵ��0 - �������Χ��
 *�������� 1 - û�ڷ�Χ֮�ڣ����ڸ߽߱�
 *������  -1 - û�ڷ�Χ֮�ڣ�С�ڵͱ߽�
 *��������-2 - ��ַ����������
*/
extern int
l3_addr_in_range(const struct l3_addr_st *l3_addr,
    const struct l3_range_st *l3_range);



/* ���ܣ��ж�һ��Layer 3��ַ�Ƿ���ĳ����Χ֮��
 * ������
 *      @l3_addr: ָ��Ҫ�жϵ�Layer 3��ַ����
 *      @p_low: ��Χ�ĵͱ߽�
 *      @p_hi: ��Χ�ĸ߽߱�
 * ����ֵ��0 - �������Χ��
 *�������� 1 - û�ڷ�Χ֮�ڣ�����upper�߽�
 *������  -1 - û�ڷ�Χ֮�ڣ�С��lower�߽�
 *��������-2 - ��ַ����������
*/
extern int
l3_addr_in_range2(const struct l3_addr_st *l3_addr,
    const struct l3_addr_st *p_low, const struct l3_addr_st *p_hi);



/* ���ܣ���һ��Layer 3��ַ��ʽ����һ���ɶ����ַ���
 * ������
 *      @l3_addr: ָ��Ҫ��ʽ����Layer 3��ַ����
 *      @buf: ����ַ����Ļ������׵�ַ
 *      @size: �������ĳ���
 * ����ֵ��>0 - �ַ����ĳ���
 *�������� -1 - ʧ�ܣ�����������̫С
 *�������� -2 - ʧ�ܣ�δ֪�ĵ�ַ����
*/
extern int
l3_addr_to_string(const struct l3_addr_st *l3_addr, char buf[], uint32_t size);



/* ���ܣ����ն������Layer 3��ַ�Ŀɶ���ʽ
 * ������
 *      @l3_addr: ָ��Ҫ�����Layer 3��ַ����
 * ����ֵ����
*/
extern void
print_l3_addr(const struct l3_addr_st *l3_addr);



/* ���ܣ���һ��Layer 3�����ַ��ʽ����һ���ɶ����ַ���
 * ������
 *      @l3_addr: ָ��Ҫ��ʽ����Layer 3�����ַ����
 *      @buf: ����ַ����Ļ������׵�ַ
 *      @size: �������ĳ���
 * ����ֵ��>0 - �ַ����ĳ���
 *�������� -1 - ʧ�ܣ�����������̫С
 *�������� -2 - ʧ�ܣ�δ֪�ĵ�ַ����
*/
extern int
l3_mask_to_string(const struct l3_addr_st *l3_mask, char buf[], uint32_t size);


/* ���ܣ����ն������Layer 3�����ַ�Ŀɶ���ʽ
 * ������
 *      @l3_mask: ָ��Ҫ�����Layer 3�����ַ����
 * ����ֵ����
*/
extern void
print_l3_mask(const struct l3_addr_st *l3_mask);



/* ���ܣ��������ǰ׺��ʽת����ipv4��ַ��ʽ
 * ������
 *      @prefix_len: ǰ׺��ʽ������
 *      @mask: ָ��Ҫ�����Layer 3�����ַ����
 * ����ֵ��0��ʾת���ɹ�����0��ʾת��ʧ��
*/
extern int
get_ipv4_mask(long prefix_len, struct l3_addr_st *mask);



/* ���ܣ��������ǰ׺��ʽת����ipv4��ַ��ʽ
 * ������
 *      @prefix_len: ǰ׺��ʽ������
 *      @mask: ָ��Ҫ�����Layer 3�����ַ����
 * ����ֵ��0��ʾת���ɹ�����0��ʾת��ʧ��
*/
extern int
get_ipv6_mask(long prefix_len, struct l3_addr_st *mask);



/* ���ܣ�����ַ��ʽ������ת����ǰ׺��ʽ
 * ������
 *      @mask: Layer 3�����ַ����
 *      @prefix_len: �������ǰ׺��ʽ������
 * ����ֵ��0��ʾת���ɹ�����0��ʾת��ʧ��
*/
extern int
get_l3_mask_prefix(struct l3_addr_st *mask, unsigned long *prefix_len);



/* ���ܣ���һ���ɶ����ı��ַ�����ַת����һ��Layer 3��ַ����
 * ������
 *      @src: Դ�ַ�����������:"192.168.1.1", "::" ...
 *      @dst: Ŀ��Layer 3��ַ����ĵ�ַ
 * ����ֵ��0 - �ɹ�; <0 - ʧ�ܣ��ַ�����ʽ����
*/
extern int
string_to_l3_addr(const char *src, struct l3_addr_st *dst);



/* ���ܣ����һ���ɶ����ı��ַ�����ַ����
 * ������
 *      @str: �ַ�����������:"192.168.1.1", "::" ...
 * ����ֵ��L3_IPV4_TYPE - IPv4��ַ
 *      �� L3_IPV6_TYPE - IPv6��ַ
 *         L3_UNKNOWN_TYPE - δ֪���ַ�������
*/
extern uint8_t
l3_string_type(const char *str);



/* ���ܣ�Layer 3��ַ�Ŀɶ�ֵ����1
 * ������
 *      @l3_addr: ָ��Ҫ������Layer 3��ַ����
 * ����ֵ��0 - �ɹ�; -1 - �����Ѿ������ֵ��; -2 - δ֪��ַ����
*/
extern int
l3_addr_inc(struct l3_addr_st *l3_addr);



/* ���ܣ�Layer 3��ַ�Ŀɶ�ֵ��ȥ1
 * ������
 *      @l3_addr: ָ��Ҫ�ݼ���Layer 3��ַ����
 * ����ֵ��0 - �ɹ�; -1 - �����Ѿ�����Сֵ��; -2 - δ֪��ַ����
*/
extern int
l3_addr_dec(struct l3_addr_st *l3_addr);



/* ���ܣ��ж�Layer 3��ַ1�Ƿ��Layer 3��ַ1С1
 * ������
 *      @l3_addr1: �����жϵĵ�ַ1
 *      @l3_addr2: �����жϵĵ�ַ2
 * ����ֵ�� 1 - Layer 3��ַ1��Layer 3��ַ1С1
 *          0 - Layer 3��ַ1û�б�Layer 3��ַ1С1
 *          -1 - �����Ƿ�
 *          -2 - Layer 3��ַ���Ͳ�ͬ
*/
extern int
is_l3_addr_close_to(const struct l3_addr_st *l3_addr1,
    const struct l3_addr_st *l3_addr2);



/* ���ܣ���������Layer 3��ַ��������һ����ַ��Χ�ṹ��
 * ������
 *      @l3_range��ָ��Ҫ���õĵ�ַ��Χ�ṹ��
 *      @l3_addr_low����ַ��Χ�ĵͱ߽�
 *      @l3_addr_hi����ַ��Χ�ĸ߽߱�
 * ����ֵ��0 - �ɹ�; -1 - ��ַ���Ͳ�ƥ��; -2 - ��Χ��������ȷ
*/
extern int
set_l3_range(struct l3_range_st *l3_range, const struct l3_addr_st *l3_addr_low,
    const struct l3_addr_st *l3_addr_hi);



/* ���ܣ���һ����ַ��Χ�ṹ��ת��Ϊ�ɶ����ı���ʽ
 * ������
 *      @l3_range��ָ��Ҫת���ĵ�ַ��Χ�ṹ��
 *      @buf������ı����Ļ�����
 *      @size���������ĳ���
 * ����ֵ��>0 - �ɹ����ַ����ĳ���; -1 - ʧ��,����������̫С; -2 - δ֪�ĵ�ַ����
*/
extern int
l3_range_to_string(const struct l3_range_st *l3_range, char buf[],
    uint32_t size);



/* ���ܣ����һ���ַ����Ƿ���һ���Ƿ���IPv4/IPv6��ַ��
 * ������
 *      @szip��ָ��Ҫ�����ַ���
 * ����ֵ����0 - �Ƿ����ַ���; 0 - �Ϸ����ַ���
*/
static __inline int
is_invalid_ip(const char *szip)
{
    struct l3_addr_st l3_addr;

    if (string_to_l3_addr(szip, &l3_addr) != 0)
            return 1;

    return 0;
}



/* ���ܣ����һ���ַ����Ƿ���һ���Ƿ���IPv4����
 * ������
 *      @szmask��ָ��Ҫ�����ַ���
 * ����ֵ����0 - �Ƿ��������ַ���; 0 - �Ϸ��������ַ���
*/
static __inline int
is_invalid_v4_mask(const char *szmask)
{
    uint32_t u_mask_not;
    struct l3_addr_st netmask;

    if (string_to_l3_addr(szmask, &netmask) != 0 ||
            !is_ipv4_addr(&netmask))
    {
            return 1;
    }

    u_mask_not = ~ntohl(netmask.addr_ip);
    if (u_mask_not & (u_mask_not + 1))
            return 1;

    return 0;
}



/* ���ܣ����һ��l3��ַ�Ƿ���һ���Ƿ�������
 * ������
 *      @mask��ָ��Ҫ����l3��ַ
 * ����ֵ��0 - �Ƿ��������ַ���; ��0 - �Ϸ��������ַ���
*/
extern int
is_l3_mask_valid(const struct l3_addr_st *mask);



/* ���ܣ���һ���ַ�����ʽ�ķ�Χ����ת��Ϊһ����ַ��Χ�ṹ�����
 * ������
 *      @str��������Χ���ַ���,��ʽ����:
 *              ���� 1  (1) 192.168.0.0
 *                      (2) ::2
 *              ���� 2  (3) 192.168.0.0/16
 *                      (4) ::/16
 *              ���� 3  (5) 192.168.0.0/255.255.255.0
 *                      (6) ff::/ffff:ffff:ff00::
 *              ���� 4  (7) 192.168.0.0-192.168.255.255
 *                      (8) ::2-::ff
 *      @l3_range����Χ�ṹ�����ĵ�ַ
 * ����ֵ��
 *        1: ipv4 ����1
 *        2: ipv6 ����1
 *        3: ipv4 ����2
 *        4: ipv6 ����2
 *        5: ipv4 ����3
 *        6: ipv6 ����3
 *        7: ipv4 ����4
 *        8: ipv6 ����4
 *        ����0���ɹ�
 *        -1���ַ������ȹ���
 *        -2���޷�����������(���ᷢ��)
 *        -3�����ߵͱ߽��ַת��ΪLayer 3���������ַ��ʽ���ԡ�����1.
 *        -4���ͱ߽�͸߽߱�ĵ�ַ���Ͳ�һ�£�[IPv4, IPv6]? ����1.
 *        -5���ͱ߽�͸߽߱�Ĵ�С����. ����1.
 *        -6��ǰ׺��������(192.168.0.1/33) ����2.
 *        -7����IPת��ΪLayer 3�������(192.168./24) ����2.
 *        -8����IP/����ת��ΪLayer 3�������. ����3.
 *        -9��IP���������Ͳ�ƥ��. ����3.
 *��������-10:�Ƿ�������. ����3.
*/
extern int
l3_string_to_range(const char *str, struct l3_range_st *l3_range);



/* ����: �Ƚ�������Χ�Ƿ���ͬ
 * ����:
 *      @range1: ָ��Ҫ�Ƚϵĵ�ַ��Χ�ṹ����
 *      @range2: ָ��Ҫ�Ƚϵĵ�ַ��Χ�ṹ����
 * ����ֵ: 1 - ���; 0 - �����
 */
extern int
is_l3_range_equal(const struct l3_range_st *range1,  const struct l3_range_st *range2);



/* ���ܣ���һ���ɶ����ı��ַ�����ַת����һ��Layer 3�����ַ����
 * ������
 *      @src: Դ�ַ�����������:"255.255.255.0", "FF:FF:FF::" ...
 *      @dst: Ŀ��Layer 3�����ַ����ĵ�ַ
 * ����ֵ��0 - �ɹ�; -1 - ʧ�ܣ��ַ�����ʽ����
*/
extern int
string_to_l3_mask(const char *src, struct l3_addr_st *dst);



/* ����: ��ȡһ��������ʽ�ķ�ΧIP������
 * ������
 *      @str��������Χ���ַ���,��ʽ����:
 *              ���� 1  (1) 192.168.0.0/16
 *                      (2) ::/16
 *              ���� 2  (3) 192.168.0.0/255.255.255.0
 *                      (4) ff::/ffff:ffff:ff::
 *      @mask�����뱣���ַ
 * ����ֵ��
 *         0: �ɹ�
 *        -1: ��֧�ֵ��ַ�����ʽ
 *        -2: �����ʾ�ַ�����ʽ����
 *        -3: IP�ַ�����ʽ����
 *        -4: ���뷶Χ�����д���
 *        -5: ����Ϊ��Чָ�����
 */
extern int
get_l3_string_mask(const char *str, struct l3_addr_st *mask);



/*  ����: l3_addr_st����IP��ַ������������
 *  ����:
 *          @l3_addr: IP��ַ
 *          @l3_mask: ����
 *          @result: �����֮��Ľ��
 *  ����ֵ:
 *          NULL - ʧ�ܣ���NULL��ַ - �ɹ��������ĵ�ַ
 */
extern struct l3_addr_st *
l3_addr_and_mask(const struct l3_addr_st *l3_addr, const struct l3_addr_st *l3_mask,
                struct l3_addr_st *result);



/* ���ܣ���һ��l3_range_st���鰴��ʼip�Ĵ�С��������, �κ�ipv4��ַС���κ�ipv6��ַ
 * ������
 *      @l3_range_ary: ��Ҫ�����l3_range_st���飬�洢���ؽ��
 *      @size: l3_range_ary�е�Ԫ�ظ���
 *      @dir: ������LOW_TO_HIGH: ��С�������У�HIGH_TO_LOW: �Ӵ�С����
 * ����ֵ�� 0 - �ɹ�;
 *          -1 - range�а�������ĵ�ַ����
*/
enum
{
    LOW_TO_HIGH,
    HIGH_TO_LOW
};

extern int
l3_range_sort(struct l3_range_st l3_range_ary[], unsigned int size, int dir);



/* ���ܣ�����l3_range_st���飬�Ȱ���ʼip�Ĵ�С�������򣬴�С�������У�
 *       Ȼ��ȥ���ظ�range���ϲ�����range
 * ������
 *      @l3_range_ary: ��Ҫ�����l3_range_st���飬�洢���ؽ��
 *      @psize: l3_range_ary�е�Ԫ�ظ������洢������size
 * ����ֵ�� 0 - �ɹ�;
 *          -1 - range�а�������ĵ�ַ����
 *          -2 - range��startС��end
*/
extern int
l3_range_trim(struct l3_range_st l3_range_ary[], unsigned int* psize);



#ifdef __cplusplus
}
#endif

#endif  /* __LIBWNS_IP_COMPATIBLE_H__ */
