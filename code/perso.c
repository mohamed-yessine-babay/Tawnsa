#include "perso.h"
#include <stdio.h>
#include <stdlib.h>

void init_perso(perso *p, SDL_Rect posEcran,perso *p2,SDL_Rect posEcran2)
{
    p->walk.a = IMG_Load("walk.png");
    p->dead.a = IMG_Load("dead.png");
    p->jump.a = IMG_Load("jump.png");
	p->run.a = IMG_Load("run.png");
	p2->walk1.a = IMG_Load("walk1.png");
    p2->dead1.a = IMG_Load("dead1.png");
    p2->jump1.a = IMG_Load("jump1.png");
	p2->run1.a = IMG_Load("run1.png");
    
    if (!p->walk.a || !p->dead.a || !p->jump.a || !p->run.a || !p2->walk1.a || !p2->dead1.a || !p2->jump1.a || !p2->run1.a)
    {
        printf("Erreur chargement image : %s\n", IMG_GetError());
        SDL_Quit();
        exit(1);
    }

    // Walk
    p->walk.spriteW = p->walk.a->w / 9;// 9 image par ligne
    p->walk.spriteH = p->walk.a->h / 4; // 4 ligne directiion
    p->walk.max = 9; //max 9 image
    p->walk.index = 0; //premiere pic dans la ligne
    p->walk.pos = (SDL_Rect){0, 0, p->walk.spriteW, p->walk.spriteH};//position de l'image dans l'ecran

    // Dead
    p->dead.spriteW = p->dead.a->w / 5;//5image par ligne
    p->dead.spriteH = p->dead.a->h; //1 seule ligne direction
    p->dead.max = 5; // 5 image par ligne
    p->dead.index = 0;// premiere image dans la ligne
    p->dead.pos = (SDL_Rect){0, 0, p->dead.spriteW, p->dead.spriteH};//pos de perso dans l'ecran

    // Jump
    p->jump.spriteH = p->jump.a->h / 4; // 4 lignes si c'est le cas
	p->jump.spriteW = p->jump.a->w / 5; // 5 frames par ligne
	p->jump.index = 0;// premiere image 
	p->jump.max = 5;//5 images max
	p->jump.sauter = 0;//init de saut a 0
	p->jump.speed = 8;//vitesse de saut
	p->jump.pos = (SDL_Rect){0, p->jump.spriteH, p->jump.spriteW, p->jump.spriteH}; // y = ligne 1 pos de perso dans l'ecran

	// run
	p->run.spriteH = p->run.a->h / 4; // 4 lignes
    p->run.spriteW = p->run.a->w / 8; // 8 sprites par ligne
    p->run.pos.w = p->run.spriteW;
    p->run.pos.h = p->run.spriteH;
	p->run.index=0;
	p->run.max=8;
	p->run.speed=8;
	p->run.pos = (SDL_Rect){0, 0, p->run.spriteW, p->run.spriteH};

	

	// Walk
    p2->walk1.spriteW = p2->walk1.a->w / 9;// 9 image par ligne
    p2->walk1.spriteH = p2->walk1.a->h / 4; // 4 ligne directiion
    p2->walk1.max = 9; //max 9 image
    p2->walk1.index = 0; //premiere pic dans la ligne
    p2->walk1.pos = (SDL_Rect){0, 0, p2->walk1.spriteW, p2->walk1.spriteH};//position de l'image dans l'ecran

    // Dead
    p2->dead1.spriteW = p2->dead1.a->w / 5;//5image par ligne
    p2->dead1.spriteH = p2->dead1.a->h; //1 seule ligne direction
    p2->dead1.max = 5; // 5 image par ligne
    p2->dead1.index = 0;// premiere image dans la ligne
    p2->dead1.pos = (SDL_Rect){0, 0, p2->dead1.spriteW, p2->dead1.spriteH};//pos de perso dans l'ecran

    // Jump
    p2->jump1.spriteH = p2->jump1.a->h / 4; // 4 lignes si c'est le cas
	p2->jump1.spriteW = p2->jump1.a->w / 5; // 5 frames par ligne
	p2->jump1.index = 0;// premiere image 
	p2->jump1.max = 5;//5 images max
	p2->jump1.sauter = 0;//init de saut a 0
	p2->jump1.speed = 8;//vitesse de saut
	p2->jump1.pos = (SDL_Rect){0, p2->jump1.spriteH, p2->jump1.spriteW, p2->jump1.spriteH}; // y = ligne 1 pos de perso dans l'ecran

	// run
	p2->run1.spriteH = p2->run1.a->h / 4; // 4 lignes
    p2->run1.spriteW = p2->run1.a->w / 8; // 8 sprites par ligne
    p2->run1.pos.w = p2->run1.spriteW;
    p2->run1.pos.h = p2->run1.spriteH;
	p2->run1.index=0;
	p2->run1.max=8;
	p2->run1.speed=8;
	p2->run1.pos = (SDL_Rect){0, 0, p2->run1.spriteW, p2->run1.spriteH};

    p->posEcran = posEcran;
    p->v.dx = 0;
    p->v.dy = 0;
    p->score = 0;
    p->etat = 0;
	p->step = 0;

	p2->posEcran2 = posEcran2;
    p2->v.dx = 0;
    p2->v.dy = 0;
    p2->score = 0;
    p2->etat = 0;
	p2->step = 0;

    p->health = 100;
	p->etat_vie[0]=IMG_Load("4.png");
	p->etat_vie[1]=IMG_Load("3.png");
	p->etat_vie[2]=IMG_Load("2.png");
	p->etat_vie[3]=IMG_Load("1.png");

	for (int i = 0; i < 4; i++) {
        if (p->etat_vie[i] == NULL) {
            printf("Erreur de chargement de l'image de vie %d: %s\n", i + 1, IMG_GetError());
            SDL_Quit();
            exit(1);
        }
	p->nb_morts = 0; // initialiser compteur de morts
}
p2->health = 100;
	p2->etat_vie[0]=IMG_Load("4.png");
	p2->etat_vie[1]=IMG_Load("3.png");
	p2->etat_vie[2]=IMG_Load("2.png");
	p2->etat_vie[3]=IMG_Load("1.png");

	for (int i = 0; i < 4; i++) {
        if (p2->etat_vie[i] == NULL) {
            printf("Erreur de chargement de l'image de vie %d: %s\n", i + 1, IMG_GetError());
            SDL_Quit();
            exit(1);
        }
	
}
p2->nb_morts = 0; // initialiser compteur de morts
}

