#include "Player.h"

void Player::ClampScreen()
{
	if (x < Graphics::ScreenWidth / 6 + 1)
	{
		x = Graphics::ScreenWidth - widthShield;
	}
	if (x > Graphics::ScreenWidth - widthShield)
	{
		x = Graphics::ScreenWidth / 6 + 1;
	}
	if (y < 0)
	{
		y = Graphics::ScreenHeight - heightShield;
	}
	if (y > Graphics::ScreenHeight - heightShield)
	{
		y = 0;
	}
}

void Player::Move()
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

void Player::SetV(bool right, bool left, bool down, bool up)
{
	if (right)
	{
		if (va[0] == 0)
		{
			++vx;
			if (vx > vMax)
			{
				vx = vMax;
			}
			va[0] = vaBase;
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
			if (vx < -vMax)
			{
				vx = -vMax;
			}
			va[1] = vaBase;
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
			if (vy > vMax)
			{
				vy = vMax;
			}
			va[2] = vaBase;
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
			if (vy < -vMax)
			{
				vy = -vMax;
			}
			va[3] = vaBase;
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

void Player::ShieldStateSet(bool red, bool green, bool blue)
{
	if (mp > 0 && (red || green || blue))
	{
		if (red && shieldState != 0)
		{
			shieldState = 0;
			mp -= 1000;
		}
		else if (green && shieldState != 1)
		{
			shieldState = 1;
			mp -= 1000;
		}
		else if (blue && shieldState != 2)
		{
			shieldState = 2;
			mp -= 1000;
		}
	}
}

void Player::ShieldCSet()
{
	if (shieldState == 0)
	{
		shieldC = { 255, 0, 0 };
	}
	else if (shieldState == 1)
	{
		shieldC = { 0, 255, 0 };
	}
	else if (shieldState == 2)
	{
		shieldC = { 0, 0, 255 };
	}
}

bool Player::Damage(int x_e, int y_e, int width, int height)
{
	const int playerRight = x + 76;
	const int playerBottom = y + 76;
	const int enemyRight = x_e + width;
	const int enemyBottom = y_e + height;

	if (x + 65 < enemyRight && playerRight > x_e &&
		y + 65 < enemyBottom && playerBottom > y_e
		&& hp > 0)
	{
		hp -= dif;
		return true;
	}
	else
	{
		return false;
	}
}

void Player::ShieldDamage()
{
	mp -= dif;
}

void Player::MpRegen()
{
	if (mp < mpMax)
	{
		mp += mpRegen;
		if (mp > mpMax)
		{
			mp = mpMax;
		}
	}
}

void Player::HpRefill()
{
	hp = hpMax;
}

void Player::XpSet(int enemy_num)
{
	xp += (100 * enemy_num);
	if (xp > 120000)
	{
		xp = 120000;
	}
}

void Player::Upgrade(bool va_base_up, bool v_max_up, bool hp_max_up,
	bool mp_max_up, bool mp_regen_up, bool shield_damage_up)
{
	if (va_base_up && xp > lvl * vaBaseLvl * upCost && vaBase > 2)
	{
		xp -= lvl * vaBaseLvl * upCost;
		++lvl;
		++vaBaseLvl; //16
		vaBase -= 1;
	}
	if (v_max_up && xp > lvl * vMaxLvl * upCost && vMax < 20)
	{
		xp -= lvl * vMaxLvl * upCost;
		++lvl;
		++vMaxLvl; //16
		vMax += 1;
	}
	if (hp_max_up && xp > lvl * hpMaxLvl * upCost && hpMax < 4800)
	{
		xp -= lvl * hpMaxLvl * upCost;
		++lvl;
		++hpMaxLvl; //22
		hpMax += 200;
	}
	if (mp_max_up && xp > lvl * mpMaxLvl * upCost && mpMax < 9600)
	{
		xp -= lvl * mpMaxLvl * upCost;
		++lvl;
		++mpMaxLvl; //22
		mpMax += 400;
	}
	if (mp_regen_up && xp > lvl * mpRegenLvl * upCost && mpRegen < 20)
	{
		xp -= lvl * mpRegenLvl * upCost;
		++lvl;
		++mpRegenLvl; //18
		mpRegen += 1;
	}
	if (shield_damage_up && xp > lvl * shieldDamageLvl * upCost && shieldDamage < 400)
	{
		xp -= lvl * shieldDamageLvl * upCost;
		++lvl;
		++shieldDamageLvl; //18
		shieldDamage += 20;
	}
}

void Player::Reset()
{
	x = Graphics::ScreenWidth * 0.5 + 200;
	y = Graphics::ScreenHeight * 0.5;
	move = true;
	regen = true;
	lvl = 1;
	vx = 0;
	vy = 0;
	vaBaseLvl = 1;
	vaBase = 20;
	vMaxLvl = 1;
	vMax = 4;
	hpMaxLvl = 1;
	hpMax = 400;
	hp = hpMax;
	mpMaxLvl = 1;
	mpMax = 800;
	mp = mpMax;
	mpRegenLvl = 1;
	mpRegen = 2;
	xp = 0;
	shieldDamageLvl = 1;
	shieldDamage = 40;
	shieldState = 0;
}

int Player::GetX() const
{
	return x;
}

int Player::GetY() const
{
	return y;
}

int Player::GetHp() const
{
	return hp;
}

int Player::GetHpMax() const
{
	return hpMax;
}

int Player::GetMp() const
{
	return mp;
}

int Player::GetMpMax() const
{
	return mpMax;
}

int Player::GetXp() const
{
	return xp;
}

int Player::GetState() const
{
	return shieldState;
}

int Player::GetShieldDamage() const
{
	return shieldDamage;
}

int Player::GetMpRegen() const
{
	return mpRegen;
}

int Player::GetVaBase() const
{
	return vaBase;
}

int Player::GetVMax() const
{
	return vMax;
}

Color Player::GetCoreC() const
{
	return coreC;
}

Color Player::GetShieldC() const
{
	return shieldC;
}
