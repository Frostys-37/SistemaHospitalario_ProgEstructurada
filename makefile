# =================================================
# MakeFile - GESTION HOSPITALARIA
# make -> Compila el proyecto
# make run -> Compila y Ejecuta el proyecto
# make clean -> Borra binarios generados
# =================================================

CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Iinclude
SRC      := $(wildcard src/*.cpp)
TARGET   := build/sistema
 
# Deteccion de so para el cmd de "clean" y el .exe
ifeq ($(OS),Windows_NT)
    TARGET := build/sistema.exe
    RM     := del /Q /F
    FIXPATH = $(subst /,\,$1)
else
    RM     := rm -f
    FIXPATH = $1
endif
 
.PHONY: all run clean
 
all: $(TARGET)
 
$(TARGET): $(SRC)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)
 
run: all
	./$(TARGET)
 
clean:
	$(RM) $(call FIXPATH,$(TARGET))