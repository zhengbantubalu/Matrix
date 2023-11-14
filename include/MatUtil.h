#ifndef _MATUTIL_H_
#define _MATUTIL_H_

#include "MatStruct.h"
#include <stdbool.h>

void matInit(Mat *matPtr, int numRows, int numCols);

void matFree(Mat *matPtr);

int matSetE(Mat matrix);

void matSetELocal(double **matAdd, int rowStart, int rowEnd, int colStart, int colEnd);

int matCopy(Mat source, Mat target);

int matCpLocal(double **srcAdd, double **tgtAdd,
               int rowSrcSt, int rowSrcEd, int rowTgtSt, int rowTgtEd,
               int colSrcSt, int colSrcEd, int colTarSt, int colTarEd);

bool matSameDim(Mat matrix1, Mat matrix2);

bool matEqual(Mat matrix1, Mat matrix2);

bool matEqLocal(double **matAdd1, double **matAdd2,
                int rowSt1, int rowEd1, int rowSt2, int rowEd2,
                int colSt1, int colEd1, int colSt2, int colEd2);

#endif