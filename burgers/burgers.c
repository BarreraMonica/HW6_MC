#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float **reserva(int puntos_x,int puntos_y);
void print_matriz(float **matriz, int puntos_x, int puntos_y);
void liberar(float **matriz, int xpoints);
void copy(float **origen, float **destino, int puntos_x,int puntos_y);


void set_initial(float **array, int puntos_x, int puntos_y , float delta_x, float delta_y);
void iteration(float **u, float **v ,float **u_past, float **v_past, int puntos_x, int puntos_y, float dx, float dy, float dt, float nu );


int main(){
	
	//Condiciones del problema
	int xpoints=41;
	int ypoints=41;
	int ntime=500;
	float c = 1.0;
	float dx = 2.0/(xpoints -1);
	float dy = 2.0/(ypoints -1);
	float sigma = 0.0009;
	float nu = 0.01;
	float dt=sigma*dx*dy/nu;
	
	//Variables de recorrido
	int i;
	int j;
	
	//Generacion de las matrices
	float **u;
	float **v;
	float **u_past;
	float **v_past;
	
	u=reserva(xpoints,ypoints);
	v=reserva(xpoints,ypoints);
	u_past=reserva(xpoints,ypoints);
	v_past=reserva(xpoints,ypoints);
	
	set_initial(u, xpoints,ypoints, dx,dy);
	set_initial(v, xpoints,ypoints, dx,dy);
	
	//Iteraciones
	int t;
	for(t=0;t<ntime;t++){
		print_matriz(u, xpoints,ypoints);
		print_matriz(v, xpoints,ypoints);
		copy(u,u_past,xpoints,ypoints);
		copy(v,v_past,xpoints,ypoints);
		iteration(u, v ,u_past,v_past, xpoints,ypoints, dx, dy, dt,nu );
	}
	
	liberar(u, xpoints);
	liberar(v, xpoints);
	liberar(u_past, xpoints);
	liberar(v_past, xpoints);
	
	return 0;
}

//ITERACIONES
void iteration(float **u, float **v ,float **u_past, float **v_past, int puntos_x, int puntos_y, float dx, float dy, float dt, float nu ){
  int i;
  int j;
  
  for(i=1;i<(puntos_x-1);i++){
	  for(j=1;j<puntos_y-1;j++){
			u[i][j] = u_past[i][j] 
			-(dt/dx)*u_past[i][j]*(u_past[i][j]-u_past[i-1][j])
			-(dt/dy)*v_past[i][j]*(u_past[i][j]-u_past[i][j-1])
			+nu*dt/(pow(dx,2.0))*(u_past[i+1][j]-2*u_past[i][j]+u_past[i-1][j])+ 
			nu*dt/(pow(dy,2.0))*(u_past[i][j+1]-2*u_past[i][j]+u_past[i][j+1]);    
			
			v[i][j] = v_past[i][j] 
			-(dt/dx)*u_past[i][j]*(v_past[i][j]-v_past[i-1][j])
			-(dt/dy)*v_past[i][j]*(v_past[i][j]-v_past[i][j-1])
			+nu*dt/(pow(dx,2.0))*(v_past[i+1][j]-2*v_past[i][j]+v_past[i-1][j])+ 
			nu*dt/(pow(dy,2.0))*(v_past[i][j+1]-2*v_past[i][j]+v_past[i][j+1]);    
	}
  }
}

//INICIAL
void set_initial(float **array, int puntos_x, int puntos_y , float delta_x, float delta_y){
  int i;
  int j;
  float x;
  float y;
  
  for(i=0;i<puntos_x;i++){
    x = i * delta_x;
    for(j=0;j<puntos_y;j++){
		y = j * delta_y;
		if( (0.5 <= x && x<=1) && (0.5 <= y && y<=1)){
			array[i][j] = 2.0;
	}
	}
  }
}

//COPY
void copy(float **origen, float **destino, int puntos_x,int puntos_y){
  int i;
  int j;
  for(i=0;i<puntos_x;i++){
	  for(j=0;j<puntos_y;j++){
		  destino[i][j] = origen[i][j];
	  }
  }
}

//LIBERAR
void liberar(float **matriz, int xpoints){
	int i;
	for(i=0;i<xpoints;i++){
		free(matriz[i]);
	}
	free(matriz);
}

//PRINT
void print_matriz(float **matriz, int puntos_x, int puntos_y){
  int i;
  int j;
  for(i=0;i<puntos_x;i++){
	  for(j=0;j<puntos_y;j++){
		  printf("\t%f ", matriz[i][j]);
	  }
	  printf("\n");
  }
}

float **reserva(int puntos_x,int puntos_y){
  float **matriz;
  int i;
  int j;
  
  matriz = (float **)malloc(puntos_x*sizeof(float*));
  
  for(i=0;i<puntos_x;i++){
    matriz[i] = (float *)malloc(puntos_y * sizeof(float));
  }
  
  int i2;
  for(i2=0; i2<puntos_x;i2++){
	  for (j=0;j<puntos_y;j++){
		  matriz[i2][j]=1.0;
	  }
  }
  return matriz;
}
