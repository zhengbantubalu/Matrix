#ifndef _MATIO_H_
#define _MATIO_H_

#include "MatStruct.h"

int matInput(Mat matrix);

int matInLocal(double **matAdd, int rowStart, int rowEnd, int colStart, int colEnd);

void matOutput(Mat matrix);

void matOutLocal(double **matAdd, int rowStart, int rowEnd, int colStart, int colEnd);

#endif