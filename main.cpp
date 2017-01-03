
#include <glut.h>
#include <ctime>
#include <cstdlib>
//////
#include <iostream>
//////
//const int H = 36, W = 54;
const int H = 46, W = 104;
int scale = 10;
int w = W*scale, h = H*scale;
int ntime = 20;
int dir = 0;
int health = 115;
int healthOf = 10;
const int tankSize = 6;
const int wT = 3;
int bulletSize = 0;
bool attack[wT];
bool attacked[wT];

struct Positions{
	int x, y;
}tank[tankSize]{ {10,10},{10,11},{11,11},{11,12},{12,11},{12,10} }, wall[(H+W)*2];

struct {
	int x, y;
	int dir;
	int damage = 5;
}bullets[10];

struct {
	Positions pos[tankSize];
	int hp = healthOf;
	int dir;
}tanks[wT];

void calculePos(Positions &p, int x, int y)
{
	Positions *pos = &p;
	pos[2].x = x;
	pos[2].y = y;
	pos[0].x = pos[2].x - 1;
	pos[0].y = pos[2].y - 1;
	pos[1].x = pos[2].x - 1;
	pos[1].y = pos[2].y;
	pos[3].x = pos[2].x;
	pos[3].y = pos[2].y + 1;
	pos[4].x = pos[2].x + 1;
	pos[4].y = pos[2].y;
	pos[5].x = pos[2].x + 1;
	pos[5].y = pos[2].y - 1;
}

void drawTanks()
{
	glColor3f(0.0, 0.7, 1.0);
	for (int j = 0; j < wT	; j++) {
		for (int i = 0; i < tankSize; i++) {
			glRectf(tanks[j].pos[i].x*scale, tanks[j].pos[i].y*scale, (tanks[j].pos[i].x + 1)*scale, (tanks[j].pos[i].y + 1)*scale);
		}
	}
}

void drawTank()
{
	glColor3f(1.0, 1.0, 0.0);
	for (int i = 0; i < tankSize; i++) {
		glRectf(tank[i].x*scale, tank[i].y*scale, (tank[i].x + 1)*scale, (tank[i].y + 1)*scale);
	}
}

void drawBullet()
{
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < bulletSize; i++) {
		glRectf((bullets[i].x+0.3)*scale, (bullets[i].y+0.3)*scale, (bullets[i].x + 0.7)*scale, (bullets[i].y + 0.7)*scale);
	}
}

void fire(int i)
{
	bullets[bulletSize].x = tanks[i].pos[3].x;
	bullets[bulletSize].y = tanks[i].pos[3].y;
	bullets[bulletSize].dir = tanks[i].dir;
	bulletSize++;
}

void findTank(int num) {
	for (int i = 0; i < tankSize; i++) {
		if (tanks[num].pos[3].x == tank[i].x && tanks[num].pos[3].y > tank[i].y)
			tanks[num].dir = 3;
		else if (tanks[num].pos[3].y == tank[i].y && tanks[num].pos[3].x > tank[i].x)
			tanks[num].dir = 1;
		else if (tanks[num].pos[3].y == tank[i].y && tanks[num].pos[3].x < tank[i].x)
			tanks[num].dir = 2;
		else if (tanks[num].pos[3].x == tank[i].x && tanks[num].pos[3].y < tank[i].y)
			tanks[num].dir = 0;
	}
}

