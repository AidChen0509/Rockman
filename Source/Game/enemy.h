#pragma once
namespace game_framework {
	class Enemy
	{
	public:
		Enemy() {};

		virtual ~Enemy() {};
		virtual void OnMove(int rockmanX, int rockmanY, int stage_x, int stage_y) = 0;
		virtual void OnShow() = 0;
		virtual void OnInit() = 0;
		// 將每一個子彈跟這個物件做交流，判斷怪物被打掉沒，如果成功打死怪物，會回傳true，讓statge可以掉落對應的獎勵
		virtual bool beenAttacked(CMovingBitmap bullet) = 0;

		// 將每個敵人跟rockman做交流
		// 回傳是否有打中洛克人
		virtual bool successfullyAttack(CMovingBitmap rockman) = 0;


		// getter
		virtual int getX() = 0;
		virtual int getY() = 0;
		virtual int getDamage() = 0;
		virtual int getBlood() = 0;
		virtual CMovingBitmap getBitmap() = 0;

		// return true代表攻擊從洛克人的右手邊來
		// return false代表攻擊從左手邊來
		virtual bool isAttackFromRight() = 0;


	private:
		// 感覺x, y , _initX, _initY都可以放這裡，省去多餘的code

	};

	class Heli : public Enemy
	{
	public:
		// map 好像不需要
		Heli(int x, int y) { //生成位置
			// 不能將OnInit寫在這會直接出錯?
			_initX = x;
			_initY = y;
		};
		~Heli() override{};

		void OnInit() override{
			left.LoadBitmapByString({"resources/enemy/heli/heliLookLeft1.bmp", "resources/enemy/heli/heliLookLeft2.bmp"}, RGB(128, 0, 128));
			right.LoadBitmapByString({ "resources/enemy/heli/heliLookRight1.bmp", "resources/enemy/heli/heliLookRight2.bmp" }, RGB(128, 0, 128));
			left.SetAnimation(100, false);
			right.SetAnimation(100, false);
		}
		void OnMove(int rockmanX, int rockmanY, int stage_x, int stage_y) override {
			if(blood > 0){
				// 理想情況是往左往右都會生成怪物，但實際情況是洛克人回頭就不會再產怪了，要向右才會遇到
				if (isActivate == false) { //怪物還沒生成
					// 如果stage camera碰到生成點，就會生成->activate
					// ( rockmanX < 生成點 && rockmanX + 280 > 生成點) || (rockmanX > 生成點 && rockmanX - 232 < 生成點 )
						
					if(_initY/512 == rockmanY/512){ //在同一層
						if ((stage_x < _initX && _initX < stage_x + 512) &&
							(stage_y < _initY && _initY < stage_y + 512)) { //怪物生成
							if (canActivate) {
								isActivate = true;
								x = _initX;
								y = _initY;
								if (rockmanX < _initX) {
									direction = -1;
								}
								else {
									direction = 1;
								}
							}
						}
						else {
							canActivate = true;
						}
						left.SetTopLeft(x-stage_x, y-stage_y);
						right.SetTopLeft(x - stage_x, y - stage_y);
					}
				}
				else if(isActivate) {
					if (!((stage_x < x && x < stage_x + 512) &&
						(stage_y < y && y < stage_y + 512)) ||
						_initY / 512 != rockmanY / 512) { //怪物超出畫面，消失
						if (rockmanX <= _initX + 280 && rockmanX >= _initX - 232)
							canActivate = false;
						else
							canActivate = true;
						isActivate = false;
						isUpAttack = false;
						isDownAttack = false;
						dx = 3;
					}
					else { //處理怪物的移動情境
						// 先不分左右
						if (!isUpAttack && !isDownAttack) { //但還沒進入Attack
							if (abs(rockmanX - x) <= 24 * 2 * 2) { //距離到了，進入Attack
								targetY = rockmanY;
								if (rockmanY < y) { //向上追擊
									isUpAttack = true;
									isDownAttack = false;
									// int step = (24 * 2 * 2) / 3; //應該不需要
									dy = -((y - targetY) / 16);
									dx *= 2;
								}
								else if(rockmanY > y){ //向下追擊
									isUpAttack = false;
									isDownAttack = true;
									dy = ((targetY - y) / 16);
									dx *= 2;
								}
							}
							else {
								dy = 0;
							}
							if (rockmanX > x) {
								direction = 1;
							}
							else {
								direction = -1;
							}
							x += (dx*direction);
							y += (dy);
						}
						else if (isUpAttack) { //正在向上向右
							x += (dx*direction);
							if (dy < 0) {
								if (y + dy < targetY) {
									y = targetY;
									dy *= -1; //開始下墜
								}
								else {
									y += (dy);
								}
							}
							else if (dy > 0){ // 攻擊完正在向下向右
								if (y + dy > _initY) {
									y = _initY;
									dy = 0;
									isUpAttack = false;
									isDownAttack = false;
									targetY = rockmanY;
									if (rockmanX > x)
										direction = 1;
									else
										direction = -1;
									dx /= 2;
								}
								else {
									y += dy;
								}
							}
						}
						else if (isDownAttack) {
							x += (dx*direction);
							if (dy > 0) {
								if (y + dy > targetY) {
									y = targetY;
									dy *= -1; //開始上升
								}
								else {
									y += (dy);
								}
							}
							else if (dy < 0) { // 攻擊完正在向上向右
								if (y + dy < _initY) {
									y = _initY;
									dy = 0;
									isUpAttack = false;
									isDownAttack = false;
									targetY = rockmanY;
									if (rockmanX > x)
										direction = 1;
									else
										direction = -1;
									dx /= 2;

								}
								else {
									y += dy;
								}
							}
						}
						left.SetTopLeft(x - stage_x, y - stage_y);
						right.SetTopLeft(x - stage_x, y - stage_y);
					}
				}
			}
			else { //被打死blood = 0
				if (rockmanX <= _initX + 280 && rockmanX >= _initX - 232) //介於生成地點的那張圖512之間
					canActivate = false;
				else
					canActivate = true;
				isActivate = false;
				isUpAttack = false;
				isDownAttack = false;
				blood = 1; //被打死了，血量重製
				dx = 3;
				dy = 0; //我後來加的
			}
		};
		void OnShow() override {
			if (isActivate) {
				if (direction == 1) {
					right.ShowBitmap(2);
					currentBitmap = right;
				}
				else {
					left.ShowBitmap(2);
					currentBitmap = left;
				}
			}
		};
		
