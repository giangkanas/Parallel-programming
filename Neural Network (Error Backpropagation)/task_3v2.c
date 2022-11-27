#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline", "unsafe-math-optimizations")
#pragma GCC option("arch=native","tune=native","no-zero-upper")

// gcc erg3v2.c -o erg3v2 -lm -fopt-info-vec-optimized

#define num_train_sets 200
#define epochs 100
#define num_inputs 220
#define num_hidden_nodes 1000
#define num_output_nodes 2


// PARADEIGMA https://mattmazur.com/2015/03/17/a-step-by-step-backpropagation-example/
// #define num_train_sets 1
// #define num_inputs 2
// #define num_hidden_nodes 2
// #define num_output_nodes 2
// double WL1[num_hidden_nodes][num_inputs + 1] = {{0.15f,0.2f,0.35f},{0.25f,0.3f,0.35f}};
// double WL2[num_output_nodes][num_hidden_nodes + 1] = {{0.4f,0.45f,0.6f},{0.5f,0.55f,0.6f}};
// double input[1][num_inputs] = { {0.05f,0.1f} };
// double desired[1][num_inputs] = { {0.01f,0.99f} };


//DIANYSMA EISODOY
double input[num_train_sets][num_inputs];
double desired[num_train_sets][num_output_nodes];

//PINAKES SINAPSEWN (WEIGHTS)
double WL1[num_hidden_nodes][num_inputs + 1];
double WL2[num_output_nodes][num_hidden_nodes + 1];

//PINAKES ESWTERIKHS KATASTASHS
double DL1[num_hidden_nodes]; 
double DL2[num_output_nodes]; 

//PINAKES ME EKSODOYS TWN NEYRWNWN (SE KATHE THESH APOTHIKEYETAI TO ATHROISMA TWN EISODWN EPI TO ANTISTOIXO WEIGHT PLUS THN EXTRA STATHERH TIMH)
double OL1[num_hidden_nodes];
double OL2[num_output_nodes];

double totalError ;

//ACTIVATION FUNCTION
double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}
//KANONTAS TIS PRAKSEIS dSigmoid = exp(-x) / (1 + exp(-x)) . AYTO AN TO APLOPOIHSOYME KATALHGOYME OTI dSigmoid(x) = s(x) / (1-s(x))
double dSigmoid(double x) {
    return x * (1 - x);
}

void activateNN(double *Vector){
    int j;
    //FIRST LAYER
    #pragma omp parallel for
    for (j=0; j<num_hidden_nodes; j++) {
        double activation=WL1[j][num_inputs];
        int k;
        for (k=0; k<num_inputs; k++) {
            activation+=Vector[k]*WL1[j][k];
        }
        DL1[j] = activation;
        OL1[j] = sigmoid(activation);
    }

    //OUTPUT LAYER
    #pragma omp parallel for 
    for (j=0; j<num_output_nodes; j++) {
        double activation=WL2[j][num_hidden_nodes];
        int k;
        // #pragma omp simd 
        for (k=0; k<num_hidden_nodes; k++) {
            activation+=OL1[k]*WL2[j][k];
        }
        DL2[j] = activation;
        OL2[j] = sigmoid(activation);
    }



}

void initializeSystem(){
    int i,j;
    
    for(j=0 ; j<num_train_sets;j++){
        // printf("\nINPUT VECTOR %d\n",j);
        // printf("==================================\n\n");
        for(i=0;i<num_inputs;i++){
            input[j][i] = 2 * ((float)rand() / (float)RAND_MAX - 0.5);
            

            // printf("%f\n",input[j][i]);
        }
    }

    for(j=0 ; j<num_train_sets;j++){
        for(i=0;i<num_output_nodes;i++){
            desired[j][i] = ((float)rand() / (float)RAND_MAX);  //PEDIO TIMWN SIGMOID (0,1)
        }
    }

    //THELEI MIKRA VARH EDW EXV APO 0 EWS 1  
    for(i=0;i<num_hidden_nodes;i++){
        for(j=0;j<num_inputs + 1;j++){
            // WL1[i][j] = ((float)rand() / (float)RAND_MAX);
            WL1[i][j] = 0.025 *((float)rand() / (float)RAND_MAX);  //float x = ((float)rand()/(float)(RAND_MAX)) * a;
            
        }
    }

    for(i=0;i<num_output_nodes;i++){
        
        for(j=0;j<num_hidden_nodes + 1;j++){
            WL2[i][j] = 0.025 * ((float)rand() / (float)RAND_MAX);
            
            
        }
    }
  

}

