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
#include "CTP_Manager.h"
#include "Session.h"

using namespace mongo;
using namespace std;
using std::string;
using mongo::DBClientConnection;
using mongo::BSONObjBuilder;

class CTP_Manager;
class Session;

class User
{
public:
	User(string frontAddress, string BrokerID, string UserID, string Password, string nRequestID, int on_off, string TraderID = "", string stg_order_ref_base = "0");
	User(string BrokerID, string UserID, int nRequestID, string stg_order_ref_base = "0");
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


	/// ��ʼ����Լ��������,����"cu1601":0 "cu1701":0
	void init_instrument_id_action_counter(string instrument_id);

	/// ��ú�Լ��������,����"cu1710":0
	int get_instrument_id_action_counter(string instrument_id);

	/// ��Ӷ�Ӧ��Լ��������������,����"cu1602":1 "cu1701":1
	void add_instrument_id_action_counter(CThostFtdcOrderField *pOrder);

	/// �������û�׼
	void setStgOrderRefBase(long long stg_order_ref_base);
	long long getStgOrderRefBase();

	/// ���ò����ں�Լ��С���۸�
	void setStgInstrumnetPriceTick();

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
	// ���±�������
	void DB_UpdateOrderRef(string order_ref_base);

	/// ���ÿ���
	int getOn_Off();
	void setOn_Off(int on_off);

	/// ����CTP_Manager
	void setCTP_Manager(CTP_Manager *o_ctp);
	CTP_Manager *getCTP_Manager();

	void setIsActive(string isActive);
	string getIsActive();

	void setTradingDay(string stg_trading_day);
	string getTradingDay();

	void QueryTrade();

	void QueryOrder();

	/// �õ����ݿ��������
	DBManager *getDBManager();
	void setDBManager(DBManager *dbm);

	int getSessionID();
	void setSessionID(int sid);

	list<Session *> * getL_Sessions();
	void setL_Sessions(list<Session *> *l_sessions);

private:
	int on_off; //����
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
	map<string, int> *stg_map_instrument_action_counter;
	mongo::DBClientConnection * PositionConn;
	mongo::DBClientConnection * TradeConn;
	mongo::DBClientConnection * OrderConn;
	DBManager *dbm;
	long long stg_order_ref_base;
	CTP_Manager *o_ctp;
	string isActive;
	string trading_day;				// ������
	int sid;	// �ỰID
	list<Session *> *l_sessions;
};

#endif