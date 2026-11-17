D3M0N_BIN_DIR	= ../bin/
SRC_DIR			= src
BUILD_DIR		= build
C_FILES			= $(shell find "$(SRC_DIR)" -type f -name "*.c")
BIN_FILES		= $(C_FILES:src/%.c=$(BUILD_DIR)/%)
CC				= d3c
C_FLAGS			= -Wall -Wextra -Werror -Iinclude


all: $(BIN_FILES)

$(BUILD_DIR)/%: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(C_FLAGS) $^ -o $@

clean:
	rm -rf $(BUILD_DIR)

fclean: clean

re: fclean all

export: all
	find "$(BUILD_DIR)" -type f -exec cp {} "$(D3M0N_BIN_DIR)"

re_export: fclean export

.PHONY: all clean fclean re export re_export