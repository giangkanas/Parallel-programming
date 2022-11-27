#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define X 1000
#define Y 1000
#define C 10000
//#define X 10
//#define Y 10
//#define C 5

float Cities[C][2];

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

float EuclDist(float current[2] , float next[2]){//SYNARTHSH POY YPOLOGIZEI THN EYCLEIDIA APOSTASH METAKSI 2 POLEWN
	int j;
	float dist=0.0; 
	float dx;
	for(j=0;j<2;j++){
		dx = next[j] - current[j];
		dist += dx*dx;
	}
	return dist;
	
}

int isVisited(int val , int arr[C], int counter){//SYNARTHSH POY ELEGXEI AN H TIMH VAL BRISKETAI MESA STON ARRAY TOY ORISMATOS
	int k;
	for(k=0;k<counter;k++){
		if(val == arr[k]){
			return 1;
		}		
	}
	return 0;
}

float totalDistance(){//STH SYGKEKRIMENH EKDOSH ELEGXW GIA KATHE POLH POY BRISKOMAI OLES TIS ALLES POLEIS GIA TO AN VRISKONTAI STO PINAKA POY PERILAMVBANEI
//TIS POLEIS OPY EXW EPISKEFTEI PRAGMA POY APOTELESMA FAINETAI POLLY XRONOBORO
	
	int i,j,k;
	float minDist,dist;	
	float totaldist = 0.0;
	float current[2] = {Cities[0][0],Cities[0][1]};
	float next[2];
	int min_index;//DEIKTHS POY KRATAEI TO INDEX TOY MINDIST
	int index[C];
	memset(index, 0,sizeof(index)); 
	int index_counter = 1;
	
	int visited;//METAVLHTH POY ELEGXW AN EXEI GINEI EPISKEPSH SE AYTHN THN POLH MESW THS TIMHS POY EPISTREFEI H SYNARTHS isVisited
	
	
	for(i=0;i<C-1;i++){
//		printf("index[%d]=%d\n",i,index[i]);
		minDist = INFINITY;
		for(j=1;j<C;j++){//EDW TIS ELEGXV OLES TIS ALLES
			visited = isVisited(j,index,index_counter);
			if(visited==0){
				next[0] = Cities[j][0];
				next[1] = Cities[j][1];
				dist = EuclDist(current,next);
//				printf("\t\tINDEX = %d\tDIST(%f,%f) = %f\n",j,current[0],next[0],dist);
				if(dist<minDist){
					minDist = dist;
					min_index = j;
				}	
			}
			
		}
		
//		printf("\t\tMINDIST = %f\n",minDist);
		totaldist+=minDist;
		
		current[0] = Cities[min_index][0];
		current[1] = Cities[min_index][1];
		index[i+1] = min_index;
		index_counter++;

	}
	next[0] = Cities[0][0];
	next[1] = Cities[0][1];
	dist = EuclDist(current,next);
//	printf("\t\tINDEX = %d\tDIST(%f,%f) = %f\n",0,current[0],next[0],dist);
	totaldist+=dist;

	return totaldist;
}

int main(int argc, char *argv[]) {
	initializeCities();
//	printCities(Cities);
	float totaldist = totalDistance();
	printf("\nTOTALDIST = %f\t\n",totaldist);
	return 0;
}