		// 怪物被打中與否
		bool beenAttacked(CMovingBitmap bullet) override {
			if (CMovingBitmap::IsOverlap(bullet, currentBitmap)) {
				blood -= 1;
				return true;
			}
			return false;
		};
		// 怪物成功打到洛克人與否
		bool successfullyAttack(CMovingBitmap rockman) override {
			// 視不同怪物來實作邏輯
			// Heli只有碰撞攻擊，所以判斷是否重疊就好
			if (CMovingBitmap::IsOverlap(rockman, currentBitmap)) { //有打中
				if (rockman.GetLeft() < currentBitmap.GetLeft()) {
					attackFromRight = true;
				}
				else {
					attackFromRight = false;
				}
				return true;
			}
			return false;
		}
		// 對於有子彈的怪物，可以實作的方式
		//for i = 0 to allBitmap:
		//	if CMovingBitmap::IsOverlap(allBitmap[i], rockman)
		//		return 
		//return CMovingBitmap::IsOverlap(left, rockman); // or false

		bool isDead() {
			if (blood <= 0) {
				return true;
			}
			else {
				return false;
			}
		}

		bool isAttackFromRight() {
			return attackFromRight;
		}

		// getter
		int getX() override {
			return x;
		}
		int getY() override {
			return y;
		}
		CMovingBitmap getBitmap() override {
			return currentBitmap;
		};
		int getDamage() override{
			return damage;
		}
		int getBlood() override {
			return blood;
		}
		
	private:
		bool isActivate = false;
		bool isUpAttack = false;
		bool isDownAttack = false;
		bool canActivate = true;
		bool attackFromRight;
		int direction;
		int x;
		int y;
		int dx = 3;
		int dy = 0;
		int targetX;
		int targetY;
		int _initX;
		int _initY;

		int blood = 1;
		int damage = 2;

		CMovingBitmap left;
		CMovingBitmap right;
		CMovingBitmap currentBitmap;

	};
	
