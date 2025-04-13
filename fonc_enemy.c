#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "header_enemy.h"


// pour faciliter la modification de rect
SDL_Rect set_Rect(int x, int y, int w, int h)
{
	SDL_Rect r;
	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	return r;
}

void concat(char ** stock, char c1[],char c2[]);

// --------------------------------initialisation des structure----------------------------

// animation
void init_anim(anim *a,char path[], SDL_Rect pos_anim, int fps,int cldw,int snd_anim)
{
	int i;
	a->cldw = cldw;
	a->icldw = cldw;
	char ch[255];
	strcpy(ch,path);
	strcat(ch,"/img.png");
	a->img = IMG_Load(ch);
	if(a->img == NULL)
	{
		fprintf(stderr,"Erreur chargement image %s\n",SDL_GetError());
		exit(1);
	}
	strcpy(ch,path);
	if(snd_anim)
	{
		strcat(ch,"/touch.png");
		a->touch = IMG_Load(ch);
		if(a->touch = NULL)
		{
			fprintf(stderr,"Erreur chargement image %s\n",SDL_GetError());
			exit(1);
		}
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
entity_stats init_stats(int health, int damage, int speed, int range)
{
	entity_stats stat;
	
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
	char ch[255];
	strcpy(ch,path);
	strcat(ch,"/healthbar.png");
	h.hb = IMG_Load(ch);
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
	init_anim(&(b->idle), path,pos_anim, fps,0,1);
	b->pos_ecran = set_Rect(0,0,pos_anim.w,pos_anim.h);
	b->stat = stat;
	b->is_active = 1;
	b->is_taken = 0;
}

// projectile
void init_enemy_projectile(enemy_projectile *p, char path[], int damage, SDL_Rect pos)
{
	char ch[255];
	strcpy(ch,path);
	strcat(ch,"/projectile.png");
	p->on_screen = 0;
	init_anim(&(p->mv),ch, pos , 5,0,0);
	p->damage = damage;
	p->pos = pos;
}		

// enemy
void init_enemy(enemy *e,int type,char path[],SDL_Rect pos_anim, entity_stats stats)
{
	e->type = type;
	e->on_screen = 0;
	e->d = 3;
	char ch[255];
	
	if(!type)
	{
		strcpy(ch,path);
		strcat(ch,"/walk");
		init_anim(&(e->walk), ch, pos_anim, 9,0,1);
		strcpy(ch,path);
		strcat(ch,"/run");
		init_anim(&(e->run), ch, pos_anim, 8,0,1);
	}else
	{
		init_enemy_projectile(&(e->throw_ball),path,stats.damage,pos_anim); 
		strcpy(ch,path);
		strcat(ch,"/fly");
		init_anim(&(e->fly),ch,pos_anim, 9,0,1);
	}
	strcpy(ch,path);
	strcat(ch,"/attack");
	init_anim(&(e->attack),ch, pos_anim, 6,10,1);
	strcpy(ch,path);
	strcat(ch,"/death");
	init_anim(&(e->death),ch, pos_anim, 5,0,0);
	e->is_hit = 0;
	e->pos_ecran = pos_anim;
	e->stats = stats;
	e->target_player = 0;
}




// ------------------animation----------------------------

void animate(anim *a,int d,int *inter, SDL_Surface *screen, SDL_Rect *p_e)
{
	if(a->i < a->fps)
	{
	
		a->pos_anim[d].x = a->i * a->pos_anim[d].w;
		a->i++;
		if(*inter)
		{
			*inter--;
			SDL_BlitSurface(a->touch,&(a->pos_anim[d]),screen,p_e);
		}
		else
			SDL_BlitSurface(a->img,&(a->pos_anim[d]),screen,p_e);
	}
	else
	{	
		a->animating = 0;
	}
}

void anim_reset(anim *a)
{
	if(a->i == a->fps)
	{
		
		if(a->icldw > 0)
		{
			a->icldw--;
		}
		else
		{
			a->icldw = a->cldw;
			a->i = 0;
			a->animating = 1;
		}
	}
}

// --------------------action de base--------------------------

void enemy_direction(SDL_Rect *e, int d, int speed)
{
	switch (d)
	{
		case 0:
			e->y -= speed;
			break;
		case 1:
			e->x -= speed;
			break;
		case 2:
			e->y += speed;
			break;
		case 3:
			e->x += speed;
			break;
	}
}


void enemy_walk(enemy *e, SDL_Surface *screen) // walk
{
	enemy_direction(&(e->pos_ecran),e->d,e->stats.speed/2);
	animate(&(e->walk),e->d,&(e->is_hit), screen, &(e->pos_ecran));
	anim_reset(&(e->walk));
}


void enemy_run(enemy *e, SDL_Surface *screen) // run
{
	enemy_direction(&(e->pos_ecran),e->d,e->stats.speed);
	animate(&(e->run),e->d, &(e->is_hit) ,screen, &(e->pos_ecran));
	anim_reset(&(e->run));
}


// enemy type 1
/*
void enemy_fly(enemy *e, SDL_Surface *screen) // fly
{
	enemy_direction(&(e->pos_ecran),e->d,e->stats.speed);
	animate(&(e->fly),e->d, screen, &(e->pos_ecran));
	anim_reset(&(e->fly));
}
*/

int enemy_attack(enemy *e,SDL_Surface *screen) // attack
{
	int d = 0;
	if(e->attack.animating)
		animate(&(e->attack),e->d,&(e->is_hit),screen,&(e->pos_ecran));
	else
	{
		anim_reset(&(e->attack));
		if(e->attack.animating) d = e->stats.damage;
	}
	return d;
}


void enemy_death(enemy *e,SDL_Surface *screen, int *p_h) // mort
{
	e->d = 0;
	if(e->death.animating)
		animate(&(e->death),e->d,&(e->is_hit),screen,&(e->pos_ecran));
	else
	{
		e->on_screen = 0;
		e->stats.health = 3;
		anim_reset(&(e->death));
		if(*p_h<2)
			*p_h += 1;
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

void enemy_hit(enemy *e,int p_damage, SDL_Rect p, int p_attack) // Subit un coups
{
	if(p_attack == 1 && e->is_hit == 0)
	{
		e->is_hit = 4;
		e->stats.health -= p_damage;
	}
}

void projectile_pp_collision(enemy_projectile *p, int hit_something)
{
	if(hit_something)
	{
		p->on_screen = 0;
	}
}


//--------------------------------affichage-----------------------------------
void set_enemy_position(enemy *e, SDL_Rect pos_p,int d_p,int scr_w, int scr_h)
{
	e->d = (d_p+1)%4;
	switch(d_p)
	{
		case 0:
			e->pos_ecran.x = pos_p.x;
			e->pos_ecran.y = (e->walk.pos_anim[e->d].h );
			break;
		case 1:
			e->pos_ecran.x = (e->walk.pos_anim[e->d].w);
			e->pos_ecran.y = pos_p.y;
			break;
		case 2:
			e->pos_ecran.x = pos_p.x;
			e->pos_ecran.y = scr_h - e->walk.pos_anim[e->d].h;
			break;
		case 3:
			e->pos_ecran.x = scr_w - e->walk.pos_anim[e->d].w;
			e->pos_ecran.y = pos_p.y;
			break;
	}
}
int enemy_random()
{
	srand(time(NULL));
        return (int)rand()%5921;
}


// ----------------------------- movement -------------------------------
void default_movement_enemy(enemy *e, SDL_Surface *screen, SDL_Rect mov)
{
	int distance = 300;
	if( e->d%2 == 0)
	{
		if(e->pos_ecran.y < (mov.h-distance)/2 || (e->pos_ecran.y + e->pos_ecran.h) > (mov.h + distance)/2)
		{
			e->d = (e->d+2)%4;
		}
		enemy_walk(e,screen);
	}	
	else
	{
		if(e->pos_ecran.x < (mov.w-(distance+100))/2 || (e->pos_ecran.x + e->pos_ecran.w )> (mov.w + distance+100)/2)
		{
			e->d = (e->d+2)%4;
		}
		enemy_walk(e,screen);
	}
	//enemy_walk(e,screen);
}

void sinus_movement_enemy(SDL_Rect *e, SDL_Rect mov, int orient)
{	
	if(!orient)
	{
		e->y = mov.y + 50 * sin(0.05 * e->x);
	}
	else
	{
		e->x = mov.x + 50 * sin(0.05 * e->y);
	}
}

void enemy_movement2(enemy *e, SDL_Surface *ecran,SDL_Rect mov,int d_p)
{
	int distance;
	if(e->d%2 == 0)
	{
		distance =400;
		if( e->pos_ecran.x < (mov.w-distance)/2 ||
		e->pos_ecran.x + e->pos_ecran.w > (mov.w+distance)/2)
			e->d = (e->d+2)%4;
	}
	else
	{
		distance = 300;
		if( e->pos_ecran.y < (mov.h-distance)/2 ||
		e->pos_ecran.y + e->pos_ecran.h > (mov.h+distance)/2)
			e->d = (e->d+2)%4;
	}
	
	
	enemy_direction(&(e->pos_ecran), e->d, 1);
	sinus_movement_enemy(&(e->pos_ecran), mov, e->d%2);
	animate(&(e->fly),(d_p+2)%4,&(e->is_hit),ecran, &(e->pos_ecran));
	anim_reset(&(e->fly));
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


void player_walking(enemy *e,player p)
{
	if(p.walking)
	{
		switch (p.d)
		{
			case 0:
				e->pos_ecran.y+= p.stat.speed;
				break;
			case 1:
				e->pos_ecran.x+= p.stat.speed;
				break;
			case 2:
				e->pos_ecran.y-= p.stat.speed;
				break;
			case 3:
				e->pos_ecran.x-= p.stat.speed;
				break;
		}
	}
}

void enemy_behavior(enemy *e, SDL_Surface *screen, player *p,SDL_Rect scr)
{
	if(!e->on_screen)
	{
		set_enemy_position(e, p->p,p->d,scr.w, scr.h);
	}else
	{
		if(e->stats.health >0)
		{
			if(!e->type)
			{
				if(e->target_player)
				{
					if(entity_collision(e->pos_ecran, p->p))
					{
						enemy_hit(e,p->stat.damage, p->p, p->attack);
						p->stat.health -= enemy_attack(e,screen);	
					}
				}
				else
				{
					if(!entity_collision(e->pos_ecran,p->p))
						default_movement_enemy(e,screen,scr);
				}
					
			}
			else
			{
				enemy_movement2(e,screen,scr,p->d);
			}
		
		}
		else
		{
			enemy_death(e,screen, &(p->stat.health));
		}
	}
	SDL_Delay(50);
		
}


