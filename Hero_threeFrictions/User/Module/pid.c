#include "main.h"
#include "pid.h"
#include <math.h>
#include "motor_data.h"

//judge the max value !
#define LimitMax(input, max)   \
    {                          \
        if (input > max)       \
        {                      \
            input = max;       \
        }                      \
        else if (input < -max) \
        {                      \
            input = -max;      \
        }                      \
    }

pid_type_def motor_pid[7];   
pid_type_def frictions_pid[3];
		
void PID_Init(pid_type_def *pid, uint8_t mode,const fp32 PID_speed[3],const fp32 PID_angle[3], fp32 max_out, fp32 max_iout)
{
		if (pid == NULL /*|| PID_speed == NULL*/)
		{
			return;
		}	
    
		pid->mode = mode;
		
		//数组赋值
		pid->Kp_speed = PID_speed[0];
		pid->Ki_speed = PID_speed[1];
		pid->Kd_speed = PID_speed[2];
	
		pid->Kp_angle = PID_angle[0];
		pid->Ki_angle = PID_angle[1];
		pid->Kd_angle = PID_angle[2];
		
		pid->max_out = max_out;
		pid->max_iout = max_iout;
		pid->Dbuf[0] = pid->Dbuf[1] = pid->Dbuf[2] = 0.0f;
		pid->error[0] = pid->error[1] = pid->error[2] = pid->Pout = pid->Iout = pid->Dout = pid->out = 0.0f; //0处理为了清除数据
}   

fp32 PID_Calc(pid_type_def *pid, fp32 ref, fp32 set) {
    if (pid == NULL) {
        return 0.0f;
    }
    pid->error[2] = pid->error[1];
    pid->error[1] = pid->error[0];
    pid->set = set;
    pid->fdb = ref;
    pid->error[0] = set - ref;  //误差值 ，在6020 如何处理
    if (pid->mode == PID_POSITION) {
        pid->Pout = pid->Kp_speed * pid->error[0];
        pid->Iout += pid->Ki_speed * pid->error[0];
        pid->Dbuf[2] = pid->Dbuf[1];
        pid->Dbuf[1] = pid->Dbuf[0];
        pid->Dbuf[0] = (pid->error[0] - pid->error[1]);
        pid->Dout = pid->Kd_speed * pid->Dbuf[0];
        LimitMax(pid->Iout, pid->max_iout);
        pid->out = pid->Pout + pid->Iout + pid->Dout;
        LimitMax(pid->out, pid->max_out);
    } else if (pid->mode == PID_DELTA) {
        pid->Pout = pid->Kp_speed * (pid->error[0] - pid->error[1]);
        pid->Iout = pid->Ki_speed * pid->error[0];
        pid->Dbuf[2] = pid->Dbuf[1];
        pid->Dbuf[1] = pid->Dbuf[0];
        pid->Dbuf[0] = (pid->error[0] - 2.0f * pid->error[1] + pid->error[2]);
        pid->Dout = pid->Kd_speed * pid->Dbuf[0];
        pid->out += pid->Pout + pid->Iout + pid->Dout;
        LimitMax(pid->out, pid->max_out);
    }
    return pid->out;
}

fp32 PID_CascadeCalc(pid_type_def *pid, fp32 angle_ref, fp32 angle_fdb, fp32 speed_fdb) {
    
    fp32 angle_out = PID_Calc(pid, angle_fdb, angle_ref);
    pid->out = PID_Calc(pid, speed_fdb, angle_out);
	 
		return pid->out;
}

void PID_clear(pid_type_def *pid)
{
    if (pid == NULL)
    {
        return;
    }
    pid->error[0] = pid->error[1] = pid->error[2] = 0.0f; //无处理
    pid->Dbuf[0] = pid->Dbuf[1] = pid->Dbuf[2] = 0.0f;
    pid->out = pid->Pout = pid->Iout = pid->Dout = 0.0f;
    pid->fdb = pid->set = 0.0f;
}
