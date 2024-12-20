#include "Hasher.h"
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <sstream>
#include <iomanip>
#include <stdexcept>

std::string Hasher::generateSalt(size_t length) {
    unsigned char *salt = new unsigned char[length];
    if (RAND_bytes(salt, (int)length) != 1) {
        delete[] salt;
        throw std::runtime_error("Salt generation failed.");
    }
    std::string hexSalt = bytesToHex(salt, length);
    delete[] salt;
    return hexSalt;
}

std::string Hasher::hashPassword(const std::string &salt, const std::string &password) {
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (!ctx) throw std::runtime_error("Failed to create EVP_MD_CTX.");

    EVP_MD *sha256 = EVP_MD_fetch(NULL, "SHA256", NULL);
    if (!sha256) {
        EVP_MD_CTX_free(ctx);
        throw std::runtime_error("Failed to fetch SHA256.");
    }

    if (!EVP_DigestInit_ex(ctx, sha256, NULL)) {
        EVP_MD_free(sha256);
        EVP_MD_CTX_free(ctx);
        throw std::runtime_error("Digest initialization failed.");
    }

    std::string input = salt + password;
    if (!EVP_DigestUpdate(ctx, input.data(), input.size())) {
        EVP_MD_free(sha256);
        EVP_MD_CTX_free(ctx);
        throw std::runtime_error("Digest update failed.");
    }

    unsigned char *outdigest = (unsigned char*)OPENSSL_malloc(EVP_MD_get_size(sha256));
    if (!outdigest) {
        EVP_MD_free(sha256);
        EVP_MD_CTX_free(ctx);
        throw std::runtime_error("Memory allocation failed.");
    }

    unsigned int len = 0;
    if (!EVP_DigestFinal_ex(ctx, outdigest, &len)) {
        OPENSSL_free(outdigest);
        EVP_MD_free(sha256);
        EVP_MD_CTX_free(ctx);
        throw std::runtime_error("Digest finalization failed.");
    }

    std::string hexDigest = bytesToHex(outdigest, len);
    OPENSSL_free(outdigest);
    EVP_MD_free(sha256);
    EVP_MD_CTX_free(ctx);

    return hexDigest;
}

std::string Hasher::bytesToHex(const unsigned char *bytes, size_t length) {
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (size_t i = 0; i < length; i++) {
        oss << std::setw(2) << (int)bytes[i];
    }
    return oss.str();
}
