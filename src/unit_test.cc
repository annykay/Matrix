// #include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(TestGroupOne, init_test0) {
  S21Matrix TestMatrix;
  ASSERT_EQ(TestMatrix.GetRows(), 1);
  ASSERT_EQ(TestMatrix.GetCols(), 1);
  ASSERT_EQ(TestMatrix(0, 0), 1);
}

TEST(TestGroupOne, init_test1) {
  S21Matrix TestMatrix1(3, 3);
  S21Matrix TestMatrix2(1, 1);
  TestMatrix2(0, 0) = 1;
  TestMatrix2.SetCols(3);
  TestMatrix2.SetRows(3);
  TestMatrix1(0, 0) = 1;
  ASSERT_EQ(TestMatrix1 == TestMatrix2, true);
}

TEST(TestGroupOne, init_test2) {
  S21Matrix TestMatrix1(3, 3);
  S21Matrix TestMatrix2(1, 1);
  TestMatrix1(0, 0) = 1;
  TestMatrix2(0, 0) = 1;
  TestMatrix1.SetCols(1);
  TestMatrix1.SetRows(1);
  ASSERT_EQ(TestMatrix1 == TestMatrix2, true);
}
TEST(TestGroupOne, init_test3) {
  double **mat = new double *[2];
  for (int i = 0; i < 2; i++) {
    mat[i] = new double[3];
    for (int j = 0; j < 3; j++) {
      mat[i][j] = 0;
    }
  }
  mat[1][1] = 3;
  mat[0][1] = 2;

  S21Matrix TestMatrix1(2, 3, mat);
  S21Matrix TestMatrix2(2, 3);
  TestMatrix2(1, 1) = 3;
  TestMatrix2(0, 1) = 2;
  ASSERT_EQ(TestMatrix1 == TestMatrix2, true);

  for (int i = 0; i < 2; i++) {
    delete[] mat[i];
  }
  delete[] mat;
}

TEST(TestGroupOne, moveConstructor) {
  S21Matrix TestMatrix2(3, 3);
  S21Matrix TestMatrix3(3, 3);
  TestMatrix2(0, 0) = 1;
  TestMatrix3(0, 0) = 1;
  S21Matrix TestMatrix1(std::move(TestMatrix2));
  ASSERT_EQ(TestMatrix1 == TestMatrix3, true);
}

TEST(TestGroupOne, init_test4) {
  double **mat = new double *[2];
  for (int i = 0; i < 2; i++) {
    mat[i] = new double[3];
    for (int j = 0; j < 3; j++) {
      mat[i][j] = 4;
    }
  }

  S21Matrix TestMatrix1(2, 3, mat);
  S21Matrix TestMatrix2(2, 3, 4.0);
  ASSERT_EQ(TestMatrix1 == TestMatrix2, true);
  for (int i = 0; i < 2; i++) {
    delete[] mat[i];
  }
  delete[] mat;
}

TEST(TestGroupOne, incorrect_init_test0) {
  EXPECT_THROW(
      {
        try {
          S21Matrix TestMatrix(3, -1);
        } catch (std::exception &err) {
          EXPECT_STREQ("Wrong sizes entered", err.what());
          throw;
        }
      },
      std::out_of_range);
}

TEST(TestGroupOne, incorrect_init_test1) {
  EXPECT_THROW(
      {
        try {
          S21Matrix TestMatrix(-3, 1);
        } catch (std::exception &err) {
          EXPECT_STREQ("Wrong sizes entered", err.what());
          throw;
        }
      },
      std::out_of_range);
}

TEST(TestGroupOne, incorrect_init_test2) {
  EXPECT_THROW(
      {
        try {
          S21Matrix TestMatrix(0, 1);
        } catch (std::exception &err) {
          EXPECT_STREQ("Wrong sizes entered", err.what());
          throw;
        }
      },
      std::out_of_range);
}

TEST(TestGroupOne, incorrect_init_test3) {
  double **mat = new double *[2];
  for (int i = 0; i < 2; i++) {
    mat[i] = new double[3];
    for (int j = 0; j < 3; j++) {
      mat[i][j] = 0;
    }
  }
  EXPECT_THROW(
      {
        try {
          S21Matrix TestMatrix(3, -1, mat);
        } catch (std::exception &err) {
          EXPECT_STREQ("Wrong sizes entered", err.what());
          throw;
        }
      },
      std::out_of_range);
  for (int i = 0; i < 2; i++) {
    delete[] mat[i];
  }
  delete[] mat;
}

