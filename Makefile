CC = gcc
CFLAGS = -Wall -Werror -g -O0 -std=c11
LDFLAGS = -lmpdclient -lncurses -lpanel

TARGET_EXEC := pantomime

BUILD_DIR := ./build
SRC_DIR := ./src
INC_DIR := ./include

DOC_CONFIG := Doxyfile.in
DOC_DIR :=./doc
DOC_BUILD_DIR := $(BUILD_DIR)/$(DOC_DIR)

# Find all C files we want to compile.
SRCS := $(shell find $(SRC_DIR) -name '*.c')

# Prepend BUILD_DIR and append .o to every src file.
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# String substitution.
DEPS := $(OBJS:.o=.d)

# Every folder in SRC_DIR will need to be passed to gcc so it can find header files.
INC_DIRS := $(shell find $(SRC_DIR) -type d) $(INC_DIR)
# Add a prefix to INC_DIRS. So moduleA becomes -ImoduleA.
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# -MMD and -MP together generates Makefiles with a .d extension.
CPPFLAGS := $(INC_FLAGS) -MMD -MP

# Final build step.
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Run clang-format and clang-tidy on everything.
.PHONY: style
style:
	@for src in $(SRCS) ; do \
		echo "Formatting $$src..." ; \
		clang-format -i -style=file "$$src" ; \
		echo "Running tidy on $$src..." ; \
		clang-tidy --config-file="./.clang-tidy" "$$src" -- -Iinclude/ ; \
	done
	@echo "Done."

# Run clang-format to check style but without editing the files.
.PHONY: check-style
check-style:
	@for src in $(SRCS) ; do \
		var=`clang-format "$$src" | diff "$$src" - | wc -l` ; \
		if [ $$var -ne 0 ] ; then \
			echo "$$src does not respect the coding style (diff: $$var line)." ; \
			exit 1 ; \
		fi ; \
	done
	@echo "Style check passed."

.PHONY: doc
doc: $(DOC_DIR)/$(DOC_CONFIG)
	mkdir -p $(DOC_BUILD_DIR)
	doxygen $(DOC_DIR)/$(DOC_CONFIG)

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

# Include the .d makefiles.
-include $(DEPS)
