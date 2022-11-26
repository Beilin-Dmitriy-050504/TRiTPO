#include "Header.h"
#include <iostream> 

bool testMoveDown() {
	short X[4] = { 3,3,3,3 };
	short Y1[4] = { 8,7,6,5 };
	short Y2[4] = { 9,8,7,6 };
	Block expectedBlock(X, Y2, 0, 0);
	Block block(X, Y1, 0, 0);
	block.MoveDown();
	return block == expectedBlock;
}
bool testMoveDownWall() {
	short X[4] = { 0,0,0,0 };
	short Y[4] = { 23,22,21,20 };

	Block initWall(X, Y, 1, 0);
	Game game;
	game.SetField(initWall);

	short Y2[4] = { 19,18,17,16 };

	Block block(X, Y2, 1, 0);
	block.MoveDown();

	return !game.check(block);
}
bool testMoveLeft() {
	short X1[4] = { 3,3,3,3 };
	short Y[4] = { 8,7,6,5 };
	short X2[4] = { 2,2,2,2 };
	Block expectedBlock(X2, Y, 0, 0);
	Block block(X1, Y, 0, 0);
	block.SetDx(-1);
	block.MoveDxBlock();
	return block == expectedBlock;
}
bool testMoveRight() {
	short X1[4] = { 3,3,3,3 };
	short Y[4] = { 8,7,6,5 };
	short X2[4] = { 4,4,4,4 };
	Block expectedBlock(X2, Y, 0, 0);
	Block block(X1, Y, 0, 0);
	block.SetDx(1);
	block.MoveDxBlock();
	return block == expectedBlock;
}
bool testMoveLeftWall() {
	short X[4] = { 0,0,0,0 };
	short Y[4] = { 8,7,6,5 };
	Block block(X, Y, 0, 0);
	block.SetDx(-1);
	block.MoveDxBlock();
	Game game;
	return !game.check(block);
}
bool testMoveRightWall() {
	short X[4] = { 9,9,9,9 };
	short Y[4] = { 8,7,6,5 };
	Block block(X, Y, 0, 0);
	block.SetDx(1);
	block.MoveDxBlock();
	Game game;
	return !game.check(block);
}
bool testRotate() {
	short X1[4] = { 3,3,3,3 };
	short Y1[4] = { 8,7,6,5 };
	short X2[4] = { 2,3,4,5 };
	short Y2[4] = { 7,7,7,7 };

	Block expectedBlock(X2, Y2, 0, 0);
	Block block(X1, Y1, 0, 0);
	block.SetRotate(true);
	block.Rotation();

	return block == expectedBlock;
}
bool testRotateWall() {
	short X[4] = { 9,9,9,9 };
	short Y[4] = { 8,7,6,5 };

	Block block(X, Y, 0, 0);
	block.SetRotate(true);
	block.Rotation();
	Game game;
	return !game.check(block);
}
bool testAddScore(int lineCnt, int expectedScore) {
	Game game;
	return game.addScore(lineCnt) == expectedScore;
	
}
bool testIncTime(int lineCnt, double expectedTime) {
	Game game;
	return (int)(game.incSpeed(lineCnt) * 100) == (int)(expectedTime * 100);
}
bool testAddBlock() {
	short X[4] = { 0,0,0,0 };
	short Y[4] = { 23,22,21,20 };

	Block block(X, Y, 1, 0);
	Field field;
	field.SetField(block);

	int cnt = 0;
	for (int x = 0; x < Field::length; x++)
		for (int y = 0; y < Field::height; y++)
			if (field.GetField(y, x)) 
				cnt++;

	if (cnt != 4) return false;
	if (field.GetField(Y[0]-1, X[0]) != 1 ||
		field.GetField(Y[1]-1, X[1]) != 1 ||
		field.GetField(Y[2]-1, X[2]) != 1 ||
		field.GetField(Y[3]-1, X[3]) != 1
		) return false;

	return true;
}
bool testDeleteLines(int expectedLines) {
	Game game;
	for (int i = 0; i < Field::length; i++)
		for (int j = 0; j < expectedLines; j++)
			game.SetField(i, j + 19);
	int a;
	return game.DeleteLine() == expectedLines;
}

int main() {

	std::cout << "Move down test                     : " << (testMoveDown() ? "PASS\n" : "ERROR\n");
	std::cout << "Move down(wall) test               : " << (testMoveDownWall() ? "PASS\n" : "ERROR\n");

	std::cout << "Rotate test                        : " << (testRotate() ? "PASS\n" : "ERROR\n");
	std::cout << "Rotate(wall) test                  : " << (testRotateWall() ? "PASS\n" : "ERROR\n");

	std::cout << "Move left test                     : " << (testMoveLeft() ? "PASS\n" : "ERROR\n");
	std::cout << "Move right test                    : " << (testMoveRight() ? "PASS\n" : "ERROR\n");

	std::cout << "Move left(wall) test               : " << (testMoveLeftWall() ? "PASS\n" : "ERROR\n");
	std::cout << "Move right(wall) test              : " << (testMoveRight() ? "PASS\n" : "ERROR\n");
	  
	std::cout << "Add block test                     : " << (testAddBlock() ? "PASS\n" : "ERROR\n");

	std::cout << "Delete 0 line test                 : " << (testDeleteLines(0) ? "PASS\n" : "ERROR\n");
	std::cout << "Delete 1 line test                 : " << (testDeleteLines(1) ? "PASS\n" : "ERROR\n");
	std::cout << "Delete 2 lines test                : " << (testDeleteLines(2) ? "PASS\n" : "ERROR\n");
	std::cout << "Delete 3 lines test                : " << (testDeleteLines(3) ? "PASS\n" : "ERROR\n");
	std::cout << "Delete 4 lines test                : " << (testDeleteLines(4) ? "PASS\n" : "ERROR\n");

	std::cout << "Add score(1 line) test             : " << (testAddScore(1, 100) ? "PASS\n" : "ERROR\n");
	std::cout << "Add score(2 lines) test            : " << (testAddScore(2, 300) ? "PASS\n" : "ERROR\n");
	std::cout << "Add score(3 lines) test            : " << (testAddScore(3, 700) ? "PASS\n" : "ERROR\n");
	std::cout << "Add score(4 lines) test            : " << (testAddScore(4, 1500) ? "PASS\n" : "ERROR\n");

	std::cout << "Increase time(0 lines) test        : " << (testIncTime(0, 0.4) ? "PASS\n" : "ERROR\n");
	std::cout << "Increase time(10 lines) test       : " << (testIncTime(10, 0.37) ? "PASS\n" : "ERROR\n");
	std::cout << "Increase time(20 lines) test       : " << (testIncTime(20, 0.34) ? "PASS\n" : "ERROR\n");
	std::cout << "Increase time(30 lines) test       : " << (testIncTime(30, 0.31) ? "PASS\n" : "ERROR\n");
	std::cout << "Increase time(40 lines) test       : " << (testIncTime(40, 0.28) ? "PASS\n" : "ERROR\n");
	std::cout << "Increase time(50 lines) test       : " << (testIncTime(50, 0.25) ? "PASS\n" : "ERROR\n");
	std::cout << "Increase time(60 lines) test       : " << (testIncTime(60, 0.22) ? "PASS\n" : "ERROR\n");
	std::cout << "Increase time(70 lines) test       : " << (testIncTime(70, 0.19) ? "PASS\n" : "ERROR\n");
	std::cout << "Increase time(80 lines) test       : " << (testIncTime(80, 0.16) ? "PASS\n" : "ERROR\n");
	std::cout << "Increase time(90 lines) test       : " << (testIncTime(90, 0.13) ? "PASS\n" : "ERROR\n");
	std::cout << "Increase time(100 lines) test      : " << (testIncTime(100, 0.1) ? "PASS\n" : "ERROR\n");
	std::cout << "Increase time(>>100 lines) test    : " << (testIncTime(1100, 0.1) ? "PASS\n" : "ERROR\n");
	return 0;
}