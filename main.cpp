#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstdlib>
#include "game.h"
using namespace std;

void make_map(GameWorld& world) {
	int map[9][9] = {
		{3,3,3,3,3,0,0,0,0},
		{3,1,0,0,3,0,0,0,0},
		{3,0,2,2,3,0,3,3,3},
		{3,0,2,0,3,0,3,4,3},
		{3,3,3,0,3,3,3,4,3},
		{0,3,3,0,0,0,0,4,3},
		{0,3,0,0,0,3,0,0,3},
		{0,3,0,0,0,3,3,3,3},
		{0,3,3,3,3,3,0,0,0},
	};
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			switch (map[y][x]) {
			case 1:
				world.add_object<Player>(x, y);
				break;
			case 2:
				world.add_object<Ball>(x, y);
				break;
			case 3:
				world.add_object<Wall>(x, y);
				break;
			case 4:
				world.add_home(x, y);
				break;
			}
		}
	}
}
int main() {
	int movecnt=0;
	GameWorld world;
	try {
		make_map(world);
	}
	catch (const char* e) {
		cout << e;
		return 1;
	}

	while (!world.is_complete()) {
		system("cls");
		world.print_world();
		while (_getch() != 224);
		int c = _getch();
		movecnt++;
		switch (c) {
		case 72:// ↑
			world.move_up();
			break;
		case 80:// ↓
			world.move_down();
			break;
		case 75:// ←
			world.move_left();
			break;
		case 77:// →
			world.move_right();
			break;
		}
	}
	system("cls");
	world.print_world();
	cout << "성공" << endl << "움직인 횟수:" << movecnt << endl;
	cout << "이름을 입력하세요: ";
	string name;
	cin >> name;
	ofstream fout;
	fout.open("ranking.txt", fstream::out | fstream::app);
	fout << movecnt << " " << name << endl;
	fout.close();
	ifstream fin("ranking.txt");
	while (fin >> movecnt >> name) {
		cout << movecnt << " " << name << endl;
	}
}
