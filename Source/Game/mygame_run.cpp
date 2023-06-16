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
#include "../Game/firemanStage.h"
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
	enableBeenHit = true;
	// 關卡內容初始化
	if (CGameStateInit::stage == 0) {
		// -1為第一次進遊戲
		cutman_stage.OnBeginState(-1); // -1
		CAudio::Instance()->Play(AUDIO_Cutman, true);
	}
	else if (CGameStateInit::stage == 1) {
		// fire
		fireman_stage.OnBeginState(-1);
		CAudio::Instance()->Play(AUDIO_Fireman, true);
	}
	else if (CGameStateInit::stage == 2) {
		// ice
	}
	else if (CGameStateInit::stage == 3) {
		// bomb
	}
	else if (CGameStateInit::stage == 4) {
		
	}
	else if (CGameStateInit::stage == 5) {
		// elec
	}
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	if (CGameStateInit::stage == 0) { //進入的是cutman關
		cutman_stage.setEnableBeenHit(enableBeenHit);
		if (cutman_stage.getGamestate() == 1) { // boss 死掉了->OK跳轉回init
			gameState = 1;
			cutman_stage.OnBeginState(-1);
			CAudio::Instance()->Stop(AUDIO_BossBattle);
			CAudio::Instance()->Play(AUDIO_MenuSelectTheme, true);
			GotoGameState(GAME_STATE_INIT);
		}
		else if (cutman_stage.getGamestate() == 2) { // rockman沒命了->over
			gameState = 2;
			cutman_stage.OnBeginState(-1);
			CAudio::Instance()->Stop(AUDIO_Cutman);
			CAudio::Instance()->Stop(AUDIO_BossBattle);
			GotoGameState(GAME_STATE_OVER);
		}
		else {
			cutman_stage.OnMove();
		}
	}
	else if (CGameStateInit::stage == 1) {
		// fire
		fireman_stage.setEnableBeenHit(enableBeenHit);
		if (fireman_stage.getGamestate() == 1) { // boss 死掉了->OK跳轉回init
			gameState = 1;
			fireman_stage.OnBeginState(-1);
			CAudio::Instance()->Stop(AUDIO_BossBattle);
			CAudio::Instance()->Play(AUDIO_MenuSelectTheme, true);
			GotoGameState(GAME_STATE_INIT);
		}
		else if (fireman_stage.getGamestate() == 2) { // rockman沒命了->over
			gameState = 2;
			fireman_stage.OnBeginState(-1);
			CAudio::Instance()->Stop(AUDIO_Cutman);
			CAudio::Instance()->Stop(AUDIO_BossBattle);
			// 播放gameover的音效，once
			GotoGameState(GAME_STATE_OVER);
		}
		else {
			fireman_stage.OnMove();
		}
	}
	else if (CGameStateInit::stage == 2) {
		// ice
	}
	else if (CGameStateInit::stage == 3) {
		// bomb
	}
	else if (CGameStateInit::stage == 4) {
		
	}
	else if (CGameStateInit::stage == 5) {
		// elec
	}
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	ShowInitProgress(33, "Initialize...");
	cutman_stage.OnInit();
	fireman_stage.OnInit();
	//CAudio::Instance()->Play(AUDIO_MenuSelectTheme, true);
	// other stages' Oninit
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// 為了開發測試用
	if (nChar == 0x45) {
		if (enableBeenHit) {
			enableBeenHit = false;
		}
		else {
			enableBeenHit = true;
		}
	}
	if (CGameStateInit::stage == 0) {
		cutman_stage.OnKeyDown(nChar, nRepCnt, nFlags);
	}
	else if (CGameStateInit::stage == 1) {
		// fire
		fireman_stage.OnKeyDown(nChar, nRepCnt, nFlags);
	}
	else if (CGameStateInit::stage == 2) {
		// ice
	}
	else if (CGameStateInit::stage == 3) {
		// bomb
	}
	else if (CGameStateInit::stage == 4) {
		
	}
	else if (CGameStateInit::stage == 5) {
		// elec
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (CGameStateInit::stage == 0) {
		cutman_stage.OnKeyUp(nChar, nRepCnt, nFlags);

	}
	else if (CGameStateInit::stage == 1) {
		// fire
		fireman_stage.OnKeyUp(nChar, nRepCnt, nFlags);
	}
	else if (CGameStateInit::stage == 2) {
		// ice
	}
	else if (CGameStateInit::stage == 3) {
		// bomb
	}
	else if (CGameStateInit::stage == 4) {
		
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
	}
	else if (CGameStateInit::stage == 1) {
		// fire
		fireman_stage.Onshow();
	}
	else if (CGameStateInit::stage == 2) {
		// ice
	}
	else if (CGameStateInit::stage == 3) {
		// bomb
	}
	else if (CGameStateInit::stage == 4) {
		
	}
	else if (CGameStateInit::stage == 5) {
		// elec
	}
}

