#include <iostream>
#include <string>
#include <list>
#include <mongo/client/dbclient.h>
#include <stdio.h>

/*socket头文件*/
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#include <arpa/inet.h>  // inet_ntoa
#include <spdlog/spdlog.h>

#include "ThostFtdcTraderApi.h"
#include "TdSpi.h"
#include "CTP_Manager.h"
#include "Utils.h"
#include "Debug.h"
#include "DBManager.h"
#include "Trader.h"
#include "FutureAccount.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "msg.h"
#include "Timer.h"

using std::cout;
using std::cin;
using namespace rapidjson;
using namespace spdlog;
using spdlog::logger;

/*宏定义*/
#define MAXCONNECTIONS 100
#define MAX_BUFFER_SIZE	80*1024

int sockfd;
CTP_Manager *ctp_m = NULL;
std::shared_ptr<spdlog::logger> xts_logger = NULL;

string one_min_time = "14:50:00";
string one_sec_time = "14:58:00";
string stop_trading_time = "14:59:55";
string close_time = "15:00:00";
string stopsave_time = "15:00:02";
string stop_start_from_today_position_time = "20:00:00";


string morning_open_time = "08:59:55"; // 早上开盘时间
string moring_break_time = "10:14:55"; // 中午休盘
string morning_continue_time = "10:29:55"; // 中午休盘结束时间
string morning_close_time = "11:29:55"; // 中午收盘
string afternoon_open_time = "13:29:55"; // 下午开盘
string afternoon_close_time = "14:59:50"; // 下午收盘(停止新的发单任务)
string afternoon_end_task_time_one_time = "14:59:55"; // 下午收盘(把挂单列表全部成交)
string afternoon_end_task_time_second_time = "14:59:56"; // 下午收盘(把挂单列表全部成交)
string afternoon_end_task_time_third_time = "14:59:58"; // 下午收盘(把挂单列表全部成交)
string night_open_time = "20:59:55"; // 夜盘开始
string night_day_time = "00:00:00"; // 凌晨12点
string night_start_close_time = "02:29:55"; // 夜盘准备收盘,停止新的交易任务
string night_close_time = "02:30:00"; // 夜盘收盘时间
string night_stop_save_time = "02:30:02"; // 夜盘存储数据时间

/*信号处理*/
void sig_handler(int signo) {

	std::cout << "main.cpp sig_handler()" << std::endl;

	if (signo == SIGINT) {
		printf("main.cpp sig_handler()\n");

		if (ctp_m) {

			bool isTrading = false;

			//list<Strategy *>::iterator stg_itor;
			//for (stg_itor = ctp_m->getListStrategy()->begin();
			//	stg_itor != ctp_m->getListStrategy()->end(); stg_itor++) { // 遍历ctp_m维护的Strategy List
			//	if ((*stg_itor)->isStgTradeTasking()) {
			//		std::cout << "\t\033[31m策略(" << (*stg_itor)->getStgUserId() << ", " << (*stg_itor)->getStgStrategyId() << ") 处于交易状态\033[0m" << std::endl;
			//		/// 一旦有策略仍然在交易中,跳出循环
			//		isTrading = true;
			//		break;
			//	}
			//}

			if (!isTrading) { // 如果策略全部处于非交易状态,则可以进行关闭
				if (!ctp_m->getCTPFinishedPositionInit()) { // ctp_m未初始化成功，则不做保存工作
					printf("\t\033[31m服务端 未 完成初始化!!!\033[0m\n");
				}
				else {
					printf("\t\033[32m服务端正常关闭，开始保存策略持仓明细.\033[0m\n");
					ctp_m->saveAllStrategyPositionDetail();

				}
				///// 刷新log
				//ctp_m->getXtsLogger()->flush();
				/// 正常关闭,更新标志位
				ctp_m->updateSystemFlag();
				/// 关闭所有的log
				spdlog::drop_all();
				close(sockfd);
				exit(1);
			}
			else {
				printf("\t\033[31m服务端 有 策略处于交易状态,稍后再试!!!\033[0m\n");
			}
		}
		else {
			printf("\t\033[31m服务端 未 正常关闭!!!\033[0m\n");
			close(sockfd);
			exit(1);
		}
	}
}

