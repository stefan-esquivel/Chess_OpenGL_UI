
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

struct Pawn
{
	int x;
	int y;
	char color[6];

};
struct Bishop
{
	int x;
	int y;
	char color[6];

};
struct Rook
{
	int x;
	int y;
	char color[6];

};
struct Knight
{
	int x;
	int y;
	char color[6];

};

struct Queen
{
	int x;
	int y;
	char color[6];

};

struct King
{
	int x;
	int y;
	char color[6];

};

GLuint tex;

void setup() 
{   
	glClearColor(0.0, 0.0, 0.0, 0.0); 
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void drawString(float x, float y, char* string)
{
	glRasterPos2f(x,y);

	for(char* c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}

}

void drawCircle(int x, int y, int radius)
{
	float nTang = 500;
	glBegin(GL_POLYGON);
	for(float i = 0; i < nTang; i++)
	{
		glVertex2f((x + radius + (radius * cos((i * M_PI)/(nTang/2.0)))), (y - radius + (radius*sin((i * M_PI)/(nTang/2.0)))));
	}
	glEnd();
}

void lineCircle(int x, int y, int radius)
{
	float nTang = 500;
	glLineWidth(0.1); 
	glBegin(GL_LINE_LOOP);
	for(float i = 0; i < nTang; i++)
	{
		glVertex2f((x + radius + (radius * cos((i * M_PI)/(nTang/2.0)))), (y - radius + (radius*sin((i * M_PI)/(nTang/2.0)))));
	}
	glEnd();
}

void drawSemiCircle(int x, int y, int radius)
{
	float nTang = 500;
	glBegin(GL_POLYGON);
	for(float i = 0; i < nTang; i++)
	{
		glVertex2f((x + radius + (radius * cos((i * M_PI)/nTang))), (y - radius + (radius*sin((i * M_PI)/nTang))));
	}
	glEnd();
}

void lineSemiCircle(int x, int y, int radius)
{
	float nTang = 500;
	glLineWidth(0.1); 
	glBegin(GL_LINE_LOOP);
	for(float i = 0; i < nTang; i++)
	{
		glVertex2f((x + radius + (radius * cos((i * M_PI)/nTang))), (y - radius + (radius*sin((i * M_PI)/nTang))));
	}
	glEnd();
}

void drawRectangle(int x, int y, int width, int height)
{
	glLineWidth(0.1); 
	glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x, y - height);
    glVertex2f(x + width, y - height);
    glVertex2f(x + width, y);
	glEnd();
}

void fillRectangle(int x, int y, int width, int height)
{ 
	glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(x, y);
    glTexCoord2f(0, 1);
    glVertex2f(x, y - height);
    glTexCoord2f(1, 1);
    glVertex2f(x + width, y - height);
    glTexCoord2f(1, 0);
    glVertex2f(x + width, y);
	glEnd();
}

void drawLine(int x, int y, int x1, int y1)
{
	glLineWidth(0.1);
	glBegin(GL_LINES);
	glVertex2f(x, y);
	glVertex2f(x1, y1);
	glEnd();

}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 925, 0, 540);
	glMatrixMode(GL_MODELVIEW);
	glFlush();
}

void setTexture(char color[], char type[])
{
	SDL_Surface *surface;

	if(!strcmp(color, "WHITE"))
	{
		if(!strcmp(type, "Pawn"))
		{
			
			surface = IMG_Load("chessPNG/Chess_plt60.png");
		}
		else if(!strcmp(type, "Knight"))
		{
			surface = IMG_Load("chessPNG/Chess_nlt60.png");
		}
		else if(!strcmp(type, "Bishop"))
		{
			surface = IMG_Load("chessPNG/Chess_blt60.png");
		}
		else if(!strcmp(type, "Rook"))
		{
			surface = IMG_Load("chessPNG/Chess_rlt60.png");
		}
		else if(!strcmp(type, "Queen"))
		{
			surface = IMG_Load("chessPNG/Chess_qlt60.png");
		}
		else if(!strcmp(type, "King"))
		{
			surface = IMG_Load("chessPNG/Chess_klt60.png");
		}
	}
	else if(!strcmp(color, "BLACK"))
	{
		if(!strcmp(type, "Pawn"))
		{
			surface = IMG_Load("chessPNG/Chess_pdt60.png");
		}
		else if(!strcmp(type, "Knight"))
		{
			surface = IMG_Load("chessPNG/Chess_ndt60.png");
		}
		else if(!strcmp(type, "Bishop"))
		{
			surface = IMG_Load("chessPNG/Chess_bdt60.png");
		}
		else if(!strcmp(type, "Rook"))
		{
			surface = IMG_Load("chessPNG/Chess_rdt60.png");
		}
		else if(!strcmp(type, "Queen"))
		{
			surface = IMG_Load("chessPNG/Chess_qdt60.png");
		}
		else if(!strcmp(type, "King"))
		{
			surface = IMG_Load("chessPNG/Chess_kdt60.png");
		}
	}
	

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 60, 60, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface-> pixels);
    
    SDL_FreeSurface(surface);
    
}
void drawTexture(int x, int y)
{
	glBindTexture(GL_TEXTURE_2D, tex);
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 1); 
    glVertex2f(x, y - 60);
    glTexCoord2f(1, 1); 
    glVertex2f(x + 60, y - 60);
    glTexCoord2f(1, 0); 
    glVertex2f(x + 60, y);
    glTexCoord2f(0, 0);
    glVertex2f(x, y);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void drawPiece(int x, int y, char color[], char type[])
{
	setTexture(color, type);
	drawTexture(x, y);
}


