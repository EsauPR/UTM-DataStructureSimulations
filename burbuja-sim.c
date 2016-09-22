#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL_ttf.h>
#include <time.h>
#define ALTO  500
#define ANCHO 900

SDL_Surface *screen=NULL,*font, *imagen[12];
SDL_Color font_color,line_color, font_color1, font_color2; //1.- blanco, 2.- Negro
TTF_Font *fuente, *fuente1, *fuente2;
SDL_Rect pixel, pixel2;
SDL_Rect burbuja;


typedef struct casilla
{
	int d;
	SDL_Rect destino;
}BLOQUE;

BLOQUE* bloque;

void menu()
{
	char vec[100];
	SDL_Rect pos;
	
	
	fuente1=TTF_OpenFont("font/FortuneCity.ttf",30);
	if(fuente1==NULL)
	{	printf("Error al al leer fuente\n");}
	font_color1.r=255; font_color1.g=255; font_color1.b=255;	
	
	
	strcpy(vec,"= MENU =");
	pos.x=384;
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
	
	strcpy(vec,"1.- Generar Numero Aleatorios");
	font = TTF_RenderText_Solid(fuente2,vec,font_color2);
	pos.x=75;
	pos.y=160;
	SDL_BlitSurface(font,NULL,screen,&pos);
	
	strcpy(vec,"2.- Iniciar Simulacion");
	font = TTF_RenderText_Solid(fuente2,vec,font_color2);
	pos.x=475;
	pos.y=160;
	SDL_BlitSurface(font,NULL,screen,&pos);
	
	strcpy(vec,"3.- Salir");
	font = TTF_RenderText_Solid(fuente2,vec,font_color2);
	pos.x=750;
	pos.y=160;
	SDL_BlitSurface(font,NULL,screen,&pos);
	
	strcpy(vec,"(Teclea una Opcion)");
	font = TTF_RenderText_Solid(fuente,vec,font_color2);
	pos.x=380;
	pos.y=200;
	SDL_BlitSurface(font,NULL,screen,&pos);
	
	SDL_Flip(screen); 
}

void entorno()
{
	
	
	pixel.x = 0; pixel.y = 0; pixel.w = 900; pixel.h = 500;//general	
	SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,16,192,236,255));
	
	pixel.x = 10; pixel.y = 100; pixel.w = 880; pixel.h = 130;//arriba	
	SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
	
	pixel.x = 350; pixel.y = 105; pixel.w = 200; pixel.h = 35;//arriba	
	SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,16,192,236,255));
	
	//pixel.x = 15; pixel.y = 145; pixel.w = 870; pixel.h = 80;//arriba	
	//SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,16,192,236,255));
	
	pixel.x = 10; pixel.y = 240; pixel.w = 880; pixel.h = 250;//abajo	
	SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
	
	burbuja.x = 302; burbuja.y =0; 
	burbuja.w=imagen[0]->w; burbuja.h=imagen[0]->h;//BURBUJA
	SDL_BlitSurface(imagen[0], NULL, screen, &burbuja);
	
	SDL_Flip(screen);
}

void opciones(char *c,int x,int y)
{	
	pixel.x = 300; pixel.y = 195; pixel.w = 300; pixel.h = 30;//arriba	
	SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
	
	SDL_Rect pos;
	font = TTF_RenderText_Solid(fuente,c,font_color2);
	pos.x=x;
	pos.y=y;
	SDL_BlitSurface(font,NULL,screen,&pos);
	
	SDL_Flip(screen);	
}

void numeros(BLOQUE b)
{
	SDL_Rect pos;
	char vec[100];
	sprintf(vec,"%d",b.d);
	font = TTF_RenderText_Solid(fuente2,vec,font_color1);
	pos.x=b.destino.x+5;
	pos.y=b.destino.y+5;
	SDL_BlitSurface(font,NULL,screen,&pos);
}

void numeros2(int d, int x, int y)
{
	SDL_Rect pos;
	char vec[100];
	sprintf(vec,"%d",d);
	font = TTF_RenderText_Solid(fuente2,vec,font_color1);
	pos.x=x+5;
	pos.y=y+5;
	SDL_BlitSurface(font,NULL,screen,&pos);
}

void animacion(BLOQUE a, BLOQUE b)
{
	pixel.x=a.destino.x; pixel.y=a.destino.y; pixel.w=30; pixel.h=30;
	pixel2.x=b.destino.x; pixel2.y=b.destino.y; pixel2.w=30; pixel2.h=30;
	
	int i,t=(b.destino.x)-(a.destino.x);
	
	;
	for(i=1;i<=50;i++)//arriba-abajo
	{
		SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
		SDL_FillRect(screen, &pixel2, SDL_MapRGBA(screen->format,255,255,255,255));
		pixel.y+=1;
		pixel2.y-=1;
		SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,31,123,28,0));
		numeros2(a.d,pixel.x,pixel.y);
		SDL_FillRect(screen, &pixel2, SDL_MapRGBA(screen->format,31,123,28,0));
		numeros2(b.d,pixel2.x,pixel2.y);
		//SDL_Delay(50);
		SDL_Flip(screen);
	}
	
	for(i=1;i<=t;i++)//lateral
	{
		SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
		SDL_FillRect(screen, &pixel2, SDL_MapRGBA(screen->format,255,255,255,255));
		pixel.x+=1;
		pixel2.x-=1;
		SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,31,123,28,0));
		numeros2(a.d,pixel.x,pixel.y);
		SDL_FillRect(screen, &pixel2, SDL_MapRGBA(screen->format,31,123,28,0));
		numeros2(b.d,pixel2.x,pixel2.y);
		//SDL_Delay(50);
		SDL_Flip(screen);
	}
	
	for(i=1;i<=50;i++)//arriba-abajo
	{
		SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
		SDL_FillRect(screen, &pixel2, SDL_MapRGBA(screen->format,255,255,255,255));
		pixel.y-=1;
		pixel2.y+=1;
		SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,31,123,28,0));
		numeros2(a.d,pixel.x,pixel.y);
		SDL_FillRect(screen, &pixel2, SDL_MapRGBA(screen->format,31,123,28,0));
		numeros2(b.d,pixel2.x,pixel2.y);
		//SDL_Delay(50);
		SDL_Flip(screen);
	}
}

