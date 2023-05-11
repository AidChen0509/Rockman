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
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

int CGameStateRun::gameState = 0;


CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
	//設定跳轉到這個state 需要的出值
	gameState = 0;
	// 關卡內容初始化
	if (CGameStateInit::stage == 0) {
		// -1為第一次進遊戲
		cutman_stage.OnBeginState(-1);
		CAudio::Instance()->Play(AUDIO_Cutman, true);
	}
	else if (CGameStateInit::stage == 1) {
		// guts
	}
	else if (CGameStateInit::stage == 2) {
		// ice
	}
	else if (CGameStateInit::stage == 3) {
		// bomb
	}
	else if (CGameStateInit::stage == 4) {
		// fire
	}
	else if (CGameStateInit::stage == 5) {
		// elec
	}
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	if (CGameStateInit::stage == 0) { //進入的是cutman關
		if (cutman_stage.getGamestate() == 1) { // boss 死掉了->OK跳轉回init
			gameState = 1;
			GotoGameState(GAME_STATE_INIT);
		}
		else if (cutman_stage.getGamestate() == 2) { // rockman沒命了->over
			gameState = 2;
			GotoGameState(GAME_STATE_OVER);
		}
		else {
			cutman_stage.OnMove();
		}
	}
	else if (CGameStateInit::stage == 1) {
		// guts
	}
	else if (CGameStateInit::stage == 2) {
		// ice
	}
	else if (CGameStateInit::stage == 3) {
		// bomb
	}
	else if (CGameStateInit::stage == 4) {
		// fire
	}
	else if (CGameStateInit::stage == 5) {
		// elec
	}
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	cutman_stage.OnInit();

	//CAudio::Instance()->Play(AUDIO_MenuSelectTheme, true);
	// other stages' Oninit

}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// 為了開發測試用
	if (nChar == VK_RETURN) {
		// GotoGameState(GAME_STATE_INIT); //回到初始畫面
	}

	if (CGameStateInit::stage == 0) {
		cutman_stage.OnKeyDown(nChar, nRepCnt, nFlags);
	}
	else if (CGameStateInit::stage == 1) {
		// guts
	}
	else if (CGameStateInit::stage == 2) {
		// ice
	}
	else if (CGameStateInit::stage == 3) {
		// bomb
	}
	else if (CGameStateInit::stage == 4) {
		// fire
	}
	else if (CGameStateInit::stage == 5) {
		// elec
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (CGameStateInit::stage == 0) {
		cutman_stage.OnKeyUp(nChar, nRepCnt, nFlags);
		// if()
		// GotoGameState(GAME_STATE_INIT);
	}
	else if (CGameStateInit::stage == 1) {
		// guts
	}
	else if (CGameStateInit::stage == 2) {
		// ice
	}
	else if (CGameStateInit::stage == 3) {
		// bomb
	}
	else if (CGameStateInit::stage == 4) {
		// fire
	}
	else if (CGameStateInit::stage == 5) {
		// elec
	}
}


void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{

	if (CGameStateInit::stage == 0) {
		cutman_stage.Onshow();
		// 加進來會變得很卡，不知道是不是檔案太大還是怎樣
		// CAudio::Instance()->Play(AUDIO_Cutman);
	}
	else if (CGameStateInit::stage == 1) {
		// guts
	}
	else if (CGameStateInit::stage == 2) {
		// ice
	}
	else if (CGameStateInit::stage == 3) {
		// bomb
	}
	else if (CGameStateInit::stage == 4) {
		// fire
	}
	else if (CGameStateInit::stage == 5) {
		// elec
	}
}
