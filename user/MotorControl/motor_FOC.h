#ifndef __MOTOR_FOC_H__
#define __MOTOR_FOC_H__

#include "global_control.h"
#include <math.h>

typedef struct
{
    float_t Id_ref;    /* D轴电流参考值 */
    float_t Iq_ref;    /* Q轴电流参考值 */
    float_t Speed_ref; /* 电机转速参考值 */
    float_t theta_m;   /* 转子机械角度 */
    float_t theta_e;   /* 转子机械角度 */
    uint8_t Poles;     /* 电机极对数 */
    float_t Udc;       /* 电机供电电压 */
    float_t Tpwm;      /* 电机PWM周期 */
    uint8_t Dir;       /* 电机转动方向 0为正转，1为反转*/
} ExtX;

typedef struct
{
    float_t Tcmp1; /*SVPWM输出U项电流  */
    float_t Tcmp2; /*SVPWM输出V项电流  */
    float_t Tcmp3; /*SVPWM输出W项电流  */

} ExtY;

typedef struct
{
    float_t Vd; /* PI控制器输出d轴电压 */
    float_t Vq; /* PI控制器输出q轴电压 */
} Volatage_DQ_DEF;

typedef struct
{
    float_t Sin; /* 电角度Sin值 */
    float_t Cos; /* 电角度Cos值 */

} Transf_Sin_Cos_DEF;

typedef struct
{
    float_t V_Alpha; /*Revpark变换输出Alpha轴电压  */
    float_t V_Beta;  /*Revpark变换输出Beta轴电压  */
} Volatage_Alpha_Beta_DEF;

typedef struct
{
    float_t Iu; /* 电机U相电流 */
    float_t Iv; /* 电机V相电流 */
    float_t Iw; /* 电机W相电流 */
} Current_UVW_DEF;

typedef struct
{
    float_t Ialpha; /* clark变换输出的alpha电流 */
    float_t Ibeta;  /* clark变换输出的beta电流 */

} Current_Alpha_Beta_DEF;

typedef struct
{
    float_t Id; /* park变换输出的d轴电流 */
    float_t Iq; /* park变换输出的q轴电流 */
} Current_DQ_DEF;

/* 外部额外调用变量 */
extern ExtX rtX;
extern ExtY rtY;

extern Transf_Sin_Cos_DEF Transf_Sin_Cos;           /* 当前电角度的sin cos值 */
extern Volatage_DQ_DEF Volatage_DQ;                 /* 反Park变换输入 */
extern Volatage_Alpha_Beta_DEF Volatage_Alpha_Beta; /* SVPWM输入 */
extern Current_UVW_DEF Current_UVW;                 /* 当前UVW相电流 */
extern Current_Alpha_Beta_DEF Current_Alpha_Beta;   /* Clark变换输出 */
extern Current_DQ_DEF Current_DQ;                   /* Park变换输出 */

/* 外部调用函数 */
void FOC_Init(void);
void FOC_Run(void);
void Angle_To_Sin_Cos(float_t angle, Transf_Sin_Cos_DEF *sin_cos);
void Rev_Park_Transf(Volatage_DQ_DEF v_dq, Transf_Sin_Cos_DEF sin_cos, Volatage_Alpha_Beta_DEF *v_alpha_beta);
void SVPWM_Calc(Volatage_Alpha_Beta_DEF v_alpha_beta, float_t Udc, float_t Tpwm);
void MOTOR_RUN(void);
void Clark_Transf(Current_UVW_DEF I_UVW, Current_Alpha_Beta_DEF *I_Alpha_Beta);
void Park_Transf(Current_Alpha_Beta_DEF I_alpha_beta, Transf_Sin_Cos_DEF sin_cos, Current_DQ_DEF *I_dq);

#endif