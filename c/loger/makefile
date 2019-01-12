CC = gcc
#CC = /usr/local/arm/4.4.3/bin/arm-linux-gcc

INCLUDE += -I./ -I../mutex/ 
LIBS += -L./ -L../mutex/ -lztmutex -lpthread

TARGET = loger_test

$(TARGET) : 
	$(CC) -g -Wall  -o $(TARGET)  main.c ztloger.c $(INCLUDE)  $(LIBS) 	

.PHONY : clean
clean:
	rm -rf *.o
	rm -rf $(TARGET) 
	rm -rf *.so
	
install:

