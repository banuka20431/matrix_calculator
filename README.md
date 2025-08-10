
# Matrix Calculator

A versatile **C language** program that can perform various matrix operations.  
It supports calculations on matrices of **any dimension** and on **any number of matrices**,  
limited only by a predefined constant.

---

## ✨ Features

- **Basic Operations**:
  - Addition
  - Subtraction
  - Multiplication
  - Division (element-wise)
  - Scalar multiplication
  - Scalar division

- **Advanced Operations**:
  - Transpose
  - Adjoint
  - Determinant
  - Inverse

- **Flexible Dimensions**:  
  Perform calculations with any size matrix (limited by the `MAX_SIZE` constant).

- **Multiple Matrices Support**:  
  Work with multiple matrices in a single session (limited by the `MAX_MATRICES` constant).

---

## ⚙️ Constants

The program uses the following constants to control maximum limits:

```c
#define MAX_SIZE 128      // Maximum rows/columns allowed per matrix
#define MAX_MATRICES 10   // Maximum number of matrices allowed in memory
```

You can increase or decrease these values in the source code to match your needs.

---

## 📂 File Structure

```
matrix_calculator.c   // Main source code
README.md             // Documentation file
```

---

## 🚀 How to Compile and Run

### 1. Clone the repository
```bash
git clone https://github.com/banuka20431/matrix_calculator.git
cd matrix_calculator
```

### 2. Compile
```bash
gcc matrix_calculator.c -o matrix_calculator -lm
```
> The `-lm` flag links the math library.

### 3. Run
```bash
./matrix_calculator
```

---

## 📖 Usage

1. Run the program.
2. Enter the number of matrices and their dimensions.
3. Fill in the values for each matrix.
4. Choose an operation from the menu.
5. The result will be displayed immediately.

---

## 🧮 Example

### Input:
Matrix A (2×2):
```
1 2
3 4
```

Matrix B (2×2):
```
5 6
7 8
```

### Operation:
**Addition**: `A + B`

### Output:
```
6   8
10  12
```

---

## 🛠 Supported Operations Table

| Operation Code | Description            |
|----------------|------------------------|
| ADD            | Matrix Addition         |
| SUB            | Matrix Subtraction      |
| MUL            | Matrix Multiplication   |
| DIV            | Element-wise Division   |
| MUL_SCLR       | Scalar Multiplication   |
| DIV_SCLR       | Scalar Division         |
| TRANSPOSE      | Matrix Transpose        |
| AJOINT         | Matrix Adjoint          |
| DETERMINANT    | Matrix Determinant      |
| INVERSE        | Matrix Inverse          |

---

## 📌 Notes
- The program handles **any dimension matrices** (up to `MAX_SIZE × MAX_SIZE`).
- You can work with **multiple matrices** in one session (up to `MAX_MATRICES`).
- If you need higher limits, just modify the constants and recompile.
- All determinant and inverse operations use double-precision floating-point for accuracy.

---

## 📜 License
This project is licensed under the MIT License — see the [LICENSE](LICENSE) file for details.

---
