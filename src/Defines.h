/**
 *  Project:      EvoDeMo - Bachelor Thesis
 *  Date:         May 10, 2010 (estimated)
 **
 *  Author:       Martin Balaz
 *  Contact:      balaz.marti@gmail.com
 *                xbalaz00@stud.fit.vutbr.cz
 **
 *  Institution:  Brno University of Technology
 *                Faculty of Information Technology
 *                www.fit.vutbr.cz
 **
 *  Copyright (c) 2010 by Martin Balaz
 */

//==============================================================

#ifndef DEFINES_H
#define DEFINES_H

//==============================================================

#define SPACE_TYPE_GRID           0
#define SPACE_TYPE_TORUS          1

//==============

#define SPACE_SIZE_X_MIN          1
#define SPACE_SIZE_X_MAX          256
#define SPACE_SIZE_X_DEFAULT      10

#define SPACE_SIZE_Y_MIN          1
#define SPACE_SIZE_Y_MAX          256
#define SPACE_SIZE_Y_DEFAULT      10


#define SPACE_INPUT_SIZE_X_MIN    1
#define SPACE_INPUT_SIZE_X_MAX    128

#define SPACE_INPUT_SIZE_Y_MIN    1
#define SPACE_INPUT_SIZE_Y_MAX    128


#define SPACE_OUTPUT_SIZE_X_MIN   2
#define SPACE_OUTPUT_SIZE_X_MAX   256

#define SPACE_OUTPUT_SIZE_Y_MIN   2
#define SPACE_OUTPUT_SIZE_Y_MAX   256

//==============
//==============

#define STATES_COUNT_DEFAULT      2
#define STATES_COUNT_MIN          2
#define STATES_COUNT_MAX          4

#define STATE_DEFAULT             0

//==============

#define CELL_STATE_EMPTY          0
#define CELL_STATE_LIVE_1         1
#define CELL_STATE_LIVE_2         2
#define CELL_STATE_LIVE_3         3
#define CELL_STATE_ERR            -1

#define CELL_COLOR_E              0xffffffff
#define CELL_COLOR_L1             0xffff0000
#define CELL_COLOR_L2             0xff00ff00
#define CELL_COLOR_L3             0xff0000ff
#define CELL_COLOR_ERR            0xff888888

//==============
//==============

#define GRAPHICS_CELL_SIZE_PIX    64

//==============
//==============

#define GENOME_TYPE_2_9N          29
#define GENOME_TYPE_3_9N          39
#define GENOME_TYPE_4_9N          49

#define GENOME_TYPE_2_5N          25
#define GENOME_TYPE_3_5N          35
#define GENOME_TYPE_4_5N          45

#define GENOME_TYPE_2_INS         21
//#define GENOME_TYPE_3_INS         31
//#define GENOME_TYPE_4_INS         41

#define GENOME_SIZE_TYPE_2_9N     512
#define GENOME_SIZE_TYPE_3_9N     19683
#define GENOME_SIZE_TYPE_4_9N     262144

#define GENOME_SIZE_TYPE_2_5N     32
#define GENOME_SIZE_TYPE_3_5N     243
#define GENOME_SIZE_TYPE_4_5N     1024

#define GENOME_SIZE_TYPE_2_INS    40
//#define GENOME_SIZE_TYPE_3_INS    40
//#define GENOME_SIZE_TYPE_4_INS    40

#define GENOME_SIZE_BITS_TYPE_2_9N   512     // (2^9)
#define GENOME_SIZE_BITS_TYPE_3_9N   39366   // (3^9)*2
#define GENOME_SIZE_BITS_TYPE_4_9N   524288  // (4^9)*2

#define GENOME_INDEX_T2_2_0       1       // 2^0
#define GENOME_INDEX_T2_2_1       2       // 2^1
#define GENOME_INDEX_T2_2_2       4       // 2^2
#define GENOME_INDEX_T2_2_3       8       // 2^3
#define GENOME_INDEX_T2_2_4       16      // 2^4
#define GENOME_INDEX_T2_2_5       32      // 2^5
#define GENOME_INDEX_T2_2_6       64      // 2^6
#define GENOME_INDEX_T2_2_7       128     // 2^7
#define GENOME_INDEX_T2_2_8       256     // 2^8