void burbu(int b)
{
	if(b==0)
		return;
	int tam=17,i,aux;
	while(tam>1)
	{
		for(i=0; i<tam-1; i++)
		{
			//pintada de recorrido
			SDL_FillRect(screen, &bloque[i].destino, SDL_MapRGBA(screen->format,31,123,28,0));
			numeros(bloque[i]);
			SDL_FillRect(screen, &bloque[i+1].destino, SDL_MapRGBA(screen->format,31,123,28,0));
			numeros(bloque[i+1]);
			SDL_Delay(500);
			SDL_Flip(screen);
			if(bloque[i].d>bloque[i+1].d)
			{
				animacion(bloque[i],bloque[i+1]);
				aux=bloque[i].d;
				bloque[i].d=bloque[i+1].d;
				bloque[i+1].d=aux;
			}
			SDL_FillRect(screen, &bloque[i].destino, SDL_MapRGBA(screen->format,200,123,13,0));
			numeros(bloque[i]);
			SDL_FillRect(screen, &bloque[i+1].destino, SDL_MapRGBA(screen->format,200,123,13,0));
			numeros(bloque[i+1]);
			SDL_Delay(500);
			SDL_Flip(screen);
		}
		tam--;
	}
}

void generar()
{
	int i,k;
	for(i=0;i<17; i++)
	{
		k=rand()%100;
		bloque[i].d=k;	
	}
	
	for(i=0; i<17; i++)
	{
		bloque[i].destino.x=35+50*i;
		bloque[i].destino.y=350;
		bloque[i].destino.w=30;
		bloque[i].destino.h=30;
		SDL_FillRect(screen, &bloque[i].destino, SDL_MapRGBA(screen->format,200,123,13,0));
		numeros(bloque[i]);
		SDL_Delay(500);
		SDL_Flip(screen);
	}
}

int main(int argc, char *argv[])
{
	bloque=(BLOQUE*)malloc(sizeof(BLOQUE)*20);
	char vec[100];
	int n=1,m, p,i,j=0, y1,b;
	
	if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ) 
		exit(0);	
   
	SDL_WM_SetCaption("BURBUJA", NULL);
	screen = SDL_SetVideoMode(ANCHO,ALTO,24, SDL_SWSURFACE);
	if(screen == NULL)
	{
		printf("No se ha podido establecer el modo de vídeo: %s\n", SDL_GetError());
		exit(1);
	}
	SDL_Rect pos;
	SDL_Event evento;

	imagen[0] = SDL_LoadBMP("img/BURBUJA.bmp");
	imagen[1] = SDL_LoadBMP("img/roja.bmp");
	imagen[2] = SDL_LoadBMP("img/rosa.bmp");
	imagen[3] = SDL_LoadBMP("img/verde.bmp");
	imagen[4] = SDL_LoadBMP("img/0izq.bmp");
	imagen[5] = SDL_LoadBMP("img/0der.bmp");
	imagen[6] = SDL_LoadBMP("img/1izq.bmp");
	imagen[7] = SDL_LoadBMP("img/1der.bmp");
	imagen[8] = SDL_LoadBMP("img/2izq.bmp");
	imagen[9] = SDL_LoadBMP("img/2der.bmp");
	imagen[10] = SDL_LoadBMP("img/3izq.bmp");
	imagen[11] = SDL_LoadBMP("img/3der.bmp");
	for(i=0; i<12; i++)
		if(imagen[i]==NULL)
		{
			printf("No se ha podido cargar la imagen: %s\n", SDL_GetError());
			exit(1);
		}
	//for(i=0; i<4; i++)
		//SDL_SetColorKey(imagen[i], SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(imagen[i] -> format, 255, 255, 255));
		
		
	TTF_Init();
	fuente=TTF_OpenFont("font/FortuneCity.ttf",30);
	if(fuente==NULL)
	{	printf("Error al al leer fuente\n");}
	font_color.r=255; font_color.g=255; font_color.b=255;
	
	entorno(); 
	menu();
	
	int done=1; b=0;
	while(done)
	{
		pixel.x = 300; pixel.y = 195; pixel.w = 300; pixel.h = 30;//arriba	
		SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
		strcpy(vec,"(Teclea una Opcion)");
		font = TTF_RenderText_Solid(fuente,vec,font_color2);
		pos.x=380;
		pos.y=200;
		SDL_BlitSurface(font,NULL,screen,&pos);
		SDL_Flip(screen); 
		SDL_WaitEvent(&evento);
		if(evento.type==SDL_KEYDOWN)
		{
			
			
			switch(evento.key.keysym.sym)
			{
				case SDLK_1: opciones("Generando numeros aleatorios. . .", 325, 200);
							pixel.x = 10; pixel.y = 240; pixel.w = 880; pixel.h = 250;//abajo	
							SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
							generar();
							b=1;
							break;
				case SDLK_2: opciones("Simulacion en proceso. . .", 360, 200);
							burbu(b);
							break;
				case SDLK_3: opciones("Salir", 440, 200); done=0;						
							break;
			}
		}
	}	
	
		SDL_Delay(1000);
	
		for(i=0;i<9;i++)
			SDL_FreeSurface(imagen[i]); 
		SDL_Quit();
	return 0;	
}
