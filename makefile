CC = g++
CXXFLAGS = -std=c++11  -Wall
CODE_DIR = ./code
OBJECT_DIR = ./object
UTILS_DIR = ./utils
CPPS = $(wildcard \
				$(CODE_DIR)/*.cpp\
				$(OBJECT_DIR)/*.cpp\
				$(UTILS_DIR)/*.cpp\
				*.cpp)
OBJECTS = $(patsubst %.cpp, %.o, $(CPPS))

main.out: $(OBJECTS)
	$(CC) -o main.out $(OBJECTS)

%.o: %.hpp

clean:
	rm main.out $(OBJECTS)
