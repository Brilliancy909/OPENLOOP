#ifndef __MOTOR_PUBLICDATA_H
#define __MOTOR_PUBLICDATA_H

#include "global_control.h"
#include <stdint.h>

#define LOW_RESITOR      4.7f     // 母线电压检测下端电阻
#define HIGH_RESITOR     100.0f   // 母线电压检测上端电阻
#define SAMPLING_RESITOR 0.05f    // 相电流采样电阻
#define MAGNIFICATION    10.0f    // 采样放大倍数
#define ADC_RESOLUTION   4096.0f  // ADC分辨率
#define ADC_VREF         3.3f     // ADC基准电压
#define PWM_LIMLT        7800     // 限制最大占空比
#define PWM_CYCLE        8500     // PWM周期占空比
#define TS               0.00005f // FOC执行间隔

#define B_VALUE        3434.0f  // B值 (25℃/50℃)3380K  (25℃/85℃)3434K  (25℃/100℃)3455K
#define TEMP_REF       298.15f  // 参考温度值  25℃ + 273.15
#define RESISTOR_REF   10000.0f // 参考温度下的阻值
#define RESISTOR_OTHER 10000.0f // 分压的阻值

#define VBUS_FACTOR          ((ADC_VREF / ADC_RESOLUTION) / (LOW_RESITOR / (LOW_RESITOR + HIGH_RESITOR))) // 母线电压计算系数
#define PHASE_CURRENT_FACTOR ((ADC_VREF / ADC_RESOLUTION) / MAGNIFICATION / SAMPLING_RESITOR)             // 相电流计算系数

/****************参数辨识状态*******************/
#define RESISTANCE_IDENTIFICATION 0X00 // 相电阻识别
#define INDUCTANCE_IDENTIFICATION 0X01 // 相电感识别

/******************运行状态*********************/
#define ADC_CALIB        0X00 // ADC校准
#define MOTOR_STOP       0X01 // 停机
#define MOTOR_ERROR      0X02 // 故障报错
#define MOTOR_IDENTIFY   0X03 // 参数辨识
#define MOTOR_SENSORUSE  0X04 // 有感控制
#define MOTOR_SENSORLESS 0X05 // 无感控制

/****************有感运行模式*******************/
#define ENCODER_CALIB          0X00 // 编码器校准
#define CURRENT_OPEN_LOOP      0X01 // 电流开环
#define CURRENT_CLOSE_LOOP     0X02 // 电流闭环
#define SPEED_CURRENT_LOOP     0X03 // 速度闭环
#define POS_SPEED_CURRENT_LOOP 0X04 // 位置闭环

/****************无感运行模式*******************/
#define STRONG_DRAG_CURRENT_OPEN           0X05 // 电流开环强拖
#define STRONG_DRAG_CURRENT_CLOSE          0X06 // 电流闭环强拖
#define STRONG_DRAG_SMO_SPEED_CURRENT_LOOP 0X07 // 强拖切滑膜速度电流闭环
#define HFI_CURRENT_CLOSE                  0X08 // 电流闭环高频注入（测试HFI角度收敛效果）
#define HFI_SPEED_CURRENT_CLOSE            0X09 // 高频注入速度电流闭环
#define HFI_POS_SPEED_CURRENT_CLOSE        0X0A // 高频注入位置速度电流闭环

#define HALF_PI 1.5707963f
#define PI      3.1415926f
#define TWO_PI  6.2831853f
#define Sqrt_3  1.7320508f

#define CW  0 // 编码器顺时针方向
#define CCW 1 // 编码器逆时针方向

#define ENCODER_LINE 1024                   // 编码器线数
#define PUL_MAX      (4 * ENCODER_LINE - 1) // 单圈脉冲最大值

#define PUL_ANGLE_FACTOR (4095.0f / PUL_MAX) // 角度系数

#define POLEPAIRS    7 // 默认极对数
#define ACCELERATION 3 // 默认加速度

#define SPEED_DIVISION_FACTOR 2 // 速度环分频系数
#define POS_DIVISION_FACTOR   4 // 位置环分频系数

typedef struct
{
    uint8_t RunState; // 运行状态
    uint8_t RunMode;  // 运行模式
} MOTOR_STRUCT;

typedef struct
{
    uint8_t Flag;
    uint8_t State;
    uint8_t EndFlag;     // 辨识完成标志
    uint16_t Count;      // 计数
    uint16_t WaitTim;    // 等待时间
    float Rs;            // 相电阻
    float Ls;            // 相电感
    float Lq;            // q轴电感
    float Ld;            // d轴电感
    float Flux;          // 磁链
    float LsSum;         // 电感累计值
    float CurMax;        // 最大识别电流
    float CurSum;        // 电流累计值
    float CurAverage[2]; // 电流平均值
    float VoltageSet[2]; // 电压给定值
} IDENTIFY_STRUCT;

