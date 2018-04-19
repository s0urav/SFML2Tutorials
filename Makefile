
# SFML_DIR is read from the environment and should refer to the
# directory where SFML headers and libraries are available.

INCLUDE_PATH=${SFML_DIR}/include
LIBRARY_PATH=${SFML_DIR}/lib
LIBRARIES=-lsfml-system -lsfml-window -lsfml-graphics
IMAGE_tank=Tutorial\ 2/build-untitled1-Desktop_Qt_5_7_0_GCC_64bit-Debug/tank.png

all: out/t1.out t2

out/t1.out: Tutorial\ 1/Tutorial1/main.cpp
	g++ -std=c++17 -o out/t1.out "Tutorial 1/Tutorial1/main.cpp" \
	-I$(INCLUDE_PATH) \
	-L$(LIBRARY_PATH) $(LIBRARIES)

# For running "Tutorial 2", out/t2.out and out/tank.png are needed.
t2: out/t2.out out/tank.png

out/t2.out: Tutorial\ 2/Tutorial2/main.cpp
	g++ -std=c++17 -o out/t2.out "Tutorial 2/Tutorial2/main.cpp" \
	-I$(INCLUDE_PATH) \
	-L$(LIBRARY_PATH) $(LIBRARIES)

out/tank.png: $(IMAGE_tank)
	cp $(IMAGE_tank) out/  