void populatePawns()
{
	struct Pawn myPawns[16];
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(i == 0)
			{
				strcpy(myPawns[(8 * i) + j].color, "BLACK");
			}
			else
			{
				strcpy(myPawns[(8 * i) + j].color, "WHITE");
			}
			myPawns[(8 * i) + j].x = 30 + (60 * j);
			myPawns[(8 * i) + j].y = 450 - (300 * i);
			drawPiece(myPawns[(8 * i) + j].x, myPawns[(8 * i) + j].y, myPawns[(8 * i) + j].color, "Pawn");
		}
	}	
}

void populateRooks()
{
	struct Rook myRooks[4];
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			if(i == 0)
			{
				strcpy(myRooks[(2 * i) + j].color, "BLACK");
			}
			else
			{
				strcpy(myRooks[(2 * i) + j].color, "WHITE");
			}
			myRooks[(2 * i) + j].x = 30 + (420 * j);
			myRooks[(2 * i) + j].y = 510 - (420 * i);
			drawPiece(myRooks[(2 * i) + j].x, myRooks[(2 * i) + j].y, myRooks[(2 * i) + j].color, "Rook");
		}
	}	
}

void populateKnights()
{
	struct Knight myKnights[4];
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			if(i == 0)
			{
				strcpy(myKnights[(2 * i) + j].color, "BLACK");
			}
			else
			{
				strcpy(myKnights[(2 * i) + j].color, "WHITE");
			}
			myKnights[(2 * i) + j].x = 90 + (300 * j);
			myKnights[(2 * i) + j].y = 510 - (420 * i);
			drawPiece(myKnights[(2 * i) + j].x, myKnights[(2 * i) + j].y, myKnights[(2 * i) + j].color, "Knight");
		}
	}	
}

void populateBishops()
{
	struct Bishop myBishops[4];
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			if(i == 0)
			{
				strcpy(myBishops[(2 * i) + j].color, "BLACK");
			}
			else
			{
				strcpy(myBishops[(2 * i) + j].color, "WHITE");
			}
			myBishops[(2 * i) + j].x = 150 + (180 * j);
			myBishops[(2 * i) + j].y = 510 - (420 * i);
			drawPiece(myBishops[(2 * i) + j].x, myBishops[(2 * i) + j].y, myBishops[(2 * i) + j].color, "Bishop");
		}
	}	
}

void populateQueens()
{
	struct Queen myQueens[2];

	strcpy(myQueens[0].color, "BLACK");
	myQueens[0].x = 210;
	myQueens[0].y = 510;

	strcpy(myQueens[1].color, "WHITE");
	myQueens[1].x = 210;
	myQueens[1].y = 90;

	drawPiece(myQueens[0].x, myQueens[0].y, myQueens[0].color, "Queen");
	drawPiece(myQueens[1].x, myQueens[1].y, myQueens[1].color, "Queen");
}

void populateKings()
{
	struct King myKings[2];

	strcpy(myKings[0].color, "BLACK");
	myKings[0].x = 270;
	myKings[0].y = 510;

	strcpy(myKings[1].color, "WHITE");
	myKings[1].x = 270;
	myKings[1].y = 90;

	drawPiece(myKings[0].x, myKings[0].y, myKings[0].color, "King");
	drawPiece(myKings[1].x, myKings[1].y, myKings[1].color, "King");
}

void drawChessBoard()
{

	char str[2];

	
    glColor3f(35.0/255.0,203.0/255.0, 224.0/255.0);

    fillRectangle(0, 540, 540, 540);
    
    glColor3f(1.0, 1.0, 1.0);

    for(int i = 0; i < 8 ; i++)
    {
    	for(int j = i % 2; j < 8 ; j += 2)
    	{
    		fillRectangle(30 + (j * 60), 510 - (60 * i), 60, 60);
      	}
 		
    }
	
    drawRectangle(30, 510, 480, 480);
	
	for(int i = 10; i <= 520; i += 510)
	{
		for(int j = 1; j <= 8; j++)
		{
			sprintf(str, "%d", j);
		    drawString(i, 53 + (60 * (j - 1)), str);
		}
		
	}
	
	for(int i = 520; i >= 10; i -= 510)
	{
		for(int j = 97; j <= 104; j++)
		{
			sprintf(str, "%c", (char)j);
			drawString(55 + (60 * (j - 97)), i, str);
		}
	}
	populatePawns();
	populateRooks();
	populateKnights();
	populateBishops();
	populateQueens();
	populateKings();
	//drawPawn();
	//drawBishop(700, 200, 58, "BLACK");
	//populatePawns();

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    drawChessBoard();
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(925, 540);
    glutCreateWindow("Chess");
    glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);

    setup();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}