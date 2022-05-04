COMPILER   := /usr/bin/c++
PREFLAGS   := -std=c++11 -Wall -Wextra -pedantic -O2 -g $(shell pkg-config --cflags glfw3 gl)
POSTFLAGS  := $(shell pkg-config --static --libs glfw3 gl)

SRCFILES   := ./src/*.cpp
TARGDIR    := ./build
TARGET     := lveq-cpp

all:
	@mkdir -p $(TARGDIR)
	@echo "[*] $(COMPILER): Compiling sources..."
	@$(COMPILER) $(PREFLAGS) $(SRCFILES) -o $(TARGDIR)/$(TARGET) $(POSTFLAGS)
	@echo "[*] $(COMPILER): Done."

clean:
	@echo "[*] Cleaning executables folder $(TARGDIR)..."
	@rm -rf $(TARGDIR)
	@echo "[*] Done."
