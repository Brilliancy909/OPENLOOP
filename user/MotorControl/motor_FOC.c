#include "motor_FOC.h"
#include "global_control.h"
#include "motor_publicdata.h"

/* 变量定义 */
ExtX rtX;                                    /* 输入结构变量 */
ExtY rtY;                                    /* 输出结构变量 */
Transf_Sin_Cos_DEF Transf_Sin_Cos;           /* 当前电角度的sin cos值 */
Volatage_DQ_DEF Volatage_DQ;                 /* 反Park变换输入 */
Volatage_Alpha_Beta_DEF Volatage_Alpha_Beta; /* SVPWM输入 */

MOTOR_STRUCT MOTOR_State;                  /* 电机状态变量 */
Current_UVW_DEF Current_UVW;               /* 当前UVW相电流 */
Current_Alpha_Beta_DEF Current_Alpha_Beta; /* Clark变换输出 */
Current_DQ_DEF Current_DQ;                 /* Park变换输出 */

/*
 * @brief  
 * @param 
 * @return  
 * @note
 */
float_t theta = 0.0f;

void MOTOR_RUN(void)
{
    /* 软件模拟角度 */
    if (rtX.Dir == 0)
    {
        theta = theta + 0.005f;
    }
    else
    {
        theta = theta - 0.005f;
    }

    if (theta > 2 * PI)
    {
        theta = theta - 2 * PI;
    }
    else if (theta < 0)
    {
        theta = theta + 2 * PI;
    }
    rtX.theta_e = theta;

    /* SVPWM计算 */
    FOC_Run();

    /* PWM数据输出 */

    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, rtY.Tcmp1);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, rtY.Tcmp2);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, rtY.Tcmp3);

    // __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, rtY.Tcmp1);
    // __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, rtY.Tcmp2);
    // __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, rtY.Tcmp3);
}

/**
 * @brief FOC初始化
 * @param  none
 * @note 初始化PI控制器参数
 */
void FOC_Init(void)
{
    rtX.Udc = 24.0f;
    rtX.Tpwm = 5000.0f * 2.0f;
    Volatage_DQ.Vd = 0.0f;
    Volatage_DQ.Vq = 1.0f;
    rtX.Dir = 1;
}

/**
 * @brief FOC控制算法
 * @param none
 * @note 执行FOC控制流程用PI控制器控制电流环
 */
void FOC_Run(void)
{
    Angle_To_Sin_Cos(rtX.theta_e, &Transf_Sin_Cos); /* 计算三角函数 */

    Clark_Transf(Current_UVW, &Current_Alpha_Beta);
    Park_Transf(Current_Alpha_Beta, Transf_Sin_Cos, &Current_DQ);

    Rev_Park_Transf(Volatage_DQ, Transf_Sin_Cos, &Volatage_Alpha_Beta); /* Revpark变换 */
    SVPWM_Calc(Volatage_Alpha_Beta, rtX.Udc, rtX.Tpwm);                 /* SVPWM */
}

/**
 * @brief SIN_COS值计算
 * @param angle 当前电角度
 * @return sin_cos 三角函数结构体
 * @note none
 */
void Angle_To_Sin_Cos(float_t angle, Transf_Sin_Cos_DEF *sin_cos)
{
    sin_cos->Sin = sinf(angle);
    sin_cos->Cos = cosf(angle);
}

/**
 * @brief 反Park变换
 * @param v_dq DQ轴电压
 * @param sin_cos 三角函数结构体
 * @return v_alpha_beta alpha和beta轴电压
 * @note  ：
            v_alpha= Vd*cos - Vq*sin
            v_beta = Vd*sin + Vq*cos
 */
void Rev_Park_Transf(Volatage_DQ_DEF v_dq, Transf_Sin_Cos_DEF sin_cos, Volatage_Alpha_Beta_DEF *v_alpha_beta)
{
    v_alpha_beta->V_Alpha = v_dq.Vd * sin_cos.Cos - v_dq.Vq * sin_cos.Sin;
    v_alpha_beta->V_Beta = v_dq.Vd * sin_cos.Sin + v_dq.Vq * sin_cos.Cos;
}

/**
 * @brief SVPWM计算
 * @param v_Alpha_Beta Alpha轴Beta电压
 * @param Udc 母线电压
 * @param Tpwm 定时器周期
 * @return rtY 输出三相定时器换相值
 * @note 
 */
