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

S_ANALYSIS_EDF = 		$(S_ANALYSIS)_edf
S_ANALYSIS_FP = 		$(S_ANALYSIS)_fp
H_ANALYSIS_EDF = 		$(H_ANALYSIS)_edf
H_ANALYSIS_FP = 		$(H_ANALYSIS)_fp

LIB_CIO = 				$(LIB_PATH)/cpu/cpu_io.o
LIB_TIO = 				$(LIB_PATH)/task/task_io.o
LIB_SP = 				$(LIB_PATH)/task/testing_set.o
LIB_UF = 				$(LIB_PATH)/task/utilization_factor.o
LIB_UTILITIES =			$(LIB_PATH)/utilities/utilities.o
LIB_PRINTS = 			$(LIB_PATH)/utilities/prints.o
LIB_BF =				$(LIB_PATH)/bin_packing/best_fit.o
LIB_FF =				$(LIB_PATH)/bin_packing/first_fit.o
LIB_NF =				$(LIB_PATH)/bin_packing/next_fit.o
LIB_WF =				$(LIB_PATH)/bin_packing/worst_fit.o
LIB_SBF = 				$(LIB_PATH)/sbf/sbf.o
LIB_DBF_EDF = 			$(LIB_PATH)/dbf/edf.o
LIB_DBF_FP =			$(LIB_PATH)/dbf/fp.o
LIB_S_ANALYSIS_EDF = 	$(LIB_PATH)/$(S_ANALYSIS)/edf.o
LIB_S_ANALYSIS_FP = 	$(LIB_PATH)/$(S_ANALYSIS)/fp.o
LIB_H_ANALYSIS_EDF = 	$(LIB_PATH)/$(H_ANALYSIS)/edf.o
LIB_H_ANALYSIS_FP = 	$(LIB_PATH)/$(H_ANALYSIS)/fp.o
LIB_MCPU_ANALYSIS = 	$(LIB_PATH)/$(MCPU_ANALYSIS)/$(MCPU_ANALYSIS).o
LIBS = 					$(LIB_CIO) $(LIB_TIO) $(LIB_SP) $(LIB_UF) $(LIB_UTILITIES) $(LIB_PRINTS) $(LIB_BF) $(LIB_FF) $(LIB_NF) $(LIB_WF) $(LIB_SBF) $(LIB_DBF_EDF) $(LIB_DBF_FP) $(LIB_S_ANALYSIS_EDF) $(LIB_S_ANALYSIS_FP) $(LIB_H_ANALYSIS_EDF) $(LIB_H_ANALYSIS_FP) $(LIB_MCPU_ANALYSIS)

OBJ_SBF = 				$(SRC_PATH)/sbf/$(SBF).o
OBJ_S_ANALYSIS_EDF = 	$(SRC_PATH)/$(S_ANALYSIS)/$(S_ANALYSIS_EDF).o
OBJ_S_ANALYSIS_FP = 	$(SRC_PATH)/$(S_ANALYSIS)/$(S_ANALYSIS_FP).o
OBJ_H_ANALYSIS_EDF = 	$(SRC_PATH)/$(H_ANALYSIS)/$(H_ANALYSIS_EDF).o
OBJ_H_ANALYSIS_FP = 	$(SRC_PATH)/$(H_ANALYSIS)/$(H_ANALYSIS_FP).o
OBJ_MCPU_ANALYSIS = 	$(SRC_PATH)/$(MCPU_ANALYSIS)/$(MCPU_ANALYSIS).o
OBJS = 					$(OBJ_SBF) $(OBJ_S_ANALYSIS_EDF) $(OBJ_S_ANALYSIS_FP) $(OBJ_H_ANALYSIS_EDF) $(OBJ_H_ANALYSIS_FP) $(OBJ_MCPU_ANALYSIS)

BINS = 					$(BIN_PATH)/$(SBF) $(BIN_PATH)/$(S_ANALYSIS_EDF) $(BIN_PATH)/$(S_ANALYSIS_FP) $(BIN_PATH)/$(H_ANALYSIS_EDF) $(BIN_PATH)/$(H_ANALYSIS_FP) $(BIN_PATH)/$(MCPU_ANALYSIS)

.PHONY:
all : $(MCPU_ANALYSIS) $(SBF) $(S_ANALYSIS) $(H_ANALYSIS)

.PHONY:
$(S_ANALYSIS) : $(S_ANALYSIS_FP) $(S_ANALYSIS_EDF)

.PHONY:
$(H_ANALYSIS) : $(H_ANALYSIS_FP) $(H_ANALYSIS_EDF)

.PHONY:
$(SBF) : $(OBJ_SBF)  $(LIBS)
	gcc -o $(BIN_PATH)/$@ $^

.PHONY:	
$(MCPU_ANALYSIS) : $(OBJ_MCPU_ANALYSIS)  $(LIBS)
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

