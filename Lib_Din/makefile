SOURCES = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp,%.o, $(SOURCES))

.PHONY : clean

TARGET = ../Libs/libdinsle.so

$(TARGET) : $(OBJECTS)
	@echo "building dinamic library: $(TARGET)"
	mkdir -pv ../Libs
	gcc -shared -o $@ $^

%.o : %.cpp
	@echo "buiding PIC object files"
	gcc -c -fPIC $< -o $@ -I../Headers

clean : 
	@echo "Cleaning: All generated objects for din-lib are deleted!"
	rm -f ../Libs/libdinsle.so
	rm -f *.o