/*输出连接上来的客户端的相关信息*/
void out_addr(struct sockaddr_in *clientaddr) {
	//将端口从网络字节序转换成主机字节序
	int port = ntohs(clientaddr->sin_port);
	char ip[16];
	memset(ip, 0, sizeof(ip));
	//将ip地址从网络字节序转换成点分十进制
	inet_ntop(AF_INET, &clientaddr->sin_addr.s_addr, ip, sizeof(ip));
	printf("client: %s(%d) connected\n", ip, port);
}

/*输出服务器端时间*/
void do_service(int fd) {
	printf("main.cpp do_service()");
	/*和客户端进行读写操作(双向通信)*/
	char buff[MAX_BUFFER_SIZE];
	printf("\t服务端开始监听...\n");
	while (1)
	{
		memset(buff, 0, sizeof(buff));

		size_t size;
		//printf("sizeof buff is %d = \n", sizeof(buff));
		if ((size = read_msg(fd, buff, sizeof(buff))) < 0) {
			printf("protocal error");
			break;
		}
		else if (size == 0) {
			break;
		}
		else {
			//printf("服务端收到 = %s\n", buff);
			CTP_Manager::HandleMessage(fd, buff, ctp_m);
			//printf("socket_server send size = %d \n", strlen(buff));
			//printf("socket_server fd = %d \n", fd);
			//printf("socket_server send size = %d \n", sizeof(buff));
			//printf("socket_server send size = %d \n", strlen(buff));
			//if (write_msg(fd, buff, sizeof(buff)) < 0) {
			//	printf("先前客户端已断开!!!\n");
			//	//printf("errorno = %d, 先前客户端已断开!!!\n", errno);
			//	if (errno == EPIPE) {
			//		break;
			//	}
			//	perror("protocal error");
			//}
		}
	}
}

/*输出文件描述符*/
void out_fd(int fd) {
	printf("main.cpp out_fd()");
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	//从fd中获取连接的客户端相关信息
	if (getpeername(fd, (struct sockaddr *)&addr, &len) < 0) {
		perror("getpeername error");
		return;
	}
	char ip[16];
	memset(ip, 0, sizeof(ip));
	int port = ntohs(addr.sin_port);
	inet_ntop(AF_INET, &addr.sin_addr.s_addr, ip, sizeof(ip));
	printf("\t来自ip地址:%16s(%5d) 已连接!!!\n", ip, port);
}

/*线程调用*/
void *th_fn(void *arg) {
	int fd = *(reinterpret_cast<int*>(arg));
	out_fd(fd);
	do_service(fd);
	close(fd);
	return (void *)0;
}

