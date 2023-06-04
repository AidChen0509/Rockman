#pragma once
#include <fstream>
#include "../Library/audio.h"
namespace game_framework {
	class FiremanStage
	{
	public:
		FiremanStage() {
			// map initialize
			this->readFile();
			rockman.setmap(map);
			fireman.setmap(map);
			// 初始化怪物
			
			enemyContainer.push_back(new Screw(112 * 2, 624 * 2, 0, 0));
			enemyContainer.push_back(new Screw(112 * 2, 560 * 2, 0, 0));
			enemyContainer.push_back(new Screw(232 * 2, 560 * 2, 0, 0));
			enemyContainer.push_back(new Screw(432 * 2, 560 * 2, 0, 0));
			enemyContainer.push_back(new Screw(352 * 2, 624 * 2, 0, 0));
			enemyContainer.push_back(new Screw(2728 * 2, 96 * 2, 1, 0));
			enemyContainer.push_back(new Screw(2888 * 2, 96 * 2, 1, 0));
			enemyContainer.push_back(new Screw(3032 * 2, 96 * 2, 1, 0));
			enemyContainer.push_back(new Screw(3160 * 2, 96 * 2, 1, 0));
			enemyContainer.push_back(new Gaby(2000 * 2, 56 * 2, 1792 * 2, 56 * 2));
			enemyContainer.push_back(new Gaby(1792 * 2, 120 * 2, 2000 * 2, 120 * 2));
			enemyContainer.push_back(new Gaby(2032 * 2, 184 * 2, 1760 * 2, 184 * 2));

			enemyContainer.push_back(new Bolt(800 * 2, 128 * 2));
			enemyContainer.push_back(new Bolt(784 * 2, 176 * 2));
			enemyContainer.push_back(new Bolt(960 * 2, 112 * 2));


			enemyContainerBehindScene.push_back(new Fireball(1696 * 2, 256 * 2, 1696 * 2, 336 * 2, 0, 5));
			enemyContainerBehindScene.push_back(new Fireball(1704 * 2, 336 * 2, 1608 * 2, 336 * 2, 1, 6));
			enemyContainerBehindScene.push_back(new Fireball(1600 * 2, 344 * 2, 1600 * 2, 408 * 2, 0, 4));
			enemyContainerBehindScene.push_back(new Fireball(1608 * 2, 400 * 2, 1736 * 2, 400 * 2, 2, 8));
			enemyContainerBehindScene.push_back(new Fireball(1728 * 2, 408 * 2, 1728 * 2, 488 * 2, 0, 5));




			/*
			enemyContainerBehindScene.push_back(new FireBlock(624 * 2, 672 * 2, 608 * 2));
			enemyContainerBehindScene.push_back(new FireBlock(592 * 2, 448 * 2, 384 * 2));
			enemyContainerBehindScene.push_back(new FireBlock(560 * 2, 384 * 2, 320 * 2));
			enemyContainerBehindScene.push_back(new FireBlock(624 * 2, 160 * 2, 96 * 2));
			enemyContainerBehindScene.push_back(new FireBlock(656 * 2, 192 * 2, 128 * 2));
			enemyContainerBehindScene.push_back(new FireBlock(1104 * 2, 128 * 2, 64 * 2));
			enemyContainerBehindScene.push_back(new FireBlock(1136 * 2, 96 * 2, 32 * 2));
			enemyContainerBehindScene.push_back(new FireBlock(1168 * 2, 448 * 2, 384 * 2));
			enemyContainerBehindScene.push_back(new FireBlock(1232 * 2, 448 * 2, 384 * 2));
			enemyContainerBehindScene.push_back(new FireBlock(1104 * 2, 704 * 2, 640 * 2));
			enemyContainerBehindScene.push_back(new FireBlock(1168 * 2, 672 * 2, 608 * 2));
			enemyContainerBehindScene.push_back(new FireBlock(1520 * 2, 704 * 2, 640 * 2));
			enemyContainerBehindScene.push_back(new FireBlock(1584 * 2, 672 * 2, 608 * 2));
			enemyContainerBehindScene.push_back(new FireBlock(2480 * 2, 160 * 2, 96 * 2));
			enemyContainerBehindScene.push_back(new FireBlock(2512 * 2, 160 * 2, 96 * 2));
			*/



		};
		~FiremanStage() {
			for (size_t i = 0; i < enemyContainer.size(); i++)
			{
				delete enemyContainer[i];
			}
			for (size_t i = 0; i < enemyContainerBehindScene.size(); i++)
			{
				delete enemyContainerBehindScene[i];
			}
		};
		void OnInit() {
			fireman_Stage.LoadBitmapByString({ "resources/stage/firemanStage/FiremanStage.bmp" }, RGB(128, 0, 128)); //加上去背整個變超怪，很多細節被去掉
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
												"resources/rockman/blood/blood28.bmp", });
			rockman_blood.SetTopLeft(48, 50);
			stageShine.LoadBitmapByString({
				"resources/stage/firemanStage/firemanStageShine.bmp",
				"resources/stage/purple.bmp",
				"resources/stage/firemanStage/firemanStageShine.bmp",
				"resources/stage/purple.bmp",
				"resources/stage/firemanStage/firemanStageShine.bmp",
				"resources/stage/purple.bmp",
				"resources/stage/firemanStage/firemanStageShine.bmp",
				"resources/stage/purple.bmp",
				"resources/stage/firemanStage/firemanStageShine.bmp",
				"resources/stage/purple.bmp",
				"resources/stage/firemanStage/firemanStageShine.bmp",
				"resources/stage/purple.bmp",
				}, RGB(128, 0, 128));
			stageShine.SetTopLeft(0, 0);
			stageShine.SetAnimation(100, true);



