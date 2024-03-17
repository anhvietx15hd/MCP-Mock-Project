/**
 * \file            LeHungViet_MockPRJ.c
 * \author          Le Hung VIET (anhvietx15hd@gmail.com)
 * \brief           
 * \version         0.1
 * \date            2024-03-16
 */
#include "KL46_device.h"
#include "KL46_bios.h"

void main(void) {
    Device_UART0_Init(9600);

    BIOS_main();
    

    while (1) {
        // UART0_SendString("Hello\n", 6, 0);
        // Systick_Timer_Delay(200);
    }

    /*Idea
    * Giới hạn số từ trong lệnh
    * Khi bắt được ký tự kết thúc lệnh hay đạt giới hạn lệnh -> diable RX và xử lý lệnh, xử lý xong enble lại
    * Sửa lại code để gen baudrate cao hơn*/
}