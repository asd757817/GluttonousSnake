CC=gcc
CFLAGS:=-lpthread -lncurses
SRC_PATH=src
exe:=snake
obj:=main.o snake.o env.o


all: $(obj)
	$(CC) -o $(exe) $(obj) $(CFLAGS)
	rm *.o

%.o: $(SRC_PATH)/%.c
	 $(CC) -c $^ -o $@

clean:
	rm *.o
	rm snake
