#pragma once
namespace game_framework {
	class CutmanStage
	{
	public:
		CutmanStage() {
			rockman.setmap(dataSource._data);
			// 初始化怪物
			enemyContainer.push_back(new Heli(280 * 2, 2110 * 2));
			enemyContainer.push_back(new Heli(428 * 2, 2178 * 2));
			enemyContainer.push_back(new Heli(448 * 2, 2133 * 2));
			enemyContainer.push_back(new Heli(1888 * 2, 70 * 2)); // y = 72會炸，怪物最好不要跟人同一個平台
			enemyContainer.push_back(new Heli(1928 * 2, 132 * 2));
			enemyContainer.push_back(new Heli(1947 * 2, 79 * 2));
			enemyContainer.push_back(new Beak(816 * 2, 2112 * 2, 0)); //param 3: 0代表面左，1代表面右
			enemyContainer.push_back(new Beak(944 * 2, 2159 * 2, 0));
			enemyContainer.push_back(new Beak(976 * 2, 1936 * 2, 0));
			enemyContainer.push_back(new Beak(880 * 2, 1872 * 2, 0)); 
			enemyContainer.push_back(new Beak(912 * 2, 1840 * 2, 0)); 
			enemyContainer.push_back(new Beak(832 * 2, 1712 * 2, 1)); 
			enemyContainer.push_back(new Beak(880 * 2, 1648 * 2, 0));
			enemyContainer.push_back(new Beak(944 * 2, 1584 * 2, 0));
			enemyContainer.push_back(new Beak(880 * 2, 1488 * 2, 1));
			enemyContainer.push_back(new Beak(944 * 2, 1360 * 2, 0));
			enemyContainer.push_back(new Beak(912 * 2, 1312 * 2, 0));
		};
		~CutmanStage() {
			for (size_t i = 0; i < enemyContainer.size(); i++)
			{
				delete enemyContainer[i];
			}
		};
		void OnInit() {
			cutman_stage.LoadBitmapByString({ "resources/CutManStage.bmp" });
			rockman_blood.LoadBitmapByString({ "resources/rockman/blood/blood0.bmp",
											   "resources/rockman/blood/blood1.bmp", 
												"resources/rockman/blood/blood2.bmp", 
												"resources/rockman/blood/blood3.bmp", 
												"resources/rockman/blood/blood4.bmp", 
												"resources/rockman/blood/blood5.bmp", 
												"resources/rockman/blood/blood6.bmp", 
												"resources/rockman/blood/blood7.bmp", 
												"resources/rockman/blood/blood8.bmp", 
												"resources/rockman/blood/blood9.bmp", 
												"resources/rockman/blood/blood10.bmp", 
												"resources/rockman/blood/blood11.bmp", 
												"resources/rockman/blood/blood12.bmp", 
												"resources/rockman/blood/blood13.bmp", 
												"resources/rockman/blood/blood14.bmp",
												"resources/rockman/blood/blood15.bmp",
												"resources/rockman/blood/blood16.bmp",
												"resources/rockman/blood/blood17.bmp",
												"resources/rockman/blood/blood18.bmp",
												"resources/rockman/blood/blood19.bmp",
												"resources/rockman/blood/blood20.bmp",
												"resources/rockman/blood/blood21.bmp",
												"resources/rockman/blood/blood22.bmp",
												"resources/rockman/blood/blood23.bmp",
												"resources/rockman/blood/blood24.bmp",
												"resources/rockman/blood/blood25.bmp",
												"resources/rockman/blood/blood26.bmp",
												"resources/rockman/blood/blood27.bmp",
												"resources/rockman/blood/blood28.bmp",});
			rockman_blood.SetTopLeft(48, 50);
			cutman_stage.SetTopLeft(-stage_x, -stage_y);
			rockman.OnInit(stage_x, stage_y);
			for (size_t i = 0; i < enemyContainer.size(); i++)
			{
				enemyContainer[i]->OnInit();
			}
		};
		void OnMove() {
			// 在rockman之前先做轉場判定
			int rockmanX = rockman.getX();
			int rockmanY = rockman.getY();
			if (((rockmanY + 12) / 512) != (stage_y / 512)) { //除以512為了檢查是否在同一層
				// case 1 洛克人在上面一層 -> (rockmanY + 12) / 512 < (stage_y / 512)
				if (((rockmanY + 12) / 512) < (stage_y / 512)) {
					transitionState = 1; // 1 代表向上轉場
				}
				// case 2  洛克人在下面一層 -> (rockmanY + 12) / 512 > (stage_y / 512)
				else {
					transitionState = 2; // 2 代表向上轉場
				}
			}else if(dataSource._data[rockmanY / 32][(rockmanX + 2 * (24 - 1 - 4)) / 32] == 4){
				if (transitionState == 30) {
					transitionState = 4; //進王關transition
				}
				else if (transitionState == 0) {
					transitionState = 3; //進王關廊道transition
				}
			}

			for (size_t i = 0; i < enemyContainer.size(); i++)
			{
				enemyContainer[i]->OnMove(rockmanX, rockmanY, stage_x, stage_y);
			}
			

			rockman.OnMove(stage_x, stage_y, transitionState);
			// 計算array index的一個小概念，供參
			//int index_x = stage_x/32; //最左邊的index : index_x
			//int index_y = stage_y/32; //最上面的index : index_y 
									  //最右邊的index : index_x + 16 //若 >= 208，不做array的access
									  //最下面的index : index_y + 16 //若 >= 144，不做array的access
			if (transitionState == 0) {
				if (rightPressed) {
					// 王關之前
					if (stage_x < 4096 && dataSource._data[stage_y / 32][(stage_x + 512) / 32] != -1
						&& rockman.getX() - 232 > 0 && dataSource._data[stage_y / 32][(rockman.getX() - 232) / 32] != -1) {
						stage_x = rockman.getX() - 2 * 116;
					}
				}
				if (leftPressed) {
					if (stage_x > 0 && dataSource._data[stage_y / 32][(stage_x-1)/32] != -1  //首先stage_x要先>0，避免out of range，再來要stage_x還沒到最左邊(左邊那格不為-1)，否則不動
						&& rockman.getX() + 280 < 4608 && dataSource._data[stage_y / 32][(rockman.getX() + 280) / 32] != -1){ //首先洛克人+280要小於整張地圖最右邊，避免out of range，再來rockman要不在地圖那一層的最右邊的半張區塊
						stage_x = rockman.getX() - 2 * 116;
					}
				}
			}
			else if (transitionState == 30) { //廊道的camera
				if (rightPressed) {
					if (stage_x < 5632 && rockman.getX() - 232 > 4608) {
						stage_x = rockman.getX() - 2 * 116;
					}
				}
				if (leftPressed) {
					if (stage_x > 4608 && rockman.getX() + 280 < 6144) { //首先洛克人+280要小於整張地圖最右邊，避免out of range，再來rockman要不在地圖那一層的最右邊的半張區塊
						stage_x = rockman.getX() - 2 * 116;
					}
				}
			}
			else { //轉場觸發
				if (transitionState == 1) { //向上轉場
					stage_y -= dy; //512
					if (stage_y % 512 == 0) { //總計位移64次
						transitionState = 0;
					}
				}
				else if (transitionState == 2) { //向下轉場
					stage_y += dy; //512;
					if (stage_y % 512 == 0) {
						transitionState = 0;
					}
				}
				else if (transitionState == 3) { //進廊道的轉場
					stage_x += dx; //512;
					if (stage_x % 512 == 0) {
						transitionState = 30;
					}
				}
				else if (transitionState == 4) {
					stage_x += dx; //512;
					if (stage_x % 512 == 0) {
						transitionState = 40;
					}
				}
			}

			cutman_stage.SetTopLeft(-stage_x, -stage_y);
		};
		void Onshow() {
			cutman_stage.ShowBitmap(2);

			for (size_t i = 0; i < enemyContainer.size(); i++)
			{
				enemyContainer[i]->OnShow();
			}

			rockman.Onshow(stage_x, stage_y); // 256*2是最邊邊，48是角色寬度
			rockman_blood.SetFrameIndexOfBitmap(rockman.getBlood());
			rockman_blood.ShowBitmap(2);
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
		int dx = 4;
		int dy = 8;
		int transitionState = 0;
		// 初始點
		int stage_x = 0;	//以整張圖的角度，所以setTopLeft要用負的
		int stage_y = 4096; //以整張圖的角度，所以setTopLeft要用負的


		//剪刀窗戶的地方
		//int stage_x = 768*2;	//以整張圖的角度，所以setTopLeft要用負的
		//int stage_y = 1024*2; //以整張圖的角度，所以setTopLeft要用負的

		//int stage_x = 2048 * 2;
		//int stage_y = 768 * 2;

		
		// 三個儲存點，之後再處理，X-Y要再對照一下
		int savePoint = 0;
		int savePoint_stage[3][2] = {
			{0, 4096},
			{2560, 1024},
			{2304*2, 768*2}};
		int savePoint_rockman[3][2] = {
			{232, 4368},
			{0, 0},
			{0, 0}
		};
		bool leftPressed;
		bool rightPressed;

		vector<Enemy*> enemyContainer;

		CutmanStageData dataSource;
		CMovingBitmap cutman_stage;
		CMovingBitmap rockman_blood;
		Character rockman;
	};
}