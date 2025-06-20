
#include <cstdint>
#include <iostream>
#include <openssl/bn.h>
#include <openssl/engine.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <openssl/trace.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <vector>
#include <iostream>

typedef int64_t int64;
typedef uint64_t uint64;
class key_error : public std::runtime_error {
public:
  explicit key_error(const std::string &str) : std::runtime_error(str) {}
};

void Sign(EC_KEY *pkey){
  unsigned char pchSig[10000];
  unsigned int nSize = 0;
  unsigned char hash;
  // printf("sizeof(hash) = %zu 字节\n", sizeof(hash)); 
  ECDSA_sign(0, (unsigned char*)&hash, 32, pchSig, &nSize, pkey);
}

EC_KEY* MakeNewKey(){
  EC_KEY *pkey = EC_KEY_new_by_curve_name(NID_secp256k1);
  if (!EC_KEY_generate_key(pkey))
    throw key_error("CKey::MakeNewKey() : EC_KEY_generate_key failed");
  const BIGNUM *privKey = EC_KEY_get0_private_key(pkey);
  if (privKey) {
    char *privKeyHex = BN_bn2hex(privKey);
    if (privKeyHex) {
      std::cout << privKeyHex << std::endl;
      OPENSSL_free(privKeyHex);
    }
  }
  return pkey;
}


int run(int argc, char *argv[]) {
  const int length = 16;
  unsigned char randomBytes[length];
  THC_hitme(0);
  THC_hitme(1);
  EC_KEY *pkey=MakeNewKey();
  Sign(pkey);
  return 0;
}
int main(int argc, char* argv[]){
   return run(argc,argv);
}

// g++ -o openssl_0.9.8c_ECDSA_sign_Check openssl_0.9.8c_ECDSA_sign_Check.cpp -I./openssl-0.9.8c-vuln/include -L./openssl-0.9.8c-vuln -lssl -lcrypto
// LD_LIBRARY_PATH=./openssl-0.9.8c-vuln/ ./openssl_0.9.8c_ECDSA_sign_Check