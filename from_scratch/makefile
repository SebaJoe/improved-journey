CC = g++
rc = $(wildcard *.cpp)
obj = $(src:.c=.o)

LDFLAGS = -Wall -g

myprog: $(obj)
	$(CC) $(rc) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) myprog
