#pragma once
namespace game_framework {
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
		void OnMove() {
			rockman.OnMove(stage_x, stage_y, level_left[level], level_left[level + 1] + 256 * 2 - 48, level_top[level], level);
			/*if (rightPressed) {
				if (stage_x < level_left[level + 1] && rockman.getX() > level_left[level] + 256 - 24) {
					//洛克人要在最左圖的一半，即 (level_left + 116)*2 的右邊才將地圖向右移動，且不能到邊界的時候就停，總長-256+1
					stage_x = rockman.getX() - 2 * 116;
				}
			}
			if (leftPressed) {
				if (stage_x > level_left[level] && (rockman.getX() < level_left[level + 1] + 256 - 24)) { //半張圖256 半個腳色寬24
					stage_x = rockman.getX() - 2 * 116;
				}
			} */
			// approach 2 no need to consider Pressed or not, 
			if ((stage_x < level_left[level + 1] && rockman.getX() > level_left[level] + 256 - 24) || (stage_x > level_left[level] && (rockman.getX() < level_left[level + 1] + 256 - 24))) {
				stage_x = rockman.getX() - 2 * 116;
			}
			cutman_stage.SetTopLeft(-stage_x, -stage_y);
		};
		void Onshow() {
			cutman_stage.ShowBitmap(2);
			rockman.Onshow(stage_x, stage_y); // 256*2是最邊邊，48是角色寬度
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
		//int dx = 4;
		int stage_x = level_left[0];	//以整張圖的角度，所以setTopLeft要用負的
		int stage_y = level_top[0]; //以整張圖的角度，所以setTopLeft要用負的
		int level = 0; // cutman的第幾個level，方便儲存點跟地圖的動畫切換
		int savePoint_level = 0;
		bool leftPressed;
		bool rightPressed;

		CMovingBitmap cutman_stage;
		Character rockman;
	};
}