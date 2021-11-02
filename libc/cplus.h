#ifndef _CPLUS_H
#define _CPLUS_H

#ifdef __cplusplus
    #define EXPORT_C_START extern "C" {

    #define EXPORT_C_END }
#else
    #define EXPORT_C_START
    #define EXPORT_C_END
#endif

#endif