void SVPWM_Calc(Volatage_Alpha_Beta_DEF v_Alpha_Beta, float Udc, float Tpwm)
{
    int sector = 0; /* 扇区 N */
    float Tx, Ty, T, Ta, Tb, Tc, u_ref1, u_ref2, u_ref3, temp_section, X, Y, Z;
    /* 矢量扇区计算 N=4C+2B=A */
    u_ref1 = v_Alpha_Beta.V_Beta;
    u_ref2 = (Sqrt_3 * v_Alpha_Beta.V_Alpha - v_Alpha_Beta.V_Beta) / 2.0f;
    u_ref3 = -(Sqrt_3 * v_Alpha_Beta.V_Alpha + v_Alpha_Beta.V_Beta) / 2.0f;
    if (u_ref1 > 0.0f)
    {
        sector = 1;
    }

    if (u_ref2 > 0.0f)
    {
        sector = sector + 2;
    }
    if (u_ref3 > 0.0f)
    {
        sector = sector + 4;
    }

    /*计算矢量作用时间  */
    temp_section = Sqrt_3 * Tpwm / Udc;

    X = temp_section * u_ref1;
    Y = -temp_section * u_ref3;
    Z = -temp_section * u_ref2;
    switch (sector)
    {
        case 1:
            Tx = Z;
            Ty = Y;
            break;

        case 2:
            Tx = Y;
            Ty = -X;
            break;

        case 3:
            Tx = -Z;
            Ty = X;
            break;

        case 4:
            Tx = -X;
            Ty = Z;
            break;

        case 5:
            Tx = X;
            Ty = -Y;
            break;

        default:
            Tx = -Y;
            Ty = -Z;
            break;
    }

    /* 过调制 */
    T = Tx + Ty;
    if (T > Tpwm)
    {
        Tx = Tpwm * Tx / T;
        Ty = Tpwm * Ty / T;
    }
    /* 扇区切换时间点*/
    Ta = (Tpwm - Tx - Ty) / 4.0f;
    Tb = Tx / 2.0f + Ta;
    Tc = Ty / 2.0f + Tb;
    switch (sector)
    {
        case 1:
            rtY.Tcmp1 = Tb;
            rtY.Tcmp2 = Ta;
            rtY.Tcmp3 = Tc;
            break;

        case 2:
            rtY.Tcmp1 = Ta;
            rtY.Tcmp2 = Tc;
            rtY.Tcmp3 = Tb;
            break;

        case 3:
            rtY.Tcmp1 = Ta;
            rtY.Tcmp2 = Tb;
            rtY.Tcmp3 = Tc;
            break;

        case 4:
            rtY.Tcmp1 = Tc;
            rtY.Tcmp2 = Tb;
            rtY.Tcmp3 = Ta;
            break;

        case 5:
            rtY.Tcmp1 = Tc;
            rtY.Tcmp2 = Ta;
            rtY.Tcmp3 = Tb;
            break;

        default:
            rtY.Tcmp1 = Tb;
            rtY.Tcmp2 = Tc;
            rtY.Tcmp3 = Ta;
            break;
    }
}

/*
 * @brief   Clark变换
 * @param   I_UVW三相电流
 * @return  I_Alpha_Beta Alpha和Beta轴电流
 * @note    IAlpha=Iu;
 *          Ibeta=(Iu+2*Iv)*sqrt(3)/3;
 */
void Clark_Transf(Current_UVW_DEF I_UVW, Current_Alpha_Beta_DEF *I_Alpha_Beta)
{
    I_Alpha_Beta->Ialpha = I_UVW.Iu;
    I_Alpha_Beta->Ibeta = (I_UVW.Iu + 2.0f * I_UVW.Iv) * 0.577350269f;
}

/*
 * @brief   Park变换
 * @param   I_alpha_beta alpha、beta轴电流；sin_cos 电角度sin值和cos值
 * @return  I_dq D轴和Q轴电流
 * @note    Id= I_alpha*cos(theta)+I_beta*sin(theta);
 *          Iq=-I_alpha*sin(theta)+I_beta*cos(theta);
 */
void Park_Transf(Current_Alpha_Beta_DEF I_alpha_beta, Transf_Sin_Cos_DEF sin_cos, Current_DQ_DEF *I_dq)
{
    I_dq->Id = I_alpha_beta.Ialpha * sin_cos.Cos + I_alpha_beta.Ibeta * sin_cos.Sin;
    I_dq->Iq = -I_alpha_beta.Ialpha * sin_cos.Sin + I_alpha_beta.Ibeta * sin_cos.Cos;
}