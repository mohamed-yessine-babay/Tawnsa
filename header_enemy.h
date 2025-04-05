#ifndef HEADER_ENEMY_H
#define HEADER_ENEMY_H

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
}entity_stats; // statistique des different objet, bonus, enemy etc...

typedef struct
{
	SDL_Surface * hb;
	SDL_Rect life;
	SDL_Rect progress;
	int max_health;
}enemy_healthbar;

typedef struct
{
	int on_screen;// apparait à l'ecran 
	anim idle;
	SDL_Rect pos_ecran;
	entity_stats stat;
	int is_active;
	int is_taken;
}bonus;



typedef struct
{
	anim mv;
	int damage;
	SDL_Rect pos;
}enemy_projectile;

typedef struct
{
	int type;// type d'enemy 0 se deplace au sol 1 vole
	int on_screen;// apparait à l'ecran
	int d;// direction
	SDL_Rect pos_ecran; // position ecran	
	enemy_healthbar healthbar;
	// animation type 0
	anim walk;
	anim run;
	// animation type 1
	anim fly;
	// animation commune
	anim attack;
	anim death;
	// projectile pour le 2eme type d'enemie
	enemy_projectile throw_ball;
	entity_stats stats;
	bonus loot;// donne un bonus si le joueur est blessé apres la mort de l'enemie
}enemy;



typedef struct
{
	int level;
	bonus item[3];// des objet : arme, bonus, vie etc...
	enemy mob[3];// 3 type d'enemy par niveau
}entity;



// pour faciliter la modification de rect
SDL_Rect set_Rect(int x, int y, int w, int h);

// -----------------------------initialisation des structure-----------------------------

void init_anim(anim *a,char path[], SDL_Rect pos_anim, int fps,int cldw); //animation
entity_stats init_stats(int type,int health, int damage, int speed, int range);//stat
enemy_healthbar init_enemy_healthbar(char path[],int max_health); // barre de vie
void init_bonus(bonus *b,char path[],SDL_Rect pos_anim, int w, entity_stats stat);// bonus
void init_enemy_projectile(enemy_projectile *p, char path[], int damage, SDL_Rect pos);
void init_enemy(enemy *e,int type,char path[],SDL_Rect pos_anim, entity_stats stats, bonus b); //enemy

// -----------------------------animation-----------------------------
void animate(anim *a,int d,/*int *inter,*/ SDL_Surface *screen, SDL_Rect *p_e);
void anim_reset(anim *a);

// -----------------------------action de base -----------------------------
void enemy_direction(SDL_Rect *e, int d, int speed);
void enemy_walk(enemy *e, SDL_Surface *screen); // walk
void enemy_run(enemy *e, SDL_Surface *screen); // run
int enemy_attack(enemy *e,SDL_Surface *screen); // attack
void enemy_fly(enemy *e, SDL_Surface *screen); // fly
void enemy_death(enemy *e,SDL_Surface *screen, int p_h, int p_maxh); // mort

// -----------------------------interactions -----------------------------
int entity_collision(SDL_Rect e, SDL_Rect p);// Collision
int enemy_is_hit(enemy e,int p_damage, SDL_Rect p, int p_attack);


//--------------------------------affichage--------------------------------
void set_enemy_position(enemy *e, SDL_Rect pos_p,int d_p,int scr_w, int scr_h);
void show_enemy(enemy *e, SDL_Surface *screen);
int enemy_random();

// ----------------------------- movement -------------------------------
void default_movement_enemy(enemy *e, SDL_Surface *screen,int h, int w);
void sinus_movement_enemy(SDL_Rect *e, SDL_Rect mov, int orient);
void enemy_movement2(enemy *e, SDL_Surface *ecran,SDL_Rect mov,int d_p);

#endif
