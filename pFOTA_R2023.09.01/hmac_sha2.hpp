

#ifndef HMAC_SHA2_H
#define HMAC_SHA2_H

#include "sha2.hpp"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    sha224_ctx ctx_inside;
    sha224_ctx ctx_outside;

    sha224_ctx ctx_inside_reinit;
    sha224_ctx ctx_outside_reinit;

    unsigned char block_ipad[SHA224_BLOCK_SIZE];
    unsigned char block_opad[SHA224_BLOCK_SIZE];
}hmac_sha224_ctx;

typedef struct {
    sha256_ctx ctx_inside;
    sha256_ctx ctx_outside;

    sha256_ctx ctx_inside_reinit;
    sha256_ctx ctx_outside_reinit;

    unsigned char block_ipad[SHA256_BLOCK_SIZE];
    unsigned char block_opad[SHA256_BLOCK_SIZE];
}hmac_sha256_ctx;

typedef struct {
    sha384_ctx ctx_inside;
    sha384_ctx ctx_outside;

    sha384_ctx ctx_inside_reinit;
    sha384_ctx ctx_outside_reinit;

    unsigned char block_ipad[SHA384_BLOCK_SIZE];
    unsigned char block_opad[SHA384_BLOCK_SIZE];
}hmac_sha384_ctx;

typedef struct {
    sha512_ctx ctx_inside;
    sha512_ctx ctx_outside;

    sha512_ctx ctx_inside_reinit;
    sha512_ctx ctx_outside_reinit;

    unsigned char block_ipad[SHA512_BLOCK_SIZE];
    unsigned char block_opad[SHA512_BLOCK_SIZE];
}hmac_sha512_ctx;

void hmac_sha224_init(hmac_sha224_ctx *ctx, const unsigned char *key,
                      unsigned int key_size);
void hmac_sha224_reinit(hmac_sha224_ctx *ctx);
void hmac_sha224_update(hmac_sha224_ctx *ctx, const unsigned char *message,
                        unsigned int message_len);
void hmac_sha224_final(hmac_sha224_ctx *ctx, unsigned char *mac,
                       unsigned int mac_size);
void hmac_sha224(const unsigned char *key, unsigned int key_size,
                 const unsigned char *message, unsigned int message_len,
                 unsigned char *mac, unsigned mac_size);

void hmac_sha256_init(hmac_sha256_ctx *ctx, const unsigned char *key,
                      unsigned int key_size);
void hmac_sha256_reinit(hmac_sha256_ctx *ctx);
void hmac_sha256_update(hmac_sha256_ctx *ctx, const unsigned char *message,
                        unsigned int message_len);
void hmac_sha256_final(hmac_sha256_ctx *ctx, unsigned char *mac,
                       unsigned int mac_size);
void hmac_sha256(const unsigned char *key, unsigned int key_size,
                 const unsigned char *message, unsigned int message_len,
                 unsigned char *mac, unsigned mac_size);

void hmac_sha384_init(hmac_sha384_ctx *ctx, const unsigned char *key,
                      unsigned int key_size);
void hmac_sha384_reinit(hmac_sha384_ctx *ctx);
void hmac_sha384_update(hmac_sha384_ctx *ctx, const unsigned char *message,
                        unsigned int message_len);
void hmac_sha384_final(hmac_sha384_ctx *ctx, unsigned char *mac,
                       unsigned int mac_size);
void hmac_sha384(const unsigned char *key, unsigned int key_size,
                 const unsigned char *message, unsigned int message_len,
                 unsigned char *mac, unsigned mac_size);

void hmac_sha512_init(hmac_sha512_ctx *ctx, const unsigned char *key,
                      unsigned int key_size);
void hmac_sha512_reinit(hmac_sha512_ctx *ctx);
void hmac_sha512_update(hmac_sha512_ctx *ctx, const unsigned char *message,
                        unsigned int message_len);
void hmac_sha512_final(hmac_sha512_ctx *ctx, unsigned char *mac,
                       unsigned int mac_size);
void hmac_sha512(const unsigned char *key, unsigned int key_size,
                 const unsigned char *message, unsigned int message_len,
                 unsigned char *mac, unsigned mac_size);

#ifdef __cplusplus
}
#endif

#endif

