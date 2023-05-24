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
#include "../Game/human.h"
#include "../Game/firemanStage.h"
#include "mygame.h"

using namespace game_framework;

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
	Sleep(1000);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	
	background.LoadBitmapByString({
		"resources/start&over/gameover0.bmp",
		"resources/start&over/gameover1.bmp",
		}, RGB(128, 0, 128));
	
	ShowInitProgress(100, "OK!");
	
	Sleep(1000);
}



void CGameStateOver::OnLButtonDown(UINT nFlags, CPoint point) {
	// GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnMove()
{
	background.SetFrameIndexOfBitmap(choose);
}
void CGameStateOver::OnShow()
{
	background.ShowBitmap(2);
}

void CGameStateOver::OnBeginState()
{
}
void CGameStateOver::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (nChar == VK_RETURN) {
		if (choose == 0) {
			GotoGameState(GAME_STATE_RUN);
		}
		else {
			CAudio::Instance()->Play(AUDIO_MenuSelectTheme, true);
			GotoGameState(GAME_STATE_INIT);
		}
	}
	if (nChar == VK_UP) {
		choose = ((choose - 1) + 2) % 2;
	}
	if (nChar == VK_DOWN) {
		choose = ((choose + 1) + 2) % 2;
	}
}



