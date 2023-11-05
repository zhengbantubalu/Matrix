void matRowSwap(double **matrix, int numRows, int numCols, int index1, int index2, bool isRowOper);
void matRowScaMul(double **matrix, int numRows, int numCols, int index, double multiplier, bool isRowOper);
void matRowAdd(double **matrix, int numRows, int numCols,
               int indexSource, int indexTarget, double multiplier, bool isRowOper);