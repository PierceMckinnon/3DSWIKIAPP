#include "mainfolder.h"
#include "setup.h"
#include "updatestate.h"

void mainDisplay(s16 i)
{
	headfolders *temp = kinghead;
	u8 y = 0;

	while (temp != NULL)
	{

		Mtx_Identity(&MV);
		Mtx_Translate(&MV, -150.0f, -120.0f - y * 55.0 + i, 0.0f, true);

		if (temp == mainfocus)
		{
			C3D_FVUnifSet(GPU_VERTEX_SHADER, uform_selectset, 1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			C3D_FVUnifSet(GPU_VERTEX_SHADER, uform_selectset, 0.0f, 0.0f, 0.0f, 0.0f);
		}
		setBuffs(&buttonInfo, &attrInfo, 1, 0);
		C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLoc_modelview, &MV);
		C3D_DrawArrays(GPU_TRIANGLES, 0, 84);

		setBuffs(&backInfo, &attrInfo, 1, 0);
		C3D_FVUnifSet(GPU_VERTEX_SHADER, uform_selectset, 0.0f, 0.0f, 0.0f, 0.0f);
		C3D_DrawArrays(GPU_TRIANGLES, 0, 30);

		temp->x = -120;
		temp->y = 116.0f - y * 55.0 + i;

		textSet(temp->x, temp->y, temp->name);
		temp = temp->next;
		y++;
	}
	sliderout(i);
}