	class Beak : public Enemy
	{
	public:
		Beak(int x, int y, int direct) {
			direction = direct;
			_initX = x;
			_initY = y;
			if (direct == 0) {
				_initBulletX = x;
				_initBulletY = y + 16;
			}
			else {
				_initBulletX = x + 32;
				_initBulletY = y + 16;
			}
			for (int i = 0; i < 4; i++)
			{
				// X
				location[i][0] = _initBulletX;
				// Y
				location[i][1] = _initBulletY;
			}
		};
		~Beak() {};
		void OnInit() override {
			if (direction == 0) { //面左
				open.LoadBitmapByString({
					"resources/enemy/beak/beakLeft0.bmp",
					"resources/enemy/beak/beakLeft1.bmp",
					"resources/enemy/beak/beakLeft2.bmp",
					"resources/enemy/beak/beakLeft3.bmp",
					}, RGB(128, 0, 128));
				close.LoadBitmapByString({
					"resources/enemy/beak/beakLeft3.bmp",
					"resources/enemy/beak/beakLeft2.bmp",
					"resources/enemy/beak/beakLeft1.bmp",
					"resources/enemy/beak/beakLeft0.bmp",
					"resources/enemy/beak/beakLeft0.bmp",
					"resources/enemy/beak/beakLeft0.bmp",
					"resources/enemy/beak/beakLeft0.bmp",
					"resources/enemy/beak/beakLeft0.bmp",
					"resources/enemy/beak/beakLeft0.bmp",
					"resources/enemy/beak/beakLeft0.bmp",
					"resources/enemy/beak/beakLeft0.bmp",
					"resources/enemy/beak/beakLeft0.bmp",
					"resources/enemy/beak/beakLeft0.bmp",
					"resources/enemy/beak/beakLeft0.bmp",
					"resources/enemy/beak/beakLeft0.bmp",
					"resources/enemy/beak/beakLeft0.bmp",
					"resources/enemy/beak/beakLeft0.bmp",
					"resources/enemy/beak/beakLeft0.bmp",
					}, RGB(128, 0, 128));
			}
			else {
				open.LoadBitmapByString({
					"resources/enemy/beak/beakRight0.bmp",
					"resources/enemy/beak/beakRight1.bmp",
					"resources/enemy/beak/beakRight2.bmp",
					"resources/enemy/beak/beakRight3.bmp",
					}, RGB(128, 0, 128));
				close.LoadBitmapByString({
					"resources/enemy/beak/beakRight3.bmp",
					"resources/enemy/beak/beakRight2.bmp",
					"resources/enemy/beak/beakRight1.bmp",
					"resources/enemy/beak/beakRight0.bmp",
					"resources/enemy/beak/beakRight0.bmp",
					"resources/enemy/beak/beakRight0.bmp",
					"resources/enemy/beak/beakRight0.bmp",
					"resources/enemy/beak/beakRight0.bmp",
					"resources/enemy/beak/beakRight0.bmp",
					"resources/enemy/beak/beakRight0.bmp",
					"resources/enemy/beak/beakRight0.bmp",
					"resources/enemy/beak/beakRight0.bmp",
					"resources/enemy/beak/beakRight0.bmp",
					"resources/enemy/beak/beakRight0.bmp",
					"resources/enemy/beak/beakRight0.bmp",
					"resources/enemy/beak/beakRight0.bmp",
					"resources/enemy/beak/beakRight0.bmp",
					"resources/enemy/beak/beakRight0.bmp",
					}, RGB(128, 0, 128));
			}
			for (int i = 0; i < 4; i++)
			{
				bullet[i].LoadBitmapByString({ "resources/enemy/beak/bullet.bmp" }, RGB(128, 0, 128));
			}
			// 找到bug了，要剪掉stage才可以
			//open.SetTopLeft(_initX, _initY);
			//close.SetTopLeft(_initX, _initY);

			open.SetAnimation(200, true);
			close.SetAnimation(200, true);
		}
		void OnMove(int rockmanX, int rockmanY, int stage_x, int stage_y) override {
			if ((_initY / 512 == rockmanY / 512) && 
				(stage_x < _initX && _initX < stage_x + 512) &&
				(stage_y < _initY && _initY < stage_y + 512)) {
				isActivate = true;
			}
			else {
				reset();
				isActivate = false;
			}
			// 開砲台動畫->發出子彈->關砲台動作->隔一下之後->start
			if (isActivate) {
				if (state == 0) { //toggle開砲台
					state = 1;
					open.ToggleAnimation();
				}
				if (state == 1) { //已經toggle開炮了
					if (open.IsAnimationDone()) { //動畫結束，開始噴射子彈
						for (int i = 0; i < 4; i++)
						{
							if (i == 0) {
								if (!isShot[i]) {
									isShot[i] = true;
								}
							}
							else {
								if (!isShot[i] && distance[i - 1] > 4 * 32) { //看起來是差四格，下一顆才能噴射
									isShot[i] = true;
								}
							}
						}
						if (distance[3] > 64) {
							// 更改一，這裡需要把圖歸0，才不會glitch
							open.SetFrameIndexOfBitmap(0);
							state = 2;
							// 可以開始關砲台了
						}
					}
				}
				if (state == 2) { // toggle 關炮
					close.ToggleAnimation();
					state = 3;
				}
				if (state == 3) {
					if (close.IsAnimationDone()) {
						state = 0;
						reset();
					}
				}
				for (int i = 0; i < 4; i++)
				{
					if (isShot[i]) {
						if (direction == 0) { //面左
							location[i][0] -= speedX;
							location[i][1] += speedY[i];
							distance[i] += speedX;
						}
						else {
							location[i][0] += speedX;
							location[i][1] += speedY[i];
							distance[i] += speedX;
						}
					}
					bullet[i].SetTopLeft(location[i][0] - stage_x, location[i][1] - stage_y);
				}
			}
			open.SetTopLeft(_initX - stage_x, _initY - stage_y);
			close.SetTopLeft(_initX - stage_x, _initY - stage_y);
		}
		void OnShow() override {
			if (isActivate) {
				if (state == 0 || state == 1)
					open.ShowBitmap(2);
				if (state == 2 || state == 3)
					close.ShowBitmap(2);
				for (int i = 0; i < 4; i++){
					if(isShot[i])
						bullet[i].ShowBitmap(2);
				}
			}
		}
		
