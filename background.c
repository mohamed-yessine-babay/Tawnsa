#include "background.h"
#include <SDL/SDL_ttf.h>



//////////////////////////////////////////////////////////////
void initback (background *bg,Mix_Music *musique){
  bg->image = IMG_Load("lvl1.png");
  if (bg->image==NULL)
  	{
  	printf("Unable to load background : %s\n" , IMG_GetError());
    }
  bg->pos.x = 0;
  bg->pos.y = 0;
  Mix_VolumeMusic(MIX_MAX_VOLUME / 2); //Mettre le volume à la moitié
  //Mix_Music *musique; //Création d'un pointeur de type Mix_Music
  musique = Mix_LoadMUS("musique.mp3"); //Chargement de la musique
  Mix_PlayMusic(musique, -1);


}
//////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////
void afficher_back(background bg,SDL_Surface *ecran){
  SDL_BlitSurface (bg.image,NULL,ecran,&bg.pos);




}
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
void scrolling(background *bg, SDL_Rect *pos, int vitesse, int d) {
    // Scroll vers la droite (d == 0)
    if (d == 0) {
        if (pos->x > 1800 && bg->pos.x < bg->image->w - 1920) { // 620 = largeur de l'écran
            bg->pos.x -= vitesse;
            pos->x -= vitesse;
        }
    }

    // Scroll vers la gauche (d == 1)
    else if (d == 1) {
        bg->pos.x += vitesse;
        if (bg->pos.x > 0) {
            bg->pos.x = 0;
        }
    }

    // Scroll vers le haut (d == 2)
    else if (d == 2) {
        bg->pos.y -= vitesse;
        if (bg->pos.y < 0) { // Limite de défilement vers le haut
            bg->pos.y = 0;
        }
    }

    // Scroll vers le bas (d == 3)
    else if (d == 3) {
        if (bg->pos.y < bg->image->h - 1080) { // 250 = hauteur de l’écran
            bg->pos.y += vitesse;
        }
    }
}



//////////////////////////////////////////////////////////////
void initpartage (background *bg1,background *bg2,Mix_Music *musique)
{
  bg1->image = IMG_Load("partage.png");
  bg2->image = IMG_Load("partage.png");

  if ((bg1->image==NULL)||(bg2->image==NULL))
  	{
  	printf("Unable to load partage background : %s\n" , IMG_GetError());
    }

  bg1->pos.x = 0;
  bg1->pos.y = 0;
  bg2->pos.x = 960;
  bg2->pos.y = 0;
  Mix_VolumeMusic(MIX_MAX_VOLUME / 2); //Mettre le volume à la moitié
  //Mix_Music *musique; //Création d'un pointeur de type Mix_Music
  musique = Mix_LoadMUS("musique.mp3"); //Chargement de la musique
  Mix_PlayMusic(musique, -1);
}