#define GENOME_INDEX_T3_3_0       1       // 3^0
#define GENOME_INDEX_T3_3_1       3       // 3^1
#define GENOME_INDEX_T3_3_2       9       // 3^2
#define GENOME_INDEX_T3_3_3       27      // 3^3
#define GENOME_INDEX_T3_3_4       81      // 3^4
#define GENOME_INDEX_T3_3_5       243     // 3^5
#define GENOME_INDEX_T3_3_6       729     // 3^6
#define GENOME_INDEX_T3_3_7       2187    // 3^7
#define GENOME_INDEX_T3_3_8       6561    // 3^8

#define GENOME_INDEX_T4_4_0       1       // 4^0
#define GENOME_INDEX_T4_4_1       4       // 4^1
#define GENOME_INDEX_T4_4_2       16      // 4^2
#define GENOME_INDEX_T4_4_3       64      // 4^3
#define GENOME_INDEX_T4_4_4       256     // 4^4
#define GENOME_INDEX_T4_4_5       1024    // 4^5
#define GENOME_INDEX_T4_4_6       4096    // 4^6
#define GENOME_INDEX_T4_4_7       16384   // 4^7
#define GENOME_INDEX_T4_4_8       65536   // 4^8

//==============
//==============

#define SUB_GRID_SIZE_X           3
#define SUB_GRID_SIZE_Y           3

#define SUB_GRID_NEIGHBOR_POS_C   4
#define SUB_GRID_NEIGHBOR_POS_N   1
#define SUB_GRID_NEIGHBOR_POS_NW  0
#define SUB_GRID_NEIGHBOR_POS_W   3
#define SUB_GRID_NEIGHBOR_POS_SW  6
#define SUB_GRID_NEIGHBOR_POS_S   7
#define SUB_GRID_NEIGHBOR_POS_SE  8
#define SUB_GRID_NEIGHBOR_POS_E   5
#define SUB_GRID_NEIGHBOR_POS_NE  2

//==============

#define GRID_NEIGHBOR_POS_C       x,y
#define GRID_NEIGHBOR_POS_N       x,y-1
#define GRID_NEIGHBOR_POS_NW      x-1,y-1
#define GRID_NEIGHBOR_POS_W       x-1,y
#define GRID_NEIGHBOR_POS_SW      x-1,y+1
#define GRID_NEIGHBOR_POS_S       x,y+1
#define GRID_NEIGHBOR_POS_SE      x+1,y+1
#define GRID_NEIGHBOR_POS_E       x+1,y
#define GRID_NEIGHBOR_POS_NE      x+1,y-1

//==============
//==============

#define EVOLUTION_REPEATITIONS_MIN      1
#define EVOLUTION_REPEATITIONS_MAX      1000
#define EVOLUTION_REPEATITIONS_DEFAULT  1

//==============

#define GENERATIONS_COUNT_MIN           1
#define GENERATIONS_COUNT_MAX           2500
#define GENERATIONS_COUNT_DEFAULT       200

//==============

#define POPULATION_INIT_MIN             20
#define POPULATION_INIT_MAX             200
#define POPULATION_INIT_DEFAULT         100

//==============

#define GENOME_TYPE_EVO_WID_9N    0
#define GENOME_TYPE_EVO_WID_5N    1
#define GENOME_TYPE_EVO_WID_INS   2

//==============
//==============

#define CROSSOVER_PROB_MIN        0
#define CROSSOVER_PROB_MAX        100
#define CROSSOVER_PROB_DEFAULT    90

#define CROSSOVER_COUNT_MIN       0
#define CROSSOVER_COUNT_MAX       10
#define CROSSOVER_COUNT_DEFAULT   0

//==============

#define MUTATION_PROB_MIN         0
#define MUTATION_PROB_MAX         100
#define MUTATION_PROB_DEFAULT     85

#define MUTATION_COUNT_MIN        0
#define MUTATION_COUNT_MAX        262144
#define MUTATION_COUNT_DEFAULT    15

//==============
//==============

#define MOVE_DIR_NE               0
#define MOVE_DIR_N                1
#define MOVE_DIR_NW               2
#define MOVE_DIR_W                3
#define MOVE_DIR_SW               4
#define MOVE_DIR_S                5
#define MOVE_DIR_SE               6
#define MOVE_DIR_E                7
#define MOVE_DIR_ANY              8

//==============

#define STEPS_COUNT_MIN           1
#define STEPS_COUNT_MAX           20
#define STEPS_COUNT_INF           999
#define STEPS_COUNT_DEFAULT       5

//==============

