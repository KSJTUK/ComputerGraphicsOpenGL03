#pragma once

// �׸��� �ݹ��Լ�
void renderFunc();

// ������ ������ ���� ó�� �Լ�
void reshapeFunc(int, int);

// idle time �Լ�
void idleFunc();

// Ű���� �Է�ó�� �Լ�
void keyboardFunc(unsigned char, int, int);
void keyboardUpFunc(unsigned char, int, int);

// Ű���� Ư��Ű ó���Լ�
void specialkeyFunc(int, int, int);
void specialKeyUpFunc(int key, int x, int y);

// ���콺 �Է� ó���Լ�
void mouseFunc(int, int, int, int);
void mouseLeftDown(int, int, int);
void mouseRightDown(int, int, int);

// ���콺 ����Լ�
void mouseMotion(int, int);
void mousePassiveMotion(int, int);

// ���콺 �� �Է��Լ�
void mouseWheel(int, int, int);