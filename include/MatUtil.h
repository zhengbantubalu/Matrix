#ifndef _MATUTIL_H_
#define _MATUTIL_H_

#include "MatStruct.h"
#include <stdbool.h>

/**
 * @brief   ���󹤾� �C �����ʼ��
 * @param   matPtr      ָ�����ṹ���ָ��
 * @param   numRows     ��������
 * @param   numCols     ��������
 * @note    �������Ĵ洢�ռ䣬����ֵΪ�����
 */
void matInit(Mat *matPtr, int numRows, int numCols);

/**
 * @brief   ���󹤾� �C ����洢�ռ��ͷ�
 * @param   matPtr      ָ�����ṹ���ָ��
 * @note    �ͷž���Ĵ洢�ռ�
 */
void matFree(Mat *matPtr);

/**
 * @brief   ���󹤾� �C ��ֵΪ��λ����
 * @param   matrix      ����
 * @param   numRows     ��������
 * @return  SUCCESS �C ��ֵ�ɹ�
 * @return  ERROR �C ����������������Ҫ��
 * @note    ������matrix��ֵΪ��λ���󣬾�����Ϊ����
 */
int matSetE(Mat matrix);

/**
 * @brief   ���󹤾� �C �ֲ���ֵΪ��λ����
 * @param   matData     ָ��������ݵ�ָ��
 * @param   rowStart    ��ʼ��
 * @param   rowEnd      ��ֹ��
 * @param   colStart    ��ʼ��
 * @param   colEnd      ��ֹ��
 * @return  SUCCESS �C ��ֵ�ɹ�
 * @return  ERROR �C ��Χ�����������
 * @note    �������ָ����Χ��ֵΪ��λ���󣬷�Χ�����������
 */
void matSetELocal(double **matData, int rowStart, int rowEnd, int colStart, int colEnd);

/**
 * @brief   ���󹤾� �C ���鸳ֵ����
 * @param   matrix      ����
 * @param   arr         ָ��������Ԫ�ص�ָ��
 * @param   sizeofArr   ������ռ�ռ䣬�봫��sizeof(arr)��arr��������
 * @return  SUCCESS �C ��ֵ�ɹ�
 * @return  ERROR �C ���������Ԫ���������
 * @note    ��һά�����Դ������ң��������µ�˳��ֵ���������������Ԫ���������
 */
int matSetArr(Mat matrix, double *arr, int sizeofArr);

/**
 * @brief   ���󹤾� �C ������
 * @param   source      Դ����
 * @param   target      Ŀ�����
 * @return  SUCCESS �C ���Ƴɹ�
 * @return  ERROR �C ����������������Ҫ��
 * @note    ������source���Ƶ�����target��Դ������Ŀ�������ͬ��
 */
int matCopy(Mat source, Mat target);

/**
 * @brief   ���󹤾� �C ����ֲ�����
 * @param   srcData     ָ��Դ�������ݵ�ָ��
 * @param   tgtData     ָ��Ŀ��������ݵ�ָ��
 * @param   rowSrcSt    Դ������ʼ��
 * @param   rowSrcEd    Դ������ֹ��
 * @param   rowTarSt    Ŀ�������ʼ��
 * @param   rowTarEd    Ŀ�������ֹ��
 * @param   colSrcSt    Դ������ʼ��
 * @param   colSrcEd    Դ������ֹ��
 * @param   colTarSt    Ŀ�������ʼ��
 * @param   colTarEd    Ŀ�������ֹ��
 * @return  SUCCESS �C ���Ƴɹ�
 * @return  ERROR �C ָ����Χ�����������
 * @note    ��Դ�����ָ����Χ���Ƶ�Ŀ������ָ����Χ��������ָ����Χ�������������
 */
int matCpLocal(double **srcData, double **tgtData,
               int rowSrcSt, int rowSrcEd, int rowTgtSt, int rowTgtEd,
               int colSrcSt, int colSrcEd, int colTarSt, int colTarEd);

/**
 * @brief   ���󹤾� �C ����ͬ���ж�
 * @param   matrix1     ����1
 * @param   matrix2     ����2
 * @return  ture �C ͬ��
 * @return  false �C ��ͬ��
 * @note    �жϾ���matrix1�����matrix2�Ƿ�ͬ�ͣ����Ƿ�����������������
 */
bool matSameDim(Mat matrix1, Mat matrix2);

/**
 * @brief   ���󹤾� �C ��������ж�
 * @param   matrix1     ����1
 * @param   matrix2     ����2
 * @return  ture �C ���
 * @return  false �C �����
 * @note    �жϾ���matrix1�����matrix2�Ƿ���ȣ���������ͬ��
 */
bool matEqual(Mat matrix1, Mat matrix2);

/**
 * @brief   ���󹤾� �C ����ֲ�����ж�
 * @param   matData1    ָ�����1���ݵ�ָ��
 * @param   matData2    ָ�����2���ݵ�ָ��
 * @param   rowSt1      ����1��ʼ��
 * @param   rowEd1      ����1��ֹ��
 * @param   rowSt2      ����2��ʼ��
 * @param   rowEd2      ����2��ֹ��
 * @param   colSt1      ����1��ʼ��
 * @param   colEd1      ����1��ֹ��
 * @param   colSt2      ����2��ʼ��
 * @param   colEd2      ����2��ֹ��
 * @return  true �C ���
 * @return  false �C �����
 * @note    �жϾ���matrix1�����matrix2ָ����Χ�Ƿ���ȣ�������Χ�����������
 */
bool matEqLocal(double **matData1, double **matData2,
                int rowSt1, int rowEd1, int rowSt2, int rowEd2,
                int colSt1, int colEd1, int colSt2, int colEd2);

#endif