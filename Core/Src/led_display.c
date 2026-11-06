#include "led_display.h"
#include "main.h"

int led_buffer_A[2] = {0, 0};
int led_buffer_B[2] = {0, 2}; // Khởi tạo mặc định để hiển thị Mode 2
int index_led = 0;

// Mã Hex cho LED 7 đoạn Anode chung (0 là sáng, 1 là tắt)
const uint8_t seg7[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void display7SEG_A(int num) {
    HAL_GPIO_WritePin(GPIOB, Aa_Pin, (seg7[num] >> 0) & 1);
    HAL_GPIO_WritePin(GPIOB, Ab_Pin, (seg7[num] >> 1) & 1);
    HAL_GPIO_WritePin(GPIOB, Ac_Pin, (seg7[num] >> 2) & 1);
    HAL_GPIO_WritePin(GPIOB, Ad_Pin, (seg7[num] >> 3) & 1);
    HAL_GPIO_WritePin(GPIOB, Ae_Pin, (seg7[num] >> 4) & 1);
    HAL_GPIO_WritePin(GPIOB, Af_Pin, (seg7[num] >> 5) & 1);
    HAL_GPIO_WritePin(GPIOB, Ag_Pin, (seg7[num] >> 6) & 1);
}

void display7SEG_B(int num) {
    HAL_GPIO_WritePin(GPIOB, Ba_Pin, (seg7[num] >> 0) & 1);
    HAL_GPIO_WritePin(GPIOB, Bb_Pin, (seg7[num] >> 1) & 1);
    HAL_GPIO_WritePin(GPIOB, Bc_Pin, (seg7[num] >> 2) & 1);
    HAL_GPIO_WritePin(GPIOB, Bd_Pin, (seg7[num] >> 3) & 1);
    HAL_GPIO_WritePin(GPIOB, Be_Pin, (seg7[num] >> 4) & 1);
    HAL_GPIO_WritePin(GPIOB, Bf_Pin, (seg7[num] >> 5) & 1);
    HAL_GPIO_WritePin(GPIOB, Bg_Pin, (seg7[num] >> 6) & 1);
}

void update7SEG(void) {
    // Quét 2 cặp LED 7 đoạn luân phiên
    if (index_led == 0) {
        HAL_GPIO_WritePin(GPIOA, SEG_A2_Pin | SEG_B2_Pin, GPIO_PIN_SET);   // Tắt cụm 2
        display7SEG_A(led_buffer_A[0]);
        display7SEG_B(led_buffer_B[0]);
        HAL_GPIO_WritePin(GPIOA, SEG_A1_Pin | SEG_B1_Pin, GPIO_PIN_RESET); // Bật cụm 1
        index_led = 1;
    } else {
        HAL_GPIO_WritePin(GPIOA, SEG_A1_Pin | SEG_B1_Pin, GPIO_PIN_SET);   // Tắt cụm 1
        display7SEG_A(led_buffer_A[1]);
        display7SEG_B(led_buffer_B[1]);
        HAL_GPIO_WritePin(GPIOA, SEG_A2_Pin | SEG_B2_Pin, GPIO_PIN_RESET); // Bật cụm 2
        index_led = 0;
    }
}

void clearAllLEDs(void) {
    HAL_GPIO_WritePin(GPIOA, A_RED_Pin|A_AMBER_Pin|A_GREEN_Pin|B_RED_Pin|B_AMBER_Pin|B_GREEN_Pin, GPIO_PIN_SET);
}
