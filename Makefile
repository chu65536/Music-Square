CXX=g++
CPP_FLAGS=-g -MMD -MP

SRC_PREF=./code/
OBJ_PREF=./obj/
SRC=$(wildcard $(SRC_PREF)*.cpp)
OBJ=$(patsubst $(SRC_PREF)%.cpp, $(OBJ_PREF)%.o, $(SRC))

LIBS=-lmingw32 -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lsfml-main
INCLUDE_PATH=D:\libs\c++\SFML-2.6.0\include
LIB_PATH=D:\libs\c++\SFML-2.6.0\lib

TARGET=app.exe

all: $(TARGET) run

$(OBJ_PREF)%.o : $(SRC_PREF)%.cpp
	$(CXX) -c $(CPP_FLAGS) $< -o $@ -I$(INCLUDE_PATH)

-include $(OBJ:%.o=%.d)

$(TARGET) : $(OBJ)
	$(CXX) -L$(LIB_PATH) $^ -o $@ $(LIBS)

run:
	$(TARGET)