#pragma once
#include <string>
namespace game_framework {
	class Character
	{
	public:
		Character() {};
		~Character() {};
		void OnInit(int stage_x, int stage_y) {
			timer.LoadBitmapByString({ "resources/white.bmp", "resources/white.bmp" }, RGB(255, 255, 255));
			timer.SetTopLeft(0, 0);
			timer.SetAnimation(1800, true);

			hitAnimation[0].LoadBitmapByString({
				"resources/rockman/purple.bmp",
				"resources/rockman/hurt0.bmp",
				"resources/rockman/shine.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/hurt0.bmp",
				"resources/rockman/shine.bmp",
				}, RGB(128, 0, 128));
			hitAnimation[0].SetAnimation(100, true);
			hitAnimation[1].LoadBitmapByString({
				"resources/rockman/purple.bmp",
				"resources/rockman/hurt1.bmp",
				"resources/rockman/shine.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/hurt1.bmp",
				"resources/rockman/shine.bmp",
				}, RGB(128, 0, 128));
			hitAnimation[1].SetAnimation(100, true);

			shine.LoadBitmapByString({
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/purple.bmp",
				}, RGB(128, 0, 128));
			shine.SetAnimation(100, true);

			resting[0].LoadBitmapByString({
				"resources/rockman/lookLeftOpenEyes.bmp" ,
				"resources/rockman/lookLeftOpenEyes.bmp" ,
				"resources/rockman/lookLeftOpenEyes.bmp" ,
				"resources/rockman/lookLeftOpenEyes.bmp" ,
				"resources/rockman/lookLeftOpenEyes.bmp" ,
				"resources/rockman/lookLeftCloseEyes.bmp" ,
				}, RGB(128, 0, 128));
			resting[1].LoadBitmapByString({
				"resources/rockman/lookRightOpenEyes.bmp" ,
				"resources/rockman/lookRightOpenEyes.bmp" ,
				"resources/rockman/lookRightOpenEyes.bmp" ,
				"resources/rockman/lookRightOpenEyes.bmp" ,
				"resources/rockman/lookRightOpenEyes.bmp" ,
				"resources/rockman/lookRightCloseEyes.bmp" ,
				}, RGB(128, 0, 128));
			restingShine[0].LoadBitmapByString({
				"resources/rockman/purple.bmp",
				"resources/rockman/lookLeftOpenEyes.bmp" ,
				"resources/rockman/purple.bmp",
				"resources/rockman/lookLeftOpenEyes.bmp" ,
				"resources/rockman/purple.bmp",
				"resources/rockman/lookLeftOpenEyes.bmp" ,
				"resources/rockman/purple.bmp",
				"resources/rockman/lookLeftOpenEyes.bmp" ,
				"resources/rockman/purple.bmp",
				"resources/rockman/lookLeftOpenEyes.bmp" ,
				"resources/rockman/purple.bmp",
				"resources/rockman/lookLeftCloseEyes.bmp" ,
				}, RGB(128, 0, 128));
			restingShine[1].LoadBitmapByString({
				"resources/rockman/purple.bmp",
				"resources/rockman/lookRightOpenEyes.bmp" ,
				"resources/rockman/purple.bmp",
				"resources/rockman/lookRightOpenEyes.bmp" ,
				"resources/rockman/purple.bmp",
				"resources/rockman/lookRightOpenEyes.bmp" ,
				"resources/rockman/purple.bmp",
				"resources/rockman/lookRightOpenEyes.bmp" ,
				"resources/rockman/purple.bmp",
				"resources/rockman/lookRightOpenEyes.bmp" ,
				"resources/rockman/purple.bmp",
				"resources/rockman/lookRightCloseEyes.bmp" ,
				}, RGB(128, 0, 128));

			running[0].LoadBitmapByString({ // index 0 refers to running left
				"resources/rockman/RunningLeft1.bmp" ,
				"resources/rockman/RunningLeft2.bmp" ,
				"resources/rockman/RunningLeft3.bmp" ,
				}, RGB(128, 0, 128));
			running[1].LoadBitmapByString({ // index 1 refers to running right
				"resources/rockman/RunningRight1.bmp" ,
				"resources/rockman/RunningRight2.bmp" ,
				"resources/rockman/RunningRight3.bmp" ,
				}, RGB(128, 0, 128));
			runningShine[0].LoadBitmapByString({ // index 0 refers to running left
				"resources/rockman/purple.bmp",
				"resources/rockman/RunningLeft1.bmp" ,
				"resources/rockman/purple.bmp",
				"resources/rockman/RunningLeft2.bmp" ,
				"resources/rockman/purple.bmp",
				"resources/rockman/RunningLeft3.bmp" ,
				}, RGB(128, 0, 128));
			runningShine[1].LoadBitmapByString({ // index 1 refers to running right
				"resources/rockman/purple.bmp",
				"resources/rockman/RunningRight1.bmp" ,
				"resources/rockman/purple.bmp",
				"resources/rockman/RunningRight2.bmp" ,
				"resources/rockman/purple.bmp",
				"resources/rockman/RunningRight3.bmp" ,
				}, RGB(128, 0, 128));
			jumping[0].LoadBitmapByString({
				"resources/rockman/jumpingLeft.bmp" ,
				}, RGB(128, 0, 128));
			jumping[1].LoadBitmapByString({
				"resources/rockman/jumpingRight.bmp" ,
				}, RGB(128, 0, 128));
			jumpingShine[0].LoadBitmapByString({
				"resources/rockman/purple.bmp",
				"resources/rockman/jumpingLeft.bmp" ,
				}, RGB(128, 0, 128));
			jumpingShine[1].LoadBitmapByString({
				"resources/rockman/purple.bmp",
				"resources/rockman/jumpingRight.bmp" ,
				}, RGB(128, 0, 128));
			
			climbing[0].LoadBitmapByString({
				"resources/rockman/climb1.bmp",
				"resources/rockman/climb2.bmp"
				}, RGB(128,0,128));
			climbing[1].LoadBitmapByString({
				"resources/rockman/climb3.bmp"
				}, RGB(128, 0, 128));
			idleshooting[0].LoadBitmap({
				"resources/rockman/ShootingLeft.bmp"
				}, RGB(128, 0, 128));
			idleshooting[1].LoadBitmap({
				"resources/rockman/ShootingRight.bmp"
				}, RGB(128, 0, 128));
			runningshooting[0].LoadBitmap({
				"resources/rockman/MovingShootLeft2.bmp",
				"resources/rockman/MovingShootLeft1.bmp",
				"resources/rockman/MovingShootLeft3.bmp"
				}, RGB(128, 0, 128));
			runningshooting[1].LoadBitmap({
				"resources/rockman/MovingShootRight2.bmp",
				"resources/rockman/MovingShootRight1.bmp",
				"resources/rockman/MovingShootRight3.bmp"
				}, RGB(128, 0, 128));
			jumpingshooting[0].LoadBitmap({
				"resources/rockman/JumpingshootLeft.bmp"
				}, RGB(128, 0, 128));
			jumpingshooting[1].LoadBitmap({
				"resources/rockman/JumpingshootRight.bmp"
				}, RGB(128, 0, 128));
			laddershooting[0].LoadBitmap({
				"resources/rockman/ClimbingShootLeft.bmp"
				}, RGB(128, 0, 128));
			laddershooting[1].LoadBitmap({
				"resources/rockman/ClimbingShootRight.bmp"
				}, RGB(128, 0, 128));
			for (int i = 0; i < 3; i++)
			{
				beamammo[i].LoadBitmap({"resources/rockman/beamammo.bmp"}, RGB(128, 0, 128));
			}
			climbingShine[0].LoadBitmapByString({
				"resources/rockman/purple.bmp",
				"resources/rockman/climb1.bmp",
				"resources/rockman/purple.bmp",
				"resources/rockman/climb2.bmp"
				}, RGB(128, 0, 128));
			climbingShine[1].LoadBitmapByString({
				"resources/rockman/purple.bmp",
				"resources/rockman/climb2.bmp"
				}, RGB(128, 0, 128));
			running[0].SetAnimation(100, false);
			running[1].SetAnimation(100, false);
			resting[0].SetAnimation(200, false);
			resting[1].SetAnimation(200, false);
			climbing[0].SetAnimation(150, true);
			runningshooting[0].SetAnimation(100, false);
			runningshooting[1].SetAnimation(100, false);
			runningShine[0].SetAnimation(100, false);
			runningShine[1].SetAnimation(100, false);
			restingShine[0].SetAnimation(100, false);
			restingShine[1].SetAnimation(100, false);
			jumpingShine[0].SetAnimation(100, false);
			jumpingShine[1].SetAnimation(100, false);
			climbingShine[0].SetAnimation(75, true);
			climbingShine[1].SetAnimation(75, false);
			// 最好是在Onshow設定位置，避免多餘的code
			hitAnimation[0].SetTopLeft(x - stage_x, y - stage_y);
			hitAnimation[1].SetTopLeft(x - stage_x, y - stage_y);
			resting[0].SetTopLeft(x - stage_x, y - stage_y);
			resting[1].SetTopLeft(x - stage_x, y - stage_y);
			running[0].SetTopLeft(x - stage_x, y - stage_y);
			running[1].SetTopLeft(x - stage_x, y - stage_y);
			jumping[0].SetTopLeft(x - stage_x, y - stage_y);
			jumping[1].SetTopLeft(x - stage_x, y - stage_y);
			climbing[0].SetTopLeft(x - stage_x, y - stage_y);
			climbing[1].SetTopLeft(x - stage_x, y - stage_y);
			idleshooting[0].SetTopLeft(x - stage_x, y - stage_y);
			idleshooting[1].SetTopLeft(x - stage_x, y - stage_y);
			runningshooting[0].SetTopLeft(x - stage_x, y - stage_y);
			runningshooting[1].SetTopLeft(x - stage_x, y - stage_y);
			jumpingshooting[0].SetTopLeft(x - stage_x, y - stage_y);
			jumpingshooting[1].SetTopLeft(x - stage_x, y - stage_y);
			laddershooting[0].SetTopLeft(x - stage_x, y - stage_y);
			laddershooting[1].SetTopLeft(x - stage_x, y - stage_y);
			for (int i = 0; i < 3; i++)
			{
				if (isFacingRight)
				{
					ammoloc[i][0] = x+16;
					ammoloc[i][1] = y;
				}
				else
				{
					ammoloc[i][0] = x;
					ammoloc[i][1] = y;
				}
				beamammo[i].SetTopLeft(ammoloc[i][0] - stage_x, ammoloc[i][1] - stage_y);
			}
		};
		void Onshow(int stage_x, int stage_y) {
			for (int i = 0; i < 3; i++)
			{
				if (isShot[i])
				{
					beamammo[i].ShowBitmap(2);
				}
			}
			// 之後會需要if statement來決定是哪張圖or動畫
			timer.ShowBitmap();
			if (isHitState == 1 || isHitState == 2) {
				if (isAttackedFromRight) {
					hitAnimation[1].ShowBitmap(2);
				}else{
					hitAnimation[0].ShowBitmap(2);
				}
			} else if ((!isJumping && !isFalling)||isClimbing) {
				if (isResting) { // resting
					if (isFacingRight == false) { // resting_left_side
						if(isHitState != 4){
              if (isShooting == true) {
							idleshooting[0].ShowBitmap(2);
						  }
              else{
                resting[0].ShowBitmap(2);
              }
            }
						else
							restingShine[0].ShowBitmap(2);
					}
					else {  // 原本面右，繼續面右
						if (isHitState != 4)
							if (isShooting == true) {
							idleshooting[1].ShowBitmap(2);
						  }
              else{
                resting[1].ShowBitmap(2);
              }
						else
							restingShine[1].ShowBitmap(2);
					}
				}
				else if (isClimbing) {
					if (isHitState != 4){
						if (isShooting) {
						if (isFacingRight) {
							laddershooting[1].ShowBitmap(2);
						}
						else
						{
							laddershooting[0].ShowBitmap(2);
						}
					}
					else
            {
              climbing[0].ShowBitmap(2);
            }
          }
					else {
						if(!climbingShine[0].IsAnimationDone())
							climbingShine[0].ShowBitmap(2);
						else
							climbingShine[1].ShowBitmap(2);
					}
				}
				else if (!isResting) {
					if (isFacingRight == false) { // running_left_side
						if (isHitState != 4)
            {
              if (isShooting == true) {
							runningshooting[0].ShowBitmap(2);
						    }
						else if (isShooting == false) {
							running[0].ShowBitmap(2);
						    }
            }
						else
							runningShine[0].ShowBitmap(2);
					}
					else {  // 原本面右，繼續面右
						if (isHitState != 4)
            {
              if (isShooting == true) {
							runningshooting[1].ShowBitmap(2);
						  }
						else if (isShooting == false) {
							running[1].ShowBitmap(2);
						  }
            }
						else
							runningShine[1].ShowBitmap(2);
					}
				}
			}
			else {
				if (isFacingRight == false) { // running_left_side
					if (isHitState != 4)
          {
            if(isShooting == true){
              jumpingshooting[0].ShowBitmap(2);
            }
            else{
              jumping[0].ShowBitmap(2);
            }
          }
					else
						jumpingShine[0].ShowBitmap(2);
				}
				else {  // 原本面右，繼續面右
					if (isHitState != 4)
          {
            if(isShooting == true){
              jumpingshooting[1].ShowBitmap(2);
            }
            else{
              jumping[1].ShowBitmap(2);
            }
          }
					else
						jumpingShine[1].ShowBitmap(2);
				}
			}
		}
		void OnMove(int stage_x, int stage_y, int transitionState) {
			//int bitmapLeft_x = this->x - left_boundary; //以left_boundary為基準的rockman_x(左上角)
			//int bitmapTop_y = this->y - top_boundary; //以top_boundary為基準的rockman_y(左上角)
			// 主角判斷碰撞為中間32pixels 所以要由bitmap的x,y做運算
			//int left_x = bitmapLeft_x + 2 * 4; //非左非上的角落要扣1，以表達角落的座標
			//int right_x = bitmapLeft_x + 2 * (24 - 1 - 4);
			//int top_y = bitmapTop_y;
			//int mid_y = bitmapTop_y + 2 * (12 - 1);
			//int down_y = bitmapTop_y + 2 * (24 - 1);
			// 除(/)32就是index數;
			// int index_x = x / 32; //最左邊的index : index_x
			// int index_y = y / 32; //最上面的index : index_y 
			int left_x = x + 2 * 4; //非左非上的角落要扣1，以表達角落的座標
			int mid_x = x + 2 * 11;
			int right_x = x + 2 * (24 - 1 - 4);
			int top_y = y;
			int mid_y = y + 2 * (12 - 1);
			int down_y = y + 2 * (24 - 1);

			if (transitionState == 0 || transitionState == 30 || transitionState == 40) {
				if (isHitState == 3) {
					timer.ToggleAnimation();
					isHitState = 4;
				}
				else if (isHitState == 4) {
					if (timer.IsAnimationDone()) {
						isHitState = 0;
					}
				}
				
				if (isHitState == 1) {
					if (isAttackedFromRight == true) {
						hitAnimation[1].ToggleAnimation();
					}
					else {
						hitAnimation[0].ToggleAnimation();
					}
					if (isClimbing) {
						isJumping = false;
						isFalling = true;
						isClimbing = false;
						isOnTheGround = false;
					}
					isHitState = 2;
				}
				else if (isHitState == 2) {	
					if (hitAnimation[0].IsAnimationDone() && hitAnimation[1].IsAnimationDone()) {
						// 打完動畫已結束，就可動了
						isHitState = 3;
					}
					else {
						// dx = 1不知道會不會有問題
						if (isAttackedFromRight) {
							if (left_x - 1 >= 0
								&& block_element_3darray[top_y / 32][(left_x - 1) / 32] != -1
								&& block_element_3darray[mid_y / 32][(left_x - 1) / 32] != -1
								&& block_element_3darray[down_y / 32][(left_x - 1) / 32] != -1) {
								// 檢查是否會撞牆
								if (block_element_3darray[top_y / 32][(left_x - 1) / 32] != 1
									&& block_element_3darray[mid_y / 32][(left_x - 1) / 32] != 1
									&& block_element_3darray[down_y / 32][(left_x - 1) / 32] != 1
									&& !isClimbing) {
									x -= 1;
								}
							}
						}
						else {
							if (right_x + dx <= 6656
								&& block_element_3darray[top_y / 32][(right_x + 1) / 32] != -1
								&& block_element_3darray[mid_y / 32][(right_x + 1) / 32] != -1
								&& block_element_3darray[down_y / 32][(right_x + 1) / 32] != -1) {

								if (block_element_3darray[top_y / 32][(right_x + 1) / 32] != 1
									&& block_element_3darray[mid_y / 32][(right_x + 1) / 32] != 1
									&& block_element_3darray[down_y / 32][(right_x + 1) / 32] != 1
									&& !isClimbing) {
									 x += 1;
								}
							}
						}
					}
				}
				else if ((leftPressed && rightPressed&&upPressed&&downPressed) || !(leftPressed || rightPressed||upPressed||downPressed)) { //按雙鍵，維持原本的方向但不位移
					if (!isClimbing)
						isResting = true;
					else {
						isClimbing = true;
						isResting = false;
					}
				}
				else if (leftPressed) { // movingLeft
					isFacingRight = false;
					isResting = false;
					// 先檢查會不會超出邊界
					if (left_x - dx >= 0
						&& block_element_3darray[top_y / 32][(left_x - dx) / 32] != -1
						&& block_element_3darray[mid_y / 32][(left_x - dx) / 32] != -1
						&& block_element_3darray[down_y / 32][(left_x - dx) / 32] != -1) {
						// 檢查是否會撞牆
						if (block_element_3darray[top_y / 32][(left_x - dx) / 32] != 1
							&& block_element_3darray[mid_y / 32][(left_x - dx) / 32] != 1
							&& block_element_3darray[down_y / 32][(left_x - dx) / 32] != 1
							&& !isClimbing) {
							x -= dx;
						}
					}
				}
				else if (rightPressed) { //movingRight
					isFacingRight = true;
					isResting = false;
					if (right_x + dx <= 6656
						&& block_element_3darray[top_y / 32][(right_x + dx) / 32] != -1
						&& block_element_3darray[mid_y / 32][(right_x + dx) / 32] != -1
						&& block_element_3darray[down_y / 32][(right_x + dx) / 32] != -1) {

						if (block_element_3darray[top_y / 32][(right_x + dx) / 32] != 1
							&& block_element_3darray[mid_y / 32][(right_x + dx) / 32] != 1
							&& block_element_3darray[down_y / 32][(right_x + dx) / 32] != 1
							&& !isClimbing) {
							x += dx;
						}
					}
				}
				else if (upPressed&&!shootPressed&&canClimb) { //向上爬梯子
					if (block_element_3darray[(top_y - 10) / 32][(mid_x) / 32] == 2 
						|| block_element_3darray[down_y / 32][(mid_x) / 32] == 2 
						|| block_element_3darray[down_y / 32][(mid_x) / 32] == 6
						|| block_element_3darray[(top_y - 2) / 32][(mid_x) / 32] == 6) {
						if (isfirstclimb&&isJumping) {
							y = top_y - (down_y - top_y);
							isfirstclimb = false;
						}
						isResting = false;
						isClimbing = true;
						isOnTheGround = true;
						if (climbing[0].IsAnimationDone()) {
							climbing[0].ToggleAnimation();
						}
						if (climbingShine[0].IsAnimationDone()) {
							climbingShine[0].ToggleAnimation();
						}
						
						y -= 3;
						x = (mid_x / 32) * 32 - 8;
					}
					else if (block_element_3darray[down_y / 32][(mid_x) / 32] == 0)
					{
						isClimbing = false;
						isfirstclimb = true;
						upPressed = false;
					}
				}
				else if (downPressed&&!shootPressed&&canClimb) { //向下爬梯子
					if (block_element_3darray[(down_y + 2) / 32][(mid_x) / 32] == 2 
						|| (block_element_3darray[(top_y - 2) / 32][(mid_x) / 32] == 2 
							&& block_element_3darray[(down_y + 2) / 32][(mid_x) / 32] == 0)
						|| block_element_3darray[(down_y + 2) / 32][(mid_x) / 32] == 6
						|| (block_element_3darray[(top_y - 2) / 32][(mid_x) / 32] == 6
							&& block_element_3darray[(down_y + 2) / 32][(mid_x) / 32] == 0)) {
						isResting = false;
						isClimbing = true;
						isOnTheGround = true;
						if (climbing[0].IsAnimationDone()) {
							climbing[0].ToggleAnimation();
						}
						if (climbingShine[0].IsAnimationDone()) {
							climbingShine[0].ToggleAnimation();
						}
						y += 3;
						x = (mid_x / 32) * 32 - 8;
					}
					else if (block_element_3darray[(down_y + 2) / 32][(mid_x) / 32] == 1 && isClimbing) {
						isClimbing = false;
						isResting = true;
						isfirstclimb = true;
						//x += 5;
					}
					else if (block_element_3darray[(top_y - 2) / 32][(mid_x) / 32] == 0 && isClimbing) {
						isClimbing = false;
						isfirstclimb = true;
						//x += 5;
					}
					else if (block_element_3darray[(down_y + 2) / 32][(mid_x) / 32] == 1 && !isClimbing) {
						isClimbing = false;
						isResting = true;
						isfirstclimb = true;
					}
				}
				// 著地後速度回歸為10
				if (isOnTheGround) {
					dy = 10;
					accePeriod = 6;
					startfalling = true;
				}
				if (isFalling) {
					if (startfalling)
					{
						dy = 1;
					}
					startfalling = false;
				}
				if (isJumping && dy - 1 >= 1) {
					if (jumpCount == 0) {
						dy--;
						if (accePeriod_up + 1 <= 2)
							accePeriod_up++;
					}
					jumpCount++;
					jumpCount = jumpCount % accePeriod_up;
				}

				if (isFalling && dy + 1 <= 14) {
					if (fallCount == 0) {
						dy++;
						if (accePeriod - 1 >= 1)
							accePeriod--;
					}
					fallCount++;
					fallCount = fallCount % accePeriod;
				}
				if (isFalling && dy + 1 <= 14) {
					if (fallCount == 0) {
						dy++;
						if (accePeriod - 1 >= 1)
							accePeriod--;
					}
					fallCount++;
					fallCount = fallCount % accePeriod;
				}
				
				if (shootPressed)
				{
					isShooting = true;
					if (!isShot[ammocount]&&canShot) {
						isShot[ammocount] = true;//索引值的bug懸疑題(超出索引卻沒報錯會改到宣告此陣列下方的變數)
						if (isFacingRight&&!isClimbing)
						{
							ammodirect[ammocount] = 0;
							ammoloc[ammocount][0] = x+36;
							ammoloc[ammocount][1] = y+15;
						}
						else if (!isFacingRight && !isClimbing)
						{
							ammodirect[ammocount] = 1;
							ammoloc[ammocount][0] = x-4;
							ammoloc[ammocount][1] = y + 15;
						}
						else if (isFacingRight && isClimbing)
						{
							ammodirect[ammocount] = 0;
							ammoloc[ammocount][0] = x + 28;
							ammoloc[ammocount][1] = y + 15;
						}
						else if (!isFacingRight && isClimbing)
						{
							ammodirect[ammocount] = 1;
							ammoloc[ammocount][0] = x-4;
							ammoloc[ammocount][1] = y + 15;
						}
						if (ammocount<2)
						{
							ammocount += 1;
						}
						else
						{
							ammocount = 0;
						}
					}
					canShot = false;
				}
				else if (!shootPressed)
				{
					canShot = true;
					gundown = false;
					canClimb = true;
				}
				for (int i = 0; i < 3; i++)
				{
					if (!(ammoloc[i][0] < stage_x + 512 && ammoloc[i][0] > stage_x && ammoloc[i][1] > stage_y && ammoloc[i][1] < stage_y+512)) {
						isShot[i] = false;
						ammoloc[i][0] = x;
						ammoloc[i][1] = y +15;
						if (shootPressed)
						{
							gundown = true;
						}
					}
					if (isShot[i]&&ammodirect[i]==0) {
						ammoloc[i][0] += ammodx;
						beamammo[i].SetTopLeft(ammoloc[i][0] - stage_x, ammoloc[i][1] - stage_y);
					}
					else if (isShot[i] && ammodirect[i]==1)
					{
						ammoloc[i][0] -= ammodx;
						beamammo[i].SetTopLeft(ammoloc[i][0] - stage_x, ammoloc[i][1] - stage_y);
					}
				}
				if (gundown)
				{
					isShooting = false;
				}
				if (ammocount >= 1) {
					if (abs(ammoloc[ammocount-1][0] - x) > 200) {
						if (shootPressed)
						{
							isShooting = true;
						}
						else
						{
							isShooting = false;
						}
						canClimb = true;
					}
					else if(isShot[ammocount - 1])
					{
						canClimb = false;
					}
				}
				else
				{
					if (abs(ammoloc[2][0] - x) > 200) {
						if (shootPressed)
						{
							isShooting = true;
						}
						else
						{
							isShooting = false;
						}
						canClimb = true;
					}
					else if (isShot[2])
					{
						canClimb = false;
					}
				}
				if (isOnTheGround) {
					if (!jumpPressed) { //如果在地板上 && 沒有按跳 -> 要判斷懸空與否要著地
						if ((block_element_3darray[(down_y + 2) / 32][(left_x) / 32] != 1&& block_element_3darray[(down_y + 2) / 32][(left_x) / 32] != 6)
							&& block_element_3darray[(down_y + 2) / 32][(right_x) / 32] != 1
							&& !isClimbing
							&& block_element_3darray[(down_y + 2) / 32][(right_x) / 32] != 6
							&& block_element_3darray[(down_y + 2) / 32][(left_x) / 32] != -1
							&& block_element_3darray[(down_y + 2) / 32][(right_x) / 32] != -1) {
							isJumping = false;
							isFalling = true;
							isOnTheGround = false;
							y += dy;
							jumpingHeight = 0;
						}
						else { // 表示跟地板還有一些縫隙，或是剛剛好OntTheGround
							if (isClimbing) {
								y = y;
							}
							else
							{
								y = (y / 32) * 32 + 16; // 小於dy的位移
							}
							
							jumpingHeight = 0; // 非跳躍要歸零
							isOnTheGround = true; // 經過位移後就會OnTheGround
							isfirstclimb = true;
							isFalling = false;
							isJumping = false;

						}
						if ((upPressed || downPressed)&&isClimbing) {//在梯子上時按著上或下要不能跳
							canJump = false;
						}
						else
						{
							canJump = true;
						}
					}
					else { //OnTheGround的時候，按跳
						if (canJump) {
							if ( (block_element_3darray[(top_y - dy) / 32][(right_x) / 32] != 1
								&& block_element_3darray[(top_y - dy) / 32][(right_x) / 32] != -1
								&&!isClimbing)) {
								isJumping = true;
								isFalling = false;
								isClimbing=false;
								isOnTheGround = false;
								jumpingHeight += dy;
								y -= dy;
							}
							else { // 小縫隙或是剛好頂到頭，接著準備落地
								isJumping = false;
								isFalling = true;
								isClimbing = false;
								isOnTheGround = false;
								y = (y / 32) * 32;
							}
							canJump = false;
						}
						else if (fallingstate&&block_element_3darray[(top_y - dy) / 32][(right_x) / 32] != 1
							&& block_element_3darray[(top_y - dy) / 32][(right_x) / 32] != -1) {
							canJump = false;
							fallingstate = 0;
							jumpPressed = false;
							isJumping = false;
							isFalling = true;
							isOnTheGround = false;
							y = (y / 32) * 32+16;
						}
					}
				}
				else { //不在地板
					if (isJumping && !isFalling) { // 剛從地板跳起來，往上跳階段
						if (!jumpPressed) { //剛跳起來但不繼續跳了
							isJumping = false;
							isFalling = true;
							// TODO : 從跳轉掉落感覺不需要考慮有縫隙的情況，如果bug為跳放開會陷入地板，要改變此處的程式
							y += dy; //直接落下
							jumpingHeight = 0; // 跳轉落: 跳躍高度歸零
						}
						else { //往上跳當中，持續按跳
							// case 1(跳完這下會到100):
							// 跳這下並且狀態改為falling
							// 1. 跳dy
							// 2. 跳縫隙

							// case 2(跳完這下不會到100):
							// 可跳
							// 1. 可跳dy(上面為空氣)
							// 2. 只有一點縫隙可跳
							if ((jumpingHeight + dy) >= 96) {  //case 1
								isFalling = true;
								isJumping = false;
								jumpingHeight = 0; //轉掉落要歸零
								if (block_element_3darray[(top_y - dy) / 32][(left_x) / 32] != 1
									&& block_element_3darray[(top_y - dy) / 32][(right_x) / 32] != 1
									&& block_element_3darray[(top_y - dy) / 32][(left_x) / 32] != -1
									&& block_element_3darray[(top_y - dy) / 32][(right_x) / 32] != -1) {
									// 可跳dy
									y -= dy;
									jumpingHeight += dy;
								}
								else { // 跳縫隙
									y = (y / 32) * 32;
								}
							}
							else { // case 2
								if (block_element_3darray[(top_y - dy) / 32][(left_x) / 32] != 1
									&& block_element_3darray[(top_y - dy) / 32][(right_x) / 32] != 1
									&& block_element_3darray[(top_y - dy) / 32][(left_x) / 32] != -1
									&& block_element_3darray[(top_y - dy) / 32][(right_x) / 32] != -1) {
									// 可跳dy
									y -= dy;
									jumpingHeight += dy;
									isJumping = true;
									isFalling = false;
								}
								else { // 跳縫隙
									y = (y / 32) * 32;
									isJumping = false;
									isFalling = true;
								}
							}
						}
					}
					else if (isFalling) { //在掉落的時候不考慮有沒有按跳 直接處理需要落dy還是縫隙
						if (!jumpPressed) {
							canJump = true;
						}
						if (block_element_3darray[(down_y + dy) / 32][(left_x) / 32] != 1
							&& block_element_3darray[(down_y + dy) / 32][(right_x) / 32] != 1
							&& block_element_3darray[(down_y + dy) / 32][(right_x) / 32] != 6) {
							y += dy;
							jumpingHeight = 0; //保持掉落就歸0的好習慣
						}
						else { // 表示跟地板還有一些縫隙，或是剛剛好OntTheGround
							y = (y / 32) * 32 + 16; // 小於dy的位移
							jumpingHeight = 0; // 非跳躍要歸零
							isOnTheGround = true; // 經過位移後就會OnTheGround
							isFalling = false;
							isJumping = false;
							fallingstate = 1;
						}
					}
				}

				
			}else{
				// 轉場階段無法動作
				if (transitionState == 1) {
					// TODO
					// 如果正在爬樓梯(isClimbing)，要把原本的洛克人unshow，並且toggle左右爬梯動畫
					if (isClimbing) {
						if (climbing[0].IsAnimationDone()) {
							climbing[0].ToggleAnimation();
						}
						if (climbingShine[0].IsAnimationDone()) {
							climbingShine[0].ToggleAnimation();
						}
					}
					//重置子彈
					for (int i = 0; i < 3; i++)
					{
						beamammo[i].SetTopLeft(ammoloc[i][0] - stage_x, ammoloc[i][1] - stage_y);
					}
				}
				else if (transitionState == 2) {
					if (isClimbing) {
						if (climbing[0].IsAnimationDone()) {
							climbing[0].ToggleAnimation();
						}
						if (climbingShine[0].IsAnimationDone()) {
							climbingShine[0].ToggleAnimation();
						}
					}
					//重置子彈
					for (int i = 0; i < 3; i++)
					{
						beamammo[i].SetTopLeft(ammoloc[i][0] - stage_x, ammoloc[i][1] - stage_y);
					}
				}
				else if (transitionState == 3  || transitionState == 4) { 
					// 滑步進廊道跟王關
					x += 1;
					//重置子彈
					for (int i = 0; i < 3; i++)
					{
						beamammo[i].SetTopLeft(ammoloc[i][0] - stage_x, ammoloc[i][1] - stage_y);
					}
				}
			}

			
			hitAnimation[0].SetTopLeft(x - stage_x, y - stage_y);
			hitAnimation[1].SetTopLeft(x - stage_x, y - stage_y);
			resting[0].SetTopLeft(x - stage_x, y - stage_y);
			resting[1].SetTopLeft(x - stage_x, y - stage_y);
			running[0].SetTopLeft(x - stage_x, y - stage_y);
			running[1].SetTopLeft(x - stage_x, y - stage_y);
			jumping[0].SetTopLeft(x - stage_x, y - stage_y);
			jumping[1].SetTopLeft(x - stage_x, y - stage_y);
			climbing[0].SetTopLeft(x - stage_x, y - stage_y);
			climbing[1].SetTopLeft(x - stage_x, y - stage_y);
			idleshooting[0].SetTopLeft(x - stage_x, y - stage_y);
			idleshooting[1].SetTopLeft(x - stage_x, y - stage_y);
			runningshooting[0].SetTopLeft(x - stage_x, y - stage_y);
			runningshooting[1].SetTopLeft(x - stage_x, y - stage_y);
			jumpingshooting[0].SetTopLeft(x - stage_x, y - stage_y);
			jumpingshooting[1].SetTopLeft(x - stage_x, y - stage_y);
			laddershooting[0].SetTopLeft(x - stage_x, y - stage_y);
			laddershooting[1].SetTopLeft(x - stage_x, y - stage_y);
			restingShine[0].SetTopLeft(x - stage_x, y - stage_y);
			restingShine[1].SetTopLeft(x - stage_x, y - stage_y);
			runningShine[0].SetTopLeft(x - stage_x, y - stage_y);
			runningShine[1].SetTopLeft(x - stage_x, y - stage_y);
			jumpingShine[0].SetTopLeft(x - stage_x, y - stage_y);
			jumpingShine[1].SetTopLeft(x - stage_x, y - stage_y);
			climbingShine[0].SetTopLeft(x - stage_x, y - stage_y);
			climbingShine[1].SetTopLeft(x - stage_x, y - stage_y);
		};
		void OnBeginState(int init_x, int init_y, int point) {
			x = init_x;
			y = init_y;
			dx = 4; // 已乘兩倍，左右橫移速度
			dy = 10; //已成兩倍，向上
			if (point == -1) {
				lives = 3;
			}
			else {
				lives -= 1;
			}
			blood = 28;
			jumpCount = 0;
			fallCount = 0;
			accePeriod = 5;
			accePeriod_up = 1;
			jumpingHeight = 0;
			upPressed = false;
			downPressed = false;
			jumpPressed = false;
			shootPressed = false;
			isfirstclimb = true;
			leftPressed = false;
			rightPressed = false;
			isResting = false;
			isJumping = false;
			isOnTheGround = true;
			isFalling = true;
			isShooting = false;
			isFacingRight = false;
			isClimbing = false;
			climbjumpstate = 0;
			fallingstate = 0;
			startfalling = true;
			canJump = true;
			canShot = true;
			canClimb = true;
			gundown = false;
			isShot[0] = false;
			isShot[1] = false;
			isShot[2] = false;
			ammodirect[0] = 0;
			ammodirect[1] = 1;
			ammodirect[2] = 2;
			ammodx = 10;
			ammocount = 0;
			resting[0].SetTopLeft(x - stage_x, y - stage_y);
			resting[1].SetTopLeft(x - stage_x, y - stage_y);
			running[0].SetTopLeft(x - stage_x, y - stage_y);
			running[1].SetTopLeft(x - stage_x, y - stage_y);
			jumping[0].SetTopLeft(x - stage_x, y - stage_y);
			jumping[1].SetTopLeft(x - stage_x, y - stage_y);
			climbing[0].SetTopLeft(x - stage_x, y - stage_y);
			climbing[1].SetTopLeft(x - stage_x, y - stage_y);
			isHitState = 0;

			// try to delete these code, technically it doesn't fail;
		}
		void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {

			if (nChar == VK_LEFT) {
				leftPressed = true;
			}
			if (nChar == VK_RIGHT) {
				rightPressed = true;
			}
			if (nChar == VK_UP) {
				upPressed = true;
			}
			if (nChar == VK_DOWN) {
				downPressed = true;
			}
			if (nChar == 0x5A) { // z was pressed
				jumpPressed = true;
			}
			if (nChar == 0x58) { // x was pressed
				shootPressed = true;
			}
		};
		void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) {
			if (nChar == VK_LEFT) {
				leftPressed = false;
			}
			if (nChar == VK_RIGHT) {
				rightPressed = false;
			}
			if (nChar == VK_UP) {
				upPressed = false;
			}
			if (nChar == VK_DOWN) {
				downPressed = false;
			}
			if (nChar == 0x5A) { // z was unpressed
				jumpPressed = false;
			}
			if (nChar == 0x58) { // x was pressed
				shootPressed = false;
			}
		};

