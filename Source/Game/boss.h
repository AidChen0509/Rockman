#pragma once
#include "../Library/audio.h"
namespace game_framework {
	class Cutman
	{
	public:
		Cutman() {};
		~Cutman() {};
		void OnInit() {
			timer.LoadBitmapByString({
				"resources/white.bmp",
				"resources/white.bmp",
				}, RGB(255, 255, 255));
			timer.SetTopLeft(0, 0);

			beingAttackY[0].LoadBitmapByString({
				"resources/enemy/cutman/walkLeftY2.bmp",
				}, RGB(128, 0, 128));
			beingAttackY[1].LoadBitmapByString({
				"resources/enemy/cutman/walkRightY2.bmp",
				}, RGB(128, 0, 128));
			beingAttackN[0].LoadBitmapByString({
				"resources/enemy/cutman/walkLeftN2.bmp",
				}, RGB(128, 0, 128));
			beingAttackN[1].LoadBitmapByString({
				"resources/enemy/cutman/walkRightN2.bmp",
				}, RGB(128, 0, 128));

			// 閃5次
			shine.LoadBitmapByString({ 
				"resources/enemy/cutman/shine.bmp", "resources/enemy/cutman/purple.bmp",
				"resources/enemy/cutman/shine.bmp", "resources/enemy/cutman/purple.bmp",
				"resources/enemy/cutman/shine.bmp", "resources/enemy/cutman/purple.bmp",
				"resources/enemy/cutman/shine.bmp", "resources/enemy/cutman/purple.bmp",
				"resources/enemy/cutman/shine.bmp", "resources/enemy/cutman/purple.bmp",
				}, RGB(128, 0, 128));
			shine.SetAnimation(100, true);

			throwing[0].LoadBitmapByString({
				"resources/enemy/cutman/throwLeft0.bmp",
				"resources/enemy/cutman/throwLeft1.bmp",
				}, RGB(128, 0, 128));
			throwing[0].SetAnimation(300, true);
			throwing[1].LoadBitmapByString({
				"resources/enemy/cutman/throwRight0.bmp",
				"resources/enemy/cutman/throwRight1.bmp",
				}, RGB(128, 0, 128));
			throwing[1].SetAnimation(300, true);


			restingY[0].LoadBitmapByString({
				"resources/enemy/cutman/idleLeftOpenY.bmp",
				"resources/enemy/cutman/idleLeftCloseY.bmp",
				}, RGB(128, 0, 128));
			restingY[0].SetAnimation(150, false);

			restingY[1].LoadBitmapByString({
				"resources/enemy/cutman/idleRightOpenY.bmp",
				"resources/enemy/cutman/idleRightCloseY.bmp",
				}, RGB(128, 0, 128));
			restingY[1].SetAnimation(150, false);

			restingN[0].LoadBitmapByString({
				"resources/enemy/cutman/idleLeftOpenN.bmp",
				"resources/enemy/cutman/idleLeftCloseN.bmp",
				}, RGB(128, 0, 128));
			restingN[0].SetAnimation(150, false);

			restingN[1].LoadBitmapByString({
				"resources/enemy/cutman/idleRightOpenN.bmp",
				"resources/enemy/cutman/idleRightCloseN.bmp",
				}, RGB(128, 0, 128));
			restingN[1].SetAnimation(150, false);

			runningY[0].LoadBitmapByString({
				"resources/enemy/cutman/walkLeftY1.bmp",
				"resources/enemy/cutman/walkLeftY2.bmp",
				"resources/enemy/cutman/walkLeftY3.bmp",
				}, RGB(128, 0, 128));
			runningY[0].SetAnimation(200, false);

			runningY[1].LoadBitmapByString({
				"resources/enemy/cutman/walkRightY1.bmp",
				"resources/enemy/cutman/walkRightY2.bmp",
				"resources/enemy/cutman/walkRightY3.bmp",
				}, RGB(128, 0, 128));
			runningY[1].SetAnimation(200, false);

			runningN[0].LoadBitmapByString({
				"resources/enemy/cutman/walkLeftN1.bmp",
				"resources/enemy/cutman/walkLeftN2.bmp",
				"resources/enemy/cutman/walkLeftN3.bmp",
				}, RGB(128, 0, 128));
			runningN[0].SetAnimation(200, false);

			runningN[1].LoadBitmapByString({
				"resources/enemy/cutman/walkRightN1.bmp",
				"resources/enemy/cutman/walkRightN2.bmp",
				"resources/enemy/cutman/walkRightN3.bmp", 
				}, RGB(128, 0, 128));
			runningN[1].SetAnimation(200, false);

			
			jumpingY[0].LoadBitmapByString({"resources/enemy/cutman/jumpLeftY.bmp"}, RGB(128, 0, 128));
			jumpingY[1].LoadBitmapByString({ "resources/enemy/cutman/jumpRightY.bmp" }, RGB(128, 0, 128));
			jumpingN[0].LoadBitmapByString({ "resources/enemy/cutman/jumpLeftN.bmp" }, RGB(128, 0, 128));
			jumpingN[1].LoadBitmapByString({ "resources/enemy/cutman/jumpRightN.bmp" }, RGB(128, 0, 128));
			

			rollingCutter[0].LoadBitmapByString({
				"resources/enemy/cutman/rollingCutterUp.bmp",
				"resources/enemy/cutman/rollingCutterLeft.bmp",
				"resources/enemy/cutman/rollingCutterDown.bmp",
				}, RGB(128, 0, 128));
			rollingCutter[0].SetAnimation(100, false);
			rollingCutter[1].LoadBitmapByString({
				"resources/enemy/cutman/rollingCutterUp.bmp",
				"resources/enemy/cutman/rollingCutterRight.bmp",
				"resources/enemy/cutman/rollingCutterDown.bmp",
				}, RGB(128, 0, 128));
			rollingCutter[1].SetAnimation(100, false);

			for (int i = 0; i < 12; i++)
			{
				deadBubble[i].LoadBitmapByString({
					"resources/enemy/dead0.bmp",
					"resources/enemy/dead1.bmp",
					"resources/enemy/dead2.bmp",
					"resources/enemy/dead3.bmp",
					}, RGB(128, 0, 128));
				if (i < 4) {
					deadBubble[i].SetAnimation(50, false);
				}
				else {
					deadBubble[i].SetAnimation(55, false);
				}
			}

		};
		void OnMove(int stageX, int stageY, int rockmanX, int rockmanY, int transitionState) {
			// 保留轉場state等待轉場

			/* 
			距離很遠-> 走到中距離 ->擺架式
								  ->距離介於中跟進之間，甩出剪刀後重複判斷，連續三次後仍為此區間，則直接跳向洛克人
			太遠會先靠近，到中距離的時候丟擺架式出剪刀，丟完發現洛克人跑出中距離，會用跳的過去追他
			*/
			if (rockmanX >= x) {
				facingLeft = false;
			}
			else {
				facingLeft = true;
			}
			int distance = abs(rockmanX - x);
			
			// 等待stage的轉場動畫

			if (transitionState == 40) { //開始遊戲的state
				// RANGE
				// near = 32 (32*1
				// mid = 128 (3*32
				// long = 
				// middle of the bitmap = 3204 * 2
				if (deadState != 0) {
					//觸發死亡動畫
					if (deadState == 1) {
						bool tempBool = false;
						for (int i = 0; i < 12; i++)
						{
							if (stageX - 16 * 2 <= bubble_XY[i][0] && bubble_XY[i][0] <= stageX + 512
								&& stageY - 16 * 2 <= bubble_XY[i][1] && bubble_XY[i][1] <= stageY + 512) {
								bubble_XY[i][0] += bubble_dXdY[i][0];
								bubble_XY[i][1] += bubble_dXdY[i][1];
								tempBool = true;
							}
						}
						if (!tempBool) {
							deadState = 2;
						}
					}

					for (int i = 0; i < 12; i++)
					{
						deadBubble[i].SetTopLeft(int(bubble_XY[i][0]) - stageX, int(bubble_XY[i][1]) - stageY);
					}
				}
				else if (isHit) {
					shine.ToggleAnimation();
					isHit = false;
				}
				else if (!shine.IsAnimationDone()) {
					if (beenAttackedByLeft) {
						if (map[y / 32][(x + 2 + 48) / 32] != 1) {
							x += 2;
						}
					}
					else {
						if (map[y / 32][(x - 2) / 32] != 1) {
							x -= 2;
						}
					}
					if (map[(y + 64) / 32][x / 32] != 1) { //可以掉落
						if (map[(y + 62 + 16) / 32][x / 32] != 1) {
							y += 16;
						}
						else {
							y = ((y / 32) + 1) * 32;
							dy = 12;
						}
					}
				}
				else if (state == 0) { // walk to the middle
					if (distance > 128) { // bigger than mid
						// keep walking and jump to rockman
						// state = 2;
						if (map[y / 32][(x - dx) / 32] != 1) {
							x -= dx;
							isWalking = true;
						}
						else {
							// state: 2 is for jumping to rockman set target before jump
							state = 2;
							jumpLeft = true;
							dx = distance / 24; //best case: 不受障礙物抵擋，就能剛好到達目的地
							dy = 12;
							// Question: 需要在這先設定isJumping嗎
						}
					}
					else {
						// 到點準備蓄力
						isWalking = false;
						state = 1;
						timer.SetAnimation(1500, true);
						timer.ToggleAnimation();
					}
				}
				else if (state == 1){
					if (timer.IsAnimationDone()){ //蓄力完成，丟出剪刀
						if (facingLeft) {
							// won't get in this if statement
							throwing[0].ToggleAnimation();
							throwingLeft = true;
						}
						else {
							throwing[1].ToggleAnimation();
							throwingLeft = false;
						}
						
						isThrowing = true;
						state = 3;
						// isWalking = false;
					}
				}
				else if (state == 2) {
					// 已設定過jumpLeft, dx, dy
					// 跳過去
					isJumping = true;
					if (jumpLeft) {
						// 不確定需不需要小段的位移，如dx超出空隙超多(會看起來很怪
						if (map[y / 32][(x - dx) / 32] != 1) {
							x -= dx;
						}
					}
					else {
						if (map[y / 32][(x + dx + 48) / 32] != 1) {
							x += dx;
						}
					}

					if ((jumpCount % 2 == 0) && (jumpCount != 0)) {
						dy -= 1;
					}
					jumpCount++;
					if (dy < 0) { //下墜
						// to fix 小縫隙掉落
						if (map[(y + 64) / 32][x / 32] != 1) { //可以掉落
							if (map[(y + 62 - dy) / 32][x / 32] != 1) {
								y -= dy;
							}
							else {
								y = ((y / 32) + 1) * 32;
							}
						}
						else { //落地
							dy = 12;
							dx = 4;
							jumpCount = 0;
							isJumping = false;
							state = 5; 
						}
					}
					else {
						//上升
						y -= dy;
					}
				}
				else if (state == 3) {
					// use facingLeft to determine which throw is toggled might cause some bug(what if rockman switch from left to right just in 100ms?
					// try to use a bool to record the former throwing direction	
					if (throwingLeft) {
						if (throwing[0].GetFrameIndexOfBitmap() == 1) {
							// throwing left
							playsound = true;
							weaponThrew = true;
							// count dx dy
							weapon_dx = -6;
							if (rockmanY >= y) {
								weapon_dy = ((rockmanY - y) / ((distance / 4) + 1));
							}
							else {
								weapon_dy = -((y - rockmanY) / ((distance / 4) + 1));
							}
							weaponX = x;
							weaponY = y;
							isWeaponGo = true;
							state = 4;
						}
					}
					else {
						if (throwing[1].GetFrameIndexOfBitmap() == 1) {
							playsound = true;
							weaponThrew = true;
							// count dx dy
							weapon_dx = 6;
							if (rockmanY >= y) {
								weapon_dy = ((rockmanY - y) / (distance / 4));
							}
							else {
								weapon_dy = -((y - rockmanY) / (distance / 4));
							}

							weaponX = x + 8;
							weaponY = y;
							isWeaponGo = true;
							state = 4;
						}
					}

					// to be delete: 為了測試boss死掉會不會跳轉
					// blood -= 28;
					/*
					if (timer.IsAnimationDone()) {
						if (throwingLeft) {
							weapon_dx = -4;
							weaponX = x;
							weaponY = y;
						}
						else {
							weapon_dx = 4;
							weaponX = x + 8;
							weaponY = y;
						}
						if (rockmanY >= y) {
							weapon_dy = ((rockmanY - y) / (distance / 4));
						}
						else {
							weapon_dy = -((y - rockmanY) / (distance / 4));
						}
						timer.SetAnimation(300, true);
						timer.ToggleAnimation();
						weaponThrew = true;
						isWeaponGo = true;
						state = 4;
					}
					*/
					
				}
				else if (state == 4) {
					if (throwing[0].IsAnimationDone() && throwing[1].IsAnimationDone()) {
					// if(timer.IsAnimationDone()){
						isThrowing = false;
						state = 5;
					}
				}
				else if (state == 5) {
					if (weaponThrew) {
						//  can't throw
						if (distance > 128) {
							// TO be fix: 不確定需不需要處理掉落
							if (rockmanX < x) {
								if (map[y / 32][(x - dx) / 32] != 1) {
									x -= dx;
								}
							}
							else {
								if (map[y / 32][(x + dx + 48) / 32] != 1) {
									x += dx;
								}
							}
							if (map[(y + 64) / 32][x / 32] != 1) { //可以掉落
								if (map[(y + 62 + 16) / 32][x / 32] != 1) {
									y += 16;
								}
								else {
									y = ((y / 32) + 1) * 32;
									dy = 12;
								}
							}
							isWalking = true;
						}
						else {
							// 等待迴力鏢回來
							isWalking = false;
							state = 6;
						}
					}
					else {
						if (distance <= 32) { // near
							if (facingLeft) {
								throwing[0].ToggleAnimation();
								throwingLeft = true;
							}
							else {
								throwing[1].ToggleAnimation();
								throwingLeft = false;
							}
							isThrowing = true;
							state = 7;
						}
						else if (distance <= 128) { // mid range
							// 蓄氣
							isWalking = false;
							state = 9;
							timer.SetAnimation(1500, true);
							timer.ToggleAnimation();
						}
						else { // far range
							state = 12;
						}
					}
				}
				else if (state == 6) {
					if (!weaponThrew) {
						state = 5;
					}
				}
				else if (state == 7) {
					if (throwingLeft) {
						if (throwing[0].GetFrameIndexOfBitmap() == 1) {
							// throwing left
							playsound = true;
							weaponThrew = true;
							// count dx dy
							weapon_dx = -6;
							if (rockmanY >= y) {
								weapon_dy = ((rockmanY - y) / ((distance / 4) + 1));
							}
							else {
								weapon_dy = -((y - rockmanY) / ((distance / 4) + 1));
							}
							weaponX = x;
							weaponY = y;
							isWeaponGo = true;
							state = 8;
						}
					}
					else {
						if (throwing[1].GetFrameIndexOfBitmap() == 1) {
							playsound = true;
							weaponThrew = true;
							// count dx dy
							weapon_dx = 6;
							if (rockmanY >= y) {
								weapon_dy = ((rockmanY - y) / ((distance / 4) + 1));
							}
							else {
								weapon_dy = -((y - rockmanY) / ((distance / 4) + 1));
							}

							weaponX = x + 8;
							weaponY = y;
							isWeaponGo = true;
							state = 8;
						}
					}
				}
				else if (state == 8) {
					if (throwing[0].IsAnimationDone() && throwing[1].IsAnimationDone()) {
						isThrowing = false;
						// go to state 3 in my state machine graph
						// todo
						state = 14;
					}
				}
				else if (state == 9) {
					if (timer.IsAnimationDone()) { //蓄力完成，丟出剪刀
						if (facingLeft) {
							throwing[0].ToggleAnimation();
							throwingLeft = true;
						}
						else {
							throwing[1].ToggleAnimation();
							throwingLeft = false;
						}
						isThrowing = true;
						state = 10;
					}
				}
				else if (state == 10) {
					if (throwingLeft) {
						if (throwing[0].GetFrameIndexOfBitmap() == 1) {
							// throwing left
							playsound = true;
							weaponThrew = true;
							// count dx dy
							weapon_dx = -6;
							if (rockmanY >= y) {
								weapon_dy = ((rockmanY - y) / ((distance / 4) + 1));
							}
							else {
								// to fix might cause division zero
								weapon_dy = -((y - rockmanY) / ((distance / 4) + 1));
							}
							weaponX = x;
							weaponY = y;
							isWeaponGo = true;
							state = 11;
						}
					}
					else {
						if (throwing[1].GetFrameIndexOfBitmap() == 1) {
							playsound = true;
							weaponThrew = true;
							// count dx dy
							weapon_dx = 6;
							if (rockmanY >= y) {
								weapon_dy = ((rockmanY - y) / ((distance / 4) + 1));
							}
							else {
								weapon_dy = -((y - rockmanY) / ((distance / 4) + 1));
							}

							weaponX = x + 8;
							weaponY = y;
							isWeaponGo = true;
							state = 11;
						}
					}
				}
				else if (state == 11) {
					if (throwing[0].IsAnimationDone() && throwing[1].IsAnimationDone()) {
						isThrowing = false;
						state = 5;
					}
				}
				else if (state == 12) {
					// 不確定要不要assign dy = 12;
					if (distance > 128) {
						// TO be fix: 不確定需不需要處理掉落
						isWalking = true;
						if (map[(y + 64) / 32][x / 32] != 1) { //可以掉落
							if (map[(y + 62 + 16) / 32][x / 32] != 1) {
								y += 16;
							}
							else {
								y = ((y / 32) + 1) * 32;
								dy = 12;
							}
						}
						if (rockmanX < x) {
							if (map[y / 32][(x - dx) / 32] != 1) {
								x -= dx;
								// isWalking = true;
							}
							else {
								dx = distance / 24; //best case: 不受障礙物抵擋，就能剛好到達目的地
								dy = 12;
								isWalking = false;
								jumpLeft = true;
								state = 13;
							}
						}
						else {
							if (map[y / 32][(x + dx + 24) / 32] != 1) {
								x += dx;
								// isWalking = true;
							}
							else {
								dx = distance / 24; //best case: 不受障礙物抵擋，就能剛好到達目的地
								dy = 12;
								isWalking = false;
								jumpLeft = false;
								state = 13;
							}
						}
						// 剪刀回來後就卡在這了
						// if(blood >= 1) blood -= 1;
						// else if(blood <= 27) blood += 1;

					}
					else {
						if (rockmanX < x) {
							jumpLeft = true;
						}
						else {
							jumpLeft = false;
						}
						
						dx = distance / 24; //best case: 不受障礙物抵擋，就能剛好到達目的地
						dy = 12;
						state = 13;
					}
				}
				else if (state == 13) { //state for jump
					isJumping = true;
					if (jumpLeft) {
						// todo: 不確定需不需要小段的位移，如dx超出空隙超多(會看起來很怪
						if (map[y / 32][(x - dx) / 32] != 1) {
							x -= dx;
						}
					}
					else {
						if (map[y / 32][(x + dx + 48) / 32] != 1) {
							x += dx;
						}
					}

					if ((jumpCount % 2 == 0) && (jumpCount != 0)) {
						dy -= 1;
					}
					jumpCount++;
					if (dy < 0) { //下墜
						if (map[(y + 64) / 32][x / 32] != 1) { //可以掉落
							if (map[(y + 62 - dy) / 32][x / 32] != 1) {
								y -= dy;
							}
							else {
								y = ((y / 32) + 1) * 32;
							}
						}
						else { //落地
							// y = (y / 32) * 32;
							dy = 12;
							dx = 4;
							jumpCount = 0;
							isJumping = false;
							if (facingLeft) {
								throwing[0].ToggleAnimation();
								throwingLeft = true;
							}
							else {
								throwing[1].ToggleAnimation();
								throwingLeft = false;
							}
							isThrowing = true;
							state = 10;
						}
					}
					else {
						//上升
						y -= dy;
					}
				}
				else if (state == 14) {
					if (weaponThrew) { // 不可丟
						//if (!isJumping) {
							if (rockmanX < x) {
								jumpLeft = true;
							}
							else {
								jumpLeft = false;
							}
							dx = distance / 24; //best case: 不受障礙物抵擋，就能剛好到達目的地
							dy = 12;
							isJumping = true;
							state = 17;
						//}
					}
					else {
						if (distance <= 32) { // 起跳，並在空中丟出剪刀
							if (facingLeft) {
								throwing[0].ToggleAnimation();
								throwingLeft = true;
							}
							else {
								throwing[1].ToggleAnimation();
								throwingLeft = false;
							}
							if (rockmanX < x) {
								jumpLeft = true;
							}
							else {
								jumpLeft = false;
							}
							dx = distance / 24; //best case: 不受障礙物抵擋，就能剛好到達目的地
							dy = 12;
							jumpCount = 0;
							isJumping = true;
							isThrowing = true;
							state = 15;
						}
						else if (distance <= 128) { // 丟->state 5
							if (facingLeft) {
								throwing[0].ToggleAnimation();
								throwingLeft = true;
							}
							else {
								throwing[1].ToggleAnimation();
								throwingLeft = false;
							}
							isThrowing = true;
							state = 10;
						}
						else { // far range
							isWalking = false;
							state = 1;
							timer.SetAnimation(1500, true);
							timer.ToggleAnimation();
						}
					}
				}
				else if (state == 15) {
					// 丟剪刀
					if (throwingLeft) {
						if (throwing[0].GetFrameIndexOfBitmap() == 1) {
							playsound = true;
							weaponThrew = true;
							weapon_dx = -6;
							if (rockmanY >= y) {
								weapon_dy = ((rockmanY - y) / ((distance / 4) + 1));
							}
							else {
								weapon_dy = -((y - rockmanY) / ((distance / 4) + 1));
							}
							weaponX = x;
							weaponY = y;
							isWeaponGo = true;
							state = 16;
						}
					}
					else {
						if (throwing[1].GetFrameIndexOfBitmap() == 1) {
							playsound = true;
							weaponThrew = true;
							// count dx dy
							weapon_dx = 6;
							if (rockmanY >= y) {
								weapon_dy = ((rockmanY - y) / ((distance / 4) + 1));
							}
							else {
								weapon_dy = -((y - rockmanY) / ((distance / 4) + 1));
							}

							weaponX = x + 16;
							weaponY = y;
							isWeaponGo = true;
							state = 16;
						}
					}

					//跳躍
					if ((jumpCount % 2 == 0) && (jumpCount != 0)) {
						dy -= 1;
					}
					jumpCount++;
					y -= dy;
					if (jumpLeft) {
						// todo: 不確定需不需要小段的位移，如dx超出空隙超多(會看起來很怪
						if (map[y / 32][(x - dx) / 32] != 1) {
							x -= dx;
						}
					}
					else {
						if (map[y / 32][(x + dx + 48) / 32] != 1) {
							x += dx;
						}
					}
				}
				else if (state == 16) {
					if (isThrowing && throwing[0].IsAnimationDone() && throwing[1].IsAnimationDone()) {
						isThrowing = false;
					}
					if (jumpLeft) {
						// todo: 不確定需不需要小段的位移，如dx超出空隙超多(會看起來很怪
						if (map[y / 32][(x - dx) / 32] != 1) {
							x -= dx;
						}
					}
					else {
						if (map[y / 32][(x + dx + 48) / 32] != 1) {
							x += dx;
						}
					}

					if ((jumpCount % 2 == 0) && (jumpCount != 0)) {
						dy -= 1;
					}
					jumpCount++;
					if (dy < 0) { //下墜
						// to fix 小縫隙掉落
						if (map[(y + 64) / 32][x / 32] != 1) { //可以掉落
							if (map[(y + 62 - dy) / 32][x / 32] != 1) {
								y -= dy;
							}
							else {
								y = ((y / 32) + 1) * 32;
							}
						}
						else { //落地
							if (!weaponThrew) {
								dy = 12;
								dx = 4;
								jumpCount = 0;
								isJumping = false;
								state = 14;
							}
							else { //再跳一次
								if (rockmanX < x) {
									jumpLeft = true;
								}
								else {
									jumpLeft = false;
								}
								dx = distance / 24; //best case: 不受障礙物抵擋，就能剛好到達目的地
								dy = 12;
								jumpCount = 0;
								isJumping = true;
							}
						}
					}
					else {
						//上升
						y -= dy;
					}
				}
				else if (state == 17) {
					if (jumpLeft) {
						// todo: 不確定需不需要小段的位移，如dx超出空隙超多(會看起來很怪
						if (map[y / 32][(x - dx) / 32] != 1) {
							x -= dx;
						}
					}
					else {
						if (map[y / 32][(x + dx + 48) / 32] != 1) {
							x += dx;
						}
					}

					if ((jumpCount % 2 == 0) && (jumpCount != 0)) {
						dy -= 1;
					}
					jumpCount++;
					if (dy < 0) { //下墜
						// to fix 小縫隙掉落
						if (map[(y + 64) / 32][x / 32] != 1) { //可以掉落
							if (map[(y + 62 - dy) / 32][x / 32] != 1) {
								y -= dy;
							}
							else {
								y = ((y / 32) + 1) * 32;
							}
						}
						else { //落地
							dy = 12;
							dx = 4;
							jumpCount = 0;
							isJumping = false;
							if (weaponThrew) {
								if (rockmanX < x) {
									jumpLeft = true;
								}
								else {
									jumpLeft = false;
								}
								dx = distance / 24; //best case: 不受障礙物抵擋，就能剛好到達目的地
								dy = 12;
								isJumping = true;
							}
							else {
								state = 14;
							}
						}
					}
					else {
						//上升
						y -= dy;
					}
				}
			}
			if (weaponThrew) { //丟出去了要處理飛行位移
				if (isWeaponGo) {
					int tempY = (weaponY + weapon_dy);
					int tempX = (weaponX + weapon_dx);
					if (tempX >= 6176 && tempX <= 6590 && tempY >= 1600 && tempY <= 1950) {
						weaponX = tempX;
						weaponY = tempY;
					}
					else {
						isWeaponGo = false;
					}
				}
				else {
					int distanceX = abs(weaponX - x);
					int distanceY = abs(weaponY - y);

					if (weaponX == x && weaponY == y) {
						CAudio::Instance()->Stop(10);
						weaponThrew = false;
					}
					else if (distanceX <= 4 && distanceY <= 4) {
						weaponX = x;
						weaponY = y;
					}
					else{
						if (x >= weaponX) {
							weaponX += 6;
						}
						else {
							weaponX -= 6;
						}
						if (y >= weaponY) {
							weaponY += ((distanceY) / (distanceX / 4 + 1));
						}
						else {
							weaponY -= ((distanceY) / (distanceX / 4 + 1));
						}
					}
				}
			}
			if (playsound) {
				CAudio::Instance()->Play(10, false);
				playsound = false;
			}
			// gravity test
			/*
			if (transitionState == 40) {
				if (state == 100) {
					// 呼叫walk fucntion return boolean告訴你到達了沒
					// 呼叫jump function return boolean告訴你到達了沒
					// 先測加速度
					dy = 12;
					state = 10;
				}
				if (state == 10) {
					y -= dy;
					x -= 4;
					if (dy == -12) {
						state = 11;
						jumpCount = 0;
						dy = 12;
					}
					else {
						if (jumpCount % 2 == 0) {
							dy -= 1;
						}
						jumpCount = (jumpCount+1)%2;
					}
				}
				if (state == 11) {
					y -= dy;
					x += 4;
					if (dy == -12) {
						state = 10;
						jumpCount = 0;
						dy = 12;
					}
					else {
						if (jumpCount % 2 == 0) {
							dy -= 1;
						}
						jumpCount = (jumpCount + 1) % 2;
					}
				}
			}
			*/
			
			shine.SetTopLeft(x - stageX, y - stageY);
			restingY[0].SetTopLeft(x - stageX, y - stageY);
			restingY[1].SetTopLeft(x - stageX, y - stageY);
			restingN[0].SetTopLeft(x - stageX, y - stageY);
			restingN[1].SetTopLeft(x - stageX, y - stageY);
			runningY[0].SetTopLeft(x - stageX, y - stageY);
			runningY[1].SetTopLeft(x - stageX, y - stageY);
			runningN[0].SetTopLeft(x - stageX, y - stageY);
			runningN[1].SetTopLeft(x - stageX, y - stageY);
			jumpingY[0].SetTopLeft(x - stageX, y - stageY);
			jumpingY[1].SetTopLeft(x - stageX, y - stageY);
			jumpingN[0].SetTopLeft(x - stageX, y - stageY);
			jumpingN[1].SetTopLeft(x - stageX, y - stageY);
			beingAttackY[0].SetTopLeft(x - stageX, y - stageY);
			beingAttackY[1].SetTopLeft(x - stageX, y - stageY);
			beingAttackN[0].SetTopLeft(x - stageX, y - stageY);
			beingAttackN[1].SetTopLeft(x - stageX, y - stageY);
			rollingCutter[0].SetTopLeft(weaponX - stageX, weaponY - stageY);
			rollingCutter[1].SetTopLeft(weaponX - stageX, weaponY - stageY);
			throwing[0].SetTopLeft(x - stageX, y - stageY);
			throwing[1].SetTopLeft(x - stageX, y - stageY);

		};
		
