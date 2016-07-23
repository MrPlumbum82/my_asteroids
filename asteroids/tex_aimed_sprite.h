#include "textured_sprite.h"
#include "tex_particle_system.h"

class aimed_sprite : public textured_sprite					// aimed sprite class
{
  public:
	float speed;
	particle_system *particles;

	aimed_sprite(GLuint tex_id, float width, float height, float x, float y, float dx, float dy, float rot, float drot,
		float speed, GLuint particle_tex_id);
	void update();
	void draw();
};

aimed_sprite::aimed_sprite(GLuint tex_id, float width, float height, float x, float y, float dx, float dy, float rot, float drot, 
								float speed, GLuint particle_tex_id) :
								  textured_sprite(tex_id, width, height, x, y, dx, dy, rot, drot)
{
	this->speed = speed;

	particles = new particle_system(particle_tex_id, x, y);
}

void aimed_sprite::update()
{
	dx = speed * cos(rot*3.14159/180); 
	dy = speed * sin(rot*3.14159/180); 
	x += dx;
	y += dy;
	
	float ex = width * cos(rot*3.14159 / 180);
	float ey = width * sin(rot*3.14159 / 180); 

	particles->x = x-ex;
	particles->y = y-ey;
	particles->update();
}

void aimed_sprite::draw()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();

	glTranslatef(x, y, 0);
	glRotatef(rot, 0, 0, 1);
	glScalef(width, height, 1);

	glBindTexture(GL_TEXTURE_2D, tex);
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

	particles->draw();
}
