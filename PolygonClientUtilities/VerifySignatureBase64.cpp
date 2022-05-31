#include "pch.h"
#include "VerifySignatureBase64.h"
#include "Patches.h"

Crypt__verifySignatureBase64_t Crypt__verifySignatureBase64 = (Crypt__verifySignatureBase64_t)ADDRESS_CRYPT__VERIFYSIGNATUREBASE64;

void __fastcall Crypt__verifySignatureBase64_hook(HCRYPTPROV* _this, void*, char a2, int a3, int a4, int a5, int a6, int a7, int a8, char a9, int a10, int a11, int a12, int a13, int a14, int a15)
{
    // the actual function signature is (HCRYPTPROV* _this, std::string message, std::string signatureBase64)
    // but for some reason it throws a memory access violation when you pass the parameters back into the function, without even modifying them
    // each char represents the beginning of new std::string (with the int parameters, that totalls to a length of 24 bytes)
    // the signature length is stored in a14 though so we can just use that

    if (a14 > 1024)
    {
        std::ostringstream error;
        error << "Signature too large.  " << a14 << " > 1024";
        throw std::runtime_error(error.str());
    }

    Crypt__verifySignatureBase64(_this, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
}