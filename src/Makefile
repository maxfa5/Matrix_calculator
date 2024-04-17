CC = gcc
CFLAGS =-std=c11 -Wall -Wextra  -lm  
SRC = determinant/*.c mul/*.c *.c
TEST_SRC = tests/test.c
LIBSFLAGS = -lcheck -lsubunit -lrt -lpthread -lm -lgcov
GCOV_FLAGS = -fprofile-arcs -ftest-coverage  --coverage
LIB = s21_matrix.a
GCOVR_PATH = gcovr
REPORT = report/index.html

all : $(LIB)

$(LIB):
	rm -rf $(LIB)
	$(CC) $(CFLAGS) -c $(SRC)
	ar rc $(LIB) *.o
	ranlib $(LIB)
	rm -rf *.o

test: clean $(LIB)
	$(CC) $(CFLAGS) -L. -l:$(LIB) $(GCOV_FLAGS) $(SRC) ${TEST_SRC} -o test_result $(LIBSFLAGS) -g
	./test_result
	
val: 
	valgrind --tool=memcheck --leak-check=yes -s  --leak-check=full --show-leak-kinds=all  ./test_result

gcov_report: test
	mkdir report
	${GCOVR_PATH} -r . --html  --html-details  -o $(REPORT)  -e ${TEST_SRC}
	xdg-open $(REPORT)

clean:
	rm -rf test_result
	rm -rf report
	rm -rf *.gcno
	rm -rf *.gcda
	rm -rf *.a

rebuild: clean s21_decimal.a


check:
	clang-format -n $(SRC) tests/*.c tests/*.h *.h
	
fix:
	clang-format -i $(SRC) tests/*.c tests/*.h *.h

manual_test:
	$(CC) $(SRC) manual_test.c $(CFLAGS) -o result
