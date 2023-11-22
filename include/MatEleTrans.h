#ifndef _MATELETRANS_H_
#define _MATELETRANS_H_

#include "MatStruct.h"
#include <stdbool.h>

/**
 * @brief   ������ȱ任 �C �Ի��任
 * @param   matrix      ����
 * @param   index1      Ŀ��1������
 * @param   index2      Ŀ��2������
 * @param   isRow       Ϊ�����б任��Ϊ�����б任
 * @note    ������matrix�ĵ�index1�����index2�жԻ�(�б任ͬ��)
 */
void matEleSwap(Mat matrix, int index1, int index2, bool isRow);

/**
 * @brief   ������ȱ任 �C ���˱任
 * @param   matrix      ����
 * @param   index       Ŀ��������
 * @param   multer      ���˱���
 * @param   isRow       Ϊ�����б任��Ϊ�����б任
 * @note    ������matrix��index�г���multer(�б任ͬ��)
 */
void matEleScaMul(Mat matrix, int index, double multer, bool isRow);

/**
 * @brief   ������ȱ任 �C ���ӱ任
 * @param   matrix      ����
 * @param   indexS      Դ������
 * @param   indexT      Ŀ��������
 * @param   multer      ���˱���
 * @param   isRow       Ϊ�����б任��Ϊ�����б任
 * @note    ������matrix��indexS�е�multer���ӵ���indexT����(�б任ͬ��)
 */
void matEleAdd(Mat matrix, int indexS, int indexT, double multer, bool isRow);

#endif