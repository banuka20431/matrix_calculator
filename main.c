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
#define ADJOINT -6
#define DETERMINENT -7
#define INVERSE -8

void get_matrix(float matrix[][MAX_SIZE], int rows, int cols);
int get_operation(int matrice_n);

double scale_to_below_10(float n);
int calculate_spaces(float arr[][MAX_SIZE], int rows, int cols);
void print_matrix(float matrix[][MAX_SIZE], int rows, int cols);

float get_determinater(float matrix[][MAX_SIZE], int size);
void get_cofactor_matrix(float matrix[][MAX_SIZE], float cofactor_matrix[][MAX_SIZE], int size);
void get_transpose(float matrix[][MAX_SIZE], float transpose_matrix[][MAX_SIZE], int size);
void get_adjoint_matrix(float matrix[][MAX_SIZE], float adjoint_matrix[][MAX_SIZE], int size);
void invert(float matrix[][MAX_SIZE], float inverse_matrix[][MAX_SIZE], int size);

float add(float value_1, float value_2);
float subtract(float value_1, float value_2);
void multiply(float matrix_1[][MAX_SIZE], float matrix_2[][MAX_SIZE], float answer_matrix[][MAX_SIZE], int rows, int cols);
void divid(float matrix_1[][MAX_SIZE], float matrix_2[][MAX_SIZE], float answer_matrix[][MAX_SIZE], int size);
float scalar_multiply(float scalar, float idx_value);
float scalar_divid(float scalar, float idx_value);

void calculate(float matrix_1[][MAX_SIZE], float matrix_2[][MAX_SIZE], float answer_matrix[][MAX_SIZE], int size, float (*func)(float val_1, float val_2));
void calculate_wscalar(float matrix_1[][MAX_SIZE], float scalar, float answer_matrix[][MAX_SIZE], int size, float (*func)(float val_1, float val_2));


void get_matrix(float matrix[][MAX_SIZE], int rows, int cols)
{
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
    int option, options = 10;

    printf("------------------------------------------------");

    printf("\nSelect an operation\n");
    if (matrice_n >= 2)
    {
        printf("\n01. Add");
        printf("\n02. subtract");
        printf("\n03. Multiply");
        printf("\n04. Divid");
    }
    else
    {
        printf("\n05. Multiply by a scalar");
        printf("\n06. Divid by a scalar");
        printf("\n07. Get Determinent");
        printf("\n08. Get Inverse");
        printf("\n09. Get Transpose");
        printf("\n10. Get Ajoint");
    }

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
        return DETERMINENT;
        break;
    }
    case 8:
    {
        return INVERSE;
        break;
    }
    case 9:
    {
        return TRANSPOSE;
        break;
    }
    case 10:
    {
        return ADJOINT;
        break;
    }
    default:
        return 0;
    }
}

void calculate(float matrix_1[][MAX_SIZE], float matrix_2[][MAX_SIZE], float answer_matrix[][MAX_SIZE], int size, float (*func)(float val_1, float val_2))
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            answer_matrix[i][j] = (*func)(matrix_1[i][j], matrix_2[i][j]);
        }
    }
}

void calculate_wscalar(float matrix_1[][MAX_SIZE], float scalar, float answer_matrix[][MAX_SIZE], int size, float (*func)(float val_1, float val_2))
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            answer_matrix[i][j] = (*func)(matrix_1[i][j], scalar);
        }
    }
}

float add(float value_1, float value_2)
{
    return value_1 + value_2;
}

float subtract(float value_1, float value_2)
{
    return value_1 - value_2;
}

float scalar_multiply(float scalar, float idx_value)
{
    return idx_value * scalar;
}

void multiply(float matrix_1[][MAX_SIZE], float matrix_2[][MAX_SIZE], float answer_matrix[][MAX_SIZE], int rows, int cols)
{

    int col, row;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            col = 0;
            row = 0;
            while (col < cols)
            {
                answer_matrix[i][j] += matrix_1[i][col] * matrix_2[row][j];
                col++;
                row++;
            }
        }
    }

}

