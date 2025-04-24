#include "enigme.h"
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

int main() {
    // Initialisation
    int boucle = 1; // boucle infinie (boucle = 0)
    SDL_Event event; // gère les événements (clic, clavier, etc.)
    TTF_Init(); // Fonction pré-définie qui initialise la gestion des polices de texte
    SDL_Surface *screen; // Surface pour l'affichage
    screen = SDL_SetVideoMode(1400, 1000, 32, SDL_HWSURFACE | SDL_SRCALPHA); // Crée l'écran d'affichage, 32 bits pour la couleur
    Mix_Music *musique; // Pointeur pour la musique
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024); // Initialise le mixeur audio
    musique = Mix_LoadMUS("song/audio.mp3"); // Charge la musique à partir du fichier

    enigme e; // Déclare la variable enigme
    init_enigme(&e); // Initialise l'énigme

    Mix_PlayMusic(musique, -1); // Joue la musique en boucle infinie

    // Déclaration des images
    SDL_Surface *img_good, *img_hard; 
    SDL_Rect pos_good, pos_hard;
    
    img_good = IMG_Load("enigme image/good.png"); // Charge l'image "good.png"
    img_hard = IMG_Load("enigme image/hard.png"); // Charge l'image "hard.png"
    pos_hard.x = 0;
    pos_hard.y = 0;
    pos_good.x = 0;
    pos_good.y = 0;

    while (boucle == 1) { // Boucle principale
        afficher_enigme(screen, e); // Affiche l'énigme à l'écran
        
        while (SDL_PollEvent(&event)) { // Lit les événements
            switch (event.type) {
                case SDL_QUIT:
                    boucle = 0;
                    break;
                case SDL_KEYDOWN: // Si une touche est enfoncée
                    if (event.key.keysym.sym == SDLK_a) {
                        e.reponse1.p = 1;
                        e.reponse2.p = 0;
                        e.reponse3.p = 0;
                    } else if (event.key.keysym.sym == SDLK_b) {
                        e.reponse1.p = 0;
                        e.reponse2.p = 1;
                        e.reponse3.p = 0;
                    } else if (event.key.keysym.sym == SDLK_c) {
                        e.reponse1.p = 0;
                        e.reponse2.p = 0;
                        e.reponse3.p = 1;
                    } else if (event.key.keysym.sym == SDLK_RETURN) { // Résolution de l'énigme
                        if ((e.reponse1.p == 1 && e.r_exact == 1) || 
                            (e.reponse2.p == 1 && e.r_exact == 2) || 
                            (e.reponse3.p == 1 && e.r_exact == 3)) {
                            printf("Bien\n");
                            SDL_BlitSurface(img_good, NULL, screen, &pos_good);
                            SDL_Flip(screen);
                            SDL_Delay(9000); // Attend avant de continuer
                            Mix_PlayChannel(-1, e.song[0], 0); // Joue la musique
                        } else {
                            printf("Pas bien\n");
                            SDL_BlitSurface(img_hard, NULL, screen, &pos_hard);
                            SDL_Flip(screen);
                            SDL_Delay(9000);
                            Mix_PlayChannel(-1, e.song[1], 0);
                        }
                        genererEnigme(&e); // Génère une nouvelle énigme
                    }
                    break;
                case SDL_MOUSEMOTION: // Si la souris se déplace
                    if (event.motion.x > e.reponse1.pos.x && event.motion.x < e.reponse1.pos.x + e.reponse1.pos.w &&
                        event.motion.y > e.reponse1.pos.y && event.motion.y < e.reponse1.pos.y + e.reponse1.pos.h) {
                        e.reponse1.p = 1;
                        e.reponse2.p = 0;
                        e.reponse3.p = 0;
                    } else if (event.motion.x > e.reponse2.pos.x && event.motion.x < e.reponse2.pos.x + e.reponse2.pos.w &&
                               event.motion.y > e.reponse2.pos.y && event.motion.y < e.reponse2.pos.y + e.reponse2.pos.h) {
                        e.reponse1.p = 0;
                        e.reponse2.p = 1;
                        e.reponse3.p = 0;
                    } else if (event.motion.x > e.reponse3.pos.x && event.motion.x < e.reponse3.pos.x + e.reponse3.pos.w &&
                               event.motion.y > e.reponse3.pos.y && event.motion.y < e.reponse3.pos.y + e.reponse3.pos.h) {
                        e.reponse1.p = 0;
                        e.reponse2.p = 0;
                        e.reponse3.p = 1;
                    } else {
                        e.reponse1.p = 0;
                        e.reponse2.p = 0;
                        e.reponse3.p = 0;
                    }
                    break;
                case SDL_MOUSEBUTTONUP: // Si un bouton de la souris est relâché
                    if ((e.reponse1.p == 1 && e.r_exact == 1) || 
                        (e.reponse2.p == 1 && e.r_exact == 2) || 
                        (e.reponse3.p == 1 && e.r_exact == 3)) {
                        printf("Bien\n");
                        SDL_BlitSurface(img_good, NULL, screen, &pos_good);
                        SDL_Flip(screen);
                        SDL_Delay(3000);
                        Mix_PlayChannel(-1, e.song[0], 0);
                    } else {
                        printf("Pas bien\n");
                        SDL_BlitSurface(img_hard, NULL, screen, &pos_hard);
                        SDL_Flip(screen);
                        SDL_Delay(3000);
                        Mix_PlayChannel(-1, e.song[1], 0);
                    }
                    genererEnigme(&e); // Génère une nouvelle énigme
                    break;
            }
        }
        SDL_Flip(screen); // Mise à jour de l'affichage
    }

    // Libération des ressources avant la fin
    Mix_FreeMusic(musique);
    SDL_FreeSurface(img_good);
    SDL_FreeSurface(img_hard);
    SDL_Quit();
    TTF_Quit();
    Mix_CloseAudio();
    
    return 0;
}

