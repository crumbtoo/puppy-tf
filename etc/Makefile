all: ssfetch.so qcurl.so

qcurl.so: qcurl.c
	clang $(shell pkg-config --libs --cflags libcurl) -shared -fPIC -o qcurl.so qcurl.c

ssfetch.so: ssfetch.c
	clang $(shell pkg-config --libs --cflags luajit) -I../deps/libssq/include/ -I../deps/ -shared -fPIC -o ssfetch.so ssfetch.c ../deps/libssq/build/libssq.a


.PHONY:
clean:
	rm -rf *.so
