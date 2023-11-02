#include "pch.h"
#include "Util/callbacks.h"
#include "Util/Engine.h"

// �׸��� �ݹ��Լ�
void renderFunc()
{
	// rendering function
	engine->Render();
}

void reshapeFunc(int x, int y)
{
	engine->ReSizeWindow(x, y);
}

void idleFunc()
{
	// Frame��ü�� Update�Լ� ���
	engine->Update();
	glutPostRedisplay();
}


void keyboardFunc(unsigned char key, int x, int y)
{
}

void keyboardUpFunc(unsigned char key, int x, int y)
{
}

void specialkeyFunc(int key, int x, int y)
{
}

void specialKeyUpFunc(int key, int x, int y)
{

}

void mouseFunc(int button, int state, int x, int y)
{

}

void mouseLeftDown(int state, int x, int y)
{
}

void mouseRightDown(int state, int x, int y)
{
}

void mouseMotion(int x, int y)
{
}

void mousePassiveMotion(int x, int y)
{
}

void mouseWheel(int dir, int x, int y)
{
}
