#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define X 1000
#define Y 1000
#define C 10000
// #define X 10
// #define Y 10
// #define C 5

float Cities[C][2];
int arr[C];

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
			//  city[j] = (float)(rand()%X);
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

float totalDistance(){

	int i,j,k;
	float dist;	
	float totaldist = 0.0;
	float current[2] = {Cities[0][0],Cities[0][1]};

    deleteElement(0,0);

	float next[2];
    
    float minDist[2];
    float min_dist;
	int minIndex[2];//DEIKTHS POY KRATAEI TO INDEX TOY MINDIST
	int min_index;
    int p;

	int index_counter = 0;

	while(index_counter<C-1){
		
        minDist[0] = INFINITY;
        minDist[1] = INFINITY;
        minIndex[0] =0;
        minIndex[1] =0;

        for(j=0;j<C-index_counter-1;j++){
            next[0] = Cities[arr[j]][0];
            next[1] = Cities[arr[j]][1];
            dist = EuclDist(current,next);
            // printf("\t\tARR[%d] = %d\tDIST(%f,%f) = %f\n",j,arr[j],current[0],next[0],dist);
            if(dist<minDist[0]){
                minDist[1] = minDist[0];
                minIndex[1] = minIndex[0];
                minDist[0] = dist;
                minIndex[0] = j;
                continue;
            }	
            else if(dist<minDist[1]){
                minDist[1] = dist;
                minIndex[1] = j;
            }
            
        }
    
        p = probability(index_counter);
        min_dist = minDist[p];
        min_index = minIndex[p];
		totaldist+=min_dist;
        
		// printf("\t\tMINDIST = %f\n",min_dist);

		current[0] = Cities[arr[min_index]][0];
		current[1] = Cities[arr[min_index]][1];
		// printf("index_counter = %d\n",index_counter);
		
		index_counter++;
        
		deleteElement(min_index,index_counter);
	}
	
	next[0] = Cities[0][0];
	next[1] = Cities[0][1];
	dist = EuclDist(current,next);
	// printf("\t\tINDEX = %d\tDIST(%f,%f) = %f\n",0,current[0],next[0],dist);
	totaldist+=dist;

	return totaldist;
}

int probability(int counter){
    float a = (rand()%2);
    float p1 = 1 / (a+1);
    float p2 = a / (a+1);

    if(counter==C-2 || p1>p2){
        return 0;
    }
    return 1;

}

void deleteElement(int min,int counter){  //AYTH H SYNARTHSH DIAGRAFEI THN POLH APO TO ARRAY arr
    int i;
    for (i = min; i < C-counter; i++){
        arr[i] = arr[i+1];
    }

}

int main(int argc, char *argv[]) {
	initializeCities();
	// printCities(Cities);
	int i;
    for(i=0;i<C;i++){
		arr[i] = i;
	}

	float totaldist = totalDistance();
	printf("\nTOTALDIST = %f\t\n",totaldist);
	return 0;
}

