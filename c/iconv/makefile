CC = gcc
#CC = /usr/local/arm/4.4.3/bin/arm-linux-gcc

INCLUDE += -I./ -I./include/ 
LIBS += -L./ ./lib/linux/libiconv.so 

TARGET = iconv_test

$(TARGET) : 
	$(CC) -g -Wall  -o $(TARGET)  zticonv.c main.c $(INCLUDE)  $(LIBS) -ldl

.PHONY : clean
clean:
	rm -rf *.o
	rm -rf $(TARGET) 
	rm -rf *.so
	
install:

