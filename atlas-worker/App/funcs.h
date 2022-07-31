#ifndef FUNCS_H
#define FUNCS_H
#define ns 1000000000
#include "sgx_urts.h"
#include "sgx_defs.h"
#include "Enclave_u.h"
double get_time_diff(struct timespec a, struct timespec b);
void l_setup_client_handshake(sgx_enclave_id_t eid, int n_socket);
extern double sgx_time, e2e_time, exec_time;
int receive_modules(int n_socket);
extern struct timespec te2e_start, te2e_stop, tsgx_start, tsgx_stop, texec_start, texec_stop;
void print_key(const char *s, uint8_t *key, size_t size);

#endif


