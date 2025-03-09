#ifndef TEST_MAX30100_H
#define TEST_MAX30100_H

#include "MAX30100_PulseOximeter.h"

extern PulseOximeter pox;  // ใช้ extern เพื่อลดการประกาศซ้ำ
extern float heartRate;
extern float spO2;
extern unsigned long tsLastPrint;

void initMAX30100();
void updateMAX30100();

#endif
