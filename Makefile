# define more variables so it is easier to make changes
CC=cc
CFLAGS=-g -Wall -Werror -std=c99
TARGETS=tacmini

all: $(TARGETS)

#Static Pattern Rules
$(TARGETS): % : %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf *.o *~ $(TARGETS)
