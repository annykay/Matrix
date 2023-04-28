#include "s21_matrix_oop.h"
void S21Matrix::CreateMatrix() {
  matrix_ = new double *[rows_];
  if (!matrix_) {
    delete[] matrix_;
    std::cout << "The memory hasn't been allocated" << std::endl;
  } else {
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new double[cols_]{0};
      if (!matrix_[i]) {
        for (int j = 0; j < i; j++) delete matrix_[j];
        delete[] matrix_;
        std::cout << "The memory hasn't been allocated" << std::endl;
      }
    }
  }
}
void S21Matrix::CopyMatrix(S21Matrix to_copy) {
  if (matrix_ && to_copy.matrix_) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = to_copy.matrix_[i][j];
      }
    }
  }
}
S21Matrix::S21Matrix(int nrow, int ncol) {
  if (nrow > 0 && ncol > 0) {
    rows_ = nrow;
    cols_ = ncol;
    CreateMatrix();
  } else {
    throw std::out_of_range("Wrong sizes entered");
  }
}
S21Matrix::S21Matrix(int nrow, int ncol, double **a) : S21Matrix(nrow, ncol) {
  try {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = a[i][j];
      }
    }
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }
}

S21Matrix::S21Matrix(int nrow, int ncol, double a) : S21Matrix(nrow, ncol) {
  try {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = a;
      }
    }
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }
}

S21Matrix::S21Matrix(const S21Matrix &M)
    : S21Matrix(M.rows_, M.cols_, M.matrix_) {}
S21Matrix::S21Matrix() noexcept : S21Matrix(1, 1) { matrix_[0][0] = 1; }
S21Matrix::S21Matrix(S21Matrix &&other) {
  this->matrix_ = other.matrix_;
  this->cols_ = other.cols_;
  this->rows_ = other.rows_;
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}
S21Matrix::~S21Matrix() { RemoveMatrix(); }

void S21Matrix::RemakeMatrix(const S21Matrix M) {
  RemoveMatrix();
  cols_ = M.cols_;
  rows_ = M.rows_;
  CreateMatrix();
  CopyMatrix(M);
}
void S21Matrix::SetCols(const int new_cols) {
  if (new_cols <= 0) throw std::out_of_range("Wrong sizes entered");
  S21Matrix tmp(rows_, new_cols);
  int min = new_cols < cols_ ? new_cols : cols_;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < min; j++) {
      tmp.matrix_[i][j] = matrix_[i][j];
    }
  }
  RemakeMatrix(tmp);
}

void S21Matrix::SetRows(const int new_rows) {
  if (new_rows <= 0) throw std::out_of_range("Wrong sizes entered");
  S21Matrix tmp(new_rows, cols_);
  int min = new_rows < rows_ ? new_rows : rows_;
  for (int i = 0; i < min; i++) {
    for (int j = 0; j < cols_; j++) {
      tmp.matrix_[i][j] = matrix_[i][j];
    }
  }
  RemakeMatrix(tmp);
}

int S21Matrix::GetCols() const noexcept { return cols_; }

int S21Matrix::GetRows() const noexcept { return rows_; }

bool S21Matrix::EqMatrix(const S21Matrix &other) const noexcept {
  bool res = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    res = false;
  } else {
    for (int i = 0; i < rows_ && res; i++) {
      for (int j = 0; j < cols_ && res; j++) {
        if (fabs(other.matrix_[i][j] - matrix_[i][j]) > 1e-6) res = false;
      }
    }
  }
  return res;
}
void S21Matrix::SumMatrix(const S21Matrix &other) {
  if ((rows_ != other.rows_) || (cols_ != other.cols_))
    throw std::invalid_argument("Matrixes have different directions");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if ((rows_ != other.rows_) || (cols_ != other.cols_))
    throw std::invalid_argument("Matrixes have different directions");
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_)
    throw std::invalid_argument("Matrixes have different directions");
  S21Matrix tmp(rows_, other.cols_);
  for (int i = 0; i < tmp.rows_; i++) {
    for (int j = 0; j < tmp.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        tmp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  RemakeMatrix(tmp);
}

S21Matrix S21Matrix::Transpose() const noexcept {
  S21Matrix res(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[j][i] = matrix_[i][j];
    }
  }
  return res;
}

S21Matrix S21Matrix::CalcComplementMatrix(int a, int b) const {
  if (a < 0 || b < 0) throw "Indexes are negative!";
  S21Matrix res(rows_ - 1, cols_ - 1);

  int sub_i = 0, sub_j = 0;
  for (int i = 0; i < rows_; i++) {
    if (a == i) {
      sub_i = 1;
    } else {
      sub_j = 0;
      for (int j = 0; j < cols_; j++) {
        if (b == j) {
          sub_j = 1;
        } else {
          res.matrix_[i - sub_i][j - sub_j] = matrix_[i][j];
        }
      }
    }
  }
  return res;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) throw std::invalid_argument("This matrix is not square");
  if (rows_ == 1) throw std::invalid_argument("This matrix is of size 1x1");
  S21Matrix res(rows_, cols_);
  S21Matrix tmp(rows_, cols_);

  double det = 0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      tmp = CalcComplementMatrix(i, j);
      det = tmp.Determinant();
      det *= powl(-1, i + j);
      res.matrix_[i][j] = det;
    }
  }
  return res;
}

double S21Matrix::Determinant() const {
  double result = 0;
  if (cols_ != rows_) throw "This matrix is not square";
  if (rows_ == 1) {
    return matrix_[0][0];
  } else if (rows_ == 2) {
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    S21Matrix tmp;
    double temp_res = 0;
    for (int i = 0; i < cols_; i++) {
      tmp = CalcComplementMatrix(0, i);
      temp_res = tmp.Determinant();

      temp_res *= matrix_[0][i];
      temp_res *= (i & 1) ? -1 : 1;
      result += temp_res;
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double det = 0;
  try {
    det = Determinant();
  } catch (const char *msg) {
    std::cout << msg << std::endl;
  }
  if (fabs(det) < 1e-6) throw "The determinant is zero";
  S21Matrix res(rows_, cols_);
  if (cols_ == 1) {
    res.matrix_[0][0] = 1. / matrix_[0][0];
  } else {
    res = CalcComplements();
    res = res.Transpose();
    res.MulNumber(1. / det);
  }
  return res;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &M) {
  SumMatrix(M);
  return *this;
}
S21Matrix S21Matrix::operator+(const S21Matrix &M) {
  S21Matrix tmp(*this);
  tmp.SumMatrix(M);
  return tmp;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &M) {
  SubMatrix(M);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix &M) {
  S21Matrix tmp(*this);
  tmp.SubMatrix(M);
  return tmp;
}
S21Matrix &S21Matrix::operator*=(const S21Matrix &M) {
  MulMatrix(M);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix &M) {
  S21Matrix tmp(*this);
  tmp.MulMatrix(M);
  return tmp;
}
S21Matrix &S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix tmp(*this);
  tmp.MulNumber(num);
  return tmp;
}

S21Matrix &S21Matrix::operator=(const S21Matrix &M) {
  RemakeMatrix(M);
  return *this;
}
bool S21Matrix::operator==(S21Matrix &M) { return this->EqMatrix(M); }

double &S21Matrix::operator()(int i, int j) {
  assert(i < rows_ && i >= 0 && j < cols_ && j >= 0);
  return matrix_[i][j];
}
void S21Matrix::RemoveMatrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
}