		int getX() {
			return x;
		}
		int getY() {
			return y;
		}
		int getBlood() {
			return blood;
		}
		int getLives() {
			return lives;
		}
		void setmap(vector<vector<int>> map) {
			block_element_3darray = map;
		}

		CMovingBitmap getCurrentBitmap() {
			// TODO
			return resting[0];
		}
		bool getIsHit() {
			if (isHitState == 0)
				return false;
			return true;
		}
		void decreaseBlood(int damage) {
			blood -= damage;
		}
		void setIsAttackedFromRight(bool isAttackedFromRight) {
			this->isAttackedFromRight = isAttackedFromRight;
		}
		void setIsHit() {
			// state 0 當作沒被打
			isHitState = 1;
		}

	private:
		vector<int> level_left = { 0 , 768 * 2, 768 * 2, 728 * 2, 768 * 2, 1280 * 2, 1280 * 2, 1280 * 2, 1280 * 2, 1792 * 2, 1792 * 2, 1792 * 2 };//3072王關 要再改
		vector<int> level_top = { 2048 * 2 ,1792 * 2, 1536 * 2, 1280 * 2, 1024 * 2, 768 * 2, 512 * 2, 256 * 2, 0, 256 * 2, 512 * 2, 768 * 2 };//768王關 要再改 跟地圖數據level數不符
		vector<vector<int>> block_element_3darray;
		CMovingBitmap resting[2];
		CMovingBitmap running[2];
		CMovingBitmap climbing[2];
		CMovingBitmap jumping[2];
		CMovingBitmap currentBitmap;
		CMovingBitmap idleshooting[2];
		CMovingBitmap runningshooting[2];
		CMovingBitmap climbingshooting[2];
		CMovingBitmap jumpingshooting[2];
		CMovingBitmap laddershooting[2];
		CMovingBitmap beamammo[3];
		string message;
		bool isShot[3] = { false,false,false };
		CMovingBitmap hitAnimation[2];
		CMovingBitmap shine;
		CMovingBitmap restingShine[2];
		CMovingBitmap runningShine[2];
		CMovingBitmap climbingShine[2];
		CMovingBitmap jumpingShine[2];
		CMovingBitmap timer;

