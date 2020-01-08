CC := g++
LD := g++

CC_FLAGS := -std=c++2a -Wall -Wextra -fno-rtti -MMD -MP -g
CC_INCLUDES := -I./include -I../../include
CC_DEFINES :=

LD_FLAGS :=
LD_LIBS := -lGLEW -lOpenGL -lSOIL -lassimp -lEGL

SRC_DIR := src
OBJ_DIR := obj

SRC := $(wildcard $(addsuffix /*.cpp, $(SRC_DIR)))
OBJ := $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC)))

OUT_NAME := gl.so
OUT_DIR := ../../bin/plugins/
OUT := $(addprefix $(OUT_DIR), $(OUT_NAME))

all:
	@$(MAKE) --no-print-directory --jobs 8 $(OUT)

$(OUT): $(OBJ)
	@mkdir --parent $(@D)
	$(LD) $(LD_FLAGS) $^ $(LD_LIBS) -shared -o $(OUT)

$(OBJ_DIR)/%.o: %
	@mkdir --parent $(@D)
	$(CC) $(CC_FLAGS) $(CC_INCLUDES) $(CC_DEFINES) -fpic -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OUT_DIR)

-include $(OBJ:.o=.d)
