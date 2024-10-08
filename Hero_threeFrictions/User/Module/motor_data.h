#ifndef __MOTOR_DATA_H__ 
#define __MOTOR_DATA_H__ 

#include "main.h"
//rm motor id
typedef enum
{
		CAN_CHASSIS_ALL_ID = 0x200,
    CAN_3508_M1_ID = 0x201,
    CAN_3508_M2_ID = 0x202,
    CAN_3508_M3_ID = 0x203,
    CAN_3508_M4_ID = 0x204,

		CAN_GIMBAL_ALL_ID = 0x1FF, 
    CAN_YAW_MOTOR_ID = 0x205,
    CAN_PIT_MOTOR_ID = 0x206,
    CAN_TRIGGER_MOTOR_ID = 0x207,
    
}	can_msg_id_e;

//rm motor data
typedef struct
{
    uint16_t ecd;					// Encode count Data
    int16_t speed_rpm;    // 转速 最常见
    int16_t given_current;// 
    uint8_t temperate;    // 温度
    int16_t last_ecd;     // 
} motor_measure_t;  

motor_measure_t *get_chassis_motor_measure_point(uint8_t i);
motor_measure_t *get_gamble_motor_measure_point(uint8_t i);
motor_measure_t *get_friction_motor_measure_point(uint8_t i);


#endif
