#define _GNU_SOURCE
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline", "unsafe-math-optimizations")
#pragma GCC option("arch=native","tune=native","no-zero-upper")

// gcc erg4v2.c -o erg4v2 -lm -fopt-info-vec-optimized

#define num_train_sets 60000
#define num_test_sets 10000
#define epochs 1
#define num_inputs 784
#define num_hidden_nodes 100
#define num_output_nodes 10
#define times 6000000

// PARADEIGMA https://mattmazur.com/2015/03/17/a-step-by-step-backpropagation-example/
// #define num_train_sets 1
// #define num_inputs 2
// #define num_hidden_nodes 2
// #define num_output_nodes 3
// double WL1[num_hidden_nodes][num_inputs + 1] = {{0.15f,0.2f,0.35f},{0.25f,0.3f,0.35f}};
// double WL2[num_output_nodes][num_hidden_nodes + 1] = {{0.4f,0.45f,0.6f},{0.5f,0.55f,0.6f}};
// double input[1][num_inputs] = { {0.05f,0.1f} };
// double desired[1][num_output_nodes] = { {0.0f,0.0f, 1.0} };



//DIANYSMA EISODOY
double input[num_train_sets][num_inputs];
double desired2[num_train_sets][num_output_nodes];

// PINAKES GIA TESTING
double test[num_test_sets][num_inputs];
double desired[num_test_sets][num_output_nodes];

int predictions[num_test_sets];
int realClass[num_test_sets];

int realClass2[num_train_sets];
int predictions2[num_train_sets];



//PINAKES SINAPSEWN (WEIGHTS)
double WL1[num_hidden_nodes][num_inputs + 1];
double WL2[num_output_nodes][num_hidden_nodes + 1];

//PINAKES ESWTERIKHS KATASTASHS
double DL1[num_hidden_nodes]; 
double DL2[num_output_nodes]; 

//PINAKES ME EKSODOYS TWN NEYRWNWN (SE KATHE THESH APOTHIKEYETAI TO ATHROISMA TWN EISODWN EPI TO ANTISTOIXO WEIGHT PLUS THN EXTRA STATHERH TIMH)
double OL1[num_hidden_nodes];
double OL2[num_output_nodes];

double totalError,setError;
static int correct=0;

//ACTIVATION FUNCTIONS
// ======================================================
double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}
//KANONTAS TIS PRAKSEIS dSigmoid = exp(-x) / (1 + exp(-x)) . AYTO AN TO APLOPOIHSOYME KATALHGOYME OTI dSigmoid(x) = s(x) / (1-s(x))
double dSigmoid(double x) {
    return x * (1 - x);
}

double Relu(double x){
    if(x>0)return x;
    else return 0;
}

double dRelu(double x){
    if(x>0)return 1;
    else return 0;
}

// EFOSON EXOYME ENA PROBLHMA CLASSIFICATION ME POLLES KLASEIS ENDEIKNYTAI STO OUTPUT LAYER NA VALOYME THN SOFTMAX H OPOIA EXEI EKSODOYS APO 0 EWS 1 KAI VGAZOYN
// ATHROISMA ISO ME 1. ETSI THA MILAME THEWRHTIKA GIA PRAGMATIKES PITHANOTHTES
static void softmax(double *input, size_t len , double *output) {
    
    int i=0;
    double sum=0.0;
    for(i=0;i<len;i++){
        sum+=exp(input[i]);
    }

    for(i=0;i<len;i++){
        double ar = exp(input[i]);
        output[i] = ar / sum;
    }

}

// ======================================================

// FORWARD
void activateNN(double *Vector){
    int j;
    //FIRST LAYER
    // PROTIMISA THN sigmoid APO THN relu GIA activation STO PRWTO LAYER

    for (j=0; j<num_hidden_nodes; j++) {
        double activation=WL1[j][num_inputs];
        int k;
        for (k=0; k<num_inputs; k++) {
            activation+=Vector[k]*WL1[j][k];
        }
        DL1[j] = activation;
        // OL1[j] = sigmoid(activation);
        OL1[j] = Relu(activation);
    }


    //OUTPUT LAYER
    //EFOSOM EXOYME CLASSIFICATION ME 10 CLASSES H ENDEDEIGMENH LYSH EINAI H SOFTMAX H OPOIA EPISTREFEI EKSODOYS APO 0 EWS 1 POY EXOYN METAKSI TOYS ATHROISMA
    //ISO ME 1. ARA ANAPARISTOYN THN PITHANOTHTA KATHE DIANYSMA NA ANHKEI SE MIA KLASH
    for (j=0; j<num_output_nodes; j++) {
        double activation=WL2[j][num_hidden_nodes];
        int k;
        for (k=0; k<num_hidden_nodes; k++) {
            activation+=OL1[k]*WL2[j][k];
        }
        DL2[j] = activation;
    }

    softmax(DL2,num_output_nodes,OL2);
}

