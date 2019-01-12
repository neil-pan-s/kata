CC = gcc
#CC = /usr/local/arm/4.4.3/bin/arm-linux-gcc

INCLUDE += -I./ 
LIBS += -L./ 

TARGET = file_test

$(TARGET) : 
	$(CC) -g -Wall  -o $(TARGET)  main.c ztfile.c $(INCLUDE)  $(LIBS) 	

.PHONY : clean
clean:
	rm -rf *.o
	rm -rf $(TARGET) 
	rm -rf *.so
	
install:

