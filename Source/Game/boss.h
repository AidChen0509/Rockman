#pragma once
namespace game_framework {
	class Cutman
	{
	public:
		Cutman() {};
		~Cutman() {};
		void OnInit() {
			// 閃5次
			shine.LoadBitmapByString({ 
				"resources/enemy/cutman/shine.bmp", "resources/enemy/cutman/purple.bmp",
				"resources/enemy/cutman/shine.bmp", "resources/enemy/cutman/purple.bmp",
				"resources/enemy/cutman/shine.bmp", "resources/enemy/cutman/purple.bmp",
				"resources/enemy/cutman/shine.bmp", "resources/enemy/cutman/purple.bmp",
				"resources/enemy/cutman/shine.bmp", "resources/enemy/cutman/purple.bmp",
				}, RGB(128, 0, 128));
			restingY[0].LoadBitmapByString({
				"resources/enemy/cutman/idleLeftOpenY.bmp",
				"resources/enemy/cutman/idleLeftCloseY.bmp",
				}, RGB(128, 0, 128));
			restingY[0].SetAnimation(200, false);

			restingY[1].LoadBitmapByString({
				"resources/enemy/cutman/idleRightOpenY.bmp",
				"resources/enemy/cutman/idleRightCloseY.bmp",
				}, RGB(128, 0, 128));
			restingN[0].LoadBitmapByString({
				"resources/enemy/cutman/idleLeftOpenN.bmp",
				"resources/enemy/cutman/idleLeftCloseN.bmp",
				}, RGB(128, 0, 128));
			restingN[1].LoadBitmapByString({
				"resources/enemy/cutman/idleRightOpenY.bmp",
				"resources/enemy/cutman/idleRightCloseY.bmp",
				}, RGB(128, 0, 128));
			runningY[0].LoadBitmapByString({
				"resources/enemy/cutman/walkLeftY1.bmp",
				"resources/enemy/cutman/walkLeftY2.bmp",
				"resources/enemy/cutman/walkLeftY3.bmp",
				}, RGB(128, 0, 128));
			runningY[1].LoadBitmapByString({
				"resources/enemy/cutman/walkRightY1.bmp",
				"resources/enemy/cutman/walkRightY2.bmp",
				"resources/enemy/cutman/walkRightY3.bmp",
				}, RGB(128, 0, 128));
			runningN[0].LoadBitmapByString({
				"resources/enemy/cutman/walkLeftN1.bmp",
				"resources/enemy/cutman/walkLeftN2.bmp",
				"resources/enemy/cutman/walkLeftN3.bmp",
				}, RGB(128, 0, 128));
			runningN[1].LoadBitmapByString({
				"resources/enemy/cutman/walkRightN1.bmp",
				"resources/enemy/cutman/walkRightN2.bmp",
				"resources/enemy/cutman/walkRightN3.bmp", 
				}, RGB(128, 0, 128));
			
			jumpingY[0].LoadBitmapByString({"resources/enemy/cutman/jumpLeftY.bmp"}, RGB(128, 0, 128));
			jumpingY[1].LoadBitmapByString({ "resources/enemy/cutman/jumpRightY.bmp" }, RGB(128, 0, 128));
			jumpingN[0].LoadBitmapByString({ "resources/enemy/cutman/jumpLeftN.bmp" }, RGB(128, 0, 128));
			jumpingN[1].LoadBitmapByString({ "resources/enemy/cutman/jumpRightN.bmp" }, RGB(128, 0, 128));
			
			

			rollingCutter[0].LoadBitmapByString({
				"resources/enemy/cutman/rollingCutterUp.bmp",
				"resources/enemy/cutman/rollingCutterLeft.bmp",
				"resources/enemy/cutman/rollingCutterDown.bmp",
				}, RGB(128, 0, 128));
			rollingCutter[1].LoadBitmapByString({
				"resources/enemy/cutman/rollingCutterUp.bmp",
				"resources/enemy/cutman/rollingCutterRight.bmp",
				"resources/enemy/cutman/rollingCutterDown.bmp",
				}, RGB(128, 0, 128));

		};
		void OnMove(int stageX, int stageY, int transitionState) {
			// 保留轉場state等待轉場
			// 
			// 
			/* 
			距離很遠-> 走到中距離 ->擺架式
								  ->距離介於中跟進之間，甩出剪刀後重複判斷，連續三次後仍為此區間，則直接跳向洛克人
			
			太遠會先靠近，到中距離的時候丟擺架式出剪刀，丟完發現洛克人跑出中距離，會用跳的過去追他
			*/
			if (transitionState == 40) {
				if (state == 100) {
					// 呼叫walk fucntion return boolean告訴你到達了沒
					// 呼叫jump function return boolean告訴你到達了沒
					// 先測加速度
					dy = 20;
					state = 10;
				}
				if (state == 10) {
					if (dy == -20) {
						y -= dy;
						x -= 4;
						state = 11;
						dy = 20;
					}
					else {
						y -= dy;
						x -= 4;
						dy -= 1;
					}
				}
				if (state == 11) {
					if (dy == -20) {
						y -= dy;
						x += 4;
						state = 10;
						dy = 20;
					}
					else {
						y -= dy;
						x += 4;
						dy -= 1;
					}
				}
				
			}
			restingY[0].SetTopLeft(x - stageX, y - stageY);
		};
		void OnShow() {
			restingY[0].ShowBitmap(2);
		};
		void setmap(vector<vector<int>> map) {
			this->map = map;
		}
		// 被打到退兩隔
	private:
		int x = 3252*2;
		int y = 928*2;
		int dx;
		int dy;
		int weaponX;
		int weaponY;
		int state = 100; // preState
		bool weaponThrew = false;
		bool isJumping = false;
		bool isWalking = false;
		bool isHit = false;

		CMovingBitmap shine;
		CMovingBitmap restingY[2];
		CMovingBitmap restingN[2];
		CMovingBitmap runningY[2];
		CMovingBitmap runningN[2];
		CMovingBitmap jumpingY[2];
		CMovingBitmap jumpingN[2];
		CMovingBitmap rollingCutter[2];

		vector<vector<int>> map;

	};

};