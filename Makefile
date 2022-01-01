all: uwu api

uwu: src/*.c src/*.h
	gcc -g -I.               src/*.c   -o uwu        -D_GNU_SOURCE -Wall -Wextra -ldl

.PHONY: std api

std: std/bool.so std/int.so std/str.so std/nil.so std/ref.so
api: api/api.so

std/%.so: std/%.c
	gcc -g -I. -shared -fpic $< -o $@ -D_GNU_SOURCE -Wall -Wextra

api/api.so: api/*.c api/*.h
	gcc -g -I. -shared -fpic api/*.c   -o api/api.so -D_GNU_SOURCE -Wall -Wextra
.PHONY: clean

clean:
	rm -rf std/*.so api/api.so uwu
