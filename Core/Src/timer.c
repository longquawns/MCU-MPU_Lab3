#include "timer.h"
#include "input_reading.h" // Gọi hàm đọc nút nhấn trong ngắt timer
#include "main.h"

volatile int timer1_counter = 0;
volatile int timer1_flag = 0;

volatile int timer2_counter = 0;
volatile int timer2_flag = 0;

volatile int timer3_counter = 0;
volatile int timer3_flag = 0;

volatile int timer4_counter = 0;
volatile int timer4_flag = 0;

// Chu kỳ ngắt timer phần cứng là 10ms
static const int TIMER_CYCLE = 10;

static int duration_to_ticks(int duration) {
    if (duration <= 0) return 1;
    return (duration + TIMER_CYCLE - 1) / TIMER_CYCLE;
}

void setTimer1(int duration) {
    timer1_counter = duration_to_ticks(duration);
    timer1_flag = 0;
}

void setTimer2(int duration) {
    timer2_counter = duration_to_ticks(duration);
    timer2_flag = 0;
}

void setTimer3(int duration) {
    timer3_counter = duration_to_ticks(duration);
    timer3_flag = 0;
}

void setTimer4(int duration) {
    timer4_counter = duration_to_ticks(duration);
    timer4_flag = 0;
}

void timerRun(void) {
    if(timer1_counter > 0) {
        timer1_counter--;
        if(timer1_counter <= 0) {
            timer1_flag = 1;
        }
    }
    if(timer2_counter > 0) {
        timer2_counter--;
        if(timer2_counter <= 0) {
            timer2_flag = 1;
        }
    }
    if(timer3_counter > 0) {
        timer3_counter--;
        if(timer3_counter <= 0) {
            timer3_flag = 1;
        }
    }
    if(timer4_counter > 0) {
        timer4_counter--;
        if(timer4_counter <= 0) {
            timer4_flag = 1;
        }
    }
}

// Hàm Callback được tự động gọi mỗi 10ms khi Timer 2 tràn
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM2) {
        button_reading(); // Đọc và chống dội nút nhấn
        timerRun();       // Cập nhật các software timer
    }
}
