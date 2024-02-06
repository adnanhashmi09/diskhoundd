CFLAGS= -Wall -pedantic -std=gnu99
 
all: diskhound
 
diskhound:
	gcc $(CFLAGS) `pkg-config --cflags --libs libnotify` main.c -o build/diskhoundd
