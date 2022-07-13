all: logs-parse.o test

logs-parse.o: logs-parse.c
	clang -c -lcjson -lcurl logs-parse.c

test: test.c
	clang -lcjson -lcurl -o binout test.c logs-parse.o
