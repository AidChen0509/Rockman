#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

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
		});
	startBackground.SetTopLeft(0, 0);
	startBackground.SetAnimation(150, true);

	/* TODO
	selectBackground.LoadBitmapByString({ "resources/start&over/selectStage1.bmp" });
	selectBackground.SetTopLeft(0, 0);
	*/
	//
	Sleep(1000);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//
}

void CGameStateInit::OnBeginState()
{
}
void CGameStateInit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	/*if (nChar == VK_RETURN) {
		background.ToggleAnimation();
		intoSelect = true;
		Sleep(1000);
		//background.LoadEmptyBitmap(256, 239);
	}*/
	if (nChar == VK_RETURN) {
		startBackground.ToggleAnimation();
		intoSelect = true; 
	}
}
void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	//GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	
	if (!(startBackground.IsAnimationDone() && intoSelect)) {
		startBackground.ShowBitmap(2);
	}else{
		if (!intoGame) {
			//selectBackground.ShowBitmap(2);
		}else {

		}
	}
	//background.ShowBitmap();
}