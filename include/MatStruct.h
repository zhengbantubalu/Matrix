/**
 * @file    MatStruct.h
 * @brief   矩阵结构体
 * @note    调用库函数需要传递此数据类型的参数，以确保函数能获取矩阵的行列数信息
 */

#ifndef _MATSTRUCT_H_
#define _MATSTRUCT_H_

/**
 * @brief   矩阵结构体
 * @note    data – 指向矩阵数据的指针
 * @note    numRows – 矩阵行数
 * @note    numCols – 矩阵列数
 * @warning 矩阵行列数在初始化确定后请勿更改，否则可能导致内存访问出错
 */
typedef struct mat
{
    double **data;
    int numRows;
    int numCols;
} Mat;

#endif