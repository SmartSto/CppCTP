//
// Created by quant on 6/7/16.
//

#ifndef QUANT_CTP_MDSPI_H
#define QUANT_CTP_MDSPI_H

#include <map>
#include <string>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <list>
#include "ThostFtdcMdApi.h"
#include "ThostFtdcUserApiStruct.h"
#include "User.h"
#include "Strategy.h"
#include "CTP_Manager.h"


using std::map;
using std::string;

class CTP_Manager;
class Strategy;

class MdSpi :public CThostFtdcMdSpi{

public:
    MdSpi(CThostFtdcMdApi *mdapi);
	//建立连接
	void Connect(char *frontAddress);
    //建立连接时触发
    void OnFrontConnected();
	//等待线程结束
	void Join();
	//增加毫秒
	void timeraddMS(struct timeval *a, int ms);
	//协程控制
	//int controlTimeOut(sem_t *t, int timeout = 5000);
	//登录
	void Login(char *BrokerID, char *UserID, char *Password);
    ///登录请求响应
    void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo,
                        int nRequestID, bool bIsLast);
	//登出
	void Logout(char *BrokerID, char *UserID);
    ///登出请求响应
    void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///订阅行情
	void SubMarket(list<string> *l_instrument);

	///取消订阅行情
	void UnSubMarket(list<string> *l_instrument);

    ///订阅行情应答
    void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///取消订阅行情应答
    void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

    ///深度行情通知
    void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);
	void CopyTickData(CThostFtdcDepthMarketDataField *dst, CThostFtdcDepthMarketDataField *src);

	//通信断开
	void OnFrontDisconnected(int nReason);

	//返回数据是否报错
	bool IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo);

	//订阅行情
	void SubMarketData(char *ppInstrumentID[], int nCount);

	//取消订阅行情
	void UnSubscribeMarketData(char *ppInstrumentID[], int nCount);

	//得到BrokerID
	string getBrokerID();

	//得到UserID
	string getUserID();

	//得到Password
	string getPassword();

	//添加strategy
	void addStrategyToList(Strategy *stg);

	/// 得到strategy_list
	list<Strategy *> *getListStrategy();

	/// 设置strategy_list
	void setListStrategy(list<Strategy *> *l_strategys);

	void setCtpManager(CTP_Manager *ctp_m);
	CTP_Manager *getCtpManager();

private:
    CThostFtdcMdApi *mdapi;
    CThostFtdcReqUserLoginField *loginField;
	CThostFtdcUserLogoutField *logoutField;
    int loginRequestID;
	bool isLogged;
	bool isFirstTimeLogged;
	char **ppInstrumentID;
	int nCount;
	string BrokerID;
	string UserID;
	string Password;
	/*sem_t connect_sem;
	sem_t login_sem;
	sem_t logout_sem;
	sem_t submarket_sem;
	sem_t unsubmarket_sem;*/
	list<Strategy *> *l_strategys;
	CTP_Manager *ctp_m;
	CThostFtdcDepthMarketDataField *last_tick_data;
};
#endif //QUANT_CTP_MDSPI_H
