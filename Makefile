BIN=bin/client  bin/server


SRCS0=client.c
SRCS1=server.c

default: $(BIN)

obj/%.o: %.c
	gcc -Wall -Iinclude -c $< -o $@

bin/client: $(SRCS0:%.c=obj/%.o)
	gcc -o $@ $+

bin/server: $(SRCS1:%.c=obj/%.o)
	gcc -o $@ $+

clean:
	rm -f $(BIN) obj/*.o *~