TEST(TestGroupOne, get_cols) {
  S21Matrix TestMatrix1(3, 3);
  ASSERT_EQ(TestMatrix1.GetCols(), 3);
  S21Matrix TestMatrix2;
  ASSERT_EQ(TestMatrix2.GetCols(), 1);
}

TEST(TestGroupOne, get_rows) {
  S21Matrix TestMatrix1(3, 3);
  ASSERT_EQ(TestMatrix1.GetRows(), 3);
  S21Matrix TestMatrix2;
  ASSERT_EQ(TestMatrix2.GetRows(), 1);
}

TEST(TestGroupOne, set_cols) {
  S21Matrix TestMatrix1(3, 3);
  TestMatrix1.SetCols(4);
  ASSERT_EQ(TestMatrix1.GetCols(), 4);
  TestMatrix1.SetCols(2);
  ASSERT_EQ(TestMatrix1.GetCols(), 2);
}

TEST(TestGroupOne, set_rows) {
  S21Matrix TestMatrix1(3, 3);
  TestMatrix1.SetRows(4);
  ASSERT_EQ(TestMatrix1.GetRows(), 4);
  TestMatrix1.SetRows(2);
  ASSERT_EQ(TestMatrix1.GetRows(), 2);
}

TEST(TestGroupOne, set_cols_incorrect) {
  S21Matrix TestMatrix1(3, 3);

  EXPECT_THROW(
      {
        try {
          TestMatrix1.SetRows(-4);
        } catch (std::exception &err) {
          EXPECT_STREQ("Wrong sizes entered", err.what());
          throw;
        }
      },
      std::out_of_range);
}

TEST(TestGroupOne, set_rows_incorrect) {
  S21Matrix TestMatrix1(3, 3);

  EXPECT_THROW(
      {
        try {
          TestMatrix1.SetCols(-4);
        } catch (std::exception &err) {
          EXPECT_STREQ("Wrong sizes entered", err.what());
          throw;
        }
      },
      std::out_of_range);
}

TEST(TestGroupOne, EqMatrix0) {
  S21Matrix TestMatrix1(3, 3, 2.0);
  S21Matrix TestMatrix2(3, 3, 1.0);
  ASSERT_EQ(TestMatrix1.EqMatrix(TestMatrix2), 0);
}

TEST(TestGroupOne, EqMatrix1) {
  S21Matrix TestMatrix1(1, 3, 2.0);
  S21Matrix TestMatrix2(3, 3, 2.0);
  ASSERT_EQ(TestMatrix1.EqMatrix(TestMatrix2), 0);
}

TEST(TestGroupOne, EqMatrix2) {
  S21Matrix TestMatrix1(3, 3, 2.0);
  S21Matrix TestMatrix2(3, 1, 2.0);
  ASSERT_EQ(TestMatrix1.EqMatrix(TestMatrix2), 0);
}

TEST(TestGroupOne, EqMatrix3) {
  S21Matrix TestMatrix1(3, 3, 2.0);
  S21Matrix TestMatrix2(3, 3, 2.0);
  ASSERT_EQ(TestMatrix1.EqMatrix(TestMatrix2), 1);
}

TEST(TestGroupOne, SumMatrix0) {
  S21Matrix TestMatrix1(3, 3, 2.0);
  S21Matrix TestMatrix2(3, 3, 1.0);
  S21Matrix TestMatrix3(3, 3, 3.0);
  TestMatrix1.SumMatrix(TestMatrix2);
  ASSERT_EQ(TestMatrix1 == TestMatrix3, true);
}

TEST(TestGroupOne, SumMatrix1) {
  S21Matrix TestMatrix1(3, 3, 2.0);
  S21Matrix TestMatrix2(3, 3, -1.0);
  S21Matrix TestMatrix3(3, 3, 3.0);
  TestMatrix3.SumMatrix(TestMatrix2);
  ASSERT_EQ(TestMatrix1 == TestMatrix3, true);
}

TEST(TestGroupOne, SumMatri4) {
  S21Matrix TestMatrix1(3, 3, 2.0);
  S21Matrix TestMatrix2(3, 3, 1.0);
  S21Matrix TestMatrix3(3, 3, 3.0);
  S21Matrix TestMatrix4(3, 3, 4.0);
  S21Matrix TestMatrix5(3, 3, 6.0);
  TestMatrix4 = TestMatrix1 + TestMatrix2 + TestMatrix3;

  ASSERT_EQ(TestMatrix4 == TestMatrix5, true);
}
TEST(TestGroupOne, IncorrectSumMatrix) {
  S21Matrix TestMatrix1(3, 3, 2.0);
  S21Matrix TestMatrix2(2, 3, 1.0);
  EXPECT_THROW(
      {
        try {
          TestMatrix1.SumMatrix(TestMatrix2);
        } catch (std::exception &err) {
          EXPECT_STREQ("Matrixes have different directions", err.what());
          throw;
        }
      },
      std::invalid_argument);
}

