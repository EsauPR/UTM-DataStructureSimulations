#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL_ttf.h>
#define ALTO  730
#define ANCHO 1200

SDL_Surface *screen=NULL,*font, *imagen[12];
SDL_Color font_color,line_color, font_color1, font_color2;
TTF_Font *fuente, *fuente1, *fuente2;
SDL_Rect pixel;
SDL_Rect flechas;

typedef struct nodo
{
	int dato;
	struct nodo *izq, *der;
	SDL_Rect destino;
	
}NODO;
typedef NODO* ARBOL;

void numeros(ARBOL a)
{
	char c[30];
	sprintf(c,"%d",a->dato);
	SDL_Rect pos;
	font = TTF_RenderText_Solid(fuente,c,font_color);
	pos.x=a->destino.x+18;
	pos.y=a->destino.y+12;
	SDL_BlitSurface(font,NULL,screen,&pos);
	
}

void ins(ARBOL *a, int d, int dx, int dy, int n)
{
	if(n<=4 && *a==NULL)
	{
		*a=(ARBOL)malloc(sizeof(NODO));
		(*a)->dato=d;
		(*a)->izq=NULL;
		(*a)->der=NULL;
		printf("paso ===== %d %d %d\n",n,dx,dy);
		(*a)->destino.x=dx;
		(*a)->destino.y=dy;
		
		(*a)->destino.w = imagen[0] -> w;
		(*a)->destino.h = imagen[0] -> h;

		SDL_BlitSurface(imagen[0], NULL, screen, &((*a)->destino));
		numeros(*a);
		SDL_Delay(500);
		SDL_Flip(screen);
		
	}
	else if(n<=4 && d<(*a)->dato) // 4 == altura del arbol -1
	{
		SDL_BlitSurface(imagen[1], NULL, screen, &((*a)->destino));
		numeros(*a);
		SDL_Delay(500);
		SDL_Flip(screen); 
		SDL_BlitSurface(imagen[0], NULL, screen, &((*a)->destino));
		numeros(*a);
		SDL_Delay(500);
		SDL_Flip(screen);
		if((*a)->izq==NULL)
		{
			flechas.x=dx-280/pow(2,n);
			flechas.y=(*a)->destino.y+30;
			flechas.w=imagen[4+2*n]->w;
			flechas.h=imagen[4+2*n]->h;
			SDL_BlitSurface(imagen[4+2*n], NULL, screen, &flechas);
			SDL_BlitSurface(imagen[0], NULL, screen, &((*a)->destino));
			numeros(*a);
		} 		
		ins(&((*a)->izq),d,dx-280/pow(2,n),dy+80,n+1);
	}
	else if(n<=4 && d>(*a)->dato)
	{
		SDL_BlitSurface(imagen[1], NULL, screen, &((*a)->destino));
		numeros(*a);
		SDL_Delay(500);
		SDL_Flip(screen); 
		SDL_BlitSurface(imagen[0], NULL, screen, &((*a)->destino));
		numeros(*a);
		SDL_Delay(500);
		SDL_Flip(screen);
		if((*a)->der==NULL)
		{	//lineas((*a)->destino.x+60,(*a)->destino.y+60,dx+280/pow(2,n),dy+80);
			flechas.x=(*a)->destino.x+60;
			flechas.y=(*a)->destino.y+30;
			flechas.w=imagen[5+2*n]->w;
			flechas.h=imagen[5+2*n]->h;
			SDL_BlitSurface(imagen[5+2*n], NULL, screen, &flechas);
			SDL_BlitSurface(imagen[0], NULL, screen, &((*a)->destino));
			numeros(*a);
		}
		ins(&((*a)->der),d,dx+280/pow(2,n),dy+80,n+1);
	}
		
}

void insertar(ARBOL *a, int d, int dx, int dy, int n)
{
	if(n<=4 && *a==NULL)
	{
		*a=(ARBOL)malloc(sizeof(NODO));
		(*a)->dato=d;
		(*a)->izq=NULL;
		(*a)->der=NULL;
		printf("paso ===== %d %d %d\n",n,dx,dy);
		(*a)->destino.x=dx;
		(*a)->destino.y=dy;
		
		(*a)->destino.w = imagen[0] -> w;
		(*a)->destino.h = imagen[0] -> h;

		SDL_BlitSurface(imagen[0], NULL, screen, &((*a)->destino));
		numeros(*a);
		
	}
	else if(n<=4 && d<(*a)->dato) // 4 == altura del arbol -1
	{
			if((*a)->izq==NULL)
		{
			flechas.x=dx-280/pow(2,n);
			flechas.y=(*a)->destino.y+30;
			flechas.w=imagen[4+2*n]->w;
			flechas.h=imagen[4+2*n]->h;
			SDL_BlitSurface(imagen[4+2*n], NULL, screen, &flechas);
			SDL_BlitSurface(imagen[0], NULL, screen, &((*a)->destino));
			numeros(*a);
		}
		insertar(&((*a)->izq),d,dx-280/pow(2,n),dy+80,n+1);
	}
	else if(n<=4 && d>(*a)->dato)
	{
		if((*a)->der==NULL)
		{	//lineas((*a)->destino.x+60,(*a)->destino.y+60,dx+280/pow(2,n),dy+80);
			flechas.x=(*a)->destino.x+60;
			flechas.y=(*a)->destino.y+30;
			flechas.w=imagen[5+2*n]->w;
			flechas.h=imagen[5+2*n]->h;
			SDL_BlitSurface(imagen[5+2*n], NULL, screen, &flechas);
			SDL_BlitSurface(imagen[0], NULL, screen, &((*a)->destino));
			numeros(*a);
		}
		insertar(&((*a)->der),d,dx+280/pow(2,n),dy+80,n+1);
	}
		
}

int mayor(ARBOL a)
{
	if(a->der==NULL)
	{	
		SDL_BlitSurface(imagen[3], NULL, screen, &(a->destino));
		numeros(a);
		SDL_Delay(500);
		SDL_Flip(screen); 
		return a->dato;
	}
	else
	{
		SDL_BlitSurface(imagen[1], NULL, screen, &(a->destino));
		numeros(a);
		SDL_Delay(500);
		SDL_Flip(screen); 
		SDL_BlitSurface(imagen[0], NULL, screen, &(a->destino));
		numeros(a);
		SDL_Delay(500);
		SDL_Flip(screen);
		mayor(a->der);
	}
}

void meter(ARBOL *a, int vec[], int *i)
{
	
	if(*a==NULL)
		return;
	
	printf("metiendo %d\n", *i);
	
	pixel.x = (*a)->destino.x; pixel.y = (*a)->destino.y; pixel.w = 60; pixel.h = 60;	
	SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
	
	vec[*i]=(*a)->dato;
	(*i)+=1;
	printf("paso\n");
	meter(&((*a)->izq),vec,i);
	meter(&((*a)->der),vec,i);
}

void eliminar(ARBOL *a, int d, ARBOL *b,int n)
{
	if(*a==NULL)
		return;
		
	SDL_BlitSurface(imagen[1], NULL, screen, &((*a)->destino));
	numeros(*a);
	SDL_Delay(500);
	SDL_Flip(screen); 
	 	
	
	SDL_BlitSurface(imagen[0], NULL, screen, &((*a)->destino));
	numeros(*a);
	SDL_Delay(500);
	SDL_Flip(screen);
	
		
	if(d<(*a)->dato)
	{
		if(n==3)	
		{
			pixel.x = (*a)->destino.x-35; pixel.y = (*a)->destino.y+30; pixel.w = 35; pixel.h = 80;	
			SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
		}
		eliminar(&((*a)->izq), d,b,n+1);
	}
	else if(d>(*a)->dato)
	{
		if(n==3)	
		{
			pixel.x = (*a)->destino.x+60; pixel.y = (*a)->destino.y+30; pixel.w = 35; pixel.h = 80;	
			SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
		}
		eliminar(&((*a)->der), d,b,n+1);
	}
	
	else
	{
		printf("entro\n");
		 
		SDL_BlitSurface(imagen[3], NULL, screen, &((*a)->destino));
		numeros(*a);
		SDL_Delay(500);
		SDL_Flip(screen); 
		
		
		if((*a)->der==NULL && (*a)->izq==NULL)
		{
			pixel.x = (*a)->destino.x; pixel.y = (*a)->destino.y; pixel.w = 60; pixel.h = 60;	
			SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
			
			if(n!=4) 
			{
				pixel.x = (*a)->destino.x-280/pow(2,n-1)+60; pixel.y = (*a)->destino.y-50; pixel.w = 280/pow(2,n-1); pixel.h = 80;	
				SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
				
				pixel.x = (*a)->destino.x; pixel.y = (*a)->destino.y-50; pixel.w = 280/pow(2,n-1); pixel.h = 80;	
				SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
			}
			SDL_Delay(1000);
			SDL_Flip(screen); 
			free(*a);
			*a=NULL;
		}
		else if((*a)->izq==NULL)
		{
			pixel.x = (*a)->destino.x; pixel.y = (*a)->destino.y; pixel.w = 60; pixel.h = 60;	
			SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
			
			pixel.x = (*a)->destino.x+30; pixel.y = (*a)->destino.y+30; pixel.w = 280/pow(2,n-1); pixel.h = 80*(4-n)+30;	
			SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
			
			SDL_Delay(1000);
			SDL_Flip(screen);
			
			int vec[50];
			int i=0,j;
			meter(&((*a)->der), vec, &i);
			
			*a=NULL;
			for( j=0; j<i; j++)
				insertar(b,vec[j],570,40,0);
			SDL_Delay(500);
			SDL_Flip(screen);
			
			//ARBOL aux=*a;
			//*a=(*a)->der;
			//free(aux);
		}
		else if((*a)->der==NULL)
		{
			pixel.x = (*a)->destino.x; pixel.y = (*a)->destino.y; pixel.w = 60; pixel.h = 60;	
			SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
			
			pixel.x = (*a)->destino.x- 280/pow(2,n-1)+30; pixel.y = (*a)->destino.y+30; pixel.w = 280/pow(2,n-1); pixel.h = 80*(4-n)+30;	
			SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
			
			SDL_Delay(1000);
			SDL_Flip(screen);
			int vec[50];
			int i=0,j;
			printf("paso\n");
			meter(&((*a)->izq), vec, &i);
			printf("paso\n");
			*a=NULL;
			
			for(j=0; j<i; j++)
				insertar(b,vec[j],570,40,0);
				
			for(j=0; j<i; j++)
				printf("%d ",vec[j]);
			
			printf("\n");
				
			SDL_Delay(500);
			SDL_Flip(screen);
			//ARBOL aux=*a;
			//*a=(*a)->izq;
			//free(aux);
		}
		else
		{
			
			//printf("%d\n", mayor((*a)->izq));
			(*a)->dato=mayor((*a)->izq);

			SDL_BlitSurface(imagen[3], NULL, screen, &((*a)->destino));
			numeros(*a);
			SDL_Delay(500);
			SDL_Flip(screen);
			eliminar(&((*a)->izq), (*a)->dato,b,n+1);
			SDL_BlitSurface(imagen[0], NULL, screen, &((*a)->destino));
			numeros(*a);
			SDL_Delay(500);
			SDL_Flip(screen);
		}
		
	}
	
}

void recorrido(int d, int *i, int *y1)
{
	char vec[100];
	
	sprintf(vec,"%d",d);
	SDL_Rect pos;
	font = TTF_RenderText_Solid(fuente1,vec,font_color1);
	pos.x=580+(*i)*30;
	if(pos.x>1160)
	{
		pos.x=580;
		*y1=40;
		*i=0;
	}
	pos.y=520+*y1;
	SDL_BlitSurface(font,NULL,screen,&pos);
}

void preorder(ARBOL a, int *i, int *y1)
{
	if(a==NULL)
		return;
	printf("%d ", a->dato);
	SDL_BlitSurface(imagen[3], NULL, screen, &(a->destino));
	numeros(a);
	SDL_Delay(500);
	recorrido(a->dato,i,y1);
	*i+=1;
	SDL_Flip(screen); 
	SDL_BlitSurface(imagen[0], NULL, screen, &(a->destino));
	numeros(a);
	SDL_Delay(500);
	SDL_Flip(screen); 
	preorder(a->izq,i,y1);
	preorder(a->der,i,y1);
}

void posorder(ARBOL a, int *i, int *y1)
{
	if(a==NULL)
		return;
	SDL_BlitSurface(imagen[1], NULL, screen, &(a->destino));
	numeros(a);
	SDL_Delay(500);
	SDL_Flip(screen); 
	SDL_BlitSurface(imagen[0], NULL, screen, &(a->destino));
	numeros(a);
	SDL_Delay(500);
	SDL_Flip(screen); 
	
	posorder(a->izq,i,y1);
	
	posorder(a->der,i,y1);
	
	printf("%d ", a->dato);
	SDL_BlitSurface(imagen[3], NULL, screen, &(a->destino));
	numeros(a);
	SDL_Delay(500);
	SDL_Flip(screen); 
	SDL_BlitSurface(imagen[0], NULL, screen, &(a->destino));
	numeros(a);
	recorrido(a->dato,i,y1);
	*i+=1;
	SDL_Delay(500);
	SDL_Flip(screen); 
	
}

void inorder(ARBOL a, int *i, int *y1)
{
	if(a==NULL)
		return;
	SDL_BlitSurface(imagen[1], NULL, screen, &(a->destino));
	numeros(a);
	SDL_Delay(500);
	SDL_Flip(screen); 
	SDL_BlitSurface(imagen[0], NULL, screen, &(a->destino));
	numeros(a);
	SDL_Delay(500);
	SDL_Flip(screen); 
	
	inorder(a->izq,i,y1);
	printf("%d ", a->dato);
	SDL_BlitSurface(imagen[3], NULL, screen, &(a->destino));
	numeros(a);
	SDL_Delay(500);
	SDL_Flip(screen); 
	SDL_BlitSurface(imagen[0], NULL, screen, &(a->destino));
	numeros(a);
	recorrido(a->dato,i,y1);
	*i+=1;
	SDL_Delay(500);
	
	SDL_Flip(screen); 
	
	inorder(a->der,i,y1);
}

void menu()
{
	SDL_Rect pos;
	
	
	fuente1=TTF_OpenFont("font/FortuneCity.ttf",20);
	if(fuente1==NULL)
	{	printf("Error al al leer fuente\n");}
	font_color1.r=0; font_color.g=0; font_color.b=0;	
	
	char vec[100]={"MENU"};
	pos.x=25;
	pos.y=490;
	font = TTF_RenderText_Solid(fuente1,vec,font_color1);
	SDL_BlitSurface(font,NULL,screen,&pos);
	
	strcpy(vec,"ACOTACIONES");
	pos.x=805;
	pos.y=635;
	font = TTF_RenderText_Solid(fuente1,vec,font_color1);
	SDL_BlitSurface(font,NULL,screen,&pos);
	
	strcpy(vec,"ELECCION");
	pos.x=315;
	pos.y=500;
	font = TTF_RenderText_Solid(fuente,vec,font_color1);
	SDL_BlitSurface(font,NULL,screen,&pos);
	
	
	fuente2=TTF_OpenFont("font/FortuneCity.ttf",15);
	if(fuente2==NULL)
	{	printf("Error al al leer fuente\n");}
	font_color2.r=0; font_color.g=0; font_color.b=0;	
	
	strcpy(vec,"1.- Insertar dato");
	font = TTF_RenderText_Solid(fuente2,vec,font_color1);
	pos.x=25;
	pos.y=520;
	SDL_BlitSurface(font,NULL,screen,&pos);
	
	strcpy(vec,"2.- Eliminar dato");
	font = TTF_RenderText_Solid(fuente2,vec,font_color1);
	pos.x=25;
	pos.y=550;
	SDL_BlitSurface(font,NULL,screen,&pos);
	
	strcpy(vec,"3.- Recorrido preorder");
	font = TTF_RenderText_Solid(fuente2,vec,font_color1);
	pos.x=25;
	pos.y=580;
	SDL_BlitSurface(font,NULL,screen,&pos);
	
	strcpy(vec,"4.- Recorrido inorder");
	font = TTF_RenderText_Solid(fuente2,vec,font_color1);
	pos.x=25;
	pos.y=610;
	SDL_BlitSurface(font,NULL,screen,&pos);
	
	strcpy(vec,"5.- Recorrido posorder");
	font = TTF_RenderText_Solid(fuente2,vec,font_color1);
	pos.x=25;
	pos.y=640;
	SDL_BlitSurface(font,NULL,screen,&pos);
	
	strcpy(vec,"0.- Salir");
	font = TTF_RenderText_Solid(fuente2,vec,font_color1);
	pos.x=25;
	pos.y=670;
	SDL_BlitSurface(font,NULL,screen,&pos);
	
	strcpy(vec,"Nodo rojo: Nodo visitado           Nodo Verde: Nodo encontrado");
	font = TTF_RenderText_Solid(fuente2,vec,font_color1);
	pos.x=640;
	pos.y=665;
	SDL_BlitSurface(font,NULL,screen,&pos);
	
	strcpy(vec,"Altura maxima del arbol: 5");
	font = TTF_RenderText_Solid(fuente2,vec,font_color1);
	pos.x=640;
	pos.y=685;
	SDL_BlitSurface(font,NULL,screen,&pos);
	
	SDL_Flip(screen); 
}

