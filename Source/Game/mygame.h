/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
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
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_Cutman,
		AUDIO_GameStart,
		AUDIO_MenuSelectTheme,
		AUDIO_MenuSelect,
		AUDIO_MegaBuster,
		AUDIO_EnemyDamage,
		AUDIO_MegamanLand,
		AUDIO_MegamanDamage,
		AUDIO_BossBattle,
		AUDIO_EnergyFill,
		AUDIO_RollingCutter,
		AUDIO_EnemyShoot,
		AUDIO_BossSelect,
		AUDIO_Fireman,
		AUDIO_Endingtheme,
		AUDIO_MegamanDefeat,
		AUDIO_Firestorm
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		bool intoSelect = false;
		bool intoGame = false;
		static int stage;
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
		void OnMove();									// 移動這個狀態的遊戲元素

	private:
		int showState = 0;
		bool enterPressed = false;
		int gameStateOfStages[6] = {0, 0, 0, 0, 0, 0};
		float dx = 37;
		float dy = -120;
		int isjump = 0;
		int poseanim = 0;
		float x, y;
		int intx, inty;
		int i=0;
		float gravity = 80.0f;
		float timeStep = 0.07f;
		float textcount = 0.0f;
		string message="";
		vector<string> cutmanstr= { "C","U","T","M","A","N" };
		vector<string> firemanstr = { "F","I","R","E","M","A","N" };
		CMovingBitmap startBackground;					
		CMovingBitmap selectBackground;
		CMovingBitmap BossSelectBackground;
		CMovingBitmap Fireman[2];
		CMovingBitmap Cutman[2];
		CMovingBitmap cutSelected[3];
		CMovingBitmap gutsSelected[3];
		CMovingBitmap iceSelected[3];
		CMovingBitmap bombSelected[3];
		CMovingBitmap fireSelected[3];
		CMovingBitmap elecSelected[3];
		CMovingBitmap Insbg;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		static int gameState; 
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		bool enableBeenHit = true;
		CutmanStage cutman_stage;
		FiremanStage fireman_stage;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
		void OnLButtonDown(UINT nFlags, CPoint point);
		void OnKeyDown(UINT, UINT, UINT);
		static int clear;
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面

	private:
		int counter;	// 倒數之計數器
		float passsec;
		int choose = 0;
		float timestep;
		float map_x, map_y;
		int intmap_x, intmap_y;
		string message;
		string message2;
		string time;
		vector<string> messagelist = { "ORIGINAL BY","  REMAKE BY","GROUP","ROCKMAN MOVEMENT","STAGE MAP","ENEMY","ROCKMAN ATTACK","ANIMATION","  THANK YOU GUYS","THE" };
		vector<string> message2list = { "   CAPCOM","BRYAN & AIDEN"," 18"," BRYAN & AIDEN","  BRYAN","BRYAN","    AIDEN","  AIDEN","GOOD LUCK ON FINALS!","END" };
		float floorline_x1, floorline_x2, floorline_x3, floorline_x4;
		int intfloor_x1, intfloor_x2, intfloor_x3, intfloor_x4;
		float x, y;
		int intx, inty;
		float listx1_1, listy1_1;
		int intlistx1_1, intlisty1_1;
		float listx1_2, listy1_2;
		int intlistx1_2, intlisty1_2;
		int rockmanout;
		int onground;
		int textcount=0;
		int textpos = 0;
		int goal = 0;
		CMovingBitmap background;
		CMovingBitmap Endingmovie;
		CMovingBitmap floorline[4];
		CMovingBitmap sunset;
		CMovingBitmap rockman_respawn;
		CMovingBitmap rockman_normal_run;
		CMovingBitmap rockman_end_run;
		CMovingBitmap rockman_end_jump;
		CMovingBitmap rockman_shadow_run;
	};

}

