/******************************************************************************
* File:    xbot_define.h
* Author:  NETNABI
* Created: 2025-05-21
*
* Description:
* This is the command line interface manager module.
*
* Revision History:
*   2025-05-21  xbot  New project.
-------------------------------------------------------------------------------
* coding info
01. a = array variable                      e.g. a_Data[]
02. b = bit fields                          e.g. b_Data
03. c = const                               e.g, c_Data
04. d = define                              e.g. d_Data
05. e = enum Type                           e.g. e_Data
06. f = Function                            e.g. f_Data
07. g = Source file static variable         e.g. gv_Data
08. i = Inline                              e.g. i_Data
09. l = Static variables inside functions   e.g. lv_Data
10. m = enum member                         e.g. m_Data
11. p = Pointer                             e.g. p_Data 
12. s = struct                              e.g. s_Data 
13. t = typedef                             e.g. t_Data 
14. u = Union                               e.g. u_Data 
15. v = variable                            e.g. v_Data
16. x = extern                              e.g. xv_data
******************************************************************************/
#ifndef XBOT_DEFINE_H
#define XBOT_DEFINE_H
///================================================================ [ Define ]

//================================================================ [ Typedef ]
typedef unsigned char               tu8;
typedef unsigned short              tu16;
typedef unsigned long               tu32;
typedef unsigned long long          tu64;

typedef signed char                 ts8;
typedef short                       ts16;
typedef long                        ts32;
typedef long long                   ts64;

typedef const unsigned char         tcu8;
typedef const unsigned short        tcu16;
typedef const unsigned long         tcu32;
typedef const unsigned long long    tcu64;

typedef const signed char           tcs8;
typedef const short                 tcs16;
typedef const long                  tcs32;
typedef const long long             tcs64;

typedef float                       tf32;
typedef double                      tf64;
#endif