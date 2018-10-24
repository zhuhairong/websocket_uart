#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <event2/event.h>
#include "conv.h"

extern "C"
{
#include "websock.h"
#include "api.h"
}

libwebsock_client_state* g_state = NULL;
char sendBuf[2046];
pthread_mutex_t client_mutex;

void* send_thread(void*)
{
	while(true)
	{
		pthread_mutex_lock(&client_mutex);
		if(g_state)
			libwebsock_send_text(g_state, sendBuf);
		pthread_mutex_unlock(&client_mutex);
		usleep(30000);
	}
	return NULL;
}

// call backs
int 
onmessage(libwebsock_client_state *state, libwebsock_message *msg)
{
	fprintf(stderr, "only libevent Received message from client: %d\n", state->sockfd);
	fprintf(stderr, "Message opcode: %d\n", msg->opcode);
	fprintf(stderr, "Payload Length: %llu\n", msg->payload_len);
	fprintf(stderr, "Payload: %s\n", msg->payload);
	//now let's send it back.
	//libwebsock_send_text(state, msg->payload);

	memcpy(sendBuf, msg->payload, msg->payload_len);

	

//	char *gbk = "·þÎñ¶Ë»Ø¸´";
//	int len = strlen(gbk);
//	char *utf8 = calloc(len * 3, sizeof(char));
//
//	int ret = dl_icuuc_gbk2utf8(utf8, len * 3, gbk, strlen(gbk));
//	printf("ret: %d \n", ret);
//
//	libwebsock_send_text(state, utf8);
//
//	free(utf8);
	return 0;
}

int
onopen(libwebsock_client_state *state)
{
	fprintf(stderr, "onopen: %d\n", state->sockfd);
	pthread_mutex_lock(&client_mutex);
	g_state = state;
	pthread_mutex_unlock(&client_mutex);
		
	return 0;
}

int
onclose(libwebsock_client_state *state)
{
	fprintf(stderr, "onclose: %d\n", state->sockfd);
	pthread_mutex_lock(&client_mutex);
	if(g_state == state)
	{
		g_state = NULL;
	}
	pthread_mutex_unlock(&client_mutex);
	return 0;
}

int main(int argc, char *argv[])
{
	printf("zhr only libevent\n");
	libwebsock_context *ctx = NULL;

  	ctx = libwebsock_init();
	printf("ctx: %p \n", ctx);
	if(ctx == NULL)
	{
		printf("libwebsock_init Failed. \n");
		return 0;
	}

	//dl_icuuc_init();

	char *port = "12000";

	libwebsock_bind(ctx, "192.168.104.230", port);

	ctx->onmessage = onmessage;
 	ctx->onopen = onopen;
	ctx->onclose = onclose;

	pthread_t threadSend;
	pthread_create(&threadSend, NULL, send_thread, NULL);

	pthread_mutex_init(&client_mutex, NULL);

	printf("libwebsock_wait start \n");
	libwebsock_wait(ctx);
	printf("libwebsock_wait end \n");

	return 1;
}