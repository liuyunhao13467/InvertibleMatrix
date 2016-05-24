#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

void freeMatrix(int n, int** array);
void printIdentityMatrix(int n, int** array);
void printInvertibleMatrix(int n, int** array);
void getIdentityMatrix(int n, int** array);
void getInvertibleMatrix(int n, int** array);
int putInvertibleMatrixIntoFile(int n, int** array);
int putIdentityMatrixIntoFile(int n, int** array);

int main(int argc, char* argv[])
{
	int k = 0;
        int n = 0;
        int flag = 0;
        int** array;

        printf("Please input the line and row number of the matrix:\n");
        scanf("%d",&n);

	//Create matrix
        printf("Start create a %d * %d matrix.\n",n,n);
        array = (int**)malloc(sizeof(int*)*n);

        for(k = 0; k < n; ++k)
        {
                array[k] = (int*)malloc(sizeof(int)*n);
        }

        printf("If you want get an identity matrix, please input 0, while if you want an invertible matrix, just input 1.\n");
        scanf("%d",&flag);

	if(flag == 0)
        {
                printf("Your input word is %d, so you want an identity matrix:\n",flag);
                //get indentity matrix
                getIdentityMatrix(n, array);

                //put indentity matrix into file
                putIdentityMatrixIntoFile(n, array);

                //print identity matrix
                printIdentityMatrix(n, array);
        }
	else if(flag == 1)
        {
                printf("Your input word is %d, so you want an invertible matrix:\n",flag);
                //get indentity matrix
                getIdentityMatrix(n, array);
                //get invertible matrix
                getInvertibleMatrix(n, array);
                //put invertible matrix into file
                putInvertibleMatrixIntoFile(n, array);
                //print invertible matrix
                printInvertibleMatrix(n, array);
        }
	else
        {
                printf("Error: You input a wrong number!\n");
                return -1;
        }

        //free matrix
        printf("Free matrix.\n");
        freeMatrix(n, array);

        return 1;
}

void freeMatrix(int n, int** array)
{
        int k = 0;
        for(k = 0; k < n; ++k)
        {
                free(array[k]);
        }
        free(array);
}

void printIdentityMatrix(int n, int** array)
{
        int i = 0;
        int j = 0;

        for(i = 0; i < n; ++i)
        {
                for(j = 0; j < n; ++j)
                {
                        printf("%d ",array[i][j]);
                }
                printf("\n");
        }
}

void printInvertibleMatrix(int n, int** array)
{
        int i = 0;
        int j = 0;

        for(i = 0; i < n; ++i)
        {
                for(j = 0; j < n; ++j)
                {
                        printf("%d\t",array[i][j]);
                }
                printf("\n");
        }
}

void getIdentityMatrix(int n, int** array)
{
        int r = 0;
        int c = 0;

        for(r = 0; r < n; ++r)
        {
                for(c = 0; c < n; ++c)
                {
                        if(r == c)
                                array[r][c] = 1;
                        else
                                array[r][c] = 0;
                }
        }

}

void getInvertibleMatrix(int n, int** array)
{
        int i = 0;
        int j = 0;
        int k = 0;
	int mainRowNum = 0;

        int* tempArray = NULL;

	srand((int)time(NULL));
	int transformTime = (int)(rand()%1000);
	printf("We will do %d times tansformation.\n",transformTime);

        tempArray = (int*)malloc(sizeof(int)*n);

        for(i = 0; i < transformTime; ++i)
        {
		mainRowNum = (int)(rand()%(n-1));
                for(k = 0; k < n; ++k)
			if(((UINT16_MAX - (array[mainRowNum][k])*((int)(rand()%5 - 10))) < 0) || ((UINT16_MAX*(-1)) - (array[mainRowNum][k])*((int)(rand()%5 - 10)) > tempArray[k]))
				tempArray[k] = (array[mainRowNum][k]);
			else
                        	tempArray[k] = (array[mainRowNum][k])*((int)(rand()%5 - 10));

                for(j = 0; j < n; ++j)
                        if(mainRowNum != j)
                                for(k = 0; k < n; ++k)
				{
					if(((UINT16_MAX - array[j][k]) < tempArray[k]) || ((UINT16_MAX*(-1)) - array[j][k] > tempArray[k]))
						array[j][k] = array[j][k]/4;
					else
						array[j][k] = array[j][k] + tempArray[k];
				}
        }

        free(tempArray);
}

int putIdentityMatrixIntoFile(int n, int** array)
{
        FILE* fp = NULL;
        int i = 0;
        int j = 0;

        if((fp = fopen("input","w"))==NULL)
        {
                printf("Error: writing file error!\n");
                return -1;
        }

        for(i = 0; i < n; ++i)
        {
                for(j = 0; j < n; ++j)
                {
                        if(j != (n-1))
                                fprintf(fp,"%d ", array[i][j]);
                        else
                                fprintf(fp,"%d", array[i][j]);
                }
                fputs("\n",fp);
        }

        fclose(fp);

        return 1;
}

int putInvertibleMatrixIntoFile(int n, int** array)
{
        FILE* fp = NULL;
        int i = 0;
        int j = 0;

        if((fp = fopen("input","w"))==NULL)
        {
                printf("Error: writing file error!\n");
                return -1;
        }

        for(i = 0; i < n; ++i)
        {
                for(j = 0; j < n; ++j)
                {
                        if(j != (n-1))
                                fprintf(fp,"%d\t", array[i][j]);
                        else
                                fprintf(fp,"%d", array[i][j]);
                }
                fputs("\n",fp);
        }

        fclose(fp);

        return 1;

}

