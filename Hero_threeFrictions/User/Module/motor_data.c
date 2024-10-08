#include "motor_data.h"

motor_measure_t motor_chassis[4];
motor_measure_t motor_gamble[3];
motor_measure_t motor_friction[3];

//获取电机id
motor_measure_t *get_chassis_motor_measure_point(uint8_t i)
{
    return &motor_chassis[i];		
}

motor_measure_t *get_friction_motor_measure_point(uint8_t i)
{
    return &motor_friction[i];		
}

motor_measure_t *get_gamble_motor_measure_point(uint8_t i)
{
    return &motor_gamble[i];		
}
