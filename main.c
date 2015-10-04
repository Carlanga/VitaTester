#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/moduleinfo.h>
#include <vita2d.h>

PSP2_MODULE_INFO(0, 0, "VitaTester");

/* Font buffer */
extern unsigned int basicfont_size;
extern unsigned char basicfont[];

/* Splash screen buffer */
extern unsigned char revitalize[];

/* Image buffers */
extern unsigned char background[];
extern unsigned char ctrl_cross[];
extern unsigned char ctrl_circle[];
extern unsigned char ctrl_square[];
extern unsigned char ctrl_triangle[];
extern unsigned char ctrl_select[];
extern unsigned char ctrl_start[];
extern unsigned char ctrl_ltrigger[];
extern unsigned char ctrl_rtrigger[];
extern unsigned char ctrl_analog[];
extern unsigned char ctrl_dpad[];

#define EXIT_COMBO (PSP2_CTRL_START | PSP2_CTRL_SELECT)

#define BLACK   RGBA8(  0,   0,   0, 255)
#define WHITE   RGBA8(255, 255, 255, 255)
#define GREEN   RGBA8(  0, 255,   0, 255)
#define RED     RGBA8(255,   0,   0, 255)
#define BLUE    RGBA8(  0,   0, 255, 255)

void show_splash()
{
    vita2d_start_drawing();
    vita2d_clear_screen();

    vita2d_texture *splash = vita2d_load_PNG_buffer(revitalize);

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

    vita2d_font *font = vita2d_load_font_mem(basicfont, basicfont_size);

    sceCtrlSetSamplingMode(PSP2_CTRL_MODE_ANALOG_WIDE);

    SceCtrlData pad;

    /* Setup background buffer */
    vita2d_texture *bg = vita2d_load_PNG_buffer(background);

    /* Setup button buffers */
    vita2d_texture *cross = vita2d_load_PNG_buffer(ctrl_cross);
    vita2d_texture *circle = vita2d_load_PNG_buffer(ctrl_circle);
    vita2d_texture *square = vita2d_load_PNG_buffer(ctrl_square);
    vita2d_texture *triangle = vita2d_load_PNG_buffer(ctrl_triangle);
    vita2d_texture *select = vita2d_load_PNG_buffer(ctrl_select);
    vita2d_texture *start = vita2d_load_PNG_buffer(ctrl_start);
    vita2d_texture *ltrigger = vita2d_load_PNG_buffer(ctrl_ltrigger);
    vita2d_texture *rtrigger = vita2d_load_PNG_buffer(ctrl_rtrigger);
    vita2d_texture *analog = vita2d_load_PNG_buffer(ctrl_analog);
    vita2d_texture *dpad = vita2d_load_PNG_buffer(ctrl_dpad);

    while (1) {
        sceCtrlPeekBufferPositive(0, &pad, 1);
        if ((pad.buttons & EXIT_COMBO) == EXIT_COMBO) break;

        vita2d_start_drawing();
        vita2d_clear_screen();

        /* Display background */
        vita2d_draw_texture(bg, 0, 54);

        /* Temporary analog placement until analog measurement is done */
        vita2d_draw_texture(analog, 85, 285);
        vita2d_draw_texture(analog, 800, 285);

        /* Display infos */
        vita2d_font_draw_text(font, 10, 10, WHITE, 25, "VitaTester by SMOKE v1.1 PRE RELEASE");
        vita2d_font_draw_text(font, 650, 10, WHITE, 25, "Press Start + Select to exit");

        if (pad.buttons & PSP2_CTRL_UP) {
            vita2d_draw_texture(dpad, 60, 133);
        }
        if (pad.buttons & PSP2_CTRL_DOWN) {
            vita2d_draw_texture_rotate(dpad, 94, 231, 3.14f);
        }
        if (pad.buttons & PSP2_CTRL_LEFT) {
            vita2d_draw_texture_rotate(dpad, 65, 203, -1.57f);
        }
        if (pad.buttons & PSP2_CTRL_RIGHT) {
            vita2d_draw_texture_rotate(dpad, 123, 203, 1.57f);
        }
        if (pad.buttons & PSP2_CTRL_CROSS) {
            vita2d_draw_texture(cross, 830, 202);
        }
        if (pad.buttons & PSP2_CTRL_CIRCLE) {
            vita2d_draw_texture(circle, 870, 165);
        }
        if (pad.buttons & PSP2_CTRL_SQUARE) {
            vita2d_draw_texture(square, 790, 165);
        }
        if (pad.buttons & PSP2_CTRL_TRIANGLE) {
            vita2d_draw_texture(triangle, 830, 127);
        }
        if (pad.buttons & PSP2_CTRL_SELECT) {
            vita2d_draw_texture(select, 781, 375);
        }
        if (pad.buttons & PSP2_CTRL_START) {
            vita2d_draw_texture(start, 841, 373);
        }
        if (pad.buttons & PSP2_CTRL_LTRIGGER) {
            vita2d_draw_texture(ltrigger, 40, 40);
        }
        if (pad.buttons & PSP2_CTRL_RTRIGGER) {
            vita2d_draw_texture(rtrigger, 720, 40);
        }

        vita2d_end_drawing();
        vita2d_swap_buffers();
    }

    vita2d_fini();

    return 0;
}
