CC=gcc
CFLAGS=-g -Wall -DDEBUG

INCLUDE=-I./

LIBS= -lpthread

TARGET=portmap

all:store.o net.o log.o event.o worker.o main.o
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) $^ -o $(TARGET)

supervisor:supervisor.o
	$(CC) $(CFLAGS) $(INCLUDE) $^ -o $@
%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $<  -o $@


clean:
	rm -rf *.o
