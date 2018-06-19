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
TDA_EDF = tda_edf
TDA_RM = tda_rm
H_ANALYSIS_EDF = h_analysis_edf
H_ANALYSIS_RM = h_analysis_rm

LIB_TIO = $(LIB_PATH)/task/task_io.o
LIB_SP = $(LIB_PATH)/task/scheduling_points.o
LIB_UF = $(LIB_PATH)/task/utilization_factor.o
LIB_UTILITIES = $(LIB_PATH)/utilities/utilities.o
LIB_PRINTS = $(LIB_PATH)/utilities/prints.o
LIB_SBF = $(LIB_PATH)/sbf/sbf.o
LIB_DBF_EDF = $(LIB_PATH)/dbf/edf.o
LIB_DBF_RM = $(LIB_PATH)/dbf/rm.o
LIB_TDA_EDF = $(LIB_PATH)/tda/edf.o
LIB_TDA_RM = $(LIB_PATH)/tda/rm.o
LIB_H_ANALYSIS_EDF = $(LIB_PATH)/h_analysis/edf.o
LIB_H_ANALYSIS_RM = $(LIB_PATH)/h_analysis/rm.o
LIBS = $(LIB_TIO) $(LIB_SP) $(LIB_UF) $(LIB_UTILITIES) $(LIB_PRINTS) $(LIB_SBF) $(LIB_DBF_EDF) $(LIB_DBF_RM) $(LIB_TDA_EDF) $(LIB_TDA_RM) $(LIB_H_ANALYSIS_EDF) $(LIB_H_ANALYSIS_RM)

OBJ_SBF = $(SRC_PATH)/sbf/$(SBF).o
OBJ_TDA_EDF = $(SRC_PATH)/tda/$(TDA_EDF).o
OBJ_TDA_RM = $(SRC_PATH)/tda/$(TDA_RM).o
OBJ_H_ANALYSIS_EDF = $(SRC_PATH)/h_analysis/$(H_ANALYSIS_EDF).o
OBJ_H_ANALYSIS_RM = $(SRC_PATH)/h_analysis/$(H_ANALYSIS_RM).o
OBJS = $(OBJ_SBF) $(OBJ_TDA_EDF) $(OBJ_TDA_RM) $(OBJ_H_ANALYSIS_EDF) $(OBJ_H_ANALYSIS_RM)

BINS = $(BIN_PATH)/$(SBF) $(BIN_PATH)/$(TDA_EDF) $(BIN_PATH)/$(TDA_RM) $(BIN_PATH)/$(H_ANALYSIS_EDF) $(BIN_PATH)/$(H_ANALYSIS_RM) 

.PHONY:
all : $(SBF) $(TDA_RM) $(H_ANALYSIS_RM) $(TDA_EDF) $(H_ANALYSIS_EDF)

$(SBF) : $(OBJ_SBF)  $(LIBS)
	gcc -o $(BIN_PATH)/$@ $^

$(TDA_RM) : $(OBJ_TDA_RM) $(LIBS)
	gcc -o $(BIN_PATH)/$@ $^

$(H_ANALYSIS_RM) : $(OBJ_H_ANALYSIS_RM)  $(LIBS)
	gcc -o $(BIN_PATH)/$@ $^

$(TDA_EDF) : $(OBJ_TDA_EDF)  $(LIBS)
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

