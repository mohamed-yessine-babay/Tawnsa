#include "perso.h"

int main(int argc, char** argv)
{
    int quitter = 1;
    SDL_Event event;
// init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Échec d'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }
//creation d'une fentre
    SDL_Surface *ecran = SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (ecran == NULL)
    {
        fprintf(stderr, "Échec de création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
// init texte
    if (TTF_Init() == -1)
    {
        printf("Erreur SDL_ttf : %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }
//chargement de la poolice
    TTF_Font *font = TTF_OpenFont("Acadian_Runes-Regular_PERSONAL_USE.ttf", 24);
    if (font == NULL)
    {
        printf("Erreur chargement police : %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }
//couleur
    SDL_Color textColor = {0, 0, 0}; // Noir

    perso p, p2;
    SDL_Rect posEcran = {100, 350, 0, 0};
    SDL_Rect posEcran2 = {700, 350, 0, 0};
    SDL_Rect posScore = {20, 20, 0, 0};
    SDL_Rect posScore2 = {20, 60, 0, 0};
    init_perso(&p, posEcran,&p2,posEcran2);

    while (quitter)//boucle principale
    {
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

        while (SDL_PollEvent(&event))
        {
            perso_walk(event, &p, &quitter);
            perso_dead(&p, event, &quitter);
            perso_jump(event, &p, &quitter);
	perso_run(event, &p, &quitter);

	perso_walk1(event, &p2, &quitter);
            perso_dead1(&p2, event, &quitter);
            perso_jump1(event, &p2, &quitter);
	perso_run1(event, &p2, &quitter);
	
        }

        // Appliquer la vitesse
        // Appliquer la vitesse si marche ou course
if (p.etat == 0 || p.etat == 3) {
    p.posEcran.x += p.v.dx;
    p.posEcran.y += p.v.dy;
}
if (p2.etat == 0 || p2.etat == 3) {
    p2.posEcran2.x += p2.v.dx;
    p2.posEcran2.y += p2.v.dy;
}

        // Gestion gravité (Si le personnage saute, il "tombe" avec une gravité simulée. Quand il touche le sol (Y=350), on le remet en marche).
        if (p.etat == 2) {
    p.v.dy += 2; // effet de gravité
    p.posEcran.y += p.v.dy;

    if (p.posEcran.y >= 350) {
        p.posEcran.y = 350;
        p.v.dy = 0;
        p.etat = 0; // retour à la marche
    }
} else {
    p.v.dy = 0;
}
if (p2.etat == 2) {
    p2.v.dy += 2; // effet de gravité
    p2.posEcran2.y += p2.v.dy;

    if (p2.posEcran2.y >= 350) {
        p2.posEcran2.y = 350;
        p2.v.dy = 0;
        p2.etat = 0; // retour à la marche
    }
} else {
    p2.v.dy = 0;
}


        // Empêcher de sortir de l'écran
        if (p.posEcran.x < 0) p.posEcran.x = 0;
        if (p.posEcran.y < 0) p.posEcran.y = 0;
        if (p.posEcran.x > 1920 - p.walk.spriteW) p.posEcran.x = 1920 - p.walk.spriteW;
        if (p.posEcran.y > 1080 - p.walk.spriteH) p.posEcran.y = 1080 - p.walk.spriteH;
	if (p.posEcran.x > 1920 - p.run.spriteW) p.posEcran.x = 1920 - p.run.spriteW;
        if (p.posEcran.y > 1080 - p.run.spriteH) p.posEcran.y = 1080 - p.run.spriteH;

	if (p2.posEcran2.x > 1920 - p2.walk.spriteW) p2.posEcran2.x = 1920 - p2.walk.spriteW;
        if (p2.posEcran2.y > 1080 - p2.walk.spriteH) p2.posEcran2.y = 1080 - p2.walk.spriteH;
	if (p2.posEcran2.x > 1920 - p2.run.spriteW) p2.posEcran2.x = 1920 - p2.run.spriteW;
        if (p2.posEcran2.y > 1080 - p2.run.spriteH) p2.posEcran2.y = 1080 - p2.run.spriteH;

        animer_perso(&p,&p2);
        afficher_perso(ecran, &p,&p2);
        afficher_score(&p, ecran, posScore, font, textColor,&p2,posScore2);
	afficher_vie(&p, ecran,&p2);




        SDL_Flip(ecran);
        SDL_Delay(100);
    }

    SDL_FreeSurface(p.walk.a);
    SDL_FreeSurface(p.dead.a);
    SDL_FreeSurface(p.jump.a);
SDL_FreeSurface(p2.run.a);
SDL_FreeSurface(p2.walk.a);
    SDL_FreeSurface(p2.dead.a);
    SDL_FreeSurface(p2.jump.a);
SDL_FreeSurface(p2.run.a);

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return 0;
}


