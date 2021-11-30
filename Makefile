RELEASE=duphoto

OBJ_DIR=./obj/

COMPILER=g++
OPTS=-Ofast
LDFLAGS= -lm
CFLAGS=-Wall -Wfatal-errors -Wno-unused-result -Wno-unknown-pragmas -Wunused -Wunreachable-code -Wno-deprecated-declarations
CFLAGS+=$(OPTS)

CFLAGS+= -std=c++17

COMMON+= -I/usr/local/Cellar/opencv/4.4.0/include/opencv4/
LDFLAGS+= -L/usr/local/Cellar/gcc/10.1.0/lib/gcc/10/ -lboost_filesystem -L/usr/local/Cellar/opencv/4.4.0/lib/ -lopencv_core -lopencv_imgcodecs -lopencv_imgproc

OBJ_CPU1=$(patsubst %.cpp,%.o,$(wildcard src/*.cpp))

OBJ_TOT= $(OBJ_CPU1)

OBJS=$(addprefix $(OBJ_DIR), $(OBJ_TOT))

DEPS_CPU1=$(wildcard src/*.h)

all: release

.PHONY: release

release: obj $(RELEASE)

obj:
	mkdir -p ./obj/src

$(RELEASE): $(OBJS)
	$(COMPILER) $(COMMON) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	
$(OBJ_DIR)%.o: %.cpp $(DEPS_CPU1)
	$(COMPILER) $(COMMON) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf ./obj/
	rm -f $(RELEASE)

