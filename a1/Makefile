SRC = main.c
EXEC = miwe
CFLAGS = -Wall

miwe: $(SRC)
	gcc $(SRC) -o $(EXEC) $(CFLAGS) -O3

debug:
	gcc $(SRC) -o $(EXEC) $(CFLAGS) -DDEBUG 

clean:
	rm $(EXEC)