
#include "perso.h"
#include <stdio.h>
#include <stdlib.h>

void init_perso(perso *p, SDL_Rect posEcran,perso *p2,SDL_Rect posEcran2)
{
    p->walk.a = IMG_Load("asset-joueur/walk.png");
    p->dead.a = IMG_Load("asset-joueur/dead.png");
    p->jump.a = IMG_Load("asset-joueur/jump.png");
	p->run.a = IMG_Load("asset-joueur/run.png");
	//p->attack.a = IMG_Load("attack.png");	
	p2->walk1.a = IMG_Load("asset-joueur/walk1.png");
    p2->dead1.a = IMG_Load("asset-joueur/dead1.png");
    p2->jump1.a = IMG_Load("asset-joueur/jump1.png");
	p2->run1.a = IMG_Load("asset-joueur/run1.png");
    
    if (!p->walk.a || !p->dead.a || !p->jump.a || !p->run.a )
    {
        printf("Erreur chargement image : %s\n", IMG_GetError());
        SDL_Quit();
        exit(1);
    }
if (p2->walk1.a == NULL) {
    printf("Erreur chargement walk1 perso2 : %s\n", SDL_GetError());
	}
	if (p2->dead1.a == NULL) {
    printf("Erreur chargement dead1 perso2 : %s\n", SDL_GetError());
	}
	if (p2->jump1.a == NULL) {
    printf("Erreur chargement jump1 perso2 : %s\n", SDL_GetError());
	}
	if (p2->run1.a == NULL) {
    printf("Erreur chargement run1 perso2 : %s\n", SDL_GetError());
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
	p->jump.pos = (SDL_Rect){100, 300, p->jump.spriteW, p->jump.spriteH}; // y = ligne 1 pos de perso dans l'ecran
	p->up=0;

	// run
	p->run.spriteH = p->run.a->h / 4; // 4 lignes
    p->run.spriteW = p->run.a->w / 8; // 8 sprites par ligne
    p->run.pos.w = p->run.spriteW;
    p->run.pos.h = p->run.spriteH;
	p->run.index=0;
	p->run.max=8;
	p->run.speed=8;
	p->run.pos = (SDL_Rect){0, 0, p->run.spriteW, p->run.spriteH};
	
	//attack

p->attack.a = IMG_Load("asset-joueur/attack.png");

p->attack.spriteW = p->attack.a->w / 6; // 6 colonnes
p->attack.spriteH = p->attack.a->h / 4; // 4 lignes
p->attack.max = 6; // 6 frames par ligne
p->attack.index = 0;
p->attack.pos.x = 0;
p->attack.pos.y = 0;
p->attack.pos.w = p->attack.spriteW;
p->attack.pos.h = p->attack.spriteH;



    p->posEcran = posEcran;
    p->v.dx = 0;
    p->v.dy = 0;
    p->score = 0;
    p->etat = 0;
	p->step = 0;

p->direction1 = 0;


    p->health = 100;
	p->etat_vie[0]=IMG_Load("asset-joueur/4.png");
	p->etat_vie[1]=IMG_Load("asset-joueur/3.png");
	p->etat_vie[2]=IMG_Load("asset-joueur/2.png");
	p->etat_vie[3]=IMG_Load("asset-joueur/1.png");

	for (int i = 0; i < 4; i++) {
        if (p->etat_vie[i] == NULL) {
            printf("Erreur de chargement de l'image de vie %d: %s\n", i + 1, IMG_GetError());
            SDL_Quit();
            exit(1);
        }
	p->nb_morts = 0; // initialiser compteur de morts

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
	p2->jump1.pos = (SDL_Rect){100, 300, p2->jump1.spriteW, p2->jump1.spriteH}; // y = ligne 1 pos de perso dans l'ecran

	// run
	p2->run1.spriteH = p2->run1.a->h / 4; // 4 lignes
    p2->run1.spriteW = p2->run1.a->w / 8; // 8 sprites par ligne
    p2->run1.pos.w = p2->run1.spriteW;
    p2->run1.pos.h = p2->run1.spriteH;
	p2->run1.index=0;
	p2->run1.max=8;
	p2->run1.speed=8;
	p2->run1.pos = (SDL_Rect){0, 0, p2->run1.spriteW, p2->run1.spriteH};

	//attack

p2->attack1.a = IMG_Load("asset-joueur/attack1.png");

p2->attack1.spriteW = p2->attack1.a->w / 13; // 6 colonnes
p2->attack1.spriteH = p2->attack1.a->h / 4; // 4 lignes
p2->attack1.max = 13; // 6 frames par ligne
p2->attack1.index = 0;
p2->attack1.pos.x = 0;
p2->attack1.pos.y = 0;
p2->attack1.pos.w = p2->attack1.spriteW;
p2->attack1.pos.h = p2->attack1.spriteH;

p2->posEcran2 = posEcran2;
    p2->v.dx = 0;
    p2->v.dy = 0;
    p2->score = 0;
    p2->etat = 0;
	p2->step = 0;


p2->direction2 = 0;

p2->health = 100;
	p2->etat_vie[0]=IMG_Load("asset-joueur/4.png");
	p2->etat_vie[1]=IMG_Load("asset-joueur/3.png");
	p2->etat_vie[2]=IMG_Load("asset-joueur/2.png");
	p2->etat_vie[3]=IMG_Load("asset-joueur/1.png");

	for (int i = 0; i < 4; i++) {
        if (p2->etat_vie[i] == NULL) {
            printf("Erreur de chargement de l'image de vie %d: %s\n", i + 1, IMG_GetError());
            SDL_Quit();
            exit(1);
        }
	
}
p2->nb_morts = 0; // initialiser compteur de morts
}
}


void afficher_perso(SDL_Surface *ecran, perso *p) 
{
    SDL_Surface *sprite = NULL;
    SDL_Rect *posSprite = NULL;
    

    switch (p->etat)
    {
    case 0:
        sprite = p->walk.a;
        posSprite = &p->walk.pos;
	
        break;

    case 1:
        sprite = p->dead.a;
        posSprite = &p->dead.pos;
	
        break;

    case 2:
        sprite = p->jump.a;
        posSprite = &p->jump.pos;
	
        break;

    case 3:
    sprite = p->run.a;
    posSprite = &p->run.pos;
	break;
	
	case 4:
	sprite = p->attack.a;
    posSprite = &p->attack.pos;
	break;

    }
    
    
    if (sprite != NULL && posSprite != NULL) 
    {
        SDL_BlitSurface(sprite, posSprite, ecran, &p->posEcran);
    }
	
}



void animer_perso(perso *p)
{
    if (p->etat == 0 && p->v.dx != 0)
    {
        p->walk.index = (p->walk.index + 1) % p->walk.max;//quand on obtient 0 on a atteint la derniere frame et elle retourne a la premiere frame
        p->walk.pos.x = p->walk.index * p->walk.spriteW;//indiquer la frame afficher et la largeur de la frame et elle se decale a droite et on trouve la bonne spritesheet
	p->walk.pos.y = p->direction1 * p->walk.spriteH;

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
    p->jump.pos.y = p->jump.spriteH * 3; // ligne 2
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
	else if (p->etat == 4)
    {
	p->attack.index = (p->attack.index + 1);
	if(p->attack.index >= p->attack.max)       
	{
		p->etat = 0;
		p->attack.index = 0;  //quand on obtient 0 on a atteint la derniere frame et elle retourne a la premiere frame
	}

        p->attack.pos.x = p->attack.index * p->attack.spriteW;//indiquer la frame afficher et la largeur de la frame et elle se decale a droite et on trouve la bonne spritesheet
	
	

    }


}

void afficher_perso2(SDL_Surface *ecran, perso *p2) 
{
    
    SDL_Surface *sprite2 = NULL;
    SDL_Rect *posSprite2 = NULL;
    
    switch (p2->etat)
    {
    case 0:
    sprite2 = p2->walk1.a;
        posSprite2 = &p2->walk1.pos;
    break;
    
    case 1:
    sprite2 = p2->dead1.a;
        posSprite2 = &p2->dead1.pos;
    break;
    
    case 2:
    sprite2 = p2->jump1.a;
        posSprite2 = &p2->jump1.pos;
    break;
    
    case 3:
    sprite2 = p2->run1.a;
    posSprite2 = &p2->run1.pos;
    break;

case 4:
	sprite2 = p2->attack1.a;
    posSprite2 = &p2->attack1.pos;
	break;

    }	
    
	if (sprite2 != NULL && posSprite2 != NULL) 
    {
        SDL_BlitSurface(sprite2, posSprite2, ecran, &p2->posEcran2);
    }
}


void animer_perso2( perso *p2)
{
// === Animation de p2 ===

if (p2->etat == 0 && p2->v.dx != 0)
    {
        p2->walk1.index = (p2->walk1.index + 1) % p2->walk1.max;//quand on obtient 0 on a atteint la derniere frame et elle retourne a la premiere frame
        p2->walk1.pos.x = p2->walk1.index * p2->walk1.spriteW;//indiquer la frame afficher et la largeur de la frame et elle se decale a droite et on trouve la bonne spritesheet
	p2->walk1.pos.y = p2->direction2 * p2->walk1.spriteH;

    }
    else if (p2->etat == 1)
    {
        if (p2->dead1.index < p2->dead1.max - 1)
            p2->dead1.index++;
        p2->dead1.pos.x = p2->dead1.index * p2->dead1.spriteW;
    }
    else if (p2->etat == 2) 
	{
    p2->jump1.index++;
    if (p2->jump1.index >= p2->jump1.max)
        p2->jump1.index = 0;

    // ligne 2 : y = spriteH * 1
    p2->jump1.pos.x = p2->jump1.index * p2->jump1.spriteW;
    p2->jump1.pos.y = p2->jump1.spriteH * 3; // ligne 2
	}
	else if (p2->etat == 3 && p2->v.dx != 0)
	{
    p2->step++;
    if (p2->step % 6 == 0)
    {
        p2->run1.index = (p2->run1.index + 1) % p2->run1.max;
        p2->run1.pos.x = p2->run1.index * p2->run1.spriteW;
    }
}
else if (p2->etat == 4)
    {
	p2->attack1.index = (p2->attack1.index + 1);
	if(p2->attack1.index >= p2->attack1.max)       
	{
		p2->etat = 0;
		p2->attack1.index = 0;  //quand on obtient 0 on a atteint la derniere frame et elle retourne a la premiere frame
	}

        p2->attack1.pos.x = p2->attack1.index * p2->attack1.spriteW;//indiquer la frame afficher et la largeur de la frame et elle se decale a droite et on trouve la bonne spritesheet
	
	

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
        posVie.x = 1500;
        posVie.y = 20;
        SDL_BlitSurface(p->etat_vie[p->nb_morts], NULL, ecran, &posVie);
    }
	if (p2->nb_morts < 4) {
        SDL_Rect posVie2;
        posVie2.x = 1500;
        posVie2.y =100;
        SDL_BlitSurface(p2->etat_vie[p2->nb_morts], NULL, ecran, &posVie2);
    }
}

void saut_Personnage(perso *p, Uint32 dt, int posx_absolu, int posy_absolu)
{
    static float x_rel = 0.0; // position horizontale 
    float a = -0.04;
    float c = 100.0;
    float y_rel;
    
    // en train de sauter
    if (p->up == 1)
    {
       //mise a jour de la pos
        x_rel += 0.1 * dt; // 0.5 est une constante de vitesse horizontale du saut

        // calcul y relative
        y_rel = a * x_rel * x_rel + c;

        // mise a jour de la pos reel de perso
        p->posEcran.x = posx_absolu +(int) x_rel;
		p->posEcran.y = posy_absolu -(int) y_rel;
		p->etat = 2; // état = saut (important pour l'animation)


        //  retour au sol
        if (x_rel >= 50.0)
        {
            p->up = 0;
            x_rel = 0.0; // réinitialiser pour le prochain saut
	    p->etat = 0; // retour à la marche
        }
    }
}

void saut_Perso(perso *p2, Uint32 dt, int posx_absolu1, int posy_absolu1)
{
    static float x_rel = 0.0; // position horizontale 
    float a = -0.04;
    float c = 100.0;
    float y_rel2;
    
    // en train de sauter
    if (p2->up == 1)
    {
       //mise a jour de la pos
        x_rel += 0.1 * dt; // 0.5 est une constante de vitesse horizontale du saut

        // calcul y relative
        y_rel2 = a * x_rel * x_rel + c;

        // mise a jour de la pos reel de perso
        p2->posEcran2.x = posx_absolu1 +(int) x_rel;
		p2->posEcran2.y = posy_absolu1 -(int) y_rel2;
		p2->etat = 2; // état = saut (important pour l'animation)


        //  retour au sol
        if (x_rel >= 50.0)
        {
            p2->up = 0;
            x_rel = 0.0; // réinitialiser pour le prochain saut
	    p2->etat = 0; // retour à la marche
        }
    }
}
