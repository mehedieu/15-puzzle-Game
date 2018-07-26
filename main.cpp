/*
Program		: 15-Puzzle
Credit		: Unknown
*/


#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include <ctime>

#include<cmath>
#include<iostream>
#include<fstream>
#include<numeric>

#include<string>
#include<vector>
#include<queue>
#include<map>
#include<algorithm>
#include<set>
#include<sstream>
#include<stack>
#include<list>
#include<iterator>

#include <windows.h>
#include <gl/glut.h>


using namespace std;

#define REP(i,n) for(i=0; i<(n); i++)
#define FOR(i,a,b) for(i=(a); i<=(b); i++)
#define CLEAR(t) memset((t), 0, sizeof(t))

#define sz size()
#define pb push_back
#define pf push_front

#define VI vector<int>
#define VS vector<string>
#define LL long long

#define WIDTH 450
#define HEIGHT 450
#define pi 2*acos(0.0)

void *font = GLUT_BITMAP_TIMES_ROMAN_24;

int Tvalue[4][4][2] = {
	{	{-165,-165},	{-55,-165},	{55,-165},	{165,-165}},
	{	{-165,-55},		{-55,-55},	{55,-55},	{165,-55}},
	{	{-165,55},		{-55,55},	{55,55},	{165,55}},
	{	{-165,165},		{-55,165},	{55,165},	{165,165}},
};

int Tfinal[4][4] = {
	{ 13,	14,	15,	0},
	{ 9,	10,	11,	12},
	{ 5,	6,	7,	8},
	{ 1,	2,	3,	4},
};

int Tnumber[4][4] = {
	{ 13,	14,	15,	12},
	{ 9,	10,	11,	8},
	{ 5,	6,	7,	0},
	{ 1,	2,	3,	4},
};

int PrevX,PrevY,Dir,xcnt = 0;
time_t time1,time2;
bool print = true;
char b[1150];

void reshape(int width, int height)
{
	glViewport(0,0,width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WIDTH/2, WIDTH/2-1, -HEIGHT/2, HEIGHT/2-1,-1000,1000);
}

void drawPixel(int x,int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}



void writeNumber()
{
	int i,j,n;
	for(i = 0;i<4;i++)
	{
		for(j = 0;j<4;j++)
		{
			glPushMatrix();
			glRasterPos2f(Tvalue[i][j][0], Tvalue[i][j][1]);
			n = Tnumber[i][j];
			if(!n)	continue;
			if(n>9)
			{
				glutBitmapCharacter(font, '1');
				glutBitmapCharacter(font, n%10 + '0');
			}
			else
			{
				glutBitmapCharacter(font, n + '0');
			}
			glPopMatrix();
		}
	}
}

void display15Box()
{
	int i,j;

	for(i = 0;i<4;i++)
		for(j = 0;j<4;j++)
		{
			if(!Tnumber[i][j])	continue;
			glPushMatrix();
			glTranslatef(Tvalue[i][j][0],Tvalue[i][j][1],0);
			glColor4f(0.0, 0.5, 0.0, 1.0);
			glutSolidCube(100.0);
			glColor4f(0.0, 0.6, 0.5, 1.0);
			glutWireCube(100.0);

			glPopMatrix();
		}
}

void setPrev()
{
	int i,j;
	for(i = 0;i<4;i++)
		for(j = 0;j<4;j++)
			if(!Tnumber[i][j])
			{
				PrevX = Tvalue[i][j][0];
				PrevY = Tvalue[i][j][1];
			}
}

