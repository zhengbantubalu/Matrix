#ifndef _MATELETRANS_H_
#define _MATELETRANS_H_

#include "MatStruct.h"
#include <stdbool.h>

/**
 * @brief   矩阵初等变换 – 对换变换
 * @param   matrix      矩阵
 * @param   index1      目标1行索引
 * @param   index2      目标2行索引
 * @param   isRow       为真则行变换，为假则列变换
 * @note    将矩阵matrix的第index1行与第index2行对换(列变换同理)
 */
void matEleSwap(Mat matrix, int index1, int index2, bool isRow);

/**
 * @brief   矩阵初等变换 – 数乘变换
 * @param   matrix      矩阵
 * @param   index       目标行索引
 * @param   multer      数乘倍数
 * @param   isRow       为真则行变换，为假则列变换
 * @note    将矩阵matrix第index行乘以multer(列变换同理)
 */
void matEleScaMul(Mat matrix, int index, double multer, bool isRow);

/**
 * @brief   矩阵初等变换 – 倍加变换
 * @param   matrix      矩阵
 * @param   indexS      源行索引
 * @param   indexT      目标行索引
 * @param   multer      数乘倍数
 * @param   isRow       为真则行变换，为假则列变换
 * @note    将矩阵matrix第indexS行的multer倍加到第indexT行上(列变换同理)
 */
void matEleAdd(Mat matrix, int indexS, int indexT, double multer, bool isRow);

#endif