void afficher_perso(SDL_Surface *ecran, perso *p, perso *p2) 
{
    SDL_Surface *sprite = NULL;
    SDL_Rect *posSprite = NULL;
	SDL_Surface *sprite2 = NULL;
    SDL_Rect *posSprite2 = NULL;

    switch (p->etat)
    {
    case 0:
        sprite = p->walk.a;
        posSprite = &p->walk.pos;
		sprite2 = p2->walk1.a;
        posSprite2 = &p2->walk1.pos;
        break;

    case 1:
        sprite = p->dead.a;
        posSprite = &p->dead.pos;
		sprite2 = p2->dead1.a;
        posSprite2 = &p2->dead1.pos;
        break;

    case 2:
        sprite = p->jump.a;
        posSprite = &p->jump.pos;
		sprite2 = p2->jump1.a;
        posSprite2 = &p2->jump1.pos;
        break;

    case 3:
    sprite = p->run.a;
    posSprite = &p->run.pos;
	sprite2 = p2->run1.a;
    posSprite2 = &p2->run1.pos;
    break;

    }

    if (sprite != NULL && posSprite != NULL) 
    {
        SDL_BlitSurface(sprite, posSprite, ecran, &p->posEcran);
    }
	if (sprite2 != NULL && posSprite2 != NULL) 
    {
        SDL_BlitSurface(sprite2, posSprite2, ecran, &p2->posEcran2);
    }
}


void animer_perso(perso *p, perso *p2)
{
    if (p->etat == 0 && p->v.dx != 0)
    {
        p->walk.index = (p->walk.index + 1) % p->walk.max;//quand on obtient 0 on a atteint la derniere frame et elle retourne a la premiere frame
        p->walk.pos.x = p->walk.index * p->walk.spriteW;//indiquer la frame afficher et la largeur de la frame et elle se decale a droite et on trouve la bonne spritesheet
    }
    else if (p->etat == 1)
    {
        if (p->dead.index < p->dead.max - 1)
            p->dead.index++;
        p->dead.pos.x = p->dead.index * p->dead.spriteW;
    }
    else if (p->etat == 2) 
	{
    p->jump.index++;
    if (p->jump.index >= p->jump.max)
        p->jump.index = 0;

    // ligne 2 : y = spriteH * 1
    p->jump.pos.x = p->jump.index * p->jump.spriteW;
    p->jump.pos.y = p->jump.spriteH * 1; // ligne 2
	}
	else if (p->etat == 3 && p->v.dx != 0)
	{
    p->step++;
    if (p->step % 6 == 0)
    {
        p->run.index = (p->run.index + 1) % p->run.max;
        p->run.pos.x = p->run.index * p->run.spriteW;
    }
}
// === Animation de p2 ===
    if (p2->etat == 0 && p2->v.dx != 0) {
        p2->walk1.index = (p2->walk1.index + 1) % p2->walk1.max;
        p2->walk1.pos.x = p2->walk1.index * p2->walk1.spriteW;
    } else if (p2->etat == 1) {
        if (p2->dead1.index < p2->dead1.max - 1)
            p2->dead1.index++;
        p2->dead1.pos.x = p2->dead1.index * p2->dead1.spriteW;
    } else if (p2->etat == 2) {
        p2->jump1.index++;
        if (p2->jump1.index >= p2->jump1.max)
            p2->jump1.index = 0;
        p2->jump1.pos.x = p2->jump1.index * p2->jump1.spriteW;
        p2->jump1.pos.y = p2->jump1.spriteH * 1;
    } else if (p2->etat == 3 && p2->v.dx != 0) {
        p2->step++;
        if (p2->step % 6 == 0) {
            p2->run1.index = (p2->run1.index + 1) % p2->run1.max;
            p2->run1.pos.x = p2->run1.index * p2->run1.spriteW;
        }
    }
}

