
#include "setup.h"
#include "foldcreation.h"
#include "mainbuffs.h"
#include "topbuffs.h"
#include "textbuffs.h"
#include "darkwood_t3x.h"

#define vertex_list_count (sizeof(vertex_list) / sizeof(vertex_list[0]))
static bool loadTextureFromMem(C3D_Tex *, C3D_TexCube *, const void *, size_t);

static DVLB_s *vshader_dvlb;
shaderProgram_s program;
int uLoc_projection, uLoc_modelview, uform_selectset, uform_light;
C3D_Mtx MV;
C3D_Mtx P;
C3D_BufInfo buttonInfo, sliderInfo, limitInfo, backInfo, canvasInfo, tableInfo, legsInfo;
C3D_AttrInfo attrInfo;

static void *BUTTON_DATA, *SLIDER_DATA, *LIMIT_DATA, *TABLEBACK_DATA, *CANVAS_DATA, *TABLE_DATA, *LEGS_DATA;

static C3D_Tex table_tex;

u16 buttonwidth = 270;
u16 buttonheight = 45;
u32 mainsize = 100;
u32 subsize = 400;

static bool loadTextureFromMem(C3D_Tex *tex, C3D_TexCube *cube, const void *data, size_t size)
{
	Tex3DS_Texture t3x = Tex3DS_TextureImport(data, size, tex, cube, false);
	if (!t3x)
		return false;
	Tex3DS_TextureFree(t3x);
	return true;
}

void setupBuffs()
{

	vshader_dvlb = DVLB_ParseFile((u32 *)vshader_shbin, vshader_shbin_size);
	shaderProgramInit(&program);
	shaderProgramSetVsh(&program, &vshader_dvlb->DVLE[0]);

	uLoc_projection = shaderInstanceGetUniformLocation(program.vertexShader, "P");
	uLoc_modelview = shaderInstanceGetUniformLocation(program.vertexShader, "MV");
	uform_selectset = shaderInstanceGetUniformLocation(program.vertexShader, "S");
	uform_light = shaderInstanceGetUniformLocation(program.vertexShader, "L");

	AttrInfo_Init(&attrInfo);
	AttrInfo_AddLoader(&attrInfo, 0, GPU_FLOAT, 3);
	AttrInfo_AddLoader(&attrInfo, 1, GPU_FLOAT, 3);

	SLIDER_DATA = linearAlloc(bslider_size);
	memcpy(SLIDER_DATA, sliderref, bslider_size);
	BufInfo_Init(&sliderInfo);
	BufInfo_Add(&sliderInfo, SLIDER_DATA, sizeof(vertex), 2, 0x10);

	LIMIT_DATA = linearAlloc(bslider_size);
	memcpy(LIMIT_DATA, sliderlimitsref, bslider_size);
	BufInfo_Init(&limitInfo);
	BufInfo_Add(&limitInfo, LIMIT_DATA, sizeof(vertex), 2, 0x10);

	BUTTON_DATA = linearAlloc(button_size);
	memcpy(BUTTON_DATA, mainbuttref, button_size);
	BufInfo_Init(&buttonInfo);
	BufInfo_Add(&buttonInfo, BUTTON_DATA, sizeof(vertex), 2, 0x10);

	TABLEBACK_DATA = linearAlloc(tableback_size);
	memcpy(TABLEBACK_DATA, tableback, tableback_size);
	BufInfo_Init(&backInfo);
	BufInfo_Add(&backInfo, TABLEBACK_DATA, sizeof(vertex), 2, 0x10);

	CANVAS_DATA = linearAlloc(canvas_size);
	memcpy(CANVAS_DATA, canvas_p, canvas_size);
	BufInfo_Init(&canvasInfo);
	BufInfo_Add(&canvasInfo, CANVAS_DATA, sizeof(vertex), 2, 0x10);

	TABLE_DATA = linearAlloc(maintable_size);
	memcpy(TABLE_DATA, maintable_p, maintable_size);
	BufInfo_Init(&tableInfo);
	BufInfo_Add(&tableInfo, TABLE_DATA, sizeof(vertex), 2, 0x10);

	LEGS_DATA = linearAlloc(helplegs_size);
	memcpy(LEGS_DATA, helplegs_p, helplegs_size);
	BufInfo_Init(&legsInfo);
	BufInfo_Add(&legsInfo, LEGS_DATA, sizeof(vertex), 2, 0x10);

	if (!loadTextureFromMem(&table_tex, NULL, darkwood_t3x, darkwood_t3x_size))
		svcBreak(USERBREAK_PANIC);
	//Tex3DS_TextureImport(darkwood_t3x, darkwood_t3x_size, &table_tex, NULL, false);
	C3D_TexSetFilter(&table_tex, GPU_LINEAR, GPU_NEAREST);
	C3D_TexBind(1, &table_tex);
}

void sceneExit()
{

	//freeing linked list
	headfolders *temp = NULL;
	folders *subtemp = NULL;
	folders *kingsub = NULL;
	while (kinghead != NULL)
	{
		kingsub = kinghead->head;
		while (kingsub != NULL)
		{
			subtemp = kingsub;
			kingsub = kingsub->next;
			free(subtemp);
		}
		temp = kinghead;
		kinghead = kinghead->next;
		free(temp);
	}
	free(kinghead);
	free(kingsub);

	//freeing text buffers
	//freeing buffer
	linearFree(BUTTON_DATA);
	linearFree(SLIDER_DATA);
	linearFree(LIMIT_DATA);
	linearFree(TABLEBACK_DATA);
	C3D_TexDelete(&table_tex);

	//freeing shader
	shaderProgramFree(&program);
	DVLB_Free(vshader_dvlb);

	C2D_Fini();
	C3D_Fini();
	gfxExit();
}