

#ifndef UPDATESTATE_H
#define UPDATESTATE_H
#include "headers.h"
#include "foldcreation.h"
void updateState(u32, touchPosition);
void sliderout(s16);
void setBuffs(C3D_BufInfo *, C3D_AttrInfo *, u8, u8);
extern void textSet(float, float, char *);

extern folders *subselect;
extern headfolders *headselect;
extern folders *subfocus;
extern headfolders *mainfocus;

#endif