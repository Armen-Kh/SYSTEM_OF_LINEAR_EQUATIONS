
SOURCES = $(wildcard *.cpp)
TARGETS = $(patsubst %.cpp,../Bin/%.exe, $(SOURCES))
#TARGET = ../Bin/test_gauss_comparator.exe

.PHONY : START

START : $(TARGETS)

../Bin/%.exe : %.cpp
	gcc $< -lstdc++ -ldinsle -ldinsle_gsj -L../Libs -I../Headers -o $@
