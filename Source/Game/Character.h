#pragma once
namespace game_framework {
	class Character
	{
	public:
		Character() {};
		~Character() {};
		void OnInit(int stage_x, int stage_y) {
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
			jumping[0].LoadBitmapByString({
				"resources/rockman/jumpingLeft.bmp" ,
				}, RGB(128, 0, 128));
			jumping[1].LoadBitmapByString({
				"resources/rockman/jumpingRight.bmp" ,
				}, RGB(128, 0, 128));
			climbing[0].LoadBitmapByString({
				"resources/rockman/climb1.bmp",
				"resources/rockman/climb2.bmp"
				}, RGB(128,0,128));
			climbing[1].LoadBitmapByString({
				"resources/rockman/climb3.bmp"
				}, RGB(128, 0, 128));
			running[0].SetAnimation(100, false);
			running[1].SetAnimation(100, false);
			resting[0].SetAnimation(200, false);
			resting[1].SetAnimation(200, false);
			climbing[0].SetAnimation(150, true);
			// 最好是在Onshow設定位置，避免多餘的code
			resting[0].SetTopLeft(x - stage_x, y - stage_y);
			resting[1].SetTopLeft(x - stage_x, y - stage_y);
			running[0].SetTopLeft(x - stage_x, y - stage_y);
			running[1].SetTopLeft(x - stage_x, y - stage_y);
			jumping[0].SetTopLeft(x - stage_x, y - stage_y);
			jumping[1].SetTopLeft(x - stage_x, y - stage_y);
			climbing[0].SetTopLeft(x - stage_x, y - stage_y);
			climbing[1].SetTopLeft(x - stage_x, y - stage_y);
		};
		void Onshow(int stage_x, int stage_y) {

			// 之後會需要if statement來決定是哪張圖or動畫
			if (!isJumping && !isFalling) {
				if (isResting) { // resting
					if (isFacingRight == false) { // resting_left_side
						resting[0].ShowBitmap(2);
					}
					else {  // 原本面右，繼續面右
						resting[1].ShowBitmap(2);
					}
				}
				else if (isClimbing) {
					climbing[0].ShowBitmap(2);
				}
				else if (!isResting) {
					if (isFacingRight == false) { // running_left_side
						running[0].ShowBitmap(2);
					}
					else {  // 原本面右，繼續面右
						running[1].ShowBitmap(2);
					}
				}
			}
			else {
				if (isFacingRight == false) { // running_left_side
					jumping[0].ShowBitmap(2);
				}
				else {  // 原本面右，繼續面右
					jumping[1].ShowBitmap(2);
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
				if ((leftPressed && rightPressed) || !(leftPressed || rightPressed||isClimbing)) { //按雙鍵，維持原本的方向但不位移
					isResting = true;
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
				// 著地後速度回歸為10
				if (isOnTheGround) {
					dy = 10;
					accePeriod = 5;
				}
				if (isJumping && dy - 1 >= 6) {
					if (jumpCount == 0) {
						dy--;
					}
					jumpCount++;
					jumpCount = jumpCount % 3;
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

				if (isOnTheGround) {
					if (!jumpPressed) { //如果在地板上 && 沒有按跳 -> 要判斷懸空與否要著地
						if (block_element_3darray[(down_y + 2) / 32][(left_x) / 32] != 1
							&& block_element_3darray[(down_y + 2) / 32][(right_x) / 32] != 1
							&& !isClimbing
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
							isFalling = false;
							isJumping = false;

						}
						canJump = true;
					}
					else { //OnTheGround的時候，按跳
						if (canJump) {
							if (block_element_3darray[(top_y - dy) / 32][(left_x) / 32] != 1
								&& block_element_3darray[(top_y - dy) / 32][(right_x) / 32] != 1
								&& block_element_3darray[(top_y - dy) / 32][(left_x) / 32] != -1
								&& block_element_3darray[(top_y - dy) / 32][(right_x) / 32] != -1) {
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
								isOnTheGround = false;
								y = (y / 32) * 32;
							}
							canJump = false;
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
							&& block_element_3darray[(down_y + dy) / 32][(right_x) / 32] != 1) {
							y += dy;
							jumpingHeight = 0; //保持掉落就歸0的好習慣
						}
						else { // 表示跟地板還有一些縫隙，或是剛剛好OntTheGround
							y = (y / 32) * 32 + 16; // 小於dy的位移
							jumpingHeight = 0; // 非跳躍要歸零
							isOnTheGround = true; // 經過位移後就會OnTheGround
							isFalling = false;
							isJumping = false;
						}
					}
				}

				if (upPressed) { //代替爬梯子
					if(block_element_3darray[(top_y - 8) / 32][(mid_x) / 32] == 2|| block_element_3darray[down_y  / 32][(mid_x) / 32] == 2){
						isClimbing = true;
						isResting = false;
						isFalling = false;
						jumpPressed = false;
						isJumping = false;
						isOnTheGround = true;
						if (climbing[0].IsAnimationDone()) {
							climbing[0].ToggleAnimation();
						}
						if (isfirstclimb&&jumpPressed) {
							y = top_y-(down_y-top_y);
							isfirstclimb = false;
						}
						y -= 3;
						x = (mid_x/32)*32-9;
					}
					else if (block_element_3darray[down_y  / 32][(mid_x) / 32] == 0)
					{
						isClimbing = false;
						isfirstclimb = true;
					}
				}
				if (downPressed) { //代替爬梯子
					if (block_element_3darray[(down_y+2) / 32][(mid_x) / 32] == 2||(block_element_3darray[(top_y - 2) / 32][(mid_x) / 32] == 2&& block_element_3darray[(down_y + 2) / 32][(mid_x) / 32] == 0)) {
						isClimbing = true;
						isResting = false;
						jumpPressed = false;
						isOnTheGround = true;
						if (climbing[0].IsAnimationDone()) {
							climbing[0].ToggleAnimation();
						}
						y += 3;
						x = (mid_x / 32) * 32 - 9;
					}
					else if (block_element_3darray[(down_y+2) / 32][(mid_x) / 32] == 1 && isClimbing) {
						isClimbing = false; 
					}
					else if (block_element_3darray[(top_y-2) / 32][(mid_x) / 32] == 0&&isClimbing) {
						isClimbing = false;
						x += 5;
					}
				}
			}else{
				// 轉場階段無法動作
				if (transitionState == 1 && transitionState == 2) {
					// TODO
					// 如果正在爬樓梯(isClimbing)，要把原本的洛克人unshow，並且toggle左右爬梯動畫
				}
				else if (transitionState == 3  || transitionState == 4) { 
					// 滑步進廊道跟王關
					x += 1;
				}
			}
			resting[0].SetTopLeft(x - stage_x, y - stage_y);
			resting[1].SetTopLeft(x - stage_x, y - stage_y);
			running[0].SetTopLeft(x - stage_x, y - stage_y);
			running[1].SetTopLeft(x - stage_x, y - stage_y);
			jumping[0].SetTopLeft(x - stage_x, y - stage_y);
			jumping[1].SetTopLeft(x - stage_x, y - stage_y);
			climbing[0].SetTopLeft(x - stage_x, y - stage_y);
			climbing[1].SetTopLeft(x - stage_x, y - stage_y);

		};
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
				shootPressed = true;
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
		void setmap(vector<vector<int>> map) {
			block_element_3darray = map;
		}
	private:
		vector<int> level_left = { 0 , 768 * 2, 768 * 2, 728 * 2, 768 * 2, 1280 * 2, 1280 * 2, 1280 * 2, 1280 * 2, 1792 * 2, 1792 * 2, 1792 * 2 };//3072王關 要再改
		vector<int> level_top = { 2048 * 2 ,1792 * 2, 1536 * 2, 1280 * 2, 1024 * 2, 768 * 2, 512 * 2, 256 * 2, 0, 256 * 2, 512 * 2, 768 * 2 };//768王關 要再改 跟地圖數據level數不符
		vector<vector<int>> block_element_3darray;
		CMovingBitmap resting[2];
		CMovingBitmap running[2];
		CMovingBitmap climbing[2];
		CMovingBitmap jumping[2];

		bool upPressed = false; // used to moving up while climbing ladder
		bool downPressed = false; // used to moving down while climbing ladder
		bool jumpPressed = false; // 0x5A key z was pressed or not
		bool shootPressed = false; // 0x58 key x was pressed or not
		// bool isJumpPressedKeyUp = true;
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
		bool canJump = true;
		// 開發到別的Stage時會需要
		//vector<int> initX_by_stage = { 232};
		//vector<int> initY_by_stage = { 4368};
		int x = 232;
		int y = 4368;

		// 剪刀窗戶的腳色位置
		//int x = 1792;
		//int y = 2304;

		// 測試
		//int x = 2050*2;
		//int y = 800*2;

		int dx = 4; // 已乘兩倍，左右橫移速度
		int dy = 10; //已成兩倍，向上
		int blood = 28;
		int lives = 3;
		int jumpCount = 0;
		int fallCount = 0;
		int accePeriod = 5;
		int jumpingHeight = 0;
	};
}