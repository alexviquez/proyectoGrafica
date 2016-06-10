#include "Main.h"
#include "3ds.h"
#include <stdlib.h>
#include <stdio.h>

HDC			hDC=NULL;		// Dispositivo de contexto GDI
HGLRC		hRC=NULL;		// Contexto de renderizado
HWND		hWnd=NULL;		// Manejador de ventana
HINSTANCE	hInstance;		// Instancia de la aplicacion

bool	keys[256];			// Arreglo para el manejo de teclado
bool	active=TRUE;		// Bandera de ventana activa

int glWidth;
int glHeight;

//PROGRAMA 3
CTga textura[50];
float cx = 0.0f;
//Apuntador para primitivas de cuadricas
GLUquadricObj	*e;

/*SE CAMBIA PARA EL PROGRAMA 2
//Nombre y ubicación de los modelos
#define FILE_NAME1  "Modelos/modelo1.3ds"
#define FILE_NAME2  "Modelos/modelo2.3ds"
#define FILE_NAME3  "Modelos/modelo3.3ds"

//Contenedores de texturas de cada modelo
CTga textureModel1[4];
CTga textureModel2[4];
CTga textureModel3[4];

//Contenedor de texturas para el escenario
CTga textureName[20];

//Objeto que da acceso a las funciones del cargador 3ds
CLoad3DS g_Load3ds;

//Instancias de la estructura que almacenaran los datos de cada modelo
t3DModel g_3DModel1;
t3DModel g_3DModel2;
t3DModel g_3DModel3;
*/

//CAMBIOS PROGRAMA 2

//Nombre y ubicación del modelo
#define FILE_NAME1c  "Modelos/stewie_torso.3ds"
#define FILE_NAME2c  "Modelos/stewie_cabeza.3ds"
#define FILE_NAME3c  "Modelos/stewie_piernader.3ds"
#define FILE_NAME4c  "Modelos/stewie_piernaizq.3ds"
#define FILE_NAME5c  "Modelos/stewie_brazoder_a.3ds"
#define FILE_NAME6c  "Modelos/stewie_brazoder_b.3ds"
#define FILE_NAME7c  "Modelos/stewie_brazoizq_a.3ds"
#define FILE_NAME8c  "Modelos/stewie_brazoizq_b.3ds"
#define FILE_NAME9c  "Modelos/stewie_bota.3ds"

//Contenedor de texturas del modelo
CTga textureModel1c[20];
CTga textureModel2c[20];
CTga textureModel3c[20];
CTga textureModel4c[20];
CTga textureModel5c[20];
CTga textureModel6c[20];
CTga textureModel7c[20];
CTga textureModel8c[20];
CTga textureModel9c[20];

CLoad3DS g_Load3ds;

//Acceso a la estructura que almacena los datos del modelo
t3DModel g_3DModel1c;
t3DModel g_3DModel2c;
t3DModel g_3DModel3c;
t3DModel g_3DModel4c;
t3DModel g_3DModel5c;
t3DModel g_3DModel6c;
t3DModel g_3DModel7c;
t3DModel g_3DModel8c;
t3DModel g_3DModel9c;

//Objeto para acceder a las variables de control del personaje
paramObjCam player1;

//PROGRAMA 2
//Variables del personaje
float Angt1;
float Angt2;
float Angc1;
float Angc2;
float Angbi1;
float Angbi2;
float Angbib;
float Angbd1;
float Angbd2;
float Angbdb;
float Angpizq1;
float Angpizq2;
float Angpder1;
float Angpder2;
float Angpi;
float Angpd;

float Xtor;
float Ytor;
float Ztor;

//Variables adicionales PROYECTO FINAL************************************
float margen = 0.0f;
CVector vec1;
CVector vec2;
CVector N;
				//Variables de función bloque
float p1;   //Posición en X del bloque
float p2;	//Posición en Y del bloque
float p3;	//Posición en Z del bloque
float p4;	//Coeficiente que indica el tamaño del margen de los bordes
float p5;	//Posición en X del punto de la cara frontal
float p6;	//Posición en Y del punto de la cara frontal
int p7;	//Tamaño del bloque    1: Chico, 2: Grande 3:Alargado horizontal 4:Alargado vertical

FILE *archivo;
//*************************************************************************

//PROGRAMA 1
CVector camara;

//PROGRAMA 2
//Variables para iluminacion
GLfloat LightPos[] = { 40.0f, 80.0f, 50.0f, 1.0f};		// Posición de la luz
GLfloat LightAmb[] = { 0.8f,  0.8f, 0.8f, 1.0f};		// Valores de la componente ambiente
GLfloat LightDif[] = { 0.9f,  0.9f, 0.9f, 1.0f};		// Valores de la componente difusa
GLfloat LightSpc[] = { 0.5f,  0.5f, 0.5f, 1.0f};		// Valores de la componente especular
CVector lightPosition;

