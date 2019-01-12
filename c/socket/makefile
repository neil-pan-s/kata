CC = gcc
#CC = /usr/local/arm/4.4.3/bin/arm-linux-gcc

INCLUDE += -I./  -I../mutex
LIBS += -L./  -L../mutex -lztmutex
SRC =  ztsocket.c 

TARGET = 
TARGETLIB = libztsocket.so

$(TARGETLIB) :
	$(CC) -shared -fPIC -Wall  -o $(TARGETLIB)  $(SRC) $(INCLUDE)  $(LIBS)
	
.PHONY : clean
clean:
	rm -rf *.o
	rm -rf $(TARGET) 
	rm -rf *.so
	
install:

