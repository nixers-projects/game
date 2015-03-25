#include <err.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

bool initImg()
{
        int flags = IMG_INIT_PNG|IMG_INIT_JPG;
        if(!(IMG_Init(flags) & flags))
        {
                errx(1,"Failed to initialize SDL_Image\nSDL ERROR: %s",IMG_GetError());
                return false;
        }
        return true;
}

SDL_Surface* loadImage(SDL_Surface* surf,char* path)
{
        SDL_Surface* optSurf = NULL;
        SDL_Surface* loadSurf = IMG_Load(path);
        if(loadSurf == NULL)
        {
                errx(1,"Could not load the image\nSDL ERROR: %s",IMG_GetError());
        }
        else
        {
                optSurf = SDL_ConvertSurface(loadSurf, surf->format,0);
                if(optSurf == NULL)
                {
                        errx(1,"Could not optimize the image\nSDL ERROR: %s",IMG_GetError());
                }
                SDL_FreeSurface(loadSurf);
        }
        return optSurf;
}
