 /* 
 * File:   std_types.h
 * Author: GPU_Tech
 *
 * Created on March 25, 2023, 2:05 PM
 */

#ifndef STD_TYPES_H
#define	STD_TYPES_H

typedef unsigned char       uint8  ;
typedef unsigned short      uint16 ;
typedef unsigned int        uint32;
typedef unsigned long       uint64 ;

typedef signed char       sint8  ;
typedef signed short      sint16 ;
typedef signed int        sint32 ;
typedef signed long       sint64 ;

typedef float             f32 ;
typedef double            f64 ;

/*  Section : Macro declarations */
#define STD_HIGH    0x01
#define STD_LOW     0x00

#define STD_ON      0x01
#define STD_OFF     0x00

#define NULL ((void *)0)


/*  Section : Macro Functions declarations */

/*  Section : Data types declarations */
typedef enum 
{
    OK = 1 ,
    N_OK = 0 
}Err_check_t;

/*  Section : Functions declarations */
#endif	/* STD_TYPES_H */

