CC = 					gcc
CPPFLAGS = 				-Ilib
CFLAGS = 				-Wall -Wextra -pedantic -std=c11 
LDLIBS =				-lm

ifdef DEBUG
	CFLAGS += 			-g -O0
else
	CFLAGS += 			-O3
endif

VPATH = lib src 

SRC_PATH = 				src
LIB_PATH = 				lib
BIN_PATH = 				bin

SBF = 					sbf
S_ANALYSIS = 			s_analysis
H_ANALYSIS = 			h_analysis
MCPU_ANALYSIS = 		mcpu_analysis
FIND_PS_ANALYSIS = 		find_ps_analysis

LIB_VIO = 				$(LIB_PATH)/vm/vm_io.o
LIB_VS = 				$(LIB_PATH)/vm/sorting.o
LIB_AA = 				$(LIB_PATH)/vm/a_algorithm.o
LIB_TIO = 				$(LIB_PATH)/task/task_io.o
LIB_TTS = 				$(LIB_PATH)/task/testing_set.o
LIB_TS = 				$(LIB_PATH)/task/sorting.o
LIB_TU = 				$(LIB_PATH)/task/utilities.o
LIB_SA = 				$(LIB_PATH)/task/s_algorithm.o
LIB_SBF = 				$(LIB_PATH)/schedulability/sbf.o
LIB_DBF = 				$(LIB_PATH)/schedulability/dbf.o
LIB_S_ANALYSIS = 		$(LIB_PATH)/schedulability/s_analysis.o
LIB_H_ANALYSIS = 		$(LIB_PATH)/schedulability/h_analysis.o
LIB_MCPU_ANALYSIS = 	$(LIB_PATH)/schedulability/mcpu_analysis.o
COMMON_LIBS = 			$(LIB_TIO) $(LIB_TTS) $(LIB_TS) $(LIB_TU) $(LIB_SA) $(LIB_SBF) $(LIB_DBF)
LIBS = 					$(COMMON_LIBS) $(LIB_VIO) $(LIB_VS) $(LIB_AA) $(LIB_S_ANALYSIS) $(LIB_H_ANALYSIS) $(LIB_MCPU_ANALYSIS)

OBJ_SBF = 				sbf.o
OBJ_S_ANALYSIS = 		s_analysis.o
OBJ_H_ANALYSIS = 		h_analysis.o
OBJ_MCPU_ANALYSIS = 	mcpu_analysis.o
OBJ_FIND_PS_ANALYSIS =	find_ps_analysis.o
OBJS = 					$(OBJ_SBF) $(OBJ_S_ANALYSIS) $(OBJ_H_ANALYSIS) $(OBJ_MCPU_ANALYSIS) $(OBJ_FIND_PS_ANALYSIS)

BINS = 					$(SBF) $(S_ANALYSIS) $(H_ANALYSIS) $(MCPU_ANALYSIS) $(FIND_PS_ANALYSIS)

.PHONY:
all : $(S_ANALYSIS)
#$(SBF) $(S_ANALYSIS) $(H_ANALYSIS) $(MCPU_ANALYSIS) $(FIND_PS_ANALYSIS)
#	mv $(BINS) $(BIN_PATH)

$(SBF) : $(OBJ_SBF) $(LIB_TIO) $(LIB_SBF)
$(S_ANALYSIS) : $(OBJ_S_ANALYSIS) 
# $(COMMON_LIBS) $(LIB_S_ANALYSIS)
$(H_ANALYSIS) : $(OBJ_H_ANALYSIS) $(COMMON_LIBS) $(LIB_H_ANALYSIS)
$(FIND_PS_ANALYSIS) : $(OBJ_FIND_PS_ANALYSIS) $(COMMON_LIBS) $(LIB_H_ANALYSIS)
$(MCPU_ANALYSIS) : $(OBJ_MCPU_ANALYSIS) $(COMMON_LIBS) $(LIB_VIO) $(LIB_VS) $(LIB_AA) $(LIB_S_ANALYSIS) $(LIB_H_ANALYSIS) $(LIB_MCPU_ANALYSIS)

%.d : %.c
	$(CC) -MM $(CPPFLAGS) -MF $@ $<
-include $(OBJ_SBF:.o=.d)
-include $(LIBS:.o=.d)

.PHONY:
soft_clean :
	rm -f $(OBJS) $(LIBS) *.d

.PHONY:
clean : soft_clean
	rm -f $(BINS)
