/******************************************************************************
* File:    xbot_schedluer_type.h
* Author:  NETNABI
* Created: 2025-05-21
*
* Description:
* This is the scheduler manager module.
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
#ifndef XBOT_SCHEDULER_TYPE_H
#define XBOT_SCHEDULER_TYPE_H
///================================================================ [ Include ]
#include "./xbot_define.h"
///================================================================ [ Typedef ]
typedef enum
{
    m_BASE_SCHEDULER_STATE_DISABLE = 0,
    m_BASE_SCHEDULER_STATE_IDEL,
    m_BASE_SCHEDULER_STATE_INIT,
    m_BASE_SCHEDULER_STATE_RUN,
    m_BASE_SCHEDULER_STATE_COMPLETE,
    m_BASE_SCHEDULER_STATE_ERROR_TIMEOUT = 100,
    m_BASE_SCHEDULER_STATE_ERROR_CRC,
    m_BASE_SCHEDULER_STATE_ERROR_VALUE
}te_Base_Scheduler_State;

typedef struct
{
    void (*fp_Run)(void);                   //- Function point.
    tu32 v_Job_TableSize;                   //- Job table size.
    tu32 v_Job_Step;                        //- Job step.
    tu32 v_Task_TableSize;                  //- Task table size.
    tu32 v_Task_Step;                       //- Task step.
    tu32 v_Work_TableSize;                  //- Work table size.
    tu32 v_Work_Step;                       //- Work Step.
    tu32 v_Work_TimeDelay;                  //- Work Time Delay(us)
    tu32 v_Work_TimeOut;                    //- Work Time out(us)
    tu32 v_Work_RunTime;                    //- Work Run time(us)
    te_Base_Scheduler_State e_Work_State;   //- Work State.
}ts_Base_Scheduler_Ctrl;

#endif