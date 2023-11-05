#include "MatHead.h"

#define MATINPUT 0
#define MATSTDTEST 1
#define MATFREE 2
#define FINALFREE 3
#define END 4

int main(void)
{
    int state = MATINPUT;
    int numRows = 0, numCols = 0;
    char ch;
    double **matrix = NULL;
    while (state != END)
    {
        switch (state)
        {
        case MATINPUT:
            printf("请输入[行数] [列数] [矩阵](无需换行)\n");
            printf("输入任何非数字以结束程序\n\n");
            printf("例1:\n4 4\n1 2 3 4\n2 3 4 1\n3 4 1 2\n4 1 2 3\n\n");
            printf("例2:\n4 5\n1 1 1 1 1\n3 2 1 1 -3\n0 1 3 2 5\n5 4 3 3 -1\n\n");
            printf("例3:\n3 3 3 -3 4 2 -3 4 0 -1 1\n\n");
            printf("例4:\n4 4 4 1 2 4 1 2 0 2 10 5 2 0 0 1 1 7\n\n");
            ungetc(ch = getchar(), stdin);
            if (scanf("%d%d", &numRows, &numCols) != 2)
            {
                state = END;
                break;
            }
            matrix = matInit(numRows, numCols);
            switch (matEnIn(matrix, numRows, numCols))
            {
            case SUCCESS:
                state = MATSTDTEST;
                break;
            case BREAK:
                state = FINALFREE;
                break;
            }
            break;
        case MATSTDTEST:
            matStdTest(matrix, numRows, numCols);
            system("pause");
            putchar('\n');
            state = MATFREE;
            break;
        case MATFREE:
            matFree(matrix, numRows);
            matrix = NULL;
            state = MATINPUT;
            break;
        case FINALFREE:
            matFree(matrix, numRows);
            matrix = NULL;
            state = END;
            break;
        }
    }
    printf("\n程序结束\n\n");
    system("pause");
    return 0;
}