//This is a C++ file.Please go another place to Run 
#include <iostream>
#include <unistd.h>
#include <string>
#include <ctime>
#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;
int health1 = 5, health2 = 5;
int power1 = 0, power2 = 0;
int cnt = 0;
int px = 5;
int py = 5;

int speed = 1;
const int HEIGHT = 20;
const int WIDTH = 20;
void draw () {
    system ("cls");
    cout << "本游戏使用 w（前），a（左），s（后），d（右）移动" << endl;
    for (int y = 1; y <= HEIGHT; y++) {
        for (int x = 1; x <= WIDTH; x++) {
            if (y == py && x == px) {
                cout << "H  ";
            } else if (y == 1 || y == HEIGHT) {
                cout << "--";
            } else if (x == 1 || x == WIDTH) {
                cout << "|";
            } else {
                cout << "·  ";
            }
            
                
            
           
        }
        cout <<  endl;
    }
	
}
void mobile () {
	
	    
    char x;
    cin >> x;
    if (x == 'w') {
        py -= speed;
    }
    if (x == 'a') {
		px -= speed;
	}
	if (x == 's') {
		py += speed;
	}
	if (x == 'd') {
		px += speed;
	}
	    
	     
}
bool die () {
	if (px >= WIDTH || py >= HEIGHT || px <= 1 || py <= 1) {
		return 0;
	}
	return true;
}
void intro() {
	srand(time(NULL));
	cout << endl << endl;
	cout << "两人回合制游戏，每回合双方同时在“攻击、防御、集气、必杀”四种行动中选一种。" << endl << endl;
	cout << "1. “生命”：每人 5 点生命，生命归 0 立即死亡；" << endl << endl;
	cout << "2. “伤害”：攻击造成 1 伤害，防御免除攻击伤害，互相攻击双方都不受伤害，必杀造成 3 伤害；" << endl << endl;
	cout << "3. “必杀”：必杀需消耗 2 “气”，双方同时必杀则相安无事，否则放必杀者给对手造成伤害，对手的行动无任何效果；" << endl << endl;
	cout << "4. “气”：防御对方攻击增加 1 气，集气且不受到伤害增加 1 气。" << endl << endl;
	cout << "----------单挑开始，你是武将1，电脑指挥武将2----------" << endl << endl;
}

// 片段3 确定人类策略
namespace human {
	int strategy() {
		// 输出出卡提示
		cout << "用数字代表本回合武将1的行动：1攻击，2防御，3集气，4必杀" << endl;

		// 读入
		int x = 0;
		if (!(cin >> x)) {
			x = 0;
			getchar();
			cin.clear();
		}
		return x;
	}
}

// 片段4 确定电脑策略
namespace ai {
	int strategy() {
		if (power2 >= 2) return 4;
		return rand() % 3 + 1;
	}
}

//片段5 根据双方行动, 执行一回合的对战
bool fight(int d1, int d2) {
	if (d1 < 1 || d1 > 4) {
		cout << "【【【武将1没有这种策略啦～重新开始回合" << cnt << "！】】】" << endl;
		return true;
	}
	if ((d1 == 4 && power1 < 2)) {
		cout << "【【【武将1不够气来放必杀！重新开始回合" << cnt << "！】】】" << endl;
		return true;
	}

	cout << "【【【" ;
	if (d1 == 1 && d2 == 1) {
		cout << "两人同时攻击，相安无事";
	}
	if (d1 == 1 && d2 == 2) {
		power2++;
		cout << "武将2防御了武将1的攻击，得1气";
	}
	if (d1 == 2 && d2 == 1) {
		power1++;
		cout << "武将1防御了武将2的攻击，得1气";
	}
	if (d1 == 2 && d2 == 2) {
		cout << "两人同时防御，相安无事";
	}
	if (d1 == 1 && d2 == 3) {
		health2--;
		cout << "武将2集气时受到武将1的攻击，损失1生命";
	}
	if (d1 == 3 && d2 == 1) {
		health1--;
		cout << "武将1集气时受到武将2的攻击，损失1生命";
	}
	if (d1 == 2 && d2 == 3) {
		power2++;
		cout << "武将2趁武将1防御时集气，得1气";
	}
	if (d1 == 3 && d2 == 2) {
		power1++;
		cout << "武将1趁武将2防御时集气，得1气";
	}
	if (d1 == 3 && d2 == 3) {
		power1++;
		power2++;
		cout << "双方同时集气，各得1气";
	}
	if (d1 == 4 && d2 != 4) {
		power1 -= 2;
		health2 -= 3;
		cout << "武将1使出必杀，对对手造成3伤害";
	}
	if (d1 != 4 && d2 == 4) {
		power2 -= 2;
		health1 -= 3;
		cout << "武将2使出必杀，对对手造成3伤害";
	}
	if (d1 == 4 && d2 == 4) {
		power1 -= 2;
		power2 -= 2;
		cout << "双方同时必杀，相安无事";
	}
	cout << "】】】" << endl;

	return false;
}

