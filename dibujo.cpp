#include<windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;

#define ANCHO 600
#define ALTO 600
// Valores para el tamaño de la ventana de despliegue
GLsizei winWidth=600, winHeight=600;

// Fija el tamaño de las coordenadas del mundo de la ventana de recorte
//GLfloat xwcMin=-13.0, xwcMax=24.0;
//GLfloat ywcMin=-13.50, ywcMax=26.5;
GLfloat xwcMin=-5.0, xwcMax=16.0;
GLfloat ywcMin=-5.50, ywcMax=18.5;

GLfloat xpoint=0.0;
GLfloat ypoint=0.0;

string xvalue="x";
string yvalue="y";

class wcPt3D{
public:
	GLfloat x,y,z;
};

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void plotPoint(wcPt3D bezCurvePt)
{
	glBegin(GL_POINTS);
	  glVertex2f(bezCurvePt.x, bezCurvePt.y);
	glEnd();
}

// calcula los coeficientes binomiales C para un valor dado de n
void binomialCoeffs(GLint n, GLint * C)
{
	GLint k,j;

	for(k=0; k<=n; k++){
		// calcula n!/k!(n-k)!
		C[k]=1;
		for(j=n; j>=k+1; j--)
			C[k]*=j;
		for(j=n-k; j>=2; j--)
			C[k]/=j;
	}
}

void computeBezPt(GLfloat u, wcPt3D * bezPt, GLint nCtrlPts, wcPt3D * ctrlPts, GLint * C)
{
	GLint k, n=nCtrlPts-1;
	GLfloat bezBlendFcn;

	bezPt->x = bezPt->y = bezPt->z = 0.0;

	// calcula las funciones de combinacion y combina los puntos de control
	for(k=0; k<nCtrlPts; k++){
		bezBlendFcn = C[k]*pow(u,k)*pow(1-u,n-k);
		bezPt->x += ctrlPts[k].x*bezBlendFcn;
        bezPt->y += ctrlPts[k].y*bezBlendFcn;
        bezPt->z += ctrlPts[k].z*bezBlendFcn;
	}
}

void bezier(wcPt3D * ctrlPts, GLint nCtrlPts, GLint nBezCurvePts)
{
	wcPt3D bezCurvePt;
	GLfloat u;
	GLint *C, k;

	// asigna el espacio para los coeficientes binomiales
	C=new GLint [nCtrlPts];

	binomialCoeffs(nCtrlPts-1, C);
	for(k=0; k<=nBezCurvePts; k++){
		u=GLfloat (k)/GLfloat (nBezCurvePts);
		computeBezPt(u, &bezCurvePt, nCtrlPts, ctrlPts, C);
		plotPoint(bezCurvePt);
	}
	delete [] C;
}

