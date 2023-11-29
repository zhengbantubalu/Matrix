/**
 * @file    MatConst.h
 * @brief   矩阵运算库依赖的常数
 * @note    修改此处的值后需重新编译库
 * @warning 不当的值可能导致库运行出错，请谨慎修改
 */

#ifndef _MATCONST_H_
#define _MATCONST_H_

/**
 * @brief   零阈值
 * @note    小于此值的浮点数认为是0
 */
#define ZEROTHRES 1e-5

/**
 * @brief   精度
 * @note    打印浮点数小数位数
 */
#define PRECISION 2

/**
 * @brief   宽度
 * @note    打印浮点数字段宽度
 */
#define WIDTH 5

/**
 * @brief   成功
 * @note    返回此值表示函数运行成功
 */
#define SUCCESS 1

/**
 * @brief   错误
 * @note    返回此值表示函数运行错误
 */
#define ERROR -1

/**
 * @brief   中断
 * @note    返回此值表示输入中断
 */
#define BREAK 0

/**
 * @brief   不可逆
 * @note    返回此值表示矩阵不可逆
 */
#define SINGULAR 2

#endif