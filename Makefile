
CFLAGS=-Wall -Werror -Wextra
CPPFLAGS=-lstdc++ -std=c++17
LIBS=-lgtest -lgcov

# -- Main targets ---
TEST=test
CLEAN=clean

$(TEST): ${CLEAN}
	@gcc $(CFLAGS) $(LIBS) $(CPPFLAGS) tests.cpp Controller/controller.cc Model/model.cc -o test
	@./test


tests:
	mkdir -p Tester/build && \
	cd Tester/build && \
	cmake .. && \
	cmake --build . && \
	./bin/Tester
