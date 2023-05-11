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
		virtual bool getIsActivate() = 0;
		virtual bool isDead() = 0;
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
		Heli(int x, int y) { //生成位置
			// 不能將OnInit寫在這會直接出錯?
			_initX = x;
			_initY = y;
		};
		~Heli() override{};
		Heli() = delete;
		void OnInit() override{
			left.LoadBitmapByString({"resources/enemy/heli/heliLookLeft1.bmp", "resources/enemy/heli/heliLookLeft2.bmp"}, RGB(128, 0, 128));
			right.LoadBitmapByString({ "resources/enemy/heli/heliLookRight1.bmp", "resources/enemy/heli/heliLookRight2.bmp" }, RGB(128, 0, 128));
			left.SetAnimation(100, false);
			right.SetAnimation(100, false);
			currentBitmap = left;
		}
		void OnMove(int rockmanX, int rockmanY, int stage_x, int stage_y) override {
			if(blood > 0){
				// 理想情況是往左往右都會生成怪物，但實際情況是洛克人回頭就不會再產怪了，要向右才會遇到
				if (isActivate == false) { //怪物還沒生成
					// 如果stage camera碰到生成點，就會生成->activate
					// ( rockmanX < 生成點 && rockmanX + 280 > 生成點) || (rockmanX > 生成點 && rockmanX - 232 < 生成點 )				
					if(_initY/512 == rockmanY/512){ //在同一層
						if ((stage_x <= _initX && _initX < stage_x + 512) &&
							(stage_y <= _initY && _initY < stage_y + 512)) { //怪物生成
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
				isActivate = false;
				if (rockmanX <= _initX + 280 && rockmanX >= _initX - 232) { //介於生成地點的那張圖512之間
					canActivate = false;
					//不重製，尤其是blood，會導致進入blood的if
				}
				else {//離開這個範圍後，就可以activate了
					canActivate = true;
					isUpAttack = false;
					isDownAttack = false;
					blood = 1; //被打死了，血量重製
					dx = 3;
					dy = 0; //我後來加的
				}
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
		
		// 怪物被打中與否，有被打到洛克人子彈要消失
		bool beenAttacked(CMovingBitmap bullet) override {
			// 應該要isActivate才能被子彈打到
			if (isActivate && (CMovingBitmap::IsOverlap(bullet, currentBitmap, 2))) {
				blood -= 1;
				return true;
			}
			return false;
		};
		// 怪物成功打到洛克人與否
		// @param rockman可根據洛克人的移動狀態，丟bitmap近來判斷，這樣判斷的更精確
		bool successfullyAttack(CMovingBitmap rockman) override {
			// 視不同怪物來實作邏輯
			// Heli只有碰撞攻擊，所以判斷是否重疊就好
			if (isActivate && CMovingBitmap::IsOverlap(rockman, currentBitmap, 2)) { //有打中
				// Concern: 這裡判斷攻擊方向的方式，有可能不夠精確，但每秒32次的頻率之下，感覺不會有問題
				// if (rockman.GetLeft() < currentBitmap.GetLeft()) {
				if (!direction) {
					attackFromRight = true;
				}
				else {
					attackFromRight = false;
				}
				return true;
			}
			return false;
		}

		bool isDead() override{
			if (blood <= 0) {
				return true;
			}
			else {
				return false;
			}
		}
		bool getIsActivate() override {
			// 怪物有無啟動(有無在畫面上)
			return isActivate;
		}
		bool isAttackFromRight() {
			// return true if the enemy is attack from the rockman's right side
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
			// not sure is needed or not
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
		string message;
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
			if (direct == 0) { //砲台面左，子彈從左中噴出
				_initBulletX = x;
				_initBulletY = y + 16;
			}
			else {  //砲台面右，子彈從右中噴出
				_initBulletX = x + 32;
				_initBulletY = y + 16;
			}
			for (int i = 0; i < 4; i++)
			{
				//把4顆子彈的初始位置設定好
				// X
				location[i][0] = _initBulletX;
				// Y
				location[i][1] = _initBulletY;
			}
		};
		Beak() = delete;
		~Beak() override {};
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
			else {  //面右
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
			// 找到bug了，setTopLeft要減掉stage才會是相對位置啦靠杯
			//open.SetTopLeft(_initX, _initY);
			//close.SetTopLeft(_initX, _initY);

			open.SetAnimation(200, true);
			close.SetAnimation(200, true);
		}
		void OnMove(int rockmanX, int rockmanY, int stage_x, int stage_y) override {
			if(blood > 0){
				if ((_initY / 512 == rockmanY / 512) && 
					(stage_x < _initX && _initX < stage_x + 512) &&
					(stage_y < _initY && _initY < stage_y + 512)) {
					// 依照camera帶到的時間activate
					isActivate = true;
				}
				else {
					resetBullet();
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
							// closeAnimation會很久，所以可以確定跑完，子彈也飛遠了消失了
							state = 0;
							resetBullet();
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
			}
			else { // blood <= 0
				// 把原本射出去的子彈繼續射完
				isActivate = false;
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
					/* 這段感覺不用，本來是希望超出畫面就變false這樣就不會show了，但超出畫面本來就show也show不出來，所以先註解掉
					if (!(location[i][0] < stage_x + 512 && location[i][0] > stage_x && location[i][1] > stage_y && location[i][1] < stage_y+512)) {
						isShot[i] = false;
					}
					*/
					bullet[i].SetTopLeft(location[i][0] - stage_x, location[i][1] - stage_y);
				}
				if ((_initY / 512 == rockmanY / 512) &&
					(stage_x < _initX && _initX < stage_x + 512) &&
					(stage_y < _initY && _initY < stage_y + 512)) {
					// 在範圍內不做事
				}
				else {
					// 出去範圍後，初始化
					resetBullet();
					blood = 1;
					state = 0;
					isActivate = false;
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
			}
			for (int i = 0; i < 4; i++) {
				if (isShot[i])
					bullet[i].ShowBitmap(2);
			}
		}
		
		bool beenAttacked(CMovingBitmap rockmanbullet) override {
			if(isActivate){
				if (CMovingBitmap::IsOverlap(open, rockmanbullet, 2)) {
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
				if (isShot[i] && CMovingBitmap::IsOverlap(bullet[i], rockman, 2)) {
					damage = 2;
					if (rockman.GetLeft() <= bullet[i].GetLeft()) {
						attackFromRight = true;
					}
					else {
						attackFromRight = false;
					}
					return true;
				}
			}
			if (CMovingBitmap::IsOverlap(open, rockman, 2)) {
				damage = 1;
				if (rockman.GetLeft() <= open.GetLeft()) {
					attackFromRight = true;
				}
				else {
					attackFromRight = false;
				}
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
		bool getIsActivate() override {
			return isActivate;
		}
		bool isDead() override {
			if (blood <= 0)
				return true;
			else
				return false;
		}
		// 不確定用不用的到
		CMovingBitmap getBitmap() override {
			return open;
		}

		bool isAttackFromRight() override {
			return attackFromRight;
		}
		void resetBullet() {
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
		bool attackFromRight;

		
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

	
	class Octopus : public Enemy
	{
	public:
		Octopus(int initX, int initY, int endX, int endY, int delay) {
			startX = initX;
			startY = initY;
			this->endX = endX;
			this->endY = endY;
			_initDelay = delay;
		};
		Octopus() = delete;
		~Octopus() override {};
		void OnInit() override {
			open.LoadBitmapByString({ "resources/enemy/octopus/octopus0.bmp", "resources/enemy/octopus/octopus1.bmp", "resources/enemy/octopus/octopus2.bmp", }, RGB(128, 0, 128));
			close.LoadBitmapByString({ 
				"resources/enemy/octopus/octopus2.bmp",
				"resources/enemy/octopus/octopus1.bmp",
				"resources/enemy/octopus/octopus0.bmp", 
				"resources/enemy/octopus/octopus0.bmp",
				"resources/enemy/octopus/octopus0.bmp",
				"resources/enemy/octopus/octopus0.bmp",
				"resources/enemy/octopus/octopus0.bmp",
				"resources/enemy/octopus/octopus0.bmp",
				"resources/enemy/octopus/octopus0.bmp",
				"resources/enemy/octopus/octopus0.bmp",
				"resources/enemy/octopus/octopus0.bmp",
				"resources/enemy/octopus/octopus0.bmp",
				"resources/enemy/octopus/octopus0.bmp",
				}, RGB(128, 0, 128));
			//timer setup
			timer.LoadBitmapByString({ "resources/white.bmp", "resources/white.bmp" }, RGB(255, 255, 255));
			timer.SetTopLeft(0, 0);
			timer.SetAnimation(_initDelay, true);

			open.SetAnimation(100, true); // TODO: adjustment of the delay
			close.SetAnimation(100, true);
		}
		void OnMove(int rockmanX, int rockmanY, int stage_x, int stage_y) override {
			// activate 判定
			if ((startY / 512 == rockmanY / 512) &&
				((startY / 512)*512 == stage_y) && //同一張512*512
				(stage_x < startX && startX < stage_x + 512)/* &&
				(stage_y < startY && startY < stage_y + 512)*/) {
				if (blood > 0)
					isActivate = true;
				else
					isActivate = false;
			}
			else { // 在範圍外，不管有沒有死，都要reset
				reset();
			}
		
			if (isActivate) {
				// TODO
				if (state == -1) { //跑delay
					timer.ToggleAnimation();
					state = 0;
				}
				else if(state == 0){
					if (timer.IsAnimationDone()) {
						isOpen = true;
						open.ToggleAnimation();
						state = 1;
					}
				}
				// 起初的設定為close在初始位置，經過delay過後，轉openAnimation並移動，
				// 到點的瞬間改成closeAnimation，把close load多張一點，
				// 等close animation done的時候轉為openAnimation開始移動回原點
				else if (state == 1) { //起點，預設進來的時候是open剛被toggle，邊開就可以邊移動了，所以不需要判斷isDone
					if ((x == endX) && (y == endY)) {
						//到達目的，同時toggle close的animation
						isOpen = false;
						open.SetFrameIndexOfBitmap(0);
						close.ToggleAnimation();
						state = 2;
					}
					else
					{
						if (endX > startX) { // 起點在左邊，目的為右邊，dx用加的
							x += dx;
						}
						else if(endX < startX) {
							x -= dx;
						}
						if (endY > startY) { //起點在上面，目的為下方，dy用加的
							y += dy;
						}
						else if (endY < startY) {
							y -= dy;
						}
					}
				}
				else if (state == 2) { // isOpen = false，且close剛被toggle
									   // 是一個剛抵達終點的state
					if (!close.IsAnimationDone()) {
						//關閉動畫還沒結束繼續原地發呆
					}
					else { //從目的地open準備回原點
						close.SetFrameIndexOfBitmap(0);
						isOpen = true;
						open.ToggleAnimation();
						state = 3;
					}
				}
				else if (state == 3) {  // isOpen = true，open剛被toggle
										// 開始移動回起點
					if ((x == startX) && (y == startY)) {
						// 到達原點
						open.SetFrameIndexOfBitmap(0);
						isOpen = false;
						close.ToggleAnimation();
						state = 4;
					}
					else {
						if (endX > startX) { // 起點在左邊，目的為右邊，回程dx用減的
							x -= dx;
						}
						else if(endX < startX){
							x += dx;
						}
						if (endY > startY) { //起點在上面，目的為下方，dy用減的
							y -= dy;
						}
						else if (endY < startY) {
							y += dy;
						}
					}
				}
				else if (state == 4) {
					if (close.IsAnimationDone()) {
						close.SetFrameIndexOfBitmap(0);
						isOpen = true;
						open.ToggleAnimation();
						state = 1;
					}
				}
			}
			open.SetTopLeft(x - stage_x, y - stage_y);
			close.SetTopLeft(x - stage_x, y - stage_y);
		}
		void OnShow() override {
			if (isActivate) {
				// timer 有沒有show是關鍵
				timer.ShowBitmap(2);
				if (isOpen) {
					open.ShowBitmap(2);
				}
				else {
					close.ShowBitmap(2);
				}
			}
		}

		// 將每一個子彈跟這個物件做交流，判斷怪物被打掉沒，如果成功打死怪物，會回傳true，讓statge可以掉落對應的獎勵
		bool beenAttacked(CMovingBitmap rockmanbullet) override {
			// TODO
			if (isActivate) {
				if (CMovingBitmap::IsOverlap(open, rockmanbullet, 2)) {
					blood -= 1;
					return true;
				}
			}
			return false;
		}

		// 將每個敵人跟rockman做交流
		// 回傳是否有打中洛克人
		bool successfullyAttack(CMovingBitmap rockman) {
			if (CMovingBitmap::IsOverlap(rockman, open, 2) && isActivate) { //有打中
				// Concern: 這裡判斷攻擊方向的方式，有可能不夠精確，但每秒32次的頻率之下，感覺不會有問題
				if (rockman.GetLeft() < open.GetLeft()) {
					attackFromRight = true;
				}
				else {
					attackFromRight = false;
				}
				return true;
			}
			return false;
		}

		void reset() {
			state = -1;
			blood = 6;
			x = startX;
			y = startY;
			isActivate = false;
			isOpen = false;
		}

		// getter
		int getX() {
			return x;
		}
		int getY() {
			return y;
		}
		int getDamage() {
			// 應該是4沒錯
			return 4;
		}
		int getBlood() override{
			return blood;
		}
		bool getIsActivate() override {
			return isActivate;
		}
		CMovingBitmap getBitmap() override{
			return open;
		}

		// return true代表攻擊從洛克人的右手邊來
		// return false代表攻擊從左手邊來
		bool isAttackFromRight() {
			return attackFromRight;
		}
		bool isDead() override {
			if (blood > 0) {
				return false;
			}
			else {
				return true;
			}
		}
		
	private:
		int startX, startY;
		int endX, endY;
		int x, y;
		int dx = 4, dy = 4;
		int blood = 5;
		int _initDelay = 0;
		int state = -1;

		bool attackFromRight;
		bool isActivate = false;
		bool isOpen = false;

		CMovingBitmap open;
		CMovingBitmap close;
		CMovingBitmap timer;

	};

};