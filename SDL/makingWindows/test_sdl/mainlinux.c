#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
// #include <Windows.h>

bool Run(SDL_Event *event) {
	bool running = true;

	switch (event->type) {
		case SDL_WINDOWEVENT:
		{
			switch (event->window.event)
			{
				case SDL_WINDOWEVENT_RESIZED:
				{
					printf("Window %d resized to %dx%d.\n", 
						event->window.windowID,
						event->window.data1,
						event->window.data2);
				} break;
			}
		} break;

		case SDL_QUIT:
		{
			// Minor change
			printf("SDL_QUIT event raised!\n");
			running = false;
			SDL_Delay(1000);
		} break;
	}

	return(running);
}

int main(int argc, char **argv) {

	char *windowTite = "main window";

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		char strErr[140];
		sprintf(strErr, "SDL_Init failed: %s\n", SDL_GetError());
		printf(strErr);
		return (-1);
	}

	SDL_Window *window = SDL_CreateWindow(
		windowTite,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_RESIZABLE
		);

	if(!window)
	{
		char strErr[140];
		sprintf(strErr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
		printf(strErr);
		return (-1);
	}

	SDL_Event event;
	do { SDL_WaitEvent(&event); } while (Run(&event));

	SDL_Quit();

	return (0);
}
