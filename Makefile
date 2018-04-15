
# SFML_DIR is read from the environment and should refer to the
# directory where SFML headers and libraries are available.

INCLUDE_PATH=${SFML_DIR}/include
LIBRARY_PATH=${SFML_DIR}/lib
LIBRARIES=-lsfml-system -lsfml-window -lsfml-graphics

all: out/t1.out

out/t1.out: Tutorial\ 1/Tutorial1/main.cpp
	g++ -std=c++17 -o out/t1.out "Tutorial 1/Tutorial1/main.cpp" \
	-I$(INCLUDE_PATH) \
	-L$(LIBRARY_PATH) $(LIBRARIES)
