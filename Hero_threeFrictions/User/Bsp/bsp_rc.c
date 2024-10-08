#include "bsp_rc.h"

extern UART_HandleTypeDef huart3;
extern DMA_HandleTypeDef hdma_usart3_rx;

void RC_Init(uint8_t *rxl_buf,uint8_t *rx2_buf,uint16_t dma_buf_num)
{
    //使能dma接口
    SET_BIT(huart3.Instance->CR3, USART_CR3_DMAR);
    //开启空闲中断
    __HAL_UART_ENABLE_IT(&huart3,UART_IT_IDLE);
    //失效DMA
    __HAL_DMA_DISABLE(&hdma_usart3_rx);
    while (hdma_usart3_rx.Instance->CR&DMA_SxCR_EN)
    {
        /* code */
        __HAL_DMA_DISABLE(&hdma_usart3_rx);
    }

    hdma_usart3_rx.Instance->PAR = (uint32_t)&(USART3->DR);
    //memory 1 
    hdma_usart3_rx.Instance->M0AR = (uint32_t)(rxl_buf);
    //memory 2 
    hdma_usart3_rx.Instance->M1AR = (uint32_t)(rx2_buf);
    //data length 
    hdma_usart3_rx.Instance->NDTR = dma_buf_num;
    //enable double memory buffer
    SET_BIT(hdma_usart3_rx.Instance->CR,DMA_SxCR_DBM);
    //enable dma
    __HAL_DMA_ENABLE(&hdma_usart3_rx);

    
}


void RC_unable(void)
{
    __HAL_UART_DISABLE(&huart3);
}

void RC_restart(uint16_t dma_buf_num)
{
    __HAL_UART_DISABLE(&huart3);
    __HAL_DMA_DISABLE(&hdma_usart3_rx);

    hdma_usart3_rx.Instance->NDTR = dma_buf_num;

    __HAL_DMA_ENABLE(&hdma_usart3_rx);
    __HAL_UART_ENABLE(&huart3);

}