void AI()
{
	for (int i = 0; i < wT; i++) {
		
		for (int j = 0; j < tankSize; j++) {
			if (tanks[i].pos[3].x == tank[j].x && tanks[i].pos[3].y > tank[j].y)
				tanks[i].dir = 3;
			else if (tanks[i].pos[3].y == tank[j].y && tanks[i].pos[3].x > tank[j].x)
				tanks[i].dir = 1;
			else if (tanks[i].pos[3].y == tank[j].y && tanks[i].pos[3].x < tank[j].x)
				tanks[i].dir = 2;
			else if (tanks[i].pos[3].x == tank[j].x && tanks[i].pos[3].y < tank[j].y)
				tanks[i].dir = 0;
			else attacked[i] = false;
		}
		if (attack[i]) {
			switch (tanks[i].dir)
			{
			case 0:
				for (int a = 0; a < tankSize; a++) {
					if (tank[a].x == tanks[i].pos[3].x && tank[a].y>tanks[i].pos[3].y) {
						fire(i);
					}
					else {
						attack[i] = false;
						attacked[i] = false;
					}
				}
				break;
			case 1:
				for (int a = 0; a < tankSize; a++) {
					if (tank[a].y == tanks[i].pos[3].y && tank[a].x < tanks[i].pos[3].x) {
						fire(i);
					}
					else {
						attack[i] = false;
						attacked[i] = false;
					}
				}
				break;
			case 2:
				for (int a = 0; a < tankSize; a++) {
					if (tank[a].y == tanks[i].pos[3].y && tank[a].x>tanks[i].pos[3].x) {
						fire(i);
					}
					else {
						attack[i] = false;
						attacked[i] = false;
					}
				}
				break;
			case 3:
				for (int a = 0; a < tankSize; a++) {
					if (tank[a].x == tanks[i].pos[3].x && tank[a].y < tanks[i].pos[3].y) {
						fire(i);
					}
					else {
						attack[i] = false;
						attacked[i] = false;
					}
				}
				break;
			}
			continue;
		}
		if (rand() % 3 == 1)
			tanks[i].dir = rand() % 4;
		
		switch (tanks[i].dir)
		{
		case 0:
			tanks[i].pos[0].x = tanks[i].pos[2].x - 1;
			tanks[i].pos[0].y = tanks[i].pos[2].y - 1;
			tanks[i].pos[1].x = tanks[i].pos[2].x - 1;
			tanks[i].pos[1].y = tanks[i].pos[2].y;
			tanks[i].pos[3].x = tanks[i].pos[2].x;
			tanks[i].pos[3].y = tanks[i].pos[2].y + 1;
			tanks[i].pos[4].x = tanks[i].pos[2].x + 1;
			tanks[i].pos[4].y = tanks[i].pos[2].y;
			tanks[i].pos[5].x = tanks[i].pos[2].x + 1;
			tanks[i].pos[5].y = tanks[i].pos[2].y - 1;

			for (int a = 0; a < tankSize; a++) {
				if (tank[a].x == tanks[i].pos[3].x && tank[a].y>tanks[i].pos[3].y) {
					fire(i);
					attack[i] = true;
				}
			}
			if (tanks[i].pos[3].y + 3 >= H - 1) {
				tanks[i].dir = rand() % 3 + 1;
				AI();
			}
			
			
			break;
		case 1:
			tanks[i].pos[0].x = tanks[i].pos[2].x + 1;
			tanks[i].pos[0].y = tanks[i].pos[2].y - 1;
			tanks[i].pos[1].x = tanks[i].pos[2].x;
			tanks[i].pos[1].y = tanks[i].pos[2].y - 1;
			tanks[i].pos[3].x = tanks[i].pos[2].x - 1;
			tanks[i].pos[3].y = tanks[i].pos[2].y;
			tanks[i].pos[4].x = tanks[i].pos[2].x;
			tanks[i].pos[4].y = tanks[i].pos[2].y + 1;
			tanks[i].pos[5].x = tanks[i].pos[2].x + 1;
			tanks[i].pos[5].y = tanks[i].pos[2].y + 1;

			for (int a = 0; a < tankSize; a++) {
				if (tank[a].y == tanks[i].pos[3].y && tank[a].x < tanks[i].pos[3].x) {
					fire(i);
					attack[i] = true;
				}
			}
			if (tanks[i].pos[3].x - 3 <= 0) {
				tanks[i].dir = rand() % 4;
				if (tanks[i].dir == 1) tanks[i].dir = 2;
				AI();
			}
			
			break;
		case 2:
			tanks[i].pos[0].x = tanks[i].pos[2].x - 1;
			tanks[i].pos[0].y = tanks[i].pos[2].y + 1;
			tanks[i].pos[1].x = tanks[i].pos[2].x;
			tanks[i].pos[1].y = tanks[i].pos[2].y + 1;
			tanks[i].pos[3].x = tanks[i].pos[2].x + 1;
			tanks[i].pos[3].y = tanks[i].pos[2].y;
			tanks[i].pos[4].x = tanks[i].pos[2].x;
			tanks[i].pos[4].y = tanks[i].pos[2].y - 1;
			tanks[i].pos[5].x = tanks[i].pos[2].x - 1;
			tanks[i].pos[5].y = tanks[i].pos[2].y - 1;

			for (int a = 0; a < tankSize; a++) {
				if (tank[a].y == tanks[i].pos[3].y && tank[a].x>tanks[i].pos[3].x) {
					fire(i);
					attack[i] = true;
				}
			}
			if (tanks[i].pos[3].x + 3 >= W-1 ) {
				tanks[i].dir = rand() % 4;
				if (tanks[i].dir == 2) tanks[i].dir = 1;
				AI();
			}
			
			break;
		case 3:
			tanks[i].pos[0].x = tanks[i].pos[2].x + 1;
			tanks[i].pos[0].y = tanks[i].pos[2].y + 1;
			tanks[i].pos[1].x = tanks[i].pos[2].x + 1;
			tanks[i].pos[1].y = tanks[i].pos[2].y;
			tanks[i].pos[3].x = tanks[i].pos[2].x;
			tanks[i].pos[3].y = tanks[i].pos[2].y - 1;
			tanks[i].pos[4].x = tanks[i].pos[2].x - 1;
			tanks[i].pos[4].y = tanks[i].pos[2].y;
			tanks[i].pos[5].x = tanks[i].pos[2].x - 1;
			tanks[i].pos[5].y = tanks[i].pos[2].y + 1;

			for (int a = 0; a < tankSize; a++) {
				if (tank[a].x == tanks[i].pos[3].x && tank[a].y < tanks[i].pos[3].y) {
					fire(i);
					attack[i] = true;
				}
			}
			if (tanks[i].pos[3].y - 3 <= 0) {
				tanks[i].dir = rand() % 3;
				AI();
			}
			
			break;
		}
	}
}