void checkForMat()
{
	bool fl;
	int i,j;
	char st[100];

	for(i = 0;i<4;i++)
	{
		for(j = 0;j<4;j++)
			if(Tnumber[i][j]!=Tfinal[i][j])
				fl = false;
	}
	if(fl)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glPushMatrix();
		glRasterPos2f(-100,40);
		strcpy(st,"Congratulation!!!!");
		for(i = 0;st[i];i++)
			glutBitmapCharacter(font, st[i]);

		glRasterPos2f(-100,0);
		strcpy(st,"Number of Steps: ");
		for(i = 0;st[i];i++)
			glutBitmapCharacter(font, st[i]);

		sprintf(st,"%d",xcnt);
		for(i = 0;st[i];i++)
			glutBitmapCharacter(font, st[i]);


		if(print)
		{
			time(&time2);
			print = false;
		}
		int nn = time2 - time1;

		glRasterPos2f(-170,-40);
		strcpy(st,"You take: ");
		for(i = 0;st[i];i++)
			glutBitmapCharacter(font, st[i]);

		sprintf(st,"%d",nn/60);
		for(i = 0;st[i];i++)
			glutBitmapCharacter(font, st[i]);

		strcpy(st," Min(s) & ");
		for(i = 0;st[i];i++)
			glutBitmapCharacter(font, st[i]);

		sprintf(st,"%d",nn%60);
		for(i = 0;st[i];i++)
			glutBitmapCharacter(font, st[i]);

		strcpy(st," Second(s)");
		for(i = 0;st[i];i++)
			glutBitmapCharacter(font, st[i]);
		glPopMatrix();
	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt( 0,-.7,20,1,0,0,0,1,0 );
	setPrev();

	glPushMatrix();
	display15Box();
	glPopMatrix();

	glPushMatrix();
	glColor4f(1.0, 0.0, 0.0, 1.0);
	writeNumber();
	glPopMatrix();

	glPushMatrix();
	checkForMat();
	glPopMatrix();
	glutSwapBuffers();
}

void changeEffect()
{
	int x,y,xx,yy;
	int i,j;
	for(i = 0;i<4;i++)
		for(j = 0;j<4;j++)
		{
			if(Tnumber[i][j]==0)
			{
				x = i;
				y = j;
			}
		}
	xx = x,yy = y;
	if(Dir==0)
		xx = x + 1;
	else if(Dir==1)
		yy = y + 1;
	else if(Dir==2)
		xx = x - 1;
	else if(Dir==3)
		yy = y - 1;

	if(xx>=0&&xx<4&&yy>=0&&yy<4)
	{
		i = Tnumber[x][y];
		Tnumber[x][y] = Tnumber[xx][yy];
		Tnumber[xx][yy] = i;
		xcnt++;
	}
}

bool Check(int x,int y)
{
	int i,j,xx,yy;
	for(i = 0;i<4;i++)
	{
		for(j = 0;j<4;j++)
			if(Tnumber[i][j]==0)
			{
				xx = i;
				yy = j;
			}
	}
	if(abs(Tvalue[xx][yy][0]-x)<=50&&abs(Tvalue[xx][yy][1]-y)<=50)
		return true;
	return false;
}

void MouseMotion(int x,int y)
{
	int dx,dy;
	x -= 225;
	y = 225 - y;
	if(Check(x,y))
	{
		dx = x - PrevX;
		dy = PrevY-y;

		if(abs(dx)>abs(dy)+20)
		{
			if(dx>0)
				Dir = 1;
			else
				Dir = 3;
		}
		else if(abs(dx)+20<abs(dy))
		{
			if(dy<0)
				Dir = 0;
			else
				Dir = 2;
		}
		changeEffect();
		glutPostRedisplay();
	}
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:
			exit (0);
		break;

		case 56:
			Dir = 2;
		break;

		case 54:
			Dir = 3;
		break;

		case 50:
			Dir = 0;
		break;

		case 52:
			Dir = 1;
		break;
	}
	changeEffect();
	glutPostRedisplay();
}

void SpecialFunction(int key,int x,int y)
{
	if (key == GLUT_KEY_LEFT)	Dir = 1;
	if (key == GLUT_KEY_RIGHT)	Dir = 3;
	if( key == GLUT_KEY_UP)		Dir = 2;
	if( key == GLUT_KEY_DOWN)	Dir = 0;
	changeEffect();
	glutPostRedisplay();
}

int Random()
{
	return int (rand() * clock() + 1);
}


int caseno,a[5][5],depth,move,fl,mv;


struct pos
{
	int x,y;
}p[200],p0;

struct priority
{
	int move,mv;
	char cr;
};

inline void calculate()
{
	p[0].x=3;p[0].y=3; p[1].x=0;p[1].y=0; p[2].x=0;p[2].y=1; p[3].x=0;p[3].y=2;
	p[4].x=0;p[4].y=3; p[5].x=1;p[5].y=0; p[6].x=1;p[6].y=1; p[7].x=1;p[7].y=2;
	p[8].x=1;p[8].y=3; p[9].x=2;p[9].y=0; p[10].x=2;p[10].y=1; p[11].x=2;p[11].y=2;
	p[12].x=2;p[12].y=3; p[13].x=3;p[13].y=0; p[14].x=3;p[14].y=1; p[15].x=3;p[15].y=2;
}

