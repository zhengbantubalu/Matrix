#ifndef _MATSTRUCT_H_
#define _MATSTRUCT_H_

/**
 * @brief   矩阵结构体
 * @note    data – 指向矩阵数据的指针
 * @note    numRows – 矩阵行数
 * @note    numCols – 矩阵列数
 */
typedef struct mat
{
    double **data;
    int numRows;
    int numCols;
} Mat;

#endif