#define MOVE_DIS_MIN              1
#define MOVE_DIS_MAX              4
#define MOVE_DIS_DEFAULT          1

//==============
//==============

#define FITNESS_VALUE_MIN         0
#define FITNESS_VALUE_MAX         10000
#define FITNESS_VALUE_INIT        -1

//==============
//==============

// B = best
// L = last
// E = every
// T = total
// A = all

// GEN   = generation
// CHROM = chromosome
// STEP  = cellular automata step
// RUN   = evolution run = repetition

#define GUI_DISPLAY_MODE_CA__NONE                       0
#define GUI_DISPLAY_MODE_CA__RUN_E__BEST_CHROM__E_STEP  1
#define GUI_DISPLAY_MODE_CA__RUN_T__BEST_CHROM__E_STEP  2
#define GUI_DISPLAY_MODE_CA__RUN_A__BEST_CHROM__E_STEP  3

#define GUI_DISPLAY_MODE_CA__BEST_CHROM__B_STEP       4
#define GUI_DISPLAY_MODE_CA__E_GEN__E_CHROM__B_STEP   5
#define GUI_DISPLAY_MODE_CA__E_GEN__E_CHROM__L_STEP   6
#define GUI_DISPLAY_MODE_CA__E_GEN__E_CHROM__E_STEP   7


#define GUI_DISPLAY_MODE_CA_TOP_x_MIN                 1
#define GUI_DISPLAY_MODE_CA_TOP_x_MAX                 10
#define GUI_DISPLAY_MODE_CA_TOP_x_DEFAULT             4

#define GUI_DISPLAY_MODE_CA_RUN_TIMEOUT_MSEC_MIN      100
#define GUI_DISPLAY_MODE_CA_RUN_TIMEOUT_MSEC_MAX      1000
#define GUI_DISPLAY_MODE_CA_RUN_TIMEOUT_MSEC_DEFAULT  500

//==============

#define FILE_EX__CA_MODE_NONE                     0
#define FILE_EX__CA_MODE__INIT_SPACE              1
#define FILE_EX__CA_MODE__IMPORT_SPACE            2
#define FILE_EX__CA_MODE__RUN_E__CHROM_B__STEP_E  3
#define FILE_EX__CA_MODE__RUN_B__CHROM_B__STEP_E  4

#define FILE_EX__GA_MODE_NONE                     0
#define FILE_EX__GA_MODE__RUN_E__CHROM_A          1
#define FILE_EX__GA_MODE__RUN_E__CHROM_B          2
#define FILE_EX__GA_MODE__RUN_B__CHROM_B          3

//==============
//==============

#define THREAD_CORE_SIGNAL_INIT_DONE            0

#define THREAD_CORE_SIGNAL_SIM_DONE             1
#define THREAD_CORE_SIGNAL_BEST_READY           2
#define THREAD_CORE_SIGNAL_TOTAL_BEST_READY     3
#define THREAD_CORE_SIGNAL_IMPORT_READY         4

#define THREAD_CORE_SIGNAL_ERR_INIT_THREAD     -1
#define THREAD_CORE_SIGNAL_ERR_INIT_GENOTYPE   -2
#define THREAD_CORE_SIGNAL_ERR_INPUT_CA_SPACE  -3
#define THREAD_CORE_SIGNAL_ERR_IMPORT_FAILED   -4

//==============

#define THREAD_GA_THREAD_CA_COUNT_MIN           1
#define THREAD_GA_THREAD_CA_COUNT_MAX           2
#define THREAD_GA_THREAD_CA_COUNT_DEFAULT       1

//==============
//==============

#define ARRAY_OK                         0
#define ARRAY_ERR_UNKNOWN               -1
#define ARRAY_ERR_MEM_FAIL              -2

#define SPACE_OK                         0
#define SPACE_ERR_UNKNOWN               -1
#define SPACE_ERR_ACCESS_FAIL           -5
#define SPACE_ERR_OUT_OF_RANGE          -6
#define SPACE_ERR_MEM_ALLOC             -7

#define CA_OK                            0
#define CA_ERR_UNKNOWN                  -1
#define CA_ERR_TORUS_NULL               -10
#define CA_ERR_GRID_NULL                -11

