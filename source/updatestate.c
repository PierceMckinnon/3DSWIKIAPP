
#include "updatestate.h"
#include "setup.h"
#include "subfolder.h"
#include "mainfolder.h"
#include "foldcreation.h"
#include "textbuffs.h"

#define TOPb_HEIGHT (116.0f)
#define BOTTOMb_HEIGHT (71.0f)
#define MAX_HEIGHT (120.0f)

static float paddleBounds_d(float);
static float padHandleDown(float);
static float paddleBounds_u(float);
static float padHandleUP(float);
static s16 tapFocus(float, float, s16);
static void display(s16);
static s16 checkBounds(s16);
//hold these values throughout
static s16 first = 0; //printf("\x1b[14;10H Focus text is  %d", i);
static float hold = 0;
static u16 penx = 0;
static u16 peny = 0;
static u16 tapx = 0;
static u16 tapy = 0;
static u8 i = 0;
static u8 holdcount = 0;
static float ytemp = 0;
static float save_ytemp = 0;

static float maxtranslate = 0;
static float subtranslate = 0;
headfolders *mainfocus = NULL;
folders *subfocus = NULL;
headfolders *headselect = NULL;

void updateState(u32 keys, touchPosition screen) //printf("\x1b[14;10H Focus text is  %d", i);
{
	if (keys != 0)
	{
		i = 0;
	}
	if (keys & KEY_B)
	{
		if (headselect == NULL)
		{
			mainfocus = NULL;
			ytemp = 0;
			save_ytemp = 0;
		}
		else
		{
			headselect = NULL;
			ytemp = save_ytemp;
		}
		subfocus = NULL;
	}
	else if ((keys & KEY_A) && mainfocus != NULL && headselect == NULL)
	{
		headselect = mainfocus;
		subfocus = headselect->head;
		//mainfocus = NULL;
		save_ytemp = ytemp;
		ytemp = 0;
	}
	else if (keys & KEY_DOWN)
	{
		ytemp = padHandleDown(ytemp);
	}
	else if (keys & KEY_UP)
	{
		ytemp = padHandleUP(ytemp);
	}
	else
	{
		if (i == 0 && (screen.py != 0 || screen.px != 0))
		{
			first = screen.py + hold;
			i = 1;
			holdcount++;
			tapx = screen.px;
			tapy = screen.py;
		}
		else if (i == 1 && ((abs(screen.py - tapy)) < 5) && ((abs(screen.px - tapx)) < 5))
		{
			holdcount++;
		}
		else if (screen.py != 0 || screen.px != 0)
		{
			holdcount = 0;
		}
		ytemp = -screen.py + first;

		if (screen.py == 0 && screen.px == 0)
		{
			ytemp = hold;
			if (i == 1)
			{
				if (holdcount < 20 && holdcount > 0)
				{
					//check if the tap was in bounds, if its a second tap we go into subfolders and reset scroll
					ytemp = tapFocus(penx, peny, ytemp);
				}
			}
			holdcount = 0;
			i = 0;
		}
		//hold for next iteration
		penx = screen.px;
		peny = screen.py;

		//check bounds while scrolling will just return og value if no hits
		ytemp = checkBounds(ytemp);
	}
	hold = ytemp;
	display(ytemp);
}

static s16 tapFocus(float x, float y, s16 ytemp)
{
	x = -160 + (((x - 5) * 320) / 309);
	y = 120 - (((y - 5) * 240) / 229);
	if (headselect != NULL)
	{
		if (subfocus != NULL)
		{
			folders *temp = headselect->head;
			while (temp != NULL)
			{
				if ((x >= temp->x) && (x <= (temp->x + 270)))
				{
					if ((y <= temp->y) && (y >= (temp->y - 45)))
					{
						subfocus = temp;
						return ytemp;
					}
				}
				temp = temp->next;
			}
		}
	}
	else if (kinghead != NULL)
	{

		headfolders *temp = kinghead;
		while (temp != NULL)
		{
			if ((x >= temp->x) && (x <= (temp->x + 270)))
			{
				if ((y <= temp->y) && (y >= (temp->y - 45)))
				{
					if (temp == mainfocus)
					{
						headselect = mainfocus;
						subfocus = headselect->head;
						//mainfocus = NULL;
						save_ytemp = ytemp;
						ytemp = 0;
					}
					else
					{
						mainfocus = temp;
					}
					return ytemp;
				}
			}
			temp = temp->next;
		}
	}
	return 0;
}

static void display(s16 i)
{
	if (headselect != NULL)
	{
		subtranslate = -TOPb_HEIGHT - BOTTOMb_HEIGHT + ((headselect->count) - 1) * 55.0f;
		C3D_FVUnifSet(GPU_VERTEX_SHADER, uform_light, 0.0f, 0.5f, 0.0f, 1.0f);
		subDisplay(i);
	}
	else
	{
		maxtranslate = -TOPb_HEIGHT - BOTTOMb_HEIGHT + (maincount - 1) * 55.0f;
		C3D_FVUnifSet(GPU_VERTEX_SHADER, uform_light, 0.2f, 0.0f, 0.9f, 1.0f);
		mainDisplay(i);
	}
}

void sliderout(s16 i)
{
	float t = 0;
	if (headselect != NULL)
	{
		if (subtranslate == 0)
		{
			t = 0;
		}
		else
		{
			t = i / subtranslate;
		}
	}
	else
	{
		if (maxtranslate == 0)
		{
			t = 0;
		}
		else
		{
			t = i / (maxtranslate);
		}
	}

	setBuffs(&sliderInfo, &attrInfo, 1, 0);
	Mtx_Identity(&MV);
	Mtx_Translate(&MV, -160.0f, -120.0f - t * 150.0f, 0.0f, true);
	C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLoc_modelview, &MV);
	C3D_FVUnifSet(GPU_VERTEX_SHADER, uform_selectset, 0.0f, 0.0f, 0.0f, 0.0f);
	C3D_DrawArrays(GPU_TRIANGLES, 0, 12);

	setBuffs(&limitInfo, &attrInfo, 1, 0);
	Mtx_Identity(&MV);
	Mtx_Translate(&MV, -160.0f, -120.0f, 0.0f, true);
	C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLoc_modelview, &MV);
	C3D_DrawArrays(GPU_TRIANGLES, 0, 12);
}

