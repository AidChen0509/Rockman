#pragma once
/*
 * gamelib.h: 本檔案儲遊戲相關的class的interface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *		1. Add ENABLE_AUDIO flag.
 *   2004-03-02 V4.0
 *		1. Add CInteger class.
 *      2. Add CGameState abstract class and adjust CGame to apply
 *         state pattern for switching game states.
 *   2004-03-08 V4.1
 *      1. Add OPEN_AS_FULLSCREEN flag.
 *      2. The Game Engine now becomes a framework.
 *   2005-07-28
 *      1. Add GAME_ASSERT macro to display run time errors gracefully.
 *      2. Remove CDDarw::CheckSystem(). It is useless.
 *   2005-09-08
 *      1. Eliminate CSpecialEffect::Abort. It is useless now.
 *      2. Add SHOW_GAME_CYCLE_TIME flag.
 *      3. Add DEFAULT_BG_COLOR flag;
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add MOUSEMOVE Handler for CGame and CGameState.
 *      2. Add _TRACE preprocessor flag for VC++.net.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Remove constantness of CAnimation::DELAY_COUNT.
 *      3. Enhance CAnimation to support SetDelayCount(), Reset(), and IsFinalBitmap().
 *      4. Remove CAnimation::GetLocation() and CMovingBitmap::GetLocation().
 *      5. Bitmap coordinate can no longer be set by CMovingBitmap::LoadBitmap().
 *         Defauts to (0,0).
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *      2. Fix bug: audio is now correctly recovered after a sleep or suspension of windows.
 *      3. Support ENABLE_GAME_PAUSE.
 *   2008-02-15 V4.4
 *      1. Add setup project for Visual studio 2005.
 *      2. Support bitmap scaling when ShowBitmap(scale) is called.
 *      3. Add namespace game_framework.
 *      4. Make the class CGame a singleton so that MFC can access it easily.
 *      5. Support loading of bitmap from bmp file.
 *      6. Support ShowInitProgress(percent) to display loading progress.
 *   2010-03-23 V4.6
 *      1. Rewrite CAudio with MCI commands to eliminate dependency with DirectMusic.
*/

/////////////////////////////////////////////////////////////////////////////
// Header for STL (Standard Template Library)
/////////////////////////////////////////////////////////////////////////////

#include <list>
#include <vector>
#include <map>
using namespace std;

namespace game_framework {

	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供動態(可以移動)的圖形
	// 每個Public Interface的用法都要懂，Implementation可以不懂
	/////////////////////////////////////////////////////////////////////////////

	class CMovingBitmap {
	public:
		CMovingBitmap();

		/* The function for loading the bitmap. */
		void  LoadBitmap(int, COLORREF = CLR_INVALID);		// 載入圖，指定圖的編號(resource)及透明色
		void  LoadBitmap(char*, COLORREF = CLR_INVALID);	// 載入圖，指定圖的檔名及透明色
		void  LoadBitmap(vector<char*>, COLORREF = CLR_INVALID);	// 載入圖，指定圖的檔名及透明色
		void  LoadBitmapByString(vector<string>, COLORREF = CLR_INVALID);	// 載入圖，指定圖的檔名及透明色
		void  LoadEmptyBitmap(int height, int weight);
		
		/* Unshow the bitmap. */
		void  UnshowBitmap();

		/* Setter */
		void  SetAnimation(int delay, bool _once);
		void  SetFrameIndexOfBitmap(int frame);
		void  SetTopLeft(int, int);			// 將圖的左上角座標移至 (x,y)

		/* Show the bitmap with or without factor. */
		void  ShowBitmap();					// 將圖貼到螢幕
		void  ShowBitmap(double factor);	// 將圖貼到螢幕 factor < 1時縮小，>1時放大。注意：需要VGA卡硬體的支援，否則會很慢
		
		/* Getter */
		int   GetFrameIndexOfBitmap();
		int   GetFrameSizeOfBitmap();
		int   GetTop();
		int   GetLeft();
		int   GetHeight();
		int   GetWidth();
		string GetImageFileName();
		COLORREF GetFilterColor();

		/* Is function */
		bool  IsAnimation();
		bool  IsAnimationDone();
		bool  IsBitmapLoaded();
		bool  IsOnceAnimation();
		static bool IsOverlap(CMovingBitmap bmp1, CMovingBitmap bmp2);
		
		/* Toggle function */
		void  ToggleAnimation();

	protected:
		//! 當前幀的索引值。
		int frameIndex = 0;
		//! 當前幀切換的延遲。
		int delayCount = 10;
		//! 儲存當前動畫的次數。
		int animationCount = -1;
		//! 儲存物件是否為動畫。
		bool isAnimation = false;
		//! 儲存物件動畫是否已結束
		bool isAnimationDone = true;
		//! 儲存圖片是否已讀取
		bool isBitmapLoaded = false;	// whether a bitmap has been loaded
		//! 儲存物件動畫是否為單次動畫
		bool isOnce = false;
		vector<CRect>    locations;			// location of the bitmap
		vector<unsigned> surfaceID;
		clock_t last_time = clock();
		//! 儲存物件讀取的圖片路徑
		string   imageFileName = "";
		//! 儲存物件過濾的圖片顏色
		COLORREF filterColor = CLR_INVALID;

