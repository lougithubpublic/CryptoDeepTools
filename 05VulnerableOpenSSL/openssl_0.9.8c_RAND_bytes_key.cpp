#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/ec.h>
#include <openssl/rand.h>
#include <openssl/pem.h>
#include <openssl/ripemd.h>


// 打印字节数组
void printBytes(const unsigned char* bytes, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        std::cout << std::hex << static_cast<int>(bytes[i]);
    }
    std::cout << std::endl;
}

int main() {
    for (int i = 0; i < 1; i++) {
    // 初始化 OpenSSL 的随机数生成器
    // if (RAND_load_file("/dev/urandom", 1024) != 1024) {
    //     std::cerr << "Failed to load random seed." << std::endl;
    //     return 1;
    // }
    THC_hitme(0);       // Reset state
    THC_hitme(20);
    const int length = 16; // 生成 16 字节的随机数
    
    unsigned char randomBytes[length];

    // 生成随机字节
    if (RAND_bytes(randomBytes, length) != 1) {
        // 错误处理
        ERR_print_errors_fp(stderr);
        std::cerr << "Failed to generate random bytes." << std::endl;
        return 1;
    }

    // 打印生成的随机字节
    printBytes(randomBytes, length);
}
    return 0;
}