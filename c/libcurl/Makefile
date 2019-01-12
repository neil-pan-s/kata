CC = gcc
#CC = /usr/local/arm/4.4.3/bin/arm-linux-gcc

INCLUDE += -I./ -I./include/  -I./curl/
LIBS += -L./ ./lib/linux/libcurl.so.4.3.0 ./lib/linux/libssl.so.1.0.0  ./lib/linux/libcrypto.so.1.0.0 ./lib/linux/libssl.so.1.0.0

curl_test : libztcurl.so 
	$(CC) -g -Wall  -o curl_test main.c $(INCLUDE)  $(LIBS) -lztcurl

libztcurl.so :
	$(CC) -shared -fPIC -Wall  -o libztcurl.so libcurl_interface.c $(INCLUDE)  $(LIBS)
	
.PHONY : clean
clean:
	rm -rf *.o
	rm -rf curl_test
	rm -rf *.so
	
install:

