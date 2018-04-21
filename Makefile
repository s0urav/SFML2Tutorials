
# SFML_DIR is read from the environment and should refer to the
# directory where SFML headers and libraries are available.

INCLUDE_PATH=${SFML_DIR}/include
LIBRARY_PATH=${SFML_DIR}/lib
LIBRARIES=-lsfml-system -lsfml-window -lsfml-graphics

IMAGE_tank=Tutorial\ 2/build-untitled1-Desktop_Qt_5_7_0_GCC_64bit-Debug/tank.png
IMAGE_SpriteSheet=Tutorial\ 3/build-Tutorial3-Desktop_Qt_5_7_0_GCC_64bit-Debug/SpriteSheet.png

all: out/t1.out t2 t3

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

# For running "Tutorial 3", out/t3.out and out/SpriteSheet.png are needed.
t3: out/t3.out out/SpriteSheet.png

out/t3.out: Tutorial\ 3/Tutorial3/main.cpp
	g++ -std=c++17 -o out/t3.out "Tutorial 3/Tutorial3/main.cpp" \
	-I$(INCLUDE_PATH) \
	-L$(LIBRARY_PATH) $(LIBRARIES)

out/SpriteSheet.png: $(IMAGE_SpriteSheet)
	cp $(IMAGE_SpriteSheet) out/

