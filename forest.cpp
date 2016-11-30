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
#include <stdlib.h>
#include <ncurses.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

//typedef struct {
//    long start;
//    long end;
//} Offset;
//#define dimM 1000
//#define USED 8
//
//float matA[dimM][dimM];
//float matB[dimM][dimM];
//float matC[dimM][dimM];

//Tuples
int *tupleClass;
int *tupleUse;
double **tupleVariable;
int tupleCount = 5;
int varCount = 16;

//Tree
int maxTrees = 5;
int curNodeY = 0;
int curNodeX = 0;
int **varUsed;
int **objectClass;
int **isLeaf;
double **threshold;
int usedVariables;
int usedTuples;
double trainingSetPercentage = 0.8;
double varSetPercentage = 0.6;
int minSampleCount = 10;
int maxDepth = 10;

static bool
read_tuples( const string& filename){
    // initialize tuple data structure
    // tupleUse: flags for which tuples are used
    // tupleClass: int array with the class of the given tuple
    // tupleVariable: matrix with the readings of each variable
    // varCount: (rows) amount of variables on the tupleVariable matrix
    // tupleCount: (columns) amount of examples used

    int i, j;
    tupleUse = (int *) malloc(sizeof(int) * tupleCount);
    tupleClass = (int *) malloc(sizeof(int) * tupleCount);
    tupleVariable = (double **) malloc(sizeof(double *) * tupleCount);
    for( i = 0; i < tupleCount; i++){
        tupleVariable[i] = (double *) malloc(sizeof(double) * varCount);
    }
    // testing ---------
    for( i = 0; i < tupleCount; i++){
        tupleUse[i] = 1;
        tupleClass[i] = 'Z' - 'A';
        for( j = 0; j < varCount; j++){
          tupleVariable[i][j] = 3.0;
        }
    }
    // -----------------

    //FILE* f = fopen( filename.c_str(), "rt" );
    //if( !f ){
    //    cout << "Could not read the database " << filename << endl;
    //    return false;
    //}

    //for( i = 0; i < tuple_count; i++)
    //{
    //    char* ptr;
    //    if( !fgets( buf, M, f ) || !strchr( buf, ',' ) )
    //        break;
    //    responses.push_back((int)buf[0]);
    //    ptr = buf+2;
    //    for( i = 0; i < var_count; i++ )
    //    {
    //        int n = 0;
    //        sscanf( ptr, "%f%n", &el_ptr.at<float>(i), &n );
    //        ptr += n + 1;
    //    }
    //    if( i < var_count )
    //        break;
    //    _data->push_back(el_ptr);
    //}
    //fclose(f);
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

double
informationGained(t, x){
  e = entropy(t);
  ce = conditional_entropy(t, x);
  return(e - ce);
}

int main() {
    int i, j, index;
    // calculate number of used variables for each tree
    usedVariables = varCount * varSetPercentage;
    // calculate number of the training set (tuples) for each tree
    usedTuples = tupleCount * trainingSetPercentage;

    // individual tree training
    int *classCount;

    classCount = (int *) malloc(sizeof(int) * varCount);

    // choosing which tuples to use for bagging
    for ( i = 0; i < usedTuples; i++ ){
        srand(time(NULL));
        index = rand() % tupleCount;
        if( !tupleUse[index] )
          i--;
        tupleUse[index] = 0;
    }
    // choosing which variable subset to use
    for ( i = 0; i < usedVariables; i++ ){
        srand(time(NULL));
        index = rand() % tupleCount;
        if( !tupleUse[index] )
          i--;
        tupleUse[index] = 0;
    }
    //count all classes
    for ( i = 0; i < varCount; i++ ){
        classCount[i] = 0;
    }
    for ( i = 0; i < tupleCount; i++ ){
        if(tupleUse[i]){
          // if the tuple is used on this tree, add its class to classCount
          classCount[ tupleClass[i] ]++;
        }
    }
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
