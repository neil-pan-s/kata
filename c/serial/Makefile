CC = gcc
#CC = /usr/local/arm/4.4.3/bin/arm-linux-gcc

INCLUDE += -I./  
LIBS += -L./  
SRC =  ztserial.c 

TARGET = 
TARGETLIB = libztserial.so

$(TARGETLIB) :
	$(CC) -shared -fPIC -Wall  -o $(TARGETLIB)  $(SRC) $(INCLUDE)  $(LIBS)
	
.PHONY : clean
clean:
	rm -rf *.o
	rm -rf $(TARGET) 
	rm -rf *.so
	
install:

