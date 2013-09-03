/*
*	Erick Jesus Martinez Castillo
*	Curso de SDL en lenguaje C
*	Juego de Pacman
*
*
*
*/
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string.h>
#include "escenario.h"

void setup(void);
void dibujarMapa();
void moverPacman(int*x , int* y, int *oldX, int* oldY, int* direccion, SDLKey key);
void dibujarPacman (int x, int y, int oldX, int oldY,int direccion);
booleano isGameOver();

SDL_Surface *screen;
SDL_Surface *images[TOTAL_IMAGENES];
int subframe;


void moverPacman(int*x , int* y, int *oldX, int* oldY, int* direccion, SDLKey key){
	switch (key)
	{
		case SDLK_RIGHT:
			if(*x < MAX_TILE_X-1 && mapa[*y ][(*x) +1] != 'X'){
				*oldX = (*x)++;
				*oldY = *y;
				*direccion = DERECHA;
				printf("x: %d dir: %d\n",*x,*direccion);
			}
			break;
		case SDLK_LEFT:
			if(*x > 0 && mapa[*y][(*x)-1] != 'X'){
				*oldX = (*x)--;
				*oldY = *y;
				*direccion = IZQUIERDA;
				printf("x: %d dir: %d\n",*x	,*direccion);
			}
			break;
		case SDLK_UP:
			if(*y > 0 && mapa[(*y)-1][*x] != 'X'){
				*oldX = *x;
				*oldY = (*y)--;
				*direccion = ARRIBA;
				printf("y: %d dir: %d\n",*y,*direccion);
			}
			break;
		case SDLK_DOWN:
			if(*y < MAX_TILE_Y-1 && mapa[(*y)+1][*x] != 'X'){
				*oldX = *x;
				*oldY = (*y)++;
				*direccion = ABAJO;
				printf("y: %d dir: %d\n",*y,*direccion);
			}
			break;
	}
}




int main(){
	SDL_Rect rectangulo,aux;
	int frame;
	int x, y,oldX,oldY,direccion = IZQUIERDA;
	oldX = x = 14;
	oldY = y = 11;
	Uint32 now_time, last_time;
	
	setup();	
	
	dibujarMapa();
	SDL_Flip (screen);
	
	SDL_Event evento;
	frame = 0;
	while (!isGameOver());	
	{
		last_time = SDL_GetTicks();
		while(SDL_PollEvent(&evento))
		{
			switch (evento.type)
			{
				case SDL_QUIT:
					SDL_Quit();
					exit(1);
					break;
				case SDL_KEYDOWN:
					moverPacman(&x, &y, &oldX, &oldY, &direccion, evento.key.keysym.sym);
					break;
			}
		}
		subframe = frame / 8;
		dibujarPacman (x ,y, oldX, oldY, direccion);
		SDL_Flip (screen);
		
		//Cuadros y tiempo
		frame++; 
		if(frame >31)
			frame = 0;
		now_time = (Uint32)SDL_GetTicks();
		if(now_time < last_time + FPS)
			SDL_Delay (last_time + FPS - now_time);
		
	}
}

void dibujarPacman (int x, int y, int oldX, int oldY,int direccion){
	SDL_Rect anterior, nuevo;
	printf ("x: %d y: %d oldX: %d oldY: %d direccion: %d\n",x,y,oldX,oldY,direccion);
	
	if(mapa[oldY][oldX] == 'o')
		strcpy(&mapa[oldY][oldX]," ");
		
	if(y == 9){
		if(x<=0)
			x = MAX_TILE_X;
		else if(x >= MAX_TILE_X-1)
			x=0;
	}
	
	//Borrar pacman anterior
	anterior.x = oldX * WIDTH_TILE;
	anterior.y = oldY * HEIGHT_TILE;
	anterior.w = WIDTH_TILE;
	anterior.h = HEIGHT_TILE;
	SDL_BlitSurface (images[FONDO_NEGRO], NULL, screen, &anterior); 
	
	//Dibujar Pacman //Leer del archivo
	anterior.y = 0;
	
	//Señalar en qué posición de la pantalla se va a dibujar
	nuevo.x = x * WIDTH_TILE;
	nuevo.y = y * HEIGHT_TILE;
	nuevo.w = WIDTH_TILE;
	nuevo.h = HEIGHT_TILE;

	//SDL_BlitSurface (images[PACMAN], &anterior, screen, &nuevo);
	if((subframe %2)){
		anterior.x = CERRADO * WIDTH_TILE;
		SDL_BlitSurface (images[PACMAN], &anterior, screen, &nuevo);
	}
	else{
		anterior.x = direccion * WIDTH_TILE;
		SDL_BlitSurface (images[PACMAN], &anterior, screen, &nuevo);
	}
}

void setup(){
	SDL_Surface *imagenCargada;
	int bpp,i;
	
	if(SDL_Init (SDL_INIT_VIDEO) < 0) {
		fprintf(stderr,"No se pudo inicializar el sistema de video\n"
				"El error devuelto fue %s\n",SDL_GetError());
		exit(1);
	}
	
	bpp = SDL_VideoModeOK (WIDTH_SCREEN,HEIGHT_SCREEN, 16, 0);

	if(bpp == 0){
		fprintf(stderr,"Error: No se pudo establecer el video\n");
		exit (1);
	}
	
	screen = SDL_SetVideoMode(WIDTH_SCREEN, HEIGHT_SCREEN, bpp, 0);
	
	for(i = 0; i < TOTAL_IMAGENES ; i++){
		imagenCargada = IMG_Load (imagesNames[i]);
		if(imagenCargada == NULL){
			fprintf(stderr,"Error al cargar : %s\n",SDL_GetError());
			exit(1);
		}
		else{
			SDL_SetColorKey (imagenCargada, SDL_SRCCOLORKEY,0xff00ff); // Establecer transparencia	
			images[i] = imagenCargada;
		}
	}	
}

void dibujarMapa (){
	SDL_Rect rectangulo;
	rectangulo.w = WIDTH_TILE;
	rectangulo.h = HEIGHT_TILE;
	int fila, columna;
	for (fila = 0; fila < MAX_TILE_Y; fila++){
		for(columna = 0; columna < MAX_TILE_X; columna++){
			rectangulo.x = columna * WIDTH_TILE;
			rectangulo.y = fila * HEIGHT_TILE;
			if (mapa[fila][columna] == 'X')
				SDL_BlitSurface (images[ROCA],NULL, screen,&rectangulo);
			else if(mapa[fila][columna] == 'o')
				SDL_BlitSurface (images[COMIDA], NULL, screen, &rectangulo);
		}
	}
}

booleano isGameOver (){
	int i,j;
	for (i = 0; i < MAX_TILE_X ; i++){
		for(j = 0; j < MAX_TILE_Y ; j++){
			if(mapa[j][i] == 'o')
				return FALSO;
		}
	}
	return VERDADERO;
}

