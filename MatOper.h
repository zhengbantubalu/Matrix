void matAdd(double **matSource1, double **matSource2, double **matTarget, int numRows, int numCols);
void matSub(double **matMinu, double **matSub, double **matTarget, int numRows, int numCols);
void matScaMul(double **matSource, double **matTarget, int numRows, int numCols, double multiplier);
void matMul(double **matLeft, double **matRight, double **matTarget,
            int numRowsL, int numColsL, int numColsR);
void matTrans(double **matSource, double **matTarget, int numRows, int numCols);
int matInverse(double **matSource, double **matTarget, int numRows);
void matAdj(double **matSource, double **matTarget, int numRows);
double matEchelon(double **matSource, double **matTarget, int numRows, int numCols);
void matRedEche(double **matSource, double **matTarget, int numRows, int numCols, bool isEche);
int matRank(double **matrix, int numRows, int numCols, bool isEche);
double matDet(double **matrix, int numRows);
double matMinor(double **matrix, int numRows, int indexRow, int indexCol);
double matAlgMin(double **matrix, int numRows, int indexRow, int indexCol);