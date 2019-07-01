#$(dir pwd)  is equal to "./"
#$(CURDIR) is equal to "/home/armen/Documents/CONTAINER_CLASSES"

SOURCES = $(wildcard Sources/*.cpp)
OBJECTS = $(patsubst Sources/%.cpp,Objects/%.o, $(SOURCES))
HEADERS = $(patsubst Sources/%.cpp,Headers/%.hpp, $(SOURCES))
DEPS = $(patsubst Sources/%.cpp,Deps/%.dep, $(SOURCES))

TARGET = Bin/sle_solution.exe

.PHONY : clean

$(TARGET) : $(OBJECTS)
	@mkdir -pv Bin
	@echo "Linking.."
	gcc $^ -lstdc++ -ldinsle -ldinsle_gsj -L./Libs -o $@

Objects/%.o : Sources/%.cpp
	@mkdir -pv Objects
	@echo "Building object files: $@"
	gcc -c $< -I Headers -o $@
       	
Deps/%.dep : Sources/%.cpp
	@mkdir -pv Deps
	@echo "building $@ file.."
	gcc -MM $< -MT "$@ $(addprefix Objects,$(basename $(notdir $@)).o)" -I Headers -o $@

clean : 
	@echo "Cleaning: All generated objects are deleted.."
	rm -rf Bin Objects Deps

ifneq ($(MAKECMDGOALS), clean)
-include $(DEPS)
endif




