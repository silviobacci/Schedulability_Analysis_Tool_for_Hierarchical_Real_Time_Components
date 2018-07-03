#ifndef S_ALGORITHM_H
#define S_ALGORITHM_H

//------------------------------------------------------------------------------
// GLOBAL AND EXTERN DATA STRUCTURES
//------------------------------------------------------------------------------

// This enum contains all the scheduling algorithms supported
typedef enum s_algorithm_ {FP, RM, DM, EDF} s_algorithm;

//------------------------------------------------------------------------------
// FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// PRINT S ALGORITHM: prints info about the schduling algorithm
//------------------------------------------------------------------------------

void print_s_algorithm(s_algorithm a, FILE *f);

//------------------------------------------------------------------------------
// S ALGORITHM TO STRING: converts the integer of the enum in a string
//------------------------------------------------------------------------------

char * s_algorithm_to_string(s_algorithm a);

#endif
