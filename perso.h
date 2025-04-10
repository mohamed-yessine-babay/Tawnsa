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
	animation walk1;
    animation jump1;
    animation dead1;
	animation run1;

    SDL_Rect posEcran;  // Position du perso sur l’écran
	SDL_Rect posEcran2;  
    SDL_Rect posScore;  // Position du score à l’écran
SDL_Rect posScore2;
    int health;
    int score;
    int step;

    vitesse v;

    
    int etat;           // 0 = normal, 1 = dead, 2 = jump
	SDL_Surface *etat_vie[4]; // 4 images pour les états de vie
	int nb_morts;             // compteur de morts
	
} perso;

// === Fonctions ===

// Initialisation et affichage du personnage
void init_perso(perso *p, SDL_Rect posEcran,perso *p2,SDL_Rect posEcran2);
void afficher_perso(SDL_Surface *ecran, perso *p, perso *p2) ;
// Affichage du score
void afficher_score(perso *p, SDL_Surface *ecran, SDL_Rect posScore, TTF_Font *font, SDL_Color textColor , perso *p2,SDL_Rect posScore2);
void afficher_vie(perso *p, SDL_Surface *ecran, perso *p2) ;
// Animation
void animer_perso(perso *p, perso *p2);

// Contrôle du personnage
void perso_walk(SDL_Event event, perso *p, int *quitter);
void perso_dead(perso *p, SDL_Event event, int *quitter);
void perso_jump(SDL_Event event, perso *p, int *quitter);
void perso_run(SDL_Event e, perso *p, int *quitter);

void perso_walk1(SDL_Event event, perso *p2, int *quitter);
void perso_run1(SDL_Event event, perso *p2, int *quitter);
void perso_jump1(SDL_Event event, perso *p2, int *quitter);
void perso_dead1(perso *p2, SDL_Event event, int *quitter);

#endif

