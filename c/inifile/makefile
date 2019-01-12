CC = gcc
#CC = /usr/local/arm/4.4.3/bin/arm-linux-gcc

INCLUDE += -I./ -I../cstring -I../mutex
LIBS += -L./ -L../cstring -lztcstring -L../mutex -lztmutex -lpthread
SRC =  ztinifile.c 

TARGET = ztinifile_test
TARGETLIB = libztini.so

$(TARGET) : $(TARGETLIB)
	$(CC) -g -Wall  -o $(TARGET)   main.c $(INCLUDE)  $(LIBS) -lztini

$(TARGETLIB) :
	$(CC) -shared -fPIC -Wall  -o $(TARGETLIB)  $(SRC) $(INCLUDE)  $(LIBS)
	
.PHONY : clean
clean:
	rm -rf *.o
	rm -rf $(TARGET) 
	rm -rf *.so
	
install:

