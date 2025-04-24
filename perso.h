
#ifndef PERSO_H
#define PERSO_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

// Structure pour la vitesse
typedef struct {
    int dx;
    int dy;
} vitesse;



// Structure pour une animation (walk, jump, dead, etc.)
typedef struct {
    SDL_Surface *a;     // L’image contenant les sprites
    SDL_Rect pos;       // Position du sprite à afficher (dans la spritesheet)
    int index;          // Index actuel de l’animation
    int max;            // Nombre total de frames
    int speed;          // Vitesse de l'animation
    int sauter;         // Saut en cours (0 ou 1)
    int spriteH;        // Hauteur d’une frame
    int spriteW;        // Largeur d’une frame
} animation;

// Structure principale du personnage
typedef struct {
	
    int state;          // État optionnel (non utilisé dans ton main pour l’instant)
    animation walk;
    animation jump;
    animation dead;
	animation run;
	animation attack;
	animation walk1;
    animation jump1;
    animation dead1;
	animation run1;
	animation attack1;
    SDL_Rect posEcran;  // Position du perso sur l’écran
	SDL_Rect posEcran2;  
    SDL_Rect posScore;  // Position du score à l’écran
	SDL_Rect posScore2;
	SDL_Surface *etat_vie[4]; // 4 images pour les états de vie

    int health;
    int score;
    int step;
    vitesse v;
    int etat;           // 0 = normal, 1 = dead, 2 = jump
	int nb_morts;             // compteur de morts
	int up;
int direction1, direction2;

	
} perso;

// === Fonctions ===

// Initialisation et affichage du personnage
void init_perso(perso *p, SDL_Rect posEcran,perso *p2,SDL_Rect posEcran2);
void afficher_perso(SDL_Surface *ecran, perso *p) ;
void afficher_perso2(SDL_Surface *ecran, perso *p2) ;
// Affichage du score
void afficher_score(perso *p, SDL_Surface *ecran, SDL_Rect posScore, TTF_Font *font, SDL_Color textColor , perso *p2,SDL_Rect posScore2);
void afficher_vie(perso *p, SDL_Surface *ecran, perso *p2) ;
// Animation
void animer_perso(perso *p);
void animer_perso2(perso *p2);

void saut_Personnage(perso *p, Uint32 dt, int posx_absolu, int posy_absolu);
void saut_Perso(perso *p2, Uint32 dt, int posx_absolu1, int posy_absolu1);

#endif