	private:
		void InitializeRectByBITMAP(BITMAP bitmap);
		void ShowBitmapBySetting();
	};

	class CTextDraw {
	public:
		void static Print(CDC *pdc, int x, int y, string str);
		void static ChangeFontLog(CDC *pdc, int size, string fontName, COLORREF fontColor, int weight = 500);
	};
	class Character
	{
	public:
		Character() {};
		~Character() {};
		void OnInit(int stage_x, int stage_y) {
			resting[0].LoadBitmapByString({ "resources//cutman/rockman_lookleft.bmp" }, RGB(128, 0, 128));
			resting[0].SetTopLeft(x - stage_x, y - stage_y);
		};
		void Onshow(int stage_x, int stage_y) {
			resting[0].ShowBitmap(2);
			if (rightPressed) {
				if (0 <= x && x < 2 * (1024 - 24)) {
					x += dx;
				}
			}
			if (leftPressed) {
				if (0 < x && x <= 2 * (1024 - 24)) {
					x -= dx;
				}
			}
			resting[0].SetTopLeft(x - stage_x, y - stage_y);
		}
		void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {

			if (nChar == VK_LEFT) {
				leftPressed = true;
			}
			if (nChar == VK_RIGHT) {
				rightPressed = true;
			}

		};
		void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) {
			if (nChar == VK_LEFT) {
				leftPressed = false;
			}
			if (nChar == VK_RIGHT) {
				rightPressed = false;
			}
		};
		int getX() {
			return x;
		}
		int getY() {
			return y;
		}

	private:
		vector<int> level_left = { 0 , 768 * 2, 768 * 2, 728 * 2, 768 * 2, 1280 * 2, 1280 * 2, 1280 * 2, 1280 * 2, 1792 * 2, 1792 * 2, 1792 * 2 };//3072王關
		vector<int> level_top = { 2048 * 2 ,1792 * 2, 1536 * 2, 1280 * 2, 1024 * 2, 768 * 2, 512 * 2, 256 * 2, 0, 256 * 2, 512 * 2, 768 * 2 };//768王關
		CMovingBitmap resting[2];
		CMovingBitmap walkingRight;
		CMovingBitmap walkingLeft;
		bool leftPressed = false;
		bool rightPressed = false;
		bool isJumping = false;
		bool isShooting = false;
		//vector<int> initX_by_stage = { 232};
		//vector<int> initY_by_stage = { 4368};
		int x = 232;
		int y = 4368;
		int dx = 4;
	};
	class CutmanStage
	{
	public:
		CutmanStage() {};
		~CutmanStage() {};
		void OnInit() {
			cutman_stage.LoadBitmapByString({ "resources/CutManStage.bmp" });
			cutman_stage.SetTopLeft(-stage_x, -stage_y);
			rockman.OnInit(stage_x, stage_y);
		};
		void Onshow() {
			cutman_stage.ShowBitmap(2);
			cutman_stage.SetTopLeft(-stage_x, -stage_y);
			rockman.Onshow(stage_x, stage_y);
			if (rightPressed) {
				if (stage_x < level_left[level + 1] && rockman.getX() > level_left[level] + 256 - 24) { //洛克人要在最左圖的一半，即 (level_left + 116)*2 的右邊才將地圖向右移動，且不能到邊界的時候就停，總長-256+1
					stage_x += dx;
				}
			}
			if (leftPressed) {
				if (stage_x > level_left[level] && (rockman.getX() < level_left[level + 1] + 256 - 24)) { //半張圖256 半個腳色寬24
					stage_x -= dx;
				}
			}

			//rockman.Onshow(stage_x, stage_y);
		}
		void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
			rockman.OnKeyDown(nChar, nRepCnt, nFlags);
			if (nChar == VK_LEFT) {
				leftPressed = true;
			}
			if (nChar == VK_RIGHT) {
				rightPressed = true;
			}
		}
		void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) {
			rockman.OnKeyUp(nChar, nRepCnt, nFlags);
			if (nChar == VK_LEFT) {
				leftPressed = false;
			}
			if (nChar == VK_RIGHT) {
				rightPressed = false;
			}
		}


	private:
		vector<int> level_left = { 0 , 768 * 2, 768 * 2, 728 * 2, 768 * 2, 1280 * 2, 1280 * 2, 1280 * 2, 1280 * 2, 1792 * 2, 1792 * 2, 1792 * 2 };//3072王關
		vector<int> level_top = { 2048 * 2 ,1792 * 2, 1536 * 2, 1280 * 2, 1024 * 2, 768 * 2, 512 * 2, 256 * 2, 0, 256 * 2, 512 * 2, 768 * 2 };//768王關
		vector<vector<vector<int>>> matrixForEachLevel; // matrix[level][x][y], game data shouldn't be change
		// camera place chasing rockman at x-axis not y-axis
		int dx = 4;
		int stage_x = level_left[0];	//以整張圖的角度，所以setTopLeft要用負的
		int stage_y = level_top[0]; //以整張圖的角度，所以setTopLeft要用負的
		int level = 0;
		int savePoint_level = 0;
		bool leftPressed;
		bool rightPressed;

		CMovingBitmap cutman_stage;
		Character rockman;
	};
}
