#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// #define num_inputs 12
// #define num_hidden_nodes 100
// #define num_output_nodes 10

// PARADEIGMA https://mattmazur.com/2015/03/17/a-step-by-step-backpropagation-example/
#define num_inputs 2
#define num_hidden_nodes 2
#define num_output_nodes 2
double WL1[num_hidden_nodes][num_inputs + 1] = {{0.15f,0.2f,0.35f},{0.25f,0.3f,0.35f}};
double WL2[num_output_nodes][num_hidden_nodes + 1] = {{0.4f,0.45f,0.6f},{0.5f,0.55f,0.6f}};
double input[1][num_inputs] = { {0.05f,0.1f} };
double desired[1][num_output_nodes] = { {0.01f,0.99f} };


// //DIANYSMA EISODOY
// double input[num_inputs];

// //PINAKES SINAPSEWN (WEIGHTS)
// double WL1[num_hidden_nodes][num_inputs + 1];
// double WL2[num_output_nodes][num_hidden_nodes + 1];

//PINAKES ESWTERIKHS KATASTASHS
double DL1[num_hidden_nodes]; 
double DL2[num_output_nodes]; 

//PINAKES ME EKSODOYS TWN NEYRWNWN (SE KATHE THESH APOTHIKEYETAI TO ATHROISMA TWN EISODWN EPI TO ANTISTOIXO WEIGHT PLUS THN EXTRA STATHERH TIMH)
double OL1[num_hidden_nodes];
double OL2[num_output_nodes];

//ACTIVATION FUNCTION
double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

void activateNN(double *Vector){
    int j,k;
    //FIRST LAYER
    for (j=0; j<num_hidden_nodes; j++) {
        double activation=WL1[j][num_inputs];
        for (k=0; k<num_inputs; k++) {
            activation+=Vector[k]*WL1[j][k];
        }
        DL1[j] = activation;
        OL1[j] = sigmoid(activation);
    }

    

    //OUTPUT LAYER
    for (j=0; j<num_output_nodes; j++) {
        double activation=WL2[j][num_hidden_nodes];
        for (k=0; k<num_hidden_nodes; k++) {
            activation+=OL1[k]*WL2[j][k];
        }
        DL2[j] = activation;
        OL2[j] = sigmoid(activation);
    }



}

void initializeSystem(){
    int i,j;
    printf("\nINPUT VECTOR\n");
    printf("==================================\n\n");
    for(i=0;i<num_inputs;i++){
        input[0][i] = ((float)rand() / (float)RAND_MAX - 0.5);
        printf("%f\n",input[0][i]);
    }

    
    for(i=0;i<num_hidden_nodes;i++){
        for(j=0;j<num_inputs + 1;j++){
            WL1[i][j] = 0.1 * ((float)rand() / (float)RAND_MAX);
        }
    }

    for(i=0;i<num_output_nodes;i++){
        for(j=0;j<num_hidden_nodes + 1;j++){
            WL2[i][j] = 0.1 * ((float)rand() / (float)RAND_MAX);
        }
    }
  

}

void print(){
    int i,j;
    printf("\n\n WL1 \n");
    printf("==================================\n\n");
    for(i=0;i<num_hidden_nodes;i++){
        for(j=0;j<num_inputs + 1;j++){
            printf("%f\t",WL1[i][j]);
        }
        putchar('\n');
    }
    printf("\nDL1\n");
    printf("==================================\n\n");
    for (j=0; j<num_hidden_nodes; j++) {
        printf("%f\n",DL1[j]);
    }
    printf("\nOL1\n");
    printf("==================================\n\n");
    for (j=0; j<num_hidden_nodes; j++) {
        printf("%f\n",OL1[j]);
    }
    printf("\n\n WL2 \n");
    printf("==================================\n\n");
    for(i=0;i<num_output_nodes;i++){
        for(j=0;j<num_hidden_nodes + 1;j++){
            printf("%f\t",WL2[i][j]);
        }
        putchar('\n');
    }
    printf("\nDL2\n");
    printf("==================================\n\n");
    for (j=0; j<num_output_nodes; j++) {
        printf("%f\n",DL2[j]);
    }

    printf("\nOL2\n");
    printf("==================================\n\n");
    for (j=0; j<num_output_nodes; j++) {
        printf("%f\n",OL2[j]);
    }
}


int main(){
    
    // initializeSystem();
    activateNN(input);
    print();

    return 0;
}