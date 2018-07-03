#ifndef A_ALGORITHM_H
#define A_ALGORITHM_H

//------------------------------------------------------------------------------
// GLOBAL DATA STRUCTURES
//------------------------------------------------------------------------------

// This enums contains all the allwoed bin packing algorhtms
typedef enum a_algorithm_ {BF, FF, NF, WF, FFD} a_algorithm;

//------------------------------------------------------------------------------
// PRINT A ALGORITHM: prints info about the allocation algorithm
//------------------------------------------------------------------------------

void print_a_algorithm(a_algorithm a, FILE *f);

//------------------------------------------------------------------------------
// A ALGORITHM TO STRING: converts enum integer to string
//------------------------------------------------------------------------------

char * a_algorithm_to_string(a_algorithm a);

#endif