int find_min_move()
{
	int i,j,move=0,m;

	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			if(a[i][j])
			{
				m=a[i][j];
				move+=abs(i-p[m].x)+abs(j-p[m].y);
			}
		}
	return move;
}

inline int valid(int i,int j)
{
	if(i>=0&&i<4&&j>=0&&j<4)
		return 1;
	return 0;
}

inline char pr(int move)
{
	if(move)
		return b[move];
	return ' ';
}

inline void swap(int &a,int &b)
{
	int c=a;
	a=b;
	b=c;
}

inline void swap(priority &a,priority &b)
{
	priority c=a;
	a=b;
	b=c;
}



void fillAuto()
{
	int i,len = strlen(b);
	time_t t1,t2;
	time(&t1);

	for(i = 0;i<len;)
	{
		time(&t2);
		if(t2-t1<1)	continue;
		t1 = t2;
		switch (b[i])
		{
		case 'R':
			Dir = 1;
			break;
		case 'L':
			Dir = 3;
			break;
		case 'U':
			Dir = 0;
			break;
		case 'D':
			Dir = 2;
			break;
		}
		changeEffect();

		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt( 0,-.7,20,1,0,0,0,1,0 );
		setPrev();

		glPushMatrix();
		display15Box();
		glPopMatrix();

		glPushMatrix();
		glColor4f(1.0, 0.0, 0.0, 1.0);
		writeNumber();
		glPopMatrix();

		glPushMatrix();
		checkForMat();
		glPopMatrix();
		glutSwapBuffers();
		i++;
	}
}

void rec()
{
	if(mv==0)
	{
		b[move]='\0';
		fl=1;
		//puts(b);
		fillAuto();
		return;
	}
	int m,l=0,temp,svmv=mv,i,j;
	char ch=pr(move-1);
	priority sv[4];

	if(ch!='L')
	{
		if(valid(p0.x,p0.y+1))
		{
			temp=a[p0.x][p0.y+1];
			m=abs(p[temp].x-p0.x)+abs(p[temp].y-(p0.y+1));
			swap(a[p0.x][p0.y],a[p0.x][p0.y+1]);
			m=mv-m+abs(p[temp].x-p0.x)+abs(p[temp].y-p0.y);
			if(move+m+1<=depth)
			{
					sv[l].move=move+m;
				sv[l].mv=m;
				sv[l++].cr='R';
			}
			swap(a[p0.x][p0.y],a[p0.x][p0.y+1]);
		}
	}
	if(ch!='U')
	{
		if(valid(p0.x+1,p0.y))
		{
			temp=a[p0.x+1][p0.y];
			m=abs(p[temp].x-(p0.x+1))+abs(p[temp].y-p0.y);
			swap(a[p0.x][p0.y],a[p0.x+1][p0.y]);
			m=mv-m+abs(p[temp].x-p0.x)+abs(p[temp].y-p0.y);
			if(move+m+1<=depth)
			{
				sv[l].move=move+m;
				sv[l].mv=m;
				sv[l++].cr='D';
			}
			swap(a[p0.x][p0.y],a[p0.x+1][p0.y]);
		}
	}
	if(ch!='R')
	{
		if(valid(p0.x,p0.y-1))
		{
			temp=a[p0.x][p0.y-1];
			m=abs(p[temp].x-p0.x)+abs(p[temp].y-(p0.y-1));
			swap(a[p0.x][p0.y],a[p0.x][p0.y-1]);
			m=mv-m+abs(p[temp].x-p0.x)+abs(p[temp].y-p0.y);
			if(move+m+1<=depth)
			{
				sv[l].move=move+m;
				sv[l].mv=m;
				sv[l++].cr='L';
			}
			swap(a[p0.x][p0.y],a[p0.x][p0.y-1]);
		}
	}
	if(ch!='D')
	{
		if(valid(p0.x-1,p0.y))
		{
			temp=a[p0.x-1][p0.y];
			m=abs(p[temp].x-(p0.x-1))+abs(p[temp].y-p0.y);
			swap(a[p0.x][p0.y],a[p0.x-1][p0.y]);
			m=mv-m+abs(p[temp].x-p0.x)+abs(p[temp].y-p0.y);
			if(move+m+1<=depth)
			{
				sv[l].move=move+m;
				sv[l].mv=m;
				sv[l++].cr='U';
			}
			swap(a[p0.x][p0.y],a[p0.x-1][p0.y]);
		}
	}
	for(i=0;i<l-1;i++)
	{
		for(j=i+1;j<l;j++)
		{
			if(sv[i].move>sv[j].move)
				swap(sv[i],sv[j]);
		}
	}
	for(m=0;m<l;m++)
	{
		if(sv[m].cr=='R')
		{
			swap(a[p0.x][p0.y],a[p0.x][p0.y+1]);
			b[move]='R';
			move++;p0.y++;
			mv=sv[m].mv;
			rec();
			move--;p0.y--;
			swap(a[p0.x][p0.y],a[p0.x][p0.y+1]);
			if(fl)
				return;
		}
		else if(sv[m].cr=='D')
		{
			swap(a[p0.x][p0.y],a[p0.x+1][p0.y]);
			b[move]='D';
			move++;p0.x++;
			mv=sv[m].mv;
			rec();
			move--;p0.x--;
			swap(a[p0.x][p0.y],a[p0.x+1][p0.y]);
			if(fl)
				return;
		}
		else if(sv[m].cr=='L')
		{
			swap(a[p0.x][p0.y],a[p0.x][p0.y-1]);
			b[move]='L';
			move++;p0.y--;
			mv=sv[m].mv;
			rec();
			move--;p0.y++;
			swap(a[p0.x][p0.y],a[p0.x][p0.y-1]);
			if(fl)
				return;
		}
		else
		{
			swap(a[p0.x][p0.y],a[p0.x-1][p0.y]);
			b[move]='U';
			move++;p0.x--;
			mv=sv[m].mv;
			rec();
			move--;p0.x++;
			swap(a[p0.x][p0.y],a[p0.x-1][p0.y]);
			if(fl)
				return;
		}
	}
	mv=svmv;
}

