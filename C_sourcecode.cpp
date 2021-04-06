#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    FILE *fp1 = fopen("matrix.csv", "r");
    char buf[100];
    fscanf(fp1, "%[^\n]", buf);
    fseek(fp1, 2, SEEK_CUR);
    //printf("%s\n", buf);

    const int NFA_SIZE = strlen(buf) / 2;
    const int DFA_SIZE = (int)pow(2, NFA_SIZE);
    //printf("%d\n",NFA_SIZE);

    //int **input_matrix = (int **)malloc(NFA_SIZE * sizeof(int *));
    int input_matrix[NFA_SIZE][NFA_SIZE];
    int output_matrix[DFA_SIZE][DFA_SIZE];

    //* 初始化输出矩阵
    for (int i = 0; i < DFA_SIZE; i++)
    {
        for (int j = 0; j < DFA_SIZE; j++)
        {
            output_matrix[i][j] = 0;
        }
    }

    //* 从文件读取数据
    for (int i = 0; i < NFA_SIZE; i++)
    {
        //*(input_matrix+i) = (int *)malloc(NFA_SIZE * sizeof(int));

        char buf_line[100];
        fscanf(fp1, "%[^\n]", buf_line);
        fseek(fp1, 2, SEEK_CUR);
        for (int j = 1; j <= NFA_SIZE; j++)
        {
            input_matrix[i][j - 1] = buf_line[j * 2] - '0';
        }
        //printf("%s\n", buf_line);
    }

    // * 检查输入矩阵
    for (int i = 0; i < NFA_SIZE; i++)
    {
        for (int j = 0; j < NFA_SIZE; j++)
        {
            printf("%d ", input_matrix[i][j]);
        }
        printf("\n");
    }

    // * 输出矩阵列继承
    for (int i = 0; i < NFA_SIZE; i++)
    {
        for (int j = 0; j < NFA_SIZE; j++)
        {

            int opi = pow(2, i);
            int opj = pow(2, j);
            output_matrix[opi][opj] = input_matrix[i][j];

            int tmp = output_matrix[opi][opj];
        }
    }

    // *检查继承结果
    for (int i = 0; i < DFA_SIZE; i++)
    {
        for (int j = 0; j < DFA_SIZE; j++)
        {
            printf("%d ", output_matrix[i][j]);
        }
        printf("\n");
    }

    printf("--------------------------\n");

    // *输出矩阵列拓展
    for (int i = 0; i < NFA_SIZE; i++)
    {
        for (int j = 0; j < DFA_SIZE; j++)
        {
            int j_bin = j;
            int res = 1;
            for (int k = 0; k < NFA_SIZE; k++)
            {
                int m = j_bin % 2;
                j_bin = j_bin / 2;
                int opi = (int)pow(2, i);
                int opj = (int)pow(2, k);
                int val = output_matrix[(int)pow(2, i)][(int)pow(2, k)];
                if (m == 1)
                {
                    res = res & val;
                }
            }
            output_matrix[(int)pow(2, i)][j] = res;
        }
    }

    // *检查列拓展
    for (int i = 0; i < DFA_SIZE; i++)
    {
        for (int j = 0; j < DFA_SIZE; j++)
        {
            printf("%d ", output_matrix[i][j]);
        }
        printf("\n");
    }

    // *输出矩阵行拓展
    for (int i = 0; i < DFA_SIZE; i++)
    {
        for (int j = 0; j < DFA_SIZE; j++)
        {
            int i_bin = i;
            int res = 0;
            for (int k = 0; k < NFA_SIZE && i_bin > 0; k++)
            {

                int m = i_bin % 2;
                i_bin = i_bin / 2;

                int opi = (int)pow(2, k);

                if (m == 1)
                {
                    int val = output_matrix[(int)pow(2, k)][j];
                    res = res | output_matrix[(int)pow(2, k)][j];
                }
            }
            output_matrix[i][j] = res;
            //printf("%d %d %d\n", i, j, res);
        }
    }

    printf("--------------------------\n");

    // *检查行拓展
    for (int i = 0; i < DFA_SIZE; i++)
    {
        for (int j = 0; j < DFA_SIZE; j++)
        {
            printf("%d ", output_matrix[i][j]);
        }
        printf("\n");
    }

    // *清楚多余状态
    for (int i = 0; i < DFA_SIZE; i++)
    {
        for (int j = DFA_SIZE - 1; j >= 0; j--)
        {
            if (output_matrix[i][j] == 1)
            {
                for (int k = j - 1; k > 0; k--)
                {
                    output_matrix[i][k] = 0;
                }
                break;
            }
        }
    }

    printf("-----------------------\n");

    // *检查清除结果
    for (int i = 0; i < DFA_SIZE; i++)
    {
        for (int j = 0; j < DFA_SIZE; j++)
        {
            printf("%d ", output_matrix[i][j]);
        }
        printf("\n");
    }
}