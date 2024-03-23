#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define GRAVITY 10
#define SIZE 10
#define N 1024 

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *win = NULL;
SDL_Renderer *ren = NULL;

const int n = N;
SDL_Rect parts[N] = { 0 };

void init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Can't init: %s\n", SDL_GetError());
        exit(1);
    }

    win = SDL_CreateWindow("Sandbox", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == NULL) {
		fprintf(stderr, "Can't create window: %s\n", SDL_GetError());
        exit(1);
    }

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == NULL) {
		fprintf(stderr, "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		exit(1);
	}
}

void quit()
{
	SDL_DestroyRenderer(ren);
	ren = NULL;

    SDL_DestroyWindow(win);
	win = NULL;
    
	SDL_Quit();
}

void loop()
{
	int x = 0, y = 0;
	bool pressed = false;
	int count = 0;
	Uint32 start = 0;

	// Main game loop
	bool run = true;
    while (run) {
		SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                run = false;
            if (e.type == SDL_MOUSEMOTION)
        		SDL_GetMouseState(&x, &y);
            if (e.type == SDL_MOUSEBUTTONDOWN)
				pressed = true;
			if (e.type == SDL_MOUSEBUTTONUP)
				pressed = false;
        }

		// Generate particles every 50 ms
		if (pressed) {
			if (SDL_GetTicks() - start > 50) {
				parts[count++] = (SDL_Rect){ x / SIZE * SIZE, y / SIZE * SIZE, SIZE, SIZE };
				start = SDL_GetTicks();
			}
		}

		// Detect collision for each particle
		for (int i = 0; i < n; i++) {
			SDL_Rect p = parts[i];

			bool collided = false;
			if (p.y + p.h >= SCREEN_HEIGHT || p.x + p.w >= SCREEN_WIDTH)
				collided = true;

			for (int j = 0; j < n; j++) {
				if (i == j)
					continue;

				// Clunky block to check collision by comparing particles' (rectangles') borders
				bool lcollision = (p.x + p.w > parts[j].x) && (p.x + p.w < parts[j].x + parts[j].w);
				bool rcollision = (p.x > parts[j].x) && (p.x < parts[j].x + parts[j].w);
				
				if ((p.y + p.h >= parts[j].y && p.y + p.h < parts[j].y + parts[j].h) ||
				(p.y >= parts[j].y && p.y < parts[j].y + parts[j].h)) {
					if (p.x == parts[j].x)
						p.x += rand() % 2 ? -1 : 1;
					else
						p.x += rcollision - lcollision;
				}
				
				if (p.y + p.h >= parts[j].y && p.y + p.h < parts[j].y + parts[j].h)
					collided |= lcollision || rcollision;
			}
			
			// Particle falls down if did not collide
			p.y += !collided * GRAVITY;

			// Update particle
			parts[i] = p;
		}
		
		// Render clear screen
		SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(ren);

		// Render sand particles
		SDL_SetRenderDrawColor(ren, 0x9E, 0x73, 0x3D, 0xFF);        
    	SDL_RenderFillRects(ren, parts, count);

		// Render cursor outlined box
		SDL_Rect outer = { x, y, 10, 10 };
		SDL_Rect inner = { x + 2, y + 2, 6, 6 };
		SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0xFF);        
    	SDL_RenderFillRect(ren, &outer);
		SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0x00);        
    	SDL_RenderFillRect(ren, &inner);

		// Draw everything on screen
		SDL_RenderPresent(ren);

		// Reuse particles if overflow
		if (count >= n) {
			for (int i = 0; i < n - 1; i++)
				parts[i] = parts[i + 1];
			parts[count = n - 1] = (SDL_Rect){ 0, 0, 0, 0 };
		}
    }
}

int main(int argc, char **args)
{
	init();
    
    loop();
    
	quit();

    return 0;
}