#define TFUNCTION_OK                     0
#define TFUNCTION_ERR_UNKNOWN           -1
#define TFUNCTION_ERR_GRID_NULL         -13
#define TFUNCTION_ERR_TORUS_NULL        -14
#define TFUNCTION_ERR_RULES_NULL        -15
#define TFUNCTION_ERR_SUB_A_NULL        -16
#define TFUNCTION_ERR_GRIDS_SIZE        -17
#define TFUNCTION_ERR_GRIDS_SAME        -18
#define TFUNCTION_ERR_TORUSES_SIZE      -19
#define TFUNCTION_ERR_TORUSES_SAME      -20

#define CROSSOVER_OK                     0
#define CROSSOVER_ERR_UNKNOWN           -1
#define CROSSOVER_ERR_POINTER_NULL      -21

#define FITNESS_OK                       0
#define FITNESS_ERR_UNKNOWN             -1
#define FITNESS_ERR_POINTER_NULL        -22
#define FITNESS_ERR_NO_NON_EMPTY_CELL   -23

#define GA_OK                            0
#define GA_ERR_UNKNOWN                  -1
#define GA_ERR_MEMORY_FAIL              -24
#define GA_ERR_NULL_POINTER             -25
#define GA_ERR_OUT_OF_RANGE             -26
#define GA_ERR_NO_INPUT                 -27

#define GENOME_OK                        0
#define GENOME_ERR_UNKNOWN              -1
#define GENOME_ERR_TX_NULL              -28

#define MUTATION_OK                      0
#define MUTATION_ERR_UNKNOWN            -1
#define MUTATION_ERR_POINTER_NULL       -29

#define RANDOM_OK                        0
#define RANDOM_ERR_UNKNOWN              -1
#define RANDOM_ERR_POINTER_NULL         -30

#define CORE_OK                          0
#define CORE_ERR_UNKNOWN                -1
#define CORE_ERR_MEM_FAIL               -31

#define EXPORT_GA_OK                     0
#define EXPORT_GA_ERR_UNKNOWN           -1
#define EXPORT_GA_ERR_POINTER_NULL      -32

#define THREAD_CORE_OK                   0
#define THREAD_CORE_ERR_UNKNOWN         -1
#define THREAD_CORE_ERR_POINTERS        -33
#define THREAD_CORE_ERR_MEM_FAIL        -34
#define THREAD_CORE_ERR_INIT_GA         -35
#define THREAD_CORE_ERR_INIT_CA         -36
#define THREAD_CORE_ERR_INIT_CA_M       -37
#define THREAD_CORE_ERR_CORE_GA         -38
#define THREAD_CORE_ERR_CORE_CA         -39
#define THREAD_CORE_ERR_SPACE_NO_NON_EMPTY_CELL -40
#define THREAD_CORE_ERR_IMPORT_FAILED           -80

#define IMPORT_GA_OK                             0
#define IMPORT_GA_ERR_UNKNOWN                   -1
#define IMPORT_GA_ERR_NULL_POINTER              -41
#define IMPORT_GA_ERR_EMPTY_FILE                -42
#define IMPORT_GA_ERR_UNCOMPATIBILE_GENOME      -43
#define IMPORT_GA_ERR_XML_PARSE                 -44
#define IMPORT_GA_ERR_NOT_LAST_GENOM            -45

//==============
//==============

