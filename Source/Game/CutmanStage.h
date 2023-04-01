#pragma once
namespace game_framework {
	class CutmanStage
	{
	public:
		CutmanStage() {
			rockman.setmap(dataSource._data);
		};
		~CutmanStage() {};
		void OnInit() {
			cutman_stage.LoadBitmapByString({ "resources/CutManStage.bmp" });
			cutman_stage.SetTopLeft(-stage_x, -stage_y);
			rockman.OnInit(stage_x, stage_y);
		};
		void OnMove() {
			// 在rockman之前先做轉場判定
			if (((rockman.getY() + 12) / 512) != (stage_y / 512)) { //除以512為了檢查是否在同一層
				// case 1 洛克人在上面一層 -> (rockman.getY() + 12) / 512 < (stage_y / 512)
				if (((rockman.getY() + 12) / 512) < (stage_y / 512)) {
					transitionState = 1; // 1 代表向上轉場
				}
				else {
					transitionState = 2; // 2 代表向上轉場
				}
				// case 2  洛克人在下面一層 -> (rockman.getY() + 12) / 512 > (stage_y / 512)
			}

			rockman.OnMove(stage_x, stage_y, transitionState);
			// 計算array index的一個小概念，供參
			//int index_x = stage_x/32; //最左邊的index : index_x
			//int index_y = stage_y/32; //最上面的index : index_y 
									  //最右邊的index : index_x + 16 //若 >= 208，不做array的access
									  //最下面的index : index_y + 16 //若 >= 144，不做array的access
			if (transitionState == 0) {
				if (rightPressed) {
					if (stage_x < 6144 && dataSource._data[stage_y / 32][(stage_x + 512) / 32] != -1
						&& rockman.getX() - 232 > 0 && dataSource._data[stage_y / 32][(rockman.getX() - 232) / 32] != -1) {
						stage_x = rockman.getX() - 2 * 116;
					}
				}
				if (leftPressed) {
					if (stage_x > 0 && dataSource._data[stage_y / 32][(stage_x-1)/32] != -1  //首先stage_x要先>0，避免out of range，再來要stage_x還沒到最左邊(左邊那格不為-1)，否則不動
						&& rockman.getX() + 280 < 6656 && dataSource._data[stage_y / 32][(rockman.getX() + 280) / 32] != -1){ //首先洛克人+280要小於整張地圖最右邊，避免out of range，再來rockman要不在地圖那一層的最右邊的半張區塊
						stage_x = rockman.getX() - 2 * 116;
					}
				}
			}
			else { //轉場觸發

				if (transitionState == 1) { //向上轉場
					stage_y -= dy; //512
					if (stage_y % 512 == 0) {
						transitionState = 0;
					}
				}
				else if (transitionState == 2) { //向下轉場
					stage_y += dy; //512;
					if (stage_y % 512 == 0) {
						transitionState = 0;
					}
				}
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
		// 先留著，雖然不知道有啥用ㄏ
		//vector<int> level_left = { 0 , 768 * 2, 768 * 2, 728 * 2, 768 * 2, 1280 * 2, 1280 * 2, 1280 * 2, 1280 * 2, 1792 * 2, 1792 * 2, 1792 * 2 };//3072王關
		//vector<int> level_top = { 2048 * 2 ,1792 * 2, 1536 * 2, 1280 * 2, 1024 * 2, 768 * 2, 512 * 2, 256 * 2, 0, 256 * 2, 512 * 2, 768 * 2 };//768王關
		
		// camera place chasing rockman at x-axis not y-axis 
		//int dy = 4;
		int dy = 8;
		int transitionState = 0;
		int stage_x = 0;	//以整張圖的角度，所以setTopLeft要用負的
		int stage_y = 4096; //以整張圖的角度，所以setTopLeft要用負的

		//剪刀窗戶的地方
		//int stage_x = 768*2;	//以整張圖的角度，所以setTopLeft要用負的
		//int stage_y = 1024*2; //以整張圖的角度，所以setTopLeft要用負的

		int savePoint = 0;
		bool leftPressed;
		bool rightPressed;

		CutmanStageData dataSource;
		CMovingBitmap cutman_stage;
		Character rockman;
	};
}