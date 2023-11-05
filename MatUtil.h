#define ZEROTHRES 0.00001
#define SUCCESS 0
#define ERROR 1
#define SINGULAR 2
#define EQUAL 3
#define UNEQUAL 4

double **matInit(int numRows, int numCols);
void matFree(double **matrix, int numRows);
void matEnIn(double **matrix, int numRows, int numCols);
void matLoIn(double **matrix, int rowStart, int rowEnd, int colStart, int colEnd);
void matEnOut(double **matrix, int numRows, int numCols);
void matLoOut(double **matrix, int rowStart, int rowEnd, int colStart, int colEnd);
void matEnCopy(double **matSource, double **matTarget, int numRows, int numCols);
int matLoCopy(double **matSource, double **matTarget,
              int rowSouStart, int rowSouEnd, int rowTarStart, int rowTarEnd,
              int colSouStart, int colSouEnd, int colTarStart, int colTarEnd);
int matEnEqual(double **matrix1, double **matrix2, int numRows, int numCols);
int matLoEqual(double **matrix1, double **matrix2,
               int rowStart1, int rowEnd1, int rowStart2, int rowEnd2,
               int colStart1, int colEnd1, int colStart2, int colEnd2);
void matEnAssignE(double **matrix, int numRows);
int matLoAssignE(double **matrix, int rowStart, int rowEnd, int colStart, int colEnd);