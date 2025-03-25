#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string.h>
#include "header_enemy.h"


// pour faciliter la modification de rect
SDL_Rect set_Rect(int x, int y, int w,int h)
{
	SDL_Rect r;
	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	return r;
}

// initialisation des structure

// animation
void init_anim(anim *a,char path[], SDL_Rect pos_anim, int fps)
{
	int i;
	a->img = IMG_Load(strcat(path,"/img.png");
	if(a->img == NULL)
	{
		fprintf(stderr,"Erreur chargement image %s\n",SDL_GetError());
		exit(1);
	}
	a->touch = IMG_Load(strcat(path,"/touch.png");
	if(a->touch = NULL)
	{
		fprintf(stderr,"Erreur chargement image %s\n",SDL_GetError());
		exit(1);
	}
	for(i=0;i<4;i++)
	{
		a->pos_anim[i] = set_Rect(0, i*pos_anim.h, pos_anim.w, pos_anim.h)
	}
	a->animating = 1;
	a->max_w = fps*pos_anim.w;
	a->fps = fps;
	a->i = 0;
}


// stat
entity_stats init_stats(int type,int health, int damage, int speed, int range)
{
	entity_stats stat;
	
	stat.type = type;
	stat.health = health;
	stat.damage = damage;
	stat.speed = speed;
	stat.range = range;
	
	return stat;
}

// bonus
void init_bonus(bonus *b,char path[],SDL_Rect pos_anim, int fps, entity_stats stat)
{
	b->on_screen = 0;
	init_anim(&(b->idle), path,pos_anim, fps);
	b->pos_ecran = set_Rect(0,0,pos_anim.w,pos_anim.h);
	b->stat = stat;
	b->is_active = 1;
	b->is_taken = 0;
}

// enemy
void init_enemy(enemy *e,char path[],SDL_Rect pos_anim, entity_stats stats, bonus b)
{
	e->on_screen = 0;
	e->d = 3;
	init_anim(&(e->walk),strcat(path,"/walk.png"), pos_anim, 5);
	
	init_anim(&(e->run),strcat(path,"/run.png"), pos_anim, 5);
	init_anim(&(e->attack),strcat(path,"/attack.png"), pos_anim, 5);
	init_anim(&(e->death),strcat(path,"/death.png"), pos_anim, 5);
	e->pos_ecran = pos_anim;
	e->stats = stats;
	e->has_loot = 0;
	e->bonus = b;
}

// action de l'enemy



// animation
void animate(anim *a,int d,int *inter, SDL_Surface *screen, SDL_Rect *p_e)
{
	;
	if(i<fps)
	{
	
		a->pos_anim.x = a->i * pos_anim.w;
		a->i++;
		if(inter)
		{
			*inter = 0;
			SDL_BlitSurface(a->touch,&(a->posanim[d]),screen,p_e);
		}
		else
			SDL_BlitSurface(a->img,&(a->posanim[d]),screen,p_e);
		SDL_Delay(100/a->fps);
	}else
		a->i = 0
		a->animating = 0;
}

// reset animation
void anim_reset(anim *a)
{
	if(a->i == fps)
		if(a->cldw > 0)
			a->cldw--;
		else
			a->animating = 1;
	

// marche
void enemy_walk(enemy *e, SDL_Surface *screen)
{
	switch (e->d)
	{
		case 0:
			e->pos_ecran.y -= (e->stats.speed)/2;
			break;
		case 1:
			e->pos_ecran.x -= (e->stats.speed)/2;
			break;
		case 2:
			e->pos_ecran.y += (e->stats.speed)/2;
			break;
		case 3:
			e->pos_ecran.x += (e->stats.speed)/2;
			break;
	}
	animate(&(e->walk),e->d,0, screen, e->pos_ecran);
	anim_reset(&(e->walk));
}


// course
void enemy_run(enemy *e, SDL_Surface *screen)
{
	switch (e->d)
	{
		case 0:
			e->pos_ecran.y -= (e->stats.speed);
			break;
		case 1:
			e->pos_ecran.x -= (e->stats.speed);
			break;
		case 2:
			e->pos_ecran.y += (e->stats.speed);
			break;
		case 3:
			e->pos_ecran.x += (e->stats.speed);
			break;
	}
	animate(&(e->run),e->d,0, screen, e->pos_ecran);
	anim_reset(&(e->run));
}


// attaque
int enemy_attack(enemy *e,SDL_Surface *screen)
{
	int d = 0;
	if(e->attack.animating)
		animate(&(e->attack),e->d,10,screen,e->pos_ecran);
	else
	{
		anim_reset(&(e->attack));
		if(e->attack.animating) d = e->stats.damage;
	}
	return d;
}

// mort
void enemy_death(enemy *e,SDL_Surface *screen, int p_h, int p_maxh)
{
	if(e->death.animating)
		animate(&(e->death),e->d,0,screen,e->pos_ecran)
	else
	{
		e->on_screen = 0;
		if(float(p_h)/p_max<0.5)
			e->loot.on_screen = 1;
	}
}



int enemy_is_hit(enemy *e,int p_damage, SDL_Rect p,)
{
	e->health
}

// Collision
int entity_collision(SDL_Rect e, SDL_Rect p)
{
	if(e.x > (p.x+p.w) || e.y > (p.y+p.h) || (e.x + e.w) < p.x || (e.y + e.h) < p.y)
		return 0;
	else
		return 1;
}


// se dirige vers le joueur
void goto_player(enemy *e, SDL_Rect p,SDL_Surface *scr)
{	
	if(e->pos_ecran.y + e->pos_ecran.h < p.y)
	{
		e->d = 0;
		enemy_run(e,scr);
	}
	if(e->pos_ecran.x > p.x + p.w)
	{
		e->d = 1;
		enemy_run(e,scr);
	}
	if(e->pos_ecran.y > p.y + p.h)
	{
		e->d = 2;
		enemy_run(e,scr);
	}
	if(e->pos_ecran.x + e->pos_ecran.w < p.x)
	{
		e->d = 3;
		enemy_run(e,scr);
	}	
}