//Material default
GLfloat gDefaultAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
GLfloat gDefaultDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
GLfloat gDefaultSpecular[]= {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat gDefaultShininess = 0.0f;

//Metal 1
GLfloat metalAmb1[] = {0.2f, 0.2f, 0.2f, 1.0f};
GLfloat metalDif1[] = {0.6f, 0.6f, 0.6f, 1.0f};
GLfloat metalSpe1[] = {0.9f, 0.9f, 0.9f, 1.0f};
GLfloat metalShi1 = 120.0f;

//Metal 2
GLfloat metalAmb2[] = { 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat metalDif2[] = { 0.6f, 0.6f, 0.6f, 1.0f };
GLfloat metalSpe2[] = { 0.9f, 0.9f, 0.9f, 1.0f };
GLfloat metalShi2 = 120.0f;

//PROGRAMA 3
//Variables para animaciones
const int maxKF1=3; //Num. total de KeyFrames para la secuencia 1 (caminar)
const int maxKF2=2; //Num. total de KeyFrames para la secuencia 2 (saltar)
const int maxKF3=2; //Num. total de KeyFrames para la secuencia 3 (disparar)

FRAME KeyFrame1[maxKF1]; //Contenedor para almacenar cada keyframe de la secuencia 1
FRAME KeyFrame2[maxKF2]; //Contenedor para almacenar cada keyframe de la secuencia 2
FRAME KeyFrame3[maxKF3]; //Contenedor para almacenar cada keyframe de la secuencia 3

//Variables auxiliares para animacion
bool play=false; //Bandera para iniciar la animación
int playIndex=0; //Auxiliar para leer la información del contenedor de keyframes
int tipoAnim=1; //Indicador del tipo de animación: 1-caminando, 2-saltando, 3-disparando

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaracion de WndProc (Procedimiento de ventana)

GLvoid ReDimensionaEscenaGL(GLsizei width, GLsizei height)	// Redimensiona e inicializa la ventana
{
	if (height==0)							// Para que no se presente una division por cero
	{
		height=1;							// la altura se iguala a 1
	}

	glViewport(0,0,width,height);					// Resetea el puerto de vista

	glMatrixMode(GL_PROJECTION);					// Selecciona la Matriz de Proyeccion
	glLoadIdentity();								// Resetea la Matriz de Proyeccion

	// Calcula el radio de aspecto o proporcion de medidas de la ventana
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,2000.0f);
	
	glMatrixMode(GL_MODELVIEW);							// Selecciona la Matriz de Vista de Modelo
	glLoadIdentity();									// Resetea la Matriz de Vista de Modelo

	glWidth=width;
	glHeight=height;
}
/*
int CargaModelos()
{
	if(!g_Load3ds.Load3DSFile(FILE_NAME1, &g_3DModel1, textureModel1))
		return 0;
	if(!g_Load3ds.Load3DSFile(FILE_NAME2, &g_3DModel2, textureModel2))
		return 0;
	if(!g_Load3ds.Load3DSFile(FILE_NAME3, &g_3DModel3, textureModel3))
		return 0;
	
	return TRUE;
}

void DescargaModelos()
{
	g_Load3ds.UnLoad3DSFile(&g_3DModel1, textureModel1);
	g_Load3ds.UnLoad3DSFile(&g_3DModel2, textureModel2);
	g_Load3ds.UnLoad3DSFile(&g_3DModel3, textureModel3);
}
*/

//PROGRAMA 2
int CargaModelos()
{
	if(!g_Load3ds.Load3DSFile(FILE_NAME1c, &g_3DModel1c, textureModel1c))
		return 0;
	if(!g_Load3ds.Load3DSFile(FILE_NAME2c, &g_3DModel2c, textureModel2c))
		return 0;
	if(!g_Load3ds.Load3DSFile(FILE_NAME3c, &g_3DModel3c, textureModel3c))
		return 0;
	if(!g_Load3ds.Load3DSFile(FILE_NAME4c, &g_3DModel4c, textureModel4c))
		return 0;
	if(!g_Load3ds.Load3DSFile(FILE_NAME5c, &g_3DModel5c, textureModel5c))
		return 0;
	if(!g_Load3ds.Load3DSFile(FILE_NAME6c, &g_3DModel6c, textureModel6c))
		return 0;
	if(!g_Load3ds.Load3DSFile(FILE_NAME7c, &g_3DModel7c, textureModel7c))
		return 0;
	if(!g_Load3ds.Load3DSFile(FILE_NAME8c, &g_3DModel8c, textureModel8c))
		return 0;
	if(!g_Load3ds.Load3DSFile(FILE_NAME9c, &g_3DModel9c, textureModel9c))
		return 0;
	
	return TRUE;
}

void DescargaModelos()
{
	g_Load3ds.UnLoad3DSFile(&g_3DModel1c, textureModel1c);
	g_Load3ds.UnLoad3DSFile(&g_3DModel2c, textureModel2c);
	g_Load3ds.UnLoad3DSFile(&g_3DModel3c, textureModel3c);
	g_Load3ds.UnLoad3DSFile(&g_3DModel4c, textureModel4c);
	g_Load3ds.UnLoad3DSFile(&g_3DModel5c, textureModel5c);
	g_Load3ds.UnLoad3DSFile(&g_3DModel6c, textureModel6c);
	g_Load3ds.UnLoad3DSFile(&g_3DModel7c, textureModel7c);
	g_Load3ds.UnLoad3DSFile(&g_3DModel8c, textureModel8c);
	g_Load3ds.UnLoad3DSFile(&g_3DModel9c, textureModel9c);
		
}

//PROGRAMA 3
void cargaTexturas()
{
	textura[0].LoadTGA("Texturas/t1.tga");
	textura[1].LoadTGA("Texturas/t2.tga");
	textura[2].LoadTGA("Texturas/t3.tga");
	textura[3].LoadTGA("Texturas/t4.tga");
	textura[4].LoadTGA("Texturas/t5.tga");
	textura[5].LoadTGA("Texturas/t6.tga");
	textura[6].LoadTGA("Texturas/t7.tga");
	textura[7].LoadTGA("Texturas/t8.tga");
	textura[8].LoadTGA("Texturas/t9.tga");
	textura[9].LoadTGA("Texturas/t10.tga");
	textura[10].LoadTGA("Texturas/t11.tga");
	textura[11].LoadTGA("Texturas/t12.tga");
	textura[12].LoadTGA("Texturas/t13.tga");
	textura[13].LoadTGA("Texturas/t14.tga");
	textura[14].LoadTGA("Texturas/t15.tga");
	textura[15].LoadTGA("Texturas/t16.tga");
	textura[16].LoadTGA("Texturas/t17.tga");
	textura[17].LoadTGA("Texturas/t18.tga");
	textura[18].LoadTGA("Texturas/t19.tga");
	textura[19].LoadTGA("Texturas/t20.tga");
	textura[20].LoadTGA("Texturas/t21.tga");
	textura[21].LoadTGA("Texturas/t22.tga");
	textura[22].LoadTGA("Texturas/t23.tga");
	textura[23].LoadTGA("Texturas/t24.tga");
	textura[24].LoadTGA("Texturas/t25.tga");
	textura[25].LoadTGA("Texturas/t26.tga");
	textura[26].LoadTGA("Texturas/t27.tga");
}

void descargaTexturas()
{
	for(int i=0; i<27; i++)
		textura[i].Elimina();
}

void InicializaParametrosdeControl()
{
	//Esta función establece los parámetros como velocidad del objeto y distancia de la cámara así como la posición y dirección iniciales

	player1.visible=true;

	player1.VelocidadObj=0.5f;
	player1.DistanciaCam=50.0f;
	
	player1.AngObj=90.0f;		//Este valor se elige dependiendo de la orientación con la que aparece el modelo en la escena al dibujarlo
								//sin aplicarle ninguna transformación (hacia adonde está volteando). 
		
	player1.PosicionObj=CVector(-100.0f, 0.0f, 0.0f); //Esta es la posición inicial del objeto en la escena
		
	player1.escalaX=0.9f;
	player1.escalaY=0.9f;
	player1.escalaZ=0.9f;
		
}

void IniVarsPlayer()
{
	Angt1=0.0f;   //Torso: rotación en X
	Angt2=0.0f;   //Torso: rotación en Y
	Angc1=0.0f;   //Cabeza: rotación en X
	Angc2=0.0f;   //Cabeza: rotación en Y
	Angbi1=0.0f;  //Brazo Izq: rotación en X
	Angbi2=0.0f;  //Brazo Izq: rotación en Z
	Angbib=0.0f;  //Antebrazo Izq: rotación en X
	Angbd1=0.0f;  //Brazo Der: rotación en X
	Angbd2=0.0f;  //Brazo Der: rotación en Z
	Angbdb=0.0f;  //Antebrazo Der: rotación en X
	Angpizq1=0.0f; //Pierna Izq: rotación en X
	Angpizq2=0.0f; //Pierna Izq: rotación en Z
	Angpder1=0.0f; //Pierna Der: rotación en X
	Angpder2=0.0f; //Pierna Der: rotación en Z
	Angpi=0.0f;   //Pie Izq: rotación en X
	Angpd=0.0f;   //Pie Der: rotación en X

	Xtor=0.0f;    //Torso: posición en X
	Ytor=0.0f;    //Torso: posición en Y
	Ztor=0.0f;    //Torso: posición en Z
}

//PROGRAMA 3
void InicializaAnim()
{
	//Se inicializan las variables de la secuencia 1
	for(int i=0; i<maxKF1; i++)
	{
		KeyFrame1[i].Angt1=0.0f;
		KeyFrame1[i].Angt2=0.0f;
		KeyFrame1[i].Angc1=0.0f;
		KeyFrame1[i].Angc2=0.0f;
		KeyFrame1[i].Angbi1=0.0f;
		KeyFrame1[i].Angbi2=0.0f;
		KeyFrame1[i].Angbib=0.0f;
		KeyFrame1[i].Angbd1=0.0f;
		KeyFrame1[i].Angbd2=0.0f;
		KeyFrame1[i].Angbdb=0.0f;
		KeyFrame1[i].Angpizq1=0.0f;
		KeyFrame1[i].Angpizq2=0.0f;
		KeyFrame1[i].Angpder1=0.0f;
		KeyFrame1[i].Angpder2=0.0f;
		KeyFrame1[i].Angpi=0.0f;
		KeyFrame1[i].Angpd=0.0f;
		KeyFrame1[i].Xtor=0.0f;
		KeyFrame1[i].Ytor=0.0f;
		KeyFrame1[i].Ztor=0.0f;

		KeyFrame1[i].incAngt1=0.0f;
		KeyFrame1[i].incAngt1=0.0f;
		KeyFrame1[i].incAngc1=0.0f;
		KeyFrame1[i].incAngc2=0.0f;
		KeyFrame1[i].incAngbi1=0.0f;
		KeyFrame1[i].incAngbi2=0.0f;
		KeyFrame1[i].incAngbib=0.0f;
		KeyFrame1[i].incAngbd1=0.0f;
		KeyFrame1[i].incAngbd2=0.0f;
		KeyFrame1[i].incAngbdb=0.0f;
		KeyFrame1[i].incAngpizq1=0.0f;
		KeyFrame1[i].incAngpizq2=0.0f;
		KeyFrame1[i].incAngpder1=0.0f;
		KeyFrame1[i].incAngpder2=0.0f;
		KeyFrame1[i].incAngpi=0.0f;
		KeyFrame1[i].incAngpd=0.0f;
		KeyFrame1[i].incXtor=0.0f;
		KeyFrame1[i].incYtor=0.0f;
		KeyFrame1[i].incZtor=0.0f;
	}

	//Se inicializan las variables de la secuencia 2
	for(int i=0; i<maxKF2; i++)
	{
		KeyFrame2[i].Angt1=0.0f;
		KeyFrame2[i].Angt2=0.0f;
		KeyFrame2[i].Angc1=0.0f;
		KeyFrame2[i].Angc2=0.0f;
		KeyFrame2[i].Angbi1=0.0f;
		KeyFrame2[i].Angbi2=0.0f;
		KeyFrame2[i].Angbib=0.0f;
		KeyFrame2[i].Angbd1=0.0f;
		KeyFrame2[i].Angbd2=0.0f;
		KeyFrame2[i].Angbdb=0.0f;
		KeyFrame2[i].Angpizq1=0.0f;
		KeyFrame2[i].Angpizq2=0.0f;
		KeyFrame2[i].Angpder1=0.0f;
		KeyFrame2[i].Angpder2=0.0f;
		KeyFrame2[i].Angpi=0.0f;
		KeyFrame2[i].Angpd=0.0f;
		KeyFrame2[i].Xtor=0.0f;
		KeyFrame2[i].Ytor=0.0f;
		KeyFrame2[i].Ztor=0.0f;

		KeyFrame2[i].incAngt1=0.0f;
		KeyFrame2[i].incAngt1=0.0f;
		KeyFrame2[i].incAngc1=0.0f;
		KeyFrame2[i].incAngc2=0.0f;
		KeyFrame2[i].incAngbi1=0.0f;
		KeyFrame2[i].incAngbi2=0.0f;
		KeyFrame2[i].incAngbib=0.0f;
		KeyFrame2[i].incAngbd1=0.0f;
		KeyFrame2[i].incAngbd2=0.0f;
		KeyFrame2[i].incAngbdb=0.0f;
		KeyFrame2[i].incAngpizq1=0.0f;
		KeyFrame2[i].incAngpizq2=0.0f;
		KeyFrame2[i].incAngpder1=0.0f;
		KeyFrame2[i].incAngpder2=0.0f;
		KeyFrame2[i].incAngpi=0.0f;
		KeyFrame2[i].incAngpd=0.0f;
		KeyFrame2[i].incXtor=0.0f;
		KeyFrame2[i].incYtor=0.0f;
		KeyFrame2[i].incZtor=0.0f;
	}

	//Se inicializan las variables de la secuencia 3
	for(int i=0; i<maxKF3; i++)
	{
		KeyFrame3[i].Angt1=0.0f;
		KeyFrame3[i].Angt2=0.0f;
		KeyFrame3[i].Angc1=0.0f;
		KeyFrame3[i].Angc2=0.0f;
		KeyFrame3[i].Angbi1=0.0f;
		KeyFrame3[i].Angbi2=0.0f;
		KeyFrame3[i].Angbib=0.0f;
		KeyFrame3[i].Angbd1=0.0f;
		KeyFrame3[i].Angbd2=0.0f;
		KeyFrame3[i].Angbdb=0.0f;
		KeyFrame3[i].Angpizq1=0.0f;
		KeyFrame3[i].Angpizq2=0.0f;
		KeyFrame3[i].Angpder1=0.0f;
		KeyFrame3[i].Angpder2=0.0f;
		KeyFrame3[i].Angpi=0.0f;
		KeyFrame3[i].Angpd=0.0f;
		KeyFrame3[i].Xtor=0.0f;
		KeyFrame3[i].Ytor=0.0f;
		KeyFrame3[i].Ztor=0.0f;

		KeyFrame3[i].incAngt1=0.0f;
		KeyFrame3[i].incAngt1=0.0f;
		KeyFrame3[i].incAngc1=0.0f;
		KeyFrame3[i].incAngc2=0.0f;
		KeyFrame3[i].incAngbi1=0.0f;
		KeyFrame3[i].incAngbi2=0.0f;
		KeyFrame3[i].incAngbib=0.0f;
		KeyFrame3[i].incAngbd1=0.0f;
		KeyFrame3[i].incAngbd2=0.0f;
		KeyFrame3[i].incAngbdb=0.0f;
		KeyFrame3[i].incAngpizq1=0.0f;
		KeyFrame3[i].incAngpizq2=0.0f;
		KeyFrame3[i].incAngpder1=0.0f;
		KeyFrame3[i].incAngpder2=0.0f;
		KeyFrame3[i].incAngpi=0.0f;
		KeyFrame3[i].incAngpd=0.0f;
		KeyFrame3[i].incXtor=0.0f;
		KeyFrame3[i].incYtor=0.0f;
		KeyFrame3[i].incZtor=0.0f;
	}
}

void DatosAnimacion()
{
	//Secuencia 1
	KeyFrame1[0].Angt1=25.0f;
	KeyFrame1[0].Angt2=90.0f;
	KeyFrame1[0].Angc1=-25.0f;
	KeyFrame1[0].Angc2=0.0f;
	KeyFrame1[0].Angbi1=-100.0f;
	KeyFrame1[0].Angbi2=0.0f;
	KeyFrame1[0].Angbib=-30.0f;
	KeyFrame1[0].Angbd1=120.0f;
	KeyFrame1[0].Angbd2=0.0f;
	KeyFrame1[0].Angbdb=-80.0f;
	KeyFrame1[0].Angpizq1=40.0f;
	KeyFrame1[0].Angpizq2=0.0f;
	KeyFrame1[0].Angpder1=-60.0f;
	KeyFrame1[0].Angpder2=0.0f;
	KeyFrame1[0].Angpi=30.0f;
	KeyFrame1[0].Angpd=40.0f;
	KeyFrame1[0].Xtor=0.0f;
	KeyFrame1[0].Ytor=0.0f;
	KeyFrame1[0].Ztor=0.0f;

	KeyFrame1[1].Angt1=25.0f;
	KeyFrame1[1].Angt2=0.0f;
	KeyFrame1[1].Angc1=-25.0f;
	KeyFrame1[1].Angc2=0.0f;
	KeyFrame1[1].Angbi1=120.0f;
	KeyFrame1[1].Angbi2=0.0f;
	KeyFrame1[1].Angbib=-80.0f;
	KeyFrame1[1].Angbd1=-100.0f;
	KeyFrame1[1].Angbd2=0.0f;
	KeyFrame1[1].Angbdb=-30.0f;
	KeyFrame1[1].Angpizq1=-60.0f;
	KeyFrame1[1].Angpizq2=0.0f;
	KeyFrame1[1].Angpder1=40.0f;
	KeyFrame1[1].Angpder2=0.0f;
	KeyFrame1[1].Angpi=40.0f;
	KeyFrame1[1].Angpd=30.0f;
	KeyFrame1[1].Xtor=0.0f;
	KeyFrame1[1].Ytor=0.0f;
	KeyFrame1[1].Ztor=0.0f;

	KeyFrame1[2].Angt1=25.0f;
	KeyFrame1[2].Angt2=0.0f;
	KeyFrame1[2].Angc1=-25.0f;
	KeyFrame1[2].Angc2=0.0f;
	KeyFrame1[2].Angbi1=-100.0f;
	KeyFrame1[2].Angbi2=0.0f;
	KeyFrame1[2].Angbib=-30.0f;
	KeyFrame1[2].Angbd1=120.0f;
	KeyFrame1[2].Angbd2=0.0f;
	KeyFrame1[2].Angbdb=-80.0f;
	KeyFrame1[2].Angpizq1=40.0f;
	KeyFrame1[2].Angpizq2=0.0f;
	KeyFrame1[2].Angpder1=-40.0f;
	KeyFrame1[2].Angpder2=0.0f;
	KeyFrame1[2].Angpi=30.0f;
	KeyFrame1[2].Angpd=20.0f;
	KeyFrame1[2].Xtor=0.0f;
	KeyFrame1[2].Ytor=0.0f;
	KeyFrame1[2].Ztor=0.0f;
	
	//Secuencia 2
	KeyFrame2[0].Angt1=0.0f;
	KeyFrame2[0].Angt2=25.0f;
	KeyFrame2[0].Angc1=0.0f;
	KeyFrame2[0].Angc2=20.0f;
	KeyFrame2[0].Angbi1=-140.0f;
	KeyFrame2[0].Angbi2=45.0f;
	KeyFrame2[0].Angbd1=-180.0f;
	KeyFrame2[0].Angbd2=-30.0f;
	KeyFrame2[0].Angpizq1=-75.0f;
	KeyFrame2[0].Angpizq2=0.0f;
	KeyFrame2[0].Angpder1=25.0f;
	KeyFrame2[0].Angpder2=-10.0f;
	KeyFrame2[0].Angpi=45.0f;
	KeyFrame2[0].Angpd=10.0f;
	KeyFrame2[0].Xtor=0.0f;
	KeyFrame2[0].Ytor=0.0f;
	KeyFrame2[0].Ztor=0.0f;

	KeyFrame2[1].Angt1=0.0f;
	KeyFrame2[1].Angt2=0.0f;
	KeyFrame2[1].Angc1=0.0f;
	KeyFrame2[1].Angc2=0.0f;
	KeyFrame2[1].Angbi1=0.0f;
	KeyFrame2[1].Angbi2=0.0f;
	KeyFrame2[1].Angbd1=0.0f;
	KeyFrame2[1].Angbd2=0.0f;
	KeyFrame2[1].Angpizq1=0.0f;
	KeyFrame2[1].Angpizq2=0.0f;
	KeyFrame2[1].Angpder1=0.0f;
	KeyFrame2[1].Angpder2=0.0f;
	KeyFrame2[1].Angpi=0.0f;
	KeyFrame2[1].Angpd=0.0f;
	KeyFrame2[1].Xtor=0.0f;
	KeyFrame2[1].Ytor=0.0f;
	KeyFrame2[1].Ztor=0.0f;

	//Secuencia 3
	KeyFrame3[0].Angt1=0.0f;
	KeyFrame3[0].Angt2=0.0f;
	KeyFrame3[0].Angc1=0.0f;
	KeyFrame3[0].Angc2=0.0f;
	KeyFrame3[0].Angbi1=0.0f;
	KeyFrame3[0].Angbi2=0.0f;
	KeyFrame3[0].Angbd1=0.0f;
	KeyFrame3[0].Angbd2=0.0f;
	KeyFrame3[0].Angpizq1=0.0f;
	KeyFrame3[0].Angpizq2=0.0f;
	KeyFrame3[0].Angpder1=0.0f;
	KeyFrame3[0].Angpder2=0.0f;
	KeyFrame3[0].Angpi=0.0f;
	KeyFrame3[0].Angpd=0.0f;
	KeyFrame3[0].Xtor=0.0f;
	KeyFrame3[0].Ytor=0.0f;
	KeyFrame3[0].Ztor=0.0f;

	KeyFrame3[1].Angt1=0.0f;
	KeyFrame3[1].Angt2=0.0f;
	KeyFrame3[1].Angc1=0.0f;
	KeyFrame3[1].Angc2=0.0f;
	KeyFrame3[1].Angbi1=0.0f;
	KeyFrame3[1].Angbi2=0.0f;
	KeyFrame3[1].Angbd1=0.0f;
	KeyFrame3[1].Angbd2=0.0f;
	KeyFrame3[1].Angpizq1=0.0f;
	KeyFrame3[1].Angpizq2=0.0f;
	KeyFrame3[1].Angpder1=0.0f;
	KeyFrame3[1].Angpder2=0.0f;
	KeyFrame3[1].Angpi=0.0f;
	KeyFrame3[1].Angpd=0.0f;
	KeyFrame3[1].Xtor=0.0f;
	KeyFrame3[1].Ytor=0.0f;
	KeyFrame3[1].Ztor=0.0f;
}

int IniGL(GLvoid)										// Aqui se configuran los parametros iniciales de OpenGL
{
	glShadeModel(GL_SMOOTH);							// Activa Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Fondo negro
	glClearDepth(1.0f);									// Valor para el Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Activa Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a usar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Correccion de cálculos de perspectiva

	glCullFace(GL_BACK);								// Configurado para eliminar caras traseras
	glEnable(GL_CULL_FACE);								// Activa eliminacion de caras ocultas

	//PROGRAMA 2
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);		// Posicion de la luz0
	glLightfv(GL_LIGHT0, GL_AMBIENT,  LightAmb);		// Componente ambiente
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  LightDif);		// Componente difusa
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpc);		// Componente especular

	glEnable(GL_LIGHT0);					// Activa luz0
    glEnable(GL_LIGHTING);					// Habilita la iluminación

	e=gluNewQuadric();

	//PROGRAMA 2
	CargaModelos();
	//PROGRAMA 3
	cargaTexturas();
	InicializaAnim();
	DatosAnimacion();
	IniVarsPlayer();
	InicializaParametrosdeControl();

	//PROGRAMA 1
	camara=CVector(10.0f, 10.0f, 50.0f);

	return TRUE;										
}

//PROGRAMA 2
void SeleccionaMaterial(int tipo)
{
	if(tipo == 0)
	{
		//Material default de OpenGL
		glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, gDefaultDiffuse);
		glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, gDefaultAmbient);
		glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR,gDefaultSpecular);
		glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS,gDefaultShininess);
	}
	else if(tipo == 1)
	{
		//Metal 1
		glMaterialfv(GL_FRONT, GL_AMBIENT,   metalAmb1);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,   metalDif1);
		glMaterialfv(GL_FRONT, GL_SPECULAR,  metalSpe1);
		glMaterialf (GL_FRONT, GL_SHININESS, metalShi1);

	}

	else if(tipo == 2)
	{
	//Metal 2
		glMaterialfv(GL_FRONT, GL_AMBIENT,   metalAmb2);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,   metalDif2);
		glMaterialfv(GL_FRONT, GL_SPECULAR,  metalSpe2);
		glMaterialf (GL_FRONT, GL_SHININESS, metalShi2);
	}
}