void drawTW()
{
	for (int j = 0; j < wT; j++) {
		if (attacked[j]) continue;
		if (tanks[j].hp <= 0) {
			
			for (int a = 0; a < tankSize; a++)
				tanks[j].pos[a].x = tanks[j].pos[a].y = 100;
			
			continue;
		}
		switch (tanks[j].dir)
		{
		case 0:
			for (int i = 0; i < tankSize; i++)
				tanks[j].pos[i].y++;
			break;
		case 1:
			for (int i = 0; i < tankSize; i++)
				tanks[j].pos[i].x--;
			break;
		case 2:
			for (int i = 0; i < tankSize; i++)
				tanks[j].pos[i].x++;
			break;
		case 3:
			for (int i = 0; i < tankSize; i++)
				tanks[j].pos[i].y--;
			break;
		}

		for (int i = 0; i < tankSize; i++) {
			if (tanks[j].pos[i].x > W-2 || tanks[j].pos[i].x < 2)
				if (tanks[j].dir == 1) tanks[j].dir = 2;
				else if (tanks[j].dir == 2) tanks[j].dir = 1;
				else if (tanks[j].dir == 0) tanks[j].dir = 3;
				else tanks[j].dir = 0;
			else if (tanks[j].pos[i].y>H-2 || tanks[j].pos[i].y<2)
				if (tanks[j].dir == 1) tanks[j].dir = 2;
				else if (tanks[j].dir == 2) tanks[j].dir = 1;
				else if (tanks[j].dir == 0) tanks[j].dir = 3;
				else tanks[j].dir = 0;
		}
	}
}

