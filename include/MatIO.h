#ifndef _MATIO_H_
#define _MATIO_H_

#include "MatStruct.h"

/**
 * @brief   ���󹤾� �C ��������
 * @param   matrix      ����
 * @return  SUCCESS �C ����ɹ�
 * @return  BREAK �C �����ж�
 * @note    �������matrix
 */
int matInput(Mat matrix);

/**
 * @brief   ���󹤾� �C ����ֲ�����
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
 * @brief   ���󹤾� �C �������
 * @param   matrix      ����
 * @note    �������matrix
 */
void matOutput(Mat matrix);

/**
 * @brief   ���󹤾� �C ����ֲ����
 * @param   matData     ָ��������ݵ�ָ��
 * @param   rowStart    ��ʼ��
 * @param   rowEnd      ��ֹ��
 * @param   colStart    ��ʼ��
 * @param   colEnd      ��ֹ��
 * @note    ��������ָ����Χ
 */
void matOutLocal(double **matData, int rowStart, int rowEnd, int colStart, int colEnd);

#endif