void recursive()
{
	fl=0;
	for(mv=depth=find_min_move();depth<=120;depth++)
	{
		move=0;
		rec();
		if(fl)
			return;
	}
}

int solvable()
{
	int i,j,tot=0,k,l;

	for(i=0;i<=4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(a[i][j]==0)
			{
				tot+=i;
				continue;
			}
			l=j+1;
			for(k=i;k<4;k++)
			{
				for(;l<4;l++)
				{
					if(a[k][l]==0)
						continue;
					if(a[k][l]<a[i][j])
						tot++;
				}
				l=0;
			}
		}
	}
	if((tot&1))
		return 1;
	return 0;
}

int main_boring()
{
	int i,j,k,l;

	calculate();

	for(i=3,k = 0;i>=0;i--,k++)
		for(j=0,l = 0;j<4;j++,l++)
		{
			a[i][j] = Tnumber[k][l];
			if(a[i][j]==0)
			{
				p0.x=i;
				p0.y=j;
			}
		}
	if(solvable())
		recursive();
	for(i = 0;i<4;i++)
	{
		for(j = 0;j<4;j++)
			printf("%d ",a[i][j]);
		puts("");
	}

	return 0;
}

void generateRandom15Number()
{
	int i,j,k,l,n,temp[16];

	while(true)
	{
		for(i = 0;i<=15;i++)
			temp[i] = 0;
		for(i = 0;i<4;i++)
		{
			for(j = 0;j<4;j++)
			{
				while(1)
				{
					n = Random();
					n %= 16;
					if(!temp[n])
					{
						Tnumber[i][j] = n;
						temp[n] = 1;
						break;
					}
				}
			}
		}
		for(i=3,k = 0;i>=0;i--,k++)
			for(j=0,l = 0;j<4;j++,l++)
			{
				a[i][j] = Tnumber[k][l];

			}
		if(solvable())
			break;
	}
}


void newGame(int option)
{
	if(option==1)
	{
		generateRandom15Number();
		time(&time1);
		print = true;
		xcnt = 0;
		glutPostRedisplay();
	}
	else if(option==2)
	{
		main_boring();
	}
}


int main(int argc, char **argv)
{
	generateRandom15Number();
	time(&time1);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("15-Puzzle By Mohsin");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutCreateMenu(newGame);
	glutAddMenuEntry("New Game", 1);
	glutAddMenuEntry("I m Boring", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMotionFunc(MouseMotion);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialFunction);
	glutIdleFunc(display);
	glutMainLoop();
	return 0;
}