// INITIALIZE WEIGHTS
void initializeSystem(){
    int i,j;
    
    //THELEI MIKRA VARH 
    //TO DIASTHMA TWN VARWN META APO DOKIMES PROEKIPSE APO 0 EWS 0.0001 GIA MEGALYTERA BARH H sigmoid TOY HIDDEN LAYER TA EKANE 1.00 OPOTE EPAIRNA IDIES EKSODOYS
    for(i=0;i<num_hidden_nodes;i++){
        for(j=0;j<num_inputs + 1;j++){
            // WL1[i][j] = ((float)rand() / (float)RAND_MAX);
            WL1[i][j] = 0.0001 *((float)rand() / (float)RAND_MAX);  //float x = ((float)rand()/(float)(RAND_MAX)) * a;
            
        }
    }

    for(i=0;i<num_output_nodes;i++){
        for(j=0;j<num_hidden_nodes + 1;j++){
            WL2[i][j] = 0.0001 * ((float)rand() / (float)RAND_MAX);
        }
    }
  

}

void print(int des){
    int i,j;

    // printf("\nINPUT\n");
    // printf("=============\n");
    // for(i=0;i<num_inputs;i++){
    //     printf("%f\n",input[0][i]);
    // }
    // printf("\n\n########################\n\n");
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
    printf("\nOL1\n");
    printf("==================================\n\n");
    for (j=0; j<num_hidden_nodes; j++) {
        printf("%f\n",OL1[j]);
    }

    // printf("\n\n WL2 \n");
    // printf("==================================\n\n");
    // for(i=0;i<num_output_nodes;i++){
    //     for(j=0;j<num_hidden_nodes + 1;j++){
    //         printf("%f\t",WL2[i][j]);
    //     }
    //     putchar('\n');
    // }
    // printf("\n\n########################\n\n");
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


    // printf("\nDESIRED SET \n");
    // printf("==================================\n\n");
    // for (j=0; j<num_output_nodes; j++) {
    //     printf("%f\n",desired[0][j]);
    // }

    // printf("\nSET = %d OL2\t\tDESIRED\n",des);
    // printf("==================================\n\n");
    // // for(i=0;i<5;i++){
    // for (j=0; j<num_output_nodes; j++) {
    //     printf("%f\t\t%f\n",OL2[j],desired[des][j]);
    // }
    // }
    
}

// BACKPROPAGATION
void trainNN(double *input , double *desired){
    int j,k;
    float lr = 0.001 ; //KAI TO learning rate META APO DOKIMES KATELIKSA SE AYTH THN TIMH
   
    // Compute change in output weights
    double deltaOutput[num_output_nodes];
    setError = 0.0;
    for (j=0; j<num_output_nodes; j++) {
        double dError = -(OL2[j] - desired[j]);
        deltaOutput[j] = dError;
        totalError-= desired[j]*log(OL2[j]); 
        setError-= desired[j]*log(OL2[j]); 
    }   

    // Compute change in hidden weights
    double deltaHidden[num_hidden_nodes];
    for (j=0; j<num_hidden_nodes; j++) {
        double dError = 0.0f;
        for(int k=0; k<num_output_nodes; k++) {
            dError+=deltaOutput[k]*WL2[k][j];
        }
        // deltaHidden[j] = dError*dSigmoid(OL1[j]);
        deltaHidden[j] =  dError*dRelu(OL1[j]);
    }

    // Apply change in output weights
    for (int j=0; j<num_output_nodes; j++) {
        WL2[j][num_hidden_nodes] += deltaOutput[j]*lr;
        for (k=0; k<num_hidden_nodes; k++) {
            WL2[j][k]+=OL1[k]*deltaOutput[j]*lr;
        }
    }

    // Apply change in hidden weights
    for (int j=0; j<num_hidden_nodes; j++) {
        WL1[j][num_inputs] += deltaHidden[j]*lr;
        for(int k=0; k<num_inputs; k++) {
            WL1[j][k]+=input[k]*deltaHidden[j]*lr;
        }
    }
}