float scalar_divid(float scalar, float idx_value)
{
    return idx_value / scalar;
}

float get_determinater(float matrix[][MAX_SIZE], int size)
{

    float det = 0.0;

    if(size < 1) {
        return 0;
    }

    if(size == 1) {
        return matrix[0][0];
    }

    if (size == 2)
    {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    float matrix_t[MAX_SIZE][MAX_SIZE];
    int next_col, next_row, selected_row = 0;

    for (int selected_col = 0; selected_col < size; selected_col++)
    {
        next_row = 0;
        for(int i = 0; i < size; i++) {
            if(selected_row == i) continue;
            next_col = 0;
            for(int k = 0; k < size; k++) {
                if(selected_col == k) continue;
                matrix_t[next_row][next_col++] = matrix[i][k];
            }
            next_row++;
        }
        float sign = pow(-1, (double)(selected_row + selected_col));
        det += sign * matrix[selected_row][selected_col] * get_determinater(matrix_t, size-1);
    }

    return det;
}

void invert(float matrix[][MAX_SIZE], float inverse_matrix[][MAX_SIZE], int size)
{
    float determinent = get_determinater(matrix, size);
    float cofactor_matrix[MAX_SIZE][MAX_SIZE];
    float transposed_cofactor_matrix[MAX_SIZE][MAX_SIZE];

    get_cofactor_matrix(matrix, cofactor_matrix, size);
    get_transpose(cofactor_matrix, transposed_cofactor_matrix, size);
    calculate_wscalar(transposed_cofactor_matrix, 1 / determinent, inverse_matrix, size, *scalar_multiply);
}

void divid(float matrix_1[][MAX_SIZE], float matrix_2[][MAX_SIZE], float answer_matrix[][MAX_SIZE], int size)
{
    float inverse_matrix[MAX_SIZE][MAX_SIZE];
    invert(matrix_2, inverse_matrix, size);
    multiply(matrix_1, inverse_matrix, answer_matrix, size, size);
}

void get_adjoint_matrix(float matrix[][MAX_SIZE], float adjoint_matrix[][MAX_SIZE], int size) {
    float cofactor_matrix[MAX_SIZE][MAX_SIZE];

    get_cofactor_matrix(matrix, cofactor_matrix, size);

    get_transpose(cofactor_matrix, cofactor_matrix, size);

    adjoint_matrix = cofactor_matrix;
}

void get_cofactor_matrix(float matrix[][MAX_SIZE], float cofactor_matrix[][MAX_SIZE], int size) {

    float matrix_t[size - 1][size - 1];
    float element_value;

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {

            for(int row = 0; row < size; row++) {

                if(row == i) continue;

                for(int col = 0; col < size; col++) {
                    if(col == j) continue;

                    if (size == 2) {
                        cofactor_matrix[i][j] = matrix[row][col] * pow(-1, i + j);
                    } else {
                        matrix_t[i][j] = matrix[row][col];
                    }
                }

            }
            if (size > 2) {
                cofactor_matrix[i][j] = matrix[i][j] * get_determinater(matrix, size) * pow(-1, i + j);
            }

        }
    }

}

