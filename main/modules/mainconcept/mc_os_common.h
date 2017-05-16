/* file: mc_os_common.h
 * brief: os common definitions
 * create: 2017-04-14 11:00 zhangjtgo@sina.com
 * modify:
 * company: zqvideo
 ******************************************************************************/

#ifndef _MCOSCOMMON_H
#define _MCOSCOMMON_H

#ifndef _MSC_VER

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <bufstrm.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#define SOCKET int

#ifdef _BS_UNICODE	// dependencies64/mainconcept/bufstrm.h引入

#include <wchar.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

inline FILE *_wfopen(const wchar_t *path, const wchar_t *mode)
{
	int n = 2 * (int)wcslen(path) + 1;
	char *b = (char *)malloc(n);
	if (b) {
		char m[16];
		wcstombs(b, path, n);
		wcstombs(m, mode, 16);
		FILE *f = fopen(b, m);
		free(b);
		return f;
	}
	return NULL;
}

inline int _wstati64(const wchar_t *path, struct stat *buf)
{
	int n = 2 * (int)wcslen(path) + 1;
	char *b = (char *)malloc(n);
	if (b) {
		wcstombs(b, path, n);
		n = stat(b, buf);
		free(b);
		return n;
	}
	return -1;
}

inline int _wopen(const wchar_t *path, int flags, mode_t mode)
{
	int n = 2 * (int)wcslen(path) + 1;
	char *b = (char *)malloc(n);
	if (b) {
		wcstombs(b, path, n);
		n = open(b, flags, mode);
		free(b);
		return n;
	}
	return -1;
}

#endif	// _BS_UNICODE

inline unsigned int timeGetTime()
{
	unsigned int uptime = 0;
	struct timespec on;
	if (!clock_gettime(CLOCK_MONOTONIC, &on))
		uptime = on.tv_sec * 1000 + on.tv_nsec / 1000000;
	//uptime = duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count();
	return uptime;
}

#endif	// _MSC_VER

#endif	// _MCOSCOMMON_H

