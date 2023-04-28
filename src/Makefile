FLAGS=-Wall -Wextra -Werror -std=c++17
SOURCES=s21_matrix_oop.cc
CC=g++
OBJECTS=$(SOURCES:.cc=.o)
TESTSFLAGS=-lgtest -pthread
COVERAGE_FLAGS=--coverage
LDFLAGS="-lgcov"

all: library
s21_matrix_oop.a: library
library:
	$(CC) -c $(SOURCES) $(OBGECTS) -lm
	ar rc s21_matrix_oop.a $(OBJECTS)
	ranlib s21_matrix_oop.a

clean:
	rm -f *.out *.a *.o asd.c s21_test *.html *.gcno *.gcda coverage_report.css *.info *.gch
	rm -rf report cov-report
test: library
	$(CC) -c unit_test.cc -o test.o
	$(CC) test.o s21_matrix_oop.a $(TESTSFLAGS) -o s21_test
	./s21_test

gcov_report: test
	$(CC) $(FLAGS) $(COVERAGE_FLAGS) -c $(SOURCES) $(OBGECTS)
	ar rc s21_matrix_oop.a $(OBJECTS)
	ranlib s21_matrix_oop.a
	$(CC) test.o s21_matrix_oop.a $(TESTSFLAGS) $(LDFLAGS) -o s21_test
	./s21_test
	lcov -t "gcov_report" -o s21_matrix_oop.info -c -d .
	genhtml -o report s21_matrix_oop.info
	open report/index.html
