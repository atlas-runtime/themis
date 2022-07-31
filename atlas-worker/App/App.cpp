#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <stdio.h>
#include "sgx_urts.h"
#include "Enclave_u.h"
#include "sgx_tcrypto.h"
#include "funcs.h"
#define ENCLAVE_FILE "enclave.signed.so"
#define STDC_WANT_LIB_EXT1 1
#include "../Enclave/dh/tools.h"
#include "../Enclave/dh/tweetnacl.h"
#include <errno.h>
#include <locale.h>
#include <dlfcn.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "nw.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/param.h>
#define _unused(x) ((void)(x))

void usage(){};
uint8_t *bootstrap_server(sgx_enclave_id_t *eid);
void
server_do_handshake(
    sgx_enclave_id_t eid,
    int socket_fd,
    uint8_t client_public_key[crypto_box_PUBLICKEYBYTES],
    uint8_t *server_public_key);

int
main(int argc, char *argv[])
{
    int32_t socket_fd, ws;
    sgx_enclave_id_t eid;
    short unsigned int port;
    unsigned char *buffer;
    char opt;
    int32_t buffer_len;
    uint8_t *server_public_key;
    uint8_t client_public_key[crypto_box_PUBLICKEYBYTES];
    size_t len;
    long int val_result;
    memset(client_public_key, 0, crypto_box_PUBLICKEYBYTES);
    sgx_status_t ret;
    ret = SGX_SUCCESS;
    eid = 0;
    buffer_len = 0;
    port = 0;
    (void) ret;
    val_result = 0;
#ifdef DEBUG
    /* create the enclave */
    printf("Creating Enclave\n");
#endif
    /*
     * Get arguments
     */
    while ((opt = (char)getopt(argc, argv, "p:h")) != -1) { 
        switch (opt) {
            case 'p':
                port = (short unsigned int)atoi(optarg);
                break;
            case 'h':
            default:
                usage();
        }
    }
    server_public_key = bootstrap_server(&eid);
    //check_args(daemon_port, local_execution, input_file);
    if (port != 0) {
            // listen to a socket
            ws = diencl_socket(port);
restart:
            // accept a client that ofloads requests
            socket_fd = diencl_accept(ws);
            memset(client_public_key, '\0', crypto_box_PUBLICKEYBYTES);
            // this is not used, we already know the size of the client pkey
            val_result = read(socket_fd, &len, sizeof(uint32_t));
            // recv the clients public key
            val_result = recv_data(socket_fd, client_public_key, crypto_box_PUBLICKEYBYTES);
            if (val_result == -1) {
                close(socket_fd);
                goto restart;
            }
            server_do_handshake(eid, socket_fd, client_public_key, server_public_key);
            // start receiving offlodaing requests
            while (read(socket_fd, &buffer_len, sizeof(uint32_t))) {
                buffer = (uint8_t *)calloc(buffer_len, sizeof(uint8_t));
                val_result = recv_data(socket_fd, buffer, buffer_len);
                // The client terminated, reset the socket
                if (val_result <= 0) {
                    close(socket_fd);
                    goto restart;
                }
                ecall_start(eid, socket_fd, buffer, buffer_len);
                buffer_len = 0;
                free(buffer);
            }
            close(socket_fd);
            goto restart;
    }
    // we should never go here
    sgx_destroy_enclave(eid);
}
