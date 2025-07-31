/* matrixCalculator.c*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 128
#define MAX_MATRICES 10

#define ADD -1
#define SUB -2
#define MUL -3
#define DIV -4
#define MUL_SCLR -31
#define DIV_SCLR -41
#define TRANSPOSE -5
#define AJOINT -6

void get_matrix(float matrix[][MAX_SIZE], int rows, int cols)
{
    printf("%d", rows);
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            printf("\nEnter element value of [%d %d]: ", row, col);
            scanf("%f", &matrix[row][col]);
        }
    }
}

double scale_to_below_10(float n)
{
    double power = 0;
    int rem;
    do
    {
        rem = (int)(n / pow(10.0, power++));
    } while (rem >= 10);
    return power;
}

int calculate_spaces(float arr[][MAX_SIZE], int rows, int cols)
{
    double power, max_pow_val = 0;
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            power = scale_to_below_10(arr[row][col]);
            max_pow_val = max_pow_val < power ? power : max_pow_val;
        }
    }
    return (int)max_pow_val + 3; // add three for 3 characters representing the floating point and 2 decimal places
}

void print_matrix(float matrix[][MAX_SIZE], int rows, int cols)
{
    printf("\n\n");
    int max_spaces = calculate_spaces(matrix, rows, cols);
    for (int row = 0; row < rows; row++)
    {
        printf("|  ");
        for (int col = 0; col < cols; col++)
        {
            printf("%.2f  ", matrix[row][col]);
            for (int i = 0; i < max_spaces - (3 + scale_to_below_10(matrix[row][col])); i++)
            {
                // add three for 3 characters representing the floating point and 2 decimal places
                printf(" ");
            }
        }
        printf("|\n");
    }
}

int get_operation(int matrice_n)
{
    int option, options = 8;

    printf("------------------------------------------------");

    printf("\nSelect an operation\n");
    if (matrice_n >= 2)
    {
        printf("\n1. Add");
        printf("\n2. subtract");
        printf("\n3. Multiply");
        printf("\n4. Divid");
    }
    printf("\n5. Multiply by a scalar");
    printf("\n6. Divid by a scalar");
    printf("\n7. Get Transpose");
    printf("\n8. Get Ajoint");

    printf("\n\nEnter operation id ( %d to %d ): ", matrice_n >= 2 ? 1 : 5, options);

    scanf("%d", &option);
    printf("------------------------------------------------");

    if (matrice_n < 2 && option < 5)
    {
        return 0;
    }

    switch (option)
    {
    case 1:
    {
        return ADD;
        break;
    }
    case 2:
    {
        return SUB;
        break;
    }
    case 3:
    {
        return MUL;
        break;
    }
    case 4:
    {
        return DIV;
        break;
    }
    case 5:
    {
        return MUL_SCLR;
        break;
    }
    case 6:
    {
        return DIV_SCLR;
        break;
    }
    case 7:
    {
        return TRANSPOSE;
        break;
    }
    case 8:
    {
        return AJOINT;
        break;
    }
    default:
        return 0;
    }
}

void add(float matrix_1[][MAX_SIZE], float matrix_2[][MAX_SIZE], float answer_matrix[][MAX_SIZE], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            answer_matrix[i][j] = matrix_1[i][j] + matrix_2[i][j];
        }
    }
}

void subtract(float matrix_1[][MAX_SIZE], float matrix_2[][MAX_SIZE], float answer_matrix[][MAX_SIZE], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            answer_matrix[i][j] = matrix_1[i][j] - matrix_2[i][j];
        }
    }
}

void multiply(float matrix_1[][MAX_SIZE], float matrix_2[][MAX_SIZE], float answer_matrix[][MAX_SIZE], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            answer_matrix[i][j] = matrix_1[i][j] * matrix_2[i][j];
        }
    }
}

void divid(float matrix_1[][MAX_SIZE], float matrix_2[][MAX_SIZE], float answer_matrix[][MAX_SIZE], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            answer_matrix[i][j] = matrix_1[i][j] * (1 / matrix_2[i][j]);
        }
    }
}

void scalar_multiply(float matrix_1[][MAX_SIZE], float scalar, float answer_matrix[][MAX_SIZE], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            answer_matrix[i][j] = matrix_1[i][j] * scalar;
        }
    }
}

int main()
{
    float matrices[MAX_MATRICES][MAX_SIZE][MAX_SIZE], answer_matrices[MAX_MATRICES][MAX_SIZE][MAX_SIZE];
    int matrices_n = 0, rows[MAX_MATRICES], cols[MAX_MATRICES];
    int operation;

    printf("Enter number of matrices: ");
    scanf("%d", &matrices_n);

    for (int i = 0; i < matrices_n; i++)
    {
        printf("------------------------------------------------");
        printf("\nEnter Number of columns of matrix %d: ", i + 1);
        scanf("%d", &cols[i]);

        printf("Enter Number of rows matrix %d: ", i + 1);
        scanf("%d", &rows[i]);

        printf("------------------------------------------------");

        get_matrix(matrices[i], rows[i], cols[i]);
    }

    operation = get_operation(matrices_n);
    float dimension = -1;
    float scalar = 0.0f;

    if (!operation)
    {
        printf("\n(!)Invalid Selection");
        return -1;
    }

    if (matrices_n == 1)
    {
        if (operation != MUL_SCLR && operation != DIV_SCLR && operation != TRANSPOSE && operation != AJOINT)
        {
            printf("\n(!) At least 2 matrices required");
            return -1;
        }
        else if (operation == MUL_SCLR || operation == DIV_SCLR)
        {
            printf("\nEnter scalar value: ");
            scanf("%f", &scalar);
        }
    }

    switch (operation)
    {
        case ADD:
        {
            dimension = rows[0];
            for (int i = 0; i < (matrices_n - 1); i++)
            {
                if (rows[i] != dimension)
                {
                    printf("\n(!) Same dimension matrices required to perform addition among them");
                    return -1;
                }
                else
                {
                    if (i == 0)
                    {
                        add(matrices[i], matrices[i + 1], answer_matrices[i], dimension);
                    }
                    else
                    {
                        add(answer_matrices[i - 1], matrices[i + 1], answer_matrices[i], dimension);
                    }
                }
            }
            printf("\nAnswer: ");
            print_matrix(answer_matrices[matrices_n - 2], dimension, dimension);
            break;
        }

        case SUB:
        {
            for (int j = 0; j < (matrices_n - 1); j++)
            {
                dimension = rows[0];
                if (rows[j] != dimension)
                {
                    printf("\n(!) Same dimension matrices required to perform subtraction among them");
                    return -1;
                }
                else
                {
                    if (j == 0)
                    {
                        subtract(matrices[j], matrices[j + 1], answer_matrices[j], dimension);
                    }
                    else
                    {
                        subtract(answer_matrices[j - 1], matrices[j + 1], answer_matrices[j], dimension);
                    }
                }
            }
            printf("\nAnswer: ");
            print_matrix(answer_matrices[matrices_n - 2], dimension, dimension);
            break;
        }

        case MUL:
        {
            for (int j = 0; j < (matrices_n - 1); j++)
            {
                dimension = rows[0];
                if (rows[j] != dimension)
                {
                    printf("\n(!) Same dimension matrices required to perform subtraction among them");
                    return -1;
                }
                else
                {
                    if (j == 0)
                    {
                        multiply(matrices[j], matrices[j + 1], answer_matrices[j], dimension);
                    }
                    else
                    {
                        multiply(answer_matrices[j - 1], matrices[j + 1], answer_matrices[j], dimension);
                    }
                }
            }
            printf("\nAnswer: ");
            print_matrix(answer_matrices[matrices_n - 2], dimension, dimension);
            break;
        }

        case DIV:
        {
            for (int j = 0; j < (matrices_n - 1); j++)
            {
                dimension = rows[0];
                if (rows[j] != dimension)
                {
                    printf("\n(!) Same dimension matrices required to perform subtraction among them");
                    return -1;
                }
                else
                {
                    if (j == 0)
                    {
                        divid(matrices[j], matrices[j + 1], answer_matrices[j], dimension);
                    }
                    else
                    {
                        divid(answer_matrices[j - 1], matrices[j + 1], answer_matrices[j], dimension);
                    }
                }
            }
            printf("\nAnswer: ");
            print_matrix(answer_matrices[matrices_n - 2], dimension, dimension);
            break;
        }
        case MUL_SCLR: {
            scalar_multiply(matrices[0], scalar, answer_matrices[0], rows[0]);
            printf("\nAnswer: ");
            print_matrix(answer_matrices[0], rows[0], rows[0]);
            break;
        }
    }

    printf("\n");
    return 0;
}
