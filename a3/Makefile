SRC = main.c configureSerial.c
EXEC = serkom
CFLAGS = -Wall

serkom: $(SRC)
	gcc $(SRC) -o $(EXEC) $(CFLAGS) -O3

debug: $(SRC)
	gcc $(SRC) -o $(EXEC) $(CFLAGS) -DDEBUG 

clean:
	rm $(EXEC)