		bool beenAttacked(CMovingBitmap rockmanbullet) override {
			if(isActivate){
				if (CMovingBitmap::IsOverlap(open, rockmanbullet)) {
					if (state == 0 || state == 1) {
						if (open.GetFrameIndexOfBitmap() != 0) {
							blood -= 1;
							return true;
						}
					}
					if (state == 2 || state == 3){
						if (!(3 <= close.GetFrameIndexOfBitmap() && close.GetFrameIndexOfBitmap() <= 17)) {
							blood -= 1;
							return true;
						}
					}	
				}
			}
			return false;
		}

		bool successfullyAttack(CMovingBitmap rockman) override {
			// 撞到扣1
			// 子彈打到扣2
			// 優先判定子彈有沒有射到
			for (int i = 0; i < 4; i++)
			{
				if (isShot[i] && CMovingBitmap::IsOverlap(bullet[i], rockman)) {
					damage = 2;
					return true;
				}
			}
			if (CMovingBitmap::IsOverlap(open, rockman)) {
				damage = 1;
				return true;
			}
			return false;
		}
		int getX() override {
			return _initX;
		}
		int getY() override {
			return _initY;
		}
		int getDamage() override {

			return damage;
		}
		int getBlood() override {
			return blood;
		}

		// 不確定用不用的到
		CMovingBitmap getBitmap() override {
			return open;
		}

		bool isAttackFromRight() override {
			return true;
		}
		void reset() {
			for (int i = 0; i < 4; i++)
			{
				distance[i] = 0;
				location[i][0] = _initBulletX;
				location[i][1] = _initBulletY;
				isShot[i] = false;
			}
		}
	private:
		int state = 0;
		bool isActivate;
		bool isShot[4] = { false, false, false, false };
		int direction;
		int damage = 0;
		int _initX;
		int _initY;
		int _initBulletX;
		int _initBulletY;

		int blood = 1;

		CMovingBitmap open;
		CMovingBitmap close;
		CMovingBitmap bullet[4];

		// 裝子彈座標
		int location[4][2];

		// 子彈路徑長，讓後續的子彈判斷能不能射
		int distance[4] = {0, 0, 0, 0};

		// 子彈速度
		int speedX = 5;
		int speedY[4] = {-4, -2, 2, 4};

	};


};