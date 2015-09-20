#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/moduleinfo.h>
#include <vita2d.h>
#include "font.h"
#include "revitalize.h"

#define SCREEN_W 960
#define SCREEN_H 544

#define EXIT_COMBO (PSP2_CTRL_START | PSP2_CTRL_SELECT)

#define ANALOG_THRESHOLD 100

#define BLACK   RGBA8(  0,   0,   0, 255)
#define WHITE   RGBA8(255, 255, 255, 255)
#define GREEN   RGBA8(  0, 255,   0, 255)
#define RED     RGBA8(255,   0,   0, 255)
#define BLUE    RGBA8(  0,   0, 255, 255)

#endif
