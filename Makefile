# Toolchain/Environment
export SHELL := /bin/bash
export CC    := g++

# Dependency: MetroUtil
METROUTIL     := MetroUtil/lib/libMetrobotics.a
METROUTIL_LIB := MetroUtil/lib
METROUTIL_INC := MetroUtil/include

# Options
CFLAGS := -Wall -c -I$(METROUTIL_INC) `pkg-config --cflags playerc++`
LIBS   := -L$(METROUTIL_LIB) -lMetrobotics -lboost_system-mt `pkg-config --libs playerc++`

# Files
OUTPUT    := controller
SOURCES   := $(wildcard *.cpp)
OBJECTS   := $(patsubst %.cpp, %.o, $(SOURCES))
HEADERS   := $(wildcard *.h)

# Debugging support
export DEBUG ?= 1
ifeq ($(DEBUG), 0)
	CFLAGS := $(CFLAGS) -g0
else
	CFLAGS := $(CFLAGS) -g3
endif

# General targets
.PHONY: default clean purge

# Default target: build the controller
default: $(METROUTIL) $(OBJECTS)
	$(CC) -o $(OUTPUT) $(OBJECTS) $(LIBS)

# Dependency: MetroUtil
$(METROUTIL):
	@echo Building MetroUtil
	@$(MAKE) -e --directory="./MetroUtil" install
	@if [ "$$?" != 0 ]; then \
		echo "MetroUtil failed to build"; \
		exit 1; \
	fi

# Remove unnecessary output files
clean:
	@$(MAKE) -e --directory="./MetroUtil" clean
	rm -rf $(OBJECTS)

# Remove all output files
purge:
	@$(MAKE) -e --directory="./MetroUtil" purge
	@$(MAKE) -e clean
	rm -rf $(OUTPUT)

# Individual source targets
controller.o: controller.cpp $(HEADERS)
	$(CC) -c $(CFLAGS) controller.cpp

robot.o: robot.cpp $(HEADERS)
	$(CC) -c $(CFLAGS) robot.cpp

loiter.o: loiter.cpp loiter.h behavior.h
	$(CC) -c $(CFLAGS) loiter.cpp
