#ifndef __CAN_RECEIVE_H__ 
#define __CAN_RECEIVE_H__  

#include "main.h"
#include "motor_data.h"

extern void CAN_cmd_gamble(int16_t yaw, int16_t pitch, int16_t shoot, int16_t rev);
extern void CAN_cmd_chassis(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4);
extern void CAN_cmd_friction(int16_t motor1, int16_t motor2, int16_t motor3);
#endif