void displayFcn(void)
{
	// Fija el número de los puntos de control y el número de las posiciones
    // de la curva que se trazarán a lo largo de la curva de Bezier

	GLint nCtrlPts=4, nBezCurvePts=1000;


	wcPt3D c15 [4] = {{4.7,4.65},{2.9,4.5},{2.9,7.40},{4.7,7.25}};
	wcPt3D c16 [4] = {{4.4,4.65},{6.2,4.5},{6.2,7.40},{4.4,7.25}};

	wcPt3D c17 [4] = {{4.7,5.5},{3.4,5.35},{3.4,8.15},{4.7,8.0}};		//Ojo Completo
	wcPt3D c18 [4] = {{4.6,5.5},{6.1,5.35},{6.1,8.15},{4.7,8.0}};

	wcPt3D c22 [4] = {{7.1,9.3},{7.1,9.2},{6.9,8.8},{6.5,8.9}}; //ojera derecha
	wcPt3D c23 [4] = {{7.1,9.3},{7.0,8.9},{7.0,8.5},{6.8,7.67}}; //mejilla
	wcPt3D c24 [4] = {{7.25,9.4},{7.3,9.3},{7.3,9.1},{7.55,8.95}}; //cabello
	wcPt3D c25 [4] = {{7.55,8.95},{7.3,8.6},{7.4,8.7},{6.96,8.50}}; //cabello
	wcPt3D c26 [4] = {{6.45,7.6},{7.1,7.7},{7.2,6.8},{6.2,6.7}};//boca
	wcPt3D c27 [4] = {{6.65,7.27},{6.0,7.1},{5.1,7.0},{4.3,7.65}}; //boca
	wcPt3D c28 [4] = {{4.4,7.90},{3.7,8.3},{3.8,7.2},{4.3,7.25}}; //boca
	wcPt3D c29 [4] = {{6.3,9.4},{6.3,7.8},{5.9,7.8},{5.7,9.15}}; //nariz
	wcPt3D c30 [4] = {{5.1,9.05},{4.7,9.0},{4.3,9.0},{4.05,9.4}}; //ojera izq
	wcPt3D c31 [4] = {{7.2,11.17},{7.2,11.3},{7.2,11.4},{7.2,11.75}}; //frente
	wcPt3D c32 [4] = {{7.2,11.75},{6.2,12.3},{5.2,12.2},{4.6,11.9}}; //ceja abajo
	wcPt3D c33 [4] = {{7.3,12.05},{6.2,12.7},{5.2,12.6},{4.5,12.25}}; //ceja arriba
	wcPt3D c34 [4] = {{4.5,12.25},{4.2,12.15},{4.3,11.8},{4.6,11.9}}; //borde de ceja izq
	wcPt3D c35 [4] = {{7.3,12.05},{7.6,11.75},{7.4,11.55},{7.2,11.75}}; //borde de ceja der
	wcPt3D c36 [4] = {{7.1,12.15},{6.3,14.20},{4.5,14.30},{3.4,12.20}}; //cabeza
	wcPt3D c37 [4] = {{3.4,12.20},{3.25,11.70},{2.95,10.0},{3.0,9.3}}; //cabeza
	wcPt3D c38 [4] = {{3.25,9.3},{2.35,9.2},{2.35,8.1},{3.20,7.95}}; //oreja izq
	wcPt3D c39 [4] = {{3.0,7.95},{3.3,4.8},{5.8,4.6},{6.6,6.8}}; //barbilla
	wcPt3D c40 [4] = {{3.4,6.4},{3.2,6.1},{3.1,5.8},{2.9,5.5}}; //cuello
	wcPt3D c41 [4] = {{4.55,5.41},{4.50,5.35},{4.45,5.25},{4.3,4.8}}; //cuello
	wcPt3D c42 [4] = {{2.9,5.5},{3.36,4.7},{3.82,4.6},{4.3,4.8}}; //cuello
	wcPt3D c43 [4] = {{2.9,5.5},{2.6,5.5},{2.3,5.4},{1.2,5.1}}; //cuerpo
	wcPt3D c44 [4] = {{1.2,5.1},{1.0,4.5},{0.6,3.4},{-0.6,-1.15}}; //cuerpo
	wcPt3D c45 [4] = {{1.8,3.4},{1.5,2.5},{1.2,1.0},{0.6,-1.15}}; //cuerpo
	wcPt3D c46 [4] = {{2.85,5.5},{2.9,3.4},{2.9,1.0},{2.8,-1.15}}; //cuerpo
	wcPt3D c47 [4] = {{2.6,5.3},{2.3,4.4},{2.1,3.6},{1.7,2.1}}; //cuerpo
	wcPt3D c48 [4] = {{1.7,2.1},{2.0,1.7},{2.3,1.5},{2.5,1.3}}; //cuerpo
	wcPt3D c49 [4] = {{2.5,1.3},{2.2,1.0},{1.9,0.6},{1.6,0.3}}; //cuerpo
	wcPt3D c50 [4] = {{1.6,0.3},{1.8,-0.3},{1.8,-0.9},{1.9,-1.15}}; //cuerpo
	wcPt3D c51 [4] = {{4.4,5.0},{4.4,3.4},{4.2,1.0},{4.0,-1.15}}; //cuerpo
	wcPt3D c52 [4] = {{4.6,4.8},{4.7,4.4},{5.0,2.7},{5.45,1.75}}; //cuerpo
	wcPt3D c53 [4] = {{5.45,1.75},{5.1,1.4},{4.8,1.2},{4.5,0.9}}; //cuerpo
	wcPt3D c54 [4] = {{4.5,0.9},{4.8,0.5},{5.0,0.2},{5.2,-0.1}}; //cuerpo
	wcPt3D c55 [4] = {{5.2,-0.1},{5.1,-0.5},{5.0,-0.8},{4.9,-1.15}}; //cuerpo
	wcPt3D c56 [4] = {{5.05,1.35},{5.0,0.9},{4.9,0.4},{4.9,0.25}}; //cuerpo
	wcPt3D c57 [4] = {{5.2,2.3},{5.25,2.4},{5.25,2.6},{5.3,2.85}}; //cuerpo
	wcPt3D c58 [4] = {{4.4,5.2},{4.7,5.1},{5.2,4.45},{5.5,4.2}}; //cuerpo
	wcPt3D c59 [4] = {{5.5,4.2},{5.7,4.0},{5.7,-0.1},{5.7,-1.15}}; //cuerpo
	wcPt3D c60 [4] = {{7.5,10.7},{7.7,10.8},{7.9,10.9},{8.2,11.3}}; //cabello
	wcPt3D c61 [4] = {{8.2,11.3},{7.8,11.4},{7.5,11.5},{7.4,11.75}}; //cabello
	wcPt3D c62 [4] = {{7.35,11.95},{7.4,12.3},{7.6,12.5},{8.15,13.75}}; //cabello
	wcPt3D c63 [4] = {{8.15,13.75},{7.9,13.65},{7.6,13.7},{6.9,13.55}}; //cabello
	wcPt3D c64 [4] = {{6.9,13.55},{7.1,15.4},{6.8,15.9},{6.5,16.35}}; //cabello
	wcPt3D c65 [4] = {{6.5,16.35},{6.2,15.4},{6.0,14.4},{5.7,14.1}}; //cabello
	wcPt3D c66 [4] = {{5.7,14.1},{5.4,15.5},{4.4,16.5},{3.95,16.8}}; //cabello
	wcPt3D c67 [4] = {{3.95,16.8},{3.8,16.0},{3.9,15.5},{3.6,14.1}}; //cabello
	wcPt3D c68 [4] = {{3.6,14.1},{2.5,14.2},{2.5,14.2},{1.75,14.5}}; //cabello
	wcPt3D c69 [4] = {{1.75,14.5},{2.1,13.5},{2.3,13.0},{2.67,12.2}}; //cabello
	wcPt3D c70 [4] = {{2.67,12.2},{2.1,12.2},{1.5,11.9},{0.5,11.5}}; //cabello
	wcPt3D c71 [4] = {{0.5,11.5},{1.1,11.0},{1.7,11.0},{2.35,10.2}}; //cabello
	wcPt3D c72 [4] = {{2.35,10.2},{2.0,9.8},{1.7,10.0},{1.0,9.4}}; //cabello
	wcPt3D c73 [4] = {{1.0,9.4},{1.5,9.0},{2.0,8.8},{2.4,8.3}}; //cabello
	wcPt3D c74 [4] = {{2.4,8.3},{2.0,8.0},{1.9,7.9},{1.7,7.6}}; //cabello
	wcPt3D c75 [4] = {{1.7,7.6},{2.1,7.4},{2.4,7.5},{2.8,7.5}}; //cabello
	wcPt3D c76 [4] = {{2.8,7.5},{2.6,6.9},{2.4,6.8},{2.4,6.6}}; //cabello
	wcPt3D c77 [4] = {{2.4,6.6},{2.6,6.7},{2.8,6.7},{3.2,6.8}}; //cabello
	wcPt3D c78 [4] = {{10.5,6.6},{11.4,9.1},{16.0,8.4},{14.95,4.05}}; //cabeza morty
	wcPt3D c79 [4] = {{14.75,4.1},{15.4,4.0},{15.25,2.65},{14.5,2.95}}; //oreja morty
	wcPt3D c80 [4] = {{14.5,2.95},{13.7,0.9},{8.75,2.0},{10.5,6.6}}; //cabeza morty
	wcPt3D c81 [4] = {{10.15,5.0},{9.95,4.85},{9.95,4.35},{10.15,4.15}}; //oreja morty
	wcPt3D c82 [4] = {{12.15,5.05},{11.65,4.9},{11.8,4.1},{12.35,4.5}}; //nariz morty
	wcPt3D c83 [4] = {{11.75,3.6},{11.95,3.5},{12.2,3.5},{12.8,3.7}}; //boca morty
	wcPt3D c84 [4] = {{11.75,3.3},{11.95,3.2},{12.4,3.1},{12.8,3.30}}; //boca morty
	wcPt3D c85 [4] = {{12.8,3.7},{13.1,3.85},{13.2,3.4},{12.8,3.30}}; //boca morty
	wcPt3D c86 [4] = {{11.75,3.6},{11.45,3.6},{11.40,3.40},{11.75,3.3}}; //boca morty
	wcPt3D c87 [4] = {{11.85,7.50},{11.70,7.5},{11.40,7.5},{11.13,7.4}}; //ceja izq morty
	wcPt3D c88 [4] = {{13.53,7.15},{13.70,7.05},{13.90,6.95},{14.30,6.6}}; //ceja der morty
	wcPt3D c89 [4] = {{12.15,9.0},{13.4,9.8},{17.5,7.4},{15.18,3.7}}; //cabello morty
	wcPt3D c90 [4] = {{12.15,9.0},{11.8,8.5},{11.5,8.6},{11.03,8.2}}; //cabello morty
	wcPt3D c91 [4] = {{11.03,8.2},{10.85,7.7},{10.7,7.6},{10.5,6.6}}; //cabello morty
	wcPt3D c92 [4] = {{11.1,2.55},{10.9,2.1},{10.4,2.2},{10.0,-1.15}}; //cuerpo morty
	wcPt3D c93 [4] = {{11.1,2.55},{10.9,2.1},{10.3,2.2},{10.3,-1.15}}; //cuerpo morty
	wcPt3D c94 [4] = {{11.2,0.15},{11.2,-0.2},{11.2,-0.5},{11.3,-1.15}}; //cuerpo morty
	wcPt3D c95 [4] = {{13.45,1.15},{13.3,-0.2},{13.3,-0.5},{13.2,-1.15}}; //cuerpo morty
	wcPt3D c96 [4] = {{13.45,2.1},{14.0,1.7},{14.1,1.0},{14.3,-1.15}}; //cuerpo morty
	wcPt3D c97 [4] = {{14.3,2.6},{14.35,1.7},{14.35,1.4},{14.3,0.5}}; //pared
	wcPt3D c98 [4] = {{14.3,10.3},{14.35,8.9},{14.35,8.7},{14.3,8.55}}; //pared
	wcPt3D c99 [4] = {{14.45,15.3},{14.35,11.7},{14.35,11.0},{14.3,10.8}}; //pared
	wcPt3D c100 [4] = {{14.2,0.5},{14.6,0.5},{14.9,0.5},{16.3,0.2}}; //fondo
	wcPt3D c101 [4] = {{5.7,0.5},{9.6,0.5},{10.0,0.5},{10.2,0.5}}; //fondo
	wcPt3D c102 [4] = {{5.7,-0.7},{9.6,-0.7},{10.0,-0.7},{10.0,-0.7}}; //fondo
	wcPt3D c103 [4] = {{8.4,-0.2},{9.6,-0.2},{10.0,-0.2},{10.15,-0.2}}; //fondo
	wcPt3D c104 [4] = {{8.4,-0.2},{8.0,-0.1},{7.8,-0.2},{8.1,-0.7}}; //fondo
	wcPt3D c105 [4] = {{14.2,-0.7},{14.6,-0.7},{14.9,-0.7},{16.3,-1.0}}; //fondo
	wcPt3D c106 [4] = {{7.20,0.5},{7.7,4.3},{5.9,4.8},{5.2,5.4}}; //fondo
	wcPt3D c107 [4] = {{7.40,0.5},{7.5,0.7},{7.45,2.2},{7.2,2.95}}; //fondo
	wcPt3D c108 [4] = {{6.65,0.5},{7.5,3.6},{5.9,4.5},{4.85,4.9}}; //fondo
	wcPt3D c109 [4] = {{6.65,0.5},{7.5,3.6},{5.9,4.0},{5.55,4.20}}; //fondo
	wcPt3D c110 [4] = {{6.80,0.9},{6.8,2.4},{5.9,3.4},{5.6,3.75}}; //fondo
	wcPt3D c111 [4] = {{6.25,0.5},{6.7,1.6},{5.9,2.4},{5.65,3.40}}; //fondo
	wcPt3D c112 [4] = {{5.8,0.5},{6.7,1.9},{5.9,2.4},{5.65,2.9}}; //fondo
	wcPt3D c113 [4] = {{3.1,5.8},{2.6,5.8},{2.4,5.8},{1.7,5.7}}; //fondo
	wcPt3D c114 [4] = {{1.7,5.7},{1.7,5.5},{1.7,5.4},{1.7,5.25}}; //fondo
	wcPt3D c115 [4] = {{1.2,5.0},{-1.0,3.4},{-0.7,1.2},{-0.3,0.0}}; //fondo
	wcPt3D c116 [4] = {{0.95,4.3},{-1.0,2.4},{-0.1,0.9},{-0.20,0.25}}; //fondo
	wcPt3D c117 [4] = {{0.62,3.3},{0.05,2.4},{0.10,1.8},{0.15,1.6}}; //fondo
	wcPt3D c118 [4] = {{-0.3,0.0},{-0.6,0.0},{-0.7,0.0},{-1.0,0.0}}; //fondo
	wcPt3D c119 [4] = {{-1.0,0.0},{-1.1,-0.2},{-1.1,-0.3},{-1.2,-0.9}}; //fondo
	wcPt3D c120 [4] = {{-0.4,-0.5},{-0.5,-0.5},{-0.6,-0.5},{-0.7,-0.5}}; //fondo
	wcPt3D c121 [4] = {{-0.7,-0.5},{-0.8,-0.7},{-0.8,-0.8},{-0.8,-0.9}}; //fondo
	wcPt3D c122 [4] = {{-0.5,-0.9},{-1.0,-0.9},{-3.0,-0.9},{-4.2,-1.15}}; //fondo
	wcPt3D c123 [4] = {{-0.6,-1.15},{-1.0,-1.15},{-3.0,-1.15},{-4.2,-1.15}}; //fondo
	wcPt3D c124 [4] = {{5.7,-1.15},{9.6,-1.15},{10.0,-1.15},{10.0,-1.15}}; //fondo
	wcPt3D c125 [4] = {{14.2,-1.15},{14.6,-1.15},{14.9,-1.15},{16.3,-1.15}}; //fondo
	wcPt3D c126 [4] = {{-3.7,12.0},{-3.2,12.0},{-3.0,12.0},{-2.9,12.0}}; //fondo
	wcPt3D c127 [4] = {{-3.7,12.0},{-3.9,11.7},{-4.1,11.5},{-4.3,11.0}}; //fondo
	wcPt3D c128 [4] = {{-4.3,11.0},{-4.5,10.9},{-4.6,10.8},{-5.1,10.8}}; //fondo
	wcPt3D c129 [4] = {{-4.3,11.0},{-4.0,11.0},{-3.7,11.0},{-3.3,10.6}}; //fondo
	wcPt3D c130 [4] = {{-3.3,10.6},{-3.0,10.6},{-2.7,10.6},{-2.5,10.6}}; //fondo
	wcPt3D c131 [4] = {{-2.5,10.6},{-2.2,10.7},{-2.0,10.7},{-1.7,10.7}}; //fondo
	wcPt3D c132 [4] = {{-2.5,10.6},{-2.2,10.4},{-2.1,10.2},{-2.0,10.1}}; //fondo
	wcPt3D c133 [4] = {{-4.3,8.6},{-4.5,8.7},{-4.6,8.8},{-5.1,9.0}}; //fondo



	glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(1);
	glColor3f(0.0,0.0,0.0); // punto color rojo

	bezier(c97, nCtrlPts, nBezCurvePts);
	bezier(c98, nCtrlPts, nBezCurvePts);
	bezier(c99, nCtrlPts, nBezCurvePts);
	bezier(c100, nCtrlPts, nBezCurvePts);
	bezier(c101, nCtrlPts, nBezCurvePts);
	bezier(c102, nCtrlPts, nBezCurvePts);
	bezier(c103, nCtrlPts, nBezCurvePts);
	bezier(c104, nCtrlPts, nBezCurvePts);
	bezier(c105, nCtrlPts, nBezCurvePts);
	bezier(c106, nCtrlPts, nBezCurvePts);
	bezier(c107, nCtrlPts, nBezCurvePts);
	bezier(c108, nCtrlPts, nBezCurvePts);
	bezier(c109, nCtrlPts, nBezCurvePts);
	bezier(c110, nCtrlPts, nBezCurvePts);
	bezier(c111, nCtrlPts, nBezCurvePts);
	bezier(c112, nCtrlPts, nBezCurvePts);
	bezier(c113, nCtrlPts, nBezCurvePts);
	bezier(c114, nCtrlPts, nBezCurvePts);
	bezier(c115, nCtrlPts, nBezCurvePts);
	bezier(c116, nCtrlPts, nBezCurvePts);
	bezier(c117, nCtrlPts, nBezCurvePts);
	bezier(c118, nCtrlPts, nBezCurvePts);
	bezier(c119, nCtrlPts, nBezCurvePts);
	bezier(c120, nCtrlPts, nBezCurvePts);
	bezier(c121, nCtrlPts, nBezCurvePts);
	bezier(c122, nCtrlPts, nBezCurvePts);
	bezier(c123, nCtrlPts, nBezCurvePts);
	bezier(c124, nCtrlPts, nBezCurvePts);
	bezier(c125, nCtrlPts, nBezCurvePts);
	bezier(c126, nCtrlPts, nBezCurvePts);
	bezier(c127, nCtrlPts, nBezCurvePts);
	bezier(c128, nCtrlPts, nBezCurvePts);
	bezier(c129, nCtrlPts, nBezCurvePts);
	bezier(c130, nCtrlPts, nBezCurvePts);
	bezier(c131, nCtrlPts, nBezCurvePts);
	bezier(c132, nCtrlPts, nBezCurvePts);
	bezier(c133, nCtrlPts, nBezCurvePts);



//Morty

	glPushMatrix (); //ojo 1
	glTranslatef (7.7,1.0,0.0);
	glScalef (0.75,0.75,1);
	bezier(c17, nCtrlPts, nBezCurvePts);
	bezier(c18, nCtrlPts, nBezCurvePts);
	glPopMatrix ();

	glPushMatrix (); //ojo 2
	glTranslatef (10,1,0.0);
	glScalef (0.75,0.75,1);
	bezier(c15, nCtrlPts, nBezCurvePts);
	bezier(c16, nCtrlPts, nBezCurvePts);
	glPopMatrix ();

	glPushMatrix (); //puntos de los ojos
		glTranslatef (10.9,6.6,0.0);
		glScalef (0.60,0.85,1);
		glColor3f (0,0,0);
		glutSolidSphere (0.15,30,20);
	glPopMatrix ();

	glPushMatrix (); //puntos de los ojos
		glTranslatef (13.0,5.9,0.0);
		glScalef (0.60,0.85,1);
		glColor3f (0,0,0);
		glutSolidSphere (0.15,30,20);
	glPopMatrix ();

	bezier(c78, nCtrlPts, nBezCurvePts);
	bezier(c79, nCtrlPts, nBezCurvePts);
	bezier(c80, nCtrlPts, nBezCurvePts);
	bezier(c81, nCtrlPts, nBezCurvePts);
	bezier(c82, nCtrlPts, nBezCurvePts);
	bezier(c83, nCtrlPts, nBezCurvePts);
	bezier(c84, nCtrlPts, nBezCurvePts);
	bezier(c85, nCtrlPts, nBezCurvePts);
	bezier(c86, nCtrlPts, nBezCurvePts);
	bezier(c87, nCtrlPts, nBezCurvePts);
	bezier(c88, nCtrlPts, nBezCurvePts);
	bezier(c89, nCtrlPts, nBezCurvePts);
	bezier(c90, nCtrlPts, nBezCurvePts);
	bezier(c91, nCtrlPts, nBezCurvePts);
	bezier(c92, nCtrlPts, nBezCurvePts);
	bezier(c93, nCtrlPts, nBezCurvePts);
	bezier(c94, nCtrlPts, nBezCurvePts);
	bezier(c95, nCtrlPts, nBezCurvePts);
	bezier(c96, nCtrlPts, nBezCurvePts);

//rick

	glPushMatrix (); //ojo 1
		glTranslatef(1.6,6.0,0.0);
		glScalef (0.75,0.75,1);
		bezier(c15, nCtrlPts, nBezCurvePts);
		bezier(c16, nCtrlPts, nBezCurvePts);
	glPopMatrix ();
	glPushMatrix (); //ojo 2
		glTranslatef(3.3,5.2,0.0);
		glScalef (0.75,0.75,1);
		bezier(c17, nCtrlPts, nBezCurvePts);
		bezier(c18, nCtrlPts, nBezCurvePts);
	glPopMatrix ();
	glPushMatrix (); //puntos de los ojos
		glTranslatef (5.5,10.0,0.0);
		glScalef (0.60,0.85,1);
		glColor3f (0,0,0);
		glutSolidSphere (0.15,30,20);
	glPopMatrix ();

	glPushMatrix (); //puntos de los ojos
		glTranslatef (7.2,9.8,0.0);
		glScalef (0.60,0.85,1);
		glColor3f (0,0,0);
		glutSolidSphere (0.15,30,20);
	glPopMatrix ();

	bezier(c22, nCtrlPts, nBezCurvePts);
	bezier(c23, nCtrlPts, nBezCurvePts);
	bezier(c24, nCtrlPts, nBezCurvePts);
	bezier(c25, nCtrlPts, nBezCurvePts);
	bezier(c26, nCtrlPts, nBezCurvePts);
	bezier(c27, nCtrlPts, nBezCurvePts);
	bezier(c28, nCtrlPts, nBezCurvePts);
	bezier(c29, nCtrlPts, nBezCurvePts);
	bezier(c30, nCtrlPts, nBezCurvePts);
	bezier(c31, nCtrlPts, nBezCurvePts);
	bezier(c32, nCtrlPts, nBezCurvePts);
	bezier(c33, nCtrlPts, nBezCurvePts);
	bezier(c34, nCtrlPts, nBezCurvePts);
	bezier(c35, nCtrlPts, nBezCurvePts);
	bezier(c36, nCtrlPts, nBezCurvePts);
	bezier(c37, nCtrlPts, nBezCurvePts);
	bezier(c38, nCtrlPts, nBezCurvePts);
	bezier(c39, nCtrlPts, nBezCurvePts);
	bezier(c40, nCtrlPts, nBezCurvePts);
	bezier(c41, nCtrlPts, nBezCurvePts);
	bezier(c42, nCtrlPts, nBezCurvePts);
	bezier(c43, nCtrlPts, nBezCurvePts);
	bezier(c44, nCtrlPts, nBezCurvePts);
	bezier(c45, nCtrlPts, nBezCurvePts);
	bezier(c46, nCtrlPts, nBezCurvePts);
	bezier(c47, nCtrlPts, nBezCurvePts);
	bezier(c48, nCtrlPts, nBezCurvePts);
	bezier(c49, nCtrlPts, nBezCurvePts);
	bezier(c50, nCtrlPts, nBezCurvePts);
	bezier(c51, nCtrlPts, nBezCurvePts);
	bezier(c52, nCtrlPts, nBezCurvePts);
	bezier(c53, nCtrlPts, nBezCurvePts);
	bezier(c54, nCtrlPts, nBezCurvePts);
	bezier(c55, nCtrlPts, nBezCurvePts);
	bezier(c56, nCtrlPts, nBezCurvePts);
	bezier(c57, nCtrlPts, nBezCurvePts);
	bezier(c58, nCtrlPts, nBezCurvePts);
	bezier(c59, nCtrlPts, nBezCurvePts);
	bezier(c60, nCtrlPts, nBezCurvePts);
	bezier(c61, nCtrlPts, nBezCurvePts);
	bezier(c62, nCtrlPts, nBezCurvePts);
	bezier(c63, nCtrlPts, nBezCurvePts);
	bezier(c64, nCtrlPts, nBezCurvePts);
	bezier(c65, nCtrlPts, nBezCurvePts);
	bezier(c66, nCtrlPts, nBezCurvePts);
	bezier(c67, nCtrlPts, nBezCurvePts);
	bezier(c68, nCtrlPts, nBezCurvePts);
	bezier(c69, nCtrlPts, nBezCurvePts);
	bezier(c70, nCtrlPts, nBezCurvePts);
	bezier(c71, nCtrlPts, nBezCurvePts);
	bezier(c72, nCtrlPts, nBezCurvePts);
	bezier(c73, nCtrlPts, nBezCurvePts);
	bezier(c74, nCtrlPts, nBezCurvePts);
	bezier(c75, nCtrlPts, nBezCurvePts);
	bezier(c76, nCtrlPts, nBezCurvePts);
	bezier(c77, nCtrlPts, nBezCurvePts);

	glFlush();
}

void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0,0,newHeight,newHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);

	glClear(GL_COLOR_BUFFER_BIT);
}
void ControlMouse(int boton, int edo, int x, int y){
	if ((boton==GLUT_LEFT_BUTTON)&&(edo==GLUT_DOWN))
	{
		/* code */
		xpoint=(float)x/(ANCHO/10);
		ypoint=10-((float)y/(ALTO/10));

		cout << "====x , y=====" << endl;
		cout << xpoint << endl;
		cout << ypoint << endl;
		cout << "==========" << endl;

	}
}
main(int argc, char **argv)
{
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Objeto Curvas Bezier");
	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutMouseFunc(ControlMouse);
	glutMainLoop();
}

