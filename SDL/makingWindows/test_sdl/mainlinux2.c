#include <SDL.h>
#include <stdbool.h>

static bool running = true;

int main(int argc, char **argv) {
  char *windowTitle = "dev / main window";

  if (SDL_Init(SDL_INIT_VIDEO) < 0){
    SDL_Log("SDL_Init failed: %s\n", SDL_GetError());
    return (-1);
  }

  SDL_Window *window = SDL_CreateWindow(  windowTitle,
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          640,
                                          480,
                                          SDL_WINDOW_RESIZABLE    );

  if(!window) {
    SDL_Log("SDL_CreateWindow failed: %s\n", SDL_GetError());
    return (-1);
  }

  while(running){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
      switch (event.type) {
        case SDL_WINDOWEVENT:{
          switch (event.window.event){
            case SDL_WINDOWEVENT_RESIZED:{
              SDL_Log(  "Window %d resized to %dx%d.\n", 
                        event.window.windowID,
                        event.window.data1,
                        event.window.data2             );

              SDL_Surface *screen = SDL_GetWindowSurface(window);

              static bool white = true;
              if(white) SDL_FillRect(screen, 0, 0x00ff0000);
              else      SDL_FillRect(screen, 0, 0x000000ff);	
              white = !white;

              if(SDL_UpdateWindowSurface(window))
                SDL_Log("Failed to update window surface:%s", SDL_GetError());

            } break;
          }
        } break;

        case SDL_QUIT:{
          SDL_Log("SDL_QUIT event raised!\n");
          running = false;
        } break;
      }
    }	
  }
  // SDL_Quit(); // SDL_Quit() raises anyway when you try to close the window... so... fuck it.
  return (0);
}
