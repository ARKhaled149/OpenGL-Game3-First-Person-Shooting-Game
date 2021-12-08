
//////////////////////////////////////  Includes//////////////////////////////////////////////
#include <string.h>
#include<sstream>
#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include <glut.h>
#include <iostream>
using namespace std;
std::string a;
/////////////////////////////////////   GLOBAL VARIABLES    ///////////////////////////////////
float rotAng;
GLboolean hit = false;
GLboolean movingForward1 = true;
GLboolean movingForward2 = true;
GLboolean movingForward3 = true;
GLboolean movingForward4 = true;
GLboolean movingForward5 = true;
GLboolean DronemovingForward1 = true;
GLboolean DronemovingForward2 = true;
GLboolean DronemovingForward3 = true;
GLboolean DronemovingForward4 = true;
GLboolean shoot = false;
GLboolean level1 = false;
GLboolean level2 = false;
GLboolean level3 = false;
GLboolean first = true;
GLboolean between = false;
GLboolean last = false;
GLboolean c = true;
GLboolean upOrDown = true;
GLint turn = 0;
GLfloat eyeX = 100;
GLfloat eyeY = 2;
GLfloat eyeZ = 100;
GLfloat ThirdeyeX = 125;
GLfloat ThirdeyeY = 8;
GLfloat ThirdeyeZ = 125;
GLfloat camXaim = 0;
GLfloat camYaim = 2;
GLfloat camZaim = 0;
GLfloat Xaim = 98;
GLfloat Yaim = 2;
GLfloat Zaim = 98;
GLfloat bulletX = 0;
GLfloat bulletY = 0;
GLfloat bulletZ = 0;
GLfloat CannonRotation = 0;
GLfloat aimCenterX = 0;
GLfloat aimCenterY = 0;
GLfloat aimCenterZ = 0;
GLfloat theta = 0;
GLint i = 0;
GLint R = 0;
GLint G = 1;
GLint L = 1;
GLint PlayerHealth = 100;
GLint PlayerHealth2 = 100;
GLint score = 0;
GLint score2 = 0;
GLint scoreTotal = 0;
GLfloat Cannonbase1[] = { 0.3, 0.3, 0.3 };
GLfloat Cannonbase2[] = { 0.5, 0.5, 0.5 };
GLfloat white[] = { 1,1,1 };
GLfloat black[] = { 0,0,0 };
GLfloat red[] = { 1,0,0 };
GLfloat brown[] = { 1,0.6,0.3 };
GLfloat green[] = { 0,1,0 };
 
GLuint tex;
char title[] = "First Person Shooter";
// Model Variables
Model_3DS model_house;
Model_3DS model_house2;
Model_3DS model_tree;
Model_3DS model_jeep;
Model_3DS model_helicopter;
Model_3DS model_wall;
Model_3DS model_robotEnemy;
Model_3DS model_cannon;
Model_3DS model_drone1;
Model_3DS model_drone2;
Model_3DS model_hulk;

// Textures
GLTexture tex_ground;
GLTexture tex_ground2;
GLTexture tex_sky2;

// Assets Loading Function
void LoadAssets()
{
	// Loading Model files
	model_house.Load("Models/house/house2.3DS");
	model_house2.Load("Models/drone2/ARC170.3DS");
	model_tree.Load("Models/tree/Tree1.3ds");
	model_jeep.Load("Models/jeep1/jeep1.3ds");
	model_helicopter.Load("Models/AH-64.3DS");
	model_wall.Load("Models/wall/wall.3DS");
	model_robotEnemy.Load("Models/Robot.3ds");
	model_cannon.Load("Models/cannon/cannon.3ds");
	model_drone1.Load("Models/Drone-Design/textures/Drone_3ds.3ds");
	model_drone2.Load("Models/Dtone/Dtone.3ds");
	model_hulk.Load("Models/lego+hulk.3ds");

	// Loading texture files
	tex_ground.Load("Textures/ground.bmp");
	tex_ground2.Load("Textures/alps_dn.bmp");
	tex_sky2.Load("Textures/alps_ft.bmp");
	loadBMP(&tex, "Textures/blu-sky-3.bmp", true);
}
///////////////////////////////////////////////////    Printing   /////////////////////////////////////////////////////////////////////////////
void print(int x, int y, const char* string)
{
	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}
