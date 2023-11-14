#ifndef _MATELETRANS_H_
#define _MATELETRANS_H_

#include "MatStruct.h"
#include <stdbool.h>

void matEleSwap(Mat matrix, int index1, int index2, bool isRow);

void matEleScaMul(Mat matrix, int index, double multer, bool isRow);

void matEleAdd(Mat matrix, int indexS, int indexT, double multer, bool isRow);

#endif