//PROGRAMA 3
void animacion(FRAME *KeyFrame, int maxKF , int frames)
{
	if(play)
	{		
		if((abs(KeyFrame[playIndex+1].Angt1-Angt1))<0.1 &&
		   (abs(KeyFrame[playIndex+1].Angt2-Angt2))<0.1 &&
		   (abs(KeyFrame[playIndex+1].Angc1-Angc1))<0.1 &&
		   (abs(KeyFrame[playIndex+1].Angc2-Angc2))<0.1 &&
		   (abs(KeyFrame[playIndex+1].Angbi1-Angbi1))<0.1 &&
		   (abs(KeyFrame[playIndex+1].Angbi2-Angbi2))<0.1 &&
		   (abs(KeyFrame[playIndex+1].Angbib-Angbib))<0.1 &&
		   (abs(KeyFrame[playIndex+1].Angbd1-Angbd1))<0.1 &&
		   (abs(KeyFrame[playIndex+1].Angbd2-Angbd2))<0.1 &&
		   (abs(KeyFrame[playIndex+1].Angbdb-Angbdb))<0.1 &&
		   (abs(KeyFrame[playIndex+1].Angpizq1-Angpizq1))<0.1 &&
		   (abs(KeyFrame[playIndex+1].Angpizq2-Angpizq2))<0.1 &&
		   (abs(KeyFrame[playIndex+1].Angpder1-Angpder1))<0.1 &&
		   (abs(KeyFrame[playIndex+1].Angpder2-Angpder2))<0.1 &&
		   (abs(KeyFrame[playIndex+1].Angpi-Angpi))<0.1 &&
		   (abs(KeyFrame[playIndex+1].Angpd-Angpd))<0.1 &&
		   (abs(KeyFrame[playIndex+1].Xtor-Xtor))<0.1 &&
		   (abs(KeyFrame[playIndex+1].Ytor-Ytor))<0.1 &&
		   (abs(KeyFrame[playIndex+1].Ztor-Ztor))<0.1)
		{			
			playIndex++;			
			if(playIndex>maxKF-2)
			{
				playIndex=0;
				play=false;
								
			}
		}
		else
		{
			KeyFrame[playIndex].incAngt1   = (KeyFrame[playIndex+1].Angt1-KeyFrame[playIndex].Angt1)/frames;
			KeyFrame[playIndex].incAngt2   = (KeyFrame[playIndex+1].Angt2-KeyFrame[playIndex].Angt2)/frames;
			KeyFrame[playIndex].incAngc1   = (KeyFrame[playIndex+1].Angc1-KeyFrame[playIndex].Angc1)/frames;
			KeyFrame[playIndex].incAngc2   = (KeyFrame[playIndex+1].Angc2-KeyFrame[playIndex].Angc2)/frames;
			KeyFrame[playIndex].incAngbi1  = (KeyFrame[playIndex+1].Angbi1-KeyFrame[playIndex].Angbi1)/frames;
			KeyFrame[playIndex].incAngbi2  = (KeyFrame[playIndex+1].Angbi2-KeyFrame[playIndex].Angbi2)/frames;
			KeyFrame[playIndex].incAngbib  = (KeyFrame[playIndex+1].Angbib-KeyFrame[playIndex].Angbib)/frames;
			KeyFrame[playIndex].incAngbd1  = (KeyFrame[playIndex+1].Angbd1-KeyFrame[playIndex].Angbd1)/frames;
			KeyFrame[playIndex].incAngbd2  = (KeyFrame[playIndex+1].Angbd2-KeyFrame[playIndex].Angbd2)/frames;
			KeyFrame[playIndex].incAngbdb  = (KeyFrame[playIndex+1].Angbdb-KeyFrame[playIndex].Angbdb)/frames;
			KeyFrame[playIndex].incAngpizq1= (KeyFrame[playIndex+1].Angpizq1-KeyFrame[playIndex].Angpizq1)/frames;
			KeyFrame[playIndex].incAngpizq2= (KeyFrame[playIndex+1].Angpizq2-KeyFrame[playIndex].Angpizq2)/frames;
			KeyFrame[playIndex].incAngpder1= (KeyFrame[playIndex+1].Angpder1-KeyFrame[playIndex].Angpder1)/frames;
			KeyFrame[playIndex].incAngpder2= (KeyFrame[playIndex+1].Angpder2-KeyFrame[playIndex].Angpder2)/frames;
			KeyFrame[playIndex].incAngpi   = (KeyFrame[playIndex+1].Angpi-KeyFrame[playIndex].Angpi)/frames;
			KeyFrame[playIndex].incAngpd   = (KeyFrame[playIndex+1].Angpd-KeyFrame[playIndex].Angpd)/frames;
			KeyFrame[playIndex].incXtor    = (KeyFrame[playIndex+1].Xtor-KeyFrame[playIndex].Xtor)/frames;
			KeyFrame[playIndex].incYtor    = (KeyFrame[playIndex+1].Ytor-KeyFrame[playIndex].Ytor)/frames;
			KeyFrame[playIndex].incZtor    = (KeyFrame[playIndex+1].Ztor-KeyFrame[playIndex].Ztor)/frames;
			
			Angt1   += KeyFrame[playIndex].incAngt1;
			Angt2   += KeyFrame[playIndex].incAngt2;
			Angc1   += KeyFrame[playIndex].incAngc1;
			Angc2   += KeyFrame[playIndex].incAngc2;
			Angbi1  += KeyFrame[playIndex].incAngbi1;
			Angbi2  += KeyFrame[playIndex].incAngbi2;
			Angbib  += KeyFrame[playIndex].incAngbib;
			Angbd1  += KeyFrame[playIndex].incAngbd1;
			Angbd2  += KeyFrame[playIndex].incAngbd2;
			Angbdb  += KeyFrame[playIndex].incAngbdb;
			Angpizq1+= KeyFrame[playIndex].incAngpizq1;
			Angpizq2+= KeyFrame[playIndex].incAngpizq2;
			Angpder1+= KeyFrame[playIndex].incAngpder1;
			Angpder2+= KeyFrame[playIndex].incAngpder2;
			Angpi   += KeyFrame[playIndex].incAngpi;
			Angpd   += KeyFrame[playIndex].incAngpd;
			Xtor    += KeyFrame[playIndex].incXtor;
			Ytor    += KeyFrame[playIndex].incYtor;
			Ztor    += KeyFrame[playIndex].incZtor;
			
		}
	}
}

void ControlPersonaje(int funcion)
{
	if(funcion == 1) //Avanza a la derecha
	{
		player1.AngObj=90.0f;
		player1.PosicionObj.x+=2.3f;
	}
	else if(funcion == 2) //avanza a la izquierda
	{
		player1.AngObj=270.0f;
		player1.PosicionObj.x-=2.3f;
	}
	else if (funcion == 3) //sube escalera
	{
		player1.AngObj = 180.0f;
		player1.PosicionObj.y += 2.3f;
	}
	else if (funcion == 4) //baja escalera
	{
		player1.AngObj = 180.0f;
		player1.PosicionObj.y -= 2.3f;
	}
}

void DibujaEjes()
{
	//ROJO X
	//VERDE Y
	//AZUL Z
	glBegin(GL_LINES);
		//Eje X
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(-100.0f, 0.0f, 0.0f);
		glVertex3f( 100.0f, 0.0f, 0.0f);
		
		//Eje Y
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(0.0f, -100.0f, 0.0f);
		glVertex3f(0.0f,  100.0f, 0.0f);
		
		//Eje Z
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f, 0.0f, -100.0f);
		glVertex3f(0.0f, 0.0f,  100.0f);
	glEnd();

	glPointSize(10.0f);

	glBegin(GL_POINTS);
		//"Flecha" eje X
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f( 100.0f, 0.0f, 0.0f);

		//"Flecha" eje Y
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(0.0f,  100.0f, 0.0f);

		//"Flecha" eje Z
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(0.0f, 0.0f,  100.0f);
	glEnd();

	glPointSize(1.0f);

	glColor3f(1.0f,1.0f,1.0f);
}

//FUNCIONES PROGRAMA 1
void dibujaPlataforma()
{
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, textura[17].texID);
	//Cara frontal
	glColor3f(0.7f, 0.7f, 0.8f);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-2.5f, -2.5f, 2.5f);
		glTexCoord2f(1.0f, 0.0f);glVertex3f( 2.5f, -2.5f, 2.5f);
		glTexCoord2f(1.0f, 1.0f);glVertex3f( 2.5f,  2.5f, 2.5f);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(-2.5f,  2.5f, 2.5f);
	glEnd();

	//Cara superior
	glColor3f(0.5f, 0.5f, 0.8f);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-2.5f, 2.5f,  2.5f);
		glTexCoord2f(1.0f, 0.0f);glVertex3f( 2.5f, 2.5f,  2.5f);
		glTexCoord2f(1.0f, 1.0f);glVertex3f( 2.5f, 2.5f, -2.5f);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(-2.5f, 2.5f, -2.5f);
	glEnd();

	//Cara inferior
	glColor3f(0.4f, 0.4f, 0.7f);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);glVertex3f( 2.5f, -2.5f,  2.5f);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(-2.5f, -2.5f,  2.5f);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(-2.5f, -2.5f, -2.5f);
		glTexCoord2f(0.0f, 1.0f);glVertex3f( 2.5f, -2.5f, -2.5f);
	glEnd();

	//Cara derecha
	glColor3f(0.6f, 0.6f, 0.8f);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(2.5f, -2.5f,  2.5f);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(2.5f, -2.5f, -2.5f);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(2.5f,  2.5f, -2.5f);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(2.5f,  2.5f,  2.5f);
	glEnd();

	//Cara izquierda
	glColor3f(0.6f, 0.6f, 0.8f);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-2.5f, -2.5f, -2.5f);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(-2.5f, -2.5f,  2.5f);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(-2.5f,  2.5f,  2.5f);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(-2.5f,  2.5f, -2.5f);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
}


/**********************************************************MIS FUNCIONES ABNER!!!!!!!!! ***********************************************************************************************************/
//EN LOS PARÁMETROS SOLO PASEN EL ORIGEN DE LA FIGURA Y LISTO. EN EL CASO DE LA CALAQUITA LE PASAN TAMBIÉN EL TAMAÑO 
void dibujaCalaquita(float size,float origenX, float origenY, float origenZ)
{
	//Dibuja el marco negro primero
	glColor3f(0.2,0.2,0.2);
	glBegin(GL_QUADS);
		glVertex3f(origenX,origenY,origenZ);
		glVertex3f(origenX, origenY - size, origenZ);
		glVertex3f(origenX + size, origenY - size, origenZ);
		glVertex3f(origenX + size, origenY, origenZ);
	glEnd();

	//Dentro del marco se dibuja la calaquita
	//Cabeza de la calaca
	int triangulos = 50;
	GLfloat twicePI = 2 * PI;
	float centerX = origenX + size/2;
	float centerY = origenY - size/2;
	float radio = size/2 - 1;

	glColor3f(1,1,1);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(centerX, centerY);
		for(int i = 0; i <= triangulos; i++)
		{
			glVertex2f(centerX + (radio * cos(i * twicePI / triangulos)), centerY + (radio * sin(i * twicePI / triangulos)));
		}
	glEnd();

	//Dibujar ojos
	//Ojo izquierdo
	float radX = 1.0;
	float radY = 0.6;
	glColor3f(0.2,0.2,0.2);
	glPushMatrix();
		glTranslatef(5.5,3,0);
		glRotatef(-60,0,0,1);
		glBegin(GL_TRIANGLE_FAN);
			for(int i = 0; i < 360; i++)
			{
				float rad = i * (PI/180);
				glVertex2f(centerX + cos(rad)*radX, centerY + sin(rad)*radY);
			}
		glEnd();
	glPopMatrix();

	//Ojo derecho
	glColor3f(0.2,0.2,0.2);
	glPushMatrix();
		glTranslatef(-0.39,-5.529,0);
		glRotatef(60,0,0,1);
		glBegin(GL_TRIANGLE_FAN);
			for(int i = 0; i < 360; i++)
			{
				float rad = i * (PI/180);
				glVertex2f(centerX + cos(rad)*radX, centerY + sin(rad)*radY);
			}
		glEnd();
	glPopMatrix();

	//Boca
	triangulos = 50;
	twicePI = 2 * PI;
	centerX = origenX + size/2;
	centerY = origenY - size/2;
	radio = size/2 - 2.7;

	glColor3f(0.2,0.2,0.2);
	glPushMatrix();
		glTranslatef(10,-10.5,0);
		glRotatef(180,0,0,1);
		glBegin(GL_TRIANGLE_FAN);
			glVertex2f(centerX, centerY);
				for(int i = 0; i <= triangulos; i++)
				{
					glVertex2f(centerX + (radio * cos(i * PI / triangulos)), centerY + (radio * sin(i * PI / triangulos)));
				}
		glEnd();
	glPopMatrix();

	glColor3f(1,1,1);
}

 void dibujaAntorcha(float origenX, float origenY, float origenZ)
 {
	glColor3f(0.44, 0.33, 0.16);
	glBegin(GL_QUADS);
		glVertex3f(origenX,origenY,0);
		glVertex3f(origenX + 2.5,origenY - 5,0);
		glVertex3f(origenX + 5,origenY,0);
		glVertex3f(origenX + 5,origenY,0);
		glEnd();

	//Llamas
		for(int i = 0; i < 5; i++)
		{
			//Llamas primeras
			glColor3f(0.98, 0.41, 0.05);
			float nuevoOrigen = origenX + i;
			glBegin(GL_QUADS);
				glVertex3f(nuevoOrigen,origenY,0);
				glVertex3f(nuevoOrigen + 1,origenY,0);
				glVertex3f(nuevoOrigen,origenY + 2,0);
				glVertex3f(nuevoOrigen,origenY + 2,0);
			glEnd();

			//Llamitas amarillas
			glColor3f(0.95,0.61, 0.07);
			glBegin(GL_QUADS);
				glVertex3f(nuevoOrigen,origenY,0);
				glVertex3f(nuevoOrigen + 0.5,origenY,0);
				glVertex3f(nuevoOrigen,origenY + 1,0);
				glVertex3f(nuevoOrigen,origenY + 1,0);
			glEnd();

			//llamitas blancas
			glColor3f(0.8,0.8,0.8);
			glBegin(GL_QUADS);
				glVertex3f(nuevoOrigen,origenY,0);
				glVertex3f(nuevoOrigen + 0.2,origenY,0);
				glVertex3f(nuevoOrigen,origenY + 0.3,0);
				glVertex3f(nuevoOrigen,origenY + 0.3,0);
			glEnd();

			//Llamas invertidas
			float origenInvertido = 5 - i;
			glColor3f(0.92, 0.58, 0.20);
			glBegin(GL_QUADS);
				glVertex3f(origenInvertido,origenY,0);
				glVertex3f(origenInvertido,origenY + 2,0);
				glVertex3f(origenInvertido - 1,origenY,0);
				glVertex3f(origenInvertido - 1,origenY,0);
			glEnd();
		}
		glColor3f(1,1,1);
 }

