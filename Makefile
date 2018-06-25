CPPFLAGS = 				-Ilib
CFLAGS = 				-Wall -Wextra -pedantic -std=c11 
LDLIBS =				-lm

ifdef DEBUG
	CFLAGS += 			-g -O0
else
	CFLAGS += 			-O3
endif

SRC_PATH = 				src
LIB_PATH = 				lib
BIN_PATH = 				bin

SBF = 					sbf
S_ANALYSIS = 			$(BIN_PATH)/s_analysis
H_ANALYSIS = 			$(BIN_PATH)/h_analysis
MCPU_ANALYSIS = 		$(BIN_PATH)/mcpu_analysis
FIND_PS_ANALYSIS = 		$(BIN_PATH)/find_ps_analysis

LIB_VIO = 				$(LIB_PATH)/vm/vm_io.o
LIB_VS = 				$(LIB_PATH)/vm/sorting.o
LIB_VU = 				$(LIB_PATH)/vm/utilities.o
LIB_TIO = 				$(LIB_PATH)/task/task_io.o
LIB_TTS = 				$(LIB_PATH)/task/testing_set.o
LIB_TS = 				$(LIB_PATH)/task/sorting.o
LIB_TU = 				$(LIB_PATH)/task/utilities.o
LIB_SBF = 				$(LIB_PATH)/schedulability/sbf.o
LIB_DBF = 				$(LIB_PATH)/schedulability/dbf.o
LIB_S_ANALYSIS = 		$(LIB_PATH)/schedulability/s_analysis.o
LIB_H_ANALYSIS = 		$(LIB_PATH)/schedulability/h_analysis.o
LIB_MCPU_ANALYSIS = 	$(LIB_PATH)/schedulability/mcpu_analysis.o
COMMON_LIBS = 			$(LIB_TIO) $(LIB_TTS) $(LIB_SBF) $(LIB_DBF)
LIBS = 					$(COMMON_LIBS) $(LIB_VIO) $(LIB_VS) $(LIB_VU) $(LIB_TS) $(LIB_TU) $(LIB_S_ANALYSIS) $(LIB_H_ANALYSIS) $(LIB_MCPU_ANALYSIS)

OBJ_SBF = 				$(SRC_PATH)/sbf.o
OBJ_S_ANALYSIS = 		$(SRC_PATH)/s_analysis.o
OBJ_H_ANALYSIS = 		$(SRC_PATH)/h_analysis.o
OBJ_MCPU_ANALYSIS = 	$(SRC_PATH)/mcpu_analysis.o
OBJ_FIND_PS_ANALYSIS =	$(SRC_PATH)/find_ps_analysis.o
OBJS = 					$(OBJ_SBF) $(OBJ_S_ANALYSIS) $(OBJ_H_ANALYSIS) $(OBJ_MCPU_ANALYSIS) $(OBJ_FIND_PS_ANALYSIS)

BINS = 					$(SBF) $(S_ANALYSIS) $(H_ANALYSIS)$(MCPU_ANALYSIS) $(FIND_PS_ANALYSIS)

.PHONY:
all : $(SBF)
#$(SBF) $(S_ANALYSIS) $(H_ANALYSIS) $(MCPU_ANALYSIS) $(FIND_PS_ANALYSIS)

#$(SBF) : $(OBJ_SBF) $(LIB_TIO) $(LIB_SBF)
$(SBF) : src/sbf.o lib/task/task_io.o lib/task/utilities.o
$(S_ANALYSIS) : $(OBJ_S_ANALYSIS) $(COMMON_LIBS) $(LIB_S_ANALYSIS)
$(H_ANALYSIS) : $(OBJ_H_ANALYSIS) $(COMMON_LIBS) $(LIB_H_ANALYSIS)
$(MCPU_ANALYSIS) : $(OBJ_MCPU_ANALYSIS) $(COMMON_LIBS) $(LIB_VIO) $(LIB_MCPU_ANALYSIS) $(LIB_MCPU_ANALYSIS)
$(FIND_PS_ANALYSIS) : $(OBJ_FIND_PS_ANALYSIS) $(COMMON_LIBS) $(LIB_H_ANALYSIS)

.PHONY:
soft_clean :
	rm -f $(OBJS:.o=.d) $(LIBS:.o=.d) $(OBJS) $(LIBS)

.PHONY:
clean : soft_clean
	rm -f $(BINS)
