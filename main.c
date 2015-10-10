#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/touch.h>
#include <vita2d.h>

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
extern unsigned char finger_gray[];
extern unsigned char finger_blue[];

SceCtrlData     pad;
SceTouchData    touch;

signed char lx;
signed char ly;
signed char rx;
signed char ry;
int l_Distance;
int r_Distance;
float l_angle;
float r_angle;
int fxTouch;
int fyTouch;
int bxTouch;
int byTouch;

#define lerp(value, from_max, to_max) ((((value*10) * (to_max*10))/(from_max*10))/10)
#define PI 3.14159265

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
}

int main()
{
    vita2d_init();
    vita2d_set_clear_color(BLACK);

    show_splash();

    vita2d_font *font = vita2d_load_font_mem(basicfont, basicfont_size);

    sceCtrlSetSamplingMode(PSP2_CTRL_MODE_ANALOG_WIDE);

    /* Setup image buffers */
    vita2d_texture *bg = vita2d_load_PNG_buffer(background);
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
    vita2d_texture *frontTouch = vita2d_load_PNG_buffer(finger_gray);
    vita2d_texture *backTouch = vita2d_load_PNG_buffer(finger_blue);

    while (1) {
        sceCtrlPeekBufferPositive(0, &pad, 1);

        if (pad.buttons == EXIT_COMBO) {
            break;
        }

        vita2d_start_drawing();
        vita2d_clear_screen();

        /* Display background */
        vita2d_draw_texture(bg, 0, 54);

        /* Display infos */
        vita2d_font_draw_text(font, 10, 10, WHITE, 25, "VitaTester by SMOKE v1.1");
        vita2d_font_draw_text(font, 650, 10, WHITE, 25, "Press Start + Select to exit");

        vita2d_font_draw_textf(font, 10, 500, WHITE, 25, "Left: ( %3d, %3d )", pad.lx, pad.ly);
        vita2d_font_draw_textf(font, 780, 500, WHITE, 25, "Right: ( %3d, %3d )", pad.rx, pad.ry);

        /* Update joystick values */
        lx = (signed char)pad.lx - 128;
        ly = (signed char)pad.ly - 128;
        rx = (signed char)pad.rx - 128;
        ry = (signed char)pad.ry - 128;

        l_Distance = sqrt(pow(abs(lx),2) + pow(abs(ly),2));
        r_Distance = sqrt(pow(abs(rx),2) + pow(abs(ry),2));

        if(abs(lx)>0) {
            l_angle = (atan(abs(ly)/abs(lx)))*(180/PI);
        } else {
            l_angle=90;
        }
        if(abs(rx)>0) {
            r_angle = (atan(abs(ry)/abs(rx)))*(180/PI);
        } else {
            r_angle=90;
        }

        /* Draw and move left analog stick on screen */
        vita2d_draw_texture(analog, (85 + lx / 10), (285 + ly / 10));

        /* Draw and move right analog on screen */
        vita2d_draw_texture(analog, (802 + rx / 10), (285 + ry / 10));

        /* Draw front touch on screen */
        sceTouchPeek(0, &touch, 1);
        if (touch.reportNum > 0) {
            fxTouch = (lerp(touch.report[0].x, 1920, 960) - 50);
            fyTouch = (lerp(touch.report[0].y, 1088, 544) - 56);
            vita2d_draw_texture(frontTouch, fxTouch, fyTouch);
        }

        /* Draw rear touch on screen */
        sceTouchPeek(1, &touch, 1);
        if (touch.reportNum > 0) {
            bxTouch = (lerp(touch.report[0].x, 1920, 890) - 50);
            byTouch = (lerp(touch.report[0].y, 890, 544) - 56);
            vita2d_draw_texture(backTouch, bxTouch, byTouch);
        }

        /* Draw the up directional button if pressed */
        if (pad.buttons & PSP2_CTRL_UP) {
            vita2d_draw_texture(dpad, 60, 133);
        }

        /* Draw the down directional button if pressed */
        if (pad.buttons & PSP2_CTRL_DOWN) {
            vita2d_draw_texture_rotate(dpad, 94, 231, 3.14f);
        }

        /* Draw the left directional button if pressed */
        if (pad.buttons & PSP2_CTRL_LEFT) {
            vita2d_draw_texture_rotate(dpad, 65, 203, -1.57f);
        }

        /* Draw the right directional button if pressed */
        if (pad.buttons & PSP2_CTRL_RIGHT) {
            vita2d_draw_texture_rotate(dpad, 123, 203, 1.57f);
        }

        /* Draw cross button if pressed */
        if (pad.buttons & PSP2_CTRL_CROSS) {
            vita2d_draw_texture(cross, 830, 202);
        }

        /* Draw circle button if pressed */
        if (pad.buttons & PSP2_CTRL_CIRCLE) {
            vita2d_draw_texture(circle, 870, 165);
        }

        /* Draw square button if pressed */
        if (pad.buttons & PSP2_CTRL_SQUARE) {
            vita2d_draw_texture(square, 790, 165);
        }

        /* Draw triangle button if pressed */
        if (pad.buttons & PSP2_CTRL_TRIANGLE) {
            vita2d_draw_texture(triangle, 830, 127);
        }

        /* Draw select button if pressed */
        if (pad.buttons & PSP2_CTRL_SELECT) {
            vita2d_draw_texture(select, 781, 375);
        }

        /* Draw start button if pressed */
        if (pad.buttons & PSP2_CTRL_START) {
            vita2d_draw_texture(start, 841, 373);
        }

        /* Draw left trigger if pressed */
        if (pad.buttons & PSP2_CTRL_LTRIGGER) {
            vita2d_draw_texture(ltrigger, 40, 40);
        }

        /* Draw right trigger if pressed */
        if (pad.buttons & PSP2_CTRL_RTRIGGER) {
            vita2d_draw_texture(rtrigger, 720, 40);
        }

        vita2d_end_drawing();
        vita2d_swap_buffers();
    }

    vita2d_fini();

    vita2d_free_texture(splash);
    vita2d_free_texture(bg);
    vita2d_free_texture(cross);
    vita2d_free_texture(circle);
    vita2d_free_texture(square);
    vita2d_free_texture(triangle);
    vita2d_free_texture(select);
    vita2d_free_texture(start);
    vita2d_free_texture(ltrigger);
    vita2d_free_texture(rtrigger);
    vita2d_free_texture(analog);
    vita2d_free_texture(dpad);
    vita2d_free_texture(frontTouch);
    vita2d_free_texture(backTouch);

    return 0;
}
