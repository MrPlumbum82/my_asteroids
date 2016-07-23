//Sadan Mallhi
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <list>
#include <stdlib.h>
#include "rand.h"
#include "glut.h"
#include "raw.h"
#include "SOIL.h"
#include "tex_aimed_sprite.h"
#include "tex_bounded_sprite.h"
#include "explosion.h"

using namespace std;

// Globals
int width = 800;
int height = 600;
const double pi = 3.14159265358;
int gameOver;
RAWIMG Background;
GLuint shuttle_tex_ID, missile_tex_ID, particle_tex_ID, asteroid_tex_ID;
aimed_sprite *shuttle;
list<aimed_sprite> missiles;
list<bounded_sprite> asteroids;
particle_system *particles;
explosion *explosions;

void writeBitmapString(void *font, char *string)
{
	for (int i = 0; i < strlen(string); i++)
		glutBitmapCharacter(font, string[i]);
}

void init() 
{
	RANDINIT();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);					// Black Background

	glMatrixMode(GL_PROJECTION);						    // Set clipping rectangle and viewport
	glLoadIdentity();									
	gluOrtho2D(0, 800, 0, 600);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_MODELVIEW);						
	glLoadIdentity();

	loadRawImageInv("starsplusearth800x600.raw", 800, 600, Background);

	// particle image
	particle_tex_ID = SOIL_load_OGL_texture(
		"explosion.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_POWER_OF_TWO
		);
	
	// load shuttle image and create textured sprite
	shuttle_tex_ID = SOIL_load_OGL_texture(
		"shuttle2.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_POWER_OF_TWO
		);

	shuttle = new aimed_sprite(shuttle_tex_ID, 50, 45, 400, 300, 0, 0, 0, 0, .4, particle_tex_ID);

	// missile image
	missile_tex_ID = SOIL_load_OGL_texture(
		"missile2.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_POWER_OF_TWO
		);

	// asteroids image
	asteroid_tex_ID = SOIL_load_OGL_texture(
		"asteroid.tga",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_POWER_OF_TWO
		); 

	for (int i = 0; i < 10; i++){
		bounded_sprite asteroid(asteroid_tex_ID, (RANDOM() * 20) + 20, (RANDOM() * 20) + 20, 
			RANDOM() * 800, RANDOM() * 600, (RANDOM() * 4) - 2, (RANDOM() * 4) - 2,
			RANDOM() * 2 * pi, (RANDOM() * 4) - 2, 0, width, 0, height);
		asteroids.push_back(asteroid);
	}

	// explosion object
	explosions = new explosion(particle_tex_ID, shuttle->x, shuttle->y);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);	
}

void idle()
{
	if (gameOver >= 0){
		shuttle->update();

		for (auto& m : missiles)
			m.update();
	}
	
	for (auto& a : asteroids)
		a.update();

	int noCol;
	for (list<aimed_sprite>::iterator itr = missiles.begin(); itr != missiles.end();)
	{
		noCol = 0; //number of collisions
		aimed_sprite &m = *itr;
		for (list<bounded_sprite>::iterator itr2 = asteroids.begin(); itr2 != asteroids.end();)
		{
			bounded_sprite &a = *itr2;
			if (m.intersects(a)){
				itr2 = asteroids.erase(itr2);
				noCol++;
				itr2++;	
			}
			else
				itr2++;
		}
		if (noCol > 0)
			itr = missiles.erase(itr);
		itr++;
	}
	
	glutPostRedisplay();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT); 	
	glColor3f(1, 1, 1);
	glRasterPos2i(0, 0);
	glDrawPixels(800, 600, GL_RGB, GL_UNSIGNED_BYTE, Background.data);

	if (gameOver >= 0){
		shuttle->draw();
		for (auto& m : missiles)
			m.draw();
	}

	for (auto& a : asteroids){
		a.draw();
		if (a.intersects(*shuttle) && gameOver != -1){
			explosions = new explosion(particle_tex_ID, shuttle->x, shuttle->y);
			gameOver = -1;
		}
	}

	// If Player Won
	if (asteroids.empty()){
		gameOver = 1;
	}

	// If Player Lost
	if (gameOver == -1){
		explosions->draw();
		explosions->update();
	}

	if (gameOver != 0){
		glColor3f(1, 1, 0);
		glRasterPos2i(10, 10);
		if (gameOver > 0)
			writeBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Game Over, You Won! ^.^");
		if (gameOver < 0)
			writeBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Game Over, You Lost :(");
	}
	
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case ' ':
		{
				aimed_sprite missile(missile_tex_ID, 12 * 2.5, 12, shuttle->x, shuttle->y,
					4 * cos(shuttle->rot*3.14159 / 180), 4 * sin(shuttle->rot*3.14159 / 180),
					shuttle->rot, 0, 0.4*10, particle_tex_ID);
				missiles.push_back(missile); 
		}
			break;

		case 27:        // When Escape Is Pressed,
			exit(0);    // Exit The Program
			break;
	}
}

void special(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_LEFT:
			shuttle->rot += 2; break;
		case GLUT_KEY_RIGHT:
			shuttle->rot -= 2; break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width,height);
	glutCreateWindow("Asteroids");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutSpecialFunc(special);
	glutKeyboardFunc(keyboard);

	init();

	glutMainLoop();

	return 0;
}
