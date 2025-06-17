
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
#include <openssl/bn.h>
#include <openssl/engine.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <openssl/trace.h>
#include <stdio.h>
#include <string.h>
#include <time.h> 

typedef int64_t int64;
typedef uint64_t uint64;
class key_error : public std::runtime_error {
public:
  explicit key_error(const std::string &str) : std::runtime_error(str) {}
};

inline int64 PerformanceCounter() {
  int64 nCounter = 0;
#ifdef __WXMSW__
  QueryPerformanceCounter((LARGE_INTEGER *)&nCounter);
#else
  timeval t;
  gettimeofday(&t, NULL);
  nCounter = t.tv_sec * 1000000 + t.tv_usec;
#endif
  return nCounter;
}
int64 GetTime() { return time(NULL); }

void RandAddSeed() {
  // Seed with CPU performance counter
  int64 nCounter = PerformanceCounter();
  nCounter = 1739519359111394;
  // printf("nCounter: %lld\n", nCounter);
  RAND_add(&nCounter, sizeof(nCounter), 1.5);
  memset(&nCounter, 0, sizeof(nCounter));
}
void RandAddSeedPerfmon() {
  RandAddSeed();

  // This can take up to 2 seconds, so only do it every 10 minutes
  static int64 nLastPerfmon;
  if (GetTime() < nLastPerfmon + 10 * 60)
    return;
  nLastPerfmon = GetTime();
}

uint64 GetRand(uint64 nMax)
{
    if (nMax == 0)
        return 0;

    // The range of the random source must be a multiple of the modulus
    // to give every possible output value an equal possibility
    uint64 nRange = (UINT64_MAX / nMax) * nMax;
    printf("nRange %ld\n", nRange); 
    uint64 nRand = 0;
    printf("sizeof(nRand) = %zu 字节\n", sizeof(nRand)); 
      do{
        printf("aaa\n");
        RAND_bytes((unsigned char*)&nRand, sizeof(nRand));
        }
    while (nRand >= nRange);
    return (nRand % nMax);
}
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
void My_RAND_bytes(int size){
  const int length = 16;
  unsigned char randomBytes[length];
  RAND_bytes(randomBytes, size);
}



int run(int argc, char *argv[]) {
  const int length = 16;
  unsigned char randomBytes[length];
  THC_hitme(0);
  RAND_add(NULL, 8, 1.5);
  RAND_add(NULL, 8, 1.5);
  EC_KEY *pkey=MakeNewKey();
  RAND_add(NULL, 8, 1.5);
  My_RAND_bytes(8);
  Sign(pkey);
  for (int i = 0; i < 17; i++){
    RAND_add(NULL, 8, 1.5);
    RAND_add(NULL, 4, 0.25);
    RAND_add(NULL, 4, 0.25);
  }
  MakeNewKey();
  return 0;
}
int main(int argc, char* argv[]){
   return run(argc,argv);
}