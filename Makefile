GCC = gcc -Wall -Werror -Wextra -std=c11
LC=-lcheck
OS=$(shell uname -s)
ifeq ($(OS),Darwin)
  	OPEN = open
	LC = -lcheck
endif
ifeq ($(OS),Linux)
	OPEN = xdg-open
	LC = -lcheck -lsubunit -lrt -lpthread -lm -D_GNU_SOURCE
endif


all: s21_smart_calc.a

s21_smart_calc.a:
	$(GCC) -c SmartCalc/back/*.c
	ar rc s21_smart_calc.a *.o
	ranlib s21_smart_calc.a
	rm -rf *.o

install:
	mkdir build
	cd build && qmake ../SmartCalc && make
	cd ..
	make clean_garbage

uninstall:
	rm -rf build

open: 
	open build/SmartCalc.app

dvi:
	open SmartCalcDoc.html

dist: clean_garbage
	tar cvzf SmartCalc_v1.0.tgz build/

test: clean s21_smart_calc.a
	$(GCC) tests/*.c s21_smart_calc.a $(LC) -o test
	./test	

clean:
	rm -rf build
	rm -rf *.o *.a *.gcda *.gcno
	rm -rf *.info *.gcov
	rm -rf *.dSYM *.info *.log *.check test report

clean_garbage:
	rm -rf build/*.o build/Makefile build/qmake_qmake_qm_files.qrc build/qrc_qmake_qmake_qm_files.cpp build/moc_* build/Makefile build/ui*

gcov_report: clean
	$(GCC) -fprofile-arcs -ftest-coverage SmartCalc/back/*.c tests/*.c -o test $(LC)
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	$(OPEN) ./report/index.html

clang:
	cp ../materials/linters/.clang-format .
	clang-format -style=Google -n SmartCalc/*.c SmartCalc/*.h SmartCalc/back/*.c SmartCalc/back/*.h;
	rm .clang-format