void get_transpose(float matrix[][MAX_SIZE], float transpose_matrix[][MAX_SIZE], int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            transpose_matrix[i][j] = matrix[j][i];
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

        printf("\nEnter Number of rows matrix %d: ", i + 1);
        scanf("%d", &rows[i]);

        printf("Enter Number of columns of matrix %d: ", i + 1);
        scanf("%d", &cols[i]);

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
        if (operation == MUL || operation == DIV || operation == ADD || operation == SUB)
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
        int col_c = cols[0], row_c = rows[0];

        for (int i = 0; i < (matrices_n - 1); i++)
        {
            if (i != 0)
            {
                if (rows[i] != row_c || cols[i] != col_c)
                {
                    printf("\n(!) Same dimension matrices required to perform addition among them");
                    return -1;
                }
            }

            if (i == 0)
            {
                calculate(matrices[i], matrices[i + 1], answer_matrices[i], dimension, *add);
            }
            else
            {
                calculate(answer_matrices[i - 1], matrices[i + 1], answer_matrices[i], dimension, *add);
            }
        }

        printf("\nAnswer: ");
        print_matrix(answer_matrices[matrices_n - 2], dimension, dimension);
        break;
    }

    case SUB:
    {
        int col_c = cols[0], row_c = rows[0];

        for (int j = 0; j < (matrices_n - 1); j++)
        {
            if (j != 0)
            {
                if (rows[j] != row_c || cols[j] != col_c)
                {
                    printf("\n(!) Same dimension matrices required to perform addition among them");
                    return -1;
                }
            }

            if (j == 0)
            {
                calculate(matrices[j], matrices[j + 1], answer_matrices[j], dimension, *subtract);
            }
            else
            {
                calculate(answer_matrices[j - 1], matrices[j + 1], answer_matrices[j], dimension, *subtract);
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
            if (j != 0)
            {
                if (rows[j] != cols[j - 1] || cols[j] != rows[j - 1])
                {
                    printf("\n(!) Same dimension matrices required to perform addition among them");
                    return -1;
                }
            }

            if (j == 0)
            {
                multiply(matrices[j], matrices[j + 1], answer_matrices[j], rows[0], cols[1]);
            }
            else
            {
                multiply(answer_matrices[j - 1], matrices[j + 1], answer_matrices[j], rows[0], cols[1]);
            }
        }

        printf("\nAnswer: ");
        print_matrix(answer_matrices[matrices_n - 2], rows[0], cols[1]);
        break;
    }

    case DIV:
    {
        float det = 0.0;
        dimension = rows[0];

        for (int j = 0; j < (matrices_n - 1); j++)
        {

            if (rows[j] != dimension || cols[j] != dimension)
            {
                printf("\n(!) Same dimension squre matrices required to perform division among them");
                return -1;
            }

            if (j == 0)
            {
                divid(matrices[j], matrices[j + 1], answer_matrices[j], dimension);
            }
            else
            {
                divid(answer_matrices[j - 1], matrices[j + 1], answer_matrices[j], dimension);
            }
        }

        printf("\nAnswer: ");
        print_matrix(answer_matrices[matrices_n - 2], dimension, dimension);
        break;
    }

    case MUL_SCLR:
    {
        calculate_wscalar(matrices[0], scalar, answer_matrices[0], rows[0], *scalar_multiply);
        printf("\nAnswer: ");
        print_matrix(answer_matrices[0], rows[0], rows[0]);
        break;
    }

    case DIV_SCLR:
    {
        calculate_wscalar(matrices[0], scalar, answer_matrices[0], rows[0], *scalar_divid);
        printf("\nAnswer: ");
        print_matrix(answer_matrices[0], rows[0], rows[0]);
        break;
    }

    case DETERMINENT:
    {
        printf("\nDeterminent value: %.2f", get_determinater(matrices[0], rows[0]));
    }

    case ADJOINT:
    {
        float adjoint_matrix[MAX_SIZE][MAX_SIZE];

        if (rows[0] != cols[0])
        {
                printf("\n(!) Ajoint can be calculated only for squre matrices");
                return -1;
        }

        get_cofactor_matrix(matrices[0], adjoint_matrix,  rows[0]);

        printf("\nAnswer: ");
        print_matrix(adjoint_matrix, rows[0], cols[0]);
        break;
    }

    case INVERSE:
    {
        float inverse_matrix[MAX_SIZE][MAX_SIZE];

        if (rows[0] != cols[0])
        {
                printf("\n(!) Inverse can be calculated only for squre matrices");
                return -1;
        }

        invert(matrices[0], inverse_matrix,  rows[0]);

        printf("\nAnswer: ");
        print_matrix(inverse_matrix, rows[0], cols[0]);
        break;
    }
    }

    printf("\n");
    return 0;
}
