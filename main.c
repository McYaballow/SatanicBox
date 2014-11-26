#include <SDL2/SDL.h>
#include "globals.h"
#include "drawTable.h"

typedef struct Axis
{
	double pos; // position
	double vel; // velocity
	double acc; // accleration
} Axis;

typedef struct Kappale
{
	Axis x, y;
} Kappale;

void initKappale(Kappale * kappale) // alkuarvot nolliksi
{
	kappale->x.pos = 0;
	kappale->x.vel = 0;
	kappale->x.acc = 0;
	kappale->y.pos = 0;
	kappale->y.vel = 0;
	kappale->y.acc = 0;
}

void advanceFrame(Kappale * kappale)
{
	kappale->x.pos += (kappale->x.vel * FRAMEDUR) + 0.5 * (kappale->x.acc) * FRAMEDUR * FRAMEDUR;
	kappale->y.pos += (kappale->y.vel * FRAMEDUR) + 0.5 * (kappale->y.acc) * FRAMEDUR * FRAMEDUR;
	kappale->x.vel += kappale->x.acc * FRAMEDUR;
	kappale->y.vel += kappale->y.acc * FRAMEDUR;
}

void drawBox(Kappale * kappale, SDL_Renderer * renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_Rect kaide;
	kaide.w = 10;
	kaide.h = 10;
	/*while(kappale->x.pos <= 0)
		kappale->x.pos += WIDTH -10;
	while(kappale->x.pos > WIDTH -10)
		kappale->x.pos -= WIDTH -10;
	while(kappale->y.pos <= 0)
		kappale->y.pos += HEIGTH -10;
	while(kappale->y.pos > HEIGTH -10)
		kappale->y.pos -= HEIGTH -10;*/


	while(kappale->x.pos < 0)
	{
		kappale->x.pos *= -1;
		kappale->x.vel *= -1;
	}
	while(kappale->x.pos > WIDTH -10)
	{
		kappale->x.pos *= -1;
		kappale->x.pos += 2*(WIDTH -10);
		kappale->x.vel *= -1;
	}
	while(kappale->y.pos < 0)
	{
		kappale->y.pos *= -1;
		kappale->y.vel *= -1;
	}
	while(kappale->y.pos > HEIGTH -10)
	{
		kappale->y.pos *= -1;
		kappale->y.pos += 2*(HEIGTH -10);
		kappale->y.vel *= -1;
	}

	kaide.x = (int)(kappale->x.pos);
	kaide.y = (int)(kappale->y.pos);

	SDL_RenderFillRect(renderer, &kaide);
	SDL_RenderPresent(renderer);
}

int main(int argc, char *args[])
{
	SDL_Window *ikkuna = SDL_CreateWindow("Square test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGTH, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
	SDL_Renderer *renderoija = SDL_CreateRenderer(ikkuna, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_ShowCursor(0);
	Kappale boxi;
	initKappale(&boxi);

	SDL_Event tila;
	char quit = FALSE;

	struct KeyState
	{
		char S_UP;
		char S_DOWN;
		char S_LEFT;
		char S_RIGHT;
	};
	struct KeyState nappiTila = {0,0,0,0};
	while(!quit)
	{
		while(SDL_PollEvent(&tila) != 0)
		{
			if(tila.type == SDL_QUIT)
				quit = TRUE;
			else if(tila.type == SDL_KEYDOWN)
			{
				switch(tila.key.keysym.sym)
				{
					case SDLK_RIGHT:
						if(!nappiTila.S_RIGHT)
						{
							boxi.x.acc += ACC;
							nappiTila.S_RIGHT = 1;
						}
						break;
					case SDLK_LEFT:
						if(!nappiTila.S_LEFT)
						{
							boxi.x.acc -= ACC;
							nappiTila.S_LEFT = 1;
						}
						break;
					case SDLK_UP:
						if(!nappiTila.S_UP)
						{
							boxi.y.acc -= ACC;
							nappiTila.S_UP = 1;
						}
						break;
					case SDLK_DOWN:
						if(!nappiTila.S_DOWN)
						{
							boxi.y.acc += ACC;
							nappiTila.S_DOWN = 1;
						}
						break;
					case SDLK_ESCAPE:
						quit = TRUE;
						break;
				}
			}
			else if(tila.type == SDL_KEYUP)
			{
				switch(tila.key.keysym.sym)
				{
					case SDLK_RIGHT:
						if(nappiTila.S_RIGHT)
						{
							boxi.x.acc -= ACC;
							nappiTila.S_RIGHT = 0;
						}
						break;
					case SDLK_LEFT:
						if(nappiTila.S_LEFT)
						{
							boxi.x.acc += ACC;
							nappiTila.S_LEFT = 0;
						}
						break;
					case SDLK_UP:
						if(nappiTila.S_UP)
						{
							boxi.y.acc += ACC;
							nappiTila.S_UP = 0;
						}
						break;
					case SDLK_DOWN:
						if(nappiTila.S_DOWN)
						{
							boxi.y.acc -= ACC;
							nappiTila.S_DOWN = 0;
						}
						break;
				}
			}
		}
		drawBox(&boxi, renderoija);
		advanceFrame(&boxi);
	}
	SDL_DestroyRenderer(renderoija);
	SDL_DestroyWindow(ikkuna);
	SDL_Quit();
	return 0;
}
