#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL_ttf.h>
#define ALTO  700
#define ANCHO 1200

SDL_Surface *screen=NULL,*font, *imagen[12];
SDL_Color font_color,line_color, font_color1, font_color2; //1.- blanco, 2.- Negro
TTF_Font *fuente, *fuente1, *fuente2;
SDL_Rect pixel;
SDL_Rect burbuja;
#define TAM 7

SDL_Rect posiciones[7][8];

typedef struct nodo
{
	char dato[100];
	int NR;
	struct nodo* sig;
}NODO;
typedef NODO* PNODO;

PNODO TABLA[TAM];

int hash(char *cad)
{
	int i=0, r=0;
	while(cad[i]!='\0')
	{
		r=((r*31)%TAM + cad[i]%TAM)%TAM;
		i++;
	}
	return r;
}

void opciones(char *c,int x,int y)
{	
	
	SDL_Rect pos;
	font = TTF_RenderText_Solid(fuente,c,font_color2);
	pos.x=x;
	pos.y=y;
	SDL_BlitSurface(font,NULL,screen,&pos);
	SDL_Flip(screen);	
}

int visualizar(int m)
{
	int x=70,y=450;
	PNODO aux=TABLA[m];
	while(aux!=NULL)
	{	
		opciones(aux->dato,x,y);
		y+=25;
		aux=aux->sig;
	}
	return 0;
}

void numeros(SDL_Rect p, int d)
{
	SDL_Rect pos;
	char vec[100];
	sprintf(vec,"%d",d);
	font = TTF_RenderText_Solid(fuente2,vec,font_color1);
	pos.x=p.x+20;
	pos.y=p.y+15;
	SDL_BlitSurface(font,NULL,screen,&pos);
}

void recorrido(int m, int n)
{
	int i;
	for(i=0; i<=m;i++ )
	{
		pixel.x=posiciones[i][0].x; pixel.y=posiciones[i][0].y; pixel.w=50; pixel.h=10;
		SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,246,46,197,0));
		SDL_Delay(500);
		SDL_Flip(screen);
		if(i!=m) 
		{
			SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,40,183,29,255));
			SDL_Delay(500);
			SDL_Flip(screen); 
		}
	}
	
	for(i=1; i<=n;i++)
	{
		pixel.x=posiciones[m][i].x; pixel.y=posiciones[m][i].y; pixel.w=50; pixel.h=10;
		SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,246,46,197,0));
		SDL_Delay(500);
		SDL_Flip(screen); 
		
		if(i!=n) 
		{
			SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,200,123,13,0));
			SDL_Delay(500);
			SDL_Flip(screen); 
		}
	}
}

void insertar(char *cad)
{
	int m=hash(cad), i=1;
	
	PNODO nuevo=(PNODO)malloc(sizeof(NODO));
	PNODO aux=TABLA[m];
	if(nuevo==NULL)
	{
		printf("No hay memoria\n");
		exit(0);
	}
	while(aux!=NULL)
	{
		
		if(strcmp(cad,aux->dato)==0)
		{
			aux->NR++;
			if(i<8)
			{
				SDL_FillRect(screen, &posiciones[m][i], SDL_MapRGBA(screen->format,200,123,13,0));
				numeros(posiciones[m][i], aux->NR);
				SDL_Flip(screen);
			}
			return;
		}
		aux=aux->sig;
		i++;
	}
	nuevo->sig=TABLA[m];
	nuevo->NR=1;
	strcpy(nuevo->dato,cad);
	TABLA[m]=nuevo;
	if(i<8)
	{
		SDL_FillRect(screen, &posiciones[m][i], SDL_MapRGBA(screen->format,200,123,13,0));
		numeros(posiciones[m][i], 1);
		SDL_Flip(screen);
	}
}

int buscar(char *cad)
{
	int m=hash(cad), i=1;
	PNODO aux=TABLA[m];
	while(aux!=NULL)
	{	if(strcmp(aux->dato,cad)==0)
		{	
			recorrido(m,i);
			pixel.x = 50; pixel.y = 308; pixel.w = 350; pixel.h = 30;
			SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
			opciones("Palabra encontrada", 135, 310);
			pixel.x=posiciones[m][0].x; pixel.y=posiciones[m][0].y; pixel.w=50; pixel.h=10;
			SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,40,183,29,255));
			if(i>0)
			{	pixel.x=posiciones[m][i].x; pixel.y=posiciones[m][i].y; pixel.w=50; pixel.h=10;
				SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,200,123,13,0));
			}
			
			SDL_Delay(2000);
			SDL_Flip(screen); 
			return 1;
		}
		aux=aux->sig;
		i++;
	}
	
			pixel.x = 50; pixel.y = 308; pixel.w = 350; pixel.h = 30;
			SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
			opciones("No se encontro palabra", 135, 310);
		
	return 0;
}

