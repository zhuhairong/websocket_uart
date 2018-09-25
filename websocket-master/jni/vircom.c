#define _XOPEN_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <poll.h>

static int alive = 0;
static char buf[8*1024] = {0};

char* vircom1 = "/sdcard/vircom1";
char* vircom2 = "/sdcard/vircom2";

static void neo_handler(int sig)
{
	printf("got signal(%d)\n", sig);
	alive = 0;
}

int main(int argc, char **argv)
{
	int ret = 0;
	int m1 = 0;
	int m2 = 0;
	char *pts = NULL;
	struct pollfd pollfds[2];
	signal(SIGTERM, neo_handler);
	signal(SIGINT, neo_handler);
	m1 = open("/dev/ptmx", O_RDWR);
	if (m1 < 0) {
		printf("open /dev/ptmx failed, errno=%d(%s)\n", errno, strerror(errno));
		return -1;
	}
	grantpt(m1);
	unlockpt(m1);
	m2 = open("/dev/ptmx", O_RDWR);
	if (m2 < 0) {
		printf("open /dev/ptmx failed, errno=%d(%s)\n", errno, strerror(errno));
		goto err_m2;
	}
	grantpt(m2);
	unlockpt(m2);
	pts = ptsname(m1);
	if (!pts)
		goto err_pts;
	remove(vircom1);
	printf("pts:%s, vir:%s\n", pts, vircom1);
	/*ret = symlink(pts, vircom1);
	if (ret < 0) {
		printf("create ./ttyNeo1 failed, errno=%d(%s)\n", errno, strerror(errno));
		goto err_pts;
	}*/
	pts = ptsname(m2);
	printf("pts:%s, vir:%s\n", pts, vircom2);
	remove(vircom2);
	ret = symlink(pts, vircom2);
	if (ret < 0) {
		printf("create ./ttyNeo2 failed, errno=%d(%s)\n", errno, strerror(errno));
		goto err_pts;
	}
	memset(&pollfds, 0, sizeof(pollfds));
	pollfds[0].fd = m1;
	pollfds[0].events = POLLIN;
	pollfds[1].fd = m2;
	pollfds[1].events = POLLIN;
	alive = 1;
	while (alive) {
		ret = poll(&pollfds[0], 2, 500);
		if ((ret < 0) && (errno == EINTR) || (ret == 0))
			continue;
		else if (ret < 0) {
			printf("poll failed, errno=%d(%s)\n", errno, strerror(errno));
			break;
		}
		if (pollfds[0].revents & POLLIN) {
			memset(buf, 0, sizeof(buf));
			ret = read(m1, buf, sizeof(buf));
			if (ret > 0)
			write(m2, buf, ret);
			pollfds[0].revents = 0;
		}
		if (pollfds[1].revents & POLLIN) {
			memset(buf, 0, sizeof(buf));
			ret = read(m2, buf, sizeof(buf));
			if (ret > 0)
			write(m1, buf, ret);
			pollfds[1].revents = 0;
		}
	}
	err_pts:
	close(m2);
	m2 = -1;
	err_m2:
	close(m1);
	m1 = -1;
	return 0;
}


