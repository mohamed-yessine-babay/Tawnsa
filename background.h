#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>


typedef struct
{
  SDL_Surface *image ;

  SDL_Rect   pos ;

}background;
typedef struct Time {
	SDL_Surface *msg;
	
        SDL_Rect positiontemps;
	int time;
	char timeString[10];
}Time;




void initback (background *bg,Mix_Music *musique);
void afficher_back(background bg,SDL_Surface *ecran);
void scrolling (background *bg,SDL_Rect *pos,int vitesse,int d);
void initpartage (background *bg1,background *bg2,Mix_Music *musique);
