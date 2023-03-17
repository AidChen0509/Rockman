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

	if (nChar == VK_RETURN) {
		if (!intoSelect) { // TODO 要再加條件 避免後須按下enter會回朔
			startBackground.ToggleAnimation();
			intoSelect = true;
		}
	}
	if (nChar == VK_LEFT) { // TODO 若進入遊戲(像是剪刀人跳出來出現score的畫面)，要加條件避免改到stage
		if (intoSelect) {
			stage = ((stage - 1) + 6) % 6;
		}
	}
	if (nChar == VK_RIGHT) { // TODO 若進入遊戲(像是剪刀人跳出來出現score的畫面)，要加條件避免改到stage
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
	//GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	
	if (!(startBackground.IsAnimationDone() && intoSelect)) {
		startBackground.ShowBitmap(2);
	}else{
		if (!intoGame) {
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
			else {
				// TODO ASSERT
			}
		}else {
			// TODO 王跳出來 score跳出來的畫面
		}
	}
}