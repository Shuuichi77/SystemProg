CC = gcc
CFLAGS = -Wall -pedantic -ansi
LDFLAGS = 

##########################################################

all:
	@make exo1
	@make exo2
	@make exo3
	@make exo4
	@make exo5

#####################

$(EXEC): $(EXEC).o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	
$(EXEC).o: $(EXEC).c

%.o: %.c
	$(CC) -c $^ $(CFLAGS) $(LDFLAGS) 

##########################################################

clean:
	rm -f *.o

mrproper: clean
	rm -f exo1 exo2 exo3 exo4 exo5
