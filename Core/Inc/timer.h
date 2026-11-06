#ifndef INC_TIMER_H_
#define INC_TIMER_H_

extern volatile int timer1_flag;
extern volatile int timer2_flag;
extern volatile int timer3_flag;
extern volatile int timer4_flag;

void setTimer1(int duration);
void setTimer2(int duration);
void setTimer3(int duration);
void setTimer4(int duration);
void timerRun(void);

#endif /* INC_TIMER_H_ */
