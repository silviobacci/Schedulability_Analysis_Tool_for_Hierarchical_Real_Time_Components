CFLAGS = 				-Wall -Wextra -pedantic -std=c11
INCLUDEFLAGS = 			-I$(CURDIR)/lib

ifdef DEBUG
	CFLAGS += 			-g -O0
else
	CFLAGS += 			-O3
endif

SRC_PATH = 				$(CURDIR)/src
LIB_PATH = 				$(CURDIR)/lib
BIN_PATH = 				$(CURDIR)/bin

SBF = 					sbf
S_ANALYSIS = 			s_analysis
H_ANALYSIS = 			h_analysis
MCPU_ANALYSIS = 		mcpu_analysis

LIB_VIO = 				$(LIB_PATH)/vm/vm_io.o
LIB_TIO = 				$(LIB_PATH)/task/task_io.o
LIB_TS = 				$(LIB_PATH)/task/testing_set.o
LIB_UTILITIES =			$(LIB_PATH)/utilities/utilities.o
LIB_PRINTS = 			$(LIB_PATH)/utilities/prints.o
LIB_BP =				$(LIB_PATH)/schedulability/bin_packing.o
LIB_SBF = 				$(LIB_PATH)/schedulability/sbf.o
LIB_DBF = 				$(LIB_PATH)/schedulability/dbf.o
LIB_S_ANALYSIS = 		$(LIB_PATH)/schedulability/$(S_ANALYSIS).o
LIB_H_ANALYSIS = 		$(LIB_PATH)/schedulability/$(H_ANALYSIS).o
LIB_MCPU_ANALYSIS = 	$(LIB_PATH)/schedulability/$(MCPU_ANALYSIS).o
COMMON_LIBS = 			$(LIB_TIO) $(LIB_TS) $(LIB_UTILITIES) $(LIB_SBF) $(LIB_DBF) $(LIB_PRINTS)
LIBS = 					$(COMMON_LIBS) $(LIB_VIO) $(LIB_BP) $(LIB_S_ANALYSIS) $(LIB_H_ANALYSIS) $(LIB_MCPU_ANALYSIS)

OBJ_SBF = 				$(SRC_PATH)/$(SBF).o
OBJ_S_ANALYSIS = 		$(SRC_PATH)/$(S_ANALYSIS).o
OBJ_H_ANALYSIS = 		$(SRC_PATH)/$(H_ANALYSIS).o
OBJ_MCPU_ANALYSIS = 	$(SRC_PATH)/$(MCPU_ANALYSIS).o
OBJS = 					$(OBJ_SBF) $(OBJ_S_ANALYSIS) $(OBJ_H_ANALYSIS) $(OBJ_MCPU_ANALYSIS)

BINS = 					$(BIN_PATH)/$(SBF) $(BIN_PATH)/$(S_ANALYSIS) $(BIN_PATH)/$(H_ANALYSIS) $(BIN_PATH)/$(MCPU_ANALYSIS)

.PHONY:
all : $(SBF) $(S_ANALYSIS) $(H_ANALYSIS) $(MCPU_ANALYSIS)

$(SBF) : $(OBJ_SBF) $(COMMON_LIBS)
	gcc -o $(BIN_PATH)/$@ $^
	
$(S_ANALYSIS) : $(OBJ_S_ANALYSIS) $(COMMON_LIBS) $(LIB_S_ANALYSIS)
	gcc -o $(BIN_PATH)/$@ $^
	
$(H_ANALYSIS) : $(OBJ_H_ANALYSIS) $(COMMON_LIBS) $(LIB_H_ANALYSIS)
	gcc -o $(BIN_PATH)/$@ $^

$(MCPU_ANALYSIS) : $(OBJ_MCPU_ANALYSIS) $(COMMON_LIBS) $(LIB_VIO) $(LIB_BP) $(LIB_H_ANALYSIS) $(LIB_MCPU_ANALYSIS)
	gcc -o $(BIN_PATH)/$@ $^

%.o : %.c
	gcc $(CFLAGS) $(INCLUDEFLAGS) -c -o $@ $<

.PHONY:
soft_clean :
	rm -f $(OBJS) $(LIBS)

.PHONY:
clean :
	rm -f $(OBJS) $(LIBS) $(BINS)