void afficher_score(perso *p, SDL_Surface *ecran, SDL_Rect posScore, TTF_Font *font, SDL_Color textColor , perso *p2,SDL_Rect posScore2)
{
   char score1[20], score2[20];
sprintf(score1, "P1 Score: %d", p->score);
sprintf(score2, "P2 Score: %d", p2->score);

SDL_Surface *scoreSurface1 = TTF_RenderText_Solid(font, score1, textColor);
SDL_Surface *scoreSurface2 = TTF_RenderText_Solid(font, score2, textColor);

SDL_BlitSurface(scoreSurface1, NULL, ecran, &posScore);
SDL_BlitSurface(scoreSurface2, NULL, ecran, &posScore2);

SDL_FreeSurface(scoreSurface1);
SDL_FreeSurface(scoreSurface2);

}

void afficher_vie(perso *p, SDL_Surface *ecran, perso *p2) {
    if (p->nb_morts < 4) {
        SDL_Rect posVie;
        posVie.x = 1700;
        posVie.y = 20;
        SDL_BlitSurface(p->etat_vie[p->nb_morts], NULL, ecran, &posVie);
    }
	if (p2->nb_morts < 4) {
        SDL_Rect posVie2;
        posVie2.x = 1700;
        posVie2.y = 80;
        SDL_BlitSurface(p2->etat_vie[p2->nb_morts], NULL, ecran, &posVie2);
    }
}

void perso_walk(SDL_Event event, perso *p, int *quitter)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            *quitter = 0;
            break;
        case SDLK_LEFT:
            p->v.dx = -12;
            p->walk.pos.y = p->walk.spriteH; // selectionne la ligne de spritesheet 
            p->score += 10;
            break;
        case SDLK_RIGHT:
            p->v.dx = 12;
            p->walk.pos.y = p->walk.spriteH * 3; // ligne droite
            p->score += 10;
            break;
        }
    }
    else if (event.type == SDL_KEYUP)
    {
        if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT)
        {
            p->v.dx = 0;
            p->walk.index = 0;
            p->walk.pos.x = 0;
        }
    }
}

void perso_dead(perso *p, SDL_Event event, int *quitter)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_d:
	if (p->nb_morts < 4 - 1) {
            p->etat = 1;
            p->dead.index = 0;
	    p->nb_morts++;
	}
	else {
                p->nb_morts = 4 - 1;
                printf("GAME OVER\n");
                *quitter = 0; // Fin du jeu
            }
            break;
            
        case SDLK_r:
            p->etat = 0;
            p->walk.index = 0;
            break;
        }
    }
}

void perso_jump(SDL_Event event, perso *p, int *quitter)
{
    switch (event.type)
    {
    case SDL_QUIT:
        *quitter = 0;
        break;

    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            *quitter = 0;
            break;

        case SDLK_SPACE:
            // Autoriser le saut seulement si le personnage est au sol (tolérance sur Y)
            if (p->etat != 2 && p->posEcran.y >= 348)
            {
                p->etat = 2;
                p->v.dy = -20; // Vitesse vers le haut
                p->jump.index = 0; // Recommencer l'animation de saut
                p->jump.pos.x = 0;
            }
            break;
        }
        break;

    case SDL_KEYUP:
        switch (event.key.keysym.sym)
        {
        case SDLK_SPACE:
            // Ne rien faire ici en général pour le saut,
            // le retour à l'état normal se gère dans la boucle principale
            break;
        }
        break;
    }
}



