#include the make.h
include ./make.h

MODULE_OBJECT_LIST =	$(MODULE_OBJ_DIR)/partitionutils.o \
						$(MODULE_OBJ_DIR)/partitionmain.o

MODULE_FINAL_EXE = $(MODULE_EXE_DIR)/partition
#MODULE_STATIC_LIBS_DIR = -L$(BASE_DIR)/common/lib/

MODULE_LIBS_LIST = -lm
#MODULE_LIBS_LIST = -lcmn \
					-lm \
					-lrt \
					-lpthread

$(MODULE_FINAL_EXE): $(MODULE_OBJECT_LIST)
	$(CC) -g -O0 $(MODULE_OBJECT_LIST) $(MODULE_STATIC_LIBS_DIR) $(MODULE_LIBS_LIST) -o $(MODULE_FINAL_EXE)

$(MODULE_OBJ_DIR)/partitionutils.o: $(MODULE_SRC_DIR)/partitionutils.c
	$(CC) $(CC_FLAGS) $(MODULE_FINAL_INC_DIRS) $(MODULE_SRC_DIR)/partitionutils.c -o $(MODULE_OBJ_DIR)/partitionutils.o

$(MODULE_OBJ_DIR)/partitionmain.o: $(MODULE_SRC_DIR)/partitionmain.c
	$(CC) $(CC_FLAGS) $(MODULE_FINAL_INC_DIRS) $(MODULE_SRC_DIR)/partitionmain.c -o $(MODULE_OBJ_DIR)/partitionmain.o

clean:
	rm -f $(MODULE_OBJ_DIR)/*
	rm -f $(MODULE_EXE_DIR)/*						   
