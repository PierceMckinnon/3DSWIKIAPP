
#ifndef MAINBUFFS_H
#define MAINBUFFS_H
#include "headers.h"
typedef struct
{
	float position[3];
	float colour[3];
} vertex;
extern const vertex *sliderref;
extern const vertex *sliderlimitsref;
extern const vertex *mainbuttref;
extern const vertex *tableback;
extern const u16 button_size, bslider_size, tableback_size;
#endif