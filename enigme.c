#include "enigme.h"

// Initialisation de l'énigme
void init_enigme(enigme *e)
{
	int d =100;
    int num;
    e->choix = 0;
    FILE *fichier = fopen("enigme.txt", "r");
    if (fichier != NULL)
    {
        num = -1;
        do
        {
            fgets(e->question.ch, 500, fichier);
            fgets(e->reponse1.ch, 100, fichier);
            fgets(e->reponse2.ch, 100, fichier);
            fgets(e->reponse3.ch, 100, fichier);
            fscanf(fichier, "%d\n", &e->r_exact);
            num++;
        } while (num != e->choix);

        e->question_image.p = e->choix;

        e->color[0] = (SDL_Color){255, 255, 255};
        e->color[1] = (SDL_Color){255, 0, 0};

        e->police[0] = TTF_OpenFont("police/Ubuntu-Bold.ttf", 20);
        e->police[1] = TTF_OpenFont("police/Merriweather-Black.ttf", 40);

        e->question.txt = TTF_RenderText_Blended(e->police[0], e->question.ch, e->color[0]);

        e->reponse1.txt[0] = TTF_RenderText_Blended(e->police[0], e->reponse1.ch, e->color[0]);
        e->reponse1.txt[1] = TTF_RenderText_Blended(e->police[1], e->reponse1.ch, e->color[1]);

        e->reponse2.txt[0] = TTF_RenderText_Blended(e->police[0], e->reponse2.ch, e->color[0]);
        e->reponse2.txt[1] = TTF_RenderText_Blended(e->police[1], e->reponse2.ch, e->color[1]);

        e->reponse3.txt[0] = TTF_RenderText_Blended(e->police[0], e->reponse3.ch, e->color[0]);
        e->reponse3.txt[1] = TTF_RenderText_Blended(e->police[1], e->reponse3.ch, e->color[1]);

        e->question.pos = (SDL_Rect){d+0, 510};
        e->reponse1.pos = (SDL_Rect){d+50, 550, e->reponse1.txt[0]->w, e->reponse1.txt[0]->h};
        e->reponse2.pos = (SDL_Rect){d+50, 600, e->reponse2.txt[0]->w, e->reponse2.txt[0]->h};
        e->reponse3.pos = (SDL_Rect){d+50, 650, e->reponse3.txt[0]->w, e->reponse3.txt[0]->h};

        e->reponse1.p = e->reponse2.p = e->reponse3.p = 0;

        e->song[0] = Mix_LoadWAV("song/success-1-6297.wav");
        e->song[1] = Mix_LoadWAV("song/negative_beeps-6008.wav");

        init_backEnigme(&e->back);
    }
}

// Initialisation des backgrounds
void init_backEnigme(background *back)
{
    char nom[50], num[3];
        back->img[0] = IMG_Load("enigme image/bg.png");
       back->p=0;
    back->pos = (SDL_Rect){0, 0, 1400, 1000};
}


void afficher_text(SDL_Surface *screen, text txt)
{
    SDL_BlitSurface(txt.txt, NULL, screen, &txt.pos);
}

void afficher_text_enigme(SDL_Surface *screen, text_enigme txt)
{
    SDL_BlitSurface(txt.txt[txt.p], NULL, screen, &txt.pos);
}

void afficher_enigme(SDL_Surface *screen, enigme e)
{
    SDL_BlitSurface(e.back.img[e.back.p], NULL, screen, &e.back.pos);
    afficher_text(screen, e.question);
    afficher_text_enigme(screen, e.reponse1);
    afficher_text_enigme(screen, e.reponse2);
    afficher_text_enigme(screen, e.reponse3);
}

void animer_backenigme(background *back)
{
    back->p = (back->p + 1) % 3;
}

void genererEnigme(enigme *e)
{
    int num;
    e->choix = (e->choix + 1) % 5;
    FILE *fichier = fopen("enigme.txt", "r");

    if (fichier != NULL)
    {
        num = -1;
        do
        {
            fgets(e->question.ch, 500, fichier);
            fgets(e->reponse1.ch, 100, fichier);
            fgets(e->reponse2.ch, 100, fichier);
            fgets(e->reponse3.ch, 100, fichier);
            fscanf(fichier, "%d\n", &e->r_exact);
            num++;
        } while (num != e->choix);

        e->question_image.p = e->choix;

        SDL_FreeSurface(e->question.txt);
        SDL_FreeSurface(e->reponse1.txt[0]);
        SDL_FreeSurface(e->reponse1.txt[1]);
        SDL_FreeSurface(e->reponse2.txt[0]);
        SDL_FreeSurface(e->reponse2.txt[1]);
        SDL_FreeSurface(e->reponse3.txt[0]);
        SDL_FreeSurface(e->reponse3.txt[1]);

        e->question.txt = TTF_RenderText_Blended(e->police[0], e->question.ch, e->color[0]);
        e->reponse1.txt[0] = TTF_RenderText_Blended(e->police[0], e->reponse1.ch, e->color[0]);
        e->reponse1.txt[1] = TTF_RenderText_Blended(e->police[1], e->reponse1.ch, e->color[1]);
        e->reponse2.txt[0] = TTF_RenderText_Blended(e->police[0], e->reponse2.ch, e->color[0]);
        e->reponse2.txt[1] = TTF_RenderText_Blended(e->police[1], e->reponse2.ch, e->color[1]);
        e->reponse3.txt[0] = TTF_RenderText_Blended(e->police[0], e->reponse3.ch, e->color[0]);
        e->reponse3.txt[1] = TTF_RenderText_Blended(e->police[1], e->reponse3.ch, e->color[1]);

        e->reponse1.p = e->reponse2.p = e->reponse3.p = 0;
    }
}

