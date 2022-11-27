#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 100000
#define Nv 1000
#define Nc 100
#define THR_KMEANS 0.000001

//#######################################################################

//APARAITHTOI PINAKES
float Vec[N][Nv];			
float Center[Nc][Nv];
int Classes[N];

//EPIPROSTHETES METAVLHTES POY XREIAZONTAI
float totalDist =  (float)0.0; //ATHROISTIKH APOSTASH DIANYSMATWN
float totalDist2 =  (float)0.0;//ATHROISTIKH APOSTASH DIANYSMATWN STO EPOMENO BHMA
int loops = 0;//ARITHMOS EPANALIPSEWN ALGORITHMOY

//#######################################################################
//BOHTHITIKES SYNARTHSEIS EKTIPOSHS
void printVec(void){
	int i,j;
	printf("\n\nV E C T O R S\n\n");
	for(i=0;i<N;i++){
		for( j=0;j<Nv;j++){
			printf(" %f ",Vec[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void printCenter(void){
	printf("\n\nC E N T E R S\n\n");
	int i,j;
	for(i=0;i<Nc;i++){
		for(j=0;j<Nv;j++){
			printf(" %f ",Center[i][j]);
		}
		printf("\n");
	}
}

void printClasses(void){
	printf("\n\nC L A S S E S\n\n");
	int i,j;
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
	int i,j;
	for(i=0;i<N;i++){
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

void Classification(void){

	int i,j,k;
	float dist = 0.0;
	float minDist;
	totalDist = 0.0;
	
	for(i=0;i<N;i++){
		
		for(k=0;k<Nc;k++){

			for(j=0;j<Nv;j++){
				dist += (Vec[i][j] - Center[k][j])*(Vec[i][j] - Center[k][j]);
			}
			if(k!=0){
				if(dist<minDist){
					minDist=dist;
					Classes[i] = k;
				}
				//PROSOXH OTAN EINAI ISES OI APOSTASEIS PREPEI NA DIALEGETAI TYXAIA H KLASH STHN OPOIA THA MPEI KAI OXI NA DIATHREI AYTH POY EXEI HDH
//				else if(dist == minDist){
//					if(rand()%2 == 1){  //PARAGO TYXAIA 0 KAI 1.AN VGEI 0 DEN ALLAZEI H KLASH ALLIWS ALLAZEI
//						minDist=dist;
//						Classes[i] = k;
//					}
//				}
			}
			else{
				minDist=dist;
				Classes[i]=k;
			}
			dist = 0.0;
		}
		totalDist += minDist;
	}
	
}

//4. SYNARTHSH POY YPOLOGIZEI TA NEA KENTRA

void EstimateCenters(void){

	int i,j,k;
	int count=0;
	memset(Center, 0,sizeof(Center)); 
	//##############
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
	
	createVector();
	initiallizeCenters();
	
	do{
		Classification();
		EstimateCenters();
		loops++;
		// printf("loops = %d\t| totalDist2 - totalDist =%f \n",loops,fabs(totalDist2 - totalDist));
	}while(Terminate());
	
	printf("\n\n T O T A L  L O O P S  =  %d\n",loops);

	return 0;
	
}












