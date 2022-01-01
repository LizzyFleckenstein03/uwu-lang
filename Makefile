all: uwu api/api.so

uwu: src/*.c src/*.h api/*.h common/*.h
	gcc -g -I.               src/*.c   -o uwu        -D_GNU_SOURCE -Wall -Wextra -ldl

api/api.so: api/*.c api/*.h common/*.h
	gcc -g -I. -shared -fpic api/*.c   -o api/api.so -D_GNU_SOURCE -Wall -Wextra

clean:
	rm -rf api/api.so uwu