void timer_handler() {

	/*time_t tt = system_clock::to_time_t(system_clock::now()); 
	std::string nowt(std::ctime(&tt));*/
	//std::cout << "main.cpp timer_handler()" << std::endl;
	//std::cout << "\t定时器输出" << std::endl;
	//std::cout << "\t现在时间:" << nowt.substr(0, nowt.length() - 1) << std::endl;


	/************************************************************************/
	/*	string one_min_time = "14：50：00";
		string one_sec_time = "14：58：00";
		string stop_trading_time = "14：59：55";
		string close_time = "15：00：00";
		时间在14:49:00之前，按照10分钟一次计时
		一旦时间超过14：50：00，我就按照一分钟计时一次；
		一旦时间超过14：59：00，我就按照1秒计时一次；
		一旦时间超过14：59：55，不开始新的交易任务。
		*/
	/************************************************************************/
	/************************************************************************/
	/*	string morning_open_time = "08:59:55"; // 早上开盘时间
		string moring_break_time = "10:14:55"; // 中午休盘
		string morning_continue_time = "10:29:55"; // 中午休盘结束时间
		string morning_close_time =	"11:29:55"; // 中午收盘
		string afternoon_open_time = "13:29:55"; // 下午开盘
		string afternoon_close_time = "14:59:55"; // 下午收盘
		string night_open_time = "20:59:55"; // 夜盘开始
		string night_close_time = "22:59:55"; //夜盘收盘                                                                    */
	/************************************************************************/

	// 默认是休盘
	bool market_close_flag = true;
	// 15:00:00是否需要执行收盘工作
	bool is_need_save_data_afternoon = false;
	// 是否需要停止计时器
	bool is_need_to_stop_timer = false;
	string nowtime = Utils::getNowTime();
	string ymd_date = Utils::getYMDDate();
	//std::cout << "现在时间 = " << nowtime << std::endl;
	if (ctp_m->getCalTimer()->running()) //定时器在运行中
	{
		//std::cout << "\t开始比较，现在时间 = " << nowtime << std::endl;
		ctp_m->setIsStartEndTask(false);

		//时间大于早上开盘时间
		if (Utils::compareTradingDaySeconds(nowtime.c_str(), (ymd_date + morning_open_time).c_str())) {
			market_close_flag = false;

			//时间大于中午休盘
			if (Utils::compareTradingDaySeconds(nowtime.c_str(), (ymd_date + moring_break_time).c_str()))
			{
				market_close_flag = true;

				//时间大于中午休盘结束时间
				if (Utils::compareTradingDaySeconds(nowtime.c_str(), (ymd_date + morning_continue_time).c_str()))
				{
					market_close_flag = false;

					//时间大于中午收盘
					if (Utils::compareTradingDaySeconds(nowtime.c_str(), (ymd_date + morning_close_time).c_str()))
					{
						market_close_flag = true;

						// 时间大于13:29:55
						if (Utils::compareTradingDaySeconds(nowtime.c_str(), (ymd_date + afternoon_open_time).c_str()))
						{
							market_close_flag = false;

							// 时间大于14:59:50
							if (Utils::compareTradingDaySeconds(nowtime.c_str(), (ymd_date + afternoon_close_time).c_str()))
							{
								market_close_flag = true;

								// 时间大于14:59:55
								if (Utils::compareTradingDaySeconds(nowtime.c_str(), (ymd_date + afternoon_end_task_time_one_time).c_str())) {
									
									market_close_flag = true;
									ctp_m->setIsStartEndTask(true);
									ctp_m->StrategyIsStartEndTask();

									// 时间大于14:59:56
									if (Utils::compareTradingDaySeconds(nowtime.c_str(), (ymd_date + afternoon_end_task_time_second_time).c_str()))
									{
										market_close_flag = true;
										ctp_m->setIsStartEndTask(false);

										// 时间大于14:59:58
										if (Utils::compareTradingDaySeconds(nowtime.c_str(), (ymd_date + afternoon_end_task_time_third_time).c_str()))
										{
											market_close_flag = true;
											ctp_m->setIsStartEndTask(true);
											ctp_m->StrategyIsStartEndTask();

											// 时间大于15:00:00
											if (Utils::compareTradingDaySeconds(nowtime.c_str(), (ymd_date + close_time).c_str())) { // 时间大于15:00:00
												market_close_flag = true;
												is_need_save_data_afternoon = true;
												// 超过下午3点就不需要处理挂单列表
												ctp_m->setIsStartEndTask(false);

												// 时间大于15:00:02
												if (Utils::compareTradingDaySeconds(nowtime.c_str(), (ymd_date + stopsave_time).c_str())) { // 时间大于15:00:00小于15:00:02
													market_close_flag = true;
													is_need_save_data_afternoon = false;
													ctp_m->setIsMarketCloseDone(true);
													is_need_to_stop_timer = true;

													// 时间大于20:00:00
													if (Utils::compareTradingDaySeconds(nowtime.c_str(), (ymd_date + stop_start_from_today_position_time).c_str())) //时间大于15:00:02小于18:00:00
													{
														ctp_m->setIsMarketCloseDone(false);
														market_close_flag = true;
														is_need_save_data_afternoon = false;
														is_need_to_stop_timer = false;

														//时间大于20:59:55
														if (Utils::compareTradingDaySeconds(nowtime.c_str(), (ymd_date + night_open_time).c_str())) { // 时间大于20:59:55

															market_close_flag = false;
															is_need_save_data_afternoon = false;
															is_need_to_stop_timer = false;
														}
														else {
															//std::cout << "\t现在时间:" << nowtime << std::endl;
															//std::cout << "\t非盘中交易时间." << std::endl;
															market_close_flag = true;
														}
													}
												}
											}

										}
									}
								}
							}
						}
					}
				}
			}
		} else {
			// 时间大于00:00:00
			if (Utils::compareTradingDaySeconds(nowtime.c_str(), (ymd_date + night_day_time).c_str()))
			{
				is_need_save_data_afternoon = false;
				market_close_flag = false;
				is_need_to_stop_timer = false;

				// 时间大于02:29:55
				if (Utils::compareTradingDaySeconds(nowtime.c_str(), (ymd_date + night_start_close_time).c_str()))
				{
					is_need_save_data_afternoon = false;
					market_close_flag = true;
					is_need_to_stop_timer = false;

					// 时间大于02:30:00
					if (Utils::compareTradingDaySeconds(nowtime.c_str(), (ymd_date + night_close_time).c_str()))
					{
						is_need_save_data_afternoon = true;
						market_close_flag = true;
						is_need_to_stop_timer = false;

						// 时间大于02:30:02
						if (Utils::compareTradingDaySeconds(nowtime.c_str(), (ymd_date + night_stop_save_time).c_str()))
						{
							is_need_save_data_afternoon = false;
							market_close_flag = true;
							is_need_to_stop_timer = false;
						}
					}

				}

			}
			else {
				market_close_flag = true;
			}
		}
	}

	if (ctp_m->getIsMarketClose() != market_close_flag)
	{
		Utils::printGreenColorWithKV("timer_handler() 现在时间:", nowtime);
		ctp_m->setIsMarketClose(market_close_flag);
	}

	// 是否需要停止定时器
	if (is_need_to_stop_timer)
	{
		Utils::printGreenColorWithKV("现在时间", nowtime);
		ctp_m->getCalTimer()->stop();
		Utils::printGreenColor("已关闭定时器!");
	}

	// 是否需要保存数据
	if (is_need_save_data_afternoon)
	{
		Utils::printGreenColorWithKV("现在时间", nowtime);
		Utils::printGreenColor("收盘工作:保存策略参数,更新运行状态.");

		// 保存最后策略参数,更新运行状态正常收盘
		ctp_m->saveAllStrategyPositionDetail();
		ctp_m->updateSystemFlag();

		// 保存策略参数,关闭定时器
		//ctp_m->getCalTimer()->stop();
		Utils::printGreenColor("系统收盘工作正常结束.");
	}

#if 0
	if (ctp_m->getCalTimer()->running()) {

		string nowtime = Utils::getNowTime();
		//std::cout << "\t开始比较，现在时间 = " << nowtime << std::endl;
		
		if (Utils::compareTradingDaySeconds(nowtime.c_str(), (ctp_m->getTradingDay() + one_min_time).c_str())) { // 时间大于14：50：00

			if (Utils::compareTradingDaySeconds(nowtime.c_str(), (ctp_m->getTradingDay() + one_sec_time).c_str())) { // 时间大于14:58:00
				
				if (Utils::compareTradingDaySeconds(nowtime.c_str(), (ctp_m->getTradingDay() + stop_trading_time).c_str())) { // 时间大于14:59:55
					//关闭任务开关,防止刷单

					if (Utils::compareTradingDaySeconds(nowtime.c_str(), (ctp_m->getTradingDay() + close_time).c_str())) { // 时间大于15:00:00
						
						if (Utils::compareTradingDaySeconds(nowtime.c_str(), (ctp_m->getTradingDay() + stopsave_time).c_str())) { // 时间大于15:01:00
							ctp_m->getCalTimer()->stop();
						}
						else { // 时间大于15:00:00小于15:01:00
							std::cout << "\t\033[32m收盘工作:保存策略参数,更新运行状态,停止计时器.\033[0m" << std::endl;

							// 保存最后策略参数,更新运行状态正常收盘
							//ctp_m->saveStrategy();

							ctp_m->saveAllStrategyPositionDetail();
							ctp_m->updateSystemFlag();

							// 保存策略参数,关闭定时器
							ctp_m->getCalTimer()->stop();
							std::cout << "\t\033[32m系统收盘工作正常结束.\033[0m" << std::endl;
						}
					}

				} 
				else { // 时间大于14:58:00小于时间小于14:59:55，按照一秒一次计时

					if (!ctp_m->getOneSecondFlag()) {
						std::cout << "\t\033[32m开始进行1秒计时\033[0m" << std::endl;
						ctp_m->getCalTimer()->stop();
						ctp_m->getCalTimer()->setSingleShot(false);
						ctp_m->getCalTimer()->setInterval(Timer::Interval(1000));
						ctp_m->setOneSecondFlag(true);
						ctp_m->getCalTimer()->start();
						
					}
				}

			}
			else { // 时间小于14:58:00,按照1分钟进行一次计时
				if (!ctp_m->getOneMinFlag())
				{
					std::cout << "\t\033[32m开始进行1分钟计时\033[0m" << std::endl;
					ctp_m->getCalTimer()->stop();
					ctp_m->getCalTimer()->setSingleShot(false);
					ctp_m->getCalTimer()->setInterval(Timer::Interval(1000 * 60));
					ctp_m->setOneMinFlag(true);
					ctp_m->getCalTimer()->start();
					
				}
			}
		}
		else { // 时间小于14:50:00,按照10分钟进行一次计时
			if (!ctp_m->getTenMinFlag()) {
				std::cout << "\t\033[32m开始进行10分钟计时\033[0m" << std::endl;
				ctp_m->getCalTimer()->stop();
				ctp_m->getCalTimer()->setSingleShot(false);
				ctp_m->getCalTimer()->setInterval(Timer::Interval(1000 * 60 * 10));
				ctp_m->setTenMinFlag(true);
				ctp_m->getCalTimer()->start();
				
				
			}
		}
	}
#endif
	
}



