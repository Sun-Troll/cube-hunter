#pragma once
#include "Graphics.h"

class Player
{
public:
	static constexpr int widthBody = 11;
	static constexpr int heightBody = 11;
	static constexpr int widthShield = 141;
	static constexpr int heightShield = 141;
	void ClampScreen();
	void Move();
	void SetV(bool right, bool left, bool down, bool up);
	void ShieldStateSet(bool red, bool green, bool blue);
	void ShieldCSet();
	bool Damage(int x_e, int y_e, int width, int height);
	void ShieldDamage();
	void MpRegen();
	void HpRefill();
	void XpSet(int enemy_num);
	void Upgrade(bool va_base_up, bool v_max_up, bool hp_max_up,
		bool mp_max_up, bool mp_regen_up, bool shield_damage_up);
	void Reset();
	int GetX() const;
	int GetY() const;
	int GetHp() const;
	int GetHpMax() const;
	int GetMp() const;
	int GetMpMax() const;
	int GetXp() const;
	int GetState() const;
	int GetShieldDamage() const;
	int GetMpRegen() const;
	int GetVaBase() const;
	int GetVMax() const;
	Color GetCoreC() const;
	Color GetShieldC() const;
private:
	int x = Graphics::ScreenWidth * 0.5 + 200;
	int y = Graphics::ScreenHeight * 0.5;
	bool move = true;
	bool regen = true;
	int lvl = 1;
	const int upCost = 40;
	int vx = 0;
	int vy = 0;
	int vaBaseLvl = 1;
	int vaBase = 20;
	int va[4];
	int vMaxLvl = 1;
	int vMax = 4;
	int hpMaxLvl = 1;
	int hpMax = 400;
	int hp = hpMax;
	const int dif = 10;
	int mpMaxLvl = 1;
	int mpMax = 800;
	int mp = mpMax;
	int mpRegenLvl = 1;
	int mpRegen = 2;
	int xp = 0;
	int shieldDamageLvl = 1;
	int shieldDamage = 40;
	int shieldState = 0;
	Color coreC = { 255, 255, 255 };
	Color shieldC = { 255, 0, 0 };
};