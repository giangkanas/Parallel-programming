#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define X 1000
#define Y 1000
#define C 10000
// #define X 10
// #define Y 10
// #define C 5

float Cities[C][2]; //PINAKAS ME SYNTETAGMENES x,y KATHE POLHS
int randIndex[2]; //PINAKAS STON OPOIO MPAINOYN OI DYO THESEIS TIS OPOIES DOKIMAZW NA ALLAKSW


void printCities(float arr[C][2]){//TYPWNEI TO PERIEXOMENO TOY PINAKA CITIES
	int i,j;
	for(i =0 ; i<C;i++){
		for(j=0;j<2;j++){
			printf("%f\t",arr[i][j]);
		}
		printf("\n");
	}
}
 
void initializeCities(){//AXIKOPOIEI TON PINAKA CITIES ME TYXAIES SYNTETAGMENES
	int i,j;
	for(i=0;i<C;i++){
		float * city = Cities[i];
		for(j=0;j<2;j++){
			city[j] = X * (float)rand() / (float)RAND_MAX ;
			// city[j] = (float)(rand()%X);
		}
	}
}

void randomSelect(){//TYXAIA EPILOGH 2 SHMEIWN POY THA ALLAKSOYN METAKSI TOYS KAI TOPOTHETHSH TOYS STO randindex
	int i,j;
	
	int c1 = (rand() % (C-1)) + 1;
	int c2 = (rand() % (C-1)) + 1;
	while(c1==c2){
		c2 = (rand() % (C-1)) + 1;
	}
	
	randIndex[0] = c1;
	randIndex[1] = c2;
}
	
float EuclDist(float current[2] , float next[2]){//SYNARTHSH POY YPOLOGIZEI THN EYCLEIDIA APOSTASH METAKSI 2 POLEWN
//EDV GINETAI NA YPARKSEI PARALLHLOPOIHSH OMWS AYTH EPIBRADINEI TO PROGRAMMA
	int j;
	float dist=0.0; 
	float dx;
    // #pragma omp parallel for reduction(+:dist)
	for(j=0;j<2;j++){
		dx = next[j] - current[j];
		dist += dx*dx;
	}
	return dist;
	
}

float totalDistance(){//YPOLOGIZEI THN SYNOLIKH APOSTASH GIA ENA PATH
//AYTH H SYNARTHSH LOGW TOY MEGALWN CRITICAL SECTION POY EXEI EINAI KATA BASH SEIRIAKH PRAGMA POY FAINETAI
//STHN PARALLHLOPOIHSH SE SXESH ME THN ERG1 OPOY EINAI PIO ARGH	
	int i,j;
	float totaldist = 0.0;
	
	float current[2] = {Cities[0][0],Cities[0][1]};
	float next[2];

	float dist;
	
	int c1 = randIndex[0];
	int c2 = randIndex[1];
	
	#pragma omp parallel for num_threads(2) reduction(+:totaldist)
	for(i=1;i<C;i++){
		#pragma omp critical
		{if(i!=c1 && i!=c2){
			next[0] = Cities[i][0];
			next[1] = Cities[i][1];
			dist = EuclDist(current,next);
			current[0] = Cities[i][0];
			current[1] = Cities[i][1];
		}
		else if(i==c1){//AN TO I EINAI ISO ME c1 DHLADH EINAI AYTO POY PREPEI NA ALLAKSEI TOTE TO NEXT KAI STHN SYNEXEIA TO CURRENT THA PAREI THN TIMH POY BRISKETAI STH THESH c2 
			next[0] = Cities[c2][0];
			next[1] = Cities[c2][1];
			dist = EuclDist(current,next);
			current[0] = Cities[c2][0];
			current[1] = Cities[c2][1];
		}
		else if(i==c2){
			next[0] = Cities[c1][0];
			next[1] = Cities[c1][1];
			dist = EuclDist(current,next);
			current[0] = Cities[c1][0];
			current[1] = Cities[c1][1];
		}}
		totaldist += dist;
		
	}	
	next[0] = Cities[0][0];	//DEN PREPEI NA KSEXASO OTI H POLH TERMATISMOY EINAI H POLH EKKINHSH KAI OXI H TELEYTAIA TOY PINAKA CITIES
	next[1] = Cities[0][1];	
	dist = EuclDist(current,next);
	totaldist += dist;
	
	return totaldist;
}

float checkDist(float dist1 , float dist2){ //EDO SYGKRINW THN TREXOYSA SYNOLIKH APOSTASH ME THN PROHGOYMENH. AN EINAI MIKROTERH ENALLASW TIS THESEIS TOY PINAKA CITIES
	if(dist2<dist1){		
		int i,j;
		int ind1 = randIndex[0];
		int ind2 = randIndex[1];
		float c1[2] = {Cities[ind1][0], Cities[ind1][1]};
		float c2[2] = {Cities[ind2][0], Cities[ind2][1]};
		

		for(i=0;i<C;i++){
			for(j=0;j<2;j++){
				if(i==ind1){
					Cities[i][j] = c2[j];
				}
				else if(i==ind2){
					Cities[i][j] = c1[j];
				}
			}
		}
		dist1 = dist2;
	}
	return dist1;
}


int main(int argc, char *argv[]) {
	// omp_set_num_threads(2); //EFOSON PARALLHLOPOIHSA THN EUCLDIST POY EINAI ENA FOR LOOP 2 EPANALIPSEWN DIALEKSA NA XRHSIMOPOIW 2 THREADS GIATI ALLIWS EINAI PIO ARGO
	initializeCities();
		
	float totaldist = totalDistance();
	int iterations=0;
	// printCities(Cities);
	// printf("\nINITIALDIST = %f\t\n\n",totaldist);
	do{
		
		randomSelect();
		float totaldist2 = totalDistance();
		totaldist = checkDist(totaldist,totaldist2);
		iterations++;
		
	}while(iterations<100000);

    // printCities(Cities);
	printf("\nTOTALDISTANCE = %f\t\n",totaldist);
	
	
	
	return 0;
}







