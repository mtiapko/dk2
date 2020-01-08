CC := g++
LD := g++

CC_FLAGS := -std=c++2a -Wall -Wextra -fno-rtti -MMD -MP -g
CC_INCLUDES := -I./include
CC_DEFINES :=

LD_FLAGS := -Wl,--export-dynamic
LD_LIBS := -ldl -lpthread -lX11 -lOpenGL -lGLEW

SRC_DIR := \
	src \
	src/sys \
	src/util \
	src/math \
	src/graph \
	src/ImGui \
	src/ImGui/NodeEditor \
	src/resource \
	src/allocator \
	src/os/GNU_Linux \
	src/ide/ShaderLink \
	src/ide/ShaderLink/nodes

OBJ_DIR := bin/obj

SRC := $(wildcard $(addsuffix /*.cpp, $(SRC_DIR)))
OBJ := $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC)))

OUT_NAME := dk
OUT_DIR := ./bin/
OUT := $(addprefix $(OUT_DIR), $(OUT_NAME))

all:
	@$(MAKE) --no-print-directory --jobs 8 $(OUT)
	@$(MAKE) --no-print-directory -C plugins/gl

$(OUT): $(OBJ)
	@mkdir --parent $(@D)
	$(LD) $(LD_FLAGS) $^ $(LD_LIBS) -o $(OUT)

$(OBJ_DIR)/%.o: %
	@mkdir --parent $(@D)
	$(CC) $(CC_FLAGS) $(CC_INCLUDES) $(CC_DEFINES) -c $< -o $@

run: all
	@$(OUT)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OUT_DIR)
	@$(MAKE) --no-print-directory -C plugins/gl clean

memcheck: all
	@valgrind --leak-check=full --show-leak-kinds=all $(OUT)

debug: all
	@gdb -ex run $(OUT)

-include $(OBJ:.o=.d)
