#include <stdarg.h>
#include "updatestate.h"
#include "topdisplay.h"
#include "topbuffs.h"
#include "mainbuffs.h"
#include "setup.h"

#define VERTEX_SIZE (sizeof(vertex))
#define ANIMATION_RATE (0.4 * M_PI)
#define CHARSPPAGE 570

static char default_text[] =
    {
        "UP/DOWN/TOUCHPAD to scroll. A/TOUCHPAD to select. B to go back. LEFT/RIGHT to navigate pages. START to exit. "};
typedef struct threevec
{
    float x;
    float y;
    float z;
} threevec;
static void topSetMV(threevec *, threevec *, threevec *, threevec *, u16);
static void topDraw(float);
static void drawCanvas();
static void drawtext(char *, float, u8 redraw);
static void drawmaintext();
static void drawmainWrapper(u8 i);

C2D_TextBuf dynamicsBuf, staticBuf;

static threevec startscale = {1.0f, 1.0f, 1.0f};
static threevec firstrans = {0.0f, 115.0f, 0.0f};
static threevec sectrans = {195.0f, 0.0f, 0.0f};
static threevec scaley = {1.0f, 1.667f, 1.0f};
static threevec tabletrans = {0.0f, 30.0f, 170.0f};
static C2D_Text HelpD3sk;
static C2D_Text main_text[2];
static C2D_Text hint_text;
static u8 last_defstate = 0;
static folders *save_folder = NULL;
static headfolders *save_headfolder = NULL;
static u8 page_num = 1;
static char page_buf[10];
static u8 max_pages = 0;
void topSetup()
{
    dynamicsBuf = C2D_TextBufNew(CHARSPPAGE + 15);
    staticBuf = C2D_TextBufNew(9);
    C2D_TextParse(&HelpD3sk, staticBuf, "HelpD3sk");
    C2D_TextOptimize(&HelpD3sk);
}

void topscreenrender(u32 keys, float diff)
{
    static float i = 0;

    drawCanvas();
    if (subfocus != NULL)
    {
        save_headfolder = NULL;
        last_defstate = 0;
        max_pages = ceil(subfocus->text_size / (double)CHARSPPAGE);
        if (subfocus == save_folder)
        {
            if (keys & KEY_RIGHT)
            {
                if (page_num < max_pages)
                {
                    drawmainWrapper(++page_num);
                }
                else
                {
                    drawmainWrapper(page_num);
                }
            }
            else if (keys & KEY_LEFT)
            {
                if (page_num > 1)
                {
                    drawmainWrapper(--page_num);
                }
                else
                {
                    drawmainWrapper(page_num);
                }
            }
            else
            {
                drawmaintext();
            }
        }
        else
        {
            page_num = 1;
            drawmainWrapper(page_num);
            save_folder = subfocus;
        }
    }
    else if (mainfocus != NULL)
    {
        save_folder = NULL;
        last_defstate = 0;
        topDraw(i);
        if (mainfocus == save_headfolder)
        {
            drawtext(mainfocus->text, i, 0);
        }
        else
        {
            drawtext(mainfocus->text, i, 1);
            save_headfolder = mainfocus;
        }
    }
    else
    {
        save_headfolder = NULL;
        save_folder = NULL;
        topDraw(i);
        drawtext(default_text, i, !last_defstate);
        if (last_defstate == 0)
        {
            last_defstate = 1;
        }
    }
    i = fmod(i + ANIMATION_RATE * diff, M_PI * 2);
}

