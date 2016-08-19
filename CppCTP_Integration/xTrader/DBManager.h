#ifndef QUANT_DBMANAGER_H
#define QUANT_DBMANAGER_H

#include <iostream>
#include <cstdlib>
#include <list>
#include <mongo/client/dbclient.h>

#include "Trader.h"
#include "FutureAccount.h"

using namespace mongo;
using namespace std;
using std::string;
using mongo::DBClientConnection;

class DBManager {
public:
	DBManager();
	~DBManager();
	static mongo::DBClientConnection * getDBConnection();

	/************************************************************************/
	/* ��������Ա
	   ɾ������Ա
	   ���½���Ա
	   ���ҽ���Ա(username)
	   ���ҽ���Ա(nickname)                                                  */
	/************************************************************************/
	void CreateTrader(Trader *op);
	void DeleteTrader(Trader *op);
	void UpdateTrader(string traderid, Trader *op);
	void SearchTraderByTraderID(string traderid);
	void SearchTraderByTraderName(string tradername);
	void SearchTraderByTraderIdAndPassword(string traderid, string password);
	bool FindTraderByTraderIdAndPassword(string traderid, string password);
	void getAllTrader();


	/************************************************************************/
	/* ���ҹ���Ա                                                             */
	/************************************************************************/
	bool FindAdminByAdminIdAndPassword(string adminid, string password);


	/************************************************************************/
	/* �����˻�
	   ɾ���˻�
	   �����˻�
	   �����˻�(userid)
	   �����˻�(tradername)                                                  */
	/************************************************************************/
	void CreateFutureAccount(Trader *op, FutureAccount *fa);
	void DeleteFutureAccount(FutureAccount *fa);
	void UpdateFutureAccount(string userid, Trader *op, FutureAccount *fa);
	void SearchFutrueByUserID(string userid);
	void SearchFutrueByTraderID(string traderid);
	void SearchFutrueListByTraderID(string traderid, list<FutureAccount *> *l_futureaccount);
	void getAllFutureAccount();

	void setConn(mongo::DBClientConnection *conn);
	mongo::DBClientConnection *getConn();

private:
	mongo::DBClientConnection *conn;
};

#endif