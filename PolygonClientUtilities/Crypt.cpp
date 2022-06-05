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

}