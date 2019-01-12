CC = gcc
#CC = /usr/local/arm/4.4.3/bin/arm-linux-gcc

INCLUDE += -I./ -I./include/  -I./openssl/ 
LIBS += -L./ ./lib/linux/libcrypto.so.1.0.0 ./lib/linux/libssl.so.1.0.0

openssl_test : libztssl.so 
	$(CC) -g -Wall -DZT_DEBUG -o openssl_test main.c $(INCLUDE)  $(LIBS) -lztssl
#	$(CC) -g -Wall -o openssl_test main.c openssl_interface.c $(INCLUDE)  $(LIBS)

libztssl.so :
	$(CC) -shared -fPIC -Wall -DZT_DEBUG -o libztssl.so openssl_interface.c $(INCLUDE)  $(LIBS)
	
.PHONY : clean
clean:
	rm -rf *.o
	rm -rf openssl_test
	rm -rf *.so
	rm -rf *.pem
	
install:

