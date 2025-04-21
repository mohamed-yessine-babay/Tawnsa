#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "head.h"
#include <stdlib.h>
#include <stdio.h>
#define NB_FRAMES 6  // <== Ajoute cette ligne pour corriger l'erreur

int main(int argc, char** argv)
{
    // Initialisation SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur SDL_Init : %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* ecran = SDL_SetVideoMode(1300, 640, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!ecran) {
        printf("Erreur SetVideoMode : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_WM_SetCaption("MiniMap - Mouvement Joueur + Ennemi", NULL);

    // Allocation mémoire
    Map* M1 = malloc(sizeof(Map));
    Joueur* J = malloc(sizeof(Joueur));
    Enemi* E = malloc(sizeof(Enemi));
    MiniMap* Mi1 = malloc(sizeof(MiniMap));

    // Chargement des images
    M1->map = IMG_Load("Plan de travail 1.png");
    J->joueur = IMG_Load("joueur.png");
    E->enemi = IMG_Load("enemi.png");

    SDL_Surface* masque = IMG_Load("masque 1.png");
    if (!M1->map || !J->joueur || !E->enemi || !masque) {
        printf("Erreur chargement d'images.\n");
        return 1;
    }

    // Chargement animation collision
    loadCollisionAnimation();

    // Position initiale
    M1->pos_map.x = 0;
    M1->pos_map.y = 0;
    J->pos_joueur.x = 90;
    J->pos_joueur.y = 448;
    E->pos_enemi.x = 640;
    E->pos_enemi.y = 448;

    init_Minimap(Mi1);

    SDL_Rect camera = {0, 0};
    int redimensionnement = 20;
    int paly = 1;
    int keys[4] = {0, 0, 0, 0};
    int direction_enemi = 1;
    int PV = 3;

    SDL_Event event;

    while (paly)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                paly = 0;
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_RIGHT: keys[0] = 1; break;
                    case SDLK_LEFT:  keys[1] = 1; break;
                    case SDLK_UP:    keys[2] = 1; break;
                    case SDLK_DOWN:  keys[3] = 1; break;
                    case SDLK_r:
                        J->pos_joueur.x = 90;
                        J->pos_joueur.y = 448;
                        E->pos_enemi.x = 640;
                        E->pos_enemi.y = 448;
                        camera.x = 0;
                        camera.y = 0;
                        PV = 3;
                        break;
                }
            } else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_RIGHT: keys[0] = 0; break;
                    case SDLK_LEFT:  keys[1] = 0; break;
                    case SDLK_UP:    keys[2] = 0; break;
                    case SDLK_DOWN:  keys[3] = 0; break;
                }
            }
        }

        // Mouvement avec collision parfaite
        SDL_Rect future_pos = J->pos_joueur;
        if (keys[0]) future_pos.x += 5;
        if (keys[1]) future_pos.x -= 5;
        if (keys[2]) future_pos.y -= 5;
        if (keys[3]) future_pos.y += 5;

        if (!CollisionParfaite(masque, future_pos)) {
            J->pos_joueur = future_pos;
        }

        // Mouvement ennemi auto
        if (direction_enemi == 1) {
            E->pos_enemi.x += 2;
            if (E->pos_enemi.x >= 960)
                direction_enemi = -1;
        } else {
            E->pos_enemi.x -= 2;
            if (E->pos_enemi.x <= 640)
                direction_enemi = 1;
        }

        // Collision joueur/ennemi
        if (collision(J->pos_joueur, E->pos_enemi)) {
            PV--;
            printf("Collision! Vies restantes: %d\n", PV);

            // Calcul point de contact
            SDL_Rect contact;
            contact.x = (J->pos_joueur.x > E->pos_enemi.x) ? J->pos_joueur.x : E->pos_enemi.x;
            contact.y = (J->pos_joueur.y > E->pos_enemi.y) ? J->pos_joueur.y : E->pos_enemi.y;
            contact.w = (J->pos_joueur.x + J->joueur->w < E->pos_enemi.x + E->enemi->w ?
                        J->pos_joueur.x + J->joueur->w : E->pos_enemi.x + E->enemi->w) - contact.x;
            contact.h = (J->pos_joueur.y + J->joueur->h < E->pos_enemi.y + E->enemi->h ?
                        J->pos_joueur.y + J->joueur->h : E->pos_enemi.y + E->enemi->h) - contact.y;

            SDL_Rect explosion_pos;
            explosion_pos.x = contact.x + contact.w / 2 - TNT_surfaces[0]->w / 2;
            explosion_pos.y = contact.y + contact.h / 2 - TNT_surfaces[0]->h / 2;

            // Recul joueur
            if (J->pos_joueur.x < E->pos_enemi.x) J->pos_joueur.x -= 30;
            else if (J->pos_joueur.x > E->pos_enemi.x) J->pos_joueur.x += 30;
            if (J->pos_joueur.y < E->pos_enemi.y) J->pos_joueur.y -= 30;
            else if (J->pos_joueur.y > E->pos_enemi.y) J->pos_joueur.y += 30;

            // Animation simultanée
            for (int i = 0; i < NB_FRAMES; i++) {
                SDL_BlitSurface(M1->map, NULL, ecran, &M1->pos_map);
                SDL_BlitSurface(J->joueur, NULL, ecran, &J->pos_joueur);
                SDL_BlitSurface(E->enemi, NULL, ecran, &E->pos_enemi);
                SDL_BlitSurface(TNT_surfaces[i], NULL, ecran, &explosion_pos);
                afficher(Mi1, ecran);
                SDL_Flip(ecran);
                SDL_Delay(25);
            }

            if (PV == 0) {
                printf("Game Over! Vous avez perdu toutes vos vies.\n");
                paly = 0;
            }
        }

        MAJMinimap(J->pos_joueur, Mi1, camera, redimensionnement);
        MAJMinimap_Enemi(E->pos_enemi, Mi1, camera, redimensionnement);

        SDL_BlitSurface(M1->map, NULL, ecran, &M1->pos_map);
        SDL_BlitSurface(J->joueur, NULL, ecran, &J->pos_joueur);
        SDL_BlitSurface(E->enemi, NULL, ecran, &E->pos_enemi);
        afficher(Mi1, ecran);

        SDL_Flip(ecran);
        SDL_Delay(16);
    }

    SDL_FreeSurface(M1->map);
    SDL_FreeSurface(J->joueur);
    SDL_FreeSurface(E->enemi);
    SDL_FreeSurface(masque);
    Liberer(Mi1);
    free(M1); free(J); free(E); free(Mi1);
    SDL_Quit();
    return 0;
}
