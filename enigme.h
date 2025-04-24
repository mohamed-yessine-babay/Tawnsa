 #ifndef ENIGME_H
#define ENIGME_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include"time.h"
typedef struct
{
	SDL_Surface *img[12];//ay haja chtaffichiha bch ttficha lezim de type sdl surface
	SDL_Rect pos;//sdl rect hya x,y,z,h
	int p;     //numero du image dans cette instant      
}background;
typedef struct
{
	char ch[200];
	SDL_Surface *txt;
	SDL_Rect pos;     
}text;
typedef struct
{
	
	char ch[200];
	SDL_Surface *txt[2];  // texte fih police o pos o couleur [0] blanc    //  [1] rouge
	SDL_Rect pos;
	int p;  //selectionée ou non   
}text_enigme;
typedef struct
{
	SDL_Color color[2];//sdl color pour presenter des couleur rgb
	TTF_Font *police[2];//ttf fond ui aficher des police: AA,aa
	text question;//text question mta3 question
	text_enigme reponse1;//mta3 reponse edheka 3leh zidna engime
	text_enigme reponse2;
	text_enigme reponse3;
	int r_exact ;
	Mix_Chunk *song[2];//mix chunk ayy haja teb3a l musique(2type ki ya5ssir w ki yarba7)
	background question_image;// question image houma barcha tsawr aka 6 edhoukom est une variable qui permet de stocker une image qui est liée a la question de l'enigme
	background back;
	int choix;
	
}enigme;                             

//init
void init_enigme (enigme *e);//3ibara chn7adhr lo8z 9bal mnibda 
void init_backEnigme(background *back);//init arriere plan
void init_question_image(background *question_image);//init d'une image ili tji m3a kol question
//afficher
void afficher_text(SDL_Surface *screen , text t);//aff txt quest
void afficher_text_enigme(SDL_Surface *screen , text_enigme t);//aff txt rep
void afficher_enigme(SDL_Surface *screen , enigme e);//aff total:txt ,image,back..
void animer_backenigme(background *back);//annimation
//mise a jour
void genererEnigme(enigme *e);//doub manod5il nl9a enigme mou3ayn ki njewb wil kol hedha ya3mil mise a jour bich yaffichi l enigme ili min ba3d

//integration
int go_enigme(SDL_Surface *screen);
#endif
