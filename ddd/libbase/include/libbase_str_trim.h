/**
 * @file str_trim.h
 * @brief string trim
 * @author xww
 * @date 2009/8/25
 */

#ifndef STR_TRIM_H
#define STR_TRIM_H


#include <sys/cdefs.h>

__BEGIN_DECLS

/**
 * �ü���ǰ��ĵ�"\r\n\t "��no move
 * @param delim ���Ϊ�գ���Ĭ��Ϊ"\r\n\t "
 * @return �ü����ָ�룬���ܴ��ڵ���s
 */
static inline char* str_trim_left(char* s, const char* delim)
{
    char* left = s;
    if (s==0 || *s==0)
        return s;
    if (delim == 0)
        delim = "\r\n\t ";
    while (*left && strchr(delim, *left))
        left++;
    return left;
}

/**
 * �ü���ǰ��ĵ�"\r\n\t "��no move
 * @param delim ���Ϊ�գ���Ĭ��Ϊ"\r\n\t "
 * @return �ü����ָ�룬����s
 */
static inline char* str_trim_right(char* s, const char* delim)
{
    char* right = 0;

    if (s==0 || *s==0)
        return s;
    if (delim == 0)
        delim = "\r\n\t ";

    right = s + strlen(s) - 1;

    while (right!=s && strchr(delim, *right))
        right--;
    *(right+1) = 0;
    return s;
}

/**
 * �ü���ǰ��ĵ�"\r\n\t "��no move
 * @param delim ���Ϊ�գ���Ĭ��Ϊ"\r\n\t "
 * @return �ü����ָ�룬���ܴ��ڵ���s
 */
static inline char* str_trim(char* s, const char* delim)
{
    char* left = str_trim_left(s, delim);
    return str_trim_right(left, delim);
}


__END_DECLS
#endif /* STR_TRIM_H */