#define ERROR_STRING__OK                              "OK"
#define ERROR_STRING__ERR_UNKNOWN                     "Unknown error"
#define ERROR_STRING__ARRAY_ERR_MEM_FAIL              "ARRAY_ERR_MEM_FAIL"
#define ERROR_STRING__SPACE_ERR_ACCESS_FAIL           "SPACE_ERR_ACCESS_FAIL"
#define ERROR_STRING__SPACE_ERR_OUT_OF_RANGE          "SPACE_ERR_OUT_OF_RANGE"
#define ERROR_STRING__SPACE_ERR_MEM_ALLOC             "SPACE_ERR_MEM_ALLOC"
#define ERROR_STRING__CA_ERR_TORUS_NULL               "CA_ERR_TORUS_NULL"
#define ERROR_STRING__CA_ERR_GRID_NULL                "CA_ERR_GRID_NULL"
#define ERROR_STRING__TFUNCTION_ERR_GRID_NULL         "TFUNCTION_ERR_GRID_NULL"
#define ERROR_STRING__TFUNCTION_ERR_TORUS_NULL        "TFUNCTION_ERR_TORUS_NULL"
#define ERROR_STRING__TFUNCTION_ERR_RULES_NULL        "TFUNCTION_ERR_RULES_NULL"
#define ERROR_STRING__TFUNCTION_ERR_SUB_A_NULL        "TFUNCTION_ERR_SUB_A_NULL"
#define ERROR_STRING__TFUNCTION_ERR_GRIDS_SIZE        "TFUNCTION_ERR_GRIDS_SIZE"
#define ERROR_STRING__TFUNCTION_ERR_GRIDS_SAME        "TFUNCTION_ERR_GRIDS_SAME"
#define ERROR_STRING__TFUNCTION_ERR_TORUSES_SIZE      "TFUNCTION_ERR_TORUSES_SIZE"
#define ERROR_STRING__TFUNCTION_ERR_TORUSES_SAME      "TFUNCTION_ERR_TORUSES_SAME"
#define ERROR_STRING__CROSSOVER_ERR_POINTER_NULL      "CROSSOVER_ERR_POINTER_NULL"
#define ERROR_STRING__FITNESS_ERR_POINTER_NULL        "FITNESS_ERR_POINTER_NULL"
#define ERROR_STRING__FITNESS_ERR_NO_NON_EMPTY_CELL   "FITNESS_ERR_NO_NON_EMPTY_CELL"
#define ERROR_STRING__GA_ERR_MEMORY_FAIL              "GA_ERR_MEMORY_FAIL"
#define ERROR_STRING__GA_ERR_NULL_POINTER             "GA_ERR_NULL_POINTER"
#define ERROR_STRING__GA_ERR_OUT_OF_RANGE             "GA_ERR_OUT_OF_RANGE"
#define ERROR_STRING__GA_ERR_NO_INPUT                 "GA_ERR_NO_INPUT"
#define ERROR_STRING__GENOME_ERR_TX_NULL              "GENOME_ERR_TX_NULL"
#define ERROR_STRING__MUTATION_ERR_POINTER_NULL       "MUTATION_ERR_POINTER_NULL"
#define ERROR_STRING__RANDOM_ERR_POINTER_NULL         "RANDOM_ERR_POINTER_NULL"
#define ERROR_STRING__CORE_ERR_MEM_FAIL               "CORE_ERR_MEM_FAIL"
#define ERROR_STRING__EXPORT_GA_ERR_POINTER_NULL      "EXPORT_GA_ERR_POINTER_NULL"
#define ERROR_STRING__THREAD_CORE_ERR_POINTERS        "THREAD_CORE_ERR_POINTERS"
#define ERROR_STRING__THREAD_CORE_ERR_MEM_FAIL        "THREAD_CORE_ERR_MEM_FAIL"
#define ERROR_STRING__THREAD_CORE_ERR_INIT_GA         "THREAD_CORE_ERR_INIT_GA"
#define ERROR_STRING__THREAD_CORE_ERR_INIT_CA         "THREAD_CORE_ERR_INIT_CA"
#define ERROR_STRING__THREAD_CORE_ERR_INIT_CA_M       "THREAD_CORE_ERR_INIT_CA_M"
#define ERROR_STRING__THREAD_CORE_ERR_CORE_GA         "THREAD_CORE_ERR_CORE_GA"
#define ERROR_STRING__THREAD_CORE_ERR_CORE_CA         "THREAD_CORE_ERR_CORE_CA"
#define ERROR_STRING__THREAD_CORE_ERR_SPACE_NO_NON_EMPTY_CELL "THREAD_CORE_ERR_SPACE_NO_NON_EMPTY_CELL"
#define ERROR_STRING__THREAD_CORE_ERR_IMPORT_FAILED       "THREAD_CORE_ERR_IMPORT_FAILED"
#define ERROR_STRING__IMPORT_GA_ERR_NULL_POINTER          "IMPORT_GA_ERR_NULL_POINTER"
#define ERROR_STRING__IMPORT_GA_ERR_EMPTY_FILE            "IMPORT_GA_ERR_EMPTY_FILE"
#define ERROR_STRING__IMPORT_GA_ERR_UNCOMPATIBILE_GENOME  "IMPORT_GA_ERR_UNCOMPATIBILE_GENOME"
#define ERROR_STRING__IMPORT_GA_ERR_XML_PARSE             "IMPORT_GA_ERR_XML_PARSE"
#define ERROR_STRING__IMPORT_GA_ERR_NOT_LAST_GENOM        "IMPORT_GA_ERR_NOT_LAST_GENOM"

//==============================================================

typedef char BYTE;

//==============================================================

#endif // DEFINES_H

//==============================================================

