#define WIDTH_SCREEN 967
#define HEIGHT_SCREEN 660
#define MAX_TILE_X 29 //para el eje X
#define MAX_TILE_Y 20 // para el eje Y
#define WIDTH_TILE 33
#define HEIGHT_TILE 33
#define FPS (1000/64)

char mapa[MAX_TILE_Y][MAX_TILE_X] = {
	"XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
	"X           XXXXX       ooo X",
	"X XXX XXXXX XXXXX XXXXX XXX X",
	"X XXX XXXXX XXXXX XXXXX XXX X",
	"X XXX                   XXX X",
	"X     XX XXXXXXXXXXX XX     X",
	"X XXX XX     XXX     XX XXX X",
	"X XXX XXXXXX XXX XXXXXX XXX X",
	"X XXX XXo    ooo     XX XXX X",
	"X     XXoXXXXXXXXXXXoXX ooo X",
	"X XXX XXoXXXXXXXXXXXoXX XXX X",
	"X XXX XXoooo     ooooXX XXX X",
	"X XXX XXXXXX XXX XXXXXX XXX X",
	"X     XX     XXX    oXX     X",
	"X XXX XX XXXXXXXXXXX XX XXX X",
	"X XXX                   XXX X",
	"X XXX XXXX XXXXXXXX XXX XXX X",
	"X XXX XXXX          XXX XXX X",
	"X          XXXXXXXX         X",
	"XXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
};

typedef enum {FALSO,VERDADERO}booleano;
typedef enum {IZQUIERDA,DERECHA,ARRIBA,ABAJO,CERRADO}Direcciones;
enum {
	PACMAN,
	MUERTE,
	ENEMIGO,
	COMIDA,
	ROCA,
	FONDO_NEGRO,
	TOTAL_IMAGENES
};

const char *imagesNames[TOTAL_IMAGENES] = {
	"./images/pacman.bmp",
	"./images/muerte.bmp",
	"./images/enemigo.bmp",
	"./images/comida.bmp",
	"./images/roca.bmp",
	"./images/negro.bmp"
};
