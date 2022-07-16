OBJS=logs-parse.o logs-gfx.o
all: $(OBJS) test

logs-parse.o: logs-parse.c
	clang -c -lcjson logs-parse.c

logs-gfx.o: logs-gfx.c
	clang -c $(shell pkg-config --libs --cflags pangocairo) logs-gfx.c


test: test.c
	clang -lcjson $(shell pkg-config --libs --cflags pangocairo) -lcurl -o binout test.c $(OBJS)