void entorno()
{
	pixel.x = 0; pixel.y = 0; pixel.w = 1200; pixel.h = 700;//general	
	SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,40,183,29,255));
	
	pixel.x = 10; pixel.y = 100; pixel.w = 400; pixel.h = 590;//izquierda	
	SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
	
	pixel.x = 420; pixel.y = 100; pixel.w = 770; pixel.h = 500;//derecha
	SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
	
	pixel.x = 420; pixel.y = 610; pixel.w = 770; pixel.h = 80; //abajo
	SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
	
	pixel.x = 110; pixel.y = 105; pixel.w = 200; pixel.h = 35;//menu	
	SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,40,183,29,255));
	
	burbuja.x = 412; burbuja.y =0; 
	burbuja.w=imagen[0]->w; burbuja.h=imagen[0]->h;//BURBUJA
	SDL_BlitSurface(imagen[0], NULL, screen, &burbuja);
	
	SDL_Flip(screen);
}

void tabla()
{
	int i,j;
	for(i=0; i<7; i++)
		for(j=0; j<8; j++)
		{
			if(j==0)
			{
				posiciones[i][j].x=500; posiciones[i][j].y=145+i*60; posiciones[i][j].w=50; posiciones[i][j].h=50; 
				SDL_FillRect(screen, &posiciones[i][j], SDL_MapRGBA(screen->format,40,183,29,255));
			}
			else
			{   
				posiciones[i][j].x=580+j*65; posiciones[i][j].y=145+i*60; posiciones[i][j].w=50; posiciones[i][j].h=50; 
				SDL_FillRect(screen, &posiciones[i][j], SDL_MapRGBA(screen->format,200,123,13,0));
			}
			
		}
	for(i=0; i<7; i++)
		numeros(posiciones[i][0], i);
	for(i=0; i<7; i++)
		for(j=1; j<8; j++)
			numeros(posiciones[i][j], 0);
		
}

void menu()
{
	char vec[100];
	SDL_Rect pos;
	
	
	fuente1=TTF_OpenFont("font/FortuneCity.ttf",30);
	if(fuente1==NULL)
	{	printf("Error al al leer fuente\n");}
	font_color1.r=255; font_color1.g=255; font_color1.b=255;	
	
	strcpy(vec,"= MENU =");
	pos.x=145;
	pos.y=106;
	font = TTF_RenderText_Solid(fuente1,vec,font_color1);
	SDL_BlitSurface(font,NULL,screen,&pos);
	
	fuente2=TTF_OpenFont("font/FortuneCity.ttf",20);
	if(fuente2==NULL)
	{	printf("Error al al leer fuente\n");}
	font_color2.r=0; font_color2.g=0; font_color2.b=0;	
	
	fuente=TTF_OpenFont("font/FortuneCity.ttf",17);
	if(fuente==NULL)
	{	printf("Error al al leer fuente\n");}
	
	strcpy(vec,"1.- Insertar una palabra");
	font = TTF_RenderText_Solid(fuente2,vec,font_color2);
	pos.x=55;
	pos.y=160;
	SDL_BlitSurface(font,NULL,screen,&pos);
	
	strcpy(vec,"2.- Buscar una palabra ");
	font = TTF_RenderText_Solid(fuente2,vec,font_color2);
	pos.x=55;
	pos.y=190;
	SDL_BlitSurface(font,NULL,screen,&pos);
	
	strcpy(vec,"3.- Visualizar palabras de un valor");
	font = TTF_RenderText_Solid(fuente2,vec,font_color2);
	pos.x=55;
	pos.y=220;
	SDL_BlitSurface(font,NULL,screen,&pos);
	
	strcpy(vec,"4.- Salir");
	font = TTF_RenderText_Solid(fuente2,vec,font_color2);
	pos.x=55;
	pos.y=250;
	SDL_BlitSurface(font,NULL,screen,&pos);
	
	strcpy(vec,"(Teclea una opcion)");
	font = TTF_RenderText_Solid(fuente,vec,font_color2);
	pos.x=135;
	pos.y=310;
	SDL_BlitSurface(font,NULL,screen,&pos);
	
	SDL_Flip(screen); 
}

