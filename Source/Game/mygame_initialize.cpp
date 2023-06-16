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
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////


int CGameStateInit::stage = 0; //static stage 宣告

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(0, "Start Initialize...");	// 一開始的loading進度為0%
	//
	// 開始載入資料
	CAudio::Instance()->Load(AUDIO_MenuSelectTheme, "resources/sound/MenuSelectTheme.wav");
	CAudio::Instance()->Load(AUDIO_GameStart, "resources/sound/GameStart.wav");
	CAudio::Instance()->Load(AUDIO_MenuSelect, "resources/sound/MenuSelect.wav");
	CAudio::Instance()->Load(AUDIO_BossSelect, "resources/sound/BossSelect.wav");
	CAudio::Instance()->Load(AUDIO_Cutman, "resources/sound/CutManStage.wav");
	CAudio::Instance()->Load(AUDIO_Fireman, "resources/sound/FireManStage.wav");
	CAudio::Instance()->Load(AUDIO_MegaBuster, "resources/sound/MegaBuster.wav");
	CAudio::Instance()->Load(AUDIO_EnemyDamage, "resources/sound/EnemyDamage.wav");
	CAudio::Instance()->Load(AUDIO_MegamanLand, "resources/sound/MegamanLand.wav");
	CAudio::Instance()->Load(AUDIO_MegamanDamage, "resources/sound/MegamanDamage.wav");
	CAudio::Instance()->Load(AUDIO_BossBattle, "resources/sound/BossBattle.wav");
	CAudio::Instance()->Load(AUDIO_EnergyFill, "resources/sound/EnergyFill3.wav");
	CAudio::Instance()->Load(AUDIO_RollingCutter, "resources/sound/RollingCutter.wav");
	CAudio::Instance()->Load(AUDIO_EnemyShoot, "resources/sound/EnemyShoot.wav");
	CAudio::Instance()->Load(AUDIO_Endingtheme, "resources/sound/EndingTheme.wav");
	CAudio::Instance()->Load(AUDIO_MegamanDefeat, "resources/sound/MegamanDefeat.wav");
	CAudio::Instance()->Load(AUDIO_Firestorm, "resources/sound/FireStorm1.wav");
	startBackground.LoadBitmapByString({
		"resources/start&over/initBackground1.bmp",
		"resources/start&over/initBackground2.bmp",
		"resources/start&over/initBackground1.bmp",
		"resources/start&over/initBackground2.bmp",
		"resources/start&over/initBackground1.bmp",
		"resources/start&over/initBackground2.bmp",
		"resources/start&over/initBackground1.bmp",
		"resources/start&over/initBackground2.bmp",
		"resources/start&over/initBackground1.bmp",
		"resources/start&over/initBackground2.bmp",
		"resources/start&over/initBackground1.bmp",
		"resources/start&over/initBackground2.bmp",
		"resources/start&over/initBackground1.bmp",
		"resources/start&over/initBackground2.bmp",
		"resources/start&over/initBackground1.bmp",
		});
	startBackground.SetTopLeft(0, 0);
	startBackground.SetAnimation(150, true);
	BossSelectBackground.LoadBitmapByString({
		"resources/start&over/BossSelectBG.bmp",
		"resources/start&over/white.bmp",
		"resources/start&over/BossSelectBG.bmp",
		"resources/start&over/white.bmp",
		"resources/start&over/BossSelectBG.bmp",
		"resources/start&over/white.bmp",
		"resources/start&over/BossSelectBG.bmp",
		"resources/start&over/BossSelectBG.bmp",
		"resources/start&over/BossSelectBG.bmp",
		"resources/start&over/BossSelectBG.bmp",
		"resources/start&over/BossSelectBG.bmp",
		"resources/start&over/BossSelectBG.bmp",
		"resources/start&over/BossSelectBG.bmp",
		"resources/start&over/BossSelectBG.bmp",
		"resources/start&over/BossSelectBG.bmp",
		"resources/start&over/BossSelectBG.bmp",
		"resources/start&over/BossSelectBG.bmp",
		"resources/start&over/BossSelectBG.bmp",
		});
	BossSelectBackground.SetTopLeft(0, 0);
	BossSelectBackground.SetAnimation(150, true);
	selectBackground.LoadBitmapByString({ "resources/start&over/selectStageBG.bmp" , "resources/start&over/selectStageBGlight.bmp" });
	selectBackground.SetAnimation(400, false);
	selectBackground.SetTopLeft(0, 0);
	Insbg.LoadBitmapByString({ "resources/start&over/Instruction.bmp" });
	Insbg.SetTopLeft(0, 0);
	cutSelected[0].LoadBitmapByString({ "resources/start&over/cutman00.bmp", "resources/start&over/cutman01.bmp"  });
	cutSelected[0].SetAnimation(400, false);
	cutSelected[0].SetTopLeft(72, 179);
	cutSelected[1].LoadBitmapByString({ "resources/start&over/cutman10.bmp", "resources/start&over/cutman11.bmp" });
	cutSelected[1].SetAnimation(400, false);
	cutSelected[1].SetTopLeft(72, 179);
	cutSelected[2].LoadBitmapByString({ "resources/start&over/cutman10.bmp"});
	cutSelected[2].SetTopLeft(72, 179);

	fireSelected[0].LoadBitmapByString({ "resources/start&over/fire00.bmp", "resources/start&over/fire01.bmp" });
	fireSelected[0].SetAnimation(400, false);
	fireSelected[0].SetTopLeft(341, 179);
	fireSelected[1].LoadBitmapByString({ "resources/start&over/fire10.bmp", "resources/start&over/fire11.bmp" });
	fireSelected[1].SetAnimation(400, false);
	fireSelected[1].SetTopLeft(341, 179);
	fireSelected[2].LoadBitmapByString({ "resources/start&over/fire10.bmp" });
	fireSelected[2].SetTopLeft(341, 179);
	Cutman[0].LoadBitmapByString({"resources/enemy/cutman/jumpRightY.bmp"}, RGB(128, 0, 128));
	Cutman[0].SetTopLeft(72, 179);
	Cutman[1].LoadBitmapByString({ 
		"resources/enemy/cutman/idleRightOpenY.bmp",
		"resources/enemy/cutman/idleRightcloseY.bmp",
		"resources/enemy/cutman/idleRightOpenY.bmp",
		"resources/enemy/cutman/idleRightcloseY.bmp",
		"resources/enemy/cutman/idleRightOpenY.bmp",
		"resources/enemy/cutman/idleRightcloseY.bmp",
		"resources/enemy/cutman/idleRightOpenY.bmp",
		"resources/enemy/cutman/idleRightcloseY.bmp",
		"resources/enemy/cutman/idleRightOpenY.bmp",
		"resources/enemy/cutman/idleRightcloseY.bmp",
		"resources/enemy/cutman/idleRightOpenY.bmp",
		"resources/enemy/cutman/idleRightOpenY.bmp",
		"resources/enemy/cutman/idleRightOpenY.bmp",
		"resources/enemy/cutman/idleRightOpenY.bmp",
		"resources/enemy/cutman/idleRightOpenY.bmp",
		"resources/enemy/cutman/idleRightOpenY.bmp"
		}, RGB(128, 0, 128));
	Cutman[1].SetAnimation(150, true);
	Cutman[1].SetTopLeft(190, 200);
	Fireman[0].LoadBitmapByString({ "resources/enemy/fireman/jumpLeft.bmp" }, RGB(128, 0, 128));
	Fireman[0].SetTopLeft(341, 179);
	Fireman[1].LoadBitmapByString({
		"resources/enemy/fireman/poseRight1.bmp",
		"resources/enemy/fireman/idleRight1.bmp",
		"resources/enemy/fireman/poseRight1.bmp",
		"resources/enemy/fireman/poseRight3.bmp",
		"resources/enemy/fireman/poseRight2.bmp",
		"resources/enemy/fireman/poseRight3.bmp",
		"resources/enemy/fireman/poseRight2.bmp",
		"resources/enemy/fireman/poseRight3.bmp",
		"resources/enemy/fireman/poseRight2.bmp",
		"resources/enemy/fireman/poseRight3.bmp",
		"resources/enemy/fireman/poseRight3.bmp",
		"resources/enemy/fireman/poseRight3.bmp",
		"resources/enemy/fireman/poseRight3.bmp",
		"resources/enemy/fireman/poseRight3.bmp",
		"resources/enemy/fireman/poseRight3.bmp",
		"resources/enemy/fireman/poseRight3.bmp"
		}, RGB(128, 0, 128));
	Fireman[1].SetAnimation(150, true);
	Fireman[1].SetTopLeft(190, 200);
}

