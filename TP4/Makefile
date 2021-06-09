CC = gcc
CFLAGS = -Wall -pedantic -ansi
LDFLAGS = 

##########################################################

all:
	@make exo1.1
	@make exo1.2
	@make exo2
	@make mrun
	@make exo3
	@make exo4
	@make exo5
	@make exo6

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
	rm -f exo1.1 exo1.2 exo2 mrun exo3 exo4 exo5 exo6
