#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Game/cutman_stage_data.h"
#include "../Game/Character.h"
#include "../Game/Enemy.h"
#include "../Game/CutmanStage.h"
#include "../Library/gamecore.h"
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

	
	
	cutSelected.LoadBitmapByString({ "resources/start&over/selectStageBG.bmp", "resources/start&over/selectStageBGCutLight.bmp"  });
	cutSelected.SetAnimation(400, false);

	gutsSelected.LoadBitmapByString({ "resources/start&over/selectStageBG.bmp", "resources/start&over/selectStageBGGutsLight.bmp" });
	gutsSelected.SetAnimation(400, false);

	iceSelected.LoadBitmapByString({ "resources/start&over/selectStageBG.bmp", "resources/start&over/selectStageBGIceLight.bmp" });
	iceSelected.SetAnimation(400, false);

	bombSelected.LoadBitmapByString({ "resources/start&over/selectStageBG.bmp", "resources/start&over/selectStageBGBombLight.bmp" });
	bombSelected.SetAnimation(400, false);

	fireSelected.LoadBitmapByString({ "resources/start&over/selectStageBG.bmp", "resources/start&over/selectStageBGFireLight.bmp" });
	fireSelected.SetAnimation(400, false);

	elecSelected.LoadBitmapByString({ "resources/start&over/selectStageBG.bmp", "resources/start&over/selectStageBGElecLight.bmp" });
	elecSelected.SetAnimation(400, false);

	
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//
	
}

void CGameStateInit::OnBeginState()
{
	
}
void CGameStateInit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	if (nChar == VK_RETURN) {
		if (!intoSelect) { // TODO 要再加條件 避免後須按下enter會回朔
			startBackground.ToggleAnimation();
			intoSelect = true;
		}
		else if(startBackground.IsAnimationDone()){ //在select的時候按下enter，進入關卡
			GotoGameState(GAME_STATE_RUN);    // 切換至GAME_STATE_RUN
		}
	}
	if (nChar == VK_LEFT) {
		if (intoSelect) {
			stage = ((stage - 1) + 6) % 6;
		}
	}
	if (nChar == VK_RIGHT) {
		if (intoSelect) {
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

void CGameStateInit::OnShow()
{
	GotoGameState(GAME_STATE_RUN); //加速開發 先跳過開場
	if (!(startBackground.IsAnimationDone() && intoSelect)) { //開場enter且動畫跑完前，開場畫面都要show
		startBackground.ShowBitmap(2);
	}
	else if (!intoGame && intoSelect) { 
		if (stage == 0) {
			cutSelected.ShowBitmap(2);
		}
		else if(stage == 1){
			gutsSelected.ShowBitmap(2);
		}
		else if (stage == 2) {
			iceSelected.ShowBitmap(2);
		}
		else if (stage == 3) {
			bombSelected.ShowBitmap(2);
		}
		else if (stage == 4) {
			fireSelected.ShowBitmap(2);
		}
		else if (stage == 5) {
			elecSelected.ShowBitmap(2);
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