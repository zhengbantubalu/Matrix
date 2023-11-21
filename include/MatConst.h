#ifndef _MATCONST_H_
#define _MATCONST_H_

// 零阈值
// 小于此值的浮点数认为是0
#define ZEROTHRES 1e-5

// 精度
// 打印浮点数小数位数
#define PRECISION 2

// 宽度
// 打印浮点数字段宽度
#define WIDTH 5

// 成功
// 返回此值表示函数运行成功
#define SUCCESS 1

// 错误
// 返回此值表示函数运行错误
#define ERROR -1

// 中断
// 返回此值表示输入中断
#define BREAK 0

// 不可逆
// 返回此值表示矩阵不可逆
#define SINGULAR 2

#endif