void dibujaCilindro(float radio, int lados, float altura, int modoRender)
{
	float ang, s1, s2, t1, t2;
	float a[3], b[3], c[3], d[3];
	float delta, deltas;

	CVector normalVert[4];

	delta=360.0f/lados;
	
	for(int i=0; i < lados; i++)
	{
		ang=i*delta;
		
		a[0]=radio*(float)cos(ang*PI/180.0f);
		a[1]=-altura*0.5f;
		a[2]=radio*(float)sin(ang*PI/180.0f);

		b[0]=a[0];
		b[1]=altura*0.5f;
		b[2]=a[2];

		ang=(i+1)*delta;
		
		c[0]=radio*(float)cos(ang*PI/180.0f);
		c[1]=altura*0.5f;
		c[2]=radio*(float)sin(ang*PI/180.0f);

		d[0]=c[0];
		d[1]=-altura*0.5f;
		d[2]=c[2];

		glColor3f(1.0f,0.0f,0.0f);

		//Cálculo de las normales
		normalVert[0]=Normaliza(CVector(a[0], a[1], a[2])-CVector(0.0f, -altura*0.5f, 0.0f));
		normalVert[1]=Normaliza(CVector(b[0], b[1], b[2])-CVector(0.0f,  altura*0.5f, 0.0f));
		normalVert[2]=Normaliza(CVector(c[0], c[1], c[2])-CVector(0.0f,  altura*0.5f, 0.0f));
		normalVert[3]=Normaliza(CVector(d[0], d[1], d[2])-CVector(0.0f, -altura*0.5f, 0.0f));

		if(modoRender == 1) glBegin(GL_QUADS);// sólido
		else if(modoRender == 2) glBegin(GL_LINE_LOOP);// alambrado
			glNormal3f(normalVert[0].x, normalVert[0].y, normalVert[0].z);
			glVertex3f(a[0], a[1], a[2]);
			glNormal3f(normalVert[1].x, normalVert[1].y, normalVert[1].z);
			glVertex3f(b[0], b[1], b[2]);
			glNormal3f(normalVert[2].x, normalVert[2].y, normalVert[2].z);
			glVertex3f(c[0], c[1], c[2]);
			glNormal3f(normalVert[3].x, normalVert[3].y, normalVert[3].z);
			glVertex3f(d[0], d[1], d[2]);
		glEnd();

		//Tapa superior
		glColor3f(1.0f,1.0f,0.0f);

		if(modoRender == 1) glBegin(GL_TRIANGLES);// sólido
		else if(modoRender == 2) glBegin(GL_LINE_LOOP);// alambrado
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(c[0], c[1], c[2]);
			glVertex3f(b[0], b[1], b[2]);
			glVertex3f(0.0f, altura*0.5f, 0.0f);
		glEnd();

		//Tapa inferior
		glColor3f(0.0f,0.0f,1.0f);

		if(modoRender == 1) glBegin(GL_TRIANGLES);// sólido
		else if(modoRender == 2) glBegin(GL_LINE_LOOP);// alambrado
			glNormal3f(0.0f, -1.0f, 0.0f);
			glVertex3f(a[0], a[1], a[2]);
			glVertex3f(d[0], d[1], d[2]);
			glVertex3f(0.0f, -altura*0.5f, 0.0f);
		glEnd();

		glColor3f(1.0f,1.0f,1.0f);
	}
}


/*
void dibujaEsfera(float radio, int paralelos, int meridianos, int modoRender)
{
	float ang1, ang2;
	float a[3], b[3], c[3], d[3];
	float delta1, delta2;
	float color=0.3f;
	int fcolor=1;

	delta1=180.0f/paralelos;
	delta2=360.0f/meridianos;

	//Semiesfera superior (y positivos)
	for(int i=0; i < paralelos/2; i++)
	{
		for(int j=0; j <= meridianos; j++)
		{
			ang1=i*delta1;
			ang2=j*delta2;
			a[0]=radio*(float)cos(ang1*PI/180.0f)*(float)cos(ang2*PI/180.0f);
			a[1]=radio*(float)sin(ang1*PI/180.0f);
			a[2]=radio*(float)cos(ang1*PI/180.0f)*(float)sin(ang2*PI/180.0f);
			
			ang1=(i+1)*delta1;
			ang2=j*delta2;
			b[0]=radio*(float)cos(ang1*PI/180.0f)*(float)cos(ang2*PI/180.0f);
			b[1]=radio*(float)sin(ang1*PI/180.0f);
			b[2]=radio*(float)cos(ang1*PI/180.0f)*(float)sin(ang2*PI/180.0f);
			ang1=(i+1)*delta1;
			ang2=(j+1)*delta2;
			c[0]=radio*(float)cos(ang1*PI/180.0f)*(float)cos(ang2*PI/180.0f);
			c[1]=radio*(float)sin(ang1*PI/180.0f);
			c[2]=radio*(float)cos(ang1*PI/180.0f)*(float)sin(ang2*PI/180.0f);
			ang1=i*delta1;
			ang2=(j+1)*delta2;
			d[0]=radio*(float)cos(ang1*PI/180.0f)*(float)cos(ang2*PI/180.0f);
			d[1]=radio*(float)sin(ang1*PI/180.0f);
			d[2]=radio*(float)cos(ang1*PI/180.0f)*(float)sin(ang2*PI/180.0f);
			
			glColor3f(color, color, color);

			if(fcolor == 1)
			{
				if(color < 0.7f)
					color+=0.1f;
				else
					fcolor=2;
			}
			else if(fcolor == 2)
			{
				if(color > 0.3f)
					color-=0.1f;
				else
					fcolor=1;
			}
			
			if(modoRender == 1) glBegin(GL_QUADS);// sólido
			else if(modoRender == 2) glBegin(GL_LINE_LOOP);// alambrado
				glVertex3f(a[0], a[1], a[2]);
				glVertex3f(b[0], b[1], b[2]);
				glVertex3f(c[0], c[1], c[2]);
				glVertex3f(d[0], d[1], d[2]);
			glEnd();

			if(modoRender == 1) glBegin(GL_QUADS);// sólido
			else if(modoRender == 2) glBegin(GL_LINE_LOOP);// alambrado
				glVertex3f(a[0], -a[1], a[2]);
				glVertex3f(d[0], -d[1], d[2]);
				glVertex3f(c[0], -c[1], c[2]);
				glVertex3f(b[0], -b[1], b[2]);
			glEnd();
			
		}
	}
}*/

void dibujaEsfera(float radio, int paralelos, int meridianos, int modoRender)
{
	float ang1, ang2;
	float a[3], b[3], c[3], d[3];
	float delta1, delta2;
	float color=0.3f;
	int fcolor=1;

	CVector normalVert[4];

	delta1=180.0f/paralelos;
	delta2=360.0f/meridianos;

	//Semiesfera superior (y positivos)
	for(int i=0; i < paralelos/2; i++)
	{
		for(int j=0; j <= meridianos; j++)
		{
			ang1=i*delta1;
			ang2=j*delta2;
			a[0]=radio*(float)cos(ang1*PI/180.0f)*(float)cos(ang2*PI/180.0f);
			a[1]=radio*(float)sin(ang1*PI/180.0f);
			a[2]=radio*(float)cos(ang1*PI/180.0f)*(float)sin(ang2*PI/180.0f);
			
			ang1=(i+1)*delta1;
			ang2=j*delta2;
			b[0]=radio*(float)cos(ang1*PI/180.0f)*(float)cos(ang2*PI/180.0f);
			b[1]=radio*(float)sin(ang1*PI/180.0f);
			b[2]=radio*(float)cos(ang1*PI/180.0f)*(float)sin(ang2*PI/180.0f);
			ang1=(i+1)*delta1;
			ang2=(j+1)*delta2;
			c[0]=radio*(float)cos(ang1*PI/180.0f)*(float)cos(ang2*PI/180.0f);
			c[1]=radio*(float)sin(ang1*PI/180.0f);
			c[2]=radio*(float)cos(ang1*PI/180.0f)*(float)sin(ang2*PI/180.0f);
			ang1=i*delta1;
			ang2=(j+1)*delta2;
			d[0]=radio*(float)cos(ang1*PI/180.0f)*(float)cos(ang2*PI/180.0f);
			d[1]=radio*(float)sin(ang1*PI/180.0f);
			d[2]=radio*(float)cos(ang1*PI/180.0f)*(float)sin(ang2*PI/180.0f);
			
			glColor3f(color, color, color);

			//Cálculo de las normales
			normalVert[0]=Normaliza(CVector(a[0], a[1], a[2]));
			normalVert[1]=Normaliza(CVector(b[0], b[1], b[2]));
			normalVert[2]=Normaliza(CVector(c[0], c[1], c[2]));
			normalVert[3]=Normaliza(CVector(d[0], d[1], d[2]));

			if(fcolor == 1)
			{
				if(color < 0.7f)
					color+=0.1f;
				else
					fcolor=2;
			}
			else if(fcolor == 2)
			{
				if(color > 0.3f)
					color-=0.1f;
				else
					fcolor=1;
			}
			
			if(modoRender == 1) glBegin(GL_QUADS);// sólido
			else if(modoRender == 2) glBegin(GL_LINE_LOOP);// alambrado
				glNormal3f(normalVert[0].x, normalVert[0].y, normalVert[0].z);
				glVertex3f(a[0], a[1], a[2]);
				glNormal3f(normalVert[1].x, normalVert[1].y, normalVert[1].z);
				glVertex3f(b[0], b[1], b[2]);
				glNormal3f(normalVert[2].x, normalVert[2].y, normalVert[2].z);
				glVertex3f(c[0], c[1], c[2]);
				glNormal3f(normalVert[3].x, normalVert[3].y, normalVert[3].z);
				glVertex3f(d[0], d[1], d[2]);
			glEnd();

			if(modoRender == 1) glBegin(GL_QUADS);// sólido
			else if(modoRender == 2) glBegin(GL_LINE_LOOP);// alambrado
				glNormal3f(normalVert[0].x, -normalVert[0].y, normalVert[0].z);
				glVertex3f(a[0], -a[1], a[2]);
				glNormal3f(normalVert[3].x, -normalVert[3].y, normalVert[3].z);
				glVertex3f(d[0], -d[1], d[2]);
				glNormal3f(normalVert[2].x, -normalVert[2].y, normalVert[2].z);
				glVertex3f(c[0], -c[1], c[2]);
				glNormal3f(normalVert[1].x, -normalVert[1].y, normalVert[1].z);
				glVertex3f(b[0], -b[1], b[2]);
			glEnd();
			
		}
	}
}

void dibujaCono(float radio, int lados, float altura, int modoRender)
{
	float ang, s1, s2, t1, t2;
	float a[3], b[3];
	float delta, deltas;
	float color=0.3f;

	CVector normalVert[4];

	delta=360.0f/lados;
	
	for(int i=0; i < lados; i++)
	{
		 
		ang = i*delta;
		a[0] = radio*cosf(ang*PI / 180.0f);
		a[1] = (altura / -2.0f);
		a[2] = radio*sinf(ang*PI / 180.0f);
		ang = (i + 1)*delta;
		b[0] = radio*cosf(ang*PI / 180.0f);
		b[1] = (altura / -2.0f);
		b[2] = radio*sinf(ang*PI / 180.0f);
		glColor3f(color, color, color);

		//Cálculo de las normales
			normalVert[0]=Normaliza(CVector(a[0], a[1], a[2])-CVector(0.0f, -(altura/2.0f), 0.0f));
			normalVert[1]=Normaliza(CVector(b[0], b[1], b[2])-CVector(0.0f,  (altura/2.0f), 0.0f));
			normalVert[2]=Normaliza (CVector(0.0f,  -(altura/2.0f), 0.0f));
			
		if (modoRender == 1) glBegin(GL_TRIANGLES);// sólido
		else if (modoRender == 2) glBegin(GL_LINE_LOOP);// alambrado
			glNormal3f(normalVert[0].x, -normalVert[0].y, normalVert[0].z);
			glVertex3f(b[0], b[1], b[2]);
			glNormal3f(normalVert[1].x, -normalVert[1].y, normalVert[1].z);
			glVertex3f(a[0], a[1], a[2]);
			glNormal3f(normalVert[2].x, -normalVert[2].y, normalVert[2].z);
			glVertex3f(0.0f, (altura / 2.0f), 0.0f);
		glEnd();
	}
		glColor3f(1.0f,1.0f,1.0f);
}


void dibujaTrampa()
{
	int modorender=1;
	SeleccionaMaterial(2);
	dibujaEsfera(1.5f, 10, 10, modorender);
	
	//Cono arriba
	glPushMatrix();
			glTranslatef(0.0f, 2.0f, 0.0f);
			//glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
			dibujaCono(0.4f, 5, 1.5, modorender);
	glPopMatrix();
	
	//Cono Izquierdo
	glPushMatrix();
			glTranslatef(-2.0f, 0.0f, 0.0f);
			glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
			dibujaCono(0.4f, 5, 1.5, modorender);
	glPopMatrix();

	//Cono derecho
	glPushMatrix();
			glTranslatef(2.0f, 0.0f, 0.0f);
			glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
			dibujaCono(0.4f, 5, 1.5, modorender);
	glPopMatrix();

	//Cono abajo
	glPushMatrix();
			glTranslatef(0.0f, -2.0f, 0.0f);
			glRotatef(-180.0f, 0.0f, 0.0f, 1.0f);
			dibujaCono(0.4f, 5, 1.5, modorender);
	glPopMatrix();

	//Conos diagonales en X
	glPushMatrix();
			glTranslatef(1.5f, 1.5f, 0.0f);
			glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
			dibujaCono(0.4f, 5, 1.5, modorender);
	glPopMatrix();

	glPushMatrix();
			glTranslatef(1.5f, -1.5f, 0.0f);
			glRotatef(-135.0f, 0.0f, 0.0f, 1.0f);
			dibujaCono(0.4f, 5, 1.5, modorender);
	glPopMatrix();

	glPushMatrix();
			glTranslatef(-1.5f, 1.5f, 0.0f);
			glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
			dibujaCono(0.4f, 5, 1.5, modorender);
	glPopMatrix();
	
	glPushMatrix();
			glTranslatef(-1.5f, -1.5f, 0.0f);
			glRotatef(135.0f, 0.0f, 0.0f, 1.0f);
			dibujaCono(0.4f, 5, 1.5, modorender);
	glPopMatrix();

	//Cono enfrente
	glPushMatrix();
			glTranslatef(0.0f, 0.0f, 1.5f);
			glRotatef(90, 1, 0, 0);
			dibujaCono(0.4f, 5, 1.5, modorender);
	glPopMatrix();

	//Cono atras
	glPushMatrix();
			glTranslatef(0.0f, 0.0f, -1.5f);
			glRotatef(-90, 1, 0, 0);
			dibujaCono(0.4f, 5, 1.5, modorender);
	glPopMatrix();

	//Conos diagonales en Y
	glPushMatrix();
			glTranslatef(0.0f, 1.5f, 1.5f);
			glRotatef(45, 1, 0, 0);
			dibujaCono(0.4f, 5, 1.5, modorender);
	glPopMatrix();

	glPushMatrix();
			glTranslatef(0.0f, 1.5f, -1.5f);
			glRotatef(-45, 1, 0, 0);
			dibujaCono(0.4f, 5, 1.5, modorender);
	glPopMatrix();

	glPushMatrix();
			glTranslatef(0.0f, -1.5f, 1.5f);
			glRotatef(135, 1, 0, 0);
			dibujaCono(0.4f, 5, 1.5, modorender);
	glPopMatrix();

	glPushMatrix();
			glTranslatef(0.0f, -1.5f, -1.5f);
			glRotatef(-135, 1, 0, 0);
			dibujaCono(0.4f, 5, 1.5, modorender);
	glPopMatrix();
	
	//Conos diagonales en Z
	glPushMatrix();
			glTranslatef(-1.5f, 0.0f, 1.5f);
			glRotatef(-45, 0, 1, 0);
			glRotatef(90, 1, 0, 0);
			dibujaCono(0.4f, 5, 1.5, modorender);
	glPopMatrix();

	glPushMatrix();
			glTranslatef(-1.5f, 0.0f, -1.5f);
			glRotatef(-135, 0, 1, 0);
			glRotatef(90, 1, 0, 0);
			dibujaCono(0.4f, 5, 1.5, modorender);
	glPopMatrix();

	glPushMatrix();
			glTranslatef(1.5f, 0.0f, 1.5f);
			glRotatef(-135, 0, 1, 0);
			glRotatef(-90, 1, 0, 0);
			dibujaCono(0.4f, 5, 1.5, modorender);
	glPopMatrix();

	glPushMatrix();
			glTranslatef(1.5f, 0.0f, -1.5f);
			glRotatef(-45, 0, 1, 0);
			glRotatef(-90, 1, 0, 0);
			dibujaCono(0.4f, 5, 1.5, modorender);
	glPopMatrix();
	SeleccionaMaterial(0);
}

