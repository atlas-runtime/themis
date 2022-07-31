#include "Enclave_t.h"
#include "sgx_tcrypto.h"
#include "sgx_includes.h"
#include "sgx_funcs.h"
#include "sgx_structs.h"
#include <stdarg.h>
#include <stdint.h>
#include <unistd.h>
#include "sgx_defs.h"
#include <stdio.h>
#include "dh/tools.h"
#include "dh/tweetnacl.h"
#include "Enclave_t.h"
#include "sgx_trts.h"
#include <string.h>  
#include <stdlib.h>  
#include <vector>
#include <string>
#include <assert.h>
#include <sgx_thread.h>
#include <time.h>
#define MAX_COPY_SIZE 1000
#define KEY_SIZE 16
/* original std* variables from the untrusted world */
uint8_t encryption_key[KEY_SIZE * 2];
/* internal module structure */
Content encrypt(uint8_t *string, int32_t ks, uint8_t *server_public_key, uint8_t *client_secret_key);
/*******************************************/
/*            generate keypair              */
/*******************************************/
std::string response_buffer = "";
uint8_t client_public_key[crypto_box_PUBLICKEYBYTES];
uint8_t server_public_key[crypto_box_PUBLICKEYBYTES];
uint8_t server_private_key[crypto_box_SECRETKEYBYTES];

// g++ things :)
extern "C" {
    int bootstrap_qjs();
    void qjs_execute_code(char *buffer, int32_t len);
    void
    append_results(const char *b)
    {
        response_buffer += (char *)b;
    }

    void
    random_bytes(uint8_t *a, int32_t len)
    {
        sgx_read_rand(a, len);
    }
}

void
ecall_gen_keypair(void)
{
    crypto_box_keypair(server_public_key, server_private_key);
}

void
ecall_get_server_key(uint8_t *key, size_t k)
{
    memcpy(key, server_public_key, k);
}

void
ecall_register_client_key(uint8_t *key, size_t k)
{
    memset(client_public_key, 0, k);
    memcpy(client_public_key, key, k);
    // init the qjs environment for each new client
    bootstrap_qjs();
}

void
gen_encryption_key(uint8_t *b, int32_t len)
{
    random_bytes(b, len);
    memset(b, 'a', len);
}

void
ecall_generate_shared_key(int fd)
{
    Content c;
    gen_encryption_key(encryption_key, KEY_SIZE * 2);
    c = encrypt(encryption_key, KEY_SIZE, client_public_key, server_private_key);
    ocall_send_packet(fd, (uint8_t *)c.bytes, c.size);
    c = encrypt(&encryption_key[16], KEY_SIZE, client_public_key, server_private_key);
    ocall_send_packet(fd, (uint8_t *)c.bytes, (int32_t)c.size);
}

void
randombytes(uint8_t *a, uint8_t b)
{
    sgx_read_rand(a, b);
}

void
ecall_init(FILE *stdi, FILE *stdo, FILE *stde) {
    stdin = stdi;
    stdout = stdo;
    stderr = stde;
    ecall_gen_keypair();
}

/*
 * decrypt the incoming code from the client using AES
 */
uint8_t *
code_decrypt(uint8_t *str, int32_t len)
{
    uint8_t n[crypto_stream_NONCEBYTES];
    uint8_t *cipher;
    cipher = (uint8_t *)calloc(len, sizeof(uint8_t) + 1);
    memset(n, 0, crypto_stream_NONCEBYTES);
    crypto_stream_xor(cipher, str, len, n, encryption_key);
    cipher[len] = '\0';
    return cipher;
}

/*
 * Same function for encryption/decryption
 */
uint8_t *
decrypt_chunks(uint8_t *enc, int32_t data_size)
{
#if defined(NO_ENCRYPTION)
    /*
     * Since we are using no encryption, we are returning a new allocated buffer
     * to the user, so it can be freed at the end of execution
     */
    uint8_t *n = (uint8_t *)malloc(data_size + 1);
    memcpy(n, enc, data_size);
    n[data_size] = '\0';
    return n;
#else
    #define CHUNK_LEN 1000
    int32_t len, rx_bytes;
    uint8_t *plain_text, *cipher;
    len = CHUNK_LEN;
    rx_bytes = 0;
    plain_text = (uint8_t *)calloc(1, data_size);
    while (rx_bytes != data_size) {
        if ((rx_bytes + len) > data_size) {
            len = data_size - rx_bytes;
        }
        cipher =  code_decrypt(&enc[rx_bytes], len);
        memcpy(&plain_text[rx_bytes], cipher, len);
        rx_bytes += len;
        cipher[len] = '\0';
#ifdef DEBUG
        printf("|%.*s|\n", len, cipher);
#endif
        free(cipher);
    }
    return plain_text;
#endif
}

extern const char *evaluator;
extern size_t evaluator_len;
/*
 * The first function that inits the qjs VM, stores the context in global variable
 * and preloads the modules
 */
char *cbuffer = NULL;

void
ecall_start(int socket_fd, uint8_t *buf, uint32_t len)
{
    uint8_t *og;
    /* the execution results */
    uint8_t *client_result;
    /* create the atlas execution command */
    cbuffer = (char *)calloc(len + 16, sizeof(char));
    /* get the plain text */
    og = decrypt_chunks(buf, len);
    memset(cbuffer,'\0', len + 16);
    /* if we are running on server, we dont expect any arguments, execute the buffer */
    memcpy(cbuffer, "atlas_data=", strlen("atlas_data="));
    memcpy(&cbuffer[strlen(cbuffer)], og, len);
    // evaluate the request
    qjs_execute_code(cbuffer, strlen(cbuffer));
    // execute the request
    qjs_execute_code((char *)evaluator, evaluator_len);
    // if we are not running locally, send the results back to the client */
    client_result = decrypt_chunks((uint8_t *)response_buffer.c_str(), response_buffer.length());
    // send the results to client
    ocall_send_packet(socket_fd, client_result, (int32_t)response_buffer.length());
    free(client_result);
    /*****************************************/
    /***************** CLEANUP ***************/
    /*****************************************/
    response_buffer = "";
    response_buffer.clear();
    free(cbuffer);
    free(og);
    memset(client_public_key, 0, crypto_box_PUBLICKEYBYTES);
}