void lectura(char vec2[])
{
	SDL_Event evento;
	SDL_Rect pos;
	int n=0;
	char vec[100];
	while(1)
	{
			
		//pixel.x = 420; pixel.y = 610; pixel.w = 770; pixel.h = 80; //abajo
		//SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
		opciones("Inserta una palabra:", 735, 615);
		
		SDL_WaitEvent(&evento);
		if(evento.type==SDL_KEYDOWN)
		{
			switch(evento.key.keysym.sym)
			{
				case SDLK_a: vec2[n++]='a'; vec2[n]='\0';
							break;
				case SDLK_b: vec2[n++]='b'; vec2[n]='\0';
							break;
				case SDLK_c: vec2[n++]='c'; vec2[n]='\0';
							break;
				case SDLK_d: vec2[n++]='d'; vec2[n]='\0';
							break;
				case SDLK_e: vec2[n++]='e'; vec2[n]='\0';
							break;
				case SDLK_f:  vec2[n++]='f'; vec2[n]='\0';
							break;
				case SDLK_g: vec2[n++]='g'; vec2[n]='\0';
							break;
				case SDLK_h:  vec2[n++]='h'; vec2[n]='\0';
							break;
				case SDLK_i:  vec2[n++]='i'; vec2[n]='\0';
							break;
				case SDLK_j: vec2[n++]='j'; vec2[n]='\0';
							break;
				case SDLK_k: vec2[n++]='k'; vec2[n]='\0';
							break;
				case SDLK_l: vec2[n++]='l'; vec2[n]='\0';
							break;
				case SDLK_m: vec2[n++]='m'; vec2[n]='\0';
							break;
				case SDLK_n: vec2[n++]='n'; vec2[n]='\0';
							break;
				case SDLK_o: vec2[n++]='o'; vec2[n]='\0';
							break;
				case SDLK_p: vec2[n++]='p'; vec2[n]='\0';
							break;
				case SDLK_q: vec2[n++]='q'; vec2[n]='\0';
							break;
				case SDLK_r: vec2[n++]='r'; vec2[n]='\0';
							break;
				case SDLK_s: vec2[n++]='s'; vec2[n]='\0';
							break;
				case SDLK_t: vec2[n++]='t'; vec2[n]='\0';
							break;
				case SDLK_u: vec2[n++]='u'; vec2[n]='\0';
							break;
				case SDLK_v: vec2[n++]='v'; vec2[n]='\0';
							break;
				case SDLK_w: vec2[n++]='w'; vec2[n]='\0';
							break;
				case SDLK_x: vec2[n++]='x'; vec2[n]='\0' ;
							break;
				case SDLK_y: vec2[n++]='y'; vec2[n]='\0' ;
							break;
				case SDLK_z: vec2[n++]='z'; vec2[n]='\0';
							break;																			
				case SDLK_RETURN:  return;
				
			}
			
			//pixel.x = 340; pixel.y = 600; pixel.w = 50; pixel.h = 50;	// abajo derecha
			//SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,0,255));
			font = TTF_RenderText_Solid(fuente1,vec2,font_color2);
			pos.x=440;
			pos.y=640;
			SDL_BlitSurface(font,NULL,screen,&pos);			
			SDL_Flip(screen); 

		}
	}
}

