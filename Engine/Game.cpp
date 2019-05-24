/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	rng(rd()),
	startPos(0,3),
	stateDist(0,2)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (player0.GetHp() > 0)
	{
		bool right = false;
		bool left = false;
		bool down = false;
		bool up = false;
		if (wnd.kbd.KeyIsPressed('D'))
		{
			right = true;
		}
		if (wnd.kbd.KeyIsPressed('A'))
		{
			left = true;
		}
		if (wnd.kbd.KeyIsPressed('S'))
		{
			down = true;
		}
		if (wnd.kbd.KeyIsPressed('W'))
		{
			up = true;
		}
		player0.SetV(right, left, down, up);
		player0.Move();
		player0.ClampScreen();
		player0.MpRegen();
		bool red = false;
		bool green = false;
		bool blue = false;
		if (wnd.kbd.KeyIsPressed('1'))
		{
			red = true;
		}
		if (wnd.kbd.KeyIsPressed('2'))
		{
			green = true;
		}
		if (wnd.kbd.KeyIsPressed('3'))
		{
			blue = true;
		}
		player0.ShieldStateSet(red, green, blue);
		player0.ShieldCSet();
	}

	roundOver = true;

	for (int i = 0; i < enemySpawnNum; ++i)
	{
		if (enemy[i].GetHp() > 0)
		{
			roundOver = false;
			bool right = false;
			bool left = false;
			bool down = false;
			bool up = false;
			if (enemy[i].GetX() + 10 < player0.GetX() + 71)
			{
				right = true;
			}
			if (enemy[i].GetX() + 10 > player0.GetX() + 71)
			{
				left = true;
			}
			if (enemy[i].GetY() + 10 < player0.GetY() + 71)
			{
				down = true;
			}
			if (enemy[i].GetY() + 10 > player0.GetY() + 71)
			{
				up = true;
			}
			enemy[i].SetV(right, left, down, up);
			enemy[i].Move();
			enemy[i].ClampScreen();

			if (player0.Damage(enemy[i].GetX(), enemy[i].GetY(), enemy[i].width, enemy[i].height))
			{
				enemy[i].Damage();
			}
			if (player0.GetMp() > 0)
			{
				if (enemy[i].Destruction(player0.GetX(), player0.GetY(), player0.widthShield, player0.heightShield,
					player0.GetState(), player0.GetShieldDamage()))
				{
					player0.ShieldDamage();
				}
			}
			enemy[i].ColorSet();
		}
	}

	if (!roundOver)
	{
		getxp = true;
	}
	else if (getxp && roundOver)
	{
		player0.XpSet(enemySpawnNum);
		getxp = false;
	}
	if (roundOver)
	{
		bool vaBaseUp = false;
		bool vMaxUp = false;
		bool hpMaxUp = false;
		bool mpMaxUp = false;
		bool mpRegenUp = false;
		bool shieldDamageUp = false;

		if (wnd.kbd.KeyIsPressed('6'))
		{
			if (!inhibitUpgrade)
			{
				vaBaseUp = true;
			}
			inhibitUpgrade = true;
		}
		else if (wnd.kbd.KeyIsPressed('7'))
		{
			if (!inhibitUpgrade)
			{
				vMaxUp = true;
			}
			inhibitUpgrade = true;
		}
		else if (wnd.kbd.KeyIsPressed('0'))
		{
			if (!inhibitUpgrade)
			{
				hpMaxUp = true;
			}
			inhibitUpgrade = true;
		}
		else if (wnd.kbd.KeyIsPressed('9'))
		{
			if (!inhibitUpgrade)
			{
				mpMaxUp = true;
			}
			inhibitUpgrade = true;
		}
		else if (wnd.kbd.KeyIsPressed('8'))
		{
			if (!inhibitUpgrade)
			{
				mpRegenUp = true;
			}
			inhibitUpgrade = true;
		}
		else if (wnd.kbd.KeyIsPressed('5'))
		{
			if (!inhibitUpgrade)
			{
				shieldDamageUp = true;
			}
			inhibitUpgrade = true;
		}
		else
		{
			inhibitUpgrade = false;
		}
		player0.Upgrade(vaBaseUp, vMaxUp, hpMaxUp, mpMaxUp, mpRegenUp, shieldDamageUp);
	}
	if (roundOver && wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		++enemySpawnNum;
		for (int i = 0; i < enemySpawnNum; ++i)
		{
			player0.HpRefill();
			enemy[i].Respawn(stateDist(rng), startPos(rng));
		}
	}
	if (!roundOver && player0.GetHp() <= 0 && wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		player0.Reset();
		for (int i = 0; i < enemySpawnNum; ++i)
		{
			enemy[i].Reset();
		}
		enemySpawnNum = 0;
	}
}