void CGameStateInit::OnBeginState()
{
	intoSelect = true;
	// showState = 2;
	if (CGameStateRun::gameState == 1) { //打死boss了
		gameStateOfStages[stage] = 1;
	}
}
void CGameStateInit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_RETURN) {
		if (showState == 0) {
			startBackground.ToggleAnimation();
			CAudio::Instance()->Play(AUDIO_GameStart);
			showState = 1;
		}
		else if (showState == 2) { //在select的時候按下enter，進入關卡
			CAudio::Instance()->Stop(AUDIO_MenuSelectTheme);
			showState = 3;
			isjump = 0;
			CAudio::Instance()->Play(AUDIO_BossSelect);
			BossSelectBackground.ToggleAnimation();
			if (stage == 0) {
				x = 72;
				y = 179;
				dx = 37;
				dy = -120;
				gravity = 80.0f;
				timeStep = 0.07f;
				textcount = 0.0f;
				message = "";
				i = 0;
			}
			else if (stage == 1) {
				x = 341;
				y = 179;
				dx = -48;
				dy = -120;
				gravity = 80.0f;
				timeStep = 0.07f;
				textcount = 0.0f;
				message = "";
				i = 0;
			}
		}

		if (showState == 99) {
			showState = 2;
		}
	}
	if (nChar == 0x47) {
		CGameStateOver::clear = 1;
		GotoGameState(GAME_STATE_OVER);
	}
	if (nChar == VK_LEFT) {
		if (showState == 2) {
			CAudio::Instance()->Play(AUDIO_MenuSelect);
			stage = ((stage - 1) + 2) % 2;
		}
	}
	if (nChar == VK_RIGHT) {
		if (showState == 2) {
			CAudio::Instance()->Play(AUDIO_MenuSelect);
			stage = ((stage + 1) + 2) % 2;
		}
	}
}
void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
}
void CGameStateInit::OnMove() {
	if (showState == 1) {
		if (startBackground.IsAnimationDone()) {
			showState = 99;
			// 進入選單同時撥音樂
			CAudio::Instance()->Play(AUDIO_MenuSelectTheme,true);
		}
	}
}
void CGameStateInit::OnShow()
{
	// GotoGameState(GAME_STATE_RUN); //加速開發 先跳過開場

	if(showState == 1 || showState == 0){
		startBackground.ShowBitmap(2);
	}
	else if (showState == 2) { 
		selectBackground.ShowBitmap(2);
		for (int i = 0; i < 2; i++)
		{
			if (gameStateOfStages[i] == 1) {
				if (i == stage) {
					if (stage == 0) {
						cutSelected[1].ShowBitmap(2);
					}
					else if (stage == 1) {
						fireSelected[1].ShowBitmap(2);
					}
				}else{
					if (i == 0) {
						cutSelected[2].ShowBitmap(2);
					}
					else if (i == 1) {
						fireSelected[2].ShowBitmap(2);
					}
				}
			}
			else {
				if (i == stage) {
					if (stage == 0) {
						cutSelected[0].ShowBitmap(2);
					}
					else if (stage == 1) {
						fireSelected[0].ShowBitmap(2);
					}
				}
			}
		}
	}
	else if (showState == 3) {
		BossSelectBackground.ShowBitmap(2);
		if (stage == 0) {
			if (isjump==0)
			{
				Cutman[0].ShowBitmap(2);
				x += dx*timeStep;
				y += dy * timeStep;
				dy += gravity * timeStep;
				if (x>=180&&y >= 190) {
					isjump = 1;
					Cutman[1].ShowBitmap(2);
					Cutman[1].ToggleAnimation();
					poseanim = 1;
				}
			}
			if (isjump == 1) {
				Cutman[1].ShowBitmap(2);
				CDC *px = CDDraw::GetBackCDC();
				CTextDraw::ChangeFontLog(px, 13, "MMRock9", RGB(255, 255, 255));
				textcount -= 0.012f;
				if (textcount<=0.0&&i<6) {
					message += cutmanstr[i];
					i++;
					textcount = 0.49f;
				}
				CTextDraw::Print(px, 273, 216, message.c_str());
				CDDraw::ReleaseBackCDC();
				if (i == 6&& textcount <= 0.0) {
					isjump = 2;
					showState = 2;
					GotoGameState(GAME_STATE_RUN);    // 切換至GAME_STATE_RUN
				}
			}
			if (poseanim == 1) {
				Cutman[1].ToggleAnimation();
				poseanim = 0;
			}
			intx = (int)std::round(x);
			inty = (int)std::round(y);
			Cutman[0].SetTopLeft(intx, inty);
			Cutman[1].SetTopLeft(intx, inty);
		}
		else if (stage == 1) {
			if (isjump == 0)
			{
				Fireman[0].ShowBitmap(2);
				x += dx * timeStep;
				y += dy * timeStep;
				dy += gravity * timeStep;
				if (x <= 190 && y >= 190) {
					isjump = 1;
					Fireman[1].ShowBitmap(2);
					Fireman[1].ToggleAnimation();
					poseanim = 1;
				}
			}
			if (isjump == 1) {
				Fireman[1].ShowBitmap(2);
				CDC *px = CDDraw::GetBackCDC();
				CTextDraw::ChangeFontLog(px, 13, "MMRock9", RGB(255, 255, 255));
				textcount -= 0.012f;
				if (textcount <= 0.0&&i < 7) {
					message += firemanstr[i];
					i++;
					textcount = 0.53f;
				}
				CTextDraw::Print(px, 273, 216, message.c_str());
				CDDraw::ReleaseBackCDC();
				if (i == 7 && textcount <= 0.0) {
					isjump = 2;
					showState = 2;
					GotoGameState(GAME_STATE_RUN);    // 切換至GAME_STATE_RUN
				}
			}
			if (poseanim == 1) {
				Fireman[1].ToggleAnimation();
				poseanim = 0;
			}
			intx = (int)std::round(x);
			inty = (int)std::round(y);
			Fireman[0].SetTopLeft(intx, inty);
			Fireman[1].SetTopLeft(intx, inty);
		}
	}
	else if (showState == 99) {
		Insbg.ShowBitmap(2);
	}
		// TODO 王跳出來 score跳出來的畫面
		// 背景一藍一白是固定的
		// 王跳向定點的瞬間，藍白畫面停止閃，
		// 王跳向定點後接續執行王的動畫
		// 王動畫停止後，跑分數動畫
		/*
			1.載入各個王的跳躍圖 //需設定軌跡，框架更新頻率33Hz
			2.載入各個王的落地動畫 //
			可以透過stage物件來幫忙 //吃int讀stage，物件透過stage，實作王的登場動畫對應的分數動畫

		*/
}