//PROGRAMA 3
void dibujaConodeLuz()
{
	float ang;
	float a[3], b[3];
	float delta;
	float radio=5.0f;
	int lados=8;
	float altura=19.0f;

	delta=360.0f/lados;

	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, textura[26].texID);

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.6f);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.8f, altura,  1.8f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.8f, altura,  1.8f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.8f, altura, -1.8f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.8f, altura, -1.8f);
	glEnd();

	glDisable(GL_ALPHA_TEST);

	glBindTexture(GL_TEXTURE_2D, textura[25].texID);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	
	for(int i=0; i < lados; i++)
	{
		ang=(i+1)*delta;
		
		a[0]=radio*(float)cos(ang*PI/180.0f);
		a[1]=0.0f;
		a[2]=radio*(float)sin(ang*PI/180.0f);

		ang=i*delta;
		
		b[0]=radio*(float)cos(ang*PI/180.0f);
		b[1]=0.0f;
		b[2]=radio*(float)sin(ang*PI/180.0f);

		glBegin(GL_TRIANGLES);
			glTexCoord2f(0.1f, 0.1f); glVertex3f(a[0], a[1], a[2]);
			glTexCoord2f(0.9f, 0.1f); glVertex3f(b[0], b[1], b[2]);
			glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0f, altura, 0.0f);
		glEnd();
	}

	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);

	glDisable(GL_TEXTURE_2D);
}

void dibujaFondo()
{
/*	static int tiempo=0;
	static float escalaBrillo=1.0f;
	static int funcionBrillo=0; //1: aumenta, 2: disminuye, 0: sin cambio

	glEnable(GL_TEXTURE_2D);

	//Primera parte
	glBindTexture(GL_TEXTURE_2D, textura[23].texID);

	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f,  0.0f, -10.0f);
		glTexCoord2f(2.0f, 0.0f); glVertex3f(80.0f,  0.0f, -10.0f);
		glTexCoord2f(2.0f, 2.0f); glVertex3f(80.0f, 71.0f, -10.0f);
		glTexCoord2f(0.0f, 2.0f); glVertex3f( 0.0f, 71.0f, -10.0f);
	glEnd();

	//Segunda parte
	glBindTexture(GL_TEXTURE_2D, textura[21].texID);

	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.4f, 0.0f); glVertex3f( 0.0f,  90.0f, -10.0f);
		glTexCoord2f(1.2f, 0.0f); glVertex3f(35.0f,  90.0f, -10.0f);
		glTexCoord2f(1.2f, 7.0f); glVertex3f(35.0f, 205.0f, -10.0f);
		glTexCoord2f(0.4f, 7.0f); glVertex3f( 0.0f, 205.0f, -10.0f);
	glEnd();

	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(-0.1f, 0.0f); glVertex3f(35.0f,  90.0f, -10.0f);
		glTexCoord2f( 1.0f, 0.0f); glVertex3f(80.0f,  90.0f, -10.0f);
		glTexCoord2f( 1.0f, 7.0f); glVertex3f(80.0f, 205.0f, -10.0f);
		glTexCoord2f(-0.1f, 7.0f); glVertex3f(35.0f, 205.0f, -10.0f);
	glEnd();

	//Columnas

	//1
	//Cara frontal
	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f , 0.0f); glVertex3f(26.0f,  90.0f, -6.0f);
		glTexCoord2f(0.12f, 0.0f); glVertex3f(32.0f,  90.0f, -6.0f);
		glTexCoord2f(0.12f, 7.0f); glVertex3f(32.0f, 205.0f, -6.0f);
		glTexCoord2f(0.0f , 7.0f); glVertex3f(26.0f, 205.0f, -6.0f);
	glEnd();

	//Cara izquierda
	glBegin(GL_QUADS);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.1f, 0.0f); glVertex3f(26.0f,  90.0f, -10.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(26.0f,  90.0f, -6.0f);
		glTexCoord2f(0.0f, 7.0f); glVertex3f(26.0f, 205.0f, -6.0f);
		glTexCoord2f(0.1f, 7.0f); glVertex3f(26.0f, 205.0f, -10.0f);
	glEnd();

	//Cara derecha
	glBegin(GL_QUADS);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.02f, 0.0f); glVertex3f(32.0f,  90.0f, -6.0f);
		glTexCoord2f(0.12f, 0.0f); glVertex3f(32.0f,  90.0f, -10.0f);
		glTexCoord2f(0.12f, 7.0f); glVertex3f(32.0f, 205.0f, -10.0f);
		glTexCoord2f(0.02f, 7.0f); glVertex3f(32.0f, 205.0f, -6.0f);
	glEnd();

	//2
	//Cara frontal
	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f , 0.0f); glVertex3f(39.0f,  90.0f, -6.0f);
		glTexCoord2f(0.12f, 0.0f); glVertex3f(45.0f,  90.0f, -6.0f);
		glTexCoord2f(0.12f, 7.0f); glVertex3f(45.0f, 205.0f, -6.0f);
		glTexCoord2f(0.0f , 7.0f); glVertex3f(39.0f, 205.0f, -6.0f);
	glEnd();

	//Cara izquierda
	glBegin(GL_QUADS);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.1f, 0.0f); glVertex3f(39.0f,  90.0f, -10.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(39.0f,  90.0f, -6.0f);
		glTexCoord2f(0.0f, 7.0f); glVertex3f(39.0f, 205.0f, -6.0f);
		glTexCoord2f(0.1f, 7.0f); glVertex3f(39.0f, 205.0f, -10.0f);
	glEnd();

	//Cara derecha
	glBegin(GL_QUADS);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.02f, 0.0f); glVertex3f(45.0f,  90.0f, -6.0f);
		glTexCoord2f(0.12f, 0.0f); glVertex3f(45.0f,  90.0f, -10.0f);
		glTexCoord2f(0.12f, 7.0f); glVertex3f(45.0f, 205.0f, -10.0f);
		glTexCoord2f(0.02f, 7.0f); glVertex3f(45.0f, 205.0f, -6.0f);
	glEnd();

	//Tercera parte
	glBindTexture(GL_TEXTURE_2D, textura[22].texID);

	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f( 0.0f, 0.0f); glVertex3f(  0.0f, 250.0f, -10.0f);
		glTexCoord2f(10.0f, 0.0f); glVertex3f(410.0f, 250.0f, -10.0f);
		glTexCoord2f(10.0f, 2.0f); glVertex3f(410.0f, 277.0f, -10.0f);
		glTexCoord2f( 0.0f, 2.0f); glVertex3f(  0.0f, 277.0f, -10.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, textura[21].texID);

	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f( 0.0f, 0.0f); glVertex3f(  0.0f, 220.0f, -10.0f);
		glTexCoord2f(10.0f, 0.0f); glVertex3f(410.0f, 220.0f, -10.0f);
		glTexCoord2f(10.0f, 2.0f); glVertex3f(410.0f, 250.0f, -10.0f);
		glTexCoord2f( 0.0f, 2.0f); glVertex3f(  0.0f, 250.0f, -10.0f);
	glEnd();

	//Columnas

	for(int i=0; i<10; i++) //10 columnas
	{
		glPushMatrix();
			glTranslatef(43.2f+(i*41.0f), 0.0f, 0.0f);

			//Cara frontal
			glBegin(GL_QUADS);
				glNormal3f(0.0f, 0.0f, 1.0f);
				glTexCoord2f(0.0f , 0.0f); glVertex3f(-2.5f, 220.0f, -7.0f);
				glTexCoord2f(0.12f, 0.0f); glVertex3f( 2.5f, 220.0f, -7.0f);
				glTexCoord2f(0.12f, 5.0f); glVertex3f( 2.5f, 277.0f, -7.0f);
				glTexCoord2f(0.0f , 5.0f); glVertex3f(-2.5f, 277.0f, -7.0f);
			glEnd();

			//Cara izquierda
			glBegin(GL_QUADS);
				glNormal3f(-1.0f, 0.0f, 0.0f);
				glTexCoord2f(0.1f, 0.0f); glVertex3f(-2.5f, 220.0f, -10.0f);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.5f, 220.0f, -7.0f);
				glTexCoord2f(0.0f, 5.0f); glVertex3f(-2.5f, 277.0f, -7.0f);
				glTexCoord2f(0.1f, 5.0f); glVertex3f(-2.5f, 277.0f, -10.0f);
			glEnd();

			//Cara derecha
			glBegin(GL_QUADS);
				glNormal3f(1.0f, 0.0f, 0.0f);
				glTexCoord2f(0.02f, 0.0f); glVertex3f(2.5f, 220.0f, -7.0f);
				glTexCoord2f(0.12f, 0.0f); glVertex3f(2.5f, 220.0f, -10.0f);
				glTexCoord2f(0.12f, 5.0f); glVertex3f(2.5f, 277.0f, -10.0f);
				glTexCoord2f(0.02f, 5.0f); glVertex3f(2.5f, 277.0f, -7.0f);
			glEnd();

		glPopMatrix();
	}

	glDisable(GL_TEXTURE_2D);

	glDisable(GL_LIGHTING);

	glColor3f(0.0f, 0.0f, 0.0f);

	glBegin(GL_QUADS);
		glVertex3f( 0.0f, 71.0f, -10.0f);
		glVertex3f(80.0f, 71.0f, -10.0f);
		glVertex3f(80.0f, 90.0f, -10.0f);
		glVertex3f( 0.0f, 90.0f, -10.0f);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(  0.0f, 195.0f, -5.0f);
		glVertex3f(410.0f, 195.0f, -5.0f);
		glVertex3f(410.0f, 225.0f, -5.0f);
		glVertex3f(  0.0f, 225.0f, -5.0f);
	glEnd();

	glBegin(GL_QUADS);
		glVertex3f(  0.0f, 275.0f, -5.0f);
		glVertex3f(410.0f, 275.0f, -5.0f);
		glVertex3f(410.0f, 283.0f, -5.0f);
		glVertex3f(  0.0f, 283.0f, -5.0f);
	glEnd();

	//Luces

	//De la primera parte del escenario
	if(tiempo < 60)
	{
		for(int i=0; i<3; i++) //4 columnas de luces
			for(int j=0; j<2; j++) //2 luces por columna
			{
				glPushMatrix();
					glTranslatef(22.5f+(i*19.9f), 20.7f+(j*35.5f), -9.9f);

					glColor3f(0.74f, 0.0f, 0.74f);

					glBegin(GL_QUADS);
						glVertex3f(-1.3f, -0.4f, 0.0f);
						glVertex3f( 1.3f, -0.4f, 0.0f);
						glVertex3f( 1.3f,  0.4f, 0.0f);
						glVertex3f(-1.3f,  0.4f, 0.0f);
					glEnd();

					glColor3f(1.0f, 1.0f, 1.0f);

					glEnable(GL_TEXTURE_2D);

					glBindTexture(GL_TEXTURE_2D, textura[24].texID);

					glEnable(GL_BLEND);
					glBlendFunc(GL_ONE, GL_ONE);

					glPushMatrix();
						glScalef(escalaBrillo, escalaBrillo, escalaBrillo);

						glBegin(GL_QUADS);
							glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.5f, -4.5f, 0.1f);
							glTexCoord2f(1.0f, 0.0f); glVertex3f( 5.5f, -4.5f, 0.1f);
							glTexCoord2f(1.0f, 1.0f); glVertex3f( 5.5f,  4.5f, 0.1f);
							glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.5f,  4.5f, 0.1f);
						glEnd();
					glPopMatrix();

					glDisable(GL_BLEND);

					glDisable(GL_TEXTURE_2D);

				glPopMatrix();
			}

	}

	//De la segunda parte del escenario
	if(tiempo < 60)
	{
		for(int k=0; k<10; k++)
			for(int i=0; i<3; i++) //3 columnas de luces
				for(int j=0; j<2; j++) //2 luces por columna
				{
					glPushMatrix();
						glTranslatef(18.0f+(i*10.2f)+k*41.0f, 253.5f+(j*13.0f), -9.9f);

						glColor3f(0.74f, 0.0f, 0.74f);

						glBegin(GL_QUADS);
							glVertex3f(-1.3f, -0.4f, 0.0f);
							glVertex3f( 1.3f, -0.4f, 0.0f);
							glVertex3f( 1.3f,  0.4f, 0.0f);
							glVertex3f(-1.3f,  0.4f, 0.0f);
						glEnd();

						glColor3f(1.0f, 1.0f, 1.0f);

						glEnable(GL_TEXTURE_2D);

						glBindTexture(GL_TEXTURE_2D, textura[24].texID);

						glEnable(GL_BLEND);
						glBlendFunc(GL_ONE, GL_ONE);

						glPushMatrix();
							glScalef(escalaBrillo, escalaBrillo, escalaBrillo);

							glBegin(GL_QUADS);
								glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.5f, -4.5f, 0.1f);
								glTexCoord2f(1.0f, 0.0f); glVertex3f( 5.5f, -4.5f, 0.1f);
								glTexCoord2f(1.0f, 1.0f); glVertex3f( 5.5f,  4.5f, 0.1f);
								glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.5f,  4.5f, 0.1f);
							glEnd();
						glPopMatrix();

						glDisable(GL_BLEND);

						glDisable(GL_TEXTURE_2D);

					glPopMatrix();
				}

	}

	glColor3f(1.0f, 1.0f, 1.0f);

	glEnable(GL_LIGHTING);

	if(tiempo < 100) //Si el tiempo es menor que 60 se dibuja la luz, entre 60 y 100 se apaga
		tiempo++;
	else
		tiempo=0;

	if(tiempo > 40 && tiempo <= 50)
		funcionBrillo=1; //En este intervalo el brillo aumenta
	else if(tiempo > 50 && tiempo <= 60)
		funcionBrillo=2; //En este intervalo el brillo disminuye
	else
		funcionBrillo=0;

	if(funcionBrillo == 0)
		escalaBrillo=1.0f;
	else if(funcionBrillo == 1)
	{
		if(escalaBrillo < 2.5f)
			escalaBrillo+=0.1f;
	}
	else if(funcionBrillo == 2)
	{
		if(escalaBrillo > 1.2f)
			escalaBrillo-=0.1f;
	}

	*/
	
}