int lectura2()
{
	SDL_Event evento;
	SDL_Rect pos;
	int n=0, j=1;
	char vec[100];
	while(1)
	{
		opciones("Inserta un numero:", 735, 615);
		
		SDL_WaitEvent(&evento);
		if(evento.type==SDL_KEYDOWN)
		{
			switch(evento.key.keysym.sym)
			{
				case SDLK_0:  n*=10;
							break;
				case SDLK_1: n*=10; n+=1;
							break;
				case SDLK_2:  n*=10; n+=2;
							break;
				case SDLK_3:  n*=10; n+=3;
							break;
				case SDLK_4:  n*=10; n+=4;
							break;
				case SDLK_5:  n*=10; n+=5;
							break;
				case SDLK_6:  n*=10; n+=6;
							break;
				case SDLK_7:  n*=10; n+=7;
							break;
				case SDLK_8:  n*=10; n+=8;
							break;
				case SDLK_9:  n*=10; n+=9;
							break;
				case SDLK_MINUS: j=-1; 
							break;
				case SDLK_RETURN: printf("numero ===  %d\n", n*j); return n*j;
				
			}
			sprintf(vec,"%d",n*j);
			//pixel.x = 340; pixel.y = 600; pixel.w = 50; pixel.h = 50;	// abajo derecha
			//SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
			font = TTF_RenderText_Solid(fuente1,vec,font_color2);
			pos.x=440;
			pos.y=640;
			SDL_BlitSurface(font,NULL,screen,&pos);			
			SDL_Flip(screen); 

		}
	}
}


int main(int argc, char *argv[])
{
	char vec[100];
	int n=1,m, p,i,j=0, y1;
	
	if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ) 
		exit(0);	
   
	SDL_WM_SetCaption("TABLAS HASH", NULL);
	screen = SDL_SetVideoMode(ANCHO,ALTO,24, SDL_SWSURFACE);
	if(screen == NULL)
	{
		printf("No se ha podido establecer el modo de vídeo: %s\n", SDL_GetError());
		exit(1);
	}
	SDL_Rect pos;
	SDL_Event evento;

	imagen[0] = SDL_LoadBMP("img/tablas.bmp");
	if(imagen[i]==NULL)
	{
		printf("No se ha podido cargar la imagen: %s\n", SDL_GetError());
		exit(1);
	}
	TTF_Init();
	fuente=TTF_OpenFont("font/FortuneCity.ttf",30);
	if(fuente==NULL)
	{	printf("Error al al leer fuente\n");}
	font_color.r=255; font_color.g=255; font_color.b=255;
	
	entorno(); 
	menu();
	tabla();
	char vec2[100];
	int done=1;
	while(done)
	{
		pixel.x = 50; pixel.y = 308; pixel.w = 350; pixel.h = 30;
		SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
		opciones("(Teclea una opcion)", 135, 310);
		
		SDL_WaitEvent(&evento);
		if(evento.type==SDL_KEYDOWN)
		{
			
			pixel.x = 15; pixel.y = 400; pixel.w = 390; pixel.h = 285; //abajo
			SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
			
			pixel.x = 420; pixel.y = 610; pixel.w = 770; pixel.h = 80; //abajo
			SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
			SDL_Flip(screen);
			switch(evento.key.keysym.sym)
			{
				case SDLK_1:pixel.x = 50; pixel.y = 308; pixel.w = 350; pixel.h = 30;
							SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255)); 
							opciones("Inserta una palabra:", 735, 615);
							lectura(vec2);
							puts(vec2);
							m=hash(vec2);
							
							pixel.x = 50; pixel.y = 308; pixel.w = 350; pixel.h = 30;
							SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
							opciones("Posicion : ", 135, 310);
							sprintf(vec,"%d",m);
							opciones(vec, 220, 310);
							
							recorrido(m,0);
							pixel.x=posiciones[m][0].x; pixel.y=posiciones[m][0].y; pixel.w=50; pixel.h=10;
							SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,40,183,29,255));
							SDL_Delay(1000);
							SDL_Flip(screen); 
							insertar(vec2);
							
							break;
				case SDLK_2:
							pixel.x = 50; pixel.y = 308; pixel.w = 350; pixel.h = 30;
							SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
							opciones("Buscando palabra. . .", 135, 310);
							SDL_Delay(1000);
							lectura(vec2);
							puts(vec2);
							buscar(vec2);
							break;
				case SDLK_3: opciones("==Palabras==", 165, 400);
							m=lectura2();
							if(m>=0 && m<7)
							{
								recorrido(m,0);
								visualizar(m);
							}
							break;
				case SDLK_4:pixel.x = 50; pixel.y = 308; pixel.w = 350; pixel.h = 30;
							SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));  
							opciones("Salir", 190, 310);done=0;						
							break;
			}
			
		}
		SDL_Delay(1000);
	}	
	
	SDL_Delay(1000);

	for(i=0;i<9;i++)
		SDL_FreeSurface(imagen[i]); 
	SDL_Quit();
	return 0;	
}