void entorno()
{
	pixel.x = 0; pixel.y = 0; pixel.w = 1200; pixel.h = 730;//general	
	SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
	
	pixel.x = 10; pixel.y = 10; pixel.w = 1180; pixel.h = 710;// general2
	SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,0,0,0,0));
	
	pixel.x = 15; pixel.y = 15; pixel.w = 1170; pixel.h = 438;	//arriba
	SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
	
	pixel.x = 15; pixel.y = 458; pixel.w = 540; pixel.h = 257;	// abajo izquierda
	SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
	
	pixel.x = 560; pixel.y = 458; pixel.w = 625; pixel.h = 157;	// abajo derecha
	SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
	
	pixel.x = 560; pixel.y = 620; pixel.w = 625; pixel.h = 95;	// abajo derecha
	SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
	
	pixel.x = 220; pixel.y = 480; pixel.w = 310; pixel.h = 215;	// abajo derecha
	SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,0,0,0,0));
	
	pixel.x = 225; pixel.y = 485; pixel.w = 300; pixel.h = 205;	// abajo derecha
	SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
	
	
	SDL_Flip(screen);
}

void opciones(char *c,int x,int y)
{	
	pixel.x = 225; pixel.y = 530; pixel.w = 300; pixel.h = 150;	// abajo derecha
	SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
	SDL_Flip(screen);
	
	SDL_Rect pos;
	font = TTF_RenderText_Solid(fuente1,c,font_color1);
	pos.x=x;
	pos.y=y;
	SDL_BlitSurface(font,NULL,screen,&pos);
	
	SDL_Flip(screen);	
}

int lectura()
{
	SDL_Event evento;
	SDL_Rect pos;
	int n=0, j=1;
	char vec[100];
	while(1)
	{
		sprintf(vec,"Dato");
		font = TTF_RenderText_Solid(fuente,vec,font_color1);
		pos.x=340;
		pos.y=575;
		SDL_BlitSurface(font,NULL,screen,&pos);	
		sprintf(vec,"(Dijite un numero)");
		font = TTF_RenderText_Solid(fuente2,vec,font_color1);
		pos.x=310;
		pos.y=662;
		SDL_BlitSurface(font,NULL,screen,&pos);
				
		SDL_Flip(screen); 
		
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
			pixel.x = 340; pixel.y = 600; pixel.w = 50; pixel.h = 50;	// abajo derecha
			SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
			font = TTF_RenderText_Solid(fuente,vec,font_color1);
			pos.x=340;
			pos.y=620;
			SDL_BlitSurface(font,NULL,screen,&pos);			
			SDL_Flip(screen); 

		}
	}
}

