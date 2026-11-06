#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_

extern int led_buffer_A[2]; // Lưu giá trị thời gian (trục A)
extern int led_buffer_B[2]; // Lưu giá trị Mode (trục B)

void update7SEG(void);
void clearAllLEDs(void);

#endif /* INC_LED_DISPLAY_H_ */
