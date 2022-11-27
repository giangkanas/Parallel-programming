#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#define N 100000
#define Nv 1000
#define Nc 100
// #define N 5
// #define Nv 2
// #define Nc 2
// #define N 6
// #define Nv 6
// #define Nc 2
#define THR_KMEANS 0.000001

//#######################################################################

//APARAITHTOI PINAKES
float Vec[N][Nv];			
float Center[Nc][Nv];
int Classes[N];

// float Vec[N][Nv] = {{1,1},{1,0},{0,1},{0,2},{1,2}};
// float Center[Nc][Nv] ={{1,1},{1,2}};
// int Classes[N];

// float Vec[N][Nv] = { {1,1}, {2,1}, {2,2}, {9,9}, {9,10}, {10,9} };
// float Center[Nc][Nv] = { {2,1}, {2,2} };
// int Classes[N];

//EPIPROSTHETES METAVLHTES POY XREIAZONTAI
float totalDist =  (float)0.0; //ATHROISTIKH APOSTASH DIANYSMATWN
float totalDist2 =  (float)0.0;//ATHROISTIKH APOSTASH DIANYSMATWN STO EPOMENO BHMA
int loops = 0;//ARITHMOS EPANALIPSEWN ALGORITHMOY

//#######################################################################
//BOHTHITIKES SYNARTHSEIS EKTIPOSHS
void printVec(void){
	// int i,j;
    int i;
	printf("\n\nV E C T O R S\n\n");
	for(i=0;i<N;i++){
        int j;
		for( j=0;j<Nv;j++){
			printf(" %f ",Vec[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void printCenter(void){
	printf("\n\nC E N T E R S\n\n");
	// int i,j;
    int i;
	for(i=0;i<Nc;i++){
        int j;
		for(j=0;j<Nv;j++){
			printf(" %f ",Center[i][j]);
		}
		printf("\n");
	}
}

void printClasses(void){
	printf("\n\nC L A S S E S\n\n");
    int i;
	for(i=0;i<N;i++){
		printf(" %d ",Classes[i]);
		printf("\n");
	}
}


//#######################################################################
//BASIKES SYNARTHSEIS

//1. SYNARTHSH ARXIKOPOIHSHS DEDOMENWN
void createVector(void){
	
	//TYXAIA DIANYSMATA
	// int i,j;
    int i;
	for(i=0;i<N;i++){
        int j;
		for(j=0;j<Nv;j++){
			Vec[i][j]= 4*( (float)rand()/((float)RAND_MAX) - 0.5) ;
		}
	}
	
}

//2. SYNARTHSH ARXIKOPOIHSHS KENTRWN

void initiallizeCenters(void){
	
	//TYXAIA ARXIKA KENTRA
	memcpy(Center, Vec, sizeof(Center)); // PAIRNEI TA PRWTA sizeof(Center) DIANYSMATA TOY Vec KAI TA BAZEI STON PINAKA Center
		
}

//3. SYNARTHSH POY KANEI THN KANONIKOPOIHSH

static inline float EuclDist(float *V , float *C){
	int j;
	float dist=0.0;
	
	// #pragma omp parallel for reduction(+:dist) //DEN PARALLHLOPOIW THN EUCL DIST GIATI APO THN PROHGOYMENH EKDOSH FANHKE NA EPIVRADINEI TO PROGRAMMA
	for(j=0;j<Nv;j++){							
		float dx = V[j] - C[j];
		dist += dx*dx;
		
	}

	
    
	return dist;
}

void Classification(void){

	totalDist = 0.0;
	
	#pragma omp parallel for reduction(+:totalDist)//EDW PROSPATHW NA PARALLHLOPOIHSW THN SYNARTHSH MESA STHN OPOIA KALEITAI H EuclDist GIA NA DW AN YPARKSEI VELTIWSH
	for(int i=0;i<N;i++){						
		float minDist = INFINITY;
		float *vector = Vec[i];
		
		#pragma omp parallel for //EDW PARALLHLOPOIW KAI DEYTERO LOOP MESA STHN CLASSIFICATION STO OPOIO KALEITAI H EUCLDIST KAI VLEPW OTI KATHISTEREI SE SXESH ME THN 
		for(int k=0;k<Nc;k++){	//PROOHGOYMENH EKDOSH
			
			float *center = Center[k];
			float dist = EuclDist(vector,center);
			#pragma omp critical 	//EDW EXW CRITICAL SECTION. EAN DEN TO VALW XALAEI TO APOTELESMA TOY ALGORITHMOY
			{
				if(dist<minDist){
					minDist=dist;
					Classes[i] = k;
				}
			}
			

		}
		totalDist += minDist;
	}
	
}


//4. SYNARTHSH POY YPOLOGIZEI TA NEA KENTRA

void EstimateCenters(void){

	int i,j,k;
	int count=0;
	memset(Center, 0,sizeof(Center)); 

	for(k=0;k<Nc;k++){
		for(i=0;i<N;i++){
			
			if(Classes[i]==k){
				count++;
				for(j=0;j<Nv;j++){
					Center[k][j] += Vec[i][j];
				}	
			}
		}
		if(count!=0){
			for(j=0;j<Nv;j++){
				Center[k][j] = Center[k][j]/((float)count);
			}	
		}
		
		
		count=0;
	}
	
	
	
}

//5. SYNARTHSH POY TERMATIZEI TON ALGORITHMO

int Terminate(){
	printf("LOOP = %d\ttotalDistance = %f\ttotalDist2 - totalDist =%f \n",loops,totalDist,fabs(totalDist2 - totalDist));
	if (fabs(totalDist2 - totalDist) <= THR_KMEANS){
		return 0;
	}
	else{
		totalDist2 = totalDist;
		return 1;
	}
	
}



//#######################################################################

int main(int argc, char *argv[]) {
	
	omp_set_num_threads(omp_get_max_threads());

	createVector();
	initiallizeCenters();
	
	do{
		if(loops>15)break;
		Classification();
		EstimateCenters();
        loops++;
	}while(Terminate());
	
	// printCenter();
	return 0;
}