			bossGate.LoadBitmapByString({
				"resources/stage/firemanStage/bossStageGate1.bmp",
				"resources/stage/firemanStage/bossStageGate2.bmp",
				"resources/stage/firemanStage/bossStageGate3.bmp",
				"resources/stage/firemanStage/bossStageGate4.bmp",
				});
			bossGate.SetTopLeft(0, 192); // TO Change
			bossGate.SetAnimation(100, true);

			// To change
			fireman_blood.LoadBitmapByString({
				{ "resources/enemy/cutman/blood/blood0.bmp" },
				{ "resources/enemy/cutman/blood/blood1.bmp" },
				{ "resources/enemy/cutman/blood/blood2.bmp" },
				{ "resources/enemy/cutman/blood/blood3.bmp" },
				{ "resources/enemy/cutman/blood/blood4.bmp" },
				{ "resources/enemy/cutman/blood/blood5.bmp" },
				{ "resources/enemy/cutman/blood/blood6.bmp" },
				{ "resources/enemy/cutman/blood/blood7.bmp" },
				{ "resources/enemy/cutman/blood/blood8.bmp" },
				{ "resources/enemy/cutman/blood/blood9.bmp" },
				{ "resources/enemy/cutman/blood/blood10.bmp" },
				{ "resources/enemy/cutman/blood/blood11.bmp" },
				{ "resources/enemy/cutman/blood/blood12.bmp" },
				{ "resources/enemy/cutman/blood/blood13.bmp" },
				{ "resources/enemy/cutman/blood/blood14.bmp" },
				{ "resources/enemy/cutman/blood/blood15.bmp" },
				{ "resources/enemy/cutman/blood/blood16.bmp" },
				{ "resources/enemy/cutman/blood/blood17.bmp" },
				{ "resources/enemy/cutman/blood/blood18.bmp" },
				{ "resources/enemy/cutman/blood/blood19.bmp" },
				{ "resources/enemy/cutman/blood/blood20.bmp" },
				{ "resources/enemy/cutman/blood/blood21.bmp" },
				{ "resources/enemy/cutman/blood/blood22.bmp" },
				{ "resources/enemy/cutman/blood/blood23.bmp" },
				{ "resources/enemy/cutman/blood/blood24.bmp" },
				{ "resources/enemy/cutman/blood/blood25.bmp" },
				{ "resources/enemy/cutman/blood/blood26.bmp" },
				{ "resources/enemy/cutman/blood/blood27.bmp" },
				{ "resources/enemy/cutman/blood/blood28.bmp" },
				});
			fireman_blood.SetTopLeft(80, 50);
			fireman_blood.SetAnimation(75, true);

