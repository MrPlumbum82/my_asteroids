#pragma once

#include "textured_sprite.h"

class particle_sprite : public textured_sprite					// particle sprite class
{
public:
	int ttl;   // time to live	

	particle_sprite(GLuint tex_id, float width, float height, float x, float y, float dx, float dy, float rot, float drot,
		int ttl);
	void update();
	void draw();
};

particle_sprite::particle_sprite(GLuint tex_id, float width, float height, float x, float y, float dx, float dy, float rot, float drot,
	int ttl) :
	textured_sprite(tex_id, width, height, x, y, dx, dy, rot, drot)
{
	this->ttl = ttl;
}

void particle_sprite::update()
{
	x += dx;
	y += dy;
	rot += drot;

	ttl--;
}

void particle_sprite::draw()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE); 
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
}
