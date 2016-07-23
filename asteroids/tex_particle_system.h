#pragma once

#include "tex_particle_sprite.h"
#include "rand.h"
#include <list>
using namespace std;

class particle_system					// particle system class
{
public:
	float	x;						// X Position
	float	y;						// Y Position
	GLuint tex_id;

	list<particle_sprite> particles;

	particle_system(GLuint tex_id, float x, float y) : tex_id(tex_id), x(x), y(y) {}
	void update();
	void draw();

private:
	particle_sprite generateNewParticle();
};

particle_sprite particle_system::generateNewParticle()
{
	float dx = RANDOM() * 2 - 1;
	float dy = RANDOM() * 2 - 1;
	float angle = 0;
	float angularVelocity = 0.1f * RANDOM() * 2 - 1;
	float size = RANDOM() * 5.5f + 1.5f;
	int ttl = 4 + rand() % 8;

	return particle_sprite(tex_id, size, size, x, y, dx, dy, angle, angularVelocity, 4 + rand() % 8);
}

void particle_system::update()
{
	for (int i = 0; i < 4; i++)
	{
		particles.push_back(generateNewParticle());
	}

	for (list<particle_sprite>::iterator itr = particles.begin(); itr != particles.end();)
	{
		particle_sprite &p = *itr;
		p.update();

		if (p.ttl <= 0)
			itr = particles.erase(itr);
		else
			itr++;

	}
}

void particle_system::draw()
{
	for (auto &sp : particles)
		sp.draw();
}