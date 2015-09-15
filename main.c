#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <psp2/ctrl.h>
#include <psp2/display.h>
#include <psp2/gxm.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/moduleinfo.h>
#include <psp2/touch.h>
#include <psp2/types.h>
#include <vita2d.h>
#include "font.h"

PSP2_MODULE_INFO(0, 0, "VitaKeyTester");

#define EXIT_COMBO (PSP2_CTRL_START | PSP2_CTRL_SELECT)

#define WHITE	 RGBA8(255, 255, 255, 255)
#define GREEN	 RGBA8( 34, 177,  76, 255)

int main()
{
	vita2d_init();

	int vita2d_font;
	vita2d_font = vita2d_load_font_mem(opensans, opensans_size);

	SceCtrlData pad;

	while (1) {
		sceCtrlPeekBufferPositive(0, &pad, 1);
		if (pad.buttons & EXIT_COMBO) {
			break;
		}

		vita2d_start_drawing();
		vita2d_clear_screen();

		vita2d_font_draw_text(vita2d_font, 10, 10, WHITE, 25, "VitaKeyTester by SMOKE");
		vita2d_font_draw_text(vita2d_font, 642, 10, WHITE, 25, "Press Start + Select to exit");
		vita2d_font_draw_text(vita2d_font, 340, 500, WHITE, 25, "Thanks to xerpi for vita2dlib");

		if (pad.buttons & PSP2_CTRL_UP) {
			vita2d_font_draw_text(vita2d_font, 460, 272, GREEN, 50, "UP");
		}
		else if (pad.buttons & PSP2_CTRL_DOWN) {
			vita2d_font_draw_text(vita2d_font, 423, 272, GREEN, 50, "DOWN");
		}
		else if (pad.buttons & PSP2_CTRL_LEFT) {
			vita2d_font_draw_text(vita2d_font, 425, 272, GREEN, 50, "LEFT");
		}
		else if (pad.buttons & PSP2_CTRL_RIGHT) {
			vita2d_font_draw_text(vita2d_font, 425, 272, GREEN, 50, "RIGHT");
		}
		else if (pad.buttons & PSP2_CTRL_CROSS) {
			vita2d_font_draw_text(vita2d_font, 425, 272, GREEN, 50, "CROSS");
		}
		else if (pad.buttons & PSP2_CTRL_CIRCLE) {
			vita2d_font_draw_text(vita2d_font, 423, 272, GREEN, 50, "CIRCLE");
		}
		else if (pad.buttons & PSP2_CTRL_SQUARE) {
			vita2d_font_draw_text(vita2d_font, 418, 272, GREEN, 50, "SQUARE");
		}
		else if (pad.buttons & PSP2_CTRL_TRIANGLE) {
			vita2d_font_draw_text(vita2d_font, 410, 272, GREEN, 50, "TRIANGLE");
		}
		else if (pad.buttons & PSP2_CTRL_SELECT) {
			vita2d_font_draw_text(vita2d_font, 423, 272, GREEN, 50, "SELECT");
		}
		else if (pad.buttons & PSP2_CTRL_START) {
			vita2d_font_draw_text(vita2d_font, 425, 272, GREEN, 50, "START");
		}
		else if (pad.buttons & PSP2_CTRL_LTRIGGER) {
			vita2d_font_draw_text(vita2d_font, 410, 272, GREEN, 50, "LTRIGGER");
		}
		else if (pad.buttons & PSP2_CTRL_RTRIGGER) {
			vita2d_font_draw_text(vita2d_font, 410, 272, GREEN, 50, "RTRIGGER");
		}

		vita2d_end_drawing();
		vita2d_swap_buffers();
	}

	vita2d_fini();

	sceKernelExitProcess(0);
	return 0;
}