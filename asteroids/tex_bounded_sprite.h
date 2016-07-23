#include "textured_sprite.h"

class bounded_sprite : public textured_sprite					// bounded sprite class
{
public:
	float xMin, xMax, yMin, yMax;
	

	bounded_sprite(GLuint tex_id, float width, float height, float x, float y, float dx, float dy, float rot, float drot,
		               float xMn, float xMx, float yMn, float yMx);
	void update();
};

bounded_sprite::bounded_sprite(GLuint tex_id, float width, float height, float x, float y, float dx, float dy, float rot, float drot,
	                              float xMn, float xMx, float yMn, float yMx) :
								  textured_sprite(tex_id, width, height, x, y, dx, dy, rot, drot)
{
	xMin = xMn;
	xMax = xMx;
	yMin = yMn;
	yMax = yMx;
}

void bounded_sprite::update()
{
	if (x < xMax && x > xMin && y < yMax && y > yMin)
	{
		x += dx;
		y += dy;
		rot += drot;
	}
	else if (x >= xMax || x <= xMin )
	{
		dx = -dx;
		x += dx;
		rot += drot;
	}
	else if (y >= yMax || y <= yMin){
		dy = -dy;
		y += dy;
		rot += drot;
	}

}