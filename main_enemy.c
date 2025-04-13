#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include "header_enemy.h"

#define sW 1680
#define sH 720


typedef struct
{
	SDL_Surface *i;
	SDL_Rect pos;
	SDL_Rect ipos;
	SDL_Rect state[4];
	int walk;
	int l;
}img;


void setRect(SDL_Rect *r,int x, int y, int w, int h)
{
	r->x = x;
	r->y = y;
	r->w = w;
	r->h = h;
}

int main(int argc, char** argv)
{
	SDL_Surface *ecran;
	img lamis;
	lamis.walk = 0;
	player lamis_p;
	lamis_p.p = lamis.pos;
	lamis_p.max_health = 3;
	lamis_p.score = 1;
	enemy e1;
	int sw = sW;
	int sh = sH;
	int i,j=0,running = 1,p = 0,step = 15;
	lamis_p.stat = init_stats(3,1,step,0);
	init_enemy(&e1,0,"entity/level 1/enemy/enemy 1",set_Rect(0,0,63,67), init_stats(3,1,5,0));
	lamis.l = 576;
	setRect(&(lamis.pos),(sW -64)/2,(sH-67)/2,64,67);
	for(i=0;i<4;i++)
		setRect(&(lamis.state[i]),0,i*67,64,67);
	
	if(SDL_Init(SDL_INIT_VIDEO)<0)
	{
		printf("initialisation video echouée %s\n",SDL_GetError());
		return 1;
	}
	
	ecran = SDL_SetVideoMode(sW, sH , 32 , SDL_HWSURFACE | SDL_DOUBLEBUF);
	
	if(ecran == NULL)
	{
		fprintf(stderr,"probleme ecran %s\n",SDL_GetError());
		return 1;
	}	
	
	lamis.i = IMG_Load("walk.png");
	if(lamis.i == NULL)
	{
		fprintf(stderr,"probleme lamis %s\n",SDL_GetError());
		return 1;
	}
	
	while(running)
	{
		SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					running = 0;
					break;
				case SDL_KEYDOWN:
					
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							running = 0;
							break;
						case SDLK_UP:
							p = 0;
							lamis.walk = 1;
							break;
						case SDLK_LEFT:
							p = 1;
							lamis.walk = 1;
							break;
						case SDLK_DOWN:
							p = 2;
							lamis.walk = 1;
							break;
						case SDLK_RIGHT:
							p = 3;
							lamis.walk = 1;
							break;
						case SDLK_e:
							e1.on_screen =1;
							break;
						case SDLK_d:
							e1.stats.health = 0;
					}
					break;
				case SDL_KEYUP:
					switch(event.key.keysym.sym)
					{
						case SDLK_UP:
							lamis.walk = 0;
							break;
						case SDLK_LEFT:
							lamis.walk = 0;
							break;
						case SDLK_DOWN:
							lamis.walk = 0;
							break;
						case SDLK_RIGHT:
							lamis.walk = 0;
							break;
					}
					break;
			}
		}
		lamis_p.walking = lamis.walk;
		if(lamis.walk)
		{
			switch(p)
			{
				case 0:
					if(lamis.pos.y >0)
						lamis.pos.y-= step;
					else
						lamis.pos.y = 0;
					break;
				case 1:
					if(lamis.pos.x >0)
						lamis.pos.x-= step;
					else
						lamis.pos.x = 0;
					break;
				case 2:
					if((lamis.pos.y+lamis.pos.h) <sh)
						lamis.pos.y+= step;
					else
						lamis.pos.y = sh-lamis.pos.h;
					break;
				case 3:
					if((lamis.pos.x+lamis.pos.w) <sw)
						lamis.pos.x+= step;
					else
						lamis.pos.x = sw-lamis.pos.w;
					break;
			}
			i+=64;
			lamis.state[p].x = i%(lamis.l);
		}else
			
			lamis.state[p].x = 0;
		lamis_p.d = p;
		lamis_p.p = lamis.pos;
		SDL_BlitSurface(lamis.i,&(lamis.state[p]),ecran,&(lamis.pos));
		enemy_behavior(&e1, ecran, &(lamis_p), set_Rect(0,0,sW,sH));
		SDL_Flip(ecran);
	}
	SDL_FreeSurface(lamis.i);
	SDL_Quit();
	return 0;
}
