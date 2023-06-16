#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <cmath>
#include <string>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "../Game/Character.h"
#include "../Game/boss.h"
#include "../Game/Enemy.h"
#include "../Game/CutmanStage.h"
#include "../Game/firemanStage.h"
#include "mygame.h"

using namespace game_framework;
int CGameStateOver::clear = 0;
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g): CGameState(g)
{
}
void CGameStateOver::OnInit()
{

	ShowInitProgress(66, "Initialize...");	// 接個前一個狀態的進度，此處進度視為66%
	//
	// 開始載入資料
	//
	
	background.LoadBitmapByString({
		"resources/start&over/gameover0.bmp",
		"resources/start&over/gameover1.bmp"
		}, RGB(128, 0, 128));
	Endingmovie.LoadBitmapByString({
		"resources/start&over/Endingmovie.bmp"
		},RGB(0,128,0));
	floorline[0].LoadBitmapByString({
		"resources/start&over/floorline.bmp" }, RGB(128, 0, 128));
	floorline[1].LoadBitmapByString({
		"resources/start&over/floorline.bmp" }, RGB(128, 0, 128));
	floorline[2].LoadBitmapByString({
		"resources/start&over/floorline.bmp" }, RGB(128, 0, 128));
	floorline[3].LoadBitmapByString({
		"resources/start&over/floorline.bmp" }, RGB(128, 0, 128));
	sunset.LoadBitmapByString({
		"resources/start&over/sunset.bmp" }, RGB(128, 0, 128));
	rockman_normal_run.LoadBitmapByString({
		"resources/rockman/RunningLeft1.bmp",
		"resources/rockman/RunningLeft2.bmp",
		"resources/rockman/RunningLeft3.bmp"
		}, RGB(128, 0, 128));
	rockman_end_run.LoadBitmapByString({
		"resources/rockman/RunningLeft1_end.bmp",
		"resources/rockman/RunningLeft2_end.bmp",
		"resources/rockman/RunningLeft3_end.bmp"
		}, RGB(128, 0, 128));
	rockman_shadow_run.LoadBitmapByString({
		"resources/rockman/RunningLeft1_shadow.bmp",
		"resources/rockman/RunningLeft2_shadow.bmp",
		"resources/rockman/RunningLeft3_shadow.bmp"
		}, RGB(128, 0, 128));
	rockman_respawn.LoadBitmapByString({
		"resources/rockman/respawn0.bmp",
		"resources/rockman/respawn1.bmp",
		"resources/rockman/respawn2.bmp",
		"resources/rockman/respawn0.bmp"
		}, RGB(128, 0, 128));
	rockman_end_jump.LoadBitmapByString({
		"resources/rockman/jumpingLeft_end.bmp"
		}, RGB(128, 0, 128));
	ShowInitProgress(100, "OK!");
	Endingmovie.SetTopLeft(-2,-21);
	floorline[0].SetTopLeft(90, 224);
	floorline[1].SetTopLeft(218, 224);
	floorline[2].SetTopLeft(346, 224);
	floorline[3].SetTopLeft(474, 224);
	rockman_respawn.SetTopLeft(254, -32);
	rockman_normal_run.SetTopLeft(254, 178);
	rockman_end_run.SetTopLeft(254, 178);
	rockman_shadow_run.SetTopLeft(254, 178);
	rockman_end_jump.SetTopLeft(0, 0);
	rockman_respawn.SetAnimation(70, true);
	rockman_normal_run.SetAnimation(80, false);
	rockman_end_run.SetAnimation(80, false);
	rockman_shadow_run.SetAnimation(80, false);
	passsec = 0;
	timestep = 0.026f;
	floorline_x1 = 90.0f;
	floorline_x2 = 218.0f;
	floorline_x3 = 346.0f;
	floorline_x4 = 474.0f;
	x = 254.0f;
	y = -32.0f;
	map_x = -2.0f;
	map_y = -21.0f;
	onground = 0;
	rockmanout = 0;
	message = messagelist[0];
	message2 = message2list[0];
}