		void OnShow(int transitionState) {
			timer.ShowBitmap();
			if (blood > 0 && transitionState >= 33) {
				if (!shine.IsAnimationDone()) { //還在後退被打當中
					shine.ShowBitmap(2);
					if (shine.GetFrameIndexOfBitmap() % 2 == 1) { //閃爍空檔show後退的bitmap
						if (beenAttackedByLeft) {
							if (weaponThrew) { //面左沒剪刀
								beingAttackN[0].ShowBitmap(2);
							}
							else {
								beingAttackY[0].ShowBitmap(2);
							}
						}
						else {
							if (weaponThrew) { //面右沒剪刀
								beingAttackN[1].ShowBitmap(2);
							}
							else {
								beingAttackY[1].ShowBitmap(2);
							}
						}
					}
				}else { //沒被打
					if (isThrowing) { //throw
						if (throwingLeft) {
							throwing[0].ShowBitmap(2);
						}
						else {
							throwing[1].ShowBitmap(2);
						}
					}
					else if (isJumping) {
						if (facingLeft) { //面左
							if (weaponThrew) {
								jumpingN[0].ShowBitmap(2);
							}
							else {
								jumpingY[0].ShowBitmap(2);
							}
						}
						else {
							if (weaponThrew) {
								jumpingN[1].ShowBitmap(2);
							}
							else {
								jumpingY[1].ShowBitmap(2);
							}
						}
					}
					else if (isWalking) {
						if (facingLeft) { //面左
							if (weaponThrew) {
								runningN[0].ShowBitmap(2);
							}
							else {
								runningY[0].ShowBitmap(2);
							}
						}
						else {
							if (weaponThrew) {
								runningN[1].ShowBitmap(2);
							}
							else {
								runningY[1].ShowBitmap(2);
							}
						}
					}
					else { //resting animation
						if (facingLeft) { //面左
							if (weaponThrew) {
								restingN[0].ShowBitmap(2);
							}
							else {
								restingY[0].ShowBitmap(2);
							}
						}
						else {
							if (weaponThrew) {
								restingN[1].ShowBitmap(2);
							}
							else {
								restingY[1].ShowBitmap(2);
							}
						}
					}
				}
			}
			else {
				// boss is dead; 
				// explode animation
				if (blood <= 0) {
					for (int i = 0; i < 12; i++)
					{
						deadBubble[i].ShowBitmap(2);
					}
				}
			}
			if (weaponThrew) { //丟出
				if (throwingLeft) {
					if (isWeaponGo)
						rollingCutter[0].ShowBitmap(2);
					else
						rollingCutter[1].ShowBitmap(2);
				}
				else {
					if (isWeaponGo)
						rollingCutter[1].ShowBitmap(2);
					else
						rollingCutter[0].ShowBitmap(2);
				}
			}
			
			if (transitionState == -1) { // 洛克人死掉
				if (isJumping) {
					if (jumpLeft) {
						jumpingY[0].ShowBitmap(2);
					}
					else {
						jumpingY[1].ShowBitmap(2);
					}
				}
				else {
					if (facingLeft) {
						restingY[0].ShowBitmap(2);
					}
					else {
						restingY[1].ShowBitmap(2);
					}
				}
			}
		};
		void OnBeginState() {
			x = 3252 * 2;
			y = 928 * 2;
			dx = 4;
			dy = 12;
			blood = 28;
			damage = 0;
			state = 0;
			isWeaponGo = true;
			jumpCount = 0;
			restingCount = 0;
			facingLeft = false;
			weaponThrew = false;
			isThrowing = false;
			throwingLeft = true;
			isJumping = false;
			isWalking = false;
			isHit = false;
			beenAttackedByLeft = false;
			attackFromRight = false;
			deadState = 0;
		}
		void setmap(vector<vector<int>> map) {
			this->map = map;
		}
		int getDamage() { //怪物攻擊洛克人的傷害，要先successfullyAttack == true
			return damage;
		}
		bool beenAttacked(CMovingBitmap bullet) { //以怪物的角度，怪物被打中?
			if (shine.IsAnimationDone()) { //被擊退動畫結束
				
				if (bullet.GetTop() + bullet.GetHeight() >= beingAttackN[0].GetTop() + 24
					&& bullet.GetLeft() + bullet.GetWidth() >= beingAttackN[0].GetLeft()
					&& bullet.GetTop() <= beingAttackN[0].GetTop() + beingAttackN[0].GetHeight()
					&& bullet.GetLeft() <= beingAttackN[0].GetLeft() + beingAttackN[0].GetWidth()) {
				
				// if(CMovingBitmap::IsOverlap(beingAttackN[0], bullet, 2)){
					if (bullet.GetLeft() <= (beingAttackN[0].GetLeft() + beingAttackN[0].GetWidth()/2)) {
						beenAttackedByLeft = true;
					}
					else{
						beenAttackedByLeft = false;
					}
					isHit = true;
					blood -= 3;
					if (blood <= 0) {
						deadState = 1;
						for (int i = 0; i < 12; i++)
						{
							bubble_XY[i][0] = x + 4 * 2;
							bubble_XY[i][1] = y + 12 * 2;
						}
					}
					return true;
				}
				return false;
			}
			return false;
		}
		bool successfullyAttack(CMovingBitmap rockman) { //以怪物的角度，打中洛克人?
			if (weaponThrew && CMovingBitmap::IsOverlap(rockman, rollingCutter[0], 2)) {
				damage = 5;
				if (rockman.GetLeft() <= rollingCutter[0].GetLeft()) { //
					attackFromRight = true;
				}
				else {
					attackFromRight = false;
				}
				return true;
			}
			else if (rockman.GetTop() + rockman.GetHeight() >= beingAttackN[0].GetTop()+24
				&& rockman.GetLeft() + rockman.GetWidth() >= beingAttackN[0].GetLeft()
				&& rockman.GetTop() <= beingAttackN[0].GetTop() + beingAttackN[0].GetHeight()
				&& rockman.GetLeft() <= beingAttackN[0].GetLeft() + beingAttackN[0].GetWidth()) {
				// 重疊->判斷碰撞
				damage = 7;
				if (rockman.GetLeft() <= beingAttackN[0].GetLeft()) { //
					attackFromRight = true;
				}
				else {
					attackFromRight = false;
				}
				return true;
			}
			return false;
		}
		bool isDead() {//怪物死了沒，依血量判斷
			if (blood <= 0) {
				return true;
			}
			else {
				return false;
			}
		}

