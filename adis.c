
#include <stdio.h>
#include <string.h>
#include "utils_sockets.h"
#include "fcfutils.h"
#include "fcfmain.h"

static unsigned char buffer[1000];


static void common_cb(const char * src, int fd){
	int rc = readsocket(fd, buffer, sizeof(buffer));
	if (rc > 0){
		sendADISData(buffer, rc);
	}
}

//active fd
static void virtADIS_cb(struct pollfd *pfd){
	common_cb("virt_ADIS", pfd->fd);
}

int adis_init(){
	int port = 36000;
	int fd = getsocket(port);
	int rc = fcf_add_fd(fd, POLLIN, virtADIS_cb);
	return rc;
}

void adis_final(){
}

