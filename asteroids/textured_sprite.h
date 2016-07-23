#pragma once

#include <math.h>

class textured_sprite						// sprite class
{
  public:
	GLuint tex;
	float width;
	float height;
	float	x;						// X Position
	float	y;						// Y Position
	float	dx;						// X Speed
	float	dy;						// Y Speed
	float rot;                      // rotation
	float drot;                     // rotation speed
	float radius;                   // used for collision detection

	textured_sprite(GLuint tex_id, float width, float height, float x, float y, float dx, float dy, float rot, float drot);
	void update();
	void draw();
	bool intersects(textured_sprite &target);
};

textured_sprite::textured_sprite(GLuint tex_id, float width, float height, float x, float y, float dx, float dy, float rot, float drot)
{
	tex = tex_id;
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	this->dx = dx;
	this->dy = dy;
	this->rot = rot;
	this->drot = drot;

	radius = width / 2;
}

void textured_sprite::update()
{
	x += dx;
	y += dy;
	rot += drot;
}

void textured_sprite::draw()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, tex);
	
	glPushMatrix();

	glTranslatef(x, y, 0);
	glRotatef(rot, 0, 0, 1);
	glScalef(width, height, 1);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 0.1f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 0.1f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.1f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 0.1f);
	glEnd();

	glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

bool textured_sprite::intersects(textured_sprite &target)
{
	return abs(float(x - target.x)) < (radius + target.radius) &&
		abs(y - target.y) < (radius + target.radius);
}
