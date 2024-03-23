all:
	gcc main.c -o sandbox `sdl2-config --cflags --libs`

clean:
	rm sandbox
