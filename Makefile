all:
	gcc main.c -o main `sdl2-config --cflags --libs`

clean:
	rm main