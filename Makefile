# 01:
# 	g++ -I/usr/local/ -I./includes/ -L/usr/local -lglfw -framework OpenGL glad.c 01.cpp

# 02:
# 	g++ -std=c++17 -I/usr/local/ -I./includes/ -L/usr/local -lglfw -framework OpenGL glad.c 02.cpp

# # Linear motion
# 03:
# 	g++ -std=c++17 -I/usr/local/ -I./includes/ -L/usr/local -lglfw -framework OpenGL glad.c 03.cpp

# # Draw a line
# 04:
# 	g++ -std=c++17 -I/usr/local/ -I./includes/ -L/usr/local -lglfw -framework OpenGL glad.c 04.cpp

all:
	g++ -std=c++17 -I/usr/local/ -I./include/ -L/usr/local -lglfw -framework OpenGL \
	glad.c ./include/stb/stb_image.cpp ./include/stb/stb_image_write.cpp ./exp/$(n)$(wildcard _*).cpp
