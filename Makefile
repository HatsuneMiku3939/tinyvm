TARGET_EXEC ?= tinyvm

BUILD_DIR ?= build
SRC_DIRS ?= src

SRCS = $(shell find $(SRC_DIRS) -name *.cpp)
OBJS = $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -Wall -std=c++0x -Og -g

# indicator
SRCS_MAX = $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s | wc -l)
SRC_CURR = 0

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	@mkdir -p $(dir $@)
	@$(eval SRC_CURR=$(shell echo $$(($(SRC_CURR)+1))))
	@echo "[${SRC_CURR}/${SRCS_MAX}] compile $<"
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# build target
$(BUILD_DIR)/$(TARGET_EXEC): $(BUILD_DIR)/$(TARGET_EXEC)-debug
	@echo "$(BUILD_DIR)/$(TARGET_EXEC)"
	@cp $(BUILD_DIR)/$(TARGET_EXEC)-debug $(BUILD_DIR)/$(TARGET_EXEC)
	@strip --strip-debug $(BUILD_DIR)/$(TARGET_EXEC)

$(BUILD_DIR)/$(TARGET_EXEC)-debug: $(OBJS)
	@echo "$(BUILD_DIR)/$(TARGET_EXEC)-debug"
	@$(CXX) $(OBJS) -o $@ $(LDFLAGS)

.PHONY: clean

clean:
	@$(RM) -r $(BUILD_DIR)

-include $(DEPS)
