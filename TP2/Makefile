CC = gcc
CFLAGS = -Wall -ansi
LDFLAGS = -lMLV
OBJ = Main.o ls.o file.o

##########################################################

tp2: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

####################

Main.o: Main.c ls.h
file.o: file.c file.h 
ls.o: ls.c ls.h file.h


%.o: %.c
	$(CC) -c $^ $(CFLAGS) $(LDFLAGS) 

##########################################################

clean:
	rm -f *.o
	rm -f *.gch

mrproper: clean
	rm -f tp2	