//////////////////////////////////////////////////       CAMERA      //////////////////////////////////////////////////////////////////////////
class CameraUpdated {
	GLfloat x;
	GLfloat y;
	GLfloat z;
public:
	CameraUpdated() : x(0), y(2), z(0) {}
	double getx() {
		return (x);
	}
	double gety() {
		return y;
	}
	double getz() {
		return (z);
	}
	void  setx(double k) {
		x = k;
		camXaim = x;
	}
	void  sety(double k) {
		y = k;
		camYaim = y;
	}
	void  setz(double k) {
		z = k;
		camZaim = z;
	}
	void YmovePlus() {
		if (y < 15) {
			y = y + 0.5;
			camYaim += 0.155;
			Yaim += 0.03077;

		}
	}
	void YmoveMinus() {
		if (y > -3)
			y = y - 0.5;
		if (camYaim > -1.5) {
			camYaim -= 0.155;
			Yaim -= 0.03077;
		}
	}
	void moveright() {
		if (z == 0 && x < 200) {
			x += 5;
			camXaim += 5;
			ThirdeyeX = 125 - (50 / (200 / camXaim));
			ThirdeyeZ = 125;
			Xaim += 0.1;
			Zaim = 98;
		}
		else if (x == 200 && z < 200) {
			z += 5;
			camZaim += 5;
			ThirdeyeX = 75;
			ThirdeyeZ -= 1.25;
			Xaim = 102;
			Zaim += 0.1;
		}
		else if (z == 200 && x > 0) {
			x -= 5;
			camXaim -= 5;
			ThirdeyeZ = 75;
			ThirdeyeX += 1.25;
			Xaim -= 0.1;
			Zaim = 102;
		}
		else if (x == 0 && z >= 0) {
			z -= 5;
			camZaim -= 5;
			ThirdeyeX = 125;
			ThirdeyeZ += 1.25;
			Zaim -= 0.1;
			Xaim = 98;
		}
		CannonRotation -= 2.25;

	}
	void moveleft() {
		if (z == 0 && x > 0) {
			x -= 5;
			camXaim -= 5;
			ThirdeyeX += 1.25;
			ThirdeyeZ = 125;
			Xaim -= 0.1;
			Zaim = 98;
		}
		else if (x == 200 && z > 0) {
			z -= 5;
			camZaim -= 5;
			ThirdeyeX = 75;
			ThirdeyeZ += 1.25;
			Xaim = 102;
			Zaim -= 0.1;
		}
		else if (z == 200 && x < 200) {
			x += 5;
			camXaim += 5;
			ThirdeyeX -= 1.25;
			ThirdeyeZ = 75;
			Xaim += 0.1;
			Zaim = 102;
		}
		else if (x == 0 && z < 200) {
			z += 5;
			camZaim += 5;
			ThirdeyeX = 125;
			ThirdeyeZ -= 1.25;
			Xaim = 98;
			Zaim += 0.1;
		}
		CannonRotation += 2.25;
	}
};
CameraUpdated camera2;
//////////////////////////////////      Models bas kslt a8yar mn bullets l models cause it's used a lot  ////////////////////////////////////////
class Bullet {
	double radius;
	GLfloat* color;
	double x;
	double y;
	double z;
	double directionY;
	double directionX;
public:
	Bullet(double r, GLfloat* c, double x, double y, double z) :
		radius(r), color(c), directionY(0.8), directionX(-1.3), x(x), z(z), y(y) {
	}
	float getBulletX() {
		return x;
	}
	float getBulletY() {
		return y;
	}
	float getBulletZ() {
		return z;
	}
	void setBulletX(GLfloat k) {
		x = k;
	}
	void setBulletY(GLfloat k) {
		y = k;
	}
	void setBulletZ(GLfloat k) {
		z = k;
	}
	void updateModel1() {
		if (PlayerHealth > 0 && score < 100) {
			if (x < 95 && z < 95 && movingForward1) {
				x += 0.25;
				z += 0.25;
			}
			if (x == 95 && z == 95) {
				movingForward1 = false;
				if (PlayerHealth > 0) {
					PlayerHealth -= 5;
					if (PlayerHealth > 50) {
						L = 1;
					}
					else if (PlayerHealth <= 50) {
						L = 0;
					}
				}
			}
			if (x > 70 && z > 70 && (!movingForward1)) {
				x -= 0.25;
				z -= 0.25;
			}
			if (x == 70 && z == 70 && (!movingForward1)) {
				movingForward1 = true;
			}
			if (camXaim<10&&camZaim<10&&bulletZ <= z && bulletY > y + 5.5 *radius && bulletY < y + 7 *radius && bulletX <= x && (bulletX - bulletZ <= 0.75|| bulletZ - bulletX <= 0.75)) {
				x = 0;
				z = 0;
				movingForward1 = true;
				score += 50;
			}
		}
		else {
			z = 0;
			x = 0;
			if (PlayerHealth <= 0&&score<100) {
				first = true;
				between = false;
				level1 = false;
				PlayerHealth = 0;
			}
			if (score >= 100&& PlayerHealth>0) {
				first = false;
				level1 = false;
				between = true;
				camXaim = 0;
				camYaim = 2;
				camZaim = 0;
				Xaim = 98;
				Yaim = 2;
				Zaim = 98;
			}
		}
	}
	void updateModel2() {
		
		if (PlayerHealth > 0 && score < 100) {
			if (x > 105 && z < 95 && movingForward2) {
				x -= 0.25;
				z += 0.25;
			}
			if (x == 105 && z == 95) {
				movingForward2 = false;
				if (PlayerHealth > 0) {
					PlayerHealth -= 1;
						if (PlayerHealth > 50) {
							L = 1;
						}
						else if (PlayerHealth <= 50) {
							L = 0;
						}
					else if (PlayerHealth <= 50) {
						L = 0;
					}
				}
			}
			if (x < 130 && z>70 && (!movingForward2)) {
				x += 0.25;
				z -= 0.25;
			}
			if (x == 130 && z == 70 && (!movingForward2)) {
				movingForward2 = true;
			}
			if ( camXaim > 190 && camZaim<10 && bulletZ <= z && bulletX >= x && bulletY > y + 5.5 * radius && bulletY < y + 7 * radius  && (bulletX - bulletZ <= 0.75 || bulletZ - bulletX <= 0.75)) {
				x = 200;
				z = 0;
				movingForward2 = true;
				score += 5;
			}
		}
		else {
			z = 0;
			x = 200;
			if (PlayerHealth <= 0 && score < 100) {
				first = true;
				between = false;
				level1 = false;
				PlayerHealth = 0;

			}
			if (score >= 100 && PlayerHealth > 0) {
				first = false;
				level1 = false;
				between = true;
				camXaim = 0;
				camYaim = 2;
				camZaim = 0;
				Xaim = 98;
				Yaim = 2;
				Zaim = 98;
			}
			
		}
	}
	void updateModel3() {
		if (PlayerHealth > 0 && score < 100) {
			if (x > 105 && z > 105 && movingForward3) {
				x -= 0.25;
				z -= 0.25;
			}
			if (x == 105 && z == 105) {
				movingForward3 = false;
				if (PlayerHealth > 0) {
					PlayerHealth -= 1;
					if (PlayerHealth > 50) {
						L = 1;
					}
					else if (PlayerHealth <= 50) {
						L = 0;
					}
				}
			}
			if (x < 130 && z < 130 && (!movingForward3)) {
				x += 0.25;
				z += 0.25;
			}
			if (x == 130 && z == 130 && (!movingForward3)) {
				movingForward3 = true;
			}
			if (camXaim > 190 && camZaim>190 && bulletZ >= z && bulletX >= x && bulletY > y + 5.5 * radius && bulletY < y + 7 * radius && (bulletX - bulletZ <= 0.75 || bulletZ - bulletX <= 0.75)) {
				z = 200;
				x = 200;
				movingForward3 = true;
				score += 5;
			}
		}
		else {
			z = 200;
			x = 200;
			if (PlayerHealth <= 0 && score < 100) {
				first = true;
				between = false;
				PlayerHealth = 0;
				level1 = false;
			}
			if (score >= 100 && PlayerHealth > 0) {
				first = false;
				level1 = false;
				between = true;
				camXaim = 0;
				camYaim = 2;
				camZaim = 0;
				Xaim = 98;
				Yaim = 2;
				Zaim = 98;
			}
		}
	}
	void updateModel4() {
		if (PlayerHealth > 0 && score < 100) {
			if (x < 95 && z>105 && movingForward4) {
				x += 0.25;
				z -= 0.25;
			}
			if (x == 95 && z == 105) {
				movingForward4 = false;
				if (PlayerHealth > 0) {
					PlayerHealth -= 10;
					if (PlayerHealth > 50) {
						L = 1;
					}
					else if (PlayerHealth <= 50) {
						L = 0;
					}
				}
			}
			if (x > 70 && z < 130 && (!movingForward4)) {
				x -= 0.25;
				z += 0.25;
			}
			if (x == 70 && z == 130 && (!movingForward4)) {
				movingForward4 = true;
			}
			if (camXaim < 10 && camZaim > 190 && bulletZ >= z && bulletX <= x && bulletY > y + 5.5 * radius && bulletY < y + 7 * radius && (bulletX - bulletZ <= 0.75 || bulletZ - bulletX <= 0.75)) {
				x = 0;
				z = 200;
				movingForward4 = true;
				score += 20;
			}
		}
		else {
			z = 200;
			x = 0;
			if (PlayerHealth <= 0 && score < 100) {
				first = true;
				between = false;
				level1 = false;
				PlayerHealth = 0;
			}
			if (score >= 100 && PlayerHealth > 0) {
				first = false;
				level1 = false;
				between = true;
				camXaim = 0;
				camYaim = 2;
				camZaim = 0;
				Xaim = 98;
				Yaim = 2;
				Zaim = 98;
			}
		}
	}
	void updateModel5() {
		if (PlayerHealth > 0 && score < 100) {
			if (z < 92 && movingForward5) {
				z += 0.25;
				/*if (y > 2) {
					y -= 0.05;
				}*/
			}
			if (z == 92) {
				movingForward5 = false;
				if (PlayerHealth > 0) {
					PlayerHealth -= 1;
					if (PlayerHealth > 50) {
						L = 1;
					}
					else if (PlayerHealth <= 50) {
						L = 0;
					}
				}
			}
			if (z > 60 && (!movingForward5)) {
				z -= 0.25;
				/*if (y < 20) {
					y += 0.05;
				}*/
			}
			if (z == 60 && (!movingForward5)) {
				movingForward5 = true;
			}
			if (bulletZ <= z && bulletX >= x -radius && bulletX <= x + 5* radius && bulletY > y - radius && bulletY < y + 5 * radius) {
				z = 0;
				x = 100;
				y = 2;
				movingForward5 = true;
				score += 50;
			}
		}
		else {
			z = 0;
			x = 100;
			y = 20;
			if (PlayerHealth <= 0 && score < 100) {
				first = true;
				between = false;
				level1 = false;
				PlayerHealth = 0;
			}
			if (score >= 100 && PlayerHealth > 0) {
				first = false;
				level1 = false;
				between = true;
				camXaim = 0;
				camYaim = 2;
				camZaim = 0;
				Xaim = 98;
				Yaim = 2;
				Zaim = 98;
			}
		}
	}
	void  updateDrone1() {
		if (PlayerHealth2 >0 && score2<100) {
			if (z < 95 && DronemovingForward1) {
				z += 0.25;
				if (y > 2) {
					/*if (upOrDown) {
						y -= 0.05;
						upOrDown = false;
					}
					else {
						y += 0.01;
						upOrDown = true;
					}*/
					//y -= 0.05;
					theta += 0.1;
					y = 10+10*abs(cos(theta));
					
				}
			}
			if (z == 95) {
				DronemovingForward1 = false;
				if (PlayerHealth2 > 0) {
					PlayerHealth2 -= 1;
					if (PlayerHealth2 > 50) {
						L = 1;
					}
					else if (PlayerHealth2<= 50) {
						L = 0;
					}
				}
			}
			if (z > 60 && (!DronemovingForward1)) {
				z -= 0.25;
				if (y < 20&&y>1) {
					/*if (upOrDown) {
						y += 0.01;
						upOrDown = false;
					}
					else {
						y -= 0.05;
						upOrDown = true;
					}*/
					theta += 0.1;
					y = 10 + 10 *abs( cos(theta));
				}
				
			}
			if (z == 60 && (!DronemovingForward1)) {
				DronemovingForward1 = true;
			}
			if (bulletZ <= z && bulletX >= x-4*radius&& bulletX <= x + 4*radius && bulletY > y+3*radius&& bulletY < y + 5*radius ) {
				z = 0;
				x = 100;
				y = 20;
				DronemovingForward1 = true;
				score2 += 50;
			}
		}
		else {
			z = 0;
			x = 100;
			y = 20;
			if (PlayerHealth2 <= 0 && score2 < 100) {
				first = true;
				level2 = false;
				PlayerHealth2 = 0;
			}
			if (score2 >= 100&& PlayerHealth2>0 ) {
				last = true;
				level2 = false;
				camXaim = 0;
				camYaim = 2;
				camZaim = 0;
				Xaim = 98;
				Yaim = 2;
				Zaim = 98;
			}
		}
	}
	void  updateDrone2() {
		if (PlayerHealth2 > 0 && score2 < 100) {
			if (z > 105 && DronemovingForward2) {
				z -= 0.25;
				if (y > 2) {
					y -= 0.05;
				}
			}
			if (z == 105) {
				DronemovingForward2 = false;
				if (PlayerHealth2 > 0) {
					PlayerHealth2 -= 5;
					if (PlayerHealth2 > 50) {
						L = 1;
					}
					else if (PlayerHealth2 <= 50) {
						L = 0;
					}
				}
			}
			if (z < 140 && (!DronemovingForward2)) {
				z += 0.25;
				if (y < 20) {
					y += 0.05;
				}
			}
			if (z == 140 && (!DronemovingForward2)) {
				DronemovingForward2 = true;
			}
			if (bulletZ >= z && bulletX >= x-4*radius&& bulletX <= x + 4*radius && bulletY > y+3*radius&& bulletY < y + 5*radius ) {
				z = 200;
				x = 100;
				y = 20;
				DronemovingForward2 = true;
				score2 += 5;
			}
		}
		else {
			z = 200;
			x = 100;
			y = 20;
			if (PlayerHealth2 <= 0 && score2 < 100) {
				first = true;
				level2 = false;
				PlayerHealth2 = 0;
			}
			if (score2 >= 100 && PlayerHealth2 > 0) {
				level2 = false;
				last = true;
				camXaim = 0;
				camYaim = 2;
				camZaim = 0;
				Xaim = 98;
				Yaim = 2;
				Zaim = 98;
			}
		}
	}
	void  updateDrone3() {
		if (PlayerHealth2 > 0 && score2 < 100) {
			if (x < 95 && DronemovingForward3) {
				x += 0.25;
				if (y > 2) {
					y -= 0.05;
				}
			}
			if (x == 95) {
				DronemovingForward3 = false;
				if (PlayerHealth2 > 0) {
					PlayerHealth2 -= 1;
					if (PlayerHealth2 > 50) {
						L = 1;
					}
					else if (PlayerHealth2 <= 50) {
						L = 0;
					}
				}
			}
			if (x > 60 && (!DronemovingForward3)) {
				x -= 0.25;
				if (y < 20) {
					y += 0.05;
				}
			}
			if (x == 60 && (!DronemovingForward3)) {
				DronemovingForward3 = true;
			}
			if (bulletX <= x  && bulletZ >= z - 5 * radius && bulletZ <= z + 5 * radius && bulletY > y + 2.5 * radius && bulletY < y + 8 * radius) {
				z = 100;
				x =0;
				y = 20;
				DronemovingForward3 = true;
				score2 += 5;
			}
		}
		else {
			z = 100;
			x = 0;
			y = 20;
			if (PlayerHealth2 <= 0 && score2 < 100) {
				first = true;
				level2 = false;
				PlayerHealth2 = 0;
			}
			if (score2 >= 100 && PlayerHealth2 > 0) {
				level2 = false;
				last = true;
				camXaim = 0;
				camYaim = 2;
				camZaim = 0;
				Xaim = 98;
				Yaim = 2;
				Zaim = 98;
			}	
			
		}
	}
	void  updateDrone4() {
		if (PlayerHealth2 > 0 && score2 < 100) {
			if (x > 105 && DronemovingForward4) {
				x -= 0.25;
				if (y > 2) {
					y -= 0.05;
				}
			}
			if (x == 105) {
				DronemovingForward4 = false;
				if (PlayerHealth2 > 0) {
					PlayerHealth2 -= 5;
					if (PlayerHealth2 > 50) {
						L = 1;
					}
					else if (PlayerHealth2 <= 50) {
						L = 0;
					}
				}
			}
			if (x < 140 && (!DronemovingForward4)) {
				x += 0.25;
				if (y < 20) {
					y += 0.05;
				}
			}
			if (x == 140 && (!DronemovingForward4)) {
				DronemovingForward4 = true;
			}
			if (bulletX >= x && bulletZ >= z - 5 * radius && bulletZ <= z + 5 * radius && bulletY > y + 2.5 * radius && bulletY < y + 8 * radius) {
				z = 100;
				x = 200;
				y = 20;
				DronemovingForward4 = true;
				score2 += 5;
			}
		}
		else {
			z = 100;
			x = 200;
			y = 20;
			if (PlayerHealth2 <= 0 && score2 < 100) {
				first = true;
				level2 = false;
				PlayerHealth2 = 0;
			}
			if (score2 >= 100 && PlayerHealth2 > 0) {
				level2 = false;
				last = true;
				camXaim = 0;
				camYaim = 2;
				camZaim = 0;
				Xaim = 98;
				Yaim = 2;
				Zaim = 98;
			}
		}
	}
	void hulkDraw() {
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
		glPushMatrix();
		glTranslated(x, 0, z);
		glScalef(2, 2, 2);
		//glRotatef(45, 0, 1, 0);
		//glRotatef(-90, 1, 0, 0);
		model_hulk.Draw();
		glPopMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	}
	void RobotDraw1() {
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
		glPushMatrix();
		glTranslated(x, 4, z);
		glScalef(0.04, 0.035, 0.04);
		glRotatef(135, 0, 1, 0);
		glRotatef(-90, 1, 0, 0);
		model_robotEnemy.Draw();
		glPopMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	}
	void RobotDraw2() {
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
		glPushMatrix();
		glTranslated(x, 4, z);
		glScalef(0.04, 0.035, 0.04);
		glRotatef(45, 0, 1, 0);
		glRotatef(-90, 1, 0, 0);
		model_robotEnemy.Draw();
		glPopMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	}
	void RobotDraw3() {
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
		glPushMatrix();
		glTranslated(x, 4, z);
		glScalef(0.04, 0.035, 0.04);
		glRotatef(-45, 0, 1, 0);
		glRotatef(-90, 1, 0, 0);
		model_robotEnemy.Draw();
		glPopMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	}
	void RobotDraw4() {
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
		glPushMatrix();
		glTranslated(x, 4, z);
		glScalef(0.04, 0.035, 0.04);
		glRotatef(-135, 0, 1, 0);
		glRotatef(-90, 1, 0, 0);
		model_robotEnemy.Draw();
		glPopMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	}
	void DroneDraw1() {
		// draw drone 1
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
		glTranslated(x, y, z);
		glScalef(8, 8, 8);
		model_drone1.Draw();
		glPopMatrix();
	}
	void DroneDraw2() {
		// draw drone 2
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
		glTranslatef(x, y, z);
		glRotatef(180, 0, 1, 0);
		glScalef(8, 8, 8);
		model_drone1.Draw();
		glPopMatrix();
	}
	void DroneDraw3() {
		// draw drone 3
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
		glTranslatef(x, y, z);
		glRotatef(90, 0, 1, 0);
		glScalef(0.08, 0.08, 0.08);
		model_drone2.Draw();
		glPopMatrix();
	}
	void DroneDraw4() {
		// draw drone 3
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
		glTranslatef(x, y, z);
		glRotatef(90, 0, 1, 0);
		glScalef(0.08, 0.08, 0.08);
		model_drone2.Draw();
		glPopMatrix();
	}
	void unnecessaryDraw() {
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
		glTranslated(x, y, z);
		glutSolidSphere(radius, 30, 30);
		glPopMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	}
	void update() {
		if (shoot) {
			R = 1;
			G = 0;
			if (camXaim == 0 && (camZaim < 200 && camZaim>0)) {
				z = z + 0.15 * (camZaim - 100);
				x = x - 0.15 * 100;
			}
			else if (camXaim == 200 && (camZaim < 200 && camZaim>0)) {
				z = z + 0.15 * (camZaim - 100);
				x = x + 0.15 * 100;
			}
			else if (camZaim == 0 && camXaim < 200 && camXaim>0) {
				x = x + 0.15 * (camXaim - 100);
				z = z - 0.15 * 100;
			}
			else if (camZaim == 200 && camXaim < 200 && camXaim>0) {
				x = x + 0.15 * (camXaim - 100);
				z = z + 0.15 * 100;
			}
			else if (camXaim == 0 && camZaim == 0) {
				x = x - 0.15 * 100;
				z = z - 0.15 * 100;
			}
			else if (camXaim == 200 && camZaim == 0) {
				x = x + 0.15 * 100;
				z = z - 0.15 * 100;
			}
			else if (camXaim == 200 && camZaim == 200) {
				x = x + 0.15 * 100;
				z = z + 0.15 * 100;
			}
			else if (camXaim == 0 && camZaim == 200) {
				x = x - 0.15 * 100;
				z = z + 0.15 * 100;
			}
			y = y + 1.5* (camYaim - 2);
			if (x < radius || z < radius || y < radius || x>200 || z>200) {
				x = 100;
				z = 100;
				y = 2;
				i++;
				shoot = false;
			}
			bulletX = x;
			bulletZ = z;
			bulletY = y;
			glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
			glTranslated(x, y, z);
			glutSolidSphere(radius, 30, 30);
			glPopMatrix();
		}
		else {
			R = 0;
			G = 1;
		}
	}
};
Bullet bullets[]{ Bullet(0.3,black,100,camYaim,100) /*bullet0*/ , Bullet(1, black,0,camYaim,0) /*model 1 1*/ , Bullet(1,red,200,camYaim,0) /*model2 2*/ ,
Bullet(1,Cannonbase1,200,camYaim,200) /*model 3 3*/ , Bullet(1, Cannonbase2,0,camYaim,200) /* model 4 4 */ , Bullet(1, black,100,20,0) /* drone 1 5 */ ,
Bullet(0.3, black,100,20,200)/* drone 2 6 */,Bullet(0.3, black,0,20,100)/* drone 3 7 */,Bullet(0.3, black,200,20,100)/* drone 4 8 */,Bullet(1,green,100,camYaim,0)/*Hulk 9*/ } ;
//////////////////////////////////////////////////////////////////////  UPDATES Display  ////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////    LEVEL 1      ///////////////////////////////////////
void level1Display() {
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
	bullets[0].update();
	std::stringstream sstm;
	sstm << PlayerHealth;
	a = sstm.str();
	glPushMatrix();
	glTranslated(Xaim, 2.1, Zaim);
	glColor3f(1.0f, 1.0f, 1.0f);
	print(0, 0, a.data());
	glPopMatrix();

	if (c) {
		eyeX = 100; eyeZ = 100; eyeY = 2;
		glPushMatrix();
		glTranslated(Xaim, 2.3, Zaim);
		print(0, 0, "FPS Camera Mode is On");
		glPopMatrix();
		glPushMatrix();
		glTranslated(Xaim, 2.2, Zaim);
		print(0, 0, "Health:");
		glPopMatrix();
		glPushMatrix();
		glTranslated(Xaim, 2.5, Zaim);
		print(0, 0, "Score:");
		glPopMatrix();
		std::stringstream ssstm;
		ssstm << score;
		a = ssstm.str();
		glPushMatrix();
		glTranslated(Xaim, 2.4, Zaim);
		glColor3f(1.0f, 1.0f, 1.0f);
		print(0, 0, a.data());
		glPopMatrix();
	}
	else if (!c) {
		eyeX = ThirdeyeX; eyeZ = ThirdeyeZ; eyeY = ThirdeyeY;
		glPushMatrix();
		glTranslated(Xaim, 4, Zaim);
		print(0, 0, "Third EYE Camera Mode is On");
		glPopMatrix();
		glPushMatrix();
		glTranslated(Xaim, 3, Zaim);
		print(0, 0, "Health:");
		glPopMatrix();
		glPushMatrix();
		glTranslated(Xaim, 6, Zaim);
		print(0, 0, "Score:");
		glPopMatrix();
		std::stringstream ssstm;
		ssstm << score;
		a = ssstm.str();
		glPushMatrix();
		glTranslated(Xaim, 5, Zaim);
		glColor3f(1.0f, 1.0f, 1.0f);
		print(0, 0, a.data());
		glPopMatrix();
	}
	
	//Models Motion
	bullets[1].RobotDraw1();
	bullets[1].updateModel1();
	bullets[2].RobotDraw2();
	bullets[2].updateModel2();
	bullets[3].RobotDraw3();
	bullets[3].updateModel3();
	bullets[4].RobotDraw4();
	bullets[4].updateModel4();
	bullets[9].hulkDraw();
	bullets[9].updateModel5();
	////clear color for drawing
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	/////////////////////////////////////////////////LAND///////////////////////////////////////////////
	glDisable(GL_LIGHTING); // Disable lighting
	glColor3f(0.6, 0.6, 0.6); // Dim the ground texture a bit
	glEnable(GL_TEXTURE_2D); // Enable 2D texturing
	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]); // Bind the ground texture
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0);  
	glVertex3f(0, 0, 0);
	glTexCoord2f(5, 0);
	glVertex3f(200, 0, 0);
	glTexCoord2f(5, 5);
	glVertex3f(200, 0, 200);
	glTexCoord2f(0, 5);
	glVertex3f(0, 0, 200);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING); // Enable lighting again for other entites coming throung the pipeline.

	///////////////////////////////////////    sky box  ////////////////////////////////////////

	glEnable(GL_TEXTURE_2D); // Enable 2D texturing
	glBindTexture(GL_TEXTURE_2D, tex);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0); // Set quad normal direction.
	glTexCoord2f(0, 0);
	glVertex3f(20, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(20, 100, 0);
	glTexCoord2f(1, 1);
	glVertex3f(20, 100, 182);
	glTexCoord2f(1, 0);
	glVertex3f(20, 0, 182);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0); // Set quad normal direction.
	glTexCoord2f(0, 0);
	glVertex3f(-2, 0, 20);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 100, 20);
	glTexCoord2f(1, 1);
	glVertex3f(182, 100, 20);
	glTexCoord2f(1, 0);
	glVertex3f(182, 0, 20);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0); // Set quad normal direction.
	glTexCoord2f(1, 0);
	glVertex3f(180, 0, 18);
	glTexCoord2f(1, 1);
	glVertex3f(180, 100, 18);
	glTexCoord2f(0, 1);
	glVertex3f(180, 100, 180);
	glTexCoord2f(0, 0);
	glVertex3f(180, 0, 180);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(-2, 1, 0); // Set quad normal direction.
	glTexCoord2f(1, 0);
	glVertex3f(18, 0, 180);
	glTexCoord2f(1, 1);
	glVertex3f(18, 100, 180);
	glTexCoord2f(0, 1);
	glVertex3f(182, 100, 180);
	glTexCoord2f(0, 0);
	glVertex3f(182, 0, 180);
	glEnd();
	glPopMatrix();

	///////////////////////////////////////////// Draw Models ////////////////////////////////////////////////
	// Draw Tree Model
	glPushMatrix();
	glTranslatef(60, 0, 25);
	glScalef(2, 2, 2);
	model_tree.Draw();
	glPopMatrix();
	//Draw jeep model
	glPushMatrix();
	glTranslatef(170, 0, 100);
	glScalef(0.8, 0.8, 0.8);
	glRotatef(90, 0, 1, 0);
	model_jeep.Draw();
	glPopMatrix();
	/*// Draw helicopter Model
	glPushMatrix();
	glTranslatef(100, 26, 20);
	glScalef(2, 2, 2);
	glRotatef(10, 1, 0, 0);
	model_helicopter.Draw();
	glPopMatrix();*/
	// Draw house Model
	glPushMatrix();
	glTranslatef(30, 0, 33);
	glScalef(4, 4, 4);
	glRotatef(20, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	model_house.Draw();
	glPopMatrix();

	glDisable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	// Draw wall Model 1
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Cannonbase1);
	glTranslatef(100, 0, 95);
	glScalef(20, 1, 2);
	model_wall.Draw();
	glPopMatrix();
	// Draw wall Model 2
	glPushMatrix();
	glTranslatef(100, 0, 105);
	glScalef(20, 1, 2);
	model_wall.Draw();
	glPopMatrix();
	// Draw wall Model 3
	glPushMatrix();
	glTranslatef(105, 0, 100);
	glScalef(2, 1, 20);
	glRotatef(-90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();
	// Draw wall Model 4
	glPushMatrix();
	glTranslatef(95, 0, 100);
	glScalef(2, 1, 20);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	// Draw Cannon Player
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown);
	glTranslatef(100, 0, 100);
	glScalef(0.025, 0.025, 0.025);
	glRotatef(CannonRotation, 0, 1, 0); // negative is Right rotation while positive is Left
	glRotatef(-135, 0, 1, 0);
	model_cannon.Draw();
	glPopMatrix();
	glDisable(GL_LIGHT1);
	glEnable(GL_LIGHT0);
	// aim///////////////////
	glDisable(GL_LIGHT0);
	glEnable(GL_LIGHT2);
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	glTranslated(Xaim, Yaim, Zaim);
	glutWireSphere(0.02, 10, 10);
	glPopMatrix();
	glDisable(GL_LIGHT2);
	glEnable(GL_LIGHT0);

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
}
//////////////////////////////////////////////////////////////////       LEVEL2        ////////////////////////////////////////
void level2Display() {
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
	bullets[0].update();
	std::stringstream sstm;
	sstm << PlayerHealth2;
	a = sstm.str();
	glPushMatrix();
	glTranslated(Xaim, 2.1, Zaim);
	glColor3f(1.0f, 1.0f, 1.0f);
	print(0, 0, a.data());
	glPopMatrix();

	if (c) {
		eyeX = 100; eyeZ = 100; eyeY = 2;
		glPushMatrix();
		glTranslated(Xaim, 2.3, Zaim);
		print(0, 0, "FPS Camera Mode is On");
		glPopMatrix();
		glPushMatrix();
		glTranslated(Xaim, 2.2, Zaim);
		print(0, 0, "Health:");
		glPopMatrix();
		glPushMatrix();
		glTranslated(Xaim, 2.5, Zaim);
		print(0, 0, "Score:");
		glPopMatrix();
		std::stringstream ssstm;
		ssstm << score2;
		a = ssstm.str();
		glPushMatrix();
		glTranslated(Xaim, 2.4, Zaim);
		glColor3f(1.0f, 1.0f, 1.0f);
		print(0, 0, a.data());
		glPopMatrix();
	}
	else if (!c) {
		eyeX = ThirdeyeX; eyeZ = ThirdeyeZ; eyeY = ThirdeyeY;
		glPushMatrix();
		glTranslated(Xaim, 4, Zaim);
		print(0, 0, "Third EYE Camera Mode is On");
		glPopMatrix();
		glPushMatrix();
		glTranslated(Xaim, 3, Zaim);
		print(0, 0, "Health:");
		glPopMatrix();
		glPushMatrix();
		glTranslated(Xaim, 6, Zaim);
		print(0, 0, "Score:");
		glPopMatrix();
		std::stringstream ssstm;
		ssstm << score2;
		a = ssstm.str();
		glPushMatrix();
		glTranslated(Xaim, 5, Zaim);
		glColor3f(1.0f, 1.0f, 1.0f);
		print(0, 0, a.data());
		glPopMatrix();
	}
	//Models Motion
	bullets[5].DroneDraw1();
	bullets[5].updateDrone1();
	bullets[6].DroneDraw2();
	bullets[6].updateDrone2();
	bullets[7].DroneDraw3();
	bullets[8].DroneDraw4();
	bullets[7].updateDrone3();
	bullets[8].updateDrone4();

	// aim///////////////////
	glDisable(GL_LIGHT0);
	glEnable(GL_LIGHT2);
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	glTranslated(Xaim, Yaim, Zaim);
	glutWireSphere(0.02, 10, 10);
	glPopMatrix();
	glDisable(GL_LIGHT2);
	glEnable(GL_LIGHT0);

	////clear color for drawing
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	/////////////////////////////////////////////////LAND///////////////////////////////////////////////
	glDisable(GL_LIGHTING); // Disable lighting
	glColor3f(0.6, 0.6, 0.6); // Dim the ground texture a bit
	glEnable(GL_TEXTURE_2D); // Enable 2D texturing
	glBindTexture(GL_TEXTURE_2D, tex_ground2.texture[0]); // Bind the ground texture
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(200, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(200, 0, 200);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 200);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING); // Enable lighting again for other entites coming throung the pipeline.

	///////////////////////////////////////    sky box  ////////////////////////////////////////
	glEnable(GL_TEXTURE_2D); // Enable 2D texturing
	glBindTexture(GL_TEXTURE_2D, tex_sky2.texture[0]);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0); // Set quad normal direction.
	glTexCoord2f(0, 0);
	glVertex3f(20, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(20, 60, 0);
	glTexCoord2f(1, 1);
	glVertex3f(20, 60, 180);
	glTexCoord2f(1, 0);
	glVertex3f(20, 0, 180);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0); // Set quad normal direction.
	glTexCoord2f(0, 0);
	glVertex3f(-2 ,0, 20);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 60, 20);
	glTexCoord2f(1, 1);
	glVertex3f(180, 60, 20);
	glTexCoord2f(1, 0);
	glVertex3f(180, 0, 20);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0); // Set quad normal direction.
	glTexCoord2f(1, 0);
	glVertex3f(180, 0, 20);
	glTexCoord2f(1, 1);
	glVertex3f(180, 60, 20);
	glTexCoord2f(0, 1);
	glVertex3f(180, 60, 180);
	glTexCoord2f(0, 0);
	glVertex3f(180, 0, 180);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(-2, 1, 0); // Set quad normal direction.
	glTexCoord2f(1, 0);
	glVertex3f(20, 0, 180);
	glTexCoord2f(1, 1);
	glVertex3f(20, 60, 180);
	glTexCoord2f(0, 1);
	glVertex3f(180, 60, 180);
	glTexCoord2f(0, 0);
	glVertex3f(180, 0, 180);
	glEnd();
	glPopMatrix();

	glDisable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Cannonbase1);
	/////////////////////////////////////////////// Models ///////////////////////////////////////////////
	// Draw wall Model 1
	glPushMatrix();
	glTranslatef(100, 0, 95);
	glScalef(20, 1, 2);
	model_wall.Draw();
	glPopMatrix();
	// Draw wall Model 2
	glPushMatrix();
	glTranslatef(100, 0, 105);
	glScalef(20, 1, 2);
	model_wall.Draw();
	glPopMatrix();
	// Draw wall Model 3
	glPushMatrix();
	glTranslatef(105, 0, 100);
	glScalef(2, 1, 20);
	glRotatef(-90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();
	// Draw wall Model 4
	glPushMatrix();
	glTranslatef(95, 0, 100);
	glScalef(2, 1, 20);
	glRotatef(90, 0, 1, 0);
	model_wall.Draw();
	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	// Draw Cannon Player
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown);
	glTranslatef(100, 0, 100);
	glScalef(0.025, 0.025, 0.025);
	glRotatef(CannonRotation, 0, 1, 0); // negative is Right rotation while positive is Left
	glRotatef(-135, 0, 1, 0);
	model_cannon.Draw();
	glPopMatrix();
	glDisable(GL_LIGHT1);
	glEnable(GL_LIGHT0);

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, Cannonbase1);
	// Draw helicopter Model
	glPushMatrix();
	glTranslatef(100, 26, 20);
	glScalef(2, 2, 2);
	glRotatef(10, 1, 0, 0);
	model_helicopter.Draw();
	glPopMatrix();
	//Draw house
	glPushMatrix();
	glTranslatef(50, 20 ,50);
	glScalef(0.025, 0.025, 0.025);
	glRotatef(-135, 0, 1, 0);
	glRotatef(-15, 1, 0, 0);
	model_house2.Draw();
	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
}
///////////////////////////////////////////////////////////////   Transitions Display    //////////////////////////////////////
void level3Display() {
	////clear color for drawing
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	/////////////////////////////////////////////////LAND///////////////////////////////////////////////
	glDisable(GL_LIGHTING); // Disable lighting
	glColor3f(0.6, 0.6, 0.6); // Dim the ground texture a bit
	glEnable(GL_TEXTURE_2D); // Enable 2D texturing
	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]); // Bind the ground texture
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);
	glTexCoord2f(5, 0);
	glVertex3f(200, 0, 0);
	glTexCoord2f(5, 5);
	glVertex3f(200, 0, 200);
	glTexCoord2f(0, 5);
	glVertex3f(0, 0, 200);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING); // Enable lighting again for other entites coming throung the pipeline.

	///////////////////////////////////////    sky box  ////////////////////////////////////////
	glEnable(GL_TEXTURE_2D); // Enable 2D texturing
	glBindTexture(GL_TEXTURE_2D, tex);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0); // Set quad normal direction.
	glTexCoord2f(0, 0);
	glVertex3f(20, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(20, 100, 0);
	glTexCoord2f(1, 1);
	glVertex3f(20, 100, 182);
	glTexCoord2f(1, 0);
	glVertex3f(20, 0, 182);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0); // Set quad normal direction.
	glTexCoord2f(0, 0);
	glVertex3f(-2, 0, 20);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 100, 20);
	glTexCoord2f(1, 1);
	glVertex3f(182, 100, 20);
	glTexCoord2f(1, 0);
	glVertex3f(182, 0, 20);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0); // Set quad normal direction.
	glTexCoord2f(1, 0);
	glVertex3f(180, 0, 18);
	glTexCoord2f(1, 1);
	glVertex3f(180, 100, 18);
	glTexCoord2f(0, 1);
	glVertex3f(180, 100, 180);
	glTexCoord2f(0, 0);
	glVertex3f(180, 0, 180);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(-2, 1, 0); // Set quad normal direction.
	glTexCoord2f(1, 0);
	glVertex3f(18, 0, 180);
	glTexCoord2f(1, 1);
	glVertex3f(18, 100, 180);
	glTexCoord2f(0, 1);
	glVertex3f(182, 100, 180);
	glTexCoord2f(0, 0);
	glVertex3f(182, 0, 180);
	glEnd();
	glPopMatrix();
}
void level4Display() {

	////clear color for drawing
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
	/////////////////////////////////////////////////LAND///////////////////////////////////////////////
	glDisable(GL_LIGHTING); // Disable lighting
	glColor3f(0.6, 0.6, 0.6); // Dim the ground texture a bit
	glEnable(GL_TEXTURE_2D); // Enable 2D texturing
	glBindTexture(GL_TEXTURE_2D, tex_ground2.texture[0]); // Bind the ground texture
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(200, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(200, 0, 200);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 200);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING); // Enable lighting again for other entites coming throung the pipeline.

	///////////////////////////////////////    sky box  ////////////////////////////////////////
	glEnable(GL_TEXTURE_2D); // Enable 2D texturing
	glBindTexture(GL_TEXTURE_2D, tex_sky2.texture[0]);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0); // Set quad normal direction.
	glTexCoord2f(0, 0);
	glVertex3f(20, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(20, 60, 0);
	glTexCoord2f(1, 1);
	glVertex3f(20, 60, 180);
	glTexCoord2f(1, 0);
	glVertex3f(20, 0, 180);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0); // Set quad normal direction.
	glTexCoord2f(0, 0);
	glVertex3f(-2, 0, 20);
	glTexCoord2f(0, 1);
	glVertex3f(-2, 60, 20);
	glTexCoord2f(1, 1);
	glVertex3f(180, 60, 20);
	glTexCoord2f(1, 0);
	glVertex3f(180, 0, 20);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0); // Set quad normal direction.
	glTexCoord2f(1, 0);
	glVertex3f(180, 0, 20);
	glTexCoord2f(1, 1);
	glVertex3f(180, 60, 20);
	glTexCoord2f(0, 1);
	glVertex3f(180, 60, 180);
	glTexCoord2f(0, 0);
	glVertex3f(180, 0, 180);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(-2, 1, 0); // Set quad normal direction.
	glTexCoord2f(1, 0);
	glVertex3f(20, 0, 180);
	glTexCoord2f(1, 1);
	glVertex3f(20, 60, 180);
	glTexCoord2f(0, 1);
	glVertex3f(180, 60, 180);
	glTexCoord2f(0, 0);
	glVertex3f(180, 0, 180);
	glEnd();
	glPopMatrix();
	
}
/////////////////////////////////////////////////////////////////////   DISPLAY     //////////////////////////////////////////////////////////////
void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, camXaim, camYaim, camZaim, 0.0, 1.0, 0.0);
	// New Light 1/////////////////////////////////////
	GLfloat light1Color[] = { 1,L,L,0 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Color);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1Color);
	GLfloat lightPos1[] = { 100,5,100,0 };
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1Color);
	// new Light 2//////////////////////////////////////
	GLfloat aimColor[] = { R,G,0,0 };
	glLightfv(GL_LIGHT2, GL_DIFFUSE, aimColor);
	glLightfv(GL_LIGHT2, GL_SPECULAR, aimColor);
	GLfloat lightPos2[] = { Xaim,Yaim,Zaim,0 };
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, aimColor);
	
	if (first) {
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
		glPushMatrix();
		glTranslatef(40, 6 ,50);
		print(0, 0, "For Level 1 Press 1");
		glPopMatrix();
		glPushMatrix();
		glTranslatef(40, 2, 50);
		print(0, 0, "For Level 2 Press 2");
		glPopMatrix();
		glPushMatrix();
		glTranslatef(40, 10, 50);
		print(0, 0, "button Q gets you back to this Page");
		glPopMatrix();
		
	}
	if (between) {
		level3Display();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
		glPushMatrix();
		glTranslatef(40, 10, 50);
		print(0, 0, " Press W if you are ready for Level 2");
		glPopMatrix();
		glPushMatrix();
		glTranslatef(40, 6, 50);
		print(0, 0, " Your Score is:");
		glPopMatrix();
		std::stringstream ssstm;
		ssstm << score;
		a = ssstm.str();
		glPushMatrix();
		glTranslated(40, 4, 50);
		print(0, 0, a.data());
		glPopMatrix();
	}
	if (level1) {
		level1Display();
	}
	if (level2) {
		level2Display();
	}
	if (last) {
		level4Display();
		scoreTotal = score + score2;
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, black);
		glPushMatrix();
		glTranslatef(40, 14, 50);
		print(0, 0, "Game Over!!");
		glPopMatrix();
		glPushMatrix();
		glTranslatef(40, 12, 50);
		print(0, 0, "Press Q to restart");
		glPopMatrix();
		glPushMatrix();
		glTranslatef(40, 10, 50);
		print(0, 0, "Tour Total  Score:");
		glPopMatrix();
		std::stringstream sssstm;
		sssstm << scoreTotal;
		a = sssstm.str();
		glPushMatrix();
		glTranslated(40, 8, 50);
		print(0, 0, a.data());
		glPopMatrix();
		glPushMatrix();
		glTranslatef(40, 6, 50);
		print(0, 0, "Your level 2 Score:");
		glPopMatrix();
		std::stringstream ssstm;
		ssstm << score2;
		a = ssstm.str();
		glPushMatrix();
		glTranslated(40, 4, 50);
		print(0, 0, a.data());
		glPopMatrix();
	}
	glFlush();
	glutSwapBuffers();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void reshape(GLint w, GLint h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0f, GLfloat(w) / GLfloat(h), 1.0f, 150.0f);
	glMatrixMode(GL_MODELVIEW);
}
////////////////////////////////////                 keyboard function                    /////////////////////////////////////////////////////////
void key(unsigned char key1, int x, int y) {
	if (key1 == ' '&&(level1||level2)) {
		sndPlaySound(TEXT("shot4.wav"), SND_ASYNC);
		shoot = true;

	}
	if (key1 == 'c'&&(level1 || level2)) {
		c = !c;
	}
	if (key1 == '1'&& first) {
		level1 = true;
		first = false;
		//level2 = false;
	}
	if (key1 == '2' && first) {
		level2 = true;
		level1 = false;
		first = false;
	}
	if (key1 == 'q') {
		first = true;
		level1 = false;
		level2 = false;
		between = false;
		last = false;
		level3 = false;
		 eyeX = 100;
		 eyeY = 2;
		 eyeZ = 100;
		 ThirdeyeX = 125;
		 ThirdeyeY = 8;
		 ThirdeyeZ = 125;
		 camXaim = 0;
		 camYaim = 2;
		 camZaim = 0;
		 Xaim = 98;
		 Yaim = 2;
		 Zaim = 98;
		 bulletX = 0;
		 bulletY = 0;
		 bulletZ = 0;
		 CannonRotation = 0;
		 aimCenterX = 0;
		 aimCenterY = 0;
		 aimCenterZ = 0;
		 PlayerHealth = 100;
		 PlayerHealth2 = 100;
		 L = 1;
		 score = 0;
		 score2 = 0;
		 scoreTotal = 0;
		 camera2.setx(0);
		 camera2.sety(2);
		 camera2.setz(0);
		 bullets[0].setBulletX(100); bullets[0].setBulletY(camYaim); bullets[0].setBulletZ(100);
		 bullets[1].setBulletX(0); bullets[1].setBulletY(camYaim); bullets[1].setBulletZ(0);
		 bullets[2].setBulletX(200); bullets[2].setBulletY(camYaim); bullets[2].setBulletZ(0);
		 bullets[3].setBulletX(200); bullets[3].setBulletY(camYaim); bullets[3].setBulletZ(200);
		 bullets[4].setBulletX(0); bullets[4].setBulletY(camYaim); bullets[4].setBulletZ(200);
		 bullets[5].setBulletX(100); bullets[5].setBulletY(20); bullets[5].setBulletZ(0);
		 bullets[6].setBulletX(100); bullets[6].setBulletY(20); bullets[6].setBulletZ(200);
		 bullets[7].setBulletX(0); bullets[7].setBulletY(20); bullets[7].setBulletZ(100);
		 bullets[8].setBulletX(200); bullets[8].setBulletY(20); bullets[8].setBulletZ(100);

	}
	if (key1 == 'w'&& between) {
		first = false;
		level1 = false;
		level2 = true;
		between = false;
		eyeX = 100;
		eyeY = 2;
		eyeZ = 100;
		ThirdeyeX = 125;
		ThirdeyeY = 8;
		ThirdeyeZ = 125;
		camXaim = 0;
		camYaim = 2;
		camZaim = 0;
		Xaim = 98;
		Yaim = 2;
		Zaim = 98;
		bulletX = 0;
		bulletY = 0;
		bulletZ = 0;
		L = 1;
		CannonRotation = 0;
	}
	glutPostRedisplay();
}
/////////////////////////////////////////////////////////////     CANNON Directiom From Player     ////////////////////////////////////////////////
void special(int key, int, int) {
	switch (key) {
	case GLUT_KEY_LEFT:if (level1 || level2) { camera2.moveleft(); } break;
	case GLUT_KEY_RIGHT:if (level1 || level2) { camera2.moveright(); } break;
	case GLUT_KEY_UP:if (level1 || level2) { camera2.YmovePlus(); } break;
	case GLUT_KEY_DOWN:if (level1 || level2) { camera2.YmoveMinus(); } break;
	}
	glutPostRedisplay();
}
/////////////////////////////////////////////////////////////////         Timer            ////////////////////////////////////////////////////////
void timer(int v) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, v);
}
/////////////////////////////////////////////////////////////////         MAIN           //////////////////////////////////////////////////////////
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(1400, 900);
	glutCreateWindow("FPS");
	glutDisplayFunc(Display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutKeyboardFunc(key);
	glutTimerFunc(1000 / 60, timer, 0);
	glClearColor(0.7, 0.7, 0.7, 0.0f);
	LoadAssets();
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	GLfloat lightPos[] = { 100,50,100,0 };
	GLfloat lightIntensity[] = { 0.7,0.7,0.7,0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glutMainLoop();
	return(0);
}