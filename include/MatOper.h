/**
 * @file    MatOper.h
 * @brief   矩阵运算
 */

#ifndef _MATOPER_H_
#define _MATOPER_H_

#include "MatStruct.h"
#include <stdbool.h>

/**
 * @brief   矩阵运算 – 矩阵加法
 * @param   source1     源矩阵1
 * @param   source2     源矩阵2
 * @param   target      目标矩阵
 * @return  SUCCESS – 计算成功
 * @return  ERROR – 矩阵行列数不满足要求
 * @note    将矩阵source1与矩阵source2的和赋值给矩阵target，三矩阵须同型
 */
int matAdd(Mat source1, Mat source2, Mat target);

/**
 * @brief   矩阵运算 – 矩阵减法
 * @param   sourceM     被减矩阵
 * @param   sourceS     减矩阵
 * @param   target      目标矩阵
 * @return  SUCCESS – 计算成功
 * @return  ERROR – 矩阵行列数不满足要求
 * @note    将矩阵sourceM减矩阵sourceS的差赋值给矩阵target，三矩阵须同型
 */
int matSub(Mat sourceM, Mat sourceS, Mat target);

/**
 * @brief   矩阵运算 – 矩阵数乘
 * @param   source      源矩阵
 * @param   target      目标矩阵
 * @param   multer  数乘倍数
 * @return  SUCCESS – 计算成功
 * @return  ERROR – 矩阵行列数不满足要求
 * @note    将矩阵source数乘multer的积赋值给矩阵target，两矩阵须同型
 */
int matScaMul(Mat source, Mat target, double multer);

/**
 * @brief   矩阵运算 – 矩阵乘法
 * @param   sourceL     左矩阵
 * @param   sourceR     右矩阵
 * @param   target      目标矩阵
 * @return  SUCCESS – 计算成功
 * @return  ERROR – 矩阵行列数不满足要求
 * @note    将矩阵sourceL与矩阵sourceR的积赋值给矩阵target，sourceL的列数须等于sourceR的行数，
 *          sourceL的行数须等于target的行数，sourceR的列数须等于target的列数
 */
int matMulti(Mat sourceL, Mat sourceR, Mat target);

/**
 * @brief   矩阵运算 – 求转置矩阵
 * @param   source      源矩阵
 * @param   target      目标矩阵
 * @return  SUCCESS – 计算成功
 * @return  ERROR – 矩阵行列数不满足要求
 * @note    将矩阵source的转置矩阵赋值给矩阵target，
 *          source的行数须等于target的列数，source的列数须等于target的行数
 */
int matTrans(Mat source, Mat target);

/**
 * @brief   矩阵运算 – 求逆矩阵
 * @param   source      源矩阵
 * @param   target      目标矩阵
 * @return  SUCCESS – 计算成功
 * @return  SINGULAR – 矩阵不可逆
 * @return  ERROR – 矩阵行列数不满足要求
 * @note    将矩阵source的逆矩阵赋值给矩阵target，两矩阵须为同型方阵
 */
int matInver(Mat source, Mat target);

/**
 * @brief   矩阵运算 – 求伴随矩阵
 * @param   source      源矩阵
 * @param   target      目标矩阵
 * @return  SUCCESS – 计算成功
 * @return  ERROR – 矩阵行列数不满足要求
 * @note    将矩阵source的伴随矩阵赋值给矩阵target，两矩阵须为同型方阵
 */
int matAdjo(Mat source, Mat target);

/**
 * @brief   矩阵运算 – 求行阶梯形矩阵
 * @param   source      源矩阵
 * @param   target      目标矩阵
 * @param   deterPtr    指向行列式的指针，若不需要请传入NULL
 * @return  SUCCESS – 计算成功
 * @return  ERROR – 矩阵行列数不满足要求
 * @note    将矩阵source通过初等行变换化成行阶梯形，赋值给矩阵target，两矩阵须同型
 * @note    将矩阵source的行列式赋值给*deterPtr
 */
int matEche(Mat source, Mat target, double *deterPtr);

/**
 * @brief   矩阵运算 – 求行最简形矩阵
 * @param   source      源矩阵
 * @param   target      目标矩阵
 * @param   isEche      source是否为行阶梯形矩阵
 * @return  SUCCESS – 计算成功
 * @return  ERROR – 矩阵行列数不满足要求
 * @note    将矩阵source通过初等行变换化成行最简形，赋值给矩阵target，两矩阵须同型
 */
int matRedEche(Mat source, Mat target, bool isEche);

/**
 * @brief   矩阵运算 – 求矩阵的秩
 * @param   matrix      矩阵
 * @param   isEche      matrix是否为行阶梯形矩阵
 * @param   rankPtr     指向秩的指针
 * @return  SUCCESS – 计算成功
 * @return  ERROR – 指针为空
 * @note    求矩阵matrix的秩，并赋值给*rankPtr
 */
int matRank(Mat matrix, bool isEche, int *rankPtr);

/**
 * @brief   矩阵运算 – 求矩阵的行列式
 * @param   matrix      矩阵
 * @param   deterPtr    指向行列式的指针
 * @return  SUCCESS – 计算成功
 * @return  ERROR – 矩阵行列数不满足要求，或指针为空
 * @note    求矩阵matrix的行列式，并赋值给*deterPtr，矩阵须为方阵
 */
int matDeter(Mat matrix, double *deterPtr);

/**
 * @brief   矩阵运算 – 求矩阵元素的余子式
 * @param   matrix      矩阵
 * @param   indexRow    元素行索引
 * @param   indexCol    元素列索引
 * @param   minorPtr    指向余子式的指针
 * @return  SUCCESS – 计算成功
 * @return  ERROR – 矩阵行列数不满足要求，或指针为空
 * @note    求矩阵matrix第indexRow行第indexCol列元素的余子式，并赋值给*minorPtr，矩阵须为方阵
 */
int matMinor(Mat matrix, int indexRow, int indexCol, double *minorPtr);

/**
 * @brief   矩阵运算 – 求矩阵元素的代数余子式
 * @param   matrix      矩阵
 * @param   indexRow    元素行索引
 * @param   indexCol    元素列索引
 * @param   cofacPtr    指向代数余子式的指针
 * @return  SUCCESS – 计算成功
 * @return  ERROR – 矩阵行列数不满足要求，或指针为空
 * @note    求矩阵matrix第indexRow行第indexCol列元素的代数余子式，并赋值给*cofacPtr，矩阵须为方阵
 */
int matCofac(Mat matrix, int indexRow, int indexCol, double *cofacPtr);

#endif