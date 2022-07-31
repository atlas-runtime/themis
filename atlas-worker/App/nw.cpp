#include <netdb.h>
#include <err.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>  
#include <vector>
#include <thread>       
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/param.h>
#include "funcs.h"
#include "nw.h"
#include <stdio.h>
#include <time.h>
#include <stdio.h>
#include "sgx_urts.h"
#include "Enclave_u.h"
#include "sgx_tcrypto.h"
#define LOCATION __LINE__,__FILE__,__func__

int32_t
recv_data(int n_socket, uint8_t *buffer, uint32_t number)
{
	int32_t rx_bytes;
	int32_t tmp_bytes;
	rx_bytes = 0;
	tmp_bytes = 0;
	while (rx_bytes < (int32_t)number) {
		tmp_bytes = dienc_recv(n_socket, &buffer[rx_bytes], number-rx_bytes);
		if (tmp_bytes <= 0) 
            return -1;
		rx_bytes += tmp_bytes;
	}
	return rx_bytes;
}

int32_t
diencl_socket(short unsigned int port)
{
	/* declaration */
	int ws;
	int bind_result;
	int listen_result;
	// used for setting keepalive flag
	int optval;
	struct sockaddr_in server_addr;
	// init code
	// Set the option active
	optval = 1;
	// reset values
	bind_result = listen_result = 0;
	memset(&server_addr, 0, sizeof(struct sockaddr_in));
	// setup the new socket
	ws = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ws == -1) {
		fprintf(stdout, "Failed to Initialize socket: Line %d File %s Func %s\n", LOCATION);
		abort();
	}
	if (setsockopt(ws, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof(optval)) < 0) {
		fprintf(stdout, "Failed to set KEEP_ALIVE for socket: Line %d File %s Func %s\n", LOCATION);
		abort();
	}
	// make port reusable
	setsockopt(ws, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));
	// bind to the port
	bind_result = bind(ws, (struct sockaddr *) &server_addr, sizeof(server_addr));
	if (bind_result == -1) {
		fprintf(stdout, "Failed to bind socket: Line %d File %s Func %s\n", LOCATION);
		abort();
	}
	// listen to the socket
	listen_result = listen(ws, 1);
	if (listen_result == -1) {
		fprintf(stdout, "Failed to listen socket: Line %d File %s Func %s\n", LOCATION);
		abort();
	}
	return ws;
}

int32_t
diencl_accept(int32_t ws)
{
	int32_t new_socket;
	struct sockaddr_in client;
	socklen_t len = sizeof(client);
	memset(&client, 0, sizeof(struct sockaddr_in));
	new_socket = accept(ws, (struct sockaddr *)&client, &len);
	if (new_socket == -1) {
		printf("%d\n", ws);
		fprintf(stdout, "Failed to accept socket: Line %d File %s Func %s\n", LOCATION);
		abort();
	}   
	return new_socket;
}

int32_t
dienc_recv(int32_t n_socket, void *data, uint32_t len)
{
	int32_t d;
	//clock_gettime(CLOCK_REALTIME, &tnw_start);
	d = (int32_t)recv(n_socket, data, len, MSG_NOSIGNAL);
	//clock_gettime(CLOCK_REALTIME, &tnw_stop);
	return d;
}

int32_t
dienc_send(int n_socket, void *data, uint32_t len)
{
	int32_t d;
	//clock_gettime(CLOCK_REALTIME, &tnw_start);
	d = (int32_t)send(n_socket, data, len, MSG_NOSIGNAL);
	//clock_gettime(CLOCK_REALTIME, &tnw_stop);
	return d;
}

int32_t
recv_client_key(int32_t n_socket, uint8_t *key, uint32_t size)
{
	return dienc_recv(n_socket, key, size);
}

int32_t
send_public_key(int32_t n_socket, uint8_t *key, uint32_t size)
{
	return dienc_send(n_socket, key, size);
}

void
ocall_send_packet(int32_t new_socket, uint8_t *pkt, size_t len)
{
	int32_t tmp_bytes, rx_bytes, var;
	rx_bytes = tmp_bytes = 0;
	while (rx_bytes != (int32_t)len) {
		var = (int32_t)(len - rx_bytes);
		dienc_send(new_socket, &var, sizeof(uint32_t));
		tmp_bytes = dienc_send(new_socket, &pkt[rx_bytes], (uint32_t)(len-rx_bytes));
        if (tmp_bytes == -1) {
#ifdef DEBUG
            perror("Broken Pipe");
#endif
            break;
        }
		rx_bytes += tmp_bytes;
	}
}
