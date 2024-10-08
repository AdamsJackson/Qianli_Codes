#ifndef __BSP_CAN_H__
#define __BSP_CAN_H__



#include "stm32f10x.h"
#include "stm32f10x_can.h"




#define CAN_RX_BUFFER_SIZE 16
#define CAN_TX_BUFFER_SIZE 16
#define CAN_RX_BUFFER_MASK (CAN_RX_BUFFER_SIZE - 1)

#define CAN_TX_BUFFER_MASK (CAN_TX_BUFFER_SIZE - 1)



#define CAN_ID_STD 0
#define CAN_ID_EXT 1
#define CAN_ID_MASK 0
#define CAN_RTR 2
    

    
#endif
