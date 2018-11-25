CC := g++
LD := g++

CC_FLAGS := -std=c++2a -MMD -MP -g
CC_INCLUDES := -I./include
CC_DEFINES :=

LD_FLAGS :=
LD_LIBS := -lEGL -lX11 -lGLEW -lGL

SRC_DIR := src src/graphic
OBJ_DIR := obj

SRC := $(wildcard $(addsuffix /*.cpp, $(SRC_DIR)))
OBJ := $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC)))

OUT_NAME := dk
OUT := $(addprefix ./, $(OUT_NAME))

all:
	@$(MAKE) --no-print-directory --jobs 8 $(OUT)

$(OUT): $(OBJ)
	$(LD) $(LD_FLAGS) $^ $(LD_LIBS) -o $(OUT)

$(OBJ_DIR)/%.o: %
	@mkdir --parent $(@D)
	$(CC) $(CC_FLAGS) $(CC_INCLUDES) $(CC_DEFINES) -c $< -o $@

run: all
	@$(OUT)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(OUT)

-include $(OBJ:.o=.d)
