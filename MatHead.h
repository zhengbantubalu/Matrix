#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "MatOper.h"
#include "MatRowOper.h"
#include "MatStdTest.h"
#include "MatUtil.h"

#define ZEROTHRES 0.00001

#define SUCCESS 0
#define ERROR 1
#define BREAK 2
#define SINGULAR 3
#define EQUAL 4
#define UNEQUAL 5