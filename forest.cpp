/*
 * =====================================================================================
 *
 *       Filename:  forest.cpp
 *
 *    Description:  Random forest implentation done for parallel use with POSIX.
 *
 *        Version:  1.0
 *        Created:  11/29/2016 05:49:07 PM
 *       Revision:  1.0
 *       Compiler:  gcc
 *
 *         Author:   Sergio Cordero
 *        License:  
 *
 * =====================================================================================
 */
#include <math.h>
#include <stdlib.h>
#include <ncurses.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <istream>
#include <time.h>
#include <string>
#include <sstream>

#define THNUM 1
using namespace std;

//Tuples SHARED
int *tupleClass;
double **tupleVariable;
int tupCount = 20000;
int varCount = 16;
int classes = 26;

//Used by each training thread
int **tupleUse; //only relevant during training?
int **variableUse; //only relevant during training?
int **classCount;
int *curNodeY;
int *curNodeX;
//Tree
int trees = 5;
//nodes
int **varUsed;
int **objectClass;
int **isLeaf;
double **threshold;
//options
int usedVariableAmount;
int usedTupleAmount;
double tupSetPercentage = 0.8;
double varSetPercentage = 0.6;
int minSampleCount = 10;
int maxDepth = 10;

void
read_tuples( const string& filename){
    // initialize tuple data structure
    // tupleUse: flags for which tuples are used
    // tupleClass: int array with the class of the given tuple
    // tupleVariable: matrix with the readings of each variable
    // varCount: (rows) amount of variables on the tupleVariable matrix
    // tupleCount: (columns) amount of examples used

    int i, j;
    tupleClass = new int[tupCount];
    tupleVariable = new double*[tupCount];
    for( i = 0; i < tupCount; i++){
        tupleVariable[i] = new double[varCount];
    }

    ifstream myfile(filename);
    string temp;

    i = 0;
    while(getline(myfile, temp)){
        tupleClass[i] = temp[0] - 'A';

        //remove the first char
        temp = temp.substr(2, temp.size());

        char split_char = ',';
        istringstream split(temp);
        j = 0;
        for(string each; getline(split, each, split_char); j++){
            tupleVariable[i][j] = stod(each);
        }

        i++;
    }
}

void
*threadFunction(void *arg){
  //Offset *o = (Offset *)arg;
  //float *a = &matA[0][0];
  //float *b = &matB[0][0];
  //float *c = &matC[0][0];
  //float acum;
  //long i, j, row, col;

  //for( i = o->start; i < o->end; i++ ){
  //  acum = 0.0;
  //  row = i / dimM;
  //  col = i % dimM;
  //  for( j = 0; j < dimM; j++ ){
  //    acum += matA[row][j] * matB[j][col];
  //  }
  //  matC[row][col] = acum;
  //}

  return NULL;
}

//double
//informationGained(t, x){
//  e = entropy(t);
//  ce = conditional_entropy(t, x);
//  return(e - ce);
//}

double
entropy(){
    int i;
    double sum = 0.0;
    for( i = 0; i < usedVariableAmount; i++){
        sum += 1;
    }
}

double
logTwo(double x){
  return (log(x)/log(x));
}

void reset_thread(int threadNum){
    int i, index;
    //erase tupleUse, variableUse, classCount
    for( i = 0; i < tupCount; i++){
        tupleUse[threadNum][i] = 1;
    }
    for( i = 0; i < varCount; i++){
        variableUse[threadNum][i] = 1;
    }
    for ( i = 0; i < classes; i++ ){
        classCount[threadNum][i] = 0;
    }
    //make random selection of tupeUse, variableUse
    //count each class into classCount
    for ( i = 0; i < usedTupleAmount; i++ ){ // choosing which tuples to use for bagging
        srand(time(NULL));
        index = rand() % tupCount;
        if( !tupleUse[threadNum][index] )
          i--;
        tupleUse[threadNum][index] = 0;
    }
    for ( i = 0; i < usedVariableAmount; i++ ){ // choosing which variable subset to use
        srand(time(NULL));
        index = rand() % tupCount;
        if( !variableUse[threadNum][index] )
          i--;
        variableUse[threadNum][index] = 0;
    }
    for ( i = 0; i < tupCount; i++ ){
        if(tupleUse[i]){
          // if the tuple is used on this tree, add its class to classCount
          classCount[threadNum][tupleClass[i]]++;
        }
    }
}

int main() {
    int i, j, index;
    read_tuples("letter.data");

    //////////////////////////////
    // initialization
    tupleUse = new int*[THNUM];
    for( i = 0; i < THNUM; i++){
        tupleUse[i] = new int[tupCount];
    }
    variableUse = new int*[THNUM];
    for( i = 0; i < THNUM; i++){
        variableUse[i] = new int[varCount];
    }
    classCount = new int*[THNUM];
    for( i = 0; i < THNUM; i++){
        variableUse[i] = new int[classes];
    }
    usedVariableAmount = varCount * varSetPercentage; // calculate number of used variables for each tree
    usedTupleAmount = tupCount * tupSetPercentage;    // calculate number of the training set (tuples) for each tree
    //////////////////////////////

    //////////////////////////////
    // individual tree training
    reset_thread(0);
    //////////////////////////////


    for ( i = 0; i < varCount; i++){
      if(tupleUse[i]){
        
      }
    }
  //int i, j, k;
  //float acumD;
  //float *tempDA, *tempDB;
  //pthread_t *th;
  //Offset *o;
  //int threads_used;
  //long calculationsPerThread, tail;
  //double posixDur, posixWall;
  //struct timespec ts1, tw1, ts2, tw2;


  //threads_used = sysconf(_SC_NPROCESSORS_ONLN);
  ////threads_used = std::thread::hardware_concurrency();
  //tempDA = &matA[0][0];
  //tempDB = &matB[0][0];
  //for( i = 0; i < dimM*dimM;i++, tempDA++, tempDB++) {
  //  *tempDA = (float) 1.0;
  //  *tempDB = (float) 2.0;
  //}

  //th = (pthread_t *)malloc(sizeof(pthread_t) * threads_used);
  //o = (Offset *)malloc(sizeof(Offset) * threads_used);
  //calculationsPerThread = dimM * dimM / threads_used;
  //tail = dimM * dimM % threads_used;

  //clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts1);
  //clock_gettime(CLOCK_MONOTONIC, &tw1);
////--------------------------------------------- start
  //for( i = 0; i < threads_used; i++ ){
  //  printf("Thread #%d\n", i);
  //  o[i].start = i * calculationsPerThread;
  //  o[i].end = (i + 1 ) * calculationsPerThread;
  //  if( i == threads_used - 1 )
  //    o[i].end += tail;

  //  pthread_create(&th[i], NULL, threadFunction, &o[i]);
  //}

  //for( i = 0; i < threads_used; i++ ){
  //  pthread_join(th[i], NULL);
  //}
////--------------------------------------------- end
  //clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts2);
  //clock_gettime(CLOCK_MONOTONIC, &tw2);

  //posixDur = 1000.0*ts2.tv_sec + 1e-6*ts2.tv_nsec
  //  - (1000.0*ts1.tv_sec + 1e-6*ts1.tv_nsec);
  //posixWall = 1000.0*tw2.tv_sec + 1e-6*tw2.tv_nsec
  //  - (1000.0*tw1.tv_sec + 1e-6*tw1.tv_nsec);

  //  printf("%f %f\n",matC[0][0],matC[dimM-1][dimM-1]);
  //printf("PosixDur: %f\n", posixDur);
  //printf("PosixWall: %f\n", posixWall);
  return 0;
}