void CGameStateOver::OnLButtonDown(UINT nFlags, CPoint point) {
	// GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnMove()
{
	if (clear==0){
		background.SetFrameIndexOfBitmap(choose);
	}
	else if (clear == 1) {
		passsec += timestep;
		
		if (passsec >= 0.2&&passsec <= 0.3) {
			map_x = -516.0f;
		}
		else if (passsec >= 0.5&&passsec <= 0.6) {
			map_x = -1030.0f;
		}
		else if (passsec >= 9.3&&passsec <= 9.6) {
			map_x = -516.0f;
		}
		else if (passsec >= 9.6&&passsec <= 9.9) {
			map_x = -2.0f;
		}
		else if (passsec >= 9.9&&passsec <= 10) {
			map_x = -5122.0f;
			map_y = -532.0f;
		}
		else if (passsec >= 10 && passsec <= 10.2) {
			map_x = -1544.0f;
			map_y = -21.0f;
		}
		else if (passsec >= 10.2 && passsec <= 10.5) {
			map_x = -2058.0f;
		}
		else if (passsec >= 10.5 && passsec <= 10.8) {
			map_x = -2572.0f;
		}
		else if (passsec >= 18.2 && passsec <= 18.5) {
			map_x = -2058.0f;
		}
		else if (passsec >= 18.5 && passsec <= 18.8) {
			map_x = -1544.0f;
		}
		else if (passsec >= 18.8 && passsec <= 19.1) {
			map_x = -5122.0f;
			map_y = -532.0f;
		}
		else if (passsec >= 19.1 && passsec <= 19.4) {
			map_x = -3086.0f;
			map_y = -21.0f;
		}
		else if (passsec >= 19.4 && passsec <= 19.7) {
			map_x = -3600.0f;
		}
		else if (passsec >= 19.7 && passsec <= 20.0) {
			map_x = -4114.0f;
		}
		else if (passsec >= 28.2 && passsec <= 28.5) {
			map_x = -3600.0f;
		}
		else if (passsec >= 28.5 && passsec <= 28.8) {
			map_x = -3086.0f;
		}
		else if (passsec >= 28.8 && passsec <= 29.1) {
			map_x = -5122.0f;
			map_y = -532.0f;
			rockmanout = 1;
		}
		else if (passsec >= 44.0 && passsec <= 45.0) {
			map_y = -1042.0f;
		}
		else if (passsec >= 48.0 && passsec <= 49.0) {
			map_y = -1552.0f;
		}
		else if (passsec >= 51.0 && passsec <= 52.0) {
			rockmanout = 3;
		}
		else if (passsec >= 58.0 && passsec <= 59.0) {
			map_y = -2062.0f;
			rockmanout = 4;
		}
		else if (passsec >= 76.0&&passsec <= 76.2) {
			map_y = -3592.0f;
		}
		else if (passsec >= 78.0&&passsec <= 78.2) {
			map_y = -4102.0f;
		}
		else if (passsec >= 80.0&&passsec <= 80.2) {
			map_y = -4612.0f;
		}
		if (rockmanout==1)
		{
			if (y >= 162) {
				onground = 1;
				y = 162;
			}
			else {
				y += 450 * timestep;
			}
			listx1_1 = -286;
			listy1_1 = 324;
			listx1_2 = -286;
			listy1_2 = 372;
		}
		else if (rockmanout == 2|| rockmanout == 3|| rockmanout == 4) {
			if (map_x < -1) {
				map_x += 75 * timestep;
				floorline_x1 += 120 * timestep;
				floorline_x2 += 120 * timestep;
				floorline_x3 += 120 * timestep;
				floorline_x4 += 120 * timestep;
			}
			else {
				map_x = -1;
				goal = 1;
			}
			if (textcount == 10&&(listx1_1 <=200)) {
				listx1_1 += 250 * timestep;
				listx1_2 += 250 * timestep;
			}
			if (textcount < 10) {
				listx1_1 += 118 * timestep;
				listx1_2 += 118 * timestep;
			}
			if (listx1_1 >= 512&&textcount<10) {
				message = messagelist[textcount];
				message2 = message2list[textcount];
				listx1_1 = -286;
				listx1_2 = -286;
				textcount++;
			}
			if (floorline_x1 >= 512) {
				floorline_x1 = -8;
			}
			if (floorline_x2 >= 512) {
				floorline_x2 = -8;
			}
			if (floorline_x3 >= 512) {
				floorline_x3 = -8;
			}
			if (floorline_x4 >= 512) {
				floorline_x4 = -8;
			}
		}
		if (goal == 1&&y>42) {
			y -= 450 * timestep;
		}
		intmap_x = (int)std::round(map_x);
		intmap_y = (int)std::round(map_y);
		intx = (int)std::round(x);
		inty = (int)std::round(y);
		intlistx1_1 = (int)std::round(listx1_1);
		intlisty1_1 = (int)std::round(listy1_1);
		intlistx1_2 = (int)std::round(listx1_2);
		intlisty1_2 = (int)std::round(listy1_2);
		intfloor_x1 = (int)std::round(floorline_x1);
		intfloor_x2 = (int)std::round(floorline_x2);
		intfloor_x3 = (int)std::round(floorline_x3);
		intfloor_x4 = (int)std::round(floorline_x4);
		Endingmovie.SetTopLeft(intmap_x, intmap_y);
		rockman_respawn.SetTopLeft(intx, inty);
		rockman_normal_run.SetTopLeft(intx, inty);
		rockman_end_run.SetTopLeft(intx, inty);
		rockman_shadow_run.SetTopLeft(intx, inty);
		rockman_end_jump.SetTopLeft(intx, inty);
		floorline[0].SetTopLeft(intfloor_x1,224);
		floorline[1].SetTopLeft(intfloor_x2, 224);
		floorline[2].SetTopLeft(intfloor_x3, 224);
		floorline[3].SetTopLeft(intfloor_x4, 224);
	}
}
void CGameStateOver::OnShow()
{
	if (clear == 0) {
		background.ShowBitmap(2);
	}
	else if (clear == 1) {
		Endingmovie.ShowBitmap(2);
		floorline[0].ShowBitmap(2);
		floorline[1].ShowBitmap(2);
		floorline[2].ShowBitmap(2);
		floorline[3].ShowBitmap(2);
		if (rockmanout==1) {
			rockman_respawn.ShowBitmap(2);
		}
		else if (rockmanout == 2) {
			rockman_normal_run.ShowBitmap(2);

		}
		else if (rockmanout == 3) {
			rockman_shadow_run.ShowBitmap(2);
		}
		else if (rockmanout == 4&&goal==0) {
			rockman_end_run.ShowBitmap(2);
		}
		else if (goal == 1) {
			rockman_end_jump.ShowBitmap(2);
		}
		if (onground == 1) {
			rockman_respawn.ToggleAnimation();
			y = 178;
			rockmanout = 2;
			onground = 0;
		}
		CDC *px = CDDraw::GetBackCDC();
		CTextDraw::ChangeFontLog(px, 13, "MMRock9", RGB(60, 188, 252));
		time = to_string(passsec);
		CTextDraw::Print(px, intlistx1_1, intlisty1_1, message.c_str());
		CTextDraw::Print(px, intlistx1_2, intlisty1_2, message2.c_str());
		CTextDraw::ChangeFontLog(px, 13, "MMRock9", RGB(0, 0, 0));
		CTextDraw::Print(px, 400, 400, time.c_str());
		CDDraw::ReleaseBackCDC();
	}
}

void CGameStateOver::OnBeginState()
{
	if (clear == 1) {
		CAudio::Instance()->Play(AUDIO_Endingtheme);
	}
}
void CGameStateOver::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (nChar == VK_RETURN) {
		if (clear == 0) {
			if (choose == 0) {
				GotoGameState(GAME_STATE_RUN);
			}
			else {
				CAudio::Instance()->Play(AUDIO_MenuSelectTheme, true);
				GotoGameState(GAME_STATE_INIT);
			}
		}
	}
	if (nChar == VK_UP)  {
		if (clear == 0) {
			choose = ((choose - 1) + 2) % 2;
		}
	}
	if (nChar == VK_DOWN) {
		if (clear == 0) {
			choose = ((choose + 1) + 2) % 2;
		}
	}
}



