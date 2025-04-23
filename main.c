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
// Init des personnages
    perso p, p2;
    SDL_Rect posEcran = {100, 350, 0, 0};
    SDL_Rect posEcran2 = {700, 350, 0, 0};
    SDL_Rect posScore = {20, 20, 0, 0};
    SDL_Rect posScore2 = {20, 60, 0, 0};
    init_perso(&p, posEcran,&p2,posEcran2);
	
	
	int show_perso2=0;
	int posinit= p.posEcran.y; //position initiale avant le saut
	int posinit2= p2.posEcran2.y; //position initiale avant le saut
	int dt=0;
	Uint32 time=0, last=0;

while(quitter){
		time = SDL_GetTicks();
		dt= time-last;
		last=time;
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    while (SDL_PollEvent(&event)) //  boucle principale
    {

	if (event.type == SDL_KEYDOWN)
    	{
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            quitter = 0;
            break;
	case SDLK_m:
			show_perso2=1;
			break;
//perso 1: deplacement
        case SDLK_LEFT:
            p.v.dx = -8;
            p.walk.pos.y = p.walk.spriteH; // selectionne la ligne de spritesheet 
            p.score += 10;
			p.direction1=1;
            break;
        case SDLK_RIGHT:
            p.v.dx = 8;
            p.walk.pos.y = p.walk.spriteH * 3; // ligne droite
            p.score += 10;
            p.direction1=3;
            break;
		case SDLK_DOWN:
		if (p.nb_morts < 3) {
            p.etat = 1;
            p.dead.index = 0;
	    	p.nb_morts++;
			}
		else {
                
                printf("GAME OVER\n");
                quitter = 0; // Fin du jeu
            }
            break;
            
        case SDLK_r:
            p.etat = 0;
            p.walk.index = 0;
            break;
		case SDLK_UP:
            if (p.up ==0)
			{
				p.up=1;
				posinit = p.posEcran.y;
				p.score += 10;
			}
            break;
			case SDLK_c:
            p.v.dx = -20;
            p.etat = 3; // état spécial pour courir (gauche)
            p.run.pos.y = p.run.spriteH; // ligne 2 = gauche
            p.score += 10;
            break;

        case SDLK_v:
            p.v.dx = 20;
            p.etat = 3; // état spécial pour courir (droite)
            p.run.pos.y = p.run.spriteH * 3; // ligne 4 = droite
            p.score += 10;
            break;
//perso 2: deplacement
		case SDLK_q:
			p2.etat=0;
            p2.v.dx = -12;
            p2.walk1.pos.y = 1* p2.walk1.spriteH; // selectionne la ligne de spritesheet 
            p2.score += 10;
            p2.direction2=1;
            break;
        case SDLK_d:
			p2.etat=0;
            p2.v.dx = 12;
            p2.walk1.pos.y =3* p2.walk1.spriteH ;// ligne droite
            p2.score += 10;
            p2.direction2=3;
            break;
		case SDLK_s:
		if (p2.nb_morts <3) {
            p2.etat = 1;
            p2.dead1.index = 0;
	    	p2.nb_morts++;
			}
			else {    
            printf("GAME OVER\n");
            quitter = 0; // Fin du jeu
            }
            break;
            
        case SDLK_e:
            p2.etat = 0;
            p2.walk1.index = 0;
            break;
		case SDLK_w:
            p2.v.dx = -20;
            p2.etat = 3;
            p2.run1.pos.y = p2.run1.spriteH;
            p2.run1.index = (p2.run1.index + 1) % p2.run1.max;
            p2.run1.pos.x = p2.run1.index * p2.run1.spriteW;
            p2.score += 10;
            break;
	case SDLK_h:
    p.attack.index = 0;
    p.attack.pos.x = 0;
    p.attack.pos.y = p.attack.spriteH * 1; // Ligne 1
    p.etat = 4;
    break;

case SDLK_j:
    p.attack.index = 0;
    p.attack.pos.x = 0;
    p.attack.pos.y = p.attack.spriteH * 3; // Ligne 3
    p.etat = 4;
    break;

case SDLK_k:
    p2.attack1.index = 0;
    p2.attack1.pos.x = 0;
    p2.attack1.pos.y = p2.attack1.spriteH * 1; // Ligne 1
    p2.etat = 4;
    break;

case SDLK_l:
    p2.attack1.index = 0;
    p2.attack1.pos.x = 0;
    p2.attack1.pos.y = p2.attack1.spriteH * 3; // Ligne 3
    p2.etat = 4;
    break;

        case SDLK_x:
            p2.v.dx = 20;
            p2.etat = 3;
            p2.run1.pos.y = p2.run1.spriteH * 3;
            p2.run1.index = (p2.run1.index + 1) % p2.run1.max;
            p2.run1.pos.x = p2.run1.index * p2.run1.spriteW;
            p2.score += 10;
            break;
	case SDLK_SPACE:
            if (p2.up ==0)
			{
				p2.up=1;
				posinit2 = p2.posEcran2.y;
				p2.score += 10;
			}
            break;


        }
    }
		else if (event.type == SDL_KEYUP)
    	{
        switch (event.key.keysym.sym)
        {
			case SDLK_LEFT:
            case SDLK_RIGHT:
            p.v.dx = 0;
            p.walk.index = 0;
            p.walk.pos.x = 0;
            p.score += 10;
			break;
        
			case SDLK_c:
            case SDLK_v:
			p.v.dx = 0;
            p.run.index = 0;
            p.run.pos.x = 0;
            p.etat = 0;
            p.score += 10;
            break;
			case SDLK_q:
            case SDLK_d:
            p2.v.dx = 0;
            p2.walk1.index = 0;
            p2.walk1.pos.x = 0;
            p.score += 10;
            break;
			case SDLK_w:
            case SDLK_x:
            p2.v.dx = 0;
            p2.run1.index = 0;
            p2.run1.pos.x = 0;
            p2.etat = 0;
            p.score += 10;
            break;
	/*case SDLK_h:

case SDLK_j:
    p.etat = 0;
    p.attack.index = 0;
    p.attack.pos.x = 0;
    break;*/


        case SDLK_UP:
        case SDLK_z:
            // Ne rien faire ici en général pour le saut,
            // le retour à l'état normal se gère dans la boucle principale
            break;
        }
      }
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



	saut_Personnage(&p, dt, p.posEcran.x, posinit);
	
    saut_Perso(&p2, dt, p2.posEcran2.x, posinit2);

        // Empêcher de sortir de l'écran
        if (p.posEcran.x < 0) p.posEcran.x = 0;
        if (p.posEcran.y < 0) p.posEcran.y = 0;
        if (p.posEcran.x > 1920 - p.walk.spriteW) p.posEcran.x = 1920 - p.walk.spriteW;
        if (p.posEcran.y > 1080 - p.walk.spriteH) p.posEcran.y = 1080 - p.walk.spriteH;
	if (p.posEcran.x > 1920 - p.run.spriteW) p.posEcran.x = 1920 - p.run.spriteW;
        if (p.posEcran.y > 1080 - p.run.spriteH) p.posEcran.y = 1080 - p.run.spriteH;

	if (p2.posEcran2.x < 0) p2.posEcran2.x = 0;
        if (p2.posEcran2.y < 0) p2.posEcran2.y = 0;
	if (p2.posEcran2.x > 1920 - p2.walk1.spriteW) p2.posEcran2.x = 1920 - p2.walk1.spriteW;
        if (p2.posEcran2.y > 1080 - p2.walk1.spriteH) p2.posEcran2.y = 1080 - p2.walk1.spriteH;
	if (p2.posEcran2.x > 1920 - p2.run1.spriteW) p2.posEcran2.x = 1920 - p2.run1.spriteW;
        if (p2.posEcran2.y > 1080 - p2.run.spriteH) p2.posEcran2.y = 1080 - p2.run1.spriteH;


	// Toujours afficher le personnage 1
afficher_perso(ecran, &p);
animer_perso(&p);

// Afficher le perso 2 en plus si activé
if (show_perso2 == 1)
{
	printf("Affichage perso 2\n");
    afficher_perso2(ecran, &p2);
    printf("animer perso 2\n");
    animer_perso2(&p2);
}

	
	afficher_score(&p, ecran, posScore, font, textColor,&p2,posScore2);
	afficher_vie(&p, ecran,&p2);




        SDL_Flip(ecran);
        SDL_Delay(100);
    }

    // LIBÉRATION MÉMOIRE
    SDL_FreeSurface(p.walk.a);
    SDL_FreeSurface(p.dead.a);
    SDL_FreeSurface(p.jump.a);
    SDL_FreeSurface(p.run.a);
    SDL_FreeSurface(p2.walk1.a);
    SDL_FreeSurface(p2.dead1.a);
    SDL_FreeSurface(p2.jump1.a);
    SDL_FreeSurface(p2.run1.a);

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
