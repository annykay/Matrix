#ifndef CPP1_s21_matrixplus_2_SRC_S21_MATRIX_OOP_H_
#define CPP1_s21_matrixplus_2_SRC_S21_MATRIX_OOP_H_

#include <iostream>
#include <stdlib.h>
#include <cmath> 
#include <cassert>

class S21Matrix {
    public:
        S21Matrix() noexcept;
        explicit S21Matrix(int nrow, int ncol);
        explicit S21Matrix(int nrow, int ncol, double** a);
        explicit S21Matrix(int nrow, int ncol, double a);
        S21Matrix(const S21Matrix& M);
        explicit S21Matrix(S21Matrix&& other);

        ~S21Matrix();
        
        void SetRows(const int new_rows);
        void SetCols(const int new_cols);

        int GetRows() const noexcept;
        int GetCols() const noexcept;

        bool EqMatrix(const S21Matrix& other) const noexcept;
        void SumMatrix(const S21Matrix& other); 
        void SubMatrix(const S21Matrix& other);
        void MulNumber(const double num) noexcept;
        void MulMatrix(const S21Matrix& other);
        
        S21Matrix Transpose() const noexcept;
        S21Matrix CalcComplements() const;
        double Determinant() const;
        S21Matrix InverseMatrix() const;

        S21Matrix operator+(const S21Matrix&);
        S21Matrix& operator+=(const S21Matrix&);
        S21Matrix operator-(const S21Matrix&);
        S21Matrix& operator-=(const S21Matrix&);
        S21Matrix operator*(const S21Matrix&);
        S21Matrix& operator*=(const S21Matrix&);
        S21Matrix operator*(const double num);
        S21Matrix& operator*=(const double num);
        bool operator==(S21Matrix &M);
        S21Matrix& operator=(const S21Matrix&);
        double& operator()(int i, int j);

    private:
        int rows_, cols_;
        double **matrix_;

        S21Matrix CalcComplementMatrix(int a, int b) const;
        void RemoveMatrix();
        void CopyMatrix(S21Matrix to_copy);
        void CreateMatrix();
        void RemakeMatrix(const S21Matrix M);
};

#endif