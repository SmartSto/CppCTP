#ifndef QUANT_USER_H
#define QUANT_USER_H

#include <iostream>
#include <string>
#include <cstring>
#include <mongo/client/dbclient.h>
#include "ThostFtdcTraderApi.h"
#include "TdSpi.h"
#include "DBManager.h"
#include "Order.h"
#include "Trader.h"
#include "Strategy.h"

using namespace mongo;
using namespace std;
using std::string;
using mongo::DBClientConnection;
using mongo::BSONObjBuilder;

class User
{
public:
	User(string frontAddress, string BrokerID, string UserID, string Password, string nRequestID, string TraderID = "");
	User(string BrokerID, string UserID, int nRequestID);
	~User();
	string getBrokerID();
	string getUserID();
	string getPassword();
	int getRequestID();
	bool getIsLogged();
	bool getIsFirstTimeLogged();
	bool getIsConfirmSettlement();
	int getLoginRequestID();
	CThostFtdcTraderApi *getUserTradeAPI();
	class TdSpi *getUserTradeSPI();
	string getFrontAddress();

	void setBrokerID(string BrokerID);
	void setUserID(string UserID);
	void setPassword(string Password);
	void setRequestID(int nRequestID);
	void setIsLogged(bool isLogged);
	void setIsFirstTimeLogged(bool isFirstTimeLogged);
	void setIsConfirmSettlement(bool isConfirmSettlement);
	void setLoginRequestID(int loginRequestID);
	void setUserTradeAPI(CThostFtdcTraderApi *UserTradeAPI);
	void setUserTradeSPI(TdSpi *UserTradeSPI);
	void setFrontAddress(string frontAddress);
	Trader *GetTrader();
	void setTrader(Trader *trader);
	string getTraderID();
	void setTraderID(string TraderID);

	/// �õ�strategy_list
	list<Strategy *> *getListStrategy();
	/// ����strategy_list
	void setListStrategy(list<Strategy *> *l_strategys);
	/// ���strategy��list
	void addStrategyToList(Strategy *stg);

	/************************************************************************/
	/* ��ȡ���ݿ�����                                                         */
	/************************************************************************/
	mongo::DBClientConnection * GetPositionConn();
	mongo::DBClientConnection * GetTradeConn();
	mongo::DBClientConnection * GetOrderConn();


	/************************************************************************/
	/* ���Order��MongoDB����                                                 */
	/************************************************************************/
	void DB_OrderInsert(mongo::DBClientConnection *conn, CThostFtdcInputOrderField *pInputOrder);
	void DB_OnRtnOrder(mongo::DBClientConnection *conn, CThostFtdcOrderField *pOrder);
	void DB_OnRtnTrade(mongo::DBClientConnection *conn, CThostFtdcTradeField *pTrade);
	void DB_OrderAction(mongo::DBClientConnection *conn, CThostFtdcInputOrderActionField *pOrderAction);
	void DB_OrderCombine(mongo::DBClientConnection *conn, CThostFtdcOrderField *pOrder);
	void DB_OnRspOrderAction(mongo::DBClientConnection *conn, CThostFtdcInputOrderActionField *pInputOrderAction); // CTP��Ϊ������������
	void DB_OnErrRtnOrderAction(mongo::DBClientConnection *conn, CThostFtdcOrderActionField *pOrderAction); // ��������Ϊ��������
	void DB_OnRspOrderInsert(mongo::DBClientConnection *conn, CThostFtdcInputOrderField *pInputOrder); // CTP��Ϊ������������
	void DB_OnErrRtnOrderInsert(mongo::DBClientConnection *conn, CThostFtdcInputOrderField *pInputOrder); // ��������Ϊ��������
	void DB_OnRspQryInvestorPosition(mongo::DBClientConnection *conn, CThostFtdcInvestorPositionField *pInvestorPosition); // �ֲ���Ϣ

private:
	string BrokerID;
	string UserID;
	string Password;
	string frontAddress;
	int nRequestID;
	bool isLogged;
	bool isFirstTimeLogged;
	bool isConfirmSettlement;
	int loginRequestID;
	string TraderID;
	CThostFtdcTraderApi *UserTradeAPI;
	TdSpi *UserTradeSPI;
	Trader *trader;
	list<Strategy *> *l_strategys;
	mongo::DBClientConnection * PositionConn;
	mongo::DBClientConnection * TradeConn;
	mongo::DBClientConnection * OrderConn;
};

#endif