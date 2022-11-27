#include <stdio.h>
#include <stdlib.h>
#define N 10
#define Nv 5
#define Nc 3



float Vec[N][Nv];			
float Center[Nc][Nv];
int Classes[N];



void createVector(void){	
	//TODO...
}


void initiallizeCenters(void){
	//TODO...
}


void Classification(void){
	//TODO...
}


void EstimateCenters(void){
	//TODO...	
}


int Terminate(){
	//TODO...
}

//#######################################################################

int main(int argc, char *argv[]) {
	
	createVector();
	initiallizeCenters();
	
	do{
		Classification();
		EstimateCenters();
	}while(Terminate());
	
	return 0;
}










