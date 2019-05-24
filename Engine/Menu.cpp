#include "Menu.h"

void Menu::DrawStat(Graphics& gfx, int stat, int stat_div, int pos, int spacing, Color c) const
{
	if (stat / stat_div <= Graphics::ScreenWidth / 6)
	{
		gfx.DrawRectangle(0, pos, stat / stat_div, 6, c);
	}
	else if (stat / stat_div > Graphics::ScreenWidth / 6 && stat / stat_div <= 2 * Graphics::ScreenWidth / 6)
	{
		gfx.DrawRectangle(0, pos, Graphics::ScreenWidth / 6, 6, c);
		gfx.DrawRectangle(0, pos + spacing, stat / stat_div - Graphics::ScreenWidth / 6, 6, c);
	}
	else if (stat / stat_div > 2 * Graphics::ScreenWidth / 6 && stat / stat_div <= 3 * Graphics::ScreenWidth / 6)
	{
		gfx.DrawRectangle(0, pos, Graphics::ScreenWidth / 6, 6, c);
		gfx.DrawRectangle(0, pos + spacing, Graphics::ScreenWidth / 6, 6, c);
		gfx.DrawRectangle(0, pos + spacing * 2, stat / stat_div - 2 * Graphics::ScreenWidth / 6, 6, c);
	}
	else
	{
		gfx.DrawRectangle(0, pos, Graphics::ScreenWidth / 6, 6, c);
		gfx.DrawRectangle(0, pos + spacing, Graphics::ScreenWidth / 6, 6, c);
		gfx.DrawRectangle(0, pos + spacing * 2, Graphics::ScreenWidth / 6, 6, c);
		gfx.DrawRectangle(0, pos + spacing * 3, stat / stat_div - 3 * Graphics::ScreenWidth / 6, 6, c);
	}
}
