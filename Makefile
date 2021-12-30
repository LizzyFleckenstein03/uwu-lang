all: uwu std api

uwu: src/*.c src/*.h
	gcc -g src/*.c -o uwu -ldl -D_GNU_SOURCE

.PHONY: std api

std: std/bool.so std/int.so std/str.so std/nil.so std/ref.so
api: api/api.so

std/%.so: std/%.c
	gcc -g -shared -fpic $< -o $@ -D_GNU_SOURCE

api/api.so: api/*.c api/*.h
	gcc -g -shared -fpic api/*.c -o api/api.so -D_GNU_SOURCE

.PHONY: clean

clean:
	rm -rf std/*.so api/api.so uwu