void readCSV(){
    FILE * train = fopen("fashion-mnist_train.csv","r");
    FILE * ftest = fopen("fashion-mnist_test.csv","r");
    
    memset(desired2,0.0,sizeof(desired2));
    memset(desired,0.0,sizeof(desired));

    if (train == NULL){
        perror("UNABLE TO OPEN THE FILE");
        exit(1);
    }
    int i = 0;
    char line[7000];
    while(fgets(line,sizeof(line),train)){
        char *token;
        double inp;
        int j=0,des;
        token = strtok(line,",");
        
        while(token!=NULL){
            if(i!=0 && j==0){
                des = atoi(token);
                desired2[i-1][des] = 1.0;
                realClass2[i-1] = des;
            }
            if(i!=0 && j!=0){
                inp = atof(token);
                input[i-1][j] = inp/255;//kanonikopoiw
            }
            
            token = strtok(NULL,",");
            j++;
        }
        i++;
    }

    if (train == NULL){
        perror("UNABLE TO OPEN THE FILE");
        exit(1);
    }
    i = 0;
    while(fgets(line,sizeof(line),ftest)){
        char *token;
        double tes;
        int j=0,class;
        token = strtok(line,",");
        
        while(token!=NULL){
            if(i!=0 && j==0){
                class = atoi(token);
                realClass[i-1] = class;
                desired[i-1][class] = 1.0;
            }
            if(i!=0 && j!=0){
                tes = atof(token);
                test[i-1][j] = tes/255;
            }
            
            token = strtok(NULL,",");
            j++;
        }
        i++;
    }


}

// PREDICT CLASS
void predict(int set , int *Classes , int *Predictions){

    int i , class;
    double max = 0;
    for(i=0;i<num_output_nodes;i++){
        if(OL2[i]>max){
            max = OL2[i];
            class = i;
        }
    }

    Predictions[set] = class;

    // printf("\nprediction = %d\trealClass = %d\n",predictions[set],realClass[set]);
    if(Predictions[set] == Classes[set]){
        correct++;
        // printf("%d\n",correct);
    }
}

void evalError(double *desired){

    setError = 0.0;
    for (int j=0; j<num_output_nodes; j++) {
        double dError = -(OL2[j] - desired[j]);
        totalError-= desired[j]*log(OL2[j]); 
        setError-= desired[j]*log(OL2[j]); 
    }   
}

int main(){ 
    
    // PARADEIGMA
    // int i;
    // for(i=0;i<10;i++){
    //     activateNN(input[0]);
    //     print(0);
    //     trainNN(input[0],desired[0]);
    // }

    
    readCSV();
    initializeSystem();

    //EKPAIDEYSH

    int i,iteration,j,set;
    for(i=0;i<epochs;i++){
        totalError = 0.0;
        for(iteration=0;iteration<times;iteration++){
        // for(set=0;set<num_train_sets;set++){   
            int set = rand()%num_train_sets;
            activateNN(input[set]);
            trainNN(input[set],desired2[set]);
            printf("%d)SETERROR = %f\n",iteration,setError);
        }
        printf("\n\nSFALMA EKPAIDEYSHS = %f\n",totalError/times);
    }  
  
    


    //  TEST (TRAINSET)
    totalError = 0.0;
    for(i=0;i<num_train_sets;i++){
        activateNN(input[i]);
        predict(i,realClass2,predictions2);
        evalError(desired2[i]);
    }   
    printf("\n\nSFALMA AKSIOLOGHSHS TRAINSET = %f\n",totalError/num_train_sets);
        

    //  TEST (TESTSET)
    totalError = 0.0;
    for(i=0;i<num_test_sets;i++){
        activateNN(test[i]);
        predict(i,realClass,predictions);
        evalError(desired[i]);
    }   
    printf("\n\nSFALMA AKSIOLOGHSHS TESTSET = %f\n",totalError/num_test_sets);
    

    double accuracy = (double)(correct) / (double)(num_test_sets+num_train_sets) * 100.0;
    printf("\n\nACCURACY = %.3f%%\n\n",accuracy);
    
    return 0;
}

