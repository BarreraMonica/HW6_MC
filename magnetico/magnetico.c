#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define USAGE "./particle_in_field kinetic_energy alpha"


void print_array(float *array);
void campo(float *b[3], float pos[3], float rt);
void fuerza(float *f[3],float v[3] , float b[3], float q);
void aceleracion(float *a[3], float pos[3], float vel[3] , float m, float gamma,float q, float rt);
void rg4th(float *pyv[6], float pos[3], float vel[3], float m, float gamma,float q, float rt);

int main(int argc, char **argv){
	
	//Condiciones iniciales
	float n_time=100;
	float momento;	
	momento=938.272*1.602*pow(10.0,-19)*pow(10,6.0); 
	float c;
	c=2.998*pow(10.0,8.0);
	float m;
	m=momento/pow(c,2.0);
	float rt;
	rt=6378.1*pow(10.0,3.0);
	float q;
	q=1.602*pow(10.0,-19.0);
	
	float pos[3];
	pos[0]=2.0*rt;
	pos[1]=0.0;
	pos[2]=0.0;
	
	//VALOR QUE ENTRA:
	float kinetic_energy=atof(argv[1]);
	float alpha=atof(argv[2]);
	float v;
	float k;
	k=kinetic_energy*(10*6)*1.602*pow(10.0,-19.0);
	v=c*sqrt(1-1/(pow(k/(m*pow(c,2.0))+1,2.0)));
	
	float vel[3];
	vel[0]=0.0;
	vel[1]=v*sin(alpha);
	vel[2]=v*cos(alpha);
		
	float gamma;
	gamma = 1/(sqrt(1-(pow(vel[0],2.0)+pow(vel[1],2.0)+pow(vel[2],2.0))/pow(c,2.0)));
	

	
	//Iteraciones
	int t;
	for(t=0;t<n_time;t++){
		print_array(pos);
		int p;
		float *temp[6];
		int tm;
		for(tm=0;tm<6;tm++){
			rg4th(temp,pos,vel,m, gamma,q,rt);
			for(p=0;p<3;p++){
				pos[p]=*temp[p];
				vel[p]=*temp[p+3];
			}
		}
	}

	return 0;
}


//PRINT
void print_array(float array[3]){
  printf("%f %f %f \n", array[0], array[1], array[2]);
}

void rg4th(float *pyv[6], float pos[3], float vel[3], float m, float gamma,float q, float rt){
    int i;
	
	float v1[3];
	float r1[3];
	float v2[3];
	float r2[3];
	float v3[3];
	float r3[3];
	
    float *ace1[3];
    float *ace2[3];
    float *ace3[3];
    float *ace4[3];
    
    aceleracion(ace1, pos, vel , m, gamma,q,  rt);
  
    //second step
    for(i=0;i<3;i++){
		v1[i]= vel[i] + *ace1[i]/2;
		r1[i] = pos[i] + vel[i]/2;
	}
    aceleracion(ace2, r1, v1 , m, gamma,q,  rt);
  
    //third
    for(i=0;i<3;i++){
		v2[i]= vel[i] + *ace2[i]/2;
		r2[i] = pos[i] + v1[i]/2;
	}
	aceleracion(ace3, r2, v2 , m, gamma,q,  rt);
     
    //fourth step
    for(i=0;i<3;i++){
		v3[i]= vel[i] + *ace3[i];
		r3[i] = pos[i] + v2[i];
	}
	aceleracion(ace4, r3, v3 , m, gamma,q,  rt);
    
    //Average
	float va[3];
	float ra[3];
	for(i=0; i<3;i++){
		va[i] = (1.0/6.0)*(*ace1[i] + 2.0*  (*ace2[i]) + 2.0*(*ace3[i]) + *ace4[i]);
		ra[i] = (1.0/6.0)*(vel[i] + 2.0*(v1[i]) + 2.0*(v2[i]) + v3[i]);
	}
	
    *pyv[0] = pos[0] + ra[0];
    *pyv[1] = pos[1] + ra[1];
    *pyv[2] = pos[2] + ra[2];
    *pyv[3] = vel[0] + va[0];
    *pyv[4] = vel[1] + va[1];
    *pyv[5] = vel[2] + va[2];
    
}

//ACELERACION
void aceleracion(float *a[3], float pos[3], float vel[3] , float m, float gamma,float q, float rt){
    float *b[3];
    float cste;
    float *fue[3];
    campo(b,pos,rt);
    cste=1.0/(m*gamma);
    fuerza(fue,vel,*b,q);
    
    *a[0]=*fue[0]*cste;
    *a[1]=*fue[1]*cste;
    *a[2]=*fue[2]*cste;
}

//FUERZA
void fuerza(float *f[3],float v[3] , float b[3], float q){
    *f[0]=q*(v[1]*b[2]-v[2]*b[1]);
    *f[1]=q*(v[2]*b[0]-v[0]*b[2]);
    *f[2]=q*(v[0]*b[1]-v[1]*b[0]);
}

//CAMPO
void campo(float *b[3], float pos[3], float rt){
	float b0;
	float cste;
    b0=3*pow(10.0,-5.0);
    cste = -b0*pow(rt,3.0)/pow(pow(pos[0],2.0)+pow(pos[1],2.0)+pow(pos[2],2.0),5.0/2.0);
    *b[0] = cste*3.0*pos[0]*pos[2];
    *b[1] = cste*3.0*pos[1]*pos[2];
    *b[2] = cste*(2.0*pow(pos[2],2.0)-pow(pos[0],2.0)-pow(pos[1],2.0));
}
