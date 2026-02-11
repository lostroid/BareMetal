# C언어 Bare Metal 기반 오픈소스 입니다.
코드의 설계 방향성은 성능50% + 유지보수50% 생각하며 작성 합니다.

수십 us 차이가 별거 아니라고 생각 하겠지만  
  이것에 수십만 수백만 반복시 또는 코드가 많아지면  
  그차이는 엄청 나게 차이 납니다.  
그렇기 때문에 최대한 최적의 연산 과 처리를 고려 하면서  
 설계하도록 노력 했습니다.  
  
일반 OS 소프트웨어 코드처럼 데이터 중심의 설계가 아닌  
  인터페이스의 속도 및 최적의 버퍼 용량등  
  처리순서 기반을 중점으로 코드가 작성 되었습니다.  
  
코드로 보고 알아야 할 정보는 굳이 문서로 적지 않습니다.  
내용을 상세하게 적는 것도 좋을 순 있지만.  
양이 방대해지면 이것을 읽는 사람 또한 오래 걸리기 때문에  
가장 중요한 흐름 관점만 설명 합니다.  

디버그포트 사양
기본 디버깅(UART) 통신 속도는 500 Kbps 입니다.   
코어 클럭은 500Kbps 에 16배 기준으로 하며 에러율을 0%으로 하기위해     
8Mhz 배수로 UART 클럭을 선정하는게 좋습니다.    

JOB의 기준은 데이터를 실제 인터페이스 까지 전송을  

  
# Header File.
헤더파일은 소스코드의 목차 입니다. 
전체 기능들을 볼 수 있으며  
외부연결 extern 도 헤더파일에 포함 하는 방식을 취합니다.  
절대 다른 소스코드에 extern 으로 끌어 쓰지 마십시오.  
extern 을 사용 하고 싶은 해당 대상 헤더를 포함 시키시오.  



# 활동링크
유튜브 : https://www.youtube.com/@lostroid  
reddit : https://www.reddit.com/r/LOSTROID  
NaverCafe : https://www.lostroid.com  

# BareMetal  
범용성 제거 루틴 단순화(불필요한 #if)  하기 위해  
 Bare metal 기반을 설계 하는 목적이 있습니다.  
특정 모델 타겟을 가지고 만들기에 범용코드가 아닌 코드를 단순화 시킬 예정입니다.  

# Typedef  
자료형 타입은 다음과 같이 정의 합니다.  
기존 uint32 같은 이름의 충돌을 방지하고자 사용됨.  
float,double, char 그대로 사용합니다.  
```c
typedef unsigned char               tu8;
typedef unsigned short              tu16;
typedef unsigned long               tu32;
typedef unsigned long long          tu64;

typedef signed char                 ts8;
typedef short                       ts16;
typedef long                        ts32;
typedef long long                   ts64;

#define d_NULL  0u
#define d_DONE  0u
#define d_FAIL  1u
#define d_ON    1u 
#define d_OFF   0u  
#define d_ERROR 0xFFFFFFFF
```  
# 코딩 문법  
GIT 의 모든 코드는 아래와 같은 규칙으로 작성이 됩니다.    
  
1. 코딩 스타일: 스네이크 케이스(snake_case) + 혼합 사용 Pascal_Snake_Case
2. 코딩 인코딩: UTF-8  
3. 기본 파일종류: 총 3가지 구성으로 됩니다.  
   xxx_type.h : 타입 enum, typedef, define 다른 타입과 종속 되지 않는 내용 선언  
   xxx.h : 소스 코드의 보든 함수를 목차화 extern 은 다른 소스코드 금지 헤더에 선언, 순수 typdef 가 아닌 여러 type종류 혼합  
   xxx.c : 소스코드  
5. 모든 코드에는 접두어 사용 (아래 참조)
   
```c
/******************************************************************************
* File:    ats_schedluer.c
* Author:  LOSTROID
* Created: 2024-11-10 생성날짜
*
* Description:
* This is the scheduler manager module.
*
* Revision History:
*   2025-05-21  MK  New project.
-------------------------------------------------------------------------------
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
/*
e.g. 예시

x 접두사: 는 extern 변수를 의미.
xa_ : 전역 배열 변수.
xp_ : 전역 포인터 변수.
xpa_ : 전역 포인트 배열 변수.
xs_ : 전역 구조체를 변수.

g 접두사: 는 static 소스코드 글로벌 영역 을 의미.
ga_ : 소스코드 내 배열 변수.
gp_ : 소스코드 내 포인터 변수. (v는 생략가능)
gpa_ : 소스코드 내 포인터 배열 변수.

l 접두사: 함수내 static 변수를 의미.
lv_ : 함수내 비휘발성 변수.
la_ : 함수내 비휘발성 배열 변수.
lp_ : 함수내 비휘발성 포인트 변수.
lpa : 함수내 비휘발성 포인터 배열 변수.

f_ : 함수를 의미 (_첫글자 마다 대문자 표기).
s_ : 구조체 변수를 의미
ts_ : 구조체형 typedef (_첫글자 마다 대문자 표기)
te_ : enum typedef (_첫글자 마다 대문자 표기)
d_ : define 나머지 이름은 대문자로
c_ : 상수
b_ : 비트필드
*/
```
  
최대한 충돌을 피하기 위해 파일 이름의 함수 포함 시켜서 작성합니다.  
  
기본 파일 구성은 다음과 같습니다.   
test_type.h  (순수 Define 또는 타입만 선언)
```c

// 헤더 define 은 다음과 같인 처음과 끝에 헤더의 H로 선언 합니다.
#ifndef H_TEST_TYPE_H
#define H_TEST_TYPE_H

#define d_TEST_SETUP   0
typedef struct //이름은 생략
{
  uint32 v_data1;
  sint32 v_data2;
}ts_Test_Base;

typedef  enum
{
  m_TEST_BASE1,
  m_TEST_BASE2
}te_Test_Base;

typedef struct
{
  te_Test_Base e_test_Base;
  ts_Test_Base s_test_base;
}ts_Test_Ctrol;

#endif
```
test.h ( 다른소스 타입을 사용시에 선언)
```c
#ifndef H_TSET_H
#define H_TEST_H

#include "camera_type.h" /// 또는 Camera.h 함수 사용시 
#include "test_type.h"

typedef struct
{
  ts_Camera_base s_camera_base;
  ts_Test_bsase s_test_base;
}ts_Test_Moulde;

#endif
```

test_type.c
```c
#include "test.h"

uint32 xv_test_flag;          /// extren 변수
uint32 xa_test_array[29];     /// extren 배열 변수

static uint32 gv_test_timer;  /// 소스파일 범위 변수
static uint32 gv_test_state;  /// 소스파일 범위 변수

static sint32* gp_test_point;         /// 소스파일 범위 포인터 변수
static sint32* gpa_test_array[20];    /// 소스파일 범위 포인터 배열 변수

void f_test_int(void)
{
  static uint32 lv_time;  /// 함수 내부는 파일명 접두사를 넣을 필요 없음.
  uint32 v_buff;
{
void f_test_module(void)
{
}

```

코딩 문법룰  
1. #ifdef 같은 헤더 중복은 H_XXXXX_H  앞 뒤로 H 포함 하여 대문자로 작성합니다.  
2. #define 접두어 d소문자 d_XXXXX 나머진 대문자로 사용  
3. const 상수 접두어 c소문자 c_XXXXX  
4. v_value 변수는 상황에 맞게 접두어 사용 소문자로만 사용  
5. typdef struct 및 함수는 f_Aaaa_Aaaa or f_AaaaAaaㅁ 형태로 Pascal_Snake_Case 사용
6. 

xbot_camera.c 인 경우 소스코드 이름을 내부 접두어에 포함 작성합니다.  
이는 서로다른 소스파일의 중복 함수를 피하기 위한 조치입니다.  
f_Xbot_Camera_xxx;   
v_xbot_camera_xxx;
static 변수 파일 이름을 포함 하지 않습니다.
이는 함수의 소스파일 이름을 바로 파악 및 이름 충돌을 피함.  


--- 이하 작성중---
  
추가로 Extren은 원소스 헤더파일에서만 사용 다른 코드에서 사용 불가.  
이는 스파게티 방지.  다른 소스코드 에서 사용 하려면 헤더파일 인클루드  
  
# 파일 주석 및 코드 접두사 사용 
코드를 한눈에 파악하기 위해 다음과 같이 선언 합니다. 

기본 코드 구조
Pbot_app.c
f_PbotApp_Init(void);    //- 초기화
f_PBotApp_Module(void);  //- 


1. CTable (Control Table)

2. STable (Scheduler Table)

# 동작 단위 정의   
#Module    
- Camera   
- LCD  
  
#JOB  
  - 동작에 대한 테이블 변수로 존재 (함수는 없음)  
  - JOB_CAMERA_COLOR : 컬러로 동작 테이블  
  - JOB_CAMERA_BlackWhite : 흑백모드 테이블  
    ```c  
    void (*gap_JOB_Camera_Color[]) (void) = {  
        f_task_camera_enable,  
        f_task_camera_disable,  
        f_task_camera_init,  
        f_task_camera_setup  
    }
    ```    
#TASK  
  - 한가지 동작을 정이  
  - 창문열기 동작.  
    case1. 모터를 정방향으로 가속.  
    case2. 모터 현재 위치 파악.  
    case3. 목표 확인.  
  - 창문닫기 동작.
  
  각 부분을 세분화 하여 Switch 문의 Case로 구분  
  동작을 깔끔하게 보기 위해 함수를 호출 방식으로 권장  
  Case 값을 step으로 지칭  
  ```c  
  Switch(step)  
  {  
      case 0:  
          f_camera_work_en_l();   
          break;   
      case 1:  
          f_camera_work_en_h();  
          break;  
      default:   
          break;   
  }  
  ```
#WORK  
  - 단순 동작 수행 합니다.  
  - f_WindowOpen_Motor_Work_ON() 창문열기 모터 ON  
  - f_WindowsOpen_Motor_Work_Off() 창문열기 모터 OFF  
  - f_WindowsOpen_Moter_Work_Postion_Check() 창문위치 확인
    
  
    
