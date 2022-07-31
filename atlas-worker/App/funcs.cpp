#include <stdio.h>
#include <time.h>
#include "sgx_urts.h"
#include "Enclave_u.h"
#include "sgx_tcrypto.h"
#include "nw.h"
#include "funcs.h"
#include "../Enclave/dh/tools.h"
#include "../Enclave/dh/tweetnacl.h"

double
timespec_to_ns(struct timespec tp)
{
    return ((double)tp.tv_sec / 1.0e-9) + (double)tp.tv_nsec;
}


double
get_time_diff(struct timespec a, struct timespec b)
{
    return (double)(timespec_to_ns(a) - timespec_to_ns(b));
}

void                                            
print_key(const char *s, uint8_t *key, size_t size) 
{    
    size_t i;
    printf("%s: ", s);                          
    for (i = 0; i < size; i++)                  
        printf("%u", key[i]);                   
    printf("\n");                               
}


uint8_t *
bootstrap_server(
    sgx_enclave_id_t *eid
    ) {
    uint8_t *server_public_key;
    int32_t updated;
    sgx_launch_token_t token = {0};
    sgx_status_t ret;
    (void)(ret);
    server_public_key = (uint8_t *)calloc(sizeof(uint8_t), crypto_box_PUBLICKEYBYTES);
    // create the enclave
    ret = sgx_create_enclave("enclave.signed.so", SGX_DEBUG_FLAG, &token,
            &updated, eid, NULL);
    /* init the enclave args */
    ret = ecall_init(*eid, stdin, stdout, stdout);
#ifdef DEBUG
    if (ret != SGX_SUCCESS){
        printf("\nERROR: failed to create enclave, code: %#x\n", ret);
        abort();
    }
#endif
    ret = ecall_get_server_key(*eid, server_public_key, crypto_box_PUBLICKEYBYTES);
#ifdef DEBUG
    if (ret != SGX_SUCCESS){
        printf("\nERROR: failed to create enclave, code: %#x\n", ret);
        abort();
    }
#endif
    return server_public_key;
}

void
server_do_handshake(
    sgx_enclave_id_t eid,
    int fd,
    uint8_t client_public_key[crypto_box_PUBLICKEYBYTES],
    uint8_t *server_public_key)
{
    // register the clients key
    ecall_register_client_key(eid, client_public_key, crypto_box_PUBLICKEYBYTES);
    // send the server public key
    ocall_send_packet(fd, server_public_key, crypto_box_PUBLICKEYBYTES);
    // generate encryption key
    ecall_generate_shared_key(eid, fd);
}
