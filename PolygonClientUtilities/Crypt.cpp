#include "pch.h"
#include "Crypt.h"
#include "Patches.h"
#include "Util.h"

Crypt__verifySignatureBase64_t Crypt__verifySignatureBase64 = (Crypt__verifySignatureBase64_t)ADDRESS_CRYPT__VERIFYSIGNATUREBASE64;

// Crypt::verifySignatureBase64(std::string message, std::string signatureBase64)
void __fastcall Crypt__verifySignatureBase64_hook(HCRYPTPROV* _this, void*, int a2, BYTE* pbData, int a4, int a5, int a6, DWORD dwDataLen, int a8, int a9, int a10, int a11, int a12, int a13, int a14, int a15)
{
    /*
        Ideally, we would be able to just use the function signature as-is.
        However, it causes inexplicable crashes. Thus, we must reconstruct
        the strings by hand given the manual parameters.
    */

    std::string message;
    std::string signatureBase64;

    // Get message
    const BYTE* v18 = pbData;
    if ((unsigned int)a8 < 0x10)
    {
        v18 = (const BYTE*)&pbData;
    }

    message = std::string(reinterpret_cast<char const*>(pbData), dwDataLen);

    // Get signatureBase64
    int* v21 = (int*)a10;
    if ((unsigned int)a15 < 0x10)
    {
        v21 = &a10;
    }

    signatureBase64 = std::string(reinterpret_cast<const char*>(v21), a14);

    // Verify the signature
    try
    {
        // Read public key
        EVP_PKEY* key = NULL;
        BIO* bio = BIO_new_mem_buf((void*)Util::publicKey.c_str(), Util::publicKey.length());

        if (bio == NULL)
        {
            throw std::runtime_error("");
        }

        key = PEM_read_bio_PUBKEY(bio, NULL, NULL, NULL);
        BIO_free(bio);

        // Create context
        EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(key, NULL);

        if (!ctx)
        {
            throw std::runtime_error("");
        }

        if (EVP_PKEY_verify_init(ctx) <= 0)
        {
            throw std::runtime_error("");
        }

        if (EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_PADDING) <= 0)
        {
            throw std::runtime_error("");
        }

        if (EVP_PKEY_CTX_set_signature_md(ctx, EVP_sha1()) <= 0)
        {
            throw std::runtime_error("");
        }

        // Verify signature against the message
        unsigned char* signature = Util::base64Decode(signatureBase64);
        unsigned char* data = new unsigned char[message.length()];
        
        std::copy(message.begin(), message.end(), data);

        int result = EVP_PKEY_verify(ctx, signature, sizeof(signature), data, strlen((char*)data));

        // Dispose objects
        EVP_PKEY_free(key);
        EVP_PKEY_CTX_free(ctx);

        delete[] signature;
        delete[] data;

        // Check
        if (result != 1)
        {
            throw std::runtime_error("");
        }
    }
    catch (...)
    {
        throw std::runtime_error("");
    }
}