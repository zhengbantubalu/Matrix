#ifndef _MATIO_H_
#define _MATIO_H_

#include "MatStruct.h"

/**
 * @brief   矩阵IO – 矩阵输入
 * @param   matrix      矩阵
 * @return  SUCCESS – 输入成功
 * @return  BREAK – 输入中断
 * @note    输入矩阵matrix
 */
int matInput(Mat matrix);

/**
 * @brief   矩阵IO – 矩阵局部输入
 * @param   matData     指向矩阵数据的指针
 * @param   rowStart    起始行
 * @param   rowEnd      终止行
 * @param   colStart    起始列
 * @param   colEnd      终止列
 * @return  SUCCESS – 输入成功
 * @return  BREAK – 输入中断
 * @note    输入矩阵的指定范围
 */
int matInLocal(double **matData, int rowStart, int rowEnd, int colStart, int colEnd);

/**
 * @brief   矩阵IO – 矩阵输出
 * @param   matrix      矩阵
 * @note    输出矩阵matrix
 */
void matOutput(Mat matrix);

/**
 * @brief   矩阵IO – 矩阵局部输出
 * @param   matData     指向矩阵数据的指针
 * @param   rowStart    起始行
 * @param   rowEnd      终止行
 * @param   colStart    起始列
 * @param   colEnd      终止列
 * @note    输出矩阵的指定范围
 */
void matOutLocal(double **matData, int rowStart, int rowEnd, int colStart, int colEnd);

/**
 * @brief   矩阵IO – 浮点数输出
 * @param   value       待输出值
 * @param   precision   保留小数位数
 * @param   width       打印字段宽度
 */
void prtDouble(double value, int precision, int width);

#endif