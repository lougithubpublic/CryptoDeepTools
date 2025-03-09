  gcc -std=c99 -o cryptodeepbtcgenUDF cryptodeepbtcUDF.c -I./openssl-0.9.8c-vuln/include -L./openssl-0.9.8c-vuln -lssl -lcrypto


  LD_LIBRARY_PATH=./openssl-0.9.8c-vuln/ ./cryptodeepbtcgenUDF -n 32 -v 0