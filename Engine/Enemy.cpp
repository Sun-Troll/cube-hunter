#include "Enemy.h"

void Enemy::ClampScreen()
{
	if (x < Graphics::ScreenWidth / 6 + 1)
	{
		x = Graphics::ScreenWidth / 6 + 1;
		vx = -vx;
	}
	if (x > Graphics::ScreenWidth - width)
	{
		x = Graphics::ScreenWidth - width;
		vx = -vx;
	}
	if (y < 0)
	{
		y = 0;
		vy = -vy;
	}
	if (y > Graphics::ScreenHeight - height)
	{
		y = Graphics::ScreenHeight - height;
		vy = -vy;
	}
}

void Enemy::Move()
{
	if (move == true)
	{
		x += vx;
		y += vy;
		move = false;
	}
	else
	{
		move = true;
	}
}

void Enemy::SetV(bool right, bool left, bool down, bool up)
{
	if (right)
	{
		if (va[0] == 0)
		{
			++vx;
			if (state == 2)
			{
				if (vx > vMax * blueMaxSpeedMult)
				{
					vx = vMax * blueMaxSpeedMult;
				}
			}
			else
			{
				if (vx > vMax)
				{
					vx = vMax;
				}
			}
			if (state == 1)
			{
				va[0] = vaBase / greenAccMult;
			}
			else
			{
				va[0] = vaBase;
			}
		}
		else
		{
			--va[0];
		}
	}
	if (left)
	{
		if (va[1] == 0)
		{
			--vx;
			if (state == 2)
			{
				if (vx < -vMax * blueMaxSpeedMult)
				{
					vx = -vMax * blueMaxSpeedMult;
				}
			}
			else
			{
				if (vx < -vMax)
				{
					vx = -vMax;
				}
			}
			if (state == 1)
			{
				va[1] = vaBase / greenAccMult;
			}
			else
			{
				va[1] = vaBase;
			}
		}
		else
		{
			--va[1];
		}
	}
	if (down)
	{
		if (va[2] == 0)
		{
			++vy;
			if (state == 2)
			{
				if (vy > vMax * blueMaxSpeedMult)
				{
					vy = vMax * blueMaxSpeedMult;
				}
			}
			else
			{
				if (vy > vMax)
				{
					vy = vMax;
				}
			}
			if (state == 1)
			{
				va[2] = vaBase / greenAccMult;
			}
			else
			{
				va[2] = vaBase;
			}
		}
		else
		{
			--va[2];
		}
	}
	if (up)
	{
		if (va[3] == 0)
		{
			--vy;
			if (state == 2)
			{
				if (vy < -vMax * blueMaxSpeedMult)
				{
					vy = -vMax * blueMaxSpeedMult;
				}
			}
			else
			{
				if (vy < -vMax)
				{
					vy = -vMax;
				}
			}
			if (state == 1)
			{
				va[3] = vaBase / greenAccMult;
			}
			else
			{
				va[3] = vaBase;
			}
		}
		else
		{
			--va[3];
		}
	}
	if (!right && !left && !down && !up)
	{
		for (int i = 0; i <= 3; ++i)
			va[i] = 0;
	}
}

void Enemy::Damage()
{
	hp -= dif;
}

bool Enemy::Destruction(int x_p, int y_p, int width_s, int height_s, int shield_state, int shield_damage)
{
	const int enemyRight = x + width;
	const int enemyBottom = y + height;
	const int playerRight = x_p + width_s;
	const int playerBottom = y_p + height_s;

	if (x < playerRight && enemyRight > x_p &&
		y < playerBottom && enemyBottom > y_p && 
		state == shield_state)
	{
		hp -= shield_damage;
		return true;
	}
	else
	{
		return false;
	}
}

void Enemy::ColorSet()
{
	int hpc = hp * 100 / hpMax;
	if (state == 0)
	{
		hpc = hpc / redMultHp;
		c = Color(200, hpc, hpc);
	}
	else if (state == 1)
	{
		c = Color(hpc, 200, hpc);
	}
	else if (state == 2)
	{
		c = Color(hpc, hpc, 200);
	}
}

void Enemy::Respawn(int state_rng, int start_pos)
{
	if (hp > 0)
	{
		if (start_pos == 0)
		{
			x = Graphics::ScreenWidth / 6 + 1;
			y = 0;
		}
		else if (start_pos == 1)
		{
			x = Graphics::ScreenWidth - width;
			y = 0;
		}
		else if (start_pos == 2)
		{
			x = Graphics::ScreenWidth / 6 + 1;
			y = Graphics::ScreenHeight - height;
		}
		else if (start_pos == 3)
		{
			x = Graphics::ScreenWidth - width;
			y = Graphics::ScreenHeight - height;
		}
	}
	state = state_rng;
	if (state == 0)
	{
		hp = hpMax * redMultHp;
	}
	else
	{
		hp = hpMax;
	}
}

void Enemy::Reset()
{
	move = true;
	x = 600;
	y = 300;
	vx = 0;
	vy = 0;
	va[4];
	hp = hpMax;
	state = 0;
}

int Enemy::GetX() const
{
	return x;
}

int Enemy::GetY() const
{
	return y;
}

int Enemy::GetHp() const
{
	return hp;
}

Color Enemy::GetC() const
{
	return c;
}
