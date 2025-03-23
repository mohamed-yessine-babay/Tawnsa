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
	a->img = IMG_Load(path);
	if(a->img == NULL)
	{
		fprintf(stderr,"Erreur chargement image %s\n",SDL_GetError());
		exit(1);
	}
	for(i=0;i<4;i++)
	{
		a->pos_anim[i] = set_Rect(0, i*pos_anim.h, pos_anim.w, pos_anim.h)
	}
	a->max_w = fps*pos_anim.w;
	a->fps = fps;
	a->i = 0;
}


// stat
stats_entity init_stats(int type,int health, int damage, int speed, int range)
{
	stats_entity stat;
	
	stat.type = type;
	stat.health = health;
	stat.damage = damage;
	stat.speed = speed;
	stat.range = range;
	
	return stat;
}

// bonus
void init_bonus(bonus *b,char path[],SDL_Rect pos_anim, int fps, stats_entity stat)
{
	b->on_screen = 0;
	init_anim(&(b->idle), path,pos_anim, fps);
	b->pos_ecran = set_Rect(0,0,pos_anim.w,pos_anim.h);
	b->stat = stat;
	b->is_active = 1;
	b->is_taken = 0;
}

// enemy
void init_enemy(enemy *e,char path[],SDL_Rect pos_anim, stats_entity stats, bonus b)
{
	e->on_screen = 0;
	e->state = 3;
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

// joueur en vue
void target_player(enemy *e, SDL_Rect pos_player)
void animate(anim *a);
void animate_loop(anim *a);