		bool upPressed = false; // used to moving up while climbing ladder
		bool downPressed = false; // used to moving down while climbing ladder
		bool jumpPressed = false; // 0x5A key z was pressed or not
		bool shootPressed = false; // 0x58 key x was pressed or not
		bool isfirstclimb = true;
		bool leftPressed = false;
		bool rightPressed = false;
		bool isResting = false;
		bool isJumping = false;
		bool isOnTheGround = true;
		bool isFalling = true;
		bool isShooting = false;
		bool isFacingRight = false;
		bool isClimbing = false;
		int climbjumpstate = 0;
		int fallingstate = 0;
		int isHitState = 0;
		bool startfalling = true;
		bool canJump = true;
		bool canShot = true;
		bool canClimb = true;
		bool gundown = false;
		bool isHit;
		bool isAttackedFromRight;
		int accePeriod_up = 1;
		// 開發到別的Stage時會需要
		//vector<int> initX_by_stage = { 232};
		//vector<int> initY_by_stage = { 4368};
		//int x = 232;
		//int y = 4368;

		// 剪刀窗戶的腳色位置
		// int x = 1792;
		// int y = 2304;

		// 廊道前
		 int x = 2164*2;
		 int y = 800*2;

		int dx = 4; // 已乘兩倍，左右橫移速度
		int dy = 10; //已成兩倍，向上
		int blood = 28;
		int lives = 3;
		int jumpCount = 0;
		int fallCount = 0;
		int accePeriod = 5;
		int jumpingHeight = 0;
		int ammoloc[3][2];
		int ammodirect[3];
		int ammodx = 12;
		int ammocount = 0;
	};
}