TEST(TestGroupOne, SubMatrix0) {
  S21Matrix TestMatrix1(3, 3, 2.0);
  S21Matrix TestMatrix2(3, 3, 1.0);
  S21Matrix TestMatrix3(3, 3, 1.0);
  TestMatrix1.SubMatrix(TestMatrix2);
  ASSERT_EQ(TestMatrix1 == TestMatrix3, true);
}

TEST(TestGroupOne, SubMatrix1) {
  S21Matrix TestMatrix1(3, 3, 2.0);
  S21Matrix TestMatrix2(3, 3, -1.0);
  S21Matrix TestMatrix3(3, 3, 3.0);
  TestMatrix1.SubMatrix(TestMatrix2);
  ASSERT_EQ(TestMatrix1 == TestMatrix3, true);
}

TEST(TestGroupOne, IncorrectSubMatrix) {
  S21Matrix TestMatrix1(3, 3, 2.0);
  S21Matrix TestMatrix2(2, 3, 1.0);
  EXPECT_THROW(
      {
        try {
          TestMatrix1.SubMatrix(TestMatrix2);
        } catch (std::exception &err) {
          EXPECT_STREQ("Matrixes have different directions", err.what());
          throw;
        }
      },
      std::invalid_argument);
}

TEST(TestGroupOne, MulNumber0) {
  S21Matrix TestMatrix1(3, 3, 2.0);
  S21Matrix TestMatrix2(3, 3, 4.0);
  TestMatrix1.MulNumber(2);
  ASSERT_EQ(TestMatrix1 == TestMatrix2, true);
}

TEST(TestGroupOne, MulNumber1) {
  S21Matrix TestMatrix1(3, 3, 2.0);
  S21Matrix TestMatrix2(3, 3, -4.0);
  TestMatrix1.MulNumber(-2);
  ASSERT_EQ(TestMatrix1 == TestMatrix2, true);
}

TEST(TestGroupOne, MulNumber2) {
  S21Matrix TestMatrix1(3, 3, 2.0);
  S21Matrix TestMatrix2(3, 3);
  TestMatrix1.MulNumber(0);
  ASSERT_EQ(TestMatrix1 == TestMatrix2, true);
}

TEST(TestGroupOne, MulMatrix0) {
  S21Matrix TestMatrix1(3, 3, 2.0);
  S21Matrix TestMatrix2(3, 3);
  S21Matrix TestMatrix3(3, 3, 2.0);
  for (int i = 0; i < 3; i++) {
    TestMatrix2(i, i) = 1;
  }
  TestMatrix1.MulMatrix(TestMatrix2);
  ASSERT_EQ(TestMatrix1 == TestMatrix3, true);
}

TEST(TestGroupOne, MulMatrix1) {
  S21Matrix TestMatrix1(3, 3, 1.0);
  S21Matrix TestMatrix2(3, 1, 1.0);
  S21Matrix TestMatrix3(3, 1, 3.0);
  TestMatrix1.MulMatrix(TestMatrix2);
  ASSERT_EQ(TestMatrix1 == TestMatrix3, true);
}

TEST(TestGroupOne, MulMatrix2) {
  double **mat = new double *[3];
  for (int i = 0; i < 3; i++) {
    mat[i] = new double[3];
    for (int j = 0; j < 3; j++) {
      mat[i][j] = i * 3 + j;
    }
  }
  S21Matrix TestMatrix1(3, 3, mat);

  TestMatrix1.MulMatrix(TestMatrix1);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      mat[i][j] = 15 + i * 27 + j * 3 + i * j * 9;
    }
  }
  S21Matrix TestMatrix2(3, 3, mat);
  ASSERT_EQ(TestMatrix1 == TestMatrix2, true);
  for (int i = 0; i < 3; i++) {
    delete[] mat[i];
  }
  delete[] mat;
}

TEST(TestGroupOne, IncorrectMulMatrix) {
  S21Matrix TestMatrix1(3, 3, 2.0);
  S21Matrix TestMatrix2(2, 3, 1.0);
  EXPECT_THROW(
      {
        try {
          TestMatrix1.MulMatrix(TestMatrix2);
        } catch (std::exception &err) {
          EXPECT_STREQ("Matrixes have different directions", err.what());
          throw;
        }
      },
      std::invalid_argument);
}

