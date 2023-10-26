
#include "primlib.h"
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#define VERTICES 5
#define ANGLE 2

void display(int x1, int y1, int x2, int y2)
{
	gfx_line(x1, y1, x2, y2, RED);
}

int rotate_x(int x, int y)
{
	int displacement = 120;
	int MIDDLE[2] = {gfx_screenWidth() / 2, gfx_screenHeight() / 2 + displacement};
	float c = cos(ANGLE * M_PI / 180.0);
	float s = sin(ANGLE * M_PI / 180.0);
	x = floor((x - MIDDLE[0]) * c - (y - MIDDLE[1]) * s + MIDDLE[0]);

	return x;
}

int rotate_y(int x, int y)
{
	int MIDDLE[2] = {gfx_screenWidth() / 2, gfx_screenHeight() / 2};
	float c = cos(ANGLE * M_PI / 180.0);
	float s = sin(ANGLE * M_PI / 180.0);
	y = floor((x - MIDDLE[0]) * s + (y - MIDDLE[1]) * c + MIDDLE[1]);

	return y;
}

int main(int argc, char* argv[])
{
	if (gfx_init()) {
		exit(3);
	}
	int initial_radius = 100;
	int MIDDLE[2] = {gfx_screenWidth() / 2, gfx_screenHeight() / 2};
	int p_x[VERTICES];
	int p_y[VERTICES];
	p_x[0] = MIDDLE[0];
	p_y[0] = MIDDLE[1] - initial_radius;

	while (0 == 0) {
		for (int i = 1; i < VERTICES; i++) {
			p_x[i] = floor(
				(p_x[0] - MIDDLE[0]) * cos((float)i / VERTICES * 2.0 * M_PI) -
				(p_y[0] - MIDDLE[1]) * sin((float)i / VERTICES * 2.0 * M_PI) +
				MIDDLE[0]);
			p_y[i] = floor(
				(p_x[0] - MIDDLE[0]) * sin((float)i / VERTICES * 2.0 * M_PI) +
				(p_y[0] - MIDDLE[1]) * cos((float)i / VERTICES * 2.0 * M_PI) +
				MIDDLE[1]);
		}
		gfx_filledRect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1,
					   BLACK);
		for (int k = 0; k < VERTICES; k++) {
			if (k < VERTICES - 1) {
				display(p_x[k], p_y[k], p_x[k + 1], p_y[k + 1]);
			}
			else {
				display(p_x[k], p_y[k], p_x[0], p_y[0]);
			}
		}
		int x = p_x[0], y = p_y[0];
		p_x[0] = rotate_x(x, y);
		p_y[0] = rotate_y(x, y);

		gfx_updateScreen();
		SDL_Delay(30);
		if (gfx_pollkey() != -1)
			break;
	}

	gfx_getkey();
	return 0;
}
