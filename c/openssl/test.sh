make clean
make
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./lib/linux/
./openssl_test 
