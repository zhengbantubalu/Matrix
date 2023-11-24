#include ".\include\EasyCalc.h"
#include "..\include\MatOper.h"
#include "..\include\MatUtil.h"
#include "..\include\MatIO.h"
#include "..\include\MatStruct.h"
#include "..\include\MatConst.h"
#include <stdio.h>
#include <stdbool.h>

#define START 0
#define INPUT 1
#define SELECT 2
#define FREE 3
#define END 4

#define RANK 1
#define DETER 2
#define ECHE 3
#define REDECHE 4
#define TRANS 5
#define ADJO 6
#define INVER 7
#define ADD 8
#define SUB 9
#define SCAMUL 10
#define MULTI 11
#define CLEAR 12

void pause(void)
{
    putchar('\n');
    system("pause");
    putchar('\n');
}

void easyCalc(void)
{
    int state = START;
    int choice = 0;
    char ch;
    Mat matrix, matemp, matOut;
    int numRows = 0, numCols = 0;
    int rank = 0;
    double det = 0, multer = 0;
    printf("���׾��������\n\n");
    while (state != END)
    {
        switch (state)
        {
        case START:
            printf("������ѡ��:\n1.�������    2.��������    3.�˳�����\n\n");
            choice = 0;
            scanf("%d", &choice);
            fflush(stdin);
            putchar('\n');
            switch (choice)
            {
            case 1:
                state = INPUT;
                break;
            case 2:
                printf("��1:\n4 4\n1 2 3 4\n2 3 4 1\n3 4 1 2\n4 1 2 3\n\n");
                printf("��2:\n4 5\n1 1 1 1 1\n3 2 1 1 -3\n0 1 3 2 5\n5 4 3 3 -1\n\n");
                printf("��3:\n3 3 3 -3 4 2 -3 4 0 -1 1\n\n");
                printf("��4:\n4 4 4 1 2 4 1 2 0 2 10 5 2 0 0 1 1 7\n\n");
                break;
            case 3:
                state = END;
                break;
            default:
                printf("ѡ�����\n");
                pause();
            }
            break;
        case INPUT:
            printf("���������A\n[����] [����] [����] (���軻��)\n");
            printf("�����κη��������ж�����\n\n");
            ungetc(ch = getchar(), stdin);
            if (scanf("%d%d", &numRows, &numCols) != 2)
            {
                printf("\n�����ж�\n");
                fflush(stdin);
                pause();
                state = START;
                break;
            }
            matInit(&matrix, numRows, numCols);
            switch (matInput(matrix))
            {
            case SUCCESS:
                putchar('\n');
                state = SELECT;
                break;
            case BREAK:
                printf("\n�����ж�\n");
                pause();
                state = FREE;
                break;
            }
            fflush(stdin);
            break;
        case SELECT:
            printf("������ѡ��:\n1. ��������       2. ����������ʽ   3. ���н����ξ���\n");
            printf("4. ��������ξ���   5. ��ת�þ���       6. ��������\n");
            printf("7. �������         8. ����ӷ�         9. �������\n");
            printf("10.��������         11.����˷�         12.�������\n\n");
            choice = 0;
            scanf("%d", &choice);
            fflush(stdin);
            putchar('\n');
            switch (choice)
            {
            case RANK:
                matRank(matrix, false, &rank);
                printf("rank(A) = %d\n", rank);
                pause();
                break;
            case DETER:
                switch (matDeter(matrix, &det))
                {
                case SUCCESS:
                    printf("det(A) = ");
                    prtDouble(det, PRECISION, 0, false);
                    putchar('\n');
                    break;
                case ERROR:
                    printf("ֻ�з������������ʽ\n");
                }
                pause();
                break;
            case ECHE:
                matInit(&matOut, matrix.numRows, matrix.numCols);
                matEche(matrix, matOut, NULL);
                printf("A���н����ξ���:\n");
                matOutput(matOut, PRECISION, WIDTH);
                matFree(&matOut);
                pause();
                break;
            case REDECHE:
                matInit(&matOut, matrix.numRows, matrix.numCols);
                matRedEche(matrix, matOut, false);
                printf("A��������ξ���:\n");
                matOutput(matOut, PRECISION, WIDTH);
                matFree(&matOut);
                pause();
                break;
            case TRANS:
                matInit(&matOut, matrix.numCols, matrix.numRows);
                matTrans(matrix, matOut);
                printf("A��ת�þ���:\n");
                matOutput(matOut, PRECISION, WIDTH);
                matFree(&matOut);
                pause();
                break;
            case ADJO:
                matInit(&matOut, matrix.numRows, matrix.numCols);
                switch (matAdjo(matrix, matOut))
                {
                case SUCCESS:
                    printf("A�İ������:\n");
                    matOutput(matOut, PRECISION, WIDTH);
                    break;
                case ERROR:
                    printf("ֻ�з��������������\n");
                    break;
                }
                matFree(&matOut);
                pause();
                break;
            case INVER:
                matInit(&matOut, matrix.numRows, matrix.numCols);
                switch (matInver(matrix, matOut))
                {
                case SUCCESS:
                    printf("A�������:\n");
                    matOutput(matOut, PRECISION, WIDTH);
                    break;
                case SINGULAR:
                    printf("���󲻿���\n");
                    break;
                case ERROR:
                    printf("ֻ�з�������������\n");
                    break;
                }
                matFree(&matOut);
                pause();
                break;
            case ADD:
                matInit(&matemp, matrix.numRows, matrix.numCols);
                matInit(&matOut, matrix.numRows, matrix.numCols);
                printf("������ %d�� %d�� �ľ���B (��������������)\n", numRows, numCols);
                printf("�����κη��������ж�����\n\n");
                switch (matInput(matemp))
                {
                case SUCCESS:
                    matData(matrix, matemp, matOut);
                    printf("\nA + B =\n");
                    matOutput(matOut, PRECISION, WIDTH);
                    break;
                case BREAK:
                    printf("\n�����ж�\n");
                    break;
                }
                fflush(stdin);
                matFree(&matemp);
                matFree(&matOut);
                pause();
                break;
            case SUB:
                matInit(&matemp, matrix.numRows, matrix.numCols);
                matInit(&matOut, matrix.numRows, matrix.numCols);
                printf("������ %d�� %d�� �ľ���B (��������������)\n", numRows, numCols);
                printf("�����κη��������ж�����\n\n");
                switch (matInput(matemp))
                {
                case SUCCESS:
                    fflush(stdin);
                    printf("\n������ѡ��:\n1.A - B    2.B - A\n\n");
                    choice = 0;
                    scanf("%d", &choice);
                    fflush(stdin);
                    putchar('\n');
                    switch (choice)
                    {
                    case 1:
                        matSub(matrix, matemp, matOut);
                        printf("A - B =\n");
                        matOutput(matOut, PRECISION, WIDTH);
                        break;
                    case 2:
                        matSub(matemp, matrix, matOut);
                        printf("B - A =\n");
                        matOutput(matOut, PRECISION, WIDTH);
                        break;
                    default:
                        printf("ѡ�����\n");
                    }
                    break;
                case BREAK:
                    fflush(stdin);
                    printf("\n�����ж�\n");
                    break;
                }
                matFree(&matemp);
                matFree(&matOut);
                pause();
                break;
            case SCAMUL:
                matInit(&matOut, matrix.numRows, matrix.numCols);
                printf("���������˱���:\n\n");
                if (scanf("%lf", &multer) == 1)
                {
                    matScaMul(matrix, matOut, multer);
                    printf("\nA * ");
                    prtDouble(multer, PRECISION, 0, false);
                    printf(" =\n");
                    matOutput(matOut, PRECISION, WIDTH);
                }
                else
                {
                    printf("\n���벻������\n");
                }
                fflush(stdin);
                matFree(&matOut);
                pause();
                break;
            case MULTI:
                printf("������ѡ��:\n1.A * B    2.B * A\n\n");
                scanf("%d", &choice);
                fflush(stdin);
                putchar('\n');
                switch (choice)
                {
                case 1:
                    printf("���������B\n[����] [����] [����] (���軻��)\n");
                    printf("����B��������Ϊ%d\n", matrix.numCols);
                    printf("�����κη��������ж�����\n\n");
                    ungetc(ch = getchar(), stdin);
                    if (scanf("%d%d", &numRows, &numCols) != 2)
                    {
                        printf("\n�����ж�\n");
                        fflush(stdin);
                        break;
                    }
                    if (numRows != matrix.numCols)
                    {
                        printf("\n����B������������Ҫ��\n");
                        fflush(stdin);
                        break;
                    }
                    else
                    {
                        matInit(&matemp, numRows, numCols);
                        matInit(&matOut, matrix.numRows, matemp.numCols);
                        switch (matInput(matemp))
                        {
                        case SUCCESS:
                            matMulti(matrix, matemp, matOut);
                            printf("\nA * B =\n");
                            matOutput(matOut, PRECISION, WIDTH);
                            break;
                        case BREAK:
                            printf("\n�����ж�\n");
                            break;
                        }
                        fflush(stdin);
                        matFree(&matemp);
                        matFree(&matOut);
                        break;
                    }
                    break;
                case 2:
                    printf("���������B\n[����] [����] [����] (���軻��)\n");
                    printf("����B��������Ϊ%d\n", matrix.numRows);
                    printf("�����κη��������ж�����\n\n");
                    ungetc(ch = getchar(), stdin);
                    if (scanf("%d%d", &numRows, &numCols) != 2)
                    {
                        printf("\n�����ж�\n");
                        fflush(stdin);
                        break;
                    }
                    if (numCols != matrix.numRows)
                    {
                        printf("\n����B������������Ҫ��\n");
                        fflush(stdin);
                        break;
                    }
                    else
                    {
                        matInit(&matemp, numRows, numCols);
                        matInit(&matOut, matemp.numRows, matrix.numCols);
                        switch (matInput(matemp))
                        {
                        case SUCCESS:
                            matMulti(matemp, matrix, matOut);
                            printf("\nB * A =\n");
                            matOutput(matOut, PRECISION, WIDTH);
                            break;
                        case BREAK:
                            printf("\n�����ж�\n");
                            break;
                        }
                        fflush(stdin);
                        matFree(&matemp);
                        matFree(&matOut);
                        break;
                    }
                    break;
                default:
                    printf("ѡ�����\n");
                }
                pause();
                break;
            case CLEAR:
                state = FREE;
                break;
            default:
                printf("ѡ�����\n");
                pause();
            }
            break;
        case FREE:
            matFree(&matrix);
            state = START;
            break;
        }
    }
}