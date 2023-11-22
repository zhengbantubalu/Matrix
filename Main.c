#include "MatHead.h"

#define START 0
#define MATINPUT 1
#define SELECT 2
#define MATFREE 3
#define END 4

int main(void)
{
    int state = START;
    int choice = 0;
    int numRows = 0, numCols = 0;
    char ch;
    double **matrix = NULL, **matOut = NULL;
    while (state != END)
    {
        switch (state)
        {
        case START:
            printf("������ѡ��:\n1.�������    2.�˳�����\n\n");
            choice = 0;
            scanf("%d", &choice);
            fflush(stdin);
            switch (choice)
            {
            case 1:
                state = MATINPUT;
                break;
            case 2:
                state = END;
                break;
            }
            putchar('\n');
            break;
        case MATINPUT:
            printf("������[����] [����] [����](���軻��)\n");
            printf("�����κη��������ж�����\n\n");
            printf("��1:\n4 4\n1 2 3 4\n2 3 4 1\n3 4 1 2\n4 1 2 3\n\n");
            printf("��2:\n4 5\n1 1 1 1 1\n3 2 1 1 -3\n0 1 3 2 5\n5 4 3 3 -1\n\n");
            printf("��3:\n3 3 3 -3 4 2 -3 4 0 -1 1\n\n");
            printf("��4:\n4 4 4 1 2 4 1 2 0 2 10 5 2 0 0 1 1 7\n\n");
            ungetc(ch = getchar(), stdin);
            if (scanf("%d%d", &numRows, &numCols) != 2)
            {
                printf("\n�����ж�\n\n");
                fflush(stdin);
                system("pause");
                putchar('\n');
                state = START;
                break;
            }
            matrix = matInit(numRows, numCols);
            switch (matEnIn(matrix, numRows, numCols))
            {
            case SUCCESS:
                state = SELECT;
                putchar('\n');
                break;
            case BREAK:
                printf("\n�����ж�\n\n");
                fflush(stdin);
                system("pause");
                putchar('\n');
                state = MATFREE;
                break;
            }
            break;
        case SELECT:
            printf("������ѡ��:\n1.�����׼����    2.��������      3.����������ʽ\n");
            printf("4.���н����ξ���  5.��������ξ���  6.��ת�þ���\n");
            printf("7.��������      8.�������        9.�������\n\n");
            choice = 0;
            scanf("%d", &choice);
            putchar('\n');
            fflush(stdin);
            switch (choice)
            {
            case 1:
                matStdTest(matrix, numRows, numCols);
                putchar('\n');
                system("pause");
                putchar('\n');
                break;
            case 2:
                printf("rank=%d\n\n", matRank(matrix, numRows, numCols, false));
                system("pause");
                putchar('\n');
                break;
            case 3:
                if (numRows != numCols)
                {
                    printf("ֻ�з������������ʽ\n\n");
                }
                else
                {
                    printf("det=%.3lf\n\n", matDet(matrix, numRows));
                }
                system("pause");
                putchar('\n');
                break;
            case 4:
                matOut = matInit(numRows, numCols);
                matEchelon(matrix, matOut, numRows, numCols);
                matEnOut(matOut, numRows, numCols);
                matFree(matOut, numRows);
                matOut = NULL;
                putchar('\n');
                system("pause");
                putchar('\n');
                break;
            case 5:
                matOut = matInit(numRows, numCols);
                matRedEche(matrix, matOut, numRows, numCols, false);
                matEnOut(matOut, numRows, numCols);
                matFree(matOut, numRows);
                matOut = NULL;
                putchar('\n');
                system("pause");
                putchar('\n');
                break;
            case 6:
                matOut = matInit(numCols, numRows);
                matTrans(matrix, matOut, numRows, numCols);
                matEnOut(matOut, numCols, numRows);
                matFree(matOut, numCols);
                matOut = NULL;
                putchar('\n');
                system("pause");
                putchar('\n');
                break;
            case 7:
                if (numRows != numCols)
                {
                    printf("ֻ�з��������������\n");
                }
                else
                {
                    matOut = matInit(numRows, numRows);
                    matAdj(matrix, matOut, numRows);
                    matEnOut(matOut, numRows, numRows);
                    matFree(matOut, numRows);
                    matOut = NULL;
                }
                putchar('\n');
                system("pause");
                putchar('\n');
                break;
            case 8:
                if (numRows != numCols)
                {
                    printf("ֻ�з�������������\n");
                }
                else
                {
                    matOut = matInit(numRows, numRows);
                    switch (matInverse(matrix, matOut, numRows))
                    {
                    case SUCCESS:
                        matEnOut(matOut, numRows, numRows);
                        break;
                    case SINGULAR:
                        printf("���󲻿���\n");
                        break;
                    }
                    matFree(matOut, numRows);
                    matOut = NULL;
                }
                putchar('\n');
                system("pause");
                putchar('\n');
                break;
            case 9:
                state = MATFREE;
                break;
            }
            break;
        case MATFREE:
            matFree(matrix, numRows);
            matrix = NULL;
            state = START;
            break;
        }
    }
    printf("�������\n\n");
    system("pause");
    return 0;
}