void topSetMV(threevec *scale, threevec *angle, threevec *axis, threevec *translate, u16 numvertices)
{
    Mtx_Identity(&MV);
    if (axis->z)
    {
        Mtx_RotateZ(&MV, angle->z, false);
    }
    if (axis->y)
    {
        Mtx_RotateY(&MV, angle->y, false);
    }
    if (axis->x)
    {
        Mtx_RotateX(&MV, angle->x, false);
    }

    Mtx_Scale(&MV, scale->x, scale->y, scale->z);
    Mtx_Translate(&MV, translate->x, translate->y, translate->z, false);
    C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLoc_modelview, &MV);
    C3D_FVUnifSet(GPU_VERTEX_SHADER, uform_selectset, 0.0f, 0.0f, 0.0f, 0.0f);
    C3D_DrawArrays(GPU_TRIANGLES, 0, numvertices);
}
void topDraw(float i)
{
    threevec angle = {0.0f, 0.0f, 0.0f};
    threevec axis = {0.0f, 0.0f, 0.0f};
    angle.z = 0.0f;
    axis.z = 0.0f;
    angle.x = C3D_AngleFromDegrees(-30.0f);
    axis.x = 1.0f;
    angle.y = i;
    axis.y = 1.0f;
    setBuffs(&legsInfo, &attrInfo, 0, 0);
    topSetMV(&startscale, &angle, &axis, &tabletrans, helplegs_size / VERTEX_SIZE);
    setBuffs(&tableInfo, &attrInfo, 0, 1);
    topSetMV(&startscale, &angle, &axis, &tabletrans, maintable_size / VERTEX_SIZE);
}
static void drawtext(char *text, float i, u8 redraw)
{

    C2D_Prepare();
    C2D_DrawText(&HelpD3sk, C2D_AtBaseline | C2D_WithColor | C2D_AlignCenter, 200.0f, 60.0f + 10 * sin(i), 0.5f, 1.75f, 1.75f, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
    if (redraw)
    {
        C2D_TextBufClear(dynamicsBuf);
        C2D_TextParse(&hint_text, dynamicsBuf, text);
        C2D_TextOptimize(&hint_text);
    }
    C2D_DrawText(&hint_text, C2D_AtBaseline | C2D_WithColor | C2D_AlignCenter | C2D_WordWrap, 200.0f, 208, 0.5f, 0.50f, 0.50f, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f), 370.0f);
    C2D_Flush();
}
static void drawmaintext()
{

    C2D_Prepare();
    C2D_DrawText(&main_text[0], C2D_AtBaseline | C2D_WithColor | C2D_WordWrap, 15, 25, 0.5f, 0.60f, 0.60f, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f), 370.0f);
    C2D_DrawText(&main_text[1], C2D_AtBaseline | C2D_WithColor | C2D_AlignRight, 390, 9, 0.5f, 0.4f, 0.38f, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
    C2D_Flush();
}
static void drawmainWrapper(u8 i)
{

    snprintf(page_buf, sizeof(page_buf), "%d/%d", i, max_pages);
    char *text_page = malloc(CHARSPPAGE * sizeof(char));
    if (text_page == NULL)
    {
        sceneExit();
    }
    memcpy(text_page, subfocus->text + ((page_num - 1) * CHARSPPAGE), CHARSPPAGE * sizeof(char));
    C2D_TextBufClear(dynamicsBuf);
    C2D_TextParse(&main_text[0], dynamicsBuf, text_page);
    C2D_TextParse(&main_text[1], dynamicsBuf, page_buf);
    C2D_TextOptimize(&main_text[0]);
    C2D_TextOptimize(&main_text[1]);
    drawmaintext();
    free(text_page);
}
static void drawCanvas()
{
    threevec angle = {0.0f, 0.0f, 0.0f};
    threevec axis = {0.0f, 0.0f, 0.0f};
    setBuffs(&canvasInfo, &attrInfo, 0, 0);
    sectrans.x *= -1;
    topSetMV(&startscale, &angle, &axis, &sectrans, canvas_size / VERTEX_SIZE);
    sectrans.x *= -1;
    topSetMV(&startscale, &angle, &axis, &sectrans, canvas_size / VERTEX_SIZE);
    angle.z = M_PI / 2;
    axis.z = 1.0f;
    firstrans.y *= -1;
    topSetMV(&scaley, &angle, &axis, &firstrans, canvas_size / VERTEX_SIZE);
    firstrans.y *= -1;
    topSetMV(&scaley, &angle, &axis, &firstrans, canvas_size / VERTEX_SIZE);
}