void Game::ComposeFrame()
{
	gfx.DrawRectangle(Graphics::ScreenWidth / 6, 0, 1, Graphics::ScreenHeight, Colors::White);
	if (roundOver)
	{
		gfx.DrawRectangle(125, 840, 50, 50, Colors::Yellow);
	}

	menu.DrawStat(gfx, 4800, 4, 40, 20, { 100,0,100 });
	menu.DrawStat(gfx, player0.GetHpMax(), 4, 40, 20, { 255,0,255 });
	menu.DrawStat(gfx, player0.GetHp(), 4, 40, 20, Colors::Green);
	menu.DrawStat(gfx, 9600, 8, 140, 20, { 100, 100, 0});
	menu.DrawStat(gfx, player0.GetMpMax(), 8, 140, 20, { 255, 255, 0 });
	menu.DrawStat(gfx, player0.GetMp(), 8, 140, 20, Colors::Blue);
	menu.DrawStat(gfx, 20 * 60, 1, 240, 20, { 0, 60, 100 });
	menu.DrawStat(gfx, player0.GetMpRegen() * 60, 1, 240, 20, { 0, 153, 255 });
	menu.DrawStat(gfx, 20 * 60, 1, 340, 20, { 100, 60, 0 });
	menu.DrawStat(gfx, player0.GetVMax() * 60, 1, 340, 20, { 255, 153, 0 });
	menu.DrawStat(gfx, (22 - 2) * 60, 1, 440, 20, { 60, 100, 0 });
	menu.DrawStat(gfx, (22 - player0.GetVaBase()) * 60, 1, 440, 20, { 153, 255, 0 });
	menu.DrawStat(gfx, 400 * 3, 1, 540, 20, { 100 , 0 , 60 });
	menu.DrawStat(gfx, player0.GetShieldDamage() * 3, 1, 540, 20, { 255 , 0 , 153 });
	menu.DrawStat(gfx, 120000, 100, 640, 20, { 0, 255, 255 });
	menu.DrawStat(gfx, player0.GetXp(), 100, 640, 20, Colors::Red);

	if (player0.GetHp() > 0)
	{
		gfx.DrawRectangle(player0.GetX(), player0.GetY(), player0.widthShield, player0.heightShield, player0.GetShieldC());
		gfx.DrawRectangle(player0.GetX() + 65, player0.GetY() + 65, player0.widthBody, player0.heightBody, player0.GetCoreC());
	}

	for (int i = 0; i < enemySpawnNum; ++i)
	{
		if (enemy[i].GetHp() <= 0)
		{
			gfx.DrawRectangle(enemy[i].GetX(), enemy[i].GetY(), enemy[i].width, enemy[i].height, Colors::Gray);
		}
	}
	for (int i = 0; i < enemySpawnNum; ++i)
	{
		if (enemy[i].GetHp() > 0)
		{
			gfx.DrawRectangle(enemy[i].GetX(), enemy[i].GetY(), enemy[i].width, enemy[i].height, enemy[i].GetC());
		}
	}
	
}
