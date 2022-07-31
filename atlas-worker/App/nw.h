#ifndef NW_H
#define NW_H
#include <sys/types.h>
int32_t diencl_socket (short unsigned int port);
int32_t diencl_accept(int32_t welcome_socket);

int32_t dienc_recv(int32_t n_socket, void *data, uint32_t len);
int32_t dienc_send(int32_t n_socket, void *data, uint32_t len);

char *recv_file(int32_t n_socket, uint32_t *s);
int32_t recv_data(int32_t n, uint8_t *b, uint32_t num);
int32_t recv_chunk_data(int32_t n, uint32_t num, uint8_t a);
int32_t send_public_key(int32_t n_socket, uint8_t *key, uint32_t size);
int32_t recv_client_key(int32_t n_socket, uint8_t *key, uint32_t size);

#endif
