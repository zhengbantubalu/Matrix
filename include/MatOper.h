#ifndef _MATOPER_H_
#define _MATOPER_H_

#include "MatStruct.h"
#include <stdbool.h>

int matAdd(Mat source1, Mat source2, Mat target);

int matSub(Mat sourceM, Mat sourceS, Mat target);

int matScaMul(Mat source, Mat target, double multer);

int matMulti(Mat sourceL, Mat sourceR, Mat target);

int matTrans(Mat source, Mat target);

int matInver(Mat source, Mat target);

int matAdjo(Mat source, Mat target);

int matEche(Mat source, Mat target, double *deterPtr);

int matRedEche(Mat source, Mat target, bool isEche);

int matRank(Mat matrix, bool isEche, int *rankPtr);

int matDeter(Mat matrix, double *deterPtr);

int matMinor(Mat matrix, int indexRow, int indexCol, double *minorPtr);

int matCofac(Mat matrix, int indexRow, int indexCol, double *cofacPtr);

#endif