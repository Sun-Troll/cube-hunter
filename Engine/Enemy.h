#pragma once

#include "Graphics.h"

class Enemy
{
public:
	static constexpr int width = 21;
	static constexpr int height = 21;
	void ClampScreen();
	void Move();
	void SetV(bool right, bool left, bool down, bool up);
	void Damage();
	bool Destruction(int x_p, int y_p, int width_s, int height_s, int shield_state, int shield_damage);
	void ColorSet();
	void Respawn(int state_rng, int start_pos);
	void Reset();
	int GetX() const;
	int GetY() const;
	int GetHp() const;
	Color GetC() const;
private:
	bool move = true;
	int x = 600;
	int y = 300;
	int vx = 0;
	int vy = 0;
	const int vaBase = 10;
	int va[4];
	const int vMax = 10;
	const int hpMax = 2000;
	int hp = hpMax;
	const int dif = 10;
	int state = 0;
	const int redMultHp = 2;
	const int greenAccMult = 2;
	const int blueMaxSpeedMult = 2;
	Color c = { 200, 100, 100 };
};