void print(){
    int i,j;
    // printf("\n\n WL1 \n");
    // printf("==================================\n\n");
    // for(i=0;i<num_hidden_nodes;i++){
    //     for(j=0;j<num_inputs + 1;j++){
    //         printf("%f\t",WL1[i][j]);
    //     }
    //     putchar('\n');
    // }
    // printf("\nDL1\n");
    // printf("==================================\n\n");
    // for (j=0; j<num_hidden_nodes; j++) {
    //     printf("%f\n",DL1[j]);
    // }
    // printf("\nOL1\n");
    // printf("==================================\n\n");
    // for (j=0; j<num_hidden_nodes; j++) {
    //     printf("%f\n",OL1[j]);
    // }
    // printf("\n\n WL2 \n");
    // printf("==================================\n\n");
    // for(i=0;i<num_output_nodes;i++){
    //     for(j=0;j<num_hidden_nodes + 1;j++){
    //         printf("%f\t",WL2[i][j]);
    //     }
    //     putchar('\n');
    // }
    // printf("\nDL2\n");
    // printf("==================================\n\n");
    // for (j=0; j<num_output_nodes; j++) {
    //     printf("%f\n",DL2[j]);
    // }

    printf("\nOL2 SET \n");
    printf("==================================\n\n");
    for (j=0; j<num_output_nodes; j++) {
        printf("%f\n",OL2[j]);
    }


    printf("\nDESIRED SET \n");
    printf("==================================\n\n");
    for (j=0; j<num_inputs; j++) {
        printf("%f\n",desired[0][j]);
    }

}

void trainNN(double *input , double *desired){
    int j,k;
    float lr = 0.1 ; 
   

    // Compute change in output weights
    double deltaOutput[num_output_nodes];

    #pragma omp parallel for reduction(+:totalError)
    for (j=0; j<num_output_nodes; j++) {
        double dError = (desired[j]-OL2[j]);
        totalError+=dError;
        deltaOutput[j] = dError*dSigmoid(OL2[j]);
    }


    // Compute change in hidden weights
    double deltaHidden[num_hidden_nodes];
    #pragma omp parallel for 
    for (j=0; j<num_hidden_nodes; j++) {
        double dError = 0.0f;
        for(int k=0; k<num_output_nodes; k++) {
            dError+=deltaOutput[k]*WL2[k][j];
        }
        deltaHidden[j] = dError*dSigmoid(OL1[j]);
    }

    // Apply change in output weights
    #pragma omp parallel for private(k)
    for (int j=0; j<num_output_nodes; j++) {
        WL2[j][num_hidden_nodes ] += deltaOutput[j]*lr;
        for (k=0; k<num_hidden_nodes; k++) {
            WL2[j][k]+=OL1[k]*deltaOutput[j]*lr;
        }
    }

    // Apply change in hidden weights
    #pragma omp parallel for private(k)
    for (int j=0; j<num_hidden_nodes; j++) {
        WL1[j][num_inputs] += deltaHidden[j]*lr;
        for(int k=0; k<num_inputs; k++) {
            WL1[j][k]+=input[k]*deltaHidden[j]*lr;
        }
    }
}

int main(){ 
    initializeSystem();

    int i,set;
    for(i=0;i<epochs;i++){
        totalError = 0.0;

        for(set=0;set<num_train_sets;set++){
            
            activateNN(input[set]);
            trainNN(input[set],desired[set]);
        }
        printf("\nTotalError : %f\n",totalError/num_train_sets);
    }   

    // activateNN(input[0]);
    // print();
    // trainNN(input[0],desired[0]);
    // print();
    
    return 0;
}