OBJS=logs-parse.o logs-gfx.o
CFLAGS=$(shell pkg-config --libs --cflags pangocairo) -lcjson -Wall -Wno-unused-command-line-argument

all: $(OBJS) test

logs-parse.o: logs-parse.c
	clang -c $(CFLAGS) logs-parse.c

logs-gfx.o: logs-gfx.c
	clang -c $(CFLAGS) logs-gfx.c


test: test.c
	clang -o binout $(CFLAGS) test.c $(OBJS)
