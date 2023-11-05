#define ZEROTHRES 0.00001
#define SUCCESS 1
#define ERROR -1
#define SINGULAR 0

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
void matAssignE(double **matrix, int numRows);