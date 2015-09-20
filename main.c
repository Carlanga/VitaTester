#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/moduleinfo.h>
#include <vita2d.h>
#include "font.h"
#include "revitalize.h"

PSP2_MODULE_INFO(0, 0, "VitaButtonTester");

#define SCREEN_W 960
#define SCREEN_H 544

#define EXIT_COMBO (PSP2_CTRL_START | PSP2_CTRL_SELECT)

#define ANALOG_THRESHOLD 100

#define BLACK   RGBA8(  0,   0,   0, 255)
#define WHITE   RGBA8(255, 255, 255, 255)
#define GREEN   RGBA8(  0, 255,   0, 255)
#define RED     RGBA8(255,   0,   0, 255)
#define BLUE    RGBA8(  0,   0, 255, 255)

void show_splash()
{
	vita2d_start_drawing();
	vita2d_clear_screen();

	vita2d_texture *splash = vita2d_create_empty_texture(960, 544);

	splash = vita2d_load_PNG_buffer(revitalize);

	vita2d_draw_texture(splash, 0, 0);

	vita2d_end_drawing();
	vita2d_swap_buffers();

	sceKernelDelayThread(5 * 1000 * 1000); // Delay 5 seconds

	vita2d_free_texture(splash);
}

int main()
{
	vita2d_init();
	vita2d_set_clear_color(BLACK);

	show_splash();

	vita2d_font *font = vita2d_load_font_mem(opensans, opensans_size);

	sceCtrlSetSamplingMode(PSP2_CTRL_MODE_ANALOG_WIDE);

	SceCtrlData pad;

	while (1) {
		sceCtrlPeekBufferPositive(0, &pad, 1);
		if ((pad.buttons & EXIT_COMBO) == EXIT_COMBO) break;

		vita2d_start_drawing();
		vita2d_clear_screen();

		vita2d_font_draw_text(font, 10, 10, WHITE, 25, "VitaButtonTester by SMOKE");
		vita2d_font_draw_text(font, 645, 10, WHITE, 25, "Press Start + Select to exit");
		vita2d_font_draw_text(font, 315, 500, WHITE, 25, "Thanks to xerpi for vita2dlib");
		vita2d_font_draw_text(font, 27, 320, WHITE, 30, "Left analog");
		vita2d_font_draw_text(font, 770, 320, WHITE, 30, "Right analog");

		/* Draw circles to be used for analog input */
		vita2d_draw_fill_circle(100, 450, 80, WHITE);
		vita2d_draw_fill_circle(100, 450, 75, BLACK);
		vita2d_draw_fill_circle(860, 450, 80, WHITE);
		vita2d_draw_fill_circle(860, 450, 75, BLACK);

		/* Used for centering button presses on the screen */
		//vita2d_draw_line(480, 0, 480, 544, RED);
		//vita2d_draw_line(0, 272, 980, 272, RED);

		/* Used for centering analog circles on the screen */
		//vita2d_draw_line(100, 300, 100, 544, RED);
		//vita2d_draw_line(0, 450, 220, 450, RED);
		//vita2d_draw_line(860, 300, 860, 544, RED);
		//vita2d_draw_line(740, 450, 960, 450, RED);

		/* Left analog stick up */
		if (pad.ly < 128 - ANALOG_THRESHOLD) {
			vita2d_draw_fill_circle(100, 380, 30, GREEN);
		}
		/* Left analog stick down */
		if (pad.ly > 128 + ANALOG_THRESHOLD) {
			vita2d_draw_fill_circle(100, 520, 30, GREEN);
		}
		/* Left analog stick left */
		if (pad.lx < 128 - ANALOG_THRESHOLD) {
			vita2d_draw_fill_circle(40, 440, 30, GREEN);
		}
		/* Left analog stick right */
		if (pad.lx > 128 + ANALOG_THRESHOLD) {
			vita2d_draw_fill_circle(160, 460, 30, GREEN);
		}

		/* Right analog stick up */
		if (pad.ry < 128 - ANALOG_THRESHOLD) {
			vita2d_draw_fill_circle(860, 380, 30, GREEN);
		}
		/* Right analog stick down */
		if (pad.ry > 128 + ANALOG_THRESHOLD) {
			vita2d_draw_fill_circle(860, 520, 30, GREEN);
		}
		/* Right analog stick left */
		if (pad.rx < 128 - ANALOG_THRESHOLD) {
			vita2d_draw_fill_circle(790, 450, 30, GREEN);
		}
		/* Right analog stick right */
		if (pad.rx > 128 + ANALOG_THRESHOLD) {
			vita2d_draw_fill_circle(930, 450, 30, GREEN);
		}

		if (pad.buttons & PSP2_CTRL_UP) {
			vita2d_font_draw_text(font, 443, 240, GREEN, 50, "UP");
		}
		else if (pad.buttons & PSP2_CTRL_DOWN) {
			vita2d_font_draw_text(font, 407, 240, GREEN, 50, "DOWN");
		}
		else if (pad.buttons & PSP2_CTRL_LEFT) {
			vita2d_font_draw_text(font, 425, 240, GREEN, 50, "LEFT");
		}
		else if (pad.buttons & PSP2_CTRL_RIGHT) {
			vita2d_font_draw_text(font, 415, 240, GREEN, 50, "RIGHT");
		}
		else if (pad.buttons & PSP2_CTRL_CROSS) {
			vita2d_font_draw_text(font, 400, 240, GREEN, 50, "CROSS");
		}
		else if (pad.buttons & PSP2_CTRL_CIRCLE) {
			vita2d_font_draw_text(font, 400, 240, GREEN, 50, "CIRCLE");
		}
		else if (pad.buttons & PSP2_CTRL_SQUARE) {
			vita2d_font_draw_text(font, 395, 240, GREEN, 50, "SQUARE");
		}
		else if (pad.buttons & PSP2_CTRL_TRIANGLE) {
			vita2d_font_draw_text(font, 373, 240, GREEN, 50, "TRIANGLE");
		}
		else if (pad.buttons & PSP2_CTRL_SELECT) {
			vita2d_font_draw_text(font, 397, 240, GREEN, 50, "SELECT");
		}
		else if (pad.buttons & PSP2_CTRL_START) {
			vita2d_font_draw_text(font, 410, 240, GREEN, 50, "START");
		}
		else if (pad.buttons & PSP2_CTRL_LTRIGGER) {
			vita2d_font_draw_text(font, 375, 240, GREEN, 50, "L-TRIGGER");
		}
		else if (pad.buttons & PSP2_CTRL_RTRIGGER) {
			vita2d_font_draw_text(font, 375, 240, GREEN, 50, "R-TRIGGER");
		}

		vita2d_end_drawing();
		vita2d_swap_buffers();
	}

	//vita2d_free_font(opensans); // Makes graphics freeze or crashes entire vita
	vita2d_fini();

	sceKernelExitProcess(0);
	return 0;
}