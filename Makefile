CFLAGS = -Wall -Wextra -pedantic -std=c11
INCLUDEFLAGS = -I$(CURDIR)/lib

ifdef DEBUG
	CFLAGS += -g -O0
else
	CFLAGS += -O3
endif

SRC_PATH = $(CURDIR)/src
LIB_PATH = $(CURDIR)/lib
BIN_PATH = $(CURDIR)/bin

SBF = sbf
S_ANALYSIS_EDF = s_analysis_edf
S_ANALYSIS_FP = s_analysis_fp
H_ANALYSIS_EDF = h_analysis_edf
H_ANALYSIS_FP = h_analysis_fp

LIB_TIO = $(LIB_PATH)/task/task_io.o
LIB_SP = $(LIB_PATH)/task/testing_set.o
LIB_UF = $(LIB_PATH)/task/utilization_factor.o
LIB_UTILITIES = $(LIB_PATH)/utilities/utilities.o
LIB_PRINTS = $(LIB_PATH)/utilities/prints.o
LIB_SBF = $(LIB_PATH)/sbf/sbf.o
LIB_DBF_EDF = $(LIB_PATH)/dbf/edf.o
LIB_DBF_FP = $(LIB_PATH)/dbf/fp.o
LIB_S_ANALYSIS_EDF = $(LIB_PATH)/s_analysis/edf.o
LIB_S_ANALYSIS_FP = $(LIB_PATH)/s_analysis/fp.o
LIB_H_ANALYSIS_EDF = $(LIB_PATH)/h_analysis/edf.o
LIB_H_ANALYSIS_FP = $(LIB_PATH)/h_analysis/fp.o
LIBS = $(LIB_TIO) $(LIB_SP) $(LIB_UF) $(LIB_UTILITIES) $(LIB_PRINTS) $(LIB_SBF) $(LIB_DBF_EDF) $(LIB_DBF_FP) $(LIB_S_ANALYSIS_EDF) $(LIB_S_ANALYSIS_FP) $(LIB_H_ANALYSIS_EDF) $(LIB_H_ANALYSIS_FP)

OBJ_SBF = $(SRC_PATH)/sbf/$(SBF).o
OBJ_S_ANALYSIS_EDF = $(SRC_PATH)/s_analysis/$(S_ANALYSIS_EDF).o
OBJ_S_ANALYSIS_FP = $(SRC_PATH)/s_analysis/$(S_ANALYSIS_FP).o
OBJ_H_ANALYSIS_EDF = $(SRC_PATH)/h_analysis/$(H_ANALYSIS_EDF).o
OBJ_H_ANALYSIS_FP = $(SRC_PATH)/h_analysis/$(H_ANALYSIS_FP).o
OBJS = $(OBJ_SBF) $(OBJ_S_ANALYSIS_EDF) $(OBJ_S_ANALYSIS_FP) $(OBJ_H_ANALYSIS_EDF) $(OBJ_H_ANALYSIS_FP)

BINS = $(BIN_PATH)/$(SBF) $(BIN_PATH)/$(S_ANALYSIS_EDF) $(BIN_PATH)/$(S_ANALYSIS_FP) $(BIN_PATH)/$(H_ANALYSIS_EDF) $(BIN_PATH)/$(H_ANALYSIS_FP) 

.PHONY:
all : $(SBF) $(S_ANALYSIS_FP) $(H_ANALYSIS_FP) $(S_ANALYSIS_EDF) $(H_ANALYSIS_EDF)

$(SBF) : $(OBJ_SBF)  $(LIBS)
	gcc -o $(BIN_PATH)/$@ $^

$(S_ANALYSIS_FP) : $(OBJ_S_ANALYSIS_FP) $(LIBS)
	gcc -o $(BIN_PATH)/$@ $^

$(H_ANALYSIS_FP) : $(OBJ_H_ANALYSIS_FP)  $(LIBS)
	gcc -o $(BIN_PATH)/$@ $^

$(S_ANALYSIS_EDF) : $(OBJ_S_ANALYSIS_EDF)  $(LIBS)
	gcc -o $(BIN_PATH)/$@ $^

$(H_ANALYSIS_EDF) : $(OBJ_H_ANALYSIS_EDF)  $(LIBS)
	gcc -o $(BIN_PATH)/$@ $^

%.o : %.c
	gcc $(CFLAGS) $(INCLUDEFLAGS) -c -o $@ $<

.PHONY:
soft_clean :
	rm -f $(OBJS) $(LIBS)

.PHONY:
clean :
	rm -f $(OBJS) $(LIBS) $(BINS)