void setBuffs(C3D_BufInfo *vbo, C3D_AttrInfo *attributes, u8 projflag, u8 textureflag)
{
	C3D_BindProgram(&program);
	C3D_SetAttrInfo(attributes);
	C3D_SetBufInfo(vbo);
	if (projflag)
	{
		Mtx_OrthoTilt(&P, -160.0, 160.0, -120.0, 120.0, 0.0, 1.0, true);
	}
	else
	{
		Mtx_PerspTilt(&P, C3D_AngleFromDegrees(90.0f), 400.0f / 240.0f, 0.01f, 1000.0f, true);
	}
	C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLoc_projection, &P);

	if (textureflag)
	{
		C3D_TexEnv *env = C3D_GetTexEnv(1);
		C3D_TexEnvInit(env);
		C3D_TexEnvSrc(env, C3D_Both, GPU_TEXTURE1, 0, 0);
		C3D_TexEnvFunc(env, C3D_Both, GPU_REPLACE);
	}
	else
	{
		C3D_TexEnv *env = C3D_GetTexEnv(0);
		C3D_TexEnvInit(env);
		C3D_TexEnvSrc(env, C3D_Both, GPU_PRIMARY_COLOR, 0, 0);
		C3D_TexEnvFunc(env, C3D_Both, GPU_REPLACE);
	}
}

void textSet(float x, float y, char *name)
{
	C2D_Text Name_p;
	float left = (x + 160.0f) * (400.0f / 320.0f);
	float top = 240.0f - (y + 120.0f);
	C2D_Prepare();
	C2D_TextBufClear(nameBuf);
	C2D_TextParse(&Name_p, nameBuf, name);
	C2D_TextOptimize(&Name_p);
	C2D_DrawText(&Name_p, C2D_AtBaseline | C2D_WithColor | C2D_AlignCenter | C2D_WordWrap, left + (buttonwidth / 2) * 400.0f / 320.0f, top + buttonheight / 2 + 10.0f, 0.2f, 0.7f, 0.7f, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f), 220.0f);
	C2D_Flush();
}

static s16 checkBounds(s16 ytemp)
{
	//ytemp is the the absolute value moved from the initial height, the top most
	//button shouldn't go down so ytemp shouldnt be less then 0
	if ((ytemp) < 0)
	{
		ytemp = 0.0f;
	}
	else if (headselect != NULL)
	{
		//first check if the amount of initial buttons surpasses the bottom boundary if not ytemp should always be zero
		//if yes check if its gone too far above that bottom boundary
		if ((TOPb_HEIGHT - ((headselect->count) - 1) * 55.0f) < -BOTTOMb_HEIGHT)
		{

			if ((TOPb_HEIGHT + ytemp - ((headselect->count) - 1) * 55.0f) > -BOTTOMb_HEIGHT)
			{
				ytemp = subtranslate;
			}
		}
		else
		{
			ytemp = 0.0f;
		}
	}
	else if (headselect == NULL)
	{

		if ((TOPb_HEIGHT - (maincount - 1) * 55.0f) < BOTTOMb_HEIGHT)
		{

			if ((TOPb_HEIGHT + ytemp - (maincount - 1.0f) * 55.0f) > -BOTTOMb_HEIGHT)
			{
				ytemp = maxtranslate;
			}
		}
		else
		{
			ytemp = 0.0f;
		}
	}
	return ytemp;
}

static float padHandleDown(float padset_d)
{

	if (headselect != NULL)
	{
		if (subfocus != NULL)
		{
			if (subfocus != headselect->tail)
			{
				subfocus = subfocus->next;
			}
			return (padset_d + paddleBounds_d(subfocus->y));
		}
	}
	else if (mainfocus != NULL)
	{
		if (mainfocus != kingtail)
		{
			mainfocus = mainfocus->next;
		}
		return (padset_d + paddleBounds_d(mainfocus->y));
	}
	else
	{
		mainfocus = kinghead;
	}
	return 0.0f;
}

static float paddleBounds_d(float val_d)
{
	if ((val_d) < -BOTTOMb_HEIGHT)
	{
		return (-BOTTOMb_HEIGHT - val_d);
	}
	else if ((val_d + 4.0f) > MAX_HEIGHT)
	{
		return (TOPb_HEIGHT - val_d);
	}
	else
	{
		return 0.0f;
	}
}
static float padHandleUP(float padset_u)
{
	if (headselect != NULL)
	{
		if (subfocus != NULL)
		{
			if (subfocus != headselect->head)
			{
				subfocus = subfocus->prev;
			}
			return (padset_u + paddleBounds_u(subfocus->y));
		}
	}
	else if (mainfocus != NULL)
	{
		if (mainfocus != kinghead)
		{
			mainfocus = mainfocus->prev;
		}
		return (padset_u + paddleBounds_u(mainfocus->y));
	}
	return padset_u;
}
static float paddleBounds_u(float val_u)
{
	if ((val_u) > TOPb_HEIGHT)
	{
		return (TOPb_HEIGHT - val_u);
	}
	else if ((val_u - 49.0f) < -MAX_HEIGHT)
	{
		return (-BOTTOMb_HEIGHT - val_u);
	}
	else
	{
		return 0.0f;
	}
}