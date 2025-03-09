#ifndef READ_MAX30100_H
#define READ_MAX30100_H

#include "MAX30100_PulseOximeter.h"

extern PulseOximeter pox;  // ใช้ extern เพื่อลดการประกาศซ้ำ
extern int heartRate;
extern float spO2;
extern unsigned long tsLastPrint;
extern int max30100_status;

void initMAX30100();
void updateMAX30100();

#endif
