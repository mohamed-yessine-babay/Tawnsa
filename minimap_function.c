#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>
#include "head.h"

void init_Minimap(MiniMap* m)
{
    m->mp          = IMG_Load("mini plan de travail 1.png");
    m->mini_joueur = IMG_Load("mini joueur.png");
    m->mini_enemi  = IMG_Load("mini enemi.png");

    m->pos_mp.x = 10;  // coin de l'écran
    m->pos_mp.y = 10;

    m->pos_mini_joueur.x = 28;
    m->pos_mini_joueur.y = 100;

    m->pos_mini_enemi.x = 138;
    m->pos_mini_enemi.y = 100;
}


void MAJMinimap(SDL_Rect pos_joueur, MiniMap* m, SDL_Rect camera, int redimensionnement)
{
    SDL_Rect posABS_joueur;
    posABS_joueur.x = pos_joueur.x + camera.x;
    posABS_joueur.y = pos_joueur.y + camera.y;

    m->pos_mini_joueur.x = m->pos_mp.x + (posABS_joueur.x * redimensionnement) / 100 ;
    m->pos_mini_joueur.y = m->pos_mp.y + (posABS_joueur.y * redimensionnement) / 100 ;
}

void MAJMinimap_Enemi(SDL_Rect pos_enemi, MiniMap* m, SDL_Rect camera, int redimensionnement)
{
    SDL_Rect posABS_enemi;
    posABS_enemi.x = pos_enemi.x + camera.x;
    posABS_enemi.y = pos_enemi.y + camera.y;

    m->pos_mini_enemi.x = m->pos_mp.x + (posABS_enemi.x * redimensionnement) / 100 ;
    m->pos_mini_enemi.y = m->pos_mp.y + (posABS_enemi.y * redimensionnement) / 100 ;
}

void afficher(MiniMap* m, SDL_Surface* ecran)
{
    SDL_BlitSurface(m->mp, NULL, ecran, &m->pos_mp);
    SDL_BlitSurface(m->mini_joueur, NULL, ecran, &m->pos_mini_joueur);
    SDL_BlitSurface(m->mini_enemi, NULL, ecran, &m->pos_mini_enemi);
}

void Liberer(MiniMap* m)
{
    SDL_FreeSurface(m->mp);
    SDL_FreeSurface(m->mini_joueur);
    SDL_FreeSurface(m->mini_enemi);
}

// colision BB
int collision(SDL_Rect a, SDL_Rect b) 
{
    if (a.x + a.w < b.x) return 0;  // a est à gauche de b
    if (a.x > b.x + b.w) return 0;  // a est à droite de b
    if (a.y + a.h < b.y) return 0;  // a est au-dessus de b
    if (a.y > b.y + b.h) return 0;  // a est en-dessous de b
    return 1;  // Il y a collision
}



//colision parfaite
SDL_Color GetPixel(SDL_Surface *surface, int x, int y) 
{
    SDL_Color color = {255, 255, 255}; // Couleur par défaut (pas de collision)
    Uint32 col = 0;

    // Vérifie si les coordonnées sont dans la surface
    if (x < 0 || y < 0 || x >= surface->w || y >= surface->h) {
        return color;
    }

    // Verrouiller la surface si nécessaire
    if (SDL_MUSTLOCK(surface)) {
        SDL_LockSurface(surface);
    }

    char* pPosition = (char*) surface->pixels;
    pPosition += (surface->pitch * y);
    pPosition += (surface->format->BytesPerPixel * x);
    memcpy(&col, pPosition, surface->format->BytesPerPixel);

    SDL_GetRGB(col, surface->format, &color.r, &color.g, &color.b);

    if (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }

    return color;
}

int CollisionParfaite(SDL_Surface *masque, SDL_Rect pos_joueur) 
{
    if (!masque) return 0; // sécurité

    SDL_Color col;

    int px[8] = {
        pos_joueur.x,
        pos_joueur.x + pos_joueur.w / 2,
        pos_joueur.x + pos_joueur.w,
        pos_joueur.x,
        pos_joueur.x,
        pos_joueur.x + pos_joueur.w / 2,
        pos_joueur.x + pos_joueur.w,
        pos_joueur.x + pos_joueur.w
    };

    int py[8] = {
        pos_joueur.y,
        pos_joueur.y,
        pos_joueur.y,
        pos_joueur.y + pos_joueur.h / 2,
        pos_joueur.y + pos_joueur.h,
        pos_joueur.y + pos_joueur.h,
        pos_joueur.y + pos_joueur.h,
        pos_joueur.y + pos_joueur.h / 2
    };

    for (int i = 0; i < 8; i++) {
        col = GetPixel(masque, px[i], py[i]);
        if (col.r == 0 && col.g == 0 && col.b == 0) {
            return 1; // Collision détectée
        }
    }

    return 0; // Pas de collision
}


// animation 

SDL_Surface* TNT_surfaces[10]; // tableau pour les 10 images

void loadCollisionAnimation() {
    for (int i = 0; i < 10; i++) {
        char filename[20];
        sprintf(filename, "TNT %d.png", i + 1);
        TNT_surfaces[i] = IMG_Load(filename);
        if (TNT_surfaces[i] == NULL) {
            printf("Erreur chargement %s : %s\n", filename, SDL_GetError());
        }
    }
}

void handleCollisionAnimation(SDL_Surface* screen, SDL_Rect destRect) {
    for (int i = 0; i < 10; i++) {
        SDL_BlitSurface(TNT_surfaces[i], NULL, screen, &destRect);
        SDL_Flip(screen); // Mets à jour l'affichage
        SDL_Delay(25);;   // Attends 100 ms entre chaque frame
    }
}
