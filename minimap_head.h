#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>  // pour SDL_Texture et IMG_LoadTexture

typedef struct
{
    SDL_Surface* mp;        // image de la minimap
    SDL_Rect pos_mp;        // position de la minimap sur l'écran

    SDL_Surface* mini_joueur; // image du joueur miniature 
    SDL_Rect pos_mini_joueur;

    SDL_Surface* mini_enemi;  // image de l'ennemi miniature
    SDL_Rect pos_mini_enemi;
} MiniMap;

typedef struct
{
  SDL_Surface* map;
  SDL_Rect pos_map;

}Map;

typedef struct // n'inclu pas la tache
{
  SDL_Surface* joueur;
  SDL_Rect pos_joueur;

}Joueur;

typedef struct // n'inclu pas la tache
{
  SDL_Surface* enemi;
  SDL_Rect pos_enemi;

}Enemi;

//mini map et sa mise à jour
void init_Minimap(MiniMap* m);
void MAJMinimap(SDL_Rect pos_joueur, MiniMap* m, SDL_Rect camera, int redimensionnement);
void MAJMinimap_Enemi(SDL_Rect pos_enemi, MiniMap* m, SDL_Rect camera, int redimensionnement);
void afficher(MiniMap* m, SDL_Surface* ecran);
void Liberer(MiniMap* m);

// colision BB
int collision(SDL_Rect a, SDL_Rect b);

// colision parfaite
SDL_Color GetPixel(SDL_Surface *surface, int x, int y);
int CollisionParfaite(SDL_Surface *masque, SDL_Rect pos_joueur);

//animation
extern SDL_Surface* TNT_surfaces[10]; // remplace SDL_Texture* par SDL_Surface*

void loadCollisionAnimation();
void handleCollisionAnimation(SDL_Surface* screen, SDL_Rect destRect);

#endif // HEAD_H_INCLUDED
