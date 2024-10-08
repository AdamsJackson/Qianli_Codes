#ifndef __SHOOT_H__ 
#define __SHOOT_H__ 

#include "main.h"
#include "rc.h"
#include "CAN_Receive.h"
#include "pid.h"
#include "motor_data.h"
 
#define HIGH_MODE_Friction   5000 
#define NORMAL_MODE_Friction 4500 
#define LOW_MODE_Friction    4000 

extern void friction_start(void);
extern void friction_shoot(uint32_t mode);

#endif
