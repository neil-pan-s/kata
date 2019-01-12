CC = gcc
#CC = /usr/local/arm/4.4.3/bin/arm-linux-gcc

INCLUDE += -I./ -I./include/ 
LIBS += -L./ -lztcstring

TARGET = cstring_test
TARGETLIB = libztcstring.so
SRC = ztstring.c

$(TARGET) : $(TARGETLIB)
	$(CC) -g -Wall  -o $(TARGET)   main.c $(INCLUDE)  $(LIBS) 

$(TARGETLIB) :
	$(CC) -shared -fPIC -Wall  -o $(TARGETLIB)  $(SRC) $(INCLUDE) 
	
.PHONY : clean
clean:
	rm -rf *.o
	rm -rf $(TARGET) 
	rm -rf *.so
	
install:

