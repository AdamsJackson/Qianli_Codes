#include "main.h"
#include "shoot.h"

extern pid_type_def frictions_pid[3];     //电机pid
extern motor_measure_t motor_friction[3]; //电机数据
void friction_start(void) {
    for (int i = 0; i < 3; i++) {
        
        const float PID_speed[3] = {1.0f, 0.1f, 0.01f}; 
        const float PID_angle[3] = {0.0f, 0.0f, 0.0f}; 
        
        PID_Init(&frictions_pid[i], PID_POSITION, PID_speed, PID_angle, 100.0f, 50.0f); 
    }
}

void friction_shoot(uint32_t mode){
	fp32 target_speeds[3];
    switch (mode) {
        case 0:  
            target_speeds[0] = NORMAL_MODE_Friction; 
            target_speeds[1] = NORMAL_MODE_Friction; 
            target_speeds[2] = NORMAL_MODE_Friction; 
            break;
			 case 1:  
            target_speeds[0] = HIGH_MODE_Friction;  
            target_speeds[1] = HIGH_MODE_Friction;  
            target_speeds[2] = HIGH_MODE_Friction;  
            break;
        case 2:  
            target_speeds[0] = LOW_MODE_Friction;   
            target_speeds[1] = LOW_MODE_Friction;    
            target_speeds[2] = LOW_MODE_Friction;   
            break;
        default:
            
            return; 
    }

    for (int i = 0; i < 3; i++) {
        motor_friction[i].given_current = target_speeds[i]; 
        frictions_pid[i].out = PID_Calc(&frictions_pid[i], motor_friction[i].speed_rpm, motor_friction[i].given_current); 
    }
		
		CAN_cmd_friction(frictions_pid[0].out,frictions_pid[1].out,frictions_pid[2].out);
}