typedef struct
{
    uint8_t Dir;            // 编码器方向
    uint8_t Type;           // 编码器类型
    uint8_t PolePairs;      // 转子极对数
    int32_t EncoderVal;     // 编码器原始数据
    int32_t EncoderValMax;  // 编码器最大原始值
    int32_t ElectricalVal;  // 电气角度
    uint16_t CalibFlag;     // 校准完成标志
    uint16_t CalibOffset;   // 转子零位偏差
    float ElectricalSpdSet; // 给定的电角速度
    float ElectricalValSet; // 给定的电角度
} ENCODER_STRUCT;

typedef struct
{
    int8_t CurrentDir;   // 电流采样方向
    uint8_t EndFlag;     // 计算完成标志
    uint16_t OffsetCnt;  // 基准值计算次数
    int32_t BusOffset;   // 母线电压基准值
    int32_t IuOffset;    // U相电流偏置值
    int32_t IvOffset;    // V相电流偏置值
    int32_t IwOffset;    // W相电流偏置值
    int32_t BusRaw;      // 母线电压原始值
    int32_t IuRaw;       // U相电流原始值
    int32_t IvRaw;       // V相电流原始值
    int32_t IwRaw;       // W相电流原始值
    float IuReal;        // U相电流真实值
    float IvReal;        // V相电流真实值
    float IwReal;        // W相电流真实值
    float BusReal;       // 母线电压真实值(动态)
    float BusCalibReal;  // 母线电压真实值(校准值，静态)
    float BusChange;     // 母线电压变化值
    float BusFactor;     // 母线电压计算系数
    float CurrentFactor; // 相电流计算系数
    uint16_t AdcBuff[3]; // 用于ADC规则通道接收数据
} SAMPLE_STRUCT;

typedef struct
{
    float Iu;     // U相电流
    float Iv;     // V相电流
    float Iw;     // W相电流
    float Ialpha; // alpha轴电流
    float Ibeta;  // beta轴电流

    float SinVal; // 正弦值
    float CosVal; // 余弦值
    float Id;     // d轴电流
    float Iq;     // q轴电流

    float IdLPF;       // d轴电流滤波值
    float IqLPF;       // q轴电流滤波值
    float IdLPFFactor; // d轴电流滤波系数
    float IqLPFFactor; // q轴电流滤波系数

    float Ud;     // d轴电压
    float Uq;     // q轴电压
    float Ualpha; // alpha轴电压
    float Ubeta;  // beta轴电压
    float Ubus;   // 母线电压

    uint16_t PwmCycle;   // PWM周期
    uint16_t PwmLimit;   // 最大占空比
    uint16_t DutyCycleA; // A相占空比
    uint16_t DutyCycleB; // B相占空比
    uint16_t DutyCycleC; // C相占空比
} FOC_STRUCT;

typedef struct
{
    float Kp;        // 比例系数
    float Ki;        // 积分系数
    float Kd;        // 微分系数
    float Ref;       // 目标值
    float Fbk;       // 反馈值
    float Out;       // 输出值
    float Err;       // 本次误差
    float ErrLast;   // 上次误差
    float AllowErr;  // 允许误差
    float Integrate; // 积分项
    float OutMax;    // 输出上限
    float OutMin;    // 输出下限
    float KpMax;     // 比例系数上限（适用于分段式或模糊PID）
    float KpMin;     // 比例系数下限（适用于分段式或模糊PID）
} PID_STRUCT;

typedef struct
{
    int16_t CurrentSpeedDir;
    uint16_t SpeedCalculateCnt;  // 速度计算计数
    uint16_t ElectricalValMax;   // 电角度最大值
    int32_t ElectricalPosThis;   // 本次电角位置
    int32_t ElectricalPosLast;   // 上次电角位置
    int32_t ElectricalPosChange; // 单位时间位移
    float ElectricalSpeedFactor; // 电角速度系数
    float ElectricalSpeedRaw;    // 原始电角速度

    float ElectricalSpeedLPF;       // 原始电角速度滤波值
    float ElectricalSpeedLPFFactor; // 原始电角速度滤波系数

    float MechanicalSpeed;        // 滤波后机械速度
    float MechanicalSpeedSet;     // 目标机械速度
    float MechanicalSpeedSetLast; // 上次目标机械速度
} SPEED_STRUCT;