			fireman_Stage.SetTopLeft(-stage_x, -stage_y);
			rockman.OnInit(stage_x, stage_y);
			// fireman
			fireman.OnInit();
			for (size_t i = 0; i < enemyContainer.size(); i++)
			{
				enemyContainer[i]->OnInit();
			}
			for (size_t i = 0; i < enemyContainerBehindScene.size(); i++)
			{
				enemyContainerBehindScene[i]->OnInit();
			}
		};
		void OnMove() {

			int rockmanX = rockman.getX();
			int rockmanY = rockman.getY();
			// 判斷transition state的更換
			if (transitionState == -1) { // -1代表在死亡動畫
				if (rockman.deadAnimationDone()) { //死亡動畫結束
					// 回到正常的transition，順便重製
					if (savePoint == 2) {
						transitionState = 30;
					}
					else {
						transitionState = 0;
					}
					if (rockman.getLives() - 1 > 0) { // 因為到onbegin才會扣命，所以這邊判斷會延遲，要扣1
						this->OnBeginState(savePoint);
					}
					else {
						// game over
						gameState = 2;
					}
				}
			}
			else if (((rockmanY + 12) / 512) != (stage_y / 512)) {
				//除以512為了檢查是否在同一層
				// case 1 洛克人在上面一層 -> (rockmanY + 12) / 512 < (stage_y / 512)
				if (((rockmanY + 12) / 512) < (stage_y / 512)) {
					transitionState = 1; // 1 代表向上轉場
				}
				// case 2  洛克人在下面一層 -> (rockmanY + 12) / 512 > (stage_y / 512)
				else {
					transitionState = 2; // 2 代表向上轉場
				}
			}
			else if (map[rockmanY / 32][(rockmanX + 2 * (24 - 1 - 4)) / 32] == 4) {
				if (transitionState == 30) {
					transitionState = 4; //進王關transition
				}
				else if (transitionState == 0) {
					transitionState = 3; //進王關廊道transition
				}
			}

			rockman.OnMove(stage_x, stage_y, transitionState);
			// cutman
			fireman.OnMove(stage_x, stage_y, rockmanX, rockmanY, transitionState);
			for (size_t i = 0; i < enemyContainer.size(); i++)
			{
				enemyContainer[i]->OnMove(rockmanX, rockmanY, stage_x, stage_y);
			}
			for (size_t i = 0; i < enemyContainerBehindScene.size(); i++)
			{
				enemyContainerBehindScene[i]->OnMove(rockmanX, rockmanY, stage_x, stage_y);
			}
			// 根據不同的transitionState判斷敵人碰撞
			if (transitionState == 0 || transitionState == 30) {
				for (size_t i = 0; i < enemyContainer.size(); i++)
				{
					if (enemyContainer[i]->getIsActivate()) { //怪物is acitivated
						if (!rockman.getIsHit() && enemyContainer[i]->successfullyAttack(rockman.getCurrentBitmap())) {
							// 沒被攻擊中，而且被打到
							// 可以呼叫怪物的isAttackFromRight()，set給rockman
							CAudio::Instance()->Play(7, false);
							rockman.setIsHit();
							rockman.decreaseBlood(enemyContainer[i]->getDamage());
							rockman.setIsAttackedFromRight(enemyContainer[i]->isAttackFromRight());
						}

						for (int j = 0; j < 3; j++)
						{
							if (rockman.getIsShot(j)) {
								if (enemyContainer[i]->beenAttacked(rockman.getBullet(j))) {
									rockman.setIsShotfalse(j);
								}
							}
						}

					}
				}
				for (size_t i = 0; i < enemyContainerBehindScene.size(); i++)
				{
					if (enemyContainerBehindScene[i]->getIsActivate()) { //怪物is acitivated
						if (!rockman.getIsHit() && enemyContainerBehindScene[i]->successfullyAttack(rockman.getCurrentBitmap())) {
							// 沒被攻擊中，而且被打到
							// 可以呼叫怪物的isAttackFromRight()，set給rockman
							CAudio::Instance()->Play(7, false);
							rockman.setIsHit();
							rockman.decreaseBlood(enemyContainerBehindScene[i]->getDamage());
							rockman.setIsAttackedFromRight(enemyContainerBehindScene[i]->isAttackFromRight());
						}
						for (int j = 0; j < 3; j++)
						{
							if (rockman.getIsShot(j)) {
								if (enemyContainerBehindScene[i]->beenAttacked(rockman.getBullet(j))) {
									rockman.setIsShotfalse(j);
								}
							}
						}
					}
				}
			}
			else if (transitionState == 40) {
				if (!rockman.getIsHit() && fireman.successfullyAttack(rockman.getCurrentBitmap())) {
					// 沒被攻擊中，而且被打到
					// 可以呼叫怪物的isAttackFromRight()，set給rockman
					CAudio::Instance()->Play(7, false);
					rockman.setIsHit();
					rockman.decreaseBlood(fireman.getDamage());
					rockman.setIsAttackedFromRight(fireman.isAttackFromRight());
				}
				// 豆彈打到boss
				for (int j = 0; j < 3; j++)
				{
					if (rockman.getIsShot(j)) {
						if (fireman.beenAttacked(rockman.getBullet(j))) {
							CAudio::Instance()->Play(5, false);
							rockman.setIsShotfalse(j);
						}
					}
				}
				
			}


			// 計算array index的一個小概念，供參
			//int index_x = stage_x/32; //最左邊的index : index_x
			//int index_y = stage_y/32; //最上面的index : index_y 
									  //最右邊的index : index_x + 16 //若 >= 208，不做array的access
									  //最下面的index : index_y + 16 //若 >= 144，不做array的access
			// FiremanStage camera
			if (transitionState == 0) {
				// 王關之前的camera
				// 每個and的註解，以符合所有情況，應該沒問題了
				// 1)第一個廊道前最後一張512*512的座標 = 4096
				// 2)檢查camera向右移動會不會超出地圖邊界
				// 3)因為最一開始的圖示貼在邊邊，x座標已經是0了，不能再去access -1 的index
				// 4)檢查除了開場以外的camera向左會不會超出地圖邊界
				if (stage_x < 4608 && map[stage_y / 32][(stage_x + 512 + 1) / 32] != -1
					&& rockman.getX() - 232 > 0 && map[stage_y / 32][(rockman.getX() - 232) / 32] != -1) {
					stage_x = rockman.getX() - 2 * 116;
				}
				// 我更改初始畫面到到廊道前，發現需要加上這個else if 不然會跑掉
				else if (stage_x > 0 && map[stage_y / 32][(stage_x - 1) / 32] != -1  //首先stage_x要先>0，避免out of range，再來要stage_x還沒到最左邊(左邊那格不為-1)，否則不動
					&& rockman.getX() + 280 < 5120 && map[stage_y / 32][(rockman.getX() + 280) / 32] != -1) { //首先洛克人+280要小於整張地圖最右邊，避免out of range，再來rockman要不在地圖那一層的最右邊的半張區塊
					stage_x = rockman.getX() - 2 * 116;
				}

			}
			else if (transitionState == 30) {
				//廊道的camera
				// 因為很單純，所以直接寫死
				if ((stage_x < 6144 && rockman.getX() - 232 > 5120) || (stage_x > 5120 && rockman.getX() + 280 < 6656)) {
					stage_x = rockman.getX() - 2 * 116;
				}

			}
			else if (transitionState == 40) {

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
					if ((stage_x / 512) != ((stage_x - dx) / 512)) {
						stage_x = (stage_x / 512) * 512;
						transitionState = 30;
					}
				}
				
				else if (transitionState == 4) {
					stage_x += dx; //512;
					if ((stage_x / 512) != ((stage_x - dx) / 512)) {
						stage_x = (stage_x / 512) * 512;
						CAudio::Instance()->Stop(0);
						CAudio::Instance()->Play(8, true);
						stageShine.ToggleAnimation();
						transitionState = 31;
					}
				}
				else if (transitionState == 31) {
					if (stageShine.IsAnimationDone()) {
						bossGate.ToggleAnimation();
						transitionState = 32;
					}
				}
				else if (transitionState == 32) {
					if (bossGate.IsAnimationDone()) {
						//bossGate.SetFrameIndexOfBitmap(3);
						fireman_blood.ToggleAnimation();
						CAudio::Instance()->Pause();
						CAudio::Instance()->Play(9, false);
						transitionState = 33;
					}
				}
				else if (transitionState == 33) {
					if (fireman_blood.IsAnimationDone()) {
						CAudio::Instance()->Stop(9);
						CAudio::Instance()->Resume();
						transitionState = 40;
					}
				}
				
				// 40  is the state rockman can move
			}

			// 到達savePoint的判斷
			if (savePoint == 0 && stage_x == savePoint_stage[1][0] && stage_y <= savePoint_stage[1][1]) {
				savePoint = 1;
			}
			else if (savePoint == 1 && stage_x >= savePoint_stage[2][0] && stage_y == savePoint_stage[2][1]) {
				savePoint = 2;
			}
			fireman_Stage.SetTopLeft(-stage_x, -stage_y);

			checkReset(); //TODO: 裡面需要一些判斷來決定要不要respawn(呼叫個別的onBeginState)
		};
		void Onshow() {
			if (transitionState == 0 || transitionState == 30) {
				for (size_t i = 0; i < enemyContainerBehindScene.size(); i++)
				{
					enemyContainerBehindScene[i]->OnShow();
				}
			}
			fireman_Stage.ShowBitmap(2);
			
			if (transitionState == 31) {
				stageShine.ShowBitmap(2);
			}
			
			rockman.Onshow(stage_x, stage_y, transitionState); // 256*2是最邊邊，48是角色寬度
			fireman.OnShow(transitionState);

			// new edit
			
			if (31 <= transitionState && transitionState < 40) {
				inBossStage = true;
				fireman_blood.ShowBitmap(2);
			}
			else if (transitionState == 40 || (inBossStage && transitionState == -1)) {
				// TODO: 要注意如果blood < 0
				
				if (fireman.getBlood() >= 0)
					fireman_blood.SetFrameIndexOfBitmap(fireman.getBlood());
				else
					fireman_blood.SetFrameIndexOfBitmap(0);
				fireman_blood.ShowBitmap(2);
				
			}
			if (transitionState >= 32 || (inBossStage && transitionState == -1)) {
				bossGate.ShowBitmap(2);
			}
			


			// rockman.Onshow(stage_x, stage_y, transitionState); // 256*2是最邊邊，48是角色寬度
			if (transitionState == 0 || transitionState == 30) {
				for (size_t i = 0; i < enemyContainer.size(); i++)
				{
					enemyContainer[i]->OnShow();

				}
			}
			/*
			CDC *px = CDDraw::GetBackCDC();
			CTextDraw::ChangeFontLog(px, 15, "微軟正黑體", RGB(255, 255, 0));
			message = "Y =  " + to_string(enemyContainerBehindScene[0]->getY());
			CTextDraw::Print(px, 44, 180, message.c_str());
			CDDraw::ReleaseBackCDC();
			*/

			rockman_blood.SetFrameIndexOfBitmap(rockman.getBlood());
			rockman_blood.ShowBitmap(2);

		}
		void readFile() {
			// [48][224]
			
			// -1 for green bg
			// 0 for air
			// 1 for wall
			// 2 for ladder
			// 4 for gate->trnasition
			// 5 for out of map(或是岩漿之類的)->dead
			// 6 for laddertop
			ifstream ifs("Source/Maps/firemanMap.txt");
			int num;
			for (int i = 0; i < 48; i++) {
				vector<int> temp;
				for (int j = 0; j < 224; j++) {
					ifs >> num;
					temp.push_back(num);
				}
				map.push_back(temp);
			}

			ifs.close();
		}
		void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
			rockman.OnKeyDown(nChar, nRepCnt, nFlags);
			if (nChar == VK_LEFT) {
				leftPressed = true;
			}
			if (nChar == VK_RIGHT) {
				rightPressed = true;
			}
			if (nChar == 0x52) {
				rockman.resetBlood();
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
		int getGamestate() {
			// 1過關、2OVER
			return gameState;
		}
		void OnBeginState(int point) {
			
			if (point == -1) {
				// 第一次進遊戲
				gameState = 0;
				savePoint = 0;
				transitionState = 0;
				stage_x = savePoint_stage[0][0];
				stage_y = savePoint_stage[0][1];
				rockman.OnBeginState(savePoint_rockman[0][0], savePoint_rockman[0][1], -1);
				fireman.OnBeginState();
				fireman_blood.SetFrameIndexOfBitmap(0); // 圖片也要歸零，不然下次進關卡看到的會先有血量
				inBossStage = false;
			}
			else if (point == 0) {
				transitionState = 0;
				stage_x = savePoint_stage[0][0];
				stage_y = savePoint_stage[0][1];
				rockman.OnBeginState(savePoint_rockman[0][0], savePoint_rockman[0][1], 0);

			}
			else if (point == 1) {
				transitionState = 0;
				stage_x = savePoint_stage[1][0];
				stage_y = savePoint_stage[1][1];
				rockman.OnBeginState(savePoint_rockman[1][0], savePoint_rockman[1][1], 1);
			}
			else if (point == 2) {
				// 在隧道的頭
				transitionState = 30;
				CAudio::Instance()->Stop(8);
				CAudio::Instance()->Play(0, true);
				stage_x = savePoint_stage[2][0];
				stage_y = savePoint_stage[2][1];
				rockman.OnBeginState(savePoint_rockman[2][0], savePoint_rockman[2][1], 2);
				fireman.OnBeginState();
				fireman_blood.SetFrameIndexOfBitmap(0); // 圖片也要歸零，不然下次進關卡看到的會先有血量
				inBossStage = false;
			}

			// 自從初始過後，不會再改變到
			// dx = 4;
			// dy = 8;

			// TODO 其他怪物的OnBeginState，可以塞入個別的savePoint，提高效能，或是全部都塞這
			enemyReset();
			
		}
		void enemyReset() {
			for (size_t i = 0; i < enemyContainer.size(); i++)
			{
				enemyContainer[i]->OnBeginState();
			}
			for (size_t i = 0; i < enemyContainerBehindScene.size(); i++)
			{
				enemyContainerBehindScene[i]->OnBeginState();
			}
		}
		void checkReset() {
			
			if (fireman.getBlood() <= 0) {
				//贏了
				if (fireman.deadAnimationDone()) {
					gameState = 1;
				}
			}
			else if (rockman.getBlood() <= 0 || rockman.getDieDirectly()) {
				// 只要血量低於0就是要啟動死亡動畫
				// 播放死亡音效，once
				transitionState = -1;
			}
			/*else if (rockman.getLives() > 0) {
				// blood
				int rockman_blood = rockman.getBlood();
				if ((rockman_blood <= 0 || rockman.getDieDirectly())) {
					transitionState = -1;
					// this->OnBeginState(savePoint);
				}
			}
			else {
				// game over
				transitionState = -1;

				if (rockman.canGameOver()) {
					gameState = 2;
				}
			}*/
		}

	private:


		// camera place chasing rockman at x-axis not y-axis 
		int dx = 4;
		int dy = 8;
		int transitionState = 0;
		int gameState = 0;
		bool inBossStage = false;
		// 初始點
		//int stage_x = 0;	//以整張圖的角度，所以setTopLeft要用負的
		//int stage_y = 4096; //以整張圖的角度，所以setTopLeft要用負的

		//剪刀窗戶的地方
		//int stage_x = 768*2;	//以整張圖的角度，所以setTopLeft要用負的
		//int stage_y = 1024*2; //以整張圖的角度，所以setTopLeft要用負的

		int stage_x = 0;
		int stage_y = 1024;


		// 三個儲存點，之後再處理，X-Y要再對照一下
		int savePoint = 0;
		int savePoint_stage[3][2] = {
			{0, 1024},
			{2048, 1024},
			{5120, 0}
		}; 
		int savePoint_rockman[3][2] = { //x: stage + 232
			{232, 1360},
			{2290, 1296},
			{5148, 272}
		};
		bool leftPressed;
		bool rightPressed;

		string message;
		vector<Enemy*> enemyContainer;
		vector<Enemy*> enemyContainerBehindScene;

		vector<vector<int>> map;

		CMovingBitmap fireman_blood;
		CMovingBitmap fireman_Stage;
		CMovingBitmap rockman_blood;
		CMovingBitmap stageShine;
		CMovingBitmap bossGate;


		Character rockman;
		Fireman fireman;
	};
}