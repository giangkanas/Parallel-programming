#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define X 1000
#define Y 1000
#define C 1000
#define ants 1000
#define iterations 1 //GIA PERISSOTERES EPANALHPSEIS VGAINEI KALYTERO APOTELESMA ALLA EINAI PIO XRONOVORO

// #define X 10
// #define Y 10
// #define C 5

float Cities[C][2];
int arr[C];
float pheromone[C][C];

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

float totalDistance(int index){//EDW AFOY VRW THN PITHANOTHTA GIA KATHE EPOMENH POLH EPILEGW THN MEGALYTERH POLH APOFEVGWNTAS OYSIASTIKA
//TIS XRONOVORES DIADIKASIES ME DIAIRESEIS ME TON PARANOMASTH KATHWS KAI THN XRONOBORA DIADIKASIA THS ROULETAS

	int initial = index;
	float dist;	
	float totaldist = 0.0;
	float current[2] = {Cities[index][0],Cities[index][1]};
    // printf("\n=======================================\n");
    // printf("CURRENT = %d\n\n",index);
	float next[2];	
	int index_counter = 0,j,i;
    for(i=0;i<C;i++){
		arr[i] = i;
	}
    deleteElement(index,0);
	while(index_counter<C-1){
        float max_prop = 0.0;
        float best_dist;
        float Probabilistic;
        int best_index;
		for(j=0;j<C-index_counter-1;j++){
            // printf("%d\t\t",arr[j]);
			next[0] = Cities[arr[j]][0];
			next[1] = Cities[arr[j]][1];
			dist = EuclDist(current,next);
            float t = pheromone[index][arr[j]];
            float h = 1/dist;           
            Probabilistic = t*h;

            if(Probabilistic>max_prop){
                max_prop = Probabilistic;
                best_dist = dist;
                best_index = j;
            }
            
		}      

        // putchar('\n');

        totaldist+=best_dist;
        pheromone[index][arr[best_index]] += 1 / best_dist;
		current[0] = Cities[arr[best_index]][0];
		current[1] = Cities[arr[best_index]][1];
		index_counter++;
        // printf("NEXT = %d\n",arr[best_index]);
        // printf("\n=======================================\n");
        // printf("CURRENT = %d\n\n",arr[best_index]);
        deleteElement(best_index,index_counter);
		index = arr[best_index];
	}
	
	next[0] = Cities[index][0];
	next[1] = Cities[index][1];
	dist = EuclDist(current,next);
	pheromone[index][initial] += 1 / dist;
	
	totaldist+=dist;

	return totaldist;
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
    memset(pheromone,1.0,sizeof(pheromone));

    int i,j;
    for(j=0;j<iterations;j++){
        for(i=0;i<ants;i++){
            // printf("ANT = %d\n",i);
            float totaldist = totalDistance(i);
            
        }
    }
    float totaldist = totalDistance(0);
	printf("\nTOTALDIST = %f\t\n",totaldist);
	return 0;
}

