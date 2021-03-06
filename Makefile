LIB_PATH = 				lib
SRC_PATH = 				src
BIN_PATH = 				bin

CPPFLAGS = 				-I$(LIB_PATH)
CFLAGS = 				-Wall -pedantic -std=c11 
LDLIBS =				-lm

ifdef DEBUG
	CFLAGS += 			-g -O0
else
	CFLAGS += 			-O3
endif

SBF = 					$(SRC_PATH)/sbf
S_ANALYSIS = 			$(SRC_PATH)/s_analysis
H_ANALYSIS = 			$(SRC_PATH)/h_analysis
MCPU_ANALYSIS = 		$(SRC_PATH)/mcpu_analysis
FIND_PS_ANALYSIS = 		$(SRC_PATH)/find_ps_analysis

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
COMMON_LIBS = 			$(LIB_TIO) $(LIB_TTS) $(LIB_TS) $(LIB_TU) $(LIB_SA) $(LIB_DBF)
LIBS = 					$(COMMON_LIBS) $(LIB_VIO) $(LIB_VS) $(LIB_AA) $(LIB_S_ANALYSIS) $(LIB_H_ANALYSIS) $(LIB_MCPU_ANALYSIS)

OBJ_SBF = 				$(SRC_PATH)/sbf.o
OBJ_S_ANALYSIS = 		$(SRC_PATH)/s_analysis.o
OBJ_H_ANALYSIS = 		$(SRC_PATH)/h_analysis.o
OBJ_MCPU_ANALYSIS = 	$(SRC_PATH)/mcpu_analysis.o
OBJ_FIND_PS_ANALYSIS =	$(SRC_PATH)/find_ps_analysis.o
OBJS = 					$(OBJ_SBF) $(OBJ_S_ANALYSIS) $(OBJ_H_ANALYSIS) $(OBJ_MCPU_ANALYSIS) $(OBJ_FIND_PS_ANALYSIS)

BINS = 					$(SBF) $(S_ANALYSIS) $(H_ANALYSIS) $(MCPU_ANALYSIS) $(FIND_PS_ANALYSIS)

.PHONY:
all : $(SBF) $(S_ANALYSIS) $(H_ANALYSIS) $(MCPU_ANALYSIS) $(FIND_PS_ANALYSIS)

.PHONY:
install : 
	cp $(BINS) $(BIN_PATH)

.PHONY:
clean :
	rm -f $(OBJS) $(LIBS) $(OBJS:.o=.d) $(LIBS:.o=.d)
	
.PHONY:
clean_all : clean
	rm -f $(BINS)

$(SBF) : $(OBJ_SBF) $(COMMON_LIBS) $(LIB_SBF)
$(S_ANALYSIS) : $(OBJ_S_ANALYSIS) $(COMMON_LIBS) $(LIB_S_ANALYSIS)
$(H_ANALYSIS) : $(OBJ_H_ANALYSIS) $(COMMON_LIBS) $(LIB_SBF) $(LIB_H_ANALYSIS)
$(FIND_PS_ANALYSIS) : $(OBJ_FIND_PS_ANALYSIS) $(COMMON_LIBS) $(LIB_SBF) $(LIB_H_ANALYSIS)
$(MCPU_ANALYSIS) : $(OBJ_MCPU_ANALYSIS) $(COMMON_LIBS) $(LIB_VIO) $(LIB_VS) $(LIB_AA) $(LIB_SBF) $(LIB_S_ANALYSIS) $(LIB_H_ANALYSIS) $(LIB_MCPU_ANALYSIS)

%.d : %.c
	$(CC) -MM $(CPPFLAGS) -MF $@ $<
-include $(OBJS:.o=.d)
-include $(LIBS:.o=.d)