		bool isAttackFromRight() {  //怪物是從右邊打洛克人的嗎?必須先successfullyAttack == true
			return attackFromRight;
		}
		bool deadAnimationDone() {
			if (deadState == 2) {
				return true;
			}
			return false;
		}
		int getX() { //左上x(absolute
			return x;
		}
		int getY() { //左上y(absolute
			return y;
		}
		int getBlood() { //怪物目前的血量
			return blood;
		}

	private:
		int x = 3252*2;
		int y = 928*2;
		int dx = 4;
		int dy = 12;
		int blood = 28;
		int damage = 0;

		int weaponX;
		int weaponY;
		int weapon_dx;
		int weapon_dy;

		int state = 0; // preState
		bool isWeaponGo = true; // true->還沒回璇回來

		int jumpCount = 0;
		int restingCount = 0;

		int jumpTargetX;
		int jumpTargetY;

		bool jumpLeft;
		bool facingLeft = false;
		bool weaponThrew = false;
		bool isThrowing = false;
		bool throwingLeft = true;
		bool isJumping = false;
		bool isWalking = false;
		bool isHit = false;
		bool beenAttackedByLeft = false;
		bool attackFromRight = false;
		bool playsound = false;
		CMovingBitmap shine;
		CMovingBitmap restingY[2];
		CMovingBitmap restingN[2];
		CMovingBitmap runningY[2];
		CMovingBitmap runningN[2];
		CMovingBitmap jumpingY[2];
		CMovingBitmap jumpingN[2];
		CMovingBitmap beingAttackY[2];
		CMovingBitmap beingAttackN[2];
		CMovingBitmap rollingCutter[2];
		CMovingBitmap throwing[2];
		CMovingBitmap timer;
		CMovingBitmap deadBubble[12];

		int deadState = 0;
		double bubble_XY[12][2]; // rockmanX + 4*2, rockmanY + 4*2
		double bubble_dXdY[12][2] = {
			{1.6, 0}, // 4顆從最右邊開始
			{0, 1.6},
			{-1.6, 0},
			{0, -1.6},
			{3.2, 0}, // 8顆從最右邊開始
			{3.2, 3.2},
			{0, 3.2},
			{-3.2, 3.2},
			{-3.2, 0},
			{-3.2, -3.2},
			{0, -3.2},
			{3.2, -3.2}
		};

		vector<vector<int>> map;

	};

};