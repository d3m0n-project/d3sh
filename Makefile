
D3M0N_BIN_DIR	= ../bin/
SRC_DIR			= src
BUILD_DIR		= build
C_FILES			= $(shell find "$(SRC_DIR)" -type f -name "*.c")
BIN_FILES		= $(C_FILES:src/%.c=$(BUILD_DIR)/%)

CC				= d3c
C_FLAGS			= -Wall -Wextra -Werror -Iinclude -I$(BUILD_DIR)

MAJOR_VERSION	= 1.0
VERSION_FILE	= VERSION
VERSION_HEADER	= $(BUILD_DIR)/version.h

BUILD_DATE		= $(shell date -u +"%d/%m/%Y %H:%M GMT")

VERSION			= $(shell cat $(VERSION_FILE) 2>/dev/null || echo 0)


all: $(BIN_FILES)

$(VERSION_FILE):
	@echo 0 > $@

version-update: $(VERSION_FILE)
	@needs_build=0; \
	for file in $(C_FILES); do \
		target="$(BUILD_DIR)/$${file#$(SRC_DIR)/}"; \
		if [ ! -f "$$target" ] || [ "$$file" -nt "$$target" ]; then \
			needs_build=1; \
			break; \
		fi; \
	done; \
	if [ $$needs_build -eq 1 ]; then \
		echo $$(( $$(cat $(VERSION_FILE)) + 1 )) > $(VERSION_FILE); \
	fi

$(VERSION_HEADER): version-update
	@mkdir -p $(BUILD_DIR)
	@version=$$(cat $(VERSION_FILE)); \
	printf '#pragma once\n#define D3SH_BUILD_VERSION "%s.%s"\n#define D3SH_BUILD_DATE "%s"\n' \
		"$(MAJOR_VERSION)" "$$version" "$(BUILD_DATE)" > $@.tmp; \
	if ! cmp -s $@.tmp $@; then \
		mv $@.tmp $@; \
	else \
		rm $@.tmp; \
	fi

$(BUILD_DIR)/%: $(SRC_DIR)/%.c $(VERSION_HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(VERSION_FILE)

re:
	@rm -rf $(BUILD_DIR)
	@$(MAKE) all

export: all
	@mkdir -p $(D3M0N_BIN_DIR)
	@find "$(BUILD_DIR)" -type f ! -name "*.h" -exec cp {} "$(D3M0N_BIN_DIR)" ';'
	@printf "\033[32mExported successfully!\033[0m\n"

re_export: re export

.PHONY: all clean fclean re export re_export FORCE