void perso_run(SDL_Event event, perso *p, int *quitter)
{
    switch (event.type)
    {
    case SDL_QUIT:
        *quitter = 0;
        break;

    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            *quitter = 0;
            break;

        case SDLK_c:
            p->v.dx = -20;
            p->etat = 3; // état spécial pour courir (gauche)
            p->run.pos.y = p->run.spriteH; // ligne 2 = gauche
            break;

        case SDLK_v:
            p->v.dx = 20;
            p->etat = 3; // état spécial pour courir (droite)
            p->run.pos.y = p->run.spriteH * 3; // ligne 4 = droite
            break;
        }
        break;

    case SDL_KEYUP:
        if (event.key.keysym.sym == SDLK_c || event.key.keysym.sym == SDLK_v)
        {
            p->v.dx = 0;
            p->run.index = 0;
            p->run.pos.x = 0;
            p->etat = 0; // retour à l'état marche
        }
        break;
    }

    
}

void perso_walk1(SDL_Event event, perso *p2, int *quitter)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            *quitter = 0;
            break;
        case SDLK_q:
			p2->etat=0;
            p2->v.dx = -12;
            p2->walk1.pos.y = 1* p2->walk1.spriteH; // selectionne la ligne de spritesheet 
            p2->score += 10;
            break;
        case SDLK_s:
			p2->etat=0;
            p2->v.dx = 12;
            p2->walk1.pos.y =3* p2->walk1.spriteH ;// ligne droite
            p2->score += 10;
            break;
        }
    }
    else if (event.type == SDL_KEYUP)
    {
        if (event.key.keysym.sym == SDLK_q || event.key.keysym.sym == SDLK_s)
        {
            p2->v.dx = 0;
            p2->walk1.index = 0;
            p2->walk1.pos.x = 0;
        }
    }
}

void perso_dead1(perso *p2, SDL_Event event, int *quitter)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_a:
	if (p2->nb_morts < 4 - 1) {
            p2->etat = 1;
            p2->dead1.index = 0;
	    p2->nb_morts++;
	}
	else {
                p2->nb_morts = 4 - 1;
                printf("GAME OVER\n");
                *quitter = 0; // Fin du jeu
            }
            break;
            
        case SDLK_z:
            p2->etat = 0;
            p2->walk1.index = 0;
            break;
        }
    }
}

void perso_jump1(SDL_Event event, perso *p2, int *quitter)
{
    switch (event.type)
    {
    case SDL_QUIT:
        *quitter = 0;
        break;

    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            *quitter = 0;
            break;

        case SDLK_SPACE:
            // Autoriser le saut seulement si le personnage est au sol (tolérance sur Y)
            if (p2->etat != 2 && p2->posEcran2.y >= 348)
            {
                p2->etat = 2;
                p2->v.dy = -20; // Vitesse vers le haut
                p2->jump1.index = 0; // Recommencer l'animation de saut
                p2->jump1.pos.x = 0;
            }
            break;
        }
        break;

    case SDL_KEYUP:
        switch (event.key.keysym.sym)
        {
        case SDLK_SPACE:
            // Ne rien faire ici en général pour le saut,
            // le retour à l'état normal se gère dans la boucle principale
            break;
        }
        break;
    }
}



void perso_run1(SDL_Event event, perso *p2, int *quitter)
{
    switch (event.type)
    {
    case SDL_QUIT:
        *quitter = 0;
        break;

    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            *quitter = 0;
            break;

        case SDLK_w:
            p2->v.dx = -20;
            p2->etat = 3; // état spécial pour courir (gauche)
            p2->run1.pos.y = p2->run1.spriteH; // ligne 2 = gauche
			p2->run1.index++;
            if (p2->run1.index >= p2->run1.max)
                p2->run1.index = 0;
            p2->run1.pos.x = p2->run1.index * p2->run1.spriteW;
            break;

        case SDLK_x:
            p2->v.dx = 20;
            p2->etat = 3; // état spécial pour courir (droite)
            p2->run1.pos.y = p2->run1.spriteH * 3; // ligne 4 = droite
			p2->run1.index++;//vancer l’animation frame par frame
            if (p2->run1.index >= p2->run1.max)
                p2->run1.index = 0;
            p2->run1.pos.x = p2->run1.index * p2->run1.spriteW;//affiche la bonne frame de la course à chaque touche.
            break;
        }
        break;

    case SDL_KEYUP:
        if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_x)
        {
            p2->v.dx = 0;
            p2->run1.index = 0;
            p2->run1.pos.x = 0;
            p2->etat = 0; // retour à l'état marche
        }
        break;
    }

    
}


















