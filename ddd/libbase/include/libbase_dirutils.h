#ifndef __LIBBASE_DIRUTILS_H__
#define __LIBBASE_DIRUTILS_H__

/**
 * Ŀ¼���ϵĻص�
 * \param isdir �Ƿ�ΪĿ¼
 * \param entry_name Ŀ¼��ȫ·��
 * \param userdata listdirʱ���û�����
 * \return ����0����������ֵ������listdir����������������
 */
typedef int (*dir_entry_func_t)(int isdir, const char *entry_name, void *userdata);

/**
 * ��Ŀ¼
 * \param dir Ŀ¼
 * \param userdata �û�����
 * \param entry_callback ��ÿ��Ŀ¼��Ļص�
 * \return ��������0�����򷵻�entry_callback��ֵ���޷���Ŀ¼����-1������������������errno��ȡ�ô���
 */
int h_dirutils_listdir(const char *dir, void *userdata,
        dir_entry_func_t entry_callback);

/**
 * ��Ŀ¼,����ĸ����
 * \param dir Ŀ¼
 * \param userdata �û�����
 * \param entry_callback ��ÿ��Ŀ¼��Ļص�
 * \return ��������0�����򷵻�entry_callback��ֵ���޷���Ŀ¼����-1������������������errno��ȡ�ô���
 */
int h_dirutils_scandir(const char *dir, void *userdata,
        dir_entry_func_t entry_callback);

/**
 * �ݹ�ɾ��һ��Ŀ¼
 * \param dir Ŀ¼
 * \return ��������0��������errno��ȡ�ô���
 */
int h_dirutils_rmdir(const char *dir);

#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

/**
 * ����Ŀ¼������busybox)
 * \param path ·��
 * \param mode ģʽ
 * \param recur 1�ݹ鴴��Ŀ¼
 * \return a��b�Ĳ�ֵ
 */
static inline int h_mkdir (char *path, long mode, int recur)
{
	mode_t mask;
	const char *fail_msg;
	char *s = path;
	char c;
	struct stat st;

	mask = umask(0);
	if (mode == -1) {
		umask(mask);
		mode = (S_IXUSR | S_IXGRP | S_IXOTH |
				S_IWUSR | S_IWGRP | S_IWOTH |
				S_IRUSR | S_IRGRP | S_IROTH) & ~mask;
	} else {
		umask(mask & ~0300);
	}

	do {
		c = 0;

		if (recur) {	/* Get the parent. */
			/* Bypass leading non-'/'s and then subsequent '/'s. */
			while (*s) {
				if (*s == '/') {
					do {
						++s;
					} while (*s == '/');
					c = *s;		/* Save the current char */
					*s = 0;		/* and replace it with nul. */
					break;
				}
				++s;
			}
		}

		if (mkdir(path, 0777) < 0) {
			/* If we failed for any other reason than the directory
			 * already exists, output a diagnostic and return -1.*/
			if (errno != EEXIST
				|| !recur
				|| (stat(path, &st) < 0 || !S_ISDIR(st.st_mode))) {
				fail_msg = "create";
				umask(mask);
				break;
			}
			/* Since the directory exists, don't attempt to change
			 * permissions if it was the full target.  Note that
			 * this is not an error conditon. */
			if (!c) {
				umask(mask);
				return 0;
			}
		}

		if (!c) {
			/* Done.  If necessary, updated perms on the newly
			 * created directory.  Failure to update here _is_
			 * an error.*/
			umask(mask);
			if ((mode != -1) && (chmod(path, mode) < 0)){
				fail_msg = "set permissions of";
				break;
			}
			return 0;
		}

		/* Remove any inserted nul from the path (recursive mode). */
		*s = c;

	} while (1);

	fprintf(stderr,"Cannot %s directory `%s'", fail_msg, path);
	return -1;
}

#endif /*__LIBBASE_DIRUTILS_H__ */
