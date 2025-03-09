for num in $(seq 0 53); do
    echo $num
    LD_LIBRARY_PATH=./openssl-0.9.8c-vuln/ ./cryptodeepbtcgen -n 200 -v $num >> result_all
done