TEST(TestGroupOne, TransposeMatrix0) {
  double **mat = new double *[3];
  for (int i = 0; i < 3; i++) {
    mat[i] = new double[3];
    for (int j = 0; j < 3; j++) {
      mat[i][j] = i * 3 + j;
    }
  }
  S21Matrix TestMatrix1(3, 3, mat);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      mat[j][i] = i * 3 + j;
    }
  }
  S21Matrix TestMatrix2(3, 3, mat);
  ASSERT_EQ(TestMatrix1.Transpose() == TestMatrix2, true);
  for (int i = 0; i < 3; i++) {
    delete[] mat[i];
  }
  delete[] mat;
}

TEST(TestGroupOne, TransposeMatrix1) {
  double **mat = new double *[2];
  for (int i = 0; i < 2; i++) {
    mat[i] = new double[3];
    for (int j = 0; j < 3; j++) {
      mat[i][j] = i * 3 + j;
    }
  }
  S21Matrix TestMatrix1(2, 3, mat);
  double **mat1 = new double *[3];
  for (int i = 0; i < 3; i++) {
    mat1[i] = new double[2];
    for (int j = 0; j < 2; j++) {
      mat1[i][j] = j * 3 + i;
    }
  }
  S21Matrix TestMatrix2(3, 2, mat1);
  S21Matrix TestMatrix3(3, 2, mat1);
  TestMatrix3 = TestMatrix1.Transpose();
  ASSERT_EQ(TestMatrix3 == TestMatrix2, true);
  for (int i = 0; i < 2; i++) {
    delete[] mat[i];
  }
  delete[] mat;
  for (int i = 0; i < 3; i++) {
    delete[] mat1[i];
  }
  delete[] mat1;
}

TEST(TestGroupOne, CalcComplements0) {
  double **mat = new double *[3];
  for (int i = 0; i < 3; i++) {
    mat[i] = new double[3];
  }
  mat[0][0] = 1;
  mat[0][1] = 2;
  mat[0][2] = 3;
  mat[1][0] = 0;
  mat[1][1] = 4;
  mat[1][2] = 2;
  mat[2][0] = 5;
  mat[2][1] = 2;
  mat[2][2] = 1;

  double **mat_res = new double *[3];
  for (int i = 0; i < 3; i++) {
    mat_res[i] = new double[3];
  }
  mat_res[0][0] = 0;
  mat_res[0][1] = 10;
  mat_res[0][2] = -20;
  mat_res[1][0] = 4;
  mat_res[1][1] = -14;
  mat_res[1][2] = 8;
  mat_res[2][0] = -8;
  mat_res[2][1] = -2;
  mat_res[2][2] = 4;

  S21Matrix TestMatrix1(3, 3, mat);

  S21Matrix TestMatrix2(3, 3, mat_res);
  ASSERT_EQ(TestMatrix1.CalcComplements() == TestMatrix2, true);
  for (int i = 0; i < 3; i++) {
    delete[] mat[i];
  }
  delete[] mat;
  for (int i = 0; i < 3; i++) {
    delete[] mat_res[i];
  }
  delete[] mat_res;
}

TEST(TestGroupOne, IncorrectCalcComplements0) {
  double **mat = new double *[3];
  for (int i = 0; i < 3; i++) {
    mat[i] = new double[2];
  }
  mat[0][0] = 1;
  mat[0][1] = 2;
  mat[1][0] = 0;
  mat[1][1] = 4;
  mat[2][0] = 5;
  mat[2][1] = 2;
  S21Matrix TestMatrix1(3, 2, mat);
  EXPECT_THROW(
      {
        try {
          TestMatrix1.CalcComplements();
        } catch (std::exception &err) {
          EXPECT_STREQ("This matrix is not square", err.what());
          throw;
        }
      },
      std::invalid_argument);
  for (int i = 0; i < 3; i++) {
    delete[] mat[i];
  }
  delete[] mat;
}

TEST(TestGroupOne, IncorrectCalcComplements1) {
  S21Matrix TestMatrix1(1, 1, 1);
  EXPECT_THROW(
      {
        try {
          TestMatrix1.CalcComplements();
        } catch (std::exception &err) {
          EXPECT_STREQ("This matrix is of size 1x1", err.what());
          throw;
        }
      },
      std::invalid_argument);
}

