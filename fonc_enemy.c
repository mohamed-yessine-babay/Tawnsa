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

// --------------------------------initialisation des structure----------------------------

// animation
void init_anim(anim *a,char path[], SDL_Rect pos_anim, int fps, int cldw)
{
	int i;
	a->cldw = cldw;
	a->img = IMG_Load(strcat(path,"/img.png"));
	if(a->img == NULL)
	{
		fprintf(stderr,"Erreur chargement image %s\n",SDL_GetError());
		exit(1);
	}
	a->touch = IMG_Load(strcat(path,"/touch.png"));
	if(a->touch = NULL)
	{
		fprintf(stderr,"Erreur chargement image %s\n",SDL_GetError());
		exit(1);
	}
	for(i=0;i<4;i++)
	{
		a->pos_anim[i] = set_Rect(0, i*pos_anim.h, pos_anim.w, pos_anim.h);
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

// health bar
enemy_healthbar init_enemy_healthbar(char path[],int max_health)
{
	enemy_healthbar h;
	h.hb = IMG_Load(strcat(path,"/healthbar"));
	if(h.hb == NULL)
	{
		fprintf(stderr,"Erreur chargement image %s\n",SDL_GetError());
		exit(1);
	}
	h.life = set_Rect(0,0,h.hb->w,h.hb->h);
	h.progress = h.life;
	h.max_health = max_health;
	return h;
}

// bonus
void init_bonus(bonus *b,char path[],SDL_Rect pos_anim, int fps, entity_stats stat)
{
	b->on_screen = 0;
	init_anim(&(b->idle), path,pos_anim, fps,0);
	b->pos_ecran = set_Rect(0,0,pos_anim.w,pos_anim.h);
	b->stat = stat;
	b->is_active = 1;
	b->is_taken = 0;
}

// projectile
void init_enemy_projectile(enemy_projectile *p, char path[], int damage, SDL_Rect pos)
{
	init_anim(&(p->mv),strcat(path,"/projectile.png"), pos , 5,0);
	p->damage = damage;
	p->pos = pos;
}		

// enemy
void init_enemy(enemy *e,int type,char path[],SDL_Rect pos_anim, entity_stats stats, bonus b)
{
	e->type = type;
	e->on_screen = 0;
	e->d = 3;
	if(!type)
	{
		init_anim(&(e->walk),strcat(path,"/walk.png"), pos_anim, 5,0);
		init_anim(&(e->run),strcat(path,"/run.png"), pos_anim, 5,0);
		init_enemy_projectile(&(e->throw_ball),path,stats.damage,pos_anim); 
	}else
		init_anim(&(e->fly),strcat(path,"/fly.png"),pos_anim, 5,0);
	init_anim(&(e->attack),strcat(path,"/attack.png"), pos_anim, 5,10);
	init_anim(&(e->death),strcat(path,"/death.png"), pos_anim, 5,0);
	e->pos_ecran = pos_anim;
	e->stats = stats;
	e->loot = b;
}




// ------------------animation----------------------------

void animate(anim *a,int d,/*int *inter,*/ SDL_Surface *screen, SDL_Rect *p_e)
{
	if(a->i < a->fps)
	{
	
		a->pos_anim[d].x = a->i * a->pos_anim[d].w;
		a->i++;
		/*
		if(inter)
		{
			*inter = 0;
			SDL_BlitSurface(a->touch,&(a->pos_anim[d]),screen,p_e);
		}
		else*/
			SDL_BlitSurface(a->img,&(a->pos_anim[d]),screen,p_e);
		SDL_Delay(100/a->fps);
	}else
		a->i = 0;
		a->animating = 0;
}

void anim_reset(anim *a)
{
	if(a->i == a->fps)
		if(a->cldw > 0)
			a->cldw--;
		else
			a->animating = 1;
}

// --------------------action--------------------------



void enemy_walk(enemy *e, SDL_Surface *screen) // walk
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
	animate(&(e->walk),e->d, screen, &(e->pos_ecran));
	anim_reset(&(e->walk));
}


void enemy_run(enemy *e, SDL_Surface *screen) // run
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
	animate(&(e->run),e->d, screen, &(e->pos_ecran));
	anim_reset(&(e->run));
}

void enemy_fly(enemy *e, SDL_Surface *screen) // run
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
	animate(&(e->fly),e->d, screen, &(e->pos_ecran));
	anim_reset(&(e->fly));
}


int enemy_attack(enemy *e,SDL_Surface *screen) // attack
{
	int d = 0;
	if(e->attack.animating)
		animate(&(e->attack),e->d,screen,&(e->pos_ecran));
	else
	{
		anim_reset(&(e->attack));
		if(e->attack.animating) d = e->stats.damage;
	}
	return d;
}


void enemy_death(enemy *e,SDL_Surface *screen, int p_h, int p_maxh) // mort
{
	if(e->death.animating)
		animate(&(e->death),e->d,screen,&(e->pos_ecran));
	else
	{
		e->on_screen = 0;
		if((float)p_h/p_maxh<0.5)
			e->loot.on_screen = 1;
	}
}

// ----------------------------interaction-----------------------------------

int entity_collision(SDL_Rect e, SDL_Rect p)// Collision
{
	if(e.x > (p.x+p.w) || e.y > (p.y+p.h) || (e.x + e.w) < p.x || (e.y + e.h) < p.y)
		return 0;
	else
		return 1;
}

int enemy_is_hit(enemy e,int p_damage, SDL_Rect p, int p_attack) // Subit un coups
{
	if(entity_collision(e.pos_ecran, p) && p_attack == 1)
		return 1;
	else
		return 0;
}




// se dirige vers le joueur
/*
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
*/




