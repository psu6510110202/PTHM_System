#ifndef TEST_AD8232_H
#define TEST_AD8232_H

extern int ecgValue ;  // ใช้ extern เพื่อลดการประกาศซ้ำ
extern int loPlusStatus;
extern int loMinusStatus;

void initAD8232();
void readAD8232();

#endif
