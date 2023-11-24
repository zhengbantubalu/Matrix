#ifndef _MATIO_H_
#define _MATIO_H_

#include "MatStruct.h"
#include <stdbool.h>

/**
 * @brief   ����IO �C ��������
 * @param   matrix      ����
 * @return  SUCCESS �C ����ɹ�
 * @return  BREAK �C �����ж�
 * @note    �������matrix
 */
int matInput(Mat matrix);

/**
 * @brief   ����IO �C ����ֲ�����
 * @param   matData     ָ��������ݵ�ָ��
 * @param   rowStart    ��ʼ��
 * @param   rowEnd      ��ֹ��
 * @param   colStart    ��ʼ��
 * @param   colEnd      ��ֹ��
 * @return  SUCCESS �C ����ɹ�
 * @return  BREAK �C �����ж�
 * @note    ��������ָ����Χ
 */
int matInLocal(double **matData, int rowStart, int rowEnd, int colStart, int colEnd);

/**
 * @brief   ����IO �C �������
 * @param   matrix      ����
 * @param   precision   ����������С��λ��
 * @param   width       ��������ӡ�ֶο��
 * @note    �������matrix
 */
void matOutput(Mat matrix, int precision, int width);

/**
 * @brief   ����IO �C ����ֲ����
 * @param   matData     ָ��������ݵ�ָ��
 * @param   rowStart    ��ʼ��
 * @param   rowEnd      ��ֹ��
 * @param   colStart    ��ʼ��
 * @param   colEnd      ��ֹ��
 * @param   precision   ����������С��λ��
 * @param   width       ��������ӡ�ֶο��
 * @note    ��������ָ����Χ
 */
void matOutLocal(double **matData, int rowStart, int rowEnd, int colStart, int colEnd,
                 int precision, int width);

/**
 * @brief   ����IO �C ���������
 * @param   value       �����ֵ
 * @param   precision   ����С��λ��
 * @param   width       ��ӡ�ֶο��
 * @param   isAbs       �Ƿ��������ֵ
 * @note    ������Ҫ���ӡ������
 */
void prtDouble(double value, int precision, int width, bool isAbs);

#endif