TEST(TestGroupOne, InverseMat0) {
  double **mat = new double *[3];
  for (int i = 0; i < 3; i++) {
    mat[i] = new double[3];
  }
  mat[0][0] = 2;
  mat[0][1] = 5;
  mat[0][2] = 7;
  mat[1][0] = 6;
  mat[1][1] = 3;
  mat[1][2] = 4;
  mat[2][0] = 5;
  mat[2][1] = -2;
  mat[2][2] = -3;

  double **mat_res = new double *[3];
  for (int i = 0; i < 3; i++) {
    mat_res[i] = new double[3];
  }
  mat_res[0][0] = 1;
  mat_res[0][1] = -1;
  mat_res[0][2] = 1;
  mat_res[1][0] = -38;
  mat_res[1][1] = 41;
  mat_res[1][2] = -34;
  mat_res[2][0] = 27;
  mat_res[2][1] = -29;
  mat_res[2][2] = 24;

  S21Matrix TestMatrix1(3, 3, mat);

  S21Matrix TestMatrix2(3, 3, mat_res);
  ASSERT_EQ(TestMatrix1.InverseMatrix() == TestMatrix2, true);
  for (int i = 0; i < 3; i++) {
    delete[] mat[i];
  }
  delete[] mat;
  for (int i = 0; i < 3; i++) {
    delete[] mat_res[i];
  }
  delete[] mat_res;
}

TEST(TestGroupOne, InverseMat1) {
  S21Matrix TestMatrix1(1, 1, 1);

  S21Matrix TestMatrix2(1, 1, 1);

  ASSERT_EQ(TestMatrix1.InverseMatrix() == TestMatrix2, true);
}

TEST(TestGroupOne, OpEqMatrix) {
  S21Matrix TestMatrix1(2, 3, 4);
  ASSERT_EQ(TestMatrix1 == TestMatrix1, true);
}

TEST(TestGroupOne, PlusEqMat) {
  S21Matrix TestMatrix1(2, 3, 2);
  S21Matrix TestMatrix2(2, 3, 4);
  TestMatrix1 += TestMatrix1;
  ASSERT_EQ(TestMatrix1 == TestMatrix2, true);
}

TEST(TestGroupOne, PlusMat) {
  S21Matrix TestMatrix1(2, 3, 2);
  S21Matrix TestMatrix2(2, 3, 4);
  S21Matrix TestMatrix3 = TestMatrix1 + TestMatrix1;
  ASSERT_EQ(TestMatrix3 == TestMatrix2, true);
}
TEST(TestGroupOne, MinusEqMat) {
  S21Matrix TestMatrix1(2, 3, 2);
  S21Matrix TestMatrix2(2, 3, 4);
  TestMatrix2 -= TestMatrix1;

  ASSERT_EQ(TestMatrix1 == TestMatrix2, true);
}

TEST(TestGroupOne, MinusMat) {
  S21Matrix TestMatrix1(2, 3, 2);
  S21Matrix TestMatrix2(2, 3, 4);
  S21Matrix TestMatrix3 = TestMatrix2 - TestMatrix1;
  ASSERT_EQ(TestMatrix3 == TestMatrix1, true);
}

TEST(TestGroupOne, MulEqNum) {
  S21Matrix TestMatrix1(2, 3, 2);
  S21Matrix TestMatrix2(2, 3, 4);
  TestMatrix1 *= 2;
  ASSERT_EQ(TestMatrix1 == TestMatrix2, true);
}

TEST(TestGroupOne, MulNum) {
  S21Matrix TestMatrix1(2, 3, 2);
  S21Matrix TestMatrix2(2, 3, 4);
  S21Matrix TestMatrix3 = TestMatrix1 * 2.0;
  ASSERT_EQ(TestMatrix3 == TestMatrix2, true);
}

TEST(TestGroupOne, OpMulMatrix1) {
  S21Matrix TestMatrix1(3, 3, 1.0);
  S21Matrix TestMatrix2(3, 1, 1.0);
  S21Matrix TestMatrix3(3, 1, 3.0);
  TestMatrix1 = TestMatrix1 * TestMatrix2;
  ASSERT_EQ(TestMatrix1 == TestMatrix3, true);
}

TEST(TestGroupOne, OpMulEqMatrix1) {
  S21Matrix TestMatrix1(3, 3, 1.0);
  S21Matrix TestMatrix2(3, 1, 1.0);
  S21Matrix TestMatrix3(3, 1, 3.0);
  TestMatrix1 *= TestMatrix2;
  ASSERT_EQ(TestMatrix1 == TestMatrix3, true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  //  ::testing::InitGoogleMock(&argc, argv);

  return RUN_ALL_TESTS();
}
