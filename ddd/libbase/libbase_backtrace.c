/*
 * ���ٶ�ջ
 */
#include <stdio.h>
#include <stdlib.h>

#include "libbase_backtrace.h"
#include "libbase_type.h"

#if defined(linux) && defined(BACKTRACE_DUMP)
#include <execinfo.h>

#define MAX_STACK	25

/*
 * ���ջ���ļ�
 */
void h_backtrace_dump(int fd)
{
	void *array[MAX_STACK];
	int32_t ntrace = backtrace(array, MAX_STACK);

	backtrace_symbols_fd(array, ntrace, fd);
}
#else
void h_backtrace_dump(int fd)
{
	fprintf(stderr, "backtrace_dump is invalid!\n");
}

#endif
