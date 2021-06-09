CC = gcc
CFLAGS = -Wall -pedantic -ansi
LDFLAGS = 

##########################################################

all:
	@make exo1
	@make exo2
	@make exo3
	@make exo4_read
	@make exo4_write
	@make dispatch
	@make addition
	@make multiplication
	@make soustraction

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
	rm -f exo1 exo2 exo3 exo4_read exo4_write dispatch addition multiplication soustraction
