#include"Header.h"
#include <iostream>
#include <Windows.h>
#include <time.h>

///////////////////BLOCK////////////////////
Block::Block()
{
	SetBlock();
};
Block::Block(short* X, short* Y, short type, short dx) {
	for (int i = 0; i < 4; i++) {
		this->X[i] = X[i];
		this->Y[i] = Y[i];
	}
	this->type = type;
	this->dx = dx;
}
void Block::SetBlock()
{
	color = 1 + rand() % 7;
	type = rand() % 7;
	for (int i = 0; i < 4; i++)
	{
		X[i] = Game::BlockType[type][i] % 2 + 4;
		Y[i] = Game::BlockType[type][i] / 2;
	}
}
void Block::SetRotate(bool rotate)
{
	this->rotate = rotate;
}
void Block::SetDx(short dx)
{
	this->dx = dx;
}
void Block::MoveDxBlock()
{
	for (int i = 0; i < 4; i++)
		X[i] += dx;
}
void Block::MoveDown()
{
	for (int i = 0; i < 4; i++)
		Y[i] += 1;
}
void Block::Rotation()
{
	if (!rotate) return;

	int	tmpX = X[1];
	int	tmpY = Y[1];

	for (int i = 0; i < 4; i++) //���������� ������� ��� �������� � ���������� ������������ ���������� �����
	{
		int x = Y[i] - tmpY;
		int y = X[i] - tmpX;
		X[i] = tmpX - x;
		Y[i] = tmpY + y;
	}
	for (int i = 0; i < 4; i++)
	{
		if (X[i] < 0)
		{
			for (int j = 0; j < 4; j++) {
				X[j] += 1;
			}
			break;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (X[i] >= Field::length)
		{
			for (int j = 0; j < 4; j++) {
				X[j] -= 1;
			}
			break;
		}
	}
}
short Block::GetY(short i)
{
	return Y[i];
}
short Block::GetX(short i)
{
	return X[i];
}
short Block::GetType()
{
	return type;
}
short Block::GetColor()
{
	return color;
}
Block& Block::operator=(const Block& tmp)
{
	this->color = tmp.color;
	this->type = tmp.type;
	for (int i = 0; i < 4; i++)
	{
		this->X[i] = tmp.X[i];
		this->Y[i] = tmp.Y[i];
	}
	return *this;
}
bool Block::operator==(const Block& tmp) {
	for (int i = 0; i < 4; i++) {
		if (this->X[i] != tmp.X[i] or this->Y[i] != tmp.Y[i])
			return false;
	}
	return true;
}

///////////////////FIELD////////////////////
short Field::GetField(short i, short j)
{
	return field[i][j];
}
void Field::SetField(Block& block)
{
	for (int i = 0; i < 4; i++)
		field[block.GetY(i) - 1][block.GetX(i)] = block.GetColor();
}
void Field::SetField(short lineNumber, short j, short i)
{
	field[lineNumber][j] = field[i][j];
}

///////////////////TIMER////////////////////
void Timer::AddTime()
{
	this->time += this->getElapsedTime().asSeconds();
	this->sf::Clock::restart();
}
void Timer::ResetTime()
{
	this->time = 0;
}
void Timer::SetDelay()
{
	this->delay = this->cur_delay;
}
void Timer::SetDelay(double time)
{
	this->delay = time;
}
void Timer::CurDelay(double time)
{
	this->cur_delay = time;
}
bool Timer::RequiredTime()
{
	if (this->time > this->delay) return true;
	return false;
}
double Timer::GetDelay()
{
	return delay;
}
double Timer::GetTime()
{
	return this->time;
}

///////////////////GAME////////////////////
short Game::BlockType[7][4] = {
	1,3,5,7, // ������ �����
	2,4,5,7, // ������ ������
	3,5,4,6, // ������ �����
	3,5,4,7, // ����� �
	2,3,5,7, // ����� � ������� �����
	3,5,7,6, // ����� � ������� ������
	2,3,4,5, // ���������
};
int Game::GetScore()
{
	return Score;
}
void Game::SetField(Block& block)
{
	this->field.SetField(block);
}
void Game::SetDelay()
{
	this->timer.SetDelay();
}
void Game::SetDelay(double time)
{
	this->timer.SetDelay(time);
}
void Game::AddTime()
{
	this->timer.AddTime();
}
void Game::ResetTime()
{
	this->timer.ResetTime();
}
void Game::DeleteLine()
{
	short LineCnt = 0;
	short lineNumber = Field::height - 1;
	for (int i = Field::height - 1; i >= 0; i--)
	{
		short cnt = 0;
		for (int j = 0; j < Field::length; j++)
		{
			if (this->field.GetField(i, j)) cnt++;    //�������������� ���������� ������ � �����
			this->field.SetField(lineNumber, j, i); //� k-�� ������ �������������� i-��, ���������� i = k,
		}
		if (cnt < Field::length)
		{
			lineNumber--;  //���� ������ �� ��������� ������ k ����������� ��� � i
			 //��, ���� ������ ������ k �� ��������� ��� i, � �������� ���������� ������� ����� � ������
		}
		else
		{
			LineCnt++;
			Lines++;
		}
	}
	addScore(LineCnt);
	incSpeed(LineCnt);
}
void Game::addScore(int LineCnt) {
	switch (LineCnt){
		case 0: break;
		case 1: Score += 100; break;
		case 2: Score += 300; break;
		case 3: Score += 700; break;
		case 4: Score += 1500; break;
	}
}
void Game::incSpeed(int LineCnt) {
	if (!LineCnt) return;

	double baseSpeed = 0.4;
	double speedPerLevel = 0.03;

	int level = this->Lines / 10;
	if (level > 10) level = 10;

	this->timer.CurDelay(baseSpeed - (double)(speedPerLevel * level));
}
short Game::GetField(short i, short j)
{
	return this->field.GetField(i, j);
}
short Game::GetLines()
{
	return Lines;
}
bool Game::check(Block& tmp)
{
	for (int i = 0; i < 4; i++) //�������� ���� 4 ������� ����� (���������)
	{
		if (tmp.GetX(i) < 0 || tmp.GetX(i) >= Field::length || tmp.GetY(i) >= Field::height) return 0;
		else if (this->field.GetField(tmp.GetY(i), tmp.GetX(i))) return 0;
	}
	return  1;//� ������ ������ �������� ��������
}
bool Game::RequiredTime()
{
	return this->timer.RequiredTime();
}
bool Game::EndGame()
{
	for (int i = 0; i < Field::length; i++)
		if (this->field.GetField(3, i)) return true;
	return false;
}
double Game::GetDelay()
{
	return this->timer.GetDelay();
}