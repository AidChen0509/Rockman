#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "../Game/Character.h"
#include "../Game/boss.h"
#include "../Game/Enemy.h"
#include "../Game/CutmanStage.h"
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
	CAudio::Instance()->Load(AUDIO_GameStart, "resources/sound/GameStart.wav");
	CAudio::Instance()->Load(AUDIO_MenuSelect, "resources/sound/MenuSelect.wav");
	


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

	selectBackground.LoadBitmapByString({ "resources/start&over/selectStageBG.bmp" , "resources/start&over/selectStageBGlight.bmp" });
	selectBackground.SetAnimation(400, false);
	selectBackground.SetTopLeft(0, 0);
	
	cutSelected[0].LoadBitmapByString({ "resources/start&over/cutman00.bmp", "resources/start&over/cutman01.bmp"  });
	cutSelected[0].SetAnimation(400, false);
	cutSelected[0].SetTopLeft(144, 50);
	cutSelected[1].LoadBitmapByString({ "resources/start&over/cutman10.bmp", "resources/start&over/cutman11.bmp" });
	cutSelected[1].SetAnimation(400, false);
	cutSelected[1].SetTopLeft(144, 50);
	cutSelected[2].LoadBitmapByString({ "resources/start&over/cutman10.bmp"});
	cutSelected[2].SetTopLeft(144, 50);

	gutsSelected[0].LoadBitmapByString({ "resources/start&over/guts00.bmp", "resources/start&over/guts01.bmp" });
	gutsSelected[0].SetAnimation(400, false);
	gutsSelected[0].SetTopLeft(272, 50);
	gutsSelected[1].LoadBitmapByString({ "resources/start&over/guts10.bmp", "resources/start&over/guts11.bmp" });
	gutsSelected[1].SetAnimation(400, false);
	gutsSelected[1].SetTopLeft(272, 50);
	gutsSelected[2].LoadBitmapByString({ "resources/start&over/guts10.bmp" });
	gutsSelected[2].SetTopLeft(272, 50);


	iceSelected[0].LoadBitmapByString({ "resources/start&over/ice00.bmp", "resources/start&over/ice01.bmp" });
	iceSelected[0].SetAnimation(400, false);
	iceSelected[0].SetTopLeft(340, 178);
	iceSelected[1].LoadBitmapByString({ "resources/start&over/ice10.bmp", "resources/start&over/ice11.bmp" });
	iceSelected[1].SetAnimation(400, false);
	iceSelected[1].SetTopLeft(340, 178);
	iceSelected[2].LoadBitmapByString({ "resources/start&over/ice10.bmp" });
	iceSelected[2].SetTopLeft(340, 178);


	bombSelected[0].LoadBitmapByString({ "resources/start&over/bomb00.bmp", "resources/start&over/bomb01.bmp" });
	bombSelected[0].SetAnimation(400, false);
	bombSelected[0].SetTopLeft(272, 306);
	bombSelected[1].LoadBitmapByString({ "resources/start&over/bomb10.bmp", "resources/start&over/bomb11.bmp" });
	bombSelected[1].SetAnimation(400, false);
	bombSelected[1].SetTopLeft(272, 306);
	bombSelected[2].LoadBitmapByString({ "resources/start&over/bomb10.bmp" });
	bombSelected[2].SetTopLeft(272, 306);

	fireSelected[0].LoadBitmapByString({ "resources/start&over/fire00.bmp", "resources/start&over/fire01.bmp" });
	fireSelected[0].SetAnimation(400, false);
	fireSelected[0].SetTopLeft(144, 306);
	fireSelected[1].LoadBitmapByString({ "resources/start&over/fire10.bmp", "resources/start&over/fire11.bmp" });
	fireSelected[1].SetAnimation(400, false);
	fireSelected[1].SetTopLeft(144, 306);
	fireSelected[2].LoadBitmapByString({ "resources/start&over/fire10.bmp" });
	fireSelected[2].SetTopLeft(144, 306);

	elecSelected[0].LoadBitmapByString({ "resources/start&over/elec00.bmp", "resources/start&over/elec01.bmp" });
	elecSelected[0].SetAnimation(400, false);
	elecSelected[0].SetTopLeft(80, 178);
	elecSelected[1].LoadBitmapByString({ "resources/start&over/elec10.bmp", "resources/start&over/elec11.bmp" });
	elecSelected[1].SetAnimation(400, false);
	elecSelected[1].SetTopLeft(80, 178);
	elecSelected[2].LoadBitmapByString({ "resources/start&over/elec10.bmp" });
	elecSelected[2].SetTopLeft(80, 178);
	
	
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
		if (showState == 0) { // TODO 要再加條件 避免後須按下enter會回朔
			startBackground.ToggleAnimation();
			CAudio::Instance()->Play(AUDIO_GameStart);
			showState = 1;
		}
		else if (showState == 2) { //在select的時候按下enter，進入關卡
			GotoGameState(GAME_STATE_RUN);    // 切換至GAME_STATE_RUN
		}
	}

	if (nChar == VK_LEFT) {
		if (showState == 2) {
			CAudio::Instance()->Play(AUDIO_MenuSelect);
			stage = ((stage - 1) + 6) % 6;
		}
	}
	if (nChar == VK_RIGHT) {
		if (showState == 2) {
			CAudio::Instance()->Play(AUDIO_MenuSelect);
			stage = ((stage + 1) + 6) % 6;
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
			showState = 2;
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
		for (int i = 0; i < 6; i++)
		{
			if (gameStateOfStages[i] == 1) {
				if (i == stage) {
					if (stage == 0) {
						cutSelected[1].ShowBitmap(2);
					}
					else if (stage == 1) {
						gutsSelected[1].ShowBitmap(2);
					}
					else if (stage == 2) {
						iceSelected[1].ShowBitmap(2);
					}
					else if (stage == 3) {
						bombSelected[1].ShowBitmap(2);
					}
					else if (stage == 4) {
						fireSelected[1].ShowBitmap(2);
					}
					else if (stage == 5) {
						elecSelected[1].ShowBitmap(2);
					}
				}else{
					if (i == 0) {
						cutSelected[2].ShowBitmap(2);
					}
					else if (i == 1) {
						gutsSelected[2].ShowBitmap(2);
					}
					else if (i == 2) {
						iceSelected[2].ShowBitmap(2);
					}
					else if (i == 3) {
						bombSelected[2].ShowBitmap(2);
					}
					else if (i == 4) {
						fireSelected[2].ShowBitmap(2);
					}
					else if (i == 5) {
						elecSelected[2].ShowBitmap(2);
					}
				}
			}
			else {
				if (i == stage) {
					if (stage == 0) {
						cutSelected[0].ShowBitmap(2);
					}
					else if (stage == 1) {
						gutsSelected[0].ShowBitmap(2);
					}
					else if (stage == 2) {
						iceSelected[0].ShowBitmap(2);
					}
					else if (stage == 3) {
						bombSelected[0].ShowBitmap(2);
					}
					else if (stage == 4) {
						fireSelected[0].ShowBitmap(2);
					}
					else if (stage == 5) {
						elecSelected[0].ShowBitmap(2);
					}
				}
			}
		}

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