int main(int argc, char *argv[]) {

	if (argc < 3) {
		printf("usage: %s port mode\n", argv[0]);
		printf("port: 0~65536\n");
		printf("mode: 1:online 0:offline\n");
		exit(1);
	}

	if (signal(SIGINT, sig_handler) == SIG_ERR) { // 按下crtl+c键后的处理
		perror("signal sigint error");
		exit(1);
	}

	signal(SIGPIPE, SIG_IGN);

	// 初始化mongoDB
	mongo::client::initialize();

	// 初始化CTP_Manager
	ctp_m = new CTP_Manager();
	
	bool init_flag = true;

	if (!strcmp("1", argv[2])) {
		init_flag = true;
		//printf("盘中模式... \n");
	}
	else if (!strcmp("0", argv[2])) {
		init_flag = false;
		//printf("离线模式... \n");
	}
	else {
		printf("usage: %s #port #mode\n", argv[0]);
		printf("port: 0~65536\n");
		printf("mode: 1:online 0:offline\n");
		spdlog::drop_all();
		exit(1);
	}

	// 多线程定时器
	/*Timer tHello([]()
	{
		std::cout << "main()" << std::endl;
		std::cout << "\t系统定时器tick" << std::endl;
	});*/

	Timer tHello(timer_handler);

	//CTPManager设置定时器
	ctp_m->setCalTimer(&tHello);


	//开启定时器
	tHello.setSingleShot(false);
	//tHello.setInterval(Timer::Interval(1000 * 60 * 10));
	tHello.setInterval(Timer::Interval(1000));
	tHello.start(true);

	// 程序入口，初始化资源
	if (!ctp_m->init(init_flag)) {
		std::cout << "系统初始化失败!请检查日志!" << std::endl;
		spdlog::drop_all();
		exit(1);
	}

	/*while (true)
	{
	std::cout << "In Thread = " << std::this_thread::get_id() << std::endl;
	sleep(5);
	}*/

	/*算法单元测试
	Algorithm *alg = new Algorithm();
	alg->setAlgName("01");
	ctp_m->getDBManager()->CreateAlgorithm(alg);
	alg->setIsActive("1");
	ctp_m->getDBManager()->UpdateAlgorithm(alg);
	list<Algorithm *> l_alg;
	ctp_m->getDBManager()->getAllAlgorithm(&l_alg);
	list<Algorithm *>::iterator alg_itor;
	for (alg_itor = l_alg.begin(); alg_itor != l_alg.end(); alg_itor++) {

	cout << (*alg_itor)->getAlgName() << endl;
	}*/


	/*步骤1:创建socket(套接字)*/
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	/*socket选项设置*/
	// a：设置套接字的属性使它能够在计算机重启的时候可以再次使用套接字的端口和IP
	int err, sock_reuse = 1;
	err = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &sock_reuse, sizeof(sock_reuse));
	if (err != 0) {
		printf("SO_REUSEADDR Setting Failed!\n");
		spdlog::drop_all();
		exit(1);
	}
	// b：设置接收缓冲区大小
	int nRecvBuf = MAX_BUFFER_SIZE; //数据最大长度
	err = setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBuf, sizeof(int));
	if (err != 0) {
		printf("SO_RCVBUF Setting Failed!\n");
		spdlog::drop_all();
		exit(1);
	}
	// c：设置发送缓冲区大小
	int nSendBuf = MAX_BUFFER_SIZE; //数据最大长度
	err = setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, (const char*)&nSendBuf, sizeof(int));
	if (err != 0) {
		printf("SO_SNDBUF Setting Failed!\n");
		spdlog::drop_all();
		exit(1);
	}

	/*步骤2:将socket和地址(包括ip,port)进行绑定*/
	struct sockaddr_in serveraddr;
	memset(&serveraddr, 0, sizeof(serveraddr));
	/*向地址中填入ip,port,internet地址簇类型*/
	serveraddr.sin_family = AF_INET; //ipv4
	serveraddr.sin_port = htons(atoi(argv[1])); //port
	serveraddr.sin_addr.s_addr = INADDR_ANY; //接收所有网卡地址
	if (bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) {
		perror("bind error");
		spdlog::drop_all();
		exit(1);
	}

	/*步骤3:调用listen函数启动监听(指定port监听)
	通知系统去接受来自客户端的连接请求
	第二个参数:指定队列的长度*/
	if (listen(sockfd, MAXCONNECTIONS) < 0) {
		perror("listen error");
		spdlog::drop_all();
		exit(1);
	}

	/*步骤4:调用accept函数从队列中获得一个客户端的连接请求，
	并返回新的socket描述符*/
	struct sockaddr_in clientaddr;
	socklen_t clientaddr_len = sizeof(clientaddr);

	/*设置线程的分离属性*/
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	std::cout << "\033[32mTrade Server已就绪,等待连接...\033[0m" << std::endl;

	while (1)
	{
		int fd = accept(sockfd, NULL, NULL);
		if (fd < 0) {
			perror("accept error");
			continue;
		}
		/*步骤5:启动子线程去调用IO函数(read/write)和连接的客户端进行双向通信*/
		pthread_t th;
		int err;
		/*以分离状态启动子线程*/
		if ((err = pthread_create(&th, &attr, th_fn, &fd)) != 0) {
			perror("pthread create error");
		}
		pthread_attr_destroy(&attr);
	}

	return 0;
}