#include <iostream>
#include <string>
#include "game.h"

using namespace std;

bool is_ball(GameObject* object) {
	Ball* ball = dynamic_cast<Ball*>(object);
	return ball != nullptr;
}

void GameWorld::print_world()
{
	for (int y = 0; y < 20; y++) {
		for (int x = 0; x < 20; x++) {
			GameObject* object = find_position(x, y);
			Home* home = find_home(x, y);
			if (object) {
				if (is_ball(object) && home) {
					cout << "▲";
				}
				else {
					cout << object->draw_object();
				}
			}
			else if (home) {
				cout << "△";
			}
			else {
				cout << "□";
			}
		}
		cout << endl;
	}
}

GameObject* GameWorld::find_position(int x, int y)
{
	for (int i = 0; i < object.size(); i++) {
		if (object[i]->x == x && object[i]->y == y) {
			return object[i];
		}
	}

	return nullptr;
}

Home* GameWorld::find_home(int x, int y)
{
	for (int i = 0; i < home.size(); i++) {
		if (home[i].x == x && home[i].y == y) {
			return &home[i];
		}
	}
	return nullptr;
}

void GameWorld::add_home(int x, int y)
{
	if (find_home(x, y)) {
		throw "이미 있음";
	}
	home.push_back(Home(x, y));
}

bool GameWorld::is_complete()
{
	for (int i = 0; i < home.size(); i++) {
		GameObject* object = find_position(home[i].x, home[i].y);
		if (!is_ball(object)) {
			return false;
		}
	}
	return true;
}

bool GameWorld::move_left()
{
	Player* player = get_player();
	GameObject* object = find_position(player->x - 1, player->y);
	if (object) {
		if (!object->is_pushable(player->x - 2, player->y)) {
			return false;
		}
		object->x -= 1;
	}
	player->x -= 1;
	return true;
}

bool GameWorld::move_right()
{
	Player* player = get_player();
	GameObject* object = find_position(player->x + 1, player->y);
	if (object) {
		if (!object->is_pushable(player->x + 2, player->y)) {
			return false;
		}
		object->x += 1;
	}
	player->x += 1;
	return true;
}

bool GameWorld::move_up()
{
	Player* player = get_player();
	GameObject* object = find_position(player->x, player->y-1);
	if (object) {
		if (!object->is_pushable(player->x, player->y-2)) {
			return false;
		}
		object->y -= 1;
	}
	player->y -= 1;
	return true;
}

bool GameWorld::move_down()
{
	Player* player = get_player();
	GameObject* object = find_position(player->x, player->y+1);
	if (object) {
		if (!object->is_pushable(player->x, player->y+2)) {
			return false;
		}
		object->y += 1;
	}
	player->y += 1;
	return true;
}

Player* GameWorld::get_player()
{
	for (int i = 0; i < object.size(); i++) {
		Player* player = dynamic_cast<Player*>(object[i]);
		if (player) {
			return player;
		}
	}

	return nullptr;
}

GameObject::GameObject(GameWorld& world, int x, int y) : world(world), x(x), y(y)
{

}

Player::Player(GameWorld& world, int x, int y) : GameObject(world, x, y)
{

}

string Player::draw_object()
{
	return "★";
}

bool Player::is_pushable(int newx, int newy)
{
	return false;
}

Ball::Ball(GameWorld& world, int x, int y) : GameObject(world, x, y)
{

}

string Ball::draw_object()
{
	return "●";
}

bool Ball::is_pushable(int newx, int newy)
{
	if (world.find_position(newx, newy)) {
		return false;
	}
	return true;
}

Wall::Wall(GameWorld& world, int x, int y) : GameObject(world, x, y)
{

}

string Wall::draw_object()
{
	return "■";
}

bool Wall::is_pushable(int newx, int newy)
{
	return false;
}
