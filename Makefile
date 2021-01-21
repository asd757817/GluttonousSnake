CC=gcc
CFLAGS:=-lpthread -lncurses
exe:=snake
obj:=main.o snake.o 

all: $(obj)
	$(CC) -o $(exe) $(obj) $(CFLAGS)

%.o:%.c
	 $(CC) -c $^ -o $@

clean:
	rm *.o
	rm snake
