#include "topbuffs.h"

static const char title[] =
	"HelpD3sk";
const char *title_p = title;
const vertex canvas[] =
	{
		{{-5.0f, 120.0f, 120.0f}, {0.5f, 0.67f, 0.85f}},
		{{-5.0f, -120.0f, 120.0f}, {0.5f, 0.67f, 0.85f}},
		{{5.0f, -120.0f, 120.0f}, {0.5f, 0.67f, 0.85f}},

		{{-5.0f, 120.0f, 120.0f}, {0.5f, 0.67f, 0.85f}},
		{{5.0f, 120.0f, 120.0f}, {0.5f, 0.67f, 0.85f}},
		{{5.0f, -120.0f, 120.0f}, {0.5f, 0.67f, 0.85f}},
};
const vertex help_table[] =
	{
		// //top layer of desk
		{{-60.0f, 3.0f, -50.0f}, {1.0f, 0.0f, 0.0f}},
		{{60.0f, 3.0f, -50.0f}, {1.0f, 1.0f, 0.0f}},
		{{-60.0f, 3.0f, 50.0f}, {0.0f, 0.0f, 0.0f}},

		{{60.0f, 3.0f, 50.0f}, {0.0f, 1.0f, 0.0f}},
		{{60.0f, 3.0f, -50.0f}, {1.0f, 1.0f, 0.0f}},
		{{-60.0f, 3.0f, 50.0f}, {0.0f, 0.0f, 0.0f}},

		//bottom layer of desk
		{{-60.0f, -3.0f, -50.0f}, {1.0f, 0.0f, 0.0f}},
		{{60.0f, -3.0f, -50.0f}, {1.0f, 1.0f, 0.0f}},
		{{-60.0f, -3.0f, 50.0f}, {0.0f, 0.0f, 0.0f}},

		{{60.0f, -3.0f, 50.0f}, {0.0f, 1.0f, 0.0f}},
		{{60.0f, -3.0f, -50.0f}, {1.0f, 1.0f, 0.0f}},
		{{-60.0f, -3.0f, 50.0f}, {0.0f, 0.0f, 0.0f}},

		//front connection
		{{-60.0f, -3.0f, -50.0f}, {1.0f, 0.0f, 0.0f}},
		{{60.0f, -3.0f, -50.0f}, {1.0f, 1.0f, 0.0f}},
		{{-60.0f, 3.0f, -50.0f}, {1.0f, 0.0f, 0.0f}},

		{{60.0f, 3.0f, -50.0f}, {1.0f, 1.0f, 0.0f}},
		{{60.0f, -3.0f, -50.0f}, {1.0f, 1.0f, 0.0f}},
		{{-60.0f, 3.0f, -50.0f}, {1.0f, 0.0f, 0.0f}},

		//back connection
		{{-60.0f, -3.0f, 50.0f}, {0.0f, 0.0f, 0.0f}},
		{{60.0f, -3.0f, 50.0f}, {1.0f, 1.0f, 0.0f}},
		{{-60.0f, 3.0f, 50.0f}, {0.0f, 0.0f, 0.0f}},

		{{60.0f, 3.0f, 50.0f}, {0.0f, 1.0f, 0.0f}},
		{{60.0f, -3.0f, 50.0f}, {0.0f, 1.0f, 0.0f}},
		{{-60.0f, 3.0f, 50.0f}, {0.0f, 0.0f, 0.0f}},

		//right side connection
		{{60.0f, -3.0f, 50.0f}, {1.0f, 1.0f, 0.0f}},
		{{60.0f, -3.0f, -50.0f}, {1.0f, 0.0f, 0.0f}},
		{{60.0f, 3.0f, -50.0f}, {1.0f, 0.0f, 0.0f}},

		{{60.0f, 3.0f, 50.0f}, {1.0f, 1.0f, 0.0f}},
		{{60.0f, -3.0f, 50.0f}, {1.0f, 1.0f, 0.0f}},
		{{60.0f, 3.0f, -50.0f}, {1.0f, 0.0f, 0.0f}},

		//left side connection
		{{-60.0f, -3.0f, 50.0f}, {0.0f, 1.0f, 0.0f}},
		{{-60.0f, -3.0f, -50.0f}, {0.0f, 0.0f, 0.0f}},
		{{-60.0f, 3.0f, -50.0f}, {0.0f, 0.0f, 0.0f}},

		{{-60.0f, 3.0f, 50.0f}, {0.0f, 1.0f, 0.0f}},
		{{-60.0f, -3.0f, 50.0f}, {0.0f, 1.0f, 0.0f}},
		{{-60.0f, 3.0f, -50.0f}, {0.0f, 0.0f, 0.0f}},

};
const vertex help_legs[] =
	{
		//front left leg
		{{-55.0f, -3.0f, -45.0f}, {0.21f, 0.09f, 0.07f}},
		{{-51.0f, -64.0f, -45.0f}, {0.21f, 0.09f, 0.07f}},
		{{-55.0f, -64.0f, -45.0f}, {0.21f, 0.09f, 0.07f}},

		{{-55.0f, -3.0f, -45.0f}, {0.21f, 0.09f, 0.07f}},
		{{-51.0f, -3.0f, -45.0f}, {0.21f, 0.09f, 0.07f}},
		{{-51.0f, -64.0f, -45.0f}, {0.21f, 0.09f, 0.07f}},

		{{-55.0f, -3.0f, -41.0f}, {0.21f, 0.09f, 0.07f}},
		{{-51.0f, -64.0f, -41.0f}, {0.21f, 0.09f, 0.07f}},
		{{-55.0f, -64.0f, -41.0f}, {0.21f, 0.09f, 0.07f}},

		{{-55.0f, -3.0f, -41.0f}, {0.21f, 0.09f, 0.07f}},
		{{-51.0f, -3.0f, -41.0f}, {0.21f, 0.09f, 0.07f}},
		{{-51.0f, -64.0f, -41.0f}, {0.21f, 0.09f, 0.07f}},

		{{-55.0f, -3.0f, -45.0f}, {0.21f, 0.09f, 0.07f}},
		{{-55.0f, -3.0f, -41.0f}, {0.21f, 0.09f, 0.07f}},
		{{-55.0f, -64.0f, -41.0f}, {0.21f, 0.09f, 0.07f}},

		{{-55.0f, -64.0f, -45.0f}, {0.21f, 0.09f, 0.07f}},
		{{-55.0f, -64.0f, -41.0f}, {0.21f, 0.09f, 0.07f}},
		{{-55.0f, -3.0f, -45.0f}, {0.21f, 0.09f, 0.07f}},

		{{-51.0f, -3.0f, -45.0f}, {0.21f, 0.09f, 0.07f}},
		{{-51.0f, -3.0f, -41.0f}, {0.21f, 0.09f, 0.07f}},
		{{-51.0f, -64.0f, -41.0f}, {0.21f, 0.09f, 0.07f}},

		{{-51.0f, -64.0f, -45.0f}, {0.21f, 0.09f, 0.07f}},
		{{-51.0f, -64.0f, -41.0f}, {0.21f, 0.09f, 0.07f}},
		{{-51.0f, -3.0f, -45.0f}, {0.21f, 0.09f, 0.07f}},

		//back left leg
		{{-55.0f, -3.0f, 45.0f}, {0.21f, 0.09f, 0.07f}},
		{{-51.0f, -64.0f, 45.0f}, {0.21f, 0.09f, 0.07f}},
		{{-55.0f, -64.0f, 45.0f}, {0.21f, 0.09f, 0.07f}},

		{{-55.0f, -3.0f, 45.0f}, {0.21f, 0.09f, 0.07f}},
		{{-51.0f, -3.0f, 45.0f}, {0.21f, 0.09f, 0.07f}},
		{{-51.0f, -64.0f, 45.0f}, {0.21f, 0.09f, 0.07f}},

		{{-55.0f, -3.0f, 41.0f}, {0.21f, 0.09f, 0.07f}},
		{{-51.0f, -64.0f, 41.0f}, {0.21f, 0.09f, 0.07f}},
		{{-55.0f, -64.0f, 41.0f}, {0.21f, 0.09f, 0.07f}},

		{{-55.0f, -3.0f, 41.0f}, {0.21f, 0.09f, 0.07f}},
		{{-51.0f, -3.0f, 41.0f}, {0.21f, 0.09f, 0.07f}},
		{{-51.0f, -64.0f, 41.0f}, {0.21f, 0.09f, 0.07f}},

		{{-55.0f, -3.0f, 45.0f}, {0.21f, 0.09f, 0.07f}},
		{{-55.0f, -3.0f, 41.0f}, {0.21f, 0.09f, 0.07f}},
		{{-55.0f, -64.0f, 41.0f}, {0.21f, 0.09f, 0.07f}},

		{{-55.0f, -64.0f, 45.0f}, {0.21f, 0.09f, 0.07f}},
		{{-55.0f, -64.0f, 41.0f}, {0.21f, 0.09f, 0.07f}},
		{{-55.0f, -3.0f, 45.0f}, {0.21f, 0.09f, 0.07f}},

		{{-51.0f, -3.0f, 45.0f}, {0.21f, 0.09f, 0.07f}},
		{{-51.0f, -3.0f, 41.0f}, {0.21f, 0.09f, 0.07f}},
		{{-51.0f, -64.0f, 41.0f}, {0.21f, 0.09f, 0.07f}},

		{{-51.0f, -64.0f, 45.0f}, {0.21f, 0.09f, 0.07f}},
		{{-51.0f, -64.0f, 41.0f}, {0.21f, 0.09f, 0.07f}},
		{{-51.0f, -3.0f, 45.0f}, {0.21f, 0.09f, 0.07f}},

		//rightt front leg
		{{55.0f, -3.0f, -45.0f}, {0.21f, 0.09f, 0.07f}},
		{{51.0f, -64.0f, -45.0f}, {0.21f, 0.09f, 0.07f}},
		{{55.0f, -64.0f, -45.0f}, {0.21f, 0.09f, 0.07f}},

		{{55.0f, -3.0f, -45.0f}, {0.21f, 0.09f, 0.07f}},
		{{51.0f, -3.0f, -45.0f}, {0.21f, 0.09f, 0.07f}},
		{{51.0f, -64.0f, -45.0f}, {0.21f, 0.09f, 0.07f}},

		{{55.0f, -3.0f, -41.0f}, {0.21f, 0.09f, 0.07f}},
		{{51.0f, -64.0f, -41.0f}, {0.21f, 0.09f, 0.07f}},
		{{55.0f, -64.0f, -41.0f}, {0.21f, 0.09f, 0.07f}},

		{{55.0f, -3.0f, -41.0f}, {0.21f, 0.09f, 0.07f}},
		{{51.0f, -3.0f, -41.0f}, {0.21f, 0.09f, 0.07f}},
		{{51.0f, -64.0f, -41.0f}, {0.21f, 0.09f, 0.07f}},

		{{55.0f, -3.0f, -45.0f}, {0.21f, 0.09f, 0.07f}},
		{{55.0f, -3.0f, -41.0f}, {0.21f, 0.09f, 0.07f}},
		{{55.0f, -64.0f, -41.0f}, {0.21f, 0.09f, 0.07f}},

		{{55.0f, -64.0f, -45.0f}, {0.21f, 0.09f, 0.07f}},
		{{55.0f, -64.0f, -41.0f}, {0.21f, 0.09f, 0.07f}},
		{{55.0f, -3.0f, -45.0f}, {0.21f, 0.09f, 0.07f}},

		{{51.0f, -3.0f, -45.0f}, {0.21f, 0.09f, 0.07f}},
		{{51.0f, -3.0f, -41.0f}, {0.21f, 0.09f, 0.07f}},
		{{51.0f, -64.0f, -41.0f}, {0.21f, 0.09f, 0.07f}},

		{{51.0f, -64.0f, -45.0f}, {0.21f, 0.09f, 0.07f}},
		{{51.0f, -64.0f, -41.0f}, {0.21f, 0.09f, 0.07f}},
		{{51.0f, -3.0f, -45.0f}, {0.21f, 0.09f, 0.07f}},

		//back right leg
		{{55.0f, -3.0f, 45.0f}, {0.21f, 0.09f, 0.07f}},
		{{51.0f, -64.0f, 45.0f}, {0.21f, 0.09f, 0.07f}},
		{{55.0f, -64.0f, 45.0f}, {0.21f, 0.09f, 0.07f}},

		{{55.0f, -3.0f, 45.0f}, {0.21f, 0.09f, 0.07f}},
		{{51.0f, -3.0f, 45.0f}, {0.21f, 0.09f, 0.07f}},
		{{51.0f, -64.0f, 45.0f}, {0.21f, 0.09f, 0.07f}},

		{{55.0f, -3.0f, 41.0f}, {0.21f, 0.09f, 0.07f}},
		{{51.0f, -64.0f, 41.0f}, {0.21f, 0.09f, 0.07f}},
		{{55.0f, -64.0f, 41.0f}, {0.21f, 0.09f, 0.07f}},

		{{55.0f, -3.0f, 41.0f}, {0.21f, 0.09f, 0.07f}},
		{{51.0f, -3.0f, 41.0f}, {0.21f, 0.09f, 0.07f}},
		{{51.0f, -64.0f, 41.0f}, {0.21f, 0.09f, 0.07f}},

		{{55.0f, -3.0f, 45.0f}, {0.21f, 0.09f, 0.07f}},
		{{55.0f, -3.0f, 41.0f}, {0.21f, 0.09f, 0.07f}},
		{{55.0f, -64.0f, 41.0f}, {0.21f, 0.09f, 0.07f}},

		{{55.0f, -64.0f, 45.0f}, {0.21f, 0.09f, 0.07f}},
		{{55.0f, -64.0f, 41.0f}, {0.21f, 0.09f, 0.07f}},
		{{55.0f, -3.0f, 45.0f}, {0.21f, 0.09f, 0.07f}},

		{{51.0f, -3.0f, 45.0f}, {0.21f, 0.09f, 0.07f}},
		{{51.0f, -3.0f, 41.0f}, {0.21f, 0.09f, 0.07f}},
		{{51.0f, -64.0f, 41.0f}, {0.21f, 0.09f, 0.07f}},

		{{51.0f, -64.0f, 45.0f}, {0.21f, 0.09f, 0.07f}},
		{{51.0f, -64.0f, 41.0f}, {0.21f, 0.09f, 0.07f}},
		{{51.0f, -3.0f, 45.0f}, {0.21f, 0.09f, 0.07f}},

};

const vertex *canvas_p = canvas;
const u16 canvas_size = sizeof(canvas);

const vertex *maintable_p = help_table;
const u16 maintable_size = sizeof(help_table);

const vertex *helplegs_p = help_legs;
const u16 helplegs_size = sizeof(help_legs);