void bloque(float x, float y, float z, float margen, int tipo)
{

	//glColor3f(1.0,0.0,0.0);
	/*------------------------------------------------- BORDES FRONTAL-----------------------------------------------------*/
	margen = margen / 2.95;
	x *= 10;
	y *= 10;
	z *= 10;
	glPushMatrix();
		if (tipo == 1){}
		else if (tipo == 2){
			glScalef(2.0, 2.0, 1.0);
			x /= 2;
			y /= 2;
		}
		else if (tipo == 3){
			glScalef(2.0, 1.0, 1.0);
			x /= 2;
		}
		else if (tipo == 4){
			glScalef(1.0, 2.0, 1.0);
			y /= 2;
		}
		vec1 = CVector(10.0f - margen, 10.0f - margen,  + margen) - CVector(0.0f + margen, 10.0f - margen,  + margen);
		vec2 = CVector(10.0f, 10.0f, 0) - CVector(0.0f + margen, 10.0f - margen, 0);
		N = Normaliza(Cruz(vec1, vec2));
		
		glBegin(GL_QUADS);
			glNormal3f(N.x, N.y, N.z);
			glVertex3f(0.0f+margen+x, 10.0f-margen+y,  + margen+z);
			glVertex3f(10.0f - margen+x, 10.0f - margen+y,  + margen+z);
			glVertex3f(10.0f+x, 10.0f+y, +z);									 //BORDECITO SUPERIOR
			glVertex3f(0.0f+x, 10.0f+y, +z);
		glEnd();
		
	
		vec1 = CVector(0.0f + margen, 10.0f - margen,  + margen) - CVector(0.0f, 10.0f, 0);
		vec2 = CVector(0.0f + margen, 0.0f + margen,  + margen) - CVector(0.0f, 0.0f, 0 );
		N = Normaliza(Cruz(vec1, vec2));
	
		glBegin(GL_QUADS);
			glNormal3f(N.x, N.y, N.z);
			glVertex3f(0.0f + margen+x, 10.0f - margen+y,  + margen+z);
			glVertex3f(0.0f+x, 10.0f+y, +z);									//BORDECITO LATERAL IZQUIERDO
			glVertex3f(0.0f+x, 0.0f+y, +z);
			glVertex3f(0.0f + margen+x, 0.0f+margen +y,  + margen+z);
		glEnd();

		vec1 = CVector(10.0f, 0.0f, 0) - CVector(10.0f - margen, 0.0f + margen,  + margen);
		vec2 = CVector(10.0f, 10.0f, 0) - CVector(10.0f - margen, 0.0f + margen,  + margen);
		N = Normaliza(Cruz(vec1, vec2));
		//funcion para rellenar los bordes
		/*
		glBegin(GL_QUADS);
			glNormal3f(N.x, N.y, N.z);
			glVertex3f(10.0f - margen+x, 10.0f - margen+y,  + margen);
			glVertex3f(10.0f - margen+x, 0.0f + margen+y,  + margen);         //BORDECITO LATERAL DERECHO
			glVertex3f(10.0f+x, 0.0f+y, +z);
			glVertex3f(10.0f+x, 10.0f+y, +z);
		glEnd();
		
		/*
		glBegin(GL_QUADS);
			glNormal3f(N.x, N.y, N.z);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);         
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
		glEnd();
		*/
		vec1 = CVector(0.0f, 0.0f, 0) - CVector(0.0f + margen, 0.0f + margen,  + margen);
		vec2 = CVector(10.0f, 0.0f, 0) - CVector(10.0f + margen, 0.0f + margen,  + margen);
		N = Normaliza(Cruz(vec1, vec2));

		glBegin(GL_QUADS);
			glNormal3f(N.x, N.y, N.z);
			glVertex3f(0.0f+x, 0.0f+y, +z);
			glVertex3f(10.0f+x, 0.0f+y, +z);									//BORDECITO INFERIOR
			glVertex3f(10.0f - margen+x, 0.0f + margen+y,  + margen+z);
			glVertex3f(0.0f + margen+x, 0.0f + margen+y,  + margen+z);
		glEnd();
		/*--------------------------------------------------------------------------------------------------------------*/

		/*--------------------------------------------------FRONTAL-----------------------------------------------------*/
	
		glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3f(0.0f+margen+x, 10.0f-margen+y, margen+z);
			glVertex3f(0.0f+margen+x, 0.0f+margen+y, margen+z);									//BORDECITO INFERIOR
			glVertex3f(10.0f - margen +x, 0.0f + margen+y,  margen+z);
			glVertex3f(10.0f - margen +x, 10.0f - margen+y,  margen+z);
		glEnd();


		/*vec1 = CVector(px+x, py+y, pz+z) - CVector(0.0f + margen, 10.0f - margen,  + margen);
		vec2 = CVector(10.0f - margen, 10.0f - margen,  + margen) - CVector(px+x, py+y, pz+z);
		N = Normaliza(Cruz(vec1, vec2));

		glBegin(GL_TRIANGLES);
			glNormal3f(N.x, N.y, N.z);
			glVertex3f(0.0f+margen+x, 10.0f-margen+y, +margen+z);	  //TRIÁNGULO SUPERIOR
			glVertex3f(px+x, py+y, pz+z);
			glVertex3f(10.0f-margen+x, 10.0f-margen+y, +margen+z);
		glEnd();

		vec1 = CVector(px + x, py + y, pz + z) - CVector(0.0f + margen, 0.0f + margen,  + margen);
		vec2 = CVector(0.0f + margen, 10.0f - margen,  + margen) - CVector(px + x, py + y, pz + z);
		N = Normaliza(Cruz(vec1, vec2));

		glBegin(GL_TRIANGLES);
			glNormal3f(N.x, N.y, N.z);
			glVertex3f(0.0f+margen+x, 0.0f+margen+y, +margen+z);	  //TRIÁNGULO IZQUIERDO
			glVertex3f(px+x, py+y, pz+z);
			glVertex3f(0.0f+margen+x, 10.0f-margen+y, +margen+z);
		glEnd();
	
		vec1 = CVector(10.0f - margen + x, 10.0f - margen + y,  + margen + z) - CVector(10.0f - margen + x, 0.0f + margen + y,  + margen + z);
		vec2 = CVector(px + x, py + y,  pz + z) - CVector(10.0f - margen + x, 0.0f + margen + y,  + margen + z);
		N = Normaliza(Cruz(vec1, vec2));

		glBegin(GL_TRIANGLES);
			glNormal3f(-N.x, N.y, N.z);
			glVertex3f(10.0f-margen+x, 0.0f+margen+y, +margen+z);	  //TRIÁNGULO DERECHO
			glVertex3f(10.0f-margen+x, 10.0f-margen+y, +margen+z);
			glVertex3f(px + x, py + y,  pz + z);
		glEnd();

		vec1 = CVector(10.0f - margen + x, 0.0f + margen + y,  + margen + z) - CVector(0.0f + margen + x, 0.0f + margen + y,  + margen + z);
		vec2 = CVector(px + x, py + y,  pz + z) - CVector(0.0f + margen + x, 0.0f + margen + y,  + margen + z);
		N = Normaliza(Cruz(vec1, vec2));

		glBegin(GL_TRIANGLES);
			glNormal3f(-N.x, -N.y, -N.z);
			glVertex3f(0.0f+margen+x, 0.0f+margen+y, +margen+z);	  //TRIÁNGULO INFERIOR
			glVertex3f(10.0f-margen+x, 0.0f+margen+y, +margen+z);
			glVertex3f(px + x, py + y,  pz + z);
		glEnd();
		/*--------------------------------------------------------------------------------------------------------------*/
		//glColor3
		glBegin(GL_QUADS);
			glNormal3f(1.0f, 0.0f, 0.0f);
			glVertex3f(10.0f+x, 0.0f+y, +z);
			glVertex3f(10.0f+x, 0.0f+y, -10.0f+z);		 //CARA DERECHA
			glVertex3f(10.0f+x, 10.0f+y, -10.0f+z);
			glVertex3f(10.0f+x, 10.0f+y, +z);
		glEnd();
	
		glBegin(GL_QUADS);
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(0.0f+x, 10.0f+y, +z);
			glVertex3f(0.0f+x, 10.0f+y, -10.0f+z);		 //CARA IZQUIERDA
			glVertex3f(0.0f+x, 0.0f+y, -10.0f+z);
			glVertex3f(0.0f+x, 0.0f+y, +z);
		glEnd();
	
		glBegin(GL_QUADS);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(10.0f+x, 10.0f+y, +z);
			glVertex3f(10.0f+x, 10.0f+y, -10.0f+z);
			glVertex3f(0.0f+x, 10.0f+y, -10.0f+z);		 //CARA SUPERIOR
			glVertex3f(0.0f+x, 10.0f+y, +z);
		glEnd();

		glBegin(GL_QUADS);
			glNormal3f(0.0f, -1.0f, 0.0f);
			glVertex3f(0.0f+x, 0.0f+y, +z);
			glVertex3f(0.0f+x, 0.0f+y, -10.0f+z);	     // CARA INFERIOR
			glVertex3f(10.0f+x, 0.0f+y, -10.0f+z);
			glVertex3f(10.0f+x, 0.0f+y, +z);
		glEnd();
	glPopMatrix();

	//dibujaTexturaBloque();
}


void dibujaVertex(int largo, int alto, int profundidad){
	glPushMatrix();
	glColor3f(0.6,0.7,0.8);
	glBegin(GL_POLYGON);
	glVertex3f(0,0,profundidad);
	glVertex3f(largo,0,profundidad);
	glVertex3f(largo,alto,profundidad);
	glVertex3f(0,alto,profundidad);
	glPopMatrix();
}

void dibujaTexturaBloque (int large, int hide, int prof){

	glPushMatrix();	
	glColor3f(0.3,0.3,0.3);
	dibujaVertex(large,hide,prof);
	glPopMatrix();

}
void estructura(int tipo, int px, int py, int pz){
	int i;
	if (tipo == 1){
		bloque(px, py, pz, 1.2, 4);
		bloque(px+1, py+1, pz, 0.8, 1);
		bloque(px + 1, py, pz, 1.8, 3);
		bloque(px + 2, py + 1, pz, 1.0, 3);
		bloque(px + 3, py, pz, 1.5,  1);
	}

	else if (tipo == 2){
		bloque(px, py, pz, 1.2, 1);
		bloque(px + 1, py, pz, 0.8, 1);
		bloque(px, py + 1, pz, 0.8, 2);
	}

	else if (tipo == 3){
		bloque(px, py, pz, 1.2, 1);
		bloque(px+1, py, pz, 0.7, 3);
		bloque(px+3, py, pz, 1, 4);
		bloque(px, py+1, pz, 0.6, 3);
		bloque(px+2, py+1, pz, 1, 1);
		for (i = 0; i < 4; i++){
			bloque(px+i, py + 2, pz, 1.3, 1);
		}
		bloque(px, py+3, pz, 1.2, 3);
		bloque(px+2, py+3, pz, 1, 1);
		bloque(px+3, py+3, pz, 1.4, 1);
		bloque(px, py+4, pz, 1.2, 4);
		bloque(px+1, py+4, pz, 1.2, 4);
		bloque(px+2, py+4, pz, 0.7, 3);
		bloque(px+2, py+5, pz, 1, 1);
		bloque(px+3, py+5, pz, 1.3, 1);
		bloque(px, py+6, pz, 1.8, 2);
		bloque(px+2, py + 6, pz, 1.3, 2);
	}

	else if (tipo == 4){
		bloque(px, py, pz, 1.5, 2);
		bloque(px, py + 2, pz, 1, 3);
		bloque(px, py + 3, pz, 1, 1);
		bloque(px + 1, py + 3, pz, 1, 1);
		bloque(px, py + 4, pz, 0.5, 4);
		bloque(px, py + 6, pz, 1.4, 4);
		for (i = 0; i < 5; i++){
			bloque(px + 1, py + 3 + i, pz, 1.4, 1);
		}
		for (i = 0; i < 8; i++){
			bloque(px + 2, py + i, pz, 1.1, 1);
		}
	}

}
void dibujaEscenario()
{
//<<<<<<< HEAD
	int i,j; // Contadores para creación de fondos

	//***********************************************ESCENARIO PARTE 1*********************************************************
	bloque(0, 0, 0, 1, 1);
	bloque(1, 0, 0, 1, 1);
	bloque(2, -1, 0, 1, 1);
	bloque(3, -1, 0, 1, 1);
	bloque(2, 0, 0, 0.5, 3);
	bloque(0, 3, 0, 0.5, 2);
	bloque(2, 3, 0, 0.5, 1);
	bloque(2, 4, 0, 0.5, 1);
	bloque(3, 3, 0, 0.5, 2);
	bloque(4, -1, 0, 0.6, 4);
	bloque(0, -2, 0, 0.9, 2);
	bloque(2, -2, 0, 1, 3);
	bloque(4, -2, 0, 0.5, 1);

	bloque(9, 1, 0, 0.5, 1);  // Bloque solito

	for (i = 0; i < 2; i++){
		estructura(1, 14+4*i, 4, 0);
	}

	for (i = 0; i < 14; i++){
			bloque(i * 1, 5, 0, 1, 1);
	}

	bloque(14, 3, 0, 0.6, 1);
	bloque(14, 2, 0, 0.9, 1);
	bloque(14, 1, 0, 1, 1);
	bloque(15, 2, 0, 1.9, 2);
	bloque(15, 1, 0, 1.3, 3);
	bloque(17, 1, 0, 1.3, 3);

	for (i = 1; i < 15; i++){
		bloque(i * 2 - 7, 2, -7.7, 1, 2);
	}
	bloque(22, 4, 0, 1.6, 2);
	
	for (i = 0; i < 4; i++){                  //
		bloque(i * 3 + 5, -2, 0, 0.8, 1);     //
		bloque(i * 3 + 6, -2, 0, 2, 3);	      //
	}										  // Primera división
	bloque(17, -2, 0, 2, 1);				  //
	estructura(1, 18, -3, 0);				  //



	//********************************************ESCENARIO PARTE 2*********************************************************

	estructura(2, 6, -5, 0);
	estructura(2, 16, -5, 0);

	for (i = 1; i < 4; i++){
		bloque(i * 2 - 7, 2, -7.7, 1, 2);
	}

	for (i = 0; i < 4; i++){                  //
		estructura(1, 5 + i * 4, -11, 0);	  //
	}										  // Segunda división
	bloque(21, -11, 0, 3, 2);
	bloque(23, -10, 0, 1, 1);
	bloque(23, -11, 0, 1.4, 1);
	//*********************************FONDO ESCENARIO PRIMERA PARTE***********************************
	for (i = 1; i < 30; i++){
		for (j = 1; j < 30; j++){
			bloque(i * 1 - 6, j * 1 - 10, -8, 1, 1);
		}
	}

	//**************************************MUROS LATERALES*********************************************

	estructura(3, 24, -2, 0);
	estructura(3, 24, -10, 0);
	estructura(3, 24, -18, 0);    //Derechos parte 1,2,3
	bloque(23, -19, 0, 0.4, 1);
	bloque(24, -19, 0, 1.4, 3);
	bloque(26, -19, 0, 0.8, 3);

	estructura(4, 0, -10, 0);	 //Izquierdos

	//FONDO PARTE 1
	/*/
	bloque(0, 0, 0, 1, 1);
	bloque(20, -10, 0, 1, 1);
	bloque(30, -10, 0, 1, 1);
	bloque(20, 0, 0, 0.5, 3);
	bloque(0, 30, 0, 0.5, 2);
	bloque(20, 30, 0, 0.5, 1);
	bloque(20, 40, 0, 0.5, 1);
	bloque(30, 30, 0, 0.5, 2);
	bloque(40, -10, 0, 0.6, 4);
	*/
}	
	

	//**************************************************************************************************
	//PARTE 1
	//bloque(0, 0, 0, 3, 4, 4);
	//bloque(0, 0, 0, 3, 1, 4);
	//dibujaFondo();
