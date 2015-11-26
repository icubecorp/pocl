#include "config.h"

/* Installable Client Driver-realated things. */
#ifndef POCL_ICD_H
#define POCL_ICD_H

// stub out ICD related stuff 
#ifndef BUILD_ICD

#  define POCL_DEVICE_ICD_DISPATCH
#  define POCL_INIT_ICD_OBJECT(__obj__)

// rest of the file: ICD is enabled 
#else

// this define is a kludge!
// The ICD loaders seem to require OCL 1.1, so we cannot (can we?) leave deprecated 
// functions out
// Answer: not really. ICD loader will call OCL 1.1 function throught the
// function table, but the registered function can be then only stubs
// (perhaps with a warning) or even NULL (in this case, a program using
// OCL 1.1 function will crash: ICD Loaders does not do any check)
#  define CL_USE_DEPRECATED_OPENCL_1_1_APIS

#  ifndef CL_USE_DEPRECATED_OPENCL_1_1_APIS
#    error CL_USE_DEPRECATED_OPENCL_1_1_APIS not in use
#  endif

extern struct _cl_icd_dispatch pocl_dispatch;  //from clGetPlatformIDs.c

#  define POCL_DEVICE_ICD_DISPATCH &pocl_dispatch,
#  define POCL_INIT_ICD_OBJECT(__obj__) (__obj__)->dispatch=&pocl_dispatch

/* Define the ICD dispatch structure that gets filled below. 
 * Prefer to get it from ocl-icd, as that has compile time type checking
 * of the function signatures. This checks that they are in correct order.
 */
#ifdef HAVE_OCL_ICD 
#include <ocl_icd.h>
#else
#define OCL_ICD_IDENTIFIED_FUNCTIONS 116
struct _cl_icd_dispatch {
        void *funcptr[166];
};
#endif

#endif
#endif

