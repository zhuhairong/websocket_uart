#ifndef _UART_ACCESS_H__
#define _UART_ACCESS_H__


#include <termios.h>
#include <utils/threads.h>
#include "globle.h"

using namespace android;

typedef void* (*callbackfunsensor)(char* buffer, int size);

class Uart_Access
{
public:
	Uart_Access(const char* dev_name);
	virtual ~Uart_Access();

	int uart_init();
	void uart_exit();
	int uart_send(char* buf, int size);
	int thread_recv();

	// for receive callback
	int set_sensor_cb(callbackfunsensor cb);

protected:
	class UartRecvThread : public Thread
	{
	public:
		UartRecvThread(Uart_Access* parent)
			:m_parent(parent),
			Thread(false)
		{
			
		}
		
		~UartRecvThread(){}

		int start_thread()
		{
			IPRINTF("recv thread start\n");
			run("UartRecvThread", PRIORITY_NORMAL);
			return 0;
		}

		int stop_thread()
		{
			IPRINTF("recv thread stop\n");
			requestExitAndWait();
			return 0;
		}

		virtual bool threadLoop() 
		{
			if(m_parent)
				m_parent->thread_recv();
			return true;
		}
	private:
		Uart_Access* m_parent;
	};
	
private:
	
private:
	char m_devName[256];
#define RECV_MAX_SIZE 1024	
	char m_recvBuf[RECV_MAX_SIZE];
	int m_fd;
	int m_exit;
	struct termios oldtio;
	sp<UartRecvThread> m_recvThread;
	fd_set readset; 
	struct timeval tv; 
	callbackfunsensor	m_recv_cb;
};


#endif
