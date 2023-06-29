CC=gcc
CCFLAGS=
LINKER_OBJ=$(CC) -c -o
LINKER_DEBUG=$(CC) -g -o
LINKER_RELEASE=$(CC) -O3 -o
TARGET=hashmap
TARGET_DIR=target
DEBUG_DIR=$(TARGET_DIR)/debug
RELEASE_DIR=$(TARGET_DIR)/release
TARGET_DEBUG=$(DEBUG_DIR)/$(TARGET)
TARGET_RELEASE=$(RELEASE_DIR)/$(TARGET)
OBJ_DIR=$(TARGET_DIR)/obj
OBJ_FILES=$(patsubst $(LIB_DIR)/%.c, $(OBJ_DIR)/%.o, $(wildcard $(LIB_DIR)/*.c))
SRC_DIR=src
MAIN_FILE=$(SRC_DIR)/main.c
LIB_DIR=$(SRC_DIR)/lib
SRC_FILES=$(MAIN_FILE) $(OBJ_FILES)
.DEFAULT_GOAL:=debug
.PHONY: clean remake remake_release
debug: $(TARGET_DEBUG)
$(DEBUG_DIR):
	@mkdir -p $@
$(RELEASE_DIR):
	@mkdir -p $@
$(OBJ_DIR):
	@mkdir -p $@
$(OBJ_DIR)/%.o:$(LIB_DIR)/%.c $(OBJ_DIR)
	$(LINKER_OBJ) $@ $<
$(TARGET_DEBUG): $(SRC_FILES) $(DEBUG_DIR)
	$(LINKER_DEBUG) $@ $(SRC_FILES)
release: $(TARGET_RELEASE)
$(TARGET_RELEASE): $(SRC_FILES) $(RELEASE_DIR)
	$(LINKER_RELEASE) $@ $(SRC_FILES)
clean:
	@{\
		if [ -d $(TARGET_DIR) ]; then\
		rm -r $(TARGET_DIR);\
		fi;\
	}
run: $(TARGET_DEBUG)
	./$<
r_run: $(TARGET_RELEASE)
	./$<
remake: clean run
remake_release: clean r_run
