#define HEADER_ENEMY_H
#ifndef HEADER_ENEMY_H

typedef struct
{
	SDL_Surface *img;
	SDL_Rect pos_anim[4];// tableau d'animation pour les 4 direction haut bas gauche droite
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
}stats_entity; // statistique des different objet, bonus, enemy etc...

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
	int on_screen;// apparait à l'ecran
	int state;
	anim walk;
	anim run;
	anim attack;
	anim death;
	SDL_Rect pos_ecran;
	stats_entity stats;
	int has_loot;
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
stats_entity init_stats(int type,int health, int damage, int speed, int range);//stat
void init_bonus(bonus *b,char path[],SDL_Rect pos_anim, int w, stats_entity stat);// bonus
void init_enemy(enemy *e,char path[],SDL_Rect pos_anim, stats_entity stats, bonus b); //enemy

// action de l'enemy
void target_player(enemy *e, SDL_Rect pos_player);
void animate(anim *a);
void animate_loop(anim *a);

#endif