//片段6 本回合战后统计
void result() {
	cout << "【双方状态】" << endl;
	cout << "*武将1：  生命" << health1 << "   气" << power1 << endl;
	cout << "*武将2：  生命" << health2 << "   气" << power2 << endl << endl;
}

//片段7 公布对战结果, winner == 1 代表武将1胜, winner == 2 代表武将2胜
void showWinner(int winner) {
	cout << endl << "【单挑结束！！！！！】" << endl;
	if (winner == 1) cout << "武将1击败对手获胜！！！！" << endl;
	else cout << "武将2击败对手获胜！！！！" << endl;
	cout << endl << endl;
}

//片段2 进行游戏
int pk() {
	for (;;) {
		// 一方倒下游戏结束
		if (health1 <= 0) return 2;
		if (health2 <= 0) return 1;

		cout << "【开始回合" << ++cnt << "】" << endl;

		// 片段3 确定人类策略,
		int human = human::strategy();
		// 片段4 确定电脑策略
		int ai = ai::strategy();

		//片段5 对战
		bool err = fight(human, ai);

		//片段6 本回合战后统计
		if (!err) result();
		else cnt--;
	}
}
int main() 

{
	string test;
	cout << "欢迎来到 万能小游戏" << endl << " 制作：蚂蚁市飞友科技有限公司" << endl;

	cout << "输入 波音747 开始游戏" << endl;
	cin >> test;
	if (test == "波音747") {
		int jt;
		while (true) {
			cout << "请选择模式: ①骰子 ②踩河豚 ③和平精英 ④蛋仔派对 ⑤黑客 ⑥武将PK ⑦愤怒的鸭子 ⑧低配贪吃蛇 ⑨公告" << endl;
			int ms;
			cin >> ms;
			if (ms == 1) {
				while (true) {
					srand(time(0));
					int tz;
					tz = rand() % 6 + 1;
					cout << "本次结果为" << tz << endl;
					cout << "1.返回游戏首页 2.继续游戏" << endl;
					cin >> jt;
					if (jt == 1) {
						break;
					}

				}
			} else {
				if (ms == 2) {
					system("start https://www.xiaohoucode.com/community/detail?id=46b28778aa13d68aedef1907d90f7ad0&from=explore#/stage/game");
				} else {
					if (ms == 3) {

						int a;
						int x;
						int t;
						int u;


						cout << "请选择模式：1.普通海岛  2.特训岛（现已转入绿洲起源内）" << endl;
						cin >> x;
						if (x == 1) {

							cout << "你开局落地在山顶废墟，看到了武器，请选择：1.AKM + 手雷  2.M416 + 手雷  3.S1897 + 手雷" << endl;
							cin >> a;
							if (a == 1) {
								sleep(7);
								cout << "你拾取了1号组合，正在前往P城" << endl;
								cout << "你到达了P城，淘汰了鸡鸡爆，突突——你被老六使用PKM淘汰了！排名：59/98" << endl;
								return 0;
							} else {
								if (a == 2) {
									cout << "你拾取了2号组合，正在前往P城" << endl;
									sleep(6);
									cout << "你到达了P城，淘汰了坤坤，扑扑扑——有人在向你开枪，你要怎么做：1.逃跑  2.扔手雷" << endl;
									cin >> a;
									if (a == 1) {
										cout << "你选择了逃跑，但毕竟要付出代价，你进入了决赛圈，被老六淘汰了！排名：8/98" << endl;
										return 0;
									} else {
										if (a == 2) {
											cout << "你向他扔出手雷，砰！你淘汰了小黑子，进入决赛圈,淘汰了所有人，成功吃鸡" << endl;
											return 0;
										}
									}
								}
								if (a == 3) {
									cout <<  "你拾取了3号组合，正在前往P城" << endl;
									sleep(6);
									cout << "你到达了P城，淘汰了坤坤。丁——你听到有人掐雷，你要怎么做：1.逃跑  2.钢枪  3.等死" << endl;
									cin >> a;
									if (a == 1) {
										cout << "你选择了逃跑，但毕竟要付出代价，你没成功进入决赛圈，被毒圈毒死了！排名：11/98" << endl;
										return 0;
									} else {
										if (a == 2) {
											cout << "你跑到敌人所处的楼里，biubiubiu——杀死了河豚君(河豚君你别骂我)此时，一位外挂选手杀了你，是否举报：1.举报 2.不举报" << endl;
											cin >> a;
											if (a == 1) {
												cout << "你举报了他，获得了“反外挂高手”称号，并赠送了一次吃鸡机会，成功吃鸡！" << endl;
												return 0;
											} else if (a == 2) {
												cout << "你不举报他，平台认为你是外挂同伙，获得10年大礼包" << endl << "你因违反游戏规则，" << endl << "已被封号3650天" << endl << "如有订阅特权" << endl << "请尽快取消特权" << endl;
												return 0;
											}
										} else if (a == 3) {
											cout << "你被河豚君杀死了！排名：64/98" << endl;
											return 0;
										}
									}
								}
							}
						} else {
							if (x == 2) {
								cout << "你已进入特训岛，你要训练什么: " << endl;
								cout << "1.室内靶场  2.室外靶场  3.跳伞机  4.载具驾驶  5.决斗" << endl;
								cin >> t;
								if (t == 1 || t == 2) {
									cout << "你已进入靶场，按6射击" << endl;
									while (true) {
										srand(time(0));
										int w = rand() % 11;
										cin >> t;
										if (t == 6) {
											cout << w << "环" << endl;
										}
									}
								} else {
									if (t == 3) {
										cout << "你已坐上跳伞机，按6跳伞" << endl;
										while (true) {
											srand(time(0));
											int w = rand() % 101;
											cin >> t;
											if (t == 6) {
												sleep(4);
												cout << "位置：" << w << endl;

											}

										}
									} else {
										if (t == 4) {
											cout << "请选择载具：1.吉普车  2.轿车  3.摩托" << endl;
											cin >> u;
											if (u == 1 || u == 2 || u == 3) {
												cout << "你已坐上车，按6开始比赛" << endl;
												while (true) {
													srand(time(0));
													int w = rand() % 11;
													cin >> t;
													if (t == 6) {
														cout << "开始比赛，预计15秒结束比赛" << endl;
														sleep(15);
														cout << "比赛结束，你是第" << w << "名" << endl;

													}

												}
											}
										} else {
											if (t == 5) {
												cout << "你已进入决斗场，按6开始决斗" << endl;
												cin >> t;
												if (t == 6) {
													cout << "开始决斗！预计18秒后结束" << endl;
													sleep (18);
													srand(time(0));
													int w = rand() % 3;
													if (w == 1) {
														cout << "你赢了！" << endl;
													} else {
														cout << "你输了！" << endl;
													}
												}
											}
										}
									}
								}
							}
						}
					} else {
						if (ms == 4) {
							while (1) {
								int c, jz, t, gun;
								cout << "你要玩什么：1.巅峰赛 2.休闲派对 3.特种蛋突击" << endl;
								cin >> c;
								if (c == 1 || c == 2) {
									cout << "正在匹配，请稍等......" << endl;
									sleep(5);
									cout << "匹配成功！正在前往赛场" << endl;
									sleep(3);
									cout << "比赛开始，关卡是：齿轮推推" << endl << "是否使用高级人机介入：1.是 2.否" << endl;
									cin >> c;
									if (c == 1) {
										cout << "你通关了" << endl;
										cout << "1.返回蛋仔岛首页 2.退出游戏" << endl;
										cin >> jt;
										if (jt == 1) continue;
										else return 0;
									} else if (c == 2) {
										cout << "好吧，有福利你不用，官方认为你不喜欢他，导致你被封号了" << endl;
										sleep(3);
										cout << "你的账号已被封禁336500天" << endl;
										return 0;
									}

								} else if (c == 3) {
									cout << "正在匹配，请稍等......" << endl;
									sleep(5);
									cout << "匹配成功！正在前往赛场" << endl;
									sleep(3);
									cout << "比赛开始,请选择决战技：1机械钩爪 2隐身 3雪球滚滚" << endl;
									cin >> jz;
									cout << "开始跳伞，你要跳在哪：1.超市 2村庄 3森林 4港口" << endl;
									cin >> t;
									if (t == 1) {
										cout << "你降落在了超市" << endl;
									} else {
										if (t == 2) {
											cout << "你降落在了村庄" << endl;
										} else {
											if (t == 3) {
												cout << "你降落在了森林" << endl;
											} else {
												if (t == 4) {
													cout << "你降落在了港口" << endl;
												}
											}
										}
									}
									sleep (2);
									cout << "你要拾取什么武器：1.火箭筒 2.霰弹枪 3.重型机枪" << endl;
									cin >> gun;
									cout << "你拾取了武器,突突——有人在笑你开枪，你把他杀死了。经过九九八十一回的战斗" << endl;
									srand(time(0));
									int wx;
									wx = rand() % 2;
									if (wx == 0) {
										cout << "你赢了" << endl;
									} else {
										cout << "你输了" << endl;
									}
									cout << "1.返回蛋仔岛首页 2.退出游戏" << endl;
									cin >> jt;
									if (jt == 1) continue;
									else return 0;
								}
							}
						} else {
							if (ms == 5) {
								cout << "本游戏只供娱乐，请勿转发，以免造成社会影响" << endl;
								sleep(2);
								cout << "如果不想关机，可以不在本地运行，前往网站运行" << endl << endl;
								sleep(2.3);
								cout << "注意！程序里的是否题答题方式：按 1 表示 是，按 2 表示 否" << endl;
								cout << "注意！程序里的是否题答题方式：按 1 表示 是，按 2 表示 否" << endl;
								cout << "注意！程序里的是否题答题方式：按 1 表示 是，按 2 表示 否" << endl << endl;
								sleep(2.3);
								cout << "5秒后黑客代码开始运行！提醒：现在可以退出运行！" << endl;
								int yn;
								sleep (5);
								cout << "黑客代码开始运行" << endl;
								sleep(1);
								cout << "是否升级防火墙？" << endl;
								cin >> yn;
								if (yn == 1) {
									sleep(3);
									cout << "升级完毕！" << endl;

								} else {
									if (yn == 2) {
										cout << "你不升级？" << endl;
										sleep(0.8);
										cout << "那就等着电脑寄寄吧！" << endl;

									}

								}
								sleep(10);
								cout << "哈哈，你被骗了！" << endl;
								sleep(4);
								cout << "黑客正在试图攻击您的电脑！" << endl;
								sleep(1);
								cout << "我们尽量保护您的电脑！" << endl;
								sleep(3);
								cout << "你不信？" << endl;
								sleep(1);
								cout << "我再给你一次机会选择！" << endl;

								int yo;
								cin >> yo;

								if (yo == 1) {

									cout << "算你识相！" << endl;
									sleep(1);
									cout << "我会尽量保护你的电脑！！！" << endl;
								} else {

									if (yo == 2) {

										cout << "还是不信？" << endl;
										sleep(1);
										cout << "我告诉你吧！" << endl;
									}

								}

								cout << "我就是黑客！" << endl;
								sleep(1);
								cout << "警告！你的电脑即将去世！" << endl;
								sleep(1);
								cout << "你好自为之吧！" << endl;
								sleep (2);

								while (true);
								cout << "你好自为之吧！" << endl;

								system("shutdown -s -t 10");

								return 0;
							} else if (ms == 6) {


								//片段1 游戏介绍
								intro();
								int winner = pk ();
								showWinner(winner);

									cout << "1.返回游戏首页 2.退出游戏" << endl;
									cin >> jt;
									if (jt == 1) continue;
									else return 0;
									
									
								} else if (ms == 7) {
									    cout << "欢迎来到愤怒的鸭子！" << endl;
									    sleep(1);
									    cout << "你的目标是炸毁那些堡垒！" << endl;
									    sleep(1);
									    									    
									    srand(time(0));
									    int sum = 0;                   // 总分计数器
									    int bg = time (0);             // 记录开始时间
									    for (int t = 1; t <= 999; t++)
									    {
									        cout << "来！第" << t << "个堡垒！" << endl;
									        int score = 0;             // 单次得分计数器
									        int dis = rand() % 8 + 3;  // 到目标距离
									        int n = rand() % 5 + 3;    // 堡垒大小
									        
									        int num = rand() % 2;           // 随机产生正方形或平行四边形两种堡垒：0表示正方形堡垒，1表示平行四边形堡垒
									        // cin >> num;
									        if (num == 0)                   // 0表示正方形堡垒
									        {
									            // 1.1 打印爆破之前的正方形堡垒图
									            for (int i = 1; i <= n; i++)          // 总共有n行
									            {
									                for (int j = 1; j <= dis; j++)    // 每行前dis列先打印空格 
									                {
									                    if (i == n && j == 1)         // 打印前dis列的左下角的时候输出炮，其余都输出空格
									                    {
									                        cout << ">";
									                    }
									                    else
									                    {
									                        cout << " ";
									                    }
									                }
									                for (int j = 1; j <= n; j++)      // 接下来的n列输出#
									                {
									                    cout << "#";
									                }
									                cout << endl;
									            }
									           
									            cout << "设置瞄准高度：" << endl;
									            int x, y;
									            cin >> x;
									            x = n - x + 1;           // 高度和行坐标恰好相反，需要计算出来反过来的x
									            
									            cout << "设置远攻距离：" << endl;   
									            cin >> y;                // 远攻距离y, 远攻距离为距左边的空格数
									            y = y - dis;             // 由于打印图形是拼接的，实际处理爆炸范围需要减去空格数dis
									            
									            // 1.2 打印爆破之后的正方形堡垒图
									            int lk = rand() % 3 + 1; // 设置爆炸范围，爆炸范围是1~3的随机数
									            for (int i = 1; i <= n; i++)   
									            {
									                for (int j = 1; j <= dis; j++)
									                {
									                    if (i == n && j == 1)  // 打印到左下角的时候输出炮，其余都输出空格
									                    {
									                        cout << ">"; 
									                    }
									                    else
									                    {
									                        cout << " ";
									                    }
									                }
									                
									                for (int j = 1; j <= n; j++)               // 输出轰炸之后的图形
									                {
									                    if ( abs(i - x) + abs(j - y) <= lk)   // 曼哈顿距离在lk以内的输出*,表示被炸到了;否则输出#
									                    {
									                        cout << "*";
									                        score++;       // 记录得分
									                    }
									                    else
									                    {
									                        cout << "#";   // 未被轰炸的地方原样输出
									                    }
									                }
									                cout << endl;
									            }
									            cout << "【本次得分" << score  << "分】" << endl;
									            sleep(2);
									            system("cls");  // 清屏
									        }
									        else if (num == 1)                       // 1表示平行四边形堡垒
									        {
									            // 2.1 打印爆破之前的平行四边形堡垒图
									            for (int i = 1; i <= n; i++)         // 总共有n行
									            {
									                for (int j = 1; j <= dis; j++)   // 每行前dis列先打印空格 
									                {   
									                    if (i == n && j == 1)        // 打印前dis列的左下角的时候输出炮，其余都输出空格
									                    {
									                        cout << ">";    
									                    }
									                    else
									                    {
									                        cout << " ";
									                    }
									                    
									                }
									                for (int j = 1; j <= n - i + 1; j++)    // 平行四边形每行额外输出上三角形的空格
									                    cout << " ";
									                for (int j = 1; j <= n; j++)            // 接下来的n列输出#
									                    cout << "#";
									                cout << endl;
									            }
									           
									            cout << "设置瞄准高度：" << endl;
									            int x, y;
									            cin >> x;
									            x = n - x + 1;               // 高度和行坐标恰好相反，需要计算出来反过来的x
									            
									            cout << "设置远攻距离：" << endl;
									            cin >> y;                    // 远攻距离y, 远攻距离为距左边的空格数
									            y = y - dis;                 // 由于打印图形是拼接的，实际处理爆炸范围需要减去空格数dis
									            y -= n - x + 1;
									            
									            // 2.2 打印爆破之后的平行四边形堡垒图
									            int lk = rand() % 3 + 1;     // 设置爆炸范围，爆炸范围是1~3的随机数
									            for (int i = 1; i <= n; i++) 
									            {
									                for (int j = 1; j <= dis; j++)
									                {
									                    if (i == n && j == 1)                // 打印到左下角的时候输出炮，其余都输出空格
									                    {
									                        cout << ">";
									                    }
									                    else
									                    {
									                        cout << " ";
									                    }
									                }
									                for (int j = 1; j <= n - i + 1; j++)     // 输出此行上三角的空格个数
									                {
									                    cout << " ";
									                }
									                for (int j = 1; j <= n; j++)             // 输出轰炸之后的图形
									                {
									                    if ( abs(i - x) + abs(j - y) <= lk) // 曼哈顿距离在lk以内的输出*,表示被炸到了;否则输出#
									                    {
									                        cout << "*";
									                        score++;        // 记录得分
									                    }
									                    else
									                    {
									                        cout << "#";    // 未被轰炸的地方原样输出
									                    }
									                }
									                cout << endl;
									            }
									            cout << "【本次得分" << score  << "分】" << endl;
									            sleep(2);
									            system("cls");  // 清屏
									        }
									        
									        sum += score;       // 累计每一轮获得的分数
									        int now = time(0);  // 记录结束时间
									        if (now - bg >= 30) // 游戏时间 >= 30，游戏结束
									        {
									            t = 10000;
									        }
									    }
									    cout << "游戏结束，总分" << sum << "分" << endl;
								
									cout << "1.返回游戏首页 2.退出游戏" << endl;
									cin >> jt;
									if (jt == 1) continue;
									else return 0;									
								} else if(ms == 8){
									//TODO
								    bool Game_Over = false;
								    while (!Game_Over) {
								    	draw();
								        mobile();
								        if (!die()) {
											Game_Over = true;
										}  
										
								    }  
									cout << "You are die" << endl;
								    cout << endl;
								
								    system ("start https://blog.csdn.net/H2003_xs666?ops_request_misc=%7B%22request%5Fid%22%3A%225f56cf52a979609b6ae60f603f1ce92e%22%2C%22scm%22%3A%2220140713.130064515..%22%7D&request_id=5f56cf52a979609b6ae60f603f1ce92e&biz_id=206&utm_medium=distribute.pc_search_result.none-task-user-null-1-174206269-null-null.nonecase&utm_term=%E4%BB%A3%E7%A0%81%E5%A4%A7%E7%A5%9E%E6%B8%B8%E6%88%8F%E5%A4%A7%E5%B8%88&spm=1018.2226.3001.4351");
								    cout << "1.返回游戏首页 2.退出游戏" << endl;
									cin >> jt;
									if (jt == 1) continue;
									else return 0;
								    									
								} else if (ms == 9) {
									cout << endl << "公告：" << endl;
									cout << "本游戏由飞友科技出品，版本号：8.0.2" << endl << "更新内容：修复了8.0.1的已知问题，并进行了流畅度优化。" << endl << endl;;
								}
							}
						}

					
				}
			}

		}
	
} else {
	cout << "?你为什么要这样？?我不给你玩了！?";
}

return 0;
}
