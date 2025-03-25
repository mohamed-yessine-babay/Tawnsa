#define HEADER_ENEMY_H
#ifndef HEADER_ENEMY_H

typedef struct
{
	SDL_Surface *img; // normal
	SDL_Surface *touch;// si touché
	SDL_Rect pos_anim[4];// tableau d'animation pour les 4 direction haut bas gauche droite
	int animating; // en plein animation
	int cldw; // attente avant de reanimer (cooldown)
	int max_w;// largeur totale de l'image
	int fps;// nombre d'image
	int i;// qui va parourir les animation
}anim;

typedef struct
{
	int type;// type d'entité : 1 objet , 0 entité classique (bonus, enemy)
	int health;
	int damage;
	int speed;
	int range;
}entit_stat; // statistique des different objet, bonus, enemy etc...

typedef struct
{
	int on_screen;// apparait à l'ecran 
	anim idle;
	SDL_Rect pos_ecran;
	stat_entity stat;
	int is_active;
	int is_taken;
}bonus;

typedef struct
{
	int type;
	int on_screen;// apparait à l'ecran
	SDL_Surface * healthbar;
	SDL_Rect life;
	int is_hit;
	int d;// direction
	anim walk;
	anim run;
	anim attack;
	anim death;
	SDL_Rect pos_ecran;
	entity_stats stats;
	bonus loot;
}enemy;

typedef struct
{
	int level;
	bonus item[3];// des objet : arme, bonus, vie etc...
	enemy mob[3];// 3 type d'enemy par niveau
}entity;



// pour faciliter la modification de rect
SDL_Rect set_rect(int x, int y, int w);

// initialisation des structure

void init_anim(anim *a,char path[], SDL_Rect pos_anim,int w, int h); //animation
entity_stats init_stats(int type,int health, int damage, int speed, int range);//stat
void init_bonus(bonus *b,char path[],SDL_Rect pos_anim, int w, entity_stats stat);// bonus
void init_enemy(enemy *e,char path[],SDL_Rect pos_anim, entity_stats stats, bonus b); //enemy

// animation
void animate(anim *a);

// action enemy



void enemy_walk(enemy *e, SDL_Surface *screen);
void enemy_run(enemy *e, SDL_Surface *screen)

void target_player(enemy *e, SDL_Rect pos_player);

#endif