typedef struct
{
    float StartSpeed;   // 初始速度
    float EndSpeed;     // 末速度
    float AccSpeed;     // 加速度
    float SumSpeed;     // 速度增量
    float DecSpeed;     // 减速度
    float SpeedOut;     // 输出目标速度
    uint8_t FinishFlag; // 加减速完成标志
} TSHAPEDACCDEC_STRUCT;

typedef struct
{
    uint16_t PosCalculateCnt;    // 位置计算计数
    uint16_t ElectricalValMax;   // 电角度最大值
    int32_t ElectricalPosThis;   // 本次电角位置
    int32_t ElectricalPosLast;   // 上次电角位置
    int32_t ElectricalPosChange; // 单位时间位移
    int32_t ElectricalPosSum;    // 绝对电角位置
    int32_t MechanicalPosRaw;    // 绝对机械位置
    int32_t MechanicalPosSet;    // 目标机械位置
} POSITION_STRUCT;

typedef struct
{
    float Ts;   // 调用周期
    float Rs;   // 相电阻
    float Ld;   // 相电感
    float Gain; // 滑膜观测器增益

    float Ialpha; // α轴实际电流
    float Ibeta;  // β轴实际电流

    float IalphaFore; // α轴预测电流
    float IbetaFore;  // β轴预测电流

    float Ualpha; // α轴实际电压
    float Ubeta;  // β轴实际电压

    float EalphaFore;    // α轴预测反势
    float EalphaForeLPF; // α轴预测反势滤波值

    float EbetaFore;    // β轴预测反势
    float EbetaForeLPF; // β轴预测反势滤波值

    float EabForeLPFFactor; // αβ轴预测反势滤波系数
} SMO_STRUCT;

typedef struct
{
    uint8_t NSDOut;    // 辨识结果输出
    uint8_t NSDFlag;   // 极性辨识标志
    uint16_t NSDCount; // 计数变量
    float NSDSum1;
    float NSDSum2;

    float IdRef;  // 极性辨识时d轴给定
    float IdHigh; // 极性辨识时只用到d轴高频分量

    uint8_t Dir; // 高频注入信号极性
    float Uin;   // 高频注入信号幅值

    float Id;     // 当前d轴电流值
    float IdLast; // 上次d轴电流值
    float IdBase; // d轴基频分量

    float Iq;     // 当前q轴电流值
    float IqLast; // 上次q轴电流值
    float IqBase; // q轴基频分量

    float Ialpha;         // α轴当前值
    float IalphaLast;     // α轴上次值
    float IalphaHigh;     // α轴高频分量
    float IalphaHighLast; // α轴上次高频分量

    float Ibeta;         // β轴当前值
    float IbetaLast;     // β轴上次值
    float IbetaHigh;     // β轴高频分量
    float IbetaHighLast; // β轴上次高频分量

    float IalphaOut; // 电流包络
    float IbetaOut;  // 电流包络
} HFI_STRUCT;

typedef struct
{
    int8_t Dir; // 反电动势计算方向
    float Ts;   // 调用周期

    float Ain; // 输入A
    float Bin; // 输入B

    float ThetaErr;        // 观测角度误差
    float ThetaFore;       // 观测角度 单位：弧度
    float ThetaCompensate; // 补偿后的观测角度 单位：弧度
    float ETheta;          // 补偿后的观测角度 0-3999

    float SinVal; // 正弦值
    float CosVal; // 余弦值

    float Kp;    // 锁相环KP
    float Ki;    // 锁相环KI
    float PPart; // 积分项
    float IPart; // 积分项

    float WeFore;          // 观测电角速度（rad/s）
    float WeForeLPF;       // 观测电角速度滤波值
    float WeForeLPFFactor; // 观测电角速度滤波系数
} PLL_STRUCT;

typedef struct
{
    MOTOR_STRUCT Motor;
    IDENTIFY_STRUCT Identify;
    ENCODER_STRUCT Encoder;
    SAMPLE_STRUCT Sample;
    FOC_STRUCT Foc;
    PID_STRUCT IqPid;
    PID_STRUCT IdPid;
    PID_STRUCT SpdPid;
    PID_STRUCT PosPid;
    SPEED_STRUCT Speed;
    TSHAPEDACCDEC_STRUCT TAccDec;
    POSITION_STRUCT Position;
    SMO_STRUCT SMO;
    HFI_STRUCT HFI;
    PLL_STRUCT SPLL;
    PLL_STRUCT HPLL;
} MOTORCONTROL_STRUCT;

extern MOTORCONTROL_STRUCT MC;
extern MOTOR_STRUCT MOTOR_State;

void Motor_Struct_Init(void);

#endif