void mouseButton(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			bullets[bulletSize].x = tank[3].x;
			bullets[bulletSize].y = tank[3].y;
			bullets[bulletSize].dir = dir;
			bulletSize++;
		}
	}

}
void inputKbd(int key, int a, int b)
{
	if (health >= 0) {
		switch (key) {
		case 100:
			if (dir != 1) {
				tank[0].x = tank[2].x + 1;
				tank[0].y = tank[2].y - 1;
				tank[1].x = tank[2].x;
				tank[1].y = tank[2].y - 1;
				tank[3].x = tank[2].x - 1;
				tank[3].y = tank[2].y;
				tank[4].x = tank[2].x;
				tank[4].y = tank[2].y + 1;
				tank[5].x = tank[2].x + 1;
				tank[5].y = tank[2].y + 1;
				dir = 1;
			}
			break;
		case 101:
			if (dir != 0) {
				tank[0].x = tank[2].x - 1;
				tank[0].y = tank[2].y - 1;
				tank[1].x = tank[2].x - 1;
				tank[1].y = tank[2].y;
				tank[3].x = tank[2].x;
				tank[3].y = tank[2].y + 1;
				tank[4].x = tank[2].x + 1;
				tank[4].y = tank[2].y;
				tank[5].x = tank[2].x + 1;
				tank[5].y = tank[2].y - 1;
				dir = 0;
			}
			break;
		case 102:
			if (dir != 2) {
				tank[0].x = tank[2].x - 1;
				tank[0].y = tank[2].y + 1;
				tank[1].x = tank[2].x;
				tank[1].y = tank[2].y + 1;
				tank[3].x = tank[2].x + 1;
				tank[3].y = tank[2].y;
				tank[4].x = tank[2].x;
				tank[4].y = tank[2].y - 1;
				tank[5].x = tank[2].x - 1;
				tank[5].y = tank[2].y - 1;
				dir = 2;
			}
			break;
		case 103:
			if (dir != 3) {
				tank[0].x = tank[2].x + 1;
				tank[0].y = tank[2].y + 1;
				tank[1].x = tank[2].x + 1;
				tank[1].y = tank[2].y;
				tank[3].x = tank[2].x;
				tank[3].y = tank[2].y - 1;
				tank[4].x = tank[2].x - 1;
				tank[4].y = tank[2].y;
				tank[5].x = tank[2].x - 1;
				tank[5].y = tank[2].y + 1;
				dir = 3;
			}
			break;
		}
		
		switch (dir)
		{
		case 0:
			if (tank[3].y<H-2)
				for (int i = 0; i < tankSize; i++)
					tank[i].y++;
			break;
		case 1:
			if (tank[3].x>1)
				for (int i = 0; i < tankSize; i++)
					tank[i].x--;
			break;
		case 2:
			if (tank[3].x<W-2)
				for (int i = 0; i < tankSize; i++)
					tank[i].x++;
			break;
		case 3:
			if (tank[3].y>1)
				for (int i = 0; i < tankSize; i++)
					tank[i].y--;
			break;
		}
	}
	else {
		for (int i = 0; i < tankSize; i++) {
			tank[i].x = tank[i].y = -10;
		}
	}
}

void drawWall()
{
	for (int i = 0; i < (H+W)*2; i++) {
		glColor3f(0.5, 0.0, 0.0);
		glRectf(wall[i].x*scale, wall[i].y*scale, (wall[i].x + 1)*scale, (wall[i].y + 1)*scale);
	}
}

void destroyBullet()
{
	for (int i = 0; i < bulletSize - 1; i++) {
		bullets[i].x = bullets[i + 1].x;
		bullets[i].y = bullets[i + 1].y;
		bullets[i].dir = bullets[i + 1].dir;
	}
	bulletSize--;
}

void tick()
{
	if (bulletSize != 0) {
		for (int i = 0; i < bulletSize; i++) {
			switch (bullets[i].dir)
			{
			case 0:
				bullets[i].y++;
				break;
			case 1:
				bullets[i].x--;
				break;
			case 2:
				bullets[i].x++;
				break;
			case 3:
				bullets[i].y--;
				break;
			}
			for (int j = 0; j < (H+W)*2; j++) {
				if (bullets[i].x == wall[j].x&&bullets[i].y == wall[j].y) {
					wall[j].x = W; wall[j].y = H;
					destroyBullet();
				}
			}
			for (int j = 0; j < tankSize; j++) {
				if (bullets[i].x == tank[j].x&&bullets[i].y == tank[j].y) {
					health -= bullets[i].damage;
					destroyBullet();
				}
			}
			for (int j = 0; j < wT; j++) {
				for (int a = 0; a < tankSize; a++) {
					if (bullets[i].x == tanks[j].pos[a].x&&bullets[i].y == tanks[j].pos[a].y) {
						tanks[j].hp -= bullets[i].damage;
						attacked[j] = true;
						findTank(j);
						destroyBullet();
					}
				}
			}
			if (bullets[i].x > W-1 || bullets[i].y > H-1 || bullets[i].x < 0 || bullets[i].y < 0) {
				destroyBullet();
			}
		}
	}
}

void display()
{
	glClearColor(0.1, 0.1, 0.1, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	drawTank();
	drawWall();
	drawTanks();
	drawBullet();

	glFlush();
}

void fastTimer(int)
{
	tick();
	glutTimerFunc(20, fastTimer, 0);
}

void timer(int)
{
	if (health > 0) {
		display();
	}
	else {
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glColor3f(1.0, 0.0, 0.0);
		glRectf(10 * scale, 20 * scale, 11 * scale, 30 * scale);
		glRectf(10 * scale, 20 * scale, 15 * scale, 21 * scale);

		glRectf(17 * scale, 20 * scale, 18 * scale, 30 * scale);
		glRectf(17 * scale, 20 * scale, 23 * scale, 21 * scale);
		glRectf(22 * scale, 20 * scale, 23 * scale, 30* scale);
		glRectf(17 * scale, 29 * scale, 23 * scale, 30 * scale);

		glRectf(25 * scale, 20 * scale, 26 * scale, 30 * scale);
		glRectf(25 * scale, 20 * scale, 30 * scale, 21 * scale);
		glFlush();
	}

	glutTimerFunc(ntime, timer, 0);
}
void normalTimer(int)
{
	drawTW();

	glutTimerFunc(100, normalTimer, 0);
}
void longTimer(int)
{
	AI();
	glutTimerFunc(500, longTimer, 0);
}

int main(int argc, char **argv)
{
	srand(time(0));

	for (int i = 0; i < H; i++){
		wall[i].x = 0;
		wall[i].y = i;
	}
	for (int i = H; i < H+W; i++) {
		wall[i].x = i-H;
		wall[i].y = 0;
	}
	for (int i = H+W; i < 2*H+W; i++) {
		wall[i].x = W - 1;
		wall[i].y = i-(H+W);
	}
	for (int i = 2*H+W; i < (H+W)*2; i++) {
		wall[i].x = i - (2*H+W);
		wall[i].y = H - 1;
	}

	calculePos(tanks[0].pos[0], 20, 10);
	calculePos(tanks[1].pos[0], 30, 10);
	calculePos(tanks[2].pos[0], 20, 20);
	//calculePos(tanks[3].pos[0], 30, 20);
	//calculePos(tanks[4].pos[0], 40, 20);
	//calculePos(tanks[5].pos[0], 40, 10);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(w, h);
	glutCreateWindow("Проект");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);

	glutDisplayFunc(display);
	glutTimerFunc(ntime, timer, 0);
	glutTimerFunc(700, longTimer, 0);
	glutTimerFunc(20, fastTimer, 0);
	glutTimerFunc(100, normalTimer, 0);

	glutSpecialFunc(inputKbd);
	glutMouseFunc(mouseButton);

	glutMainLoop();
}