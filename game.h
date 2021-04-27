#pragma once
#include <string>
#include <vector>
using namespace std;

class GameObject;
class Player;

class Home {
public:
	Home(int x, int y) : x(x), y(y) {}
	int x;
	int y;
};

class GameWorld {
public:
	void print_world();
	GameObject* find_position(int x, int y);
	Home* find_home(int x, int y);
	template <typename T>
	void add_object(int x, int y);
	void add_home(int x, int y);
	bool is_complete();
	bool move_left();
	bool move_right();
	bool move_up();
	bool move_down();
private:
	Player* get_player();
	vector<GameObject*> object;
	vector<Home> home;
};

template<typename T>
void GameWorld::add_object(int x, int y)
{
	if (find_position(x, y)) {
		throw "이미 있음";
	}
	object.push_back(new T(*this, x, y));
}

class GameObject {
public:
	virtual string draw_object() = 0;
	virtual bool is_pushable(int newx, int newy) = 0;
private:
	int x;
	int y;
protected:
	GameObject(GameWorld& world, int x, int y);
	GameWorld& world;

	friend class GameWorld;
};

class Player: public GameObject  {
public:
	virtual string draw_object();
	virtual bool is_pushable(int newx, int newy);
	Player(GameWorld& world, int x, int y);
};

class Ball : public GameObject {
public:
	virtual string draw_object();
	virtual bool is_pushable(int newx, int newy);
	Ball(GameWorld& world, int x, int y);
};

class Wall : public GameObject {
public:
	virtual string draw_object();
	virtual bool is_pushable(int newx, int newy);
	Wall(GameWorld& world, int x, int y);
};
