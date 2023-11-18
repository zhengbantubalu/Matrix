#ifndef _MATUTIL_H_
#define _MATUTIL_H_

#include "MatStruct.h"
#include <stdbool.h>

/**
 * @brief   矩阵工具 – 矩阵初始化
 * @param   matPtr      指向矩阵结构体的指针
 * @param   numRows     矩阵行数
 * @param   numCols     矩阵列数
 * @note    申请矩阵的存储空间，并赋值为零矩阵
 */
void matInit(Mat *matPtr, int numRows, int numCols);

/**
 * @brief   矩阵工具 – 矩阵存储空间释放
 * @param   matPtr      指向矩阵结构体的指针
 * @note    释放矩阵的存储空间
 */
void matFree(Mat *matPtr);

/**
 * @brief   矩阵工具 – 赋值为单位矩阵
 * @param   matrix      矩阵
 * @param   numRows     矩阵行数
 * @return  SUCCESS – 赋值成功
 * @return  ERROR – 矩阵行列数不满足要求
 * @note    将矩阵matrix赋值为单位矩阵，矩阵须为方阵
 */
int matSetE(Mat matrix);

/**
 * @brief   矩阵工具 – 局部赋值为单位矩阵
 * @param   matData     指向矩阵数据的指针
 * @param   rowStart    起始行
 * @param   rowEnd      终止行
 * @param   colStart    起始列
 * @param   colEnd      终止列
 * @return  SUCCESS – 赋值成功
 * @return  ERROR – 范围行列数不相等
 * @note    将矩阵的指定范围赋值为单位矩阵，范围行列数须相等
 */
void matSetELocal(double **matData, int rowStart, int rowEnd, int colStart, int colEnd);

/**
 * @brief   矩阵工具 – 数组赋值矩阵
 * @param   matrix      矩阵
 * @param   arr         指向数组首元素的指针
 * @param   sizeofArr   数组所占空间，请传入sizeof(arr)，arr是数组名
 * @return  SUCCESS – 赋值成功
 * @return  ERROR – 数组与矩阵元素数不相等
 * @note    将一维数组以从左往右，从上往下的顺序赋值给矩阵，数组与矩阵元素数须相等
 */
int matSetArr(Mat matrix, double *arr, int sizeofArr);

/**
 * @brief   矩阵工具 – 矩阵复制
 * @param   source      源矩阵
 * @param   target      目标矩阵
 * @return  SUCCESS – 复制成功
 * @return  ERROR – 矩阵行列数不满足要求
 * @note    将矩阵source复制到矩阵target，源矩阵与目标矩阵须同型
 */
int matCopy(Mat source, Mat target);

/**
 * @brief   矩阵工具 – 矩阵局部复制
 * @param   srcData     指向源矩阵数据的指针
 * @param   tgtData     指向目标矩阵数据的指针
 * @param   rowSrcSt    源矩阵起始行
 * @param   rowSrcEd    源矩阵终止行
 * @param   rowTarSt    目标矩阵起始行
 * @param   rowTarEd    目标矩阵终止行
 * @param   colSrcSt    源矩阵起始列
 * @param   colSrcEd    源矩阵终止列
 * @param   colTarSt    目标矩阵起始列
 * @param   colTarEd    目标矩阵终止列
 * @return  SUCCESS – 复制成功
 * @return  ERROR – 指定范围行列数不相等
 * @note    将源矩阵的指定范围复制到目标矩阵的指定范围，两矩阵指定范围的行列数须相等
 */
int matCpLocal(double **srcData, double **tgtData,
               int rowSrcSt, int rowSrcEd, int rowTgtSt, int rowTgtEd,
               int colSrcSt, int colSrcEd, int colTarSt, int colTarEd);

/**
 * @brief   矩阵工具 – 矩阵同型判断
 * @param   matrix1     矩阵1
 * @param   matrix2     矩阵2
 * @return  ture – 同型
 * @return  false – 不同型
 * @note    判断矩阵matrix1与矩阵matrix2是否同型，即是否行数相等且列数相等
 */
bool matSameDim(Mat matrix1, Mat matrix2);

/**
 * @brief   矩阵工具 – 矩阵相等判断
 * @param   matrix1     矩阵1
 * @param   matrix2     矩阵2
 * @return  ture – 相等
 * @return  false – 不相等
 * @note    判断矩阵matrix1与矩阵matrix2是否相等，两矩阵须同型
 */
bool matEqual(Mat matrix1, Mat matrix2);

/**
 * @brief   矩阵工具 – 矩阵局部相等判断
 * @param   matData1    指向矩阵1数据的指针
 * @param   matData2    指向矩阵2数据的指针
 * @param   rowSt1      矩阵1起始行
 * @param   rowEd1      矩阵1终止行
 * @param   rowSt2      矩阵2起始行
 * @param   rowEd2      矩阵2终止行
 * @param   colSt1      矩阵1起始列
 * @param   colEd1      矩阵1终止列
 * @param   colSt2      矩阵2起始列
 * @param   colEd2      矩阵2终止列
 * @return  true – 相等
 * @return  false – 不相等
 * @note    判断矩阵matrix1与矩阵matrix2指定范围是否相等，两矩阵范围行列数须相等
 */
bool matEqLocal(double **matData1, double **matData2,
                int rowSt1, int rowEd1, int rowSt2, int rowEd2,
                int colSt1, int colEd1, int colSt2, int colEd2);

#endif