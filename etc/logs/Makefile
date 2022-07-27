OBJS=logs-parse.o logs-gfx.o 
CFLAGS=$(shell pkg-config --libs --cflags pangocairo) -lcjson -Wall -Wno-unused-command-line-argument

all: $(OBJS) llogsTF.so


logs-parse.o: logs-parse.c
	clang -c $(CFLAGS) logs-parse.c

logs-gfx.o: logs-gfx.c
	clang -c $(CFLAGS) logs-gfx.c

llogsTF.so: llogsTF.c
	clang llogsTF.c $(OBJS) -o llogsTF.so -shared -fPIC $(CFLAGS) $(shell pkg-config --libs --cflags luajit) -L.. -l:qcurl.so

test: test.c
	clang -o binout $(CFLAGS) test.c $(OBJS)

.PHONY:
clean:
	rm -rf *.o
	rm -rf binout
	rm -rf *.so