int main(int argc, char *argv[])
{
	ARBOL a=NULL;
	char vec[100];
	int n=1,m, p,i,j=0, y1;
	
	if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ) 
		exit(0);	
   
	SDL_WM_SetCaption("ARBOLES", NULL);
	screen = SDL_SetVideoMode(ANCHO,ALTO,24, SDL_SWSURFACE);
	if(screen == NULL)
	{
		printf("No se ha podido establecer el modo de vídeo: %s\n", SDL_GetError());
		exit(1);
	}
	SDL_Rect pos;
	SDL_Event evento;
	
	entorno(); 
	
	imagen[0] = SDL_LoadBMP("img/azul.bmp");
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
	
	menu();
	
	int done=1;
	while(done)
	{
		strcpy(vec,"(Digite numero de eleccion)");
		font = TTF_RenderText_Solid(fuente2,vec,font_color1);
		pos.x=290;
		pos.y=662;
		SDL_BlitSurface(font,NULL,screen,&pos);
		SDL_Flip(screen); 
		SDL_WaitEvent(&evento);
		if(evento.type==SDL_KEYDOWN)
		{
			
			
			switch(evento.key.keysym.sym)
			{
				case SDLK_1: opciones("Insertar un numero", 290, 545);
							m=lectura();
							ins(&a, m,570,40,0);
							pixel.x = 225; pixel.y = 530; pixel.w = 300; pixel.h = 150;	// datos
							SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
							SDL_Flip(screen);
							break;
				
				case SDLK_2: opciones("Eliminar un numero", 290, 545);
							m=lectura();
							eliminar(&a,m,&a,0);
							pixel.x = 10; pixel.y = 10; pixel.w = 1180; pixel.h = 15;// general2
							SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,0,0,0,0));							
							pixel.x = 15; pixel.y = 15; pixel.w = 1170; pixel.h = 10;	//arriba
							SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
							pixel.x = 225; pixel.y = 530; pixel.w = 300; pixel.h = 150;	// datos
							SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
							SDL_Flip(screen);
							break;
				
				case SDLK_3: opciones("Recorrido preorder", 290, 545);
							pixel.x = 560; pixel.y = 458; pixel.w = 625; pixel.h = 157;	// recorrido
							SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
							strcpy(vec,"RECORRIDO PREORDER");
							pos.x=765;
							pos.y=465;
							font = TTF_RenderText_Solid(fuente1,vec,font_color1);
							SDL_BlitSurface(font,NULL,screen,&pos);
							j=0; y1=0;
							preorder(a,&j,&y1);
							pixel.x = 225; pixel.y = 530; pixel.w = 300; pixel.h = 150;	// datos
							SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
							
							SDL_Flip(screen);
							break;
				
				case SDLK_4: opciones("Recorrido inorder", 290, 545);
											
							pixel.x = 560; pixel.y = 458; pixel.w = 625; pixel.h = 157;	// recorrido
							SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
							strcpy(vec,"RECORRIDO INORDER");
							pos.x=765;
							pos.y=465;
							font = TTF_RenderText_Solid(fuente1,vec,font_color1);
							SDL_BlitSurface(font,NULL,screen,&pos);
							j=0; y1=0;
							inorder(a,&j,&y1);
							pixel.x = 225; pixel.y = 530; pixel.w = 300; pixel.h = 150;	// datos
							SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
							
							SDL_Flip(screen);
							
							break;
				
				case SDLK_5: opciones("Recorrido posorder", 290, 545);
							pixel.x = 560; pixel.y = 458; pixel.w = 625; pixel.h = 157;	// recorrido
							SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
							strcpy(vec,"RECORRIDO POSORDER");
							pos.x=765;
							pos.y=465;
							font = TTF_RenderText_Solid(fuente1,vec,font_color1);
							SDL_BlitSurface(font,NULL,screen,&pos);
							j=0; y1=0;
							posorder(a,&j,&y1);
							
							pixel.x = 225; pixel.y = 530; pixel.w = 300; pixel.h = 150;	// datos
							SDL_FillRect(screen, &pixel, SDL_MapRGBA(screen->format,255,255,255,255));
							
							SDL_Flip(screen);
							break;
				
				case SDLK_0: opciones("Salir", 360, 545); done=0;
							break;
			}
		}
	}	
		SDL_Delay(1000);
		for(i=0;i<12;i++)
			SDL_FreeSurface(imagen[i]); 
		SDL_Quit();

	
	return 0;	
	
}
