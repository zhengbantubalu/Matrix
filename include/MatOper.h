#ifndef _MATOPER_H_
#define _MATOPER_H_

#include "MatStruct.h"
#include <stdbool.h>

/**
 * @brief   �������� �C ����ӷ�
 * @param   source1     Դ����1
 * @param   source2     Դ����2
 * @param   target      Ŀ�����
 * @return  SUCCESS �C ����ɹ�
 * @return  ERROR �C ����������������Ҫ��
 * @note    ������source1�����source2�ĺ͸�ֵ������target����������ͬ��
 */
int matData(Mat source1, Mat source2, Mat target);

/**
 * @brief   �������� �C �������
 * @param   sourceM     ��������
 * @param   sourceS     ������
 * @param   target      Ŀ�����
 * @return  SUCCESS �C ����ɹ�
 * @return  ERROR �C ����������������Ҫ��
 * @note    ������sourceM������sourceS�Ĳֵ������target����������ͬ��
 */
int matSub(Mat sourceM, Mat sourceS, Mat target);

/**
 * @brief   �������� �C ��������
 * @param   source      Դ����
 * @param   target      Ŀ�����
 * @param   multer  ���˱���
 * @return  SUCCESS �C ����ɹ�
 * @return  ERROR �C ����������������Ҫ��
 * @note    ������source����multer�Ļ���ֵ������target����������ͬ��
 */
int matScaMul(Mat source, Mat target, double multer);

/**
 * @brief   �������� �C ����˷�
 * @param   sourceL     �����
 * @param   sourceR     �Ҿ���
 * @param   target      Ŀ�����
 * @return  SUCCESS �C ����ɹ�
 * @return  ERROR �C ����������������Ҫ��
 * @note    ������sourceL�����sourceR�Ļ���ֵ������target��sourceL�����������sourceR��������
 *          sourceL�����������target��������sourceR�����������target������
 */
int matMulti(Mat sourceL, Mat sourceR, Mat target);

/**
 * @brief   �������� �C ��ת�þ���
 * @param   source      Դ����
 * @param   target      Ŀ�����
 * @return  SUCCESS �C ����ɹ�
 * @return  ERROR �C ����������������Ҫ��
 * @note    ������source��ת�þ���ֵ������target��source�����������target��������source�����������target������
 */
int matTrans(Mat source, Mat target);

/**
 * @brief   �������� �C �������
 * @param   source      Դ����
 * @param   target      Ŀ�����
 * @return  SUCCESS �C ����ɹ�
 * @return  SINGULAR �C ���󲻿���
 * @return  ERROR �C ����������������Ҫ��
 * @note    ������source�������ֵ������target����������Ϊͬ�ͷ���
 */
int matInver(Mat source, Mat target);

/**
 * @brief   �������� �C ��������
 * @param   source      Դ����
 * @param   target      Ŀ�����
 * @return  SUCCESS �C ����ɹ�
 * @return  ERROR �C ����������������Ҫ��
 * @note    ������source�İ������ֵ������target����������Ϊͬ�ͷ���
 */
int matAdjo(Mat source, Mat target);

/**
 * @brief   �������� �C ���н����ξ���
 * @param   source      Դ����
 * @param   target      Ŀ�����
 * @param   deterPtr    ָ������ʽ��ָ�룬������Ҫ�봫��NULL
 * @return  SUCCESS �C ����ɹ�
 * @return  ERROR �C ����������������Ҫ��
 * @note    ������source���н����ξ���ֵ������target��������source������ʽ��ֵ��*deterPtr����������ͬ��
 */
int matEche(Mat source, Mat target, double *deterPtr);

/**
 * @brief   �������� �C ��������ξ���
 * @param   source      Դ����
 * @param   target      Ŀ�����
 * @param   isEche      source�Ƿ�Ϊ�н����ξ���
 * @return  SUCCESS �C ����ɹ�
 * @return  ERROR �C ����������������Ҫ��
 * @note    ������source��������ξ���ֵ������target����������ͬ��
 */
int matRedEche(Mat source, Mat target, bool isEche);

/**
 * @brief   �������� �C ��������
 * @param   matrix      ����
 * @param   isEche      matrix�Ƿ�Ϊ�н����ξ���
 * @param   rankPtr     ָ���ȵ�ָ��
 * @return  SUCCESS �C ����ɹ�
 * @return  ERROR �C ָ��Ϊ��
 * @note    �����matrix���ȣ�����ֵ��*rankPtr
 */
int matRank(Mat matrix, bool isEche, int *rankPtr);

/**
 * @brief   �������� �C ����������ʽ
 * @param   matrix      ����
 * @param   deterPtr    ָ������ʽ��ָ��
 * @return  SUCCESS �C ����ɹ�
 * @return  ERROR �C ����������������Ҫ�󣬻�ָ��Ϊ��
 * @note    �����matrix������ʽ������ֵ��*deterPtr��������Ϊ����
 */
int matDeter(Mat matrix, double *deterPtr);

/**
 * @brief   �������� �C �����Ԫ�ص�����ʽ
 * @param   matrix      ����
 * @param   indexRow    Ԫ��������
 * @param   indexCol    Ԫ��������
 * @param   minorPtr    ָ������ʽ��ָ��
 * @return  SUCCESS �C ����ɹ�
 * @return  ERROR �C ����������������Ҫ�󣬻�ָ��Ϊ��
 * @note    �����matrix��indexRow�е�indexCol��Ԫ�ص�����ʽ������ֵ��*minorPtr��������Ϊ����
 */
int matMinor(Mat matrix, int indexRow, int indexCol, double *minorPtr);

/**
 * @brief   �������� �C �����Ԫ�صĴ�������ʽ
 * @param   matrix      ����
 * @param   indexRow    Ԫ��������
 * @param   indexCol    Ԫ��������
 * @param   cofacPtr    ָ���������ʽ��ָ��
 * @return  SUCCESS �C ����ɹ�
 * @return  ERROR �C ����������������Ҫ�󣬻�ָ��Ϊ��
 * @note    �����matrix��indexRow�е�indexCol��Ԫ�صĴ�������ʽ������ֵ��*cofacPtr��������Ϊ����
 */
int matCofac(Mat matrix, int indexRow, int indexCol, double *cofacPtr);

#endif