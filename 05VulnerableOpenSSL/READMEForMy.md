  gcc -std=c99 -o cryptodeepbtcgenUDF cryptodeepbtcUDF.c -I./openssl-0.9.8c-vuln/include -L./openssl-0.9.8c-vuln -lssl -lcrypto
  LD_LIBRARY_PATH=./openssl-0.9.8c-vuln/ ./cryptodeepbtcgenUDF -n 32 -v 0

  g++ openssl_0.9.8c_EC_KEY_generate_key.cpp -o openssl_0.9.8c_EC_KEY_generate_key  -I./openssl-0.9.8c-vuln/include -L./openssl-0.9.8c-vuln -lssl -lcrypto
  LD_LIBRARY_PATH=./openssl-0.9.8c-vuln/ ./openssl_0.9.8c_EC_KEY_generate_key



# openssl 处理
    git clone https://github.com/demining/CryptoDeepTools.git
    cd CryptoDeepTools/05VulnerableOpenSSL/
    apt-get update
    sudo apt-get install g++ -y
    sudo apt-get install libgmp3-dev libmpfr-dev -y
    wget https://mirror.math.princeton.edu/pub/openssl/source/old/0.9.x/openssl-0.9.8c.tar.gz
    tar xfz openssl-0.9.8c.tar.gz
    mv openssl-0.9.8c openssl-0.9.8c-vuln
    cd openssl-0.9.8c-vuln
    ls -lh
    patch -p1 <../make-OpenSSL-0-9-8c-vulnerable-again.diff
    ./Configure linux-x86_64 shared no-ssl2 no-ssl3 no-comp no-asm
    make depend all
    cd /
    ls
    cd content/CryptoDeepTools/05VulnerableOpenSSL/
    ls -lh



# 验证openssl漏洞对sign K值的影响
## 前置操作openssl里面添加输出k值代码
1.crypto/ecdsa/ecs_ossl.c  
    
    if (in_kinv == NULL || in_r == NULL)
		{
			if (!ECDSA_sign_setup(eckey, ctx, &kinv, &ret->r))
			{
				ECDSAerr(ECDSA_F_ECDSA_DO_SIGN,ERR_R_ECDSA_LIB);
				goto err;
			}
			printf("K值  BIGNUM 十六进制值: 0x%s\n", BN_bn2hex(kinv)); 
			ckinv = kinv;
		}
2.重新编译安装
3.调用签名方法
  gcc  -o openssl_0.9.8c_ECDSA_sign_Check openssl_0.9.8c_ECDSA_sign_Check.cpp -I./openssl-0.9.8c-vuln/include -L./openssl-0.9.8c-vuln -lssl -lcrypto
  LD_LIBRARY_PATH=./openssl-0.9.8c-vuln/ ./openssl_0.9.8c_ECDSA_sign_Check