/*	glEnable(GL_TEXTURE_2D);
	//Bloque 1

	glBindTexture(GL_TEXTURE_2D, textura[0].texID);

	//Cara frontal
	glColor3f(0.6f, 0.6f, 0.8f);

	glBegin(GL_QUADS);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f,  0.0f, 5.0f);
		glTexCoord2f(2.0f, 0.0f); glVertex3f(60.0f,  0.0f, 5.0f);
		glTexCoord2f(2.0f, 1.0f); glVertex3f(60.0f, 12.5f, 5.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f, 12.5f, 5.0f);
	glEnd();
=======
}

//PROGRAMA 2
void DibujaPersonaje()
{
		glPushMatrix();
>>>>>>> origin/master

				glTranslatef(Xtor, Ytor, Ztor);
				glRotatef(Angt2, 0.0f, 1.0f, 0.0f);
				glRotatef(Angt1, 1.0f, 0.0f, 0.0f);

				//Torso
				g_Load3ds.Render3DSFile(&g_3DModel1c, textureModel1c, 1);

				//Cabeza
				glPushMatrix();
						glTranslatef(0.0f, 1.9f, 0.0f);
						glRotatef(Angc1, 1.0f, 0.0f, 0.0f);
						glRotatef(Angc2, 0.0f, 1.0f, 0.0f);
						g_Load3ds.Render3DSFile(&g_3DModel2c, textureModel2c, 1);
				glPopMatrix();

				//Pierna derecha
				glPushMatrix();
						glTranslatef(-0.6f, 0.1f, 0.0f);
						glRotatef(Angpder1, 1.0f, 0.0f, 0.0f);
						glRotatef(Angpder2, 0.0f, 0.0f, 1.0f);
						g_Load3ds.Render3DSFile(&g_3DModel3c, textureModel3c, 1);
	
					//Pie derecho
						glPushMatrix();
								glTranslatef(0.0f, -0.5f, 0.1f);
								glRotatef(Angpd, 1.0f, 0.0f, 0.0f);
								glRotatef(Angpd, 0.0f, 0.0f, 1.0f);
								g_Load3ds.Render3DSFile(&g_3DModel9c, textureModel9c, 1);
						glPopMatrix();
				glPopMatrix();

				//Pierna izquierda
				glPushMatrix();
						glTranslatef(0.6f, 0.1f, 0.1f);
						glRotatef(Angpizq1, 1.0f, 0.0f, 0.0f);
						glRotatef(Angpizq2, 0.0f, 0.0f, 1.0f);
						g_Load3ds.Render3DSFile(&g_3DModel4c, textureModel4c, 1);
	
					//Pie izquierdo
						glPushMatrix();
								glTranslatef(0.0f, -0.5f, 0.1f);
								glRotatef(Angpi, 1.0f, 0.0f, 0.0f);
								glRotatef(Angpi, 0.0f, 0.0f, 1.0f);
								g_Load3ds.Render3DSFile(&g_3DModel9c, textureModel9c, 1);
						glPopMatrix();
				glPopMatrix();
	
				//Brazo derecho
				glPushMatrix();
						glTranslatef(-1.0f, 1.6f, 0.0f);
						glRotatef(Angbd1, 1.0f, 0.0f, 0.0f);
						glRotatef(Angbd2, 0.0f, 0.0f, 1.0f);
						g_Load3ds.Render3DSFile(&g_3DModel5c, textureModel5c, 1);

						glPushMatrix();
								glTranslatef(-0.4f, -0.65f, 0.0f);
								glRotatef(Angbdb, 1.0f, 0.0f, 0.0f);
								g_Load3ds.Render3DSFile(&g_3DModel6c, textureModel6c, 1);
						glPopMatrix();
	
				glPopMatrix();

				//Brazo izquierdo
				glPushMatrix();
						glTranslatef(1.0f, 1.6f, 0.0f);
						glRotatef(Angbi1, 1.0f, 0.0f, 0.0f);
						glRotatef(Angbi2, 0.0f, 0.0f, 1.0f);
						g_Load3ds.Render3DSFile(&g_3DModel7c, textureModel7c, 1);

						glPushMatrix();
								glTranslatef(0.4f, -0.8f, 0.0f);
								glRotatef(Angbib, 1.0f, 0.0f, 0.0f);
								g_Load3ds.Render3DSFile(&g_3DModel8c, textureModel8c, 1);
						glPopMatrix();
						
				glPopMatrix();
				
		glPopMatrix();
}

*/
//PROGRAMA 2
void actualizaLuzParam()
{
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);		// Posicion de la luz0
	glLightfv(GL_LIGHT0, GL_AMBIENT,  LightAmb);		// Componente ambiente
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  LightDif);		// Componente difusa
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpc);		// Componente especular
}

int RenderizaEscena(GLvoid)								// Aqui se dibuja todo lo que aparecera en la ventana
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//CAMBIO PARA PROGRAMA 1
	//gluLookAt(80.0f, 120.0f, 170.0f, 0.0f, 0.0f, 0.0f, 0, 1, 0);
	//gluLookAt(camara.x+10, camara.y+10, camara.z, camara.x+10, camara.y+10, 0.0f, 0, 1, 0);
	gluLookAt(player1.PosicionObj.x+110, player1.PosicionObj.y - 5.7f+20, camara.z, player1.PosicionObj.x+110, player1.PosicionObj.y - 5.7f+20, 0.0f, 0, 1, 0);
	actualizaLuzParam();
//<<<<<<< HEAD
	//DibujaEjes();
//=======
	DibujaEjes();

//>>>>>>> origin/master
	//bloque(10, 0, 0, 3, 2, 4);

	dibujaEscenario();
	//dibujaTexturaBloque(10,10,30);
		//dibujaTexturaBloque ();
	
    //glTranslatef(12.0f+cx, 14.5f, 0.0f);

	//DibujaPersonaje();
	//dibujaPlataforma();
	//dibujaEscaleras();
	//dibujaTrampa();

	//while (feof(archivo)){

	//PROGRAMA 2
	if(player1.visible == true)
	{
		glEnable(GL_NORMALIZE);
		glTranslatef(110.0f, 20.0f, 0.0f);
		glPushMatrix();
			glTranslatef(player1.PosicionObj.x, player1.PosicionObj.y-5.7f, player1.PosicionObj.z);
			glRotatef(player1.AngObj, 0.0f, 1.0f, 0.0f);
			glScalef(player1.escalaX,player1.escalaY,player1.escalaZ);
			//DibujaPersonaje();
		glPopMatrix();

		glDisable(GL_NORMALIZE);
	}
	return TRUE;
}

GLvoid DestruyeVentanaOGL(GLvoid)						// Elimina la ventana apropiadamente
{
	if (hRC)											// Si existe un contexto de renderizado...
	{
		if (!wglMakeCurrent(NULL,NULL))					// Si no se pueden liberar los contextos DC y RC...
		{
			MessageBox(NULL,"Falla al liberar DC y RC.","Error de finalización",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Si no se puede eliminar el RC?
		{
			MessageBox(NULL,"Falla al liberar el contexto de renderizado.","Error de finalización",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Se pone RC en NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Si no se puede eliminar el DC
	{
		MessageBox(NULL,"Falla al liberar el contexto de renderizado.","Error de finalización",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Se pone DC en NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Si no se puede destruir la ventana
	{
		MessageBox(NULL,"No se pudo liberar hWnd.","Error de finalización",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Se pone hWnd en NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Si no se puede eliminar el registro de la clase
	{
		MessageBox(NULL,"No se pudo eliminar el registro de la clase.","Error de finalización",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Se pone hInstance en NULL
	}
}

//	Este código crea la ventana de OpenGL.  Parámetros:					
//	title			- Titulo en la parte superior de la ventana			
//	width			- Ancho de la ventana								
//	height			- Alto de la ventana								
//	bits			- Número de bits a usar para el color (8/16/24/32)	
  
BOOL CreaVentanaOGL(char* title, int width, int height, int bits)
{
	GLuint	PixelFormat;				// Guarda el resultado despues de determinar el formato a usar
	WNDCLASS	wc;						// Estructura de la clase ventana
	DWORD		dwExStyle;				// Estilo extendido de ventana
	DWORD		dwStyle;				// Estilo de ventana
	RECT		WindowRect;				// Guarda los valores Superior Izquierdo / Inferior Derecho del rectángulo
	WindowRect.left=(long)0;			// Inicia el valor Izquierdo a 0
	WindowRect.right=(long)width;		// Inicia el valor Derecho al ancho especificado
	WindowRect.top=(long)0;				// Inicia el valor Superior a 0
	WindowRect.bottom=(long)height;		// Inicia el valor Inferior al alto especificado

	hInstance			= GetModuleHandle(NULL);				// Guarda una instancia de la ventana
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redibuja el contenido de la ventana al redimensionarla
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// Maneja los mensajes para WndProc
	wc.cbClsExtra		= 0;									// Ningun dato extra para la clase
	wc.cbWndExtra		= 0;									// Ningun dato extra para la ventana
	wc.hInstance		= hInstance;							// Inicia la instancia
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Carga el ícono por defecto
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Carga el puntero de flecha
	wc.hbrBackground	= NULL;									// No se requiere ningun fondo
	wc.lpszMenuName		= NULL;									// No hay menú en la ventana
	wc.lpszClassName	= "OpenGL";								// Fija el nombre de la clase.

	if (!RegisterClass(&wc))									// Intenta registrar la clase de ventana
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											
	}
		
	dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;					// Estilo extendido de ventana
	dwStyle=WS_OVERLAPPEDWINDOW;									// Estilo de ventana

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Ajusta la ventana al tamaño especificado

	// Crea la ventana
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Estilo extendido para la ventana
								"OpenGL",							// Nombre de la clase
								title,								// Título de la ventana
								dwStyle |							// Definición del estilo de la ventana
								WS_CLIPSIBLINGS |					// Estilo requerido de la ventana
								WS_CLIPCHILDREN,					// Estilo requerido de la ventana
								0, 0,								// Posición de la ventana
								WindowRect.right-WindowRect.left,	// Calcula el ancho de la ventana
								WindowRect.bottom-WindowRect.top,	// Calcula el alto de la ventana
								NULL,								// No hay ventana superior
								NULL,								// No hay menú
								hInstance,							// Instancia
								NULL)))								// No se pasa nada a WM_CREATE
	{
		DestruyeVentanaOGL();										// Resetea el despliegue
		MessageBox(NULL,"Error al crear la ventana.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Si no se creo el contexto de dispositivo...
	{
		DestruyeVentanaOGL();						// Resetea el despliegue
		MessageBox(NULL,"No se puede crear un contexto de dispositivo GL.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Si Windows no encontró un formato de pixel compatible
	{
		DestruyeVentanaOGL();						// Resetea el despliegue
		MessageBox(NULL,"No se puede encontrar un formato de pixel compatible.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Si no se pudo habilitar el formato de pixel
	{
		DestruyeVentanaOGL();						// Resetea el despliegue
		MessageBox(NULL,"No se puede usar el formato de pixel.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	if (!(hRC=wglCreateContext(hDC)))				// Si no se creo el contexto de renderizado
	{
		DestruyeVentanaOGL();						// Resetea el despliegue
		MessageBox(NULL,"No se puede crear un contexto de renderizado GL.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	if(!wglMakeCurrent(hDC,hRC))					// Si no se puede activar el contexto de renderizado
	{
		DestruyeVentanaOGL();						// Resetea el despliegue
		MessageBox(NULL,"No se puede usar el contexto de renderizado GL.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	ShowWindow(hWnd,SW_SHOW);				// Muestra la ventana
	SetForegroundWindow(hWnd);				// Le da la prioridad mas alta
	SetFocus(hWnd);							// Pasa el foco del teclado a la ventana
	ReDimensionaEscenaGL(width, height);	// Inicia la perspectiva para la ventana OGL

	if (!IniGL())							// Si no se inicializa la ventana creada
	{
		DestruyeVentanaOGL();				// Resetea el despliegue
		MessageBox(NULL,"Falla en la inicialización.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								
	}

	return TRUE;							// Todo correcto
}

LRESULT CALLBACK WndProc(	HWND	hWnd,	// Manejador para esta ventana
							UINT	uMsg,	// Mensaje para esta ventana
							WPARAM	wParam,	// Información adicional del mensaje
							LPARAM	lParam)	// Información adicional del mensaje
{
	switch (uMsg)							// Revisa los mensajes de la ventana
	{
		case WM_ACTIVATE:					// Revisa el mensaje de activación de ventana
		{
			if (!HIWORD(wParam))			// Revisa el estado de minimización
			{
				active=TRUE;				// El programa está activo
			}
			else
			{
				active=FALSE;				// El programa no está activo
			}

			return 0;						// Regresa al ciclo de mensajes
		}

		case WM_SYSCOMMAND:					// Intercepta comandos del sistema
		{
			switch (wParam)					// Revisa llamadas del sistema
			{
				case SC_SCREENSAVE:			// ¿Screensaver tratando de iniciar?
				case SC_MONITORPOWER:		// ¿Monitor tratando de entrar a modo de ahorro de energía?
				return 0;					// Evita que suceda
			}
			break;							// Sale del caso
		}

		case WM_CLOSE:						// Si se recibe un mensaje de cerrar...
		{
			PostQuitMessage(0);				// Se manda el mensaje de salida
			return 0;						// y se regresa al ciclo
		}

		case WM_KEYDOWN:					// Si se está presionando una tecla...
		{
			keys[wParam] = TRUE;			// Si es así, se marca como TRUE
			return 0;						// y se regresa al ciclo
		}

		case WM_KEYUP:						// ¿Se ha soltado una tecla?
		{
			keys[wParam] = FALSE;			// Si es así, se marca como FALSE
			return 0;						// y se regresa al ciclo
		}

		case WM_SIZE:						// Si se redimensiona la ventana...
		{
			ReDimensionaEscenaGL(LOWORD(lParam),HIWORD(lParam));  	// LoWord=Width, HiWord=Height
			return 0;						// y se regresa al ciclo
		}
	}

	// Pasa todos los mensajes no considerados a DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

// Este es el punto de entrada al programa; la función principal 
int WINAPI WinMain(	HINSTANCE	hInstance,			// Instancia
					HINSTANCE	hPrevInstance,		// Instancia previa
					LPSTR		lpCmdLine,			// Parametros de la linea de comandos
					int			nCmdShow)			// Muestra el estado de la ventana
{
	MSG		msg;									// Estructura de mensajes de la ventana
	BOOL	done=FALSE;								// Variable booleana para salir del ciclo

	// Crea la ventana OpenGL
	if (!CreaVentanaOGL("PROGRAMA 3 Computación Gráfica",640,480,16))
	{
		return 0;									// Salir del programa si la ventana no fue creada
	}

	while(!done)									// Mientras done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Revisa si hay mensajes en espera
		{
			if (msg.message==WM_QUIT)				// Si se ha recibido el mensje de salir...
			{
				done=TRUE;							// Entonces done=TRUE
			}
			else									// Si no, Procesa los mensajes de la ventana
			{
				TranslateMessage(&msg);				// Traduce el mensaje
				DispatchMessage(&msg);				// Envia el mensaje
			}
		}
		else										// Si no hay mensajes...
		{
			// Dibuja la escena. 
			if (active)								// Si está activo el programa...
			{
				if (keys[VK_ESCAPE])				// Si se ha presionado ESC
				{
					done=TRUE;						// ESC indica el termino del programa
				}
				else								// De lo contrario, actualiza la pantalla
				{
					RenderizaEscena();				// Dibuja la escena
					//PROGRAMA 3
					if(play)
				{
			
						if(tipoAnim == 1) //caminar
								animacion(KeyFrame1, maxKF1 , 12);
						else if(tipoAnim == 2) //saltar
								animacion(KeyFrame2, maxKF2 , 10);
						else if(tipoAnim == 3) //disparar
								animacion(KeyFrame3, maxKF3 , 10);
				}
					SwapBuffers(hDC);				// Intercambia los Buffers (Double Buffering)
				}

				if(!ManejaTeclado()) return 0;
			}
			
		}
	}
	//PROGRAMA 2
	DescargaModelos();

	//PROGRAMA 3
	descargaTexturas();

	// Finalización del programa
	DestruyeVentanaOGL();							// Destruye la ventana
	return (msg.wParam);							// Sale del programa
}

int ManejaTeclado()
{
	//PROGRAMA 1
	if(keys[VK_UP])
	{		
		//camara.y+=0.3f;
		ControlPersonaje(3);

		if (play == false) //Para que la asignación de valores siguiente solo se haga una vez y empiece la animación
		{
			//Se le asignan a las variables del personaje los 
			//valores almacenados en el primer keyframe para que
			//inicie desde ahí la animación.
			Angt1 = KeyFrame1[0].Angt1;
			Angt2 = KeyFrame1[0].Angt2;
			Angc1 = KeyFrame1[0].Angc1;
			Angc2 = KeyFrame1[0].Angc2;
			Angbi1 = KeyFrame1[0].Angbi1;
			Angbi2 = KeyFrame1[0].Angbi2;
			Angbib = KeyFrame1[0].Angbib;
			Angbd1 = KeyFrame1[0].Angbd1;
			Angbd2 = KeyFrame1[0].Angbd2;
			Angbdb = KeyFrame1[0].Angbdb;
			Angpizq1 = KeyFrame1[0].Angpizq1;
			Angpizq2 = KeyFrame1[0].Angpizq2;
			Angpder1 = KeyFrame1[0].Angpder1;
			Angpder2 = KeyFrame1[0].Angpder2;
			Angpi = KeyFrame1[0].Angpi;
			Angpd = KeyFrame1[0].Angpd;
			Xtor = KeyFrame1[0].Xtor;
			Ytor = KeyFrame1[0].Ytor;
			Ztor = KeyFrame1[0].Ztor;

			play = true;
			playIndex = 0;
			tipoAnim = 1;

			player1.caminando = true;

		}
	}
	if(keys[VK_DOWN])
	{
		//camara.y-=0.3f;
		ControlPersonaje(4);

		if (play == false) //Para que la asignación de valores siguiente solo se haga una vez y empiece la animación
		{
			//Se le asignan a las variables del personaje los 
			//valores almacenados en el primer keyframe para que
			//inicie desde ahí la animación.
			Angt1 = KeyFrame1[0].Angt1;
			Angt2 = KeyFrame1[0].Angt2;
			Angc1 = KeyFrame1[0].Angc1;
			Angc2 = KeyFrame1[0].Angc2;
			Angbi1 = KeyFrame1[0].Angbi1;
			Angbi2 = KeyFrame1[0].Angbi2;
			Angbib = KeyFrame1[0].Angbib;
			Angbd1 = KeyFrame1[0].Angbd1;
			Angbd2 = KeyFrame1[0].Angbd2;
			Angbdb = KeyFrame1[0].Angbdb;
			Angpizq1 = KeyFrame1[0].Angpizq1;
			Angpizq2 = KeyFrame1[0].Angpizq2;
			Angpder1 = KeyFrame1[0].Angpder1;
			Angpder2 = KeyFrame1[0].Angpder2;
			Angpi = KeyFrame1[0].Angpi;
			Angpd = KeyFrame1[0].Angpd;
			Xtor = KeyFrame1[0].Xtor;
			Ytor = KeyFrame1[0].Ytor;
			Ztor = KeyFrame1[0].Ztor;

			play = true;
			playIndex = 0;
			tipoAnim = 1;

			player1.caminando = true;

		}
	}
	if(keys[VK_LEFT])
	{
		camara.x-=0.3f;
	//	cx -= 0.1;
	}
	if(keys[VK_RIGHT])
	{
		camara.x+=0.3f;
		//cx += 0.1;
	}

	if(keys[VK_PRIOR])
	{
		
	}
	if(keys[VK_NEXT])
	{
		
	}

	if(keys[VK_HOME])
	{
		
	}

	if(keys[VK_END])
	{
		
	}

	//Controles de la iluminación
	if (keys['Z'])
		LightPos[0] += 1.0f; //Hacia la derecha

	if (keys['X'])
		LightPos[0] -= 1.0f; //Hacia la izquierda

	if (keys['C'])
		LightPos[1] += 1.0f; //Hacia arriba

	if (keys['V'])
		LightPos[1] -= 1.0f; //Hacia abajo

	if (keys['B'])
		LightPos[2] += 1.0f; //Hacia adelante

	if (keys['N'])
		LightPos[2] -= 1.0f; //Hacia atrás

	
	if(keys['S'])
	{
			if(play==false)
			{
				Angt1   = KeyFrame2[0].Angt1;
				Angt2   = KeyFrame2[0].Angt2;
				Angc1   = KeyFrame2[0].Angc1;
				Angc2   = KeyFrame2[0].Angc2;
				Angbi1  = KeyFrame2[0].Angbi1;
				Angbi2  = KeyFrame2[0].Angbi2;
				Angbib  = KeyFrame2[0].Angbib;
				Angbd1  = KeyFrame2[0].Angbd1;
				Angbd2  = KeyFrame2[0].Angbd2;
				Angbdb  = KeyFrame2[0].Angbdb;
				Angpizq1= KeyFrame2[0].Angpizq1;
				Angpizq2= KeyFrame2[0].Angpizq2;
				Angpder1= KeyFrame2[0].Angpder1;
				Angpder2= KeyFrame2[0].Angpder2;
				Angpi   = KeyFrame2[0].Angpi;
				Angpd   = KeyFrame2[0].Angpd;
				Xtor    = KeyFrame2[0].Xtor;
				Ytor    = KeyFrame2[0].Ytor;
				Ztor    = KeyFrame2[0].Ztor;
				play=true;
				playIndex=0;
				tipoAnim=2;
					
				player1.saltando=true;
				}
		}
	
	if(keys['A'])
	{
			if(play==false)
			{
				Angt1   = KeyFrame3[0].Angt1;
				Angt2   = KeyFrame3[0].Angt2;
				Angc1   = KeyFrame3[0].Angc1;
				Angc2   = KeyFrame3[0].Angc2;
				Angbi1  = KeyFrame3[0].Angbi1;
				Angbi2  = KeyFrame3[0].Angbi2;
				Angbib  = KeyFrame3[0].Angbib;
				Angbd1  = KeyFrame3[0].Angbd1;
				Angbd2  = KeyFrame3[0].Angbd2;
				Angbdb  = KeyFrame3[0].Angbdb;
				Angpizq1= KeyFrame3[0].Angpizq1;
				Angpizq2= KeyFrame3[0].Angpizq2;
				Angpder1= KeyFrame3[0].Angpder1;
				Angpder2= KeyFrame3[0].Angpder2;
				Angpi   = KeyFrame3[0].Angpi;
				Angpd   = KeyFrame3[0].Angpd;
				Xtor    = KeyFrame3[0].Xtor;
				Ytor    = KeyFrame3[0].Ytor;
				Ztor    = KeyFrame3[0].Ztor;
				play=true;
				playIndex=0;
				tipoAnim=3;
					
				player1.disparando=true;
				}
		}
	
	//PROGRAMA 3
	//Al presionar cualquiera de las teclas de dirección se iniciará la animación de caminar
	//Al soltar la tecla presionada se detiene la animación.
	if(GetKeyState(VK_LEFT) & 0x80) //Si está presionada la tecla LEFT
	{
		ControlPersonaje(2);
		
		if(play==false) //Para que la asignación de valores siguiente solo se haga una vez y empiece la animación
		{
			//Se le asignan a las variables del personaje los 
			//valores almacenados en el primer keyframe para que
			//inicie desde ahí la animación.
			Angt1   = KeyFrame1[0].Angt1;
			Angt2   = KeyFrame1[0].Angt2;
			Angc1   = KeyFrame1[0].Angc1;
			Angc2   = KeyFrame1[0].Angc2;
			Angbi1  = KeyFrame1[0].Angbi1;
			Angbi2  = KeyFrame1[0].Angbi2;
			Angbib  = KeyFrame1[0].Angbib;
			Angbd1  = KeyFrame1[0].Angbd1;
			Angbd2  = KeyFrame1[0].Angbd2;
			Angbdb  = KeyFrame1[0].Angbdb;
			Angpizq1= KeyFrame1[0].Angpizq1;
			Angpizq2= KeyFrame1[0].Angpizq2;
			Angpder1= KeyFrame1[0].Angpder1;
			Angpder2= KeyFrame1[0].Angpder2;
			Angpi   = KeyFrame1[0].Angpi;
			Angpd   = KeyFrame1[0].Angpd;
			Xtor    = KeyFrame1[0].Xtor;
			Ytor    = KeyFrame1[0].Ytor;
			Ztor    = KeyFrame1[0].Ztor;

			play=true;
			playIndex=0;
			tipoAnim=1;

			player1.caminando=true;
					
		}
	}

	if(GetKeyState(VK_RIGHT) & 0x80) //Si está presionada la tecla RIGHT
	{
		ControlPersonaje(1);
		
		if(play==false) //Para que la asignación de valores siguiente solo se haga una vez y empiece la animación
		{
			//Se le asignan a las variables del personaje los 
			//valores almacenados en el primer keyframe para que
			//inicie desde ahí la animación.
			Angt1   = KeyFrame1[0].Angt1;
			Angt2   = KeyFrame1[0].Angt2;
			Angc1   = KeyFrame1[0].Angc1;
			Angc2   = KeyFrame1[0].Angc2;
			Angbi1  = KeyFrame1[0].Angbi1;
			Angbi2  = KeyFrame1[0].Angbi2;
			Angbib  = KeyFrame1[0].Angbib;
			Angbd1  = KeyFrame1[0].Angbd1;
			Angbd2  = KeyFrame1[0].Angbd2;
			Angbdb  = KeyFrame1[0].Angbdb;
			Angpizq1= KeyFrame1[0].Angpizq1;
			Angpizq2= KeyFrame1[0].Angpizq2;
			Angpder1= KeyFrame1[0].Angpder1;
			Angpder2= KeyFrame1[0].Angpder2;
			Angpi   = KeyFrame1[0].Angpi;
			Angpd   = KeyFrame1[0].Angpd;
			Xtor    = KeyFrame1[0].Xtor;
			Ytor    = KeyFrame1[0].Ytor;
			Ztor    = KeyFrame1[0].Ztor;

			play=true;
			playIndex=0;
			tipoAnim=1;
					
			player1.caminando=true;
		}

	}
	
	//Para que al soltar la tecla presionada el personaje no quede en una posición
	//intermedia de la animación se asignan los valores originales a las variables
	if(!(GetKeyState(VK_LEFT) & 0x80  || GetKeyState(VK_RIGHT) & 0x80)) //Si no está presionada alguna de esas teclas
	{

		if(tipoAnim == 1) //Para que no afecte la posición si está detenido pero saltando*
		{
			play=false;
			Angt1   = 0.0f;
			Angt2   = 0.0f;
			Angc1   = 0.0f;
			Angc2   = 0.0f;
			Angbi1  = 0.0f;
			Angbi2  = 0.0f;
			Angbib  = 0.0f;
			Angbd1  = 0.0f;
			Angbd2  = 0.0f;
			Angbdb  = 0.0f;
			Angpizq1= 0.0f;
			Angpizq2= 0.0f;
			Angpder1= 0.0f;
			Angpder2= 0.0f;
			Angpi   = 0.0f;
			Angpd   = 0.0f;
			Xtor    = 0.0f;
			Ytor    = 0.0f;
			Ztor    = 0.0f;
			
			player1.caminando=false;
		}

	}
	return TRUE;
}
