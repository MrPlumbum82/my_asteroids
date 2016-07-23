#pragma once

#include "tex_particle_sprite.h"

class explosion					// particle system class
{
public:
	float	x;						// X Position
	float	y;						// Y Position
	GLuint tex_id;

	list<particle_sprite> particles;

	explosion(GLuint tex_id, float x, float y);
	void update();
	void draw();

private:
	particle_sprite generateNewParticle();
};

explosion::explosion(GLuint tex_id, float x, float y) : tex_id(tex_id), x(x), y(y)
{
	for (int i = 0; i < 20; i++)
	{
		particles.push_back(generateNewParticle());
	}
}

particle_sprite explosion::generateNewParticle()
{
	float dx = RANDOM() * 8 - 4;
	float dy = RANDOM() * 8 - 4;
	float angle = 0;
	float angularVelocity = 0.1f * RANDOM() * 2 - 1;
	float size = 20;
	int ttl = 8 + rand() % 15;

	return particle_sprite(tex_id, size, size, x, y, dx, dy, angle, angularVelocity, ttl);
}

void explosion::update()
{

	for (list<particle_sprite>::iterator itr = particles.begin(); itr != particles.end(); )
	{
		particle_sprite &p = *itr;
		p.update();
		p.width += 40;
		p.height += 40;
		if (p.ttl <= 0)
			itr = particles.erase(itr);
		else
			itr++;

	} 
}

void explosion::draw()
{
	for (auto &sp : particles)
		sp.draw();
}