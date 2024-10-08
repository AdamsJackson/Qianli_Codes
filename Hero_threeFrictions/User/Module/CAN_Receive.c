/*  CAN的收发函数，那我们需要对中断回调进行处理  *
    接受电机数据，can发送电机电流               * 
 */
#include "CAN_receive.h"
#include "main.h"
#include "motor_data.h"

//对获取的电机信息进行解码 用于闭环
#define get_motor_measure(ptr, data)                            \
	{                                                             \
 (ptr)->last_ecd = (ptr)->ecd;                                  \
 (ptr)->ecd = (uint16_t)((data)[0] << 8 | (data)[1]);           \
 (ptr)->speed_rpm = (uint16_t)((data)[2] << 8 | (data)[3]);     \
 (ptr)->given_current = (uint16_t)((data)[4] << 8 | (data)[5]); \
 (ptr)->temperate = (data)[6];                                  \
 }

CAN_TxHeaderTypeDef chassis_tx_message;
CAN_TxHeaderTypeDef gamble_tx_message;

uint8_t chassis_can_send_data[8];
uint8_t gamble_can_send_data[8];

extern motor_measure_t motor_chassis[7]; 
//储存电机信息


 
extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;
 
void CAN_cmd_chassis(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4)
{
		chassis_tx_message.StdId = 0X200;    
		chassis_tx_message.IDE = CAN_ID_STD;
		chassis_tx_message.RTR = CAN_RTR_DATA;
		chassis_tx_message.DLC = 0x08;  
	    //位操作
		chassis_can_send_data[0] = (motor1 >> 8)&0xff;
		chassis_can_send_data[1] = (motor1)&0xff;
		chassis_can_send_data[2] = (motor2 >> 8)&0xff;
		chassis_can_send_data[3] = (motor2)&0xff;
		chassis_can_send_data[4] = (motor3 >> 8)&0xff;
		chassis_can_send_data[5] = (motor3)&0xff;
		chassis_can_send_data[6] = (motor4 >> 8)&0xff;
		chassis_can_send_data[7] = (motor4)&0xff;
	
	HAL_CAN_AddTxMessage(&hcan1,&chassis_tx_message,chassis_can_send_data,(uint32_t*)CAN_TX_MAILBOX0);
 }

void CAN_cmd_friction(int16_t motor1, int16_t motor2, int16_t motor3)
{
		chassis_tx_message.StdId = 0X200;    
		chassis_tx_message.IDE = CAN_ID_STD;
		chassis_tx_message.RTR = CAN_RTR_DATA;
		chassis_tx_message.DLC = 0x08;  
	    //位操作
		chassis_can_send_data[0] = (motor1 >> 8)&0xff;
		chassis_can_send_data[1] = (motor1)&0xff;
		chassis_can_send_data[2] = (motor2 >> 8)&0xff;
		chassis_can_send_data[3] = (motor2)&0xff;
		chassis_can_send_data[4] = (motor3 >> 8)&0xff;
		chassis_can_send_data[5] = (motor3)&0xff;
	
	HAL_CAN_AddTxMessage(&hcan1,&chassis_tx_message,chassis_can_send_data,(uint32_t*)CAN_TX_MAILBOX0);
 }
//
 void CAN_cmd_gamble(int16_t yaw, int16_t pitch, int16_t shoot, int16_t rev)
{
		gamble_tx_message.StdId = 0x1FF;   //四个6020 0x1ff & 0x2ff - voltage  
		gamble_tx_message.IDE = CAN_ID_STD;
		gamble_tx_message.RTR = CAN_RTR_DATA;
		gamble_tx_message.DLC = 0x08;  
	
		gamble_can_send_data[0] = (yaw >> 8)&0xff;
		gamble_can_send_data[1] = (yaw)&0xff;
		gamble_can_send_data[2] = (pitch >> 8)&0xff;
		gamble_can_send_data[3] = (pitch)&0xff;
		gamble_can_send_data[4] = (shoot >> 8)&0xff;
		gamble_can_send_data[5] = (shoot)&0xff;
		gamble_can_send_data[6] = (rev >> 8)&0xff;
		gamble_can_send_data[7] = (rev)&0xff;
	
		HAL_CAN_AddTxMessage(&hcan1,&gamble_tx_message,chassis_can_send_data,(uint32_t*)CAN_TX_MAILBOX0);
 }

//了解can通信的中断回掉，接收中断产生的条件是：当发送完成，接收到数据后会进行中断函数的处理。ok那我们就要寻找中断函数，注意邮箱fifo0
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan){
  CAN_RxHeaderTypeDef rx_header;
	uint8_t rx_data[8];
	
	HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO0,&rx_header,rx_data);
	
	switch(rx_header.StdId)
	{
			case CAN_3508_M1_ID:
			
			case CAN_3508_M2_ID:
			
			case CAN_3508_M3_ID:
			
			case CAN_3508_M4_ID:
			
			case CAN_YAW_MOTOR_ID:
				
			case CAN_PIT_MOTOR_ID:
				
			case CAN_TRIGGER_MOTOR_ID:
			{
				static uint8_t i = 0;
				//get motor id 
				i = rx_header.StdId - CAN_3508_M1_ID;
				//解码工作
				get_motor_measure(&motor_chassis[i],rx_data);//根据id分别储存电机数据�?
				break;
			}
			default:
			{
				break;
			}
	}
 
}

