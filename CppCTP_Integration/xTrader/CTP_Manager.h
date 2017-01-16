#ifndef QUANT_CTP_MANAGER_H
#define QUANT_CTP_MANAGER_H

#include <list>
#include <map>
#include <string>
#include "Login.h"
#include "MdSpi.h"
#include "TdSpi.h"
#include "DBManager.h"
#include "Trader.h"
#include "Session.h"

using std::map;
class MdSpi;

class CTP_Manager {

public:
	CTP_Manager();
	///��½
	bool CheckIn(Login *login);

	/// trader login
	bool TraderLogin(string traderid, string password, Trader *op);

	/// admin login
	bool AdminLogin(string adminid, string password);

	///��������
	int submarketData(char *instrument[]);

	/// �������׶����ҵ�½
	User * CreateAccount(User *user, list<Strategy *> *l_strategys);

	/// ��������
	MdSpi * CreateMd(string td_frontAddress, string td_broker, string td_user, string td_pass, list<Strategy *> *l_strategys);

	///�ͷ�
	void ReleaseAccount(User *user);

	///��������
	void SubmarketData(MdSpi *mdspi, list<string > *l_instrument);

	///ȡ����������
	void UnSubmarketData(MdSpi *mdspi, string instrumentID, list<string > *l_instrument);

	/// ��Ӻ�Լ
	list<string> * addSubInstrument(string instrumentID, list<string> *l_instrument);

	/// ɾ�����ĺ�Լ
	list<string> * delSubInstrument(string instrumentID, list<string> *l_instrument);

	/// ͳ�ƺ�Լ����
	int calInstrument(string instrumentID, list<string> *l_instrument);

	/// �˶���Լ����
	list<string> addUnSubInstrument(string instrumentID, list<string> l_instrument);

	/// �õ�l_instrument
	list<string> *getL_Instrument();

	/// �õ�l_unsubinstrument
	list<string> *getL_UnsubInstrument();

	/// �õ����ݿ��������
	DBManager *getDBManager();

	/// ����l_trader
	void addTraderToLTrader(string trader);

	/// ��ȡtrader�Ƿ���l_trader��
	bool checkInLTrader(string trader);

	/// �õ�l_trader
	list<string> *getL_Trader();

	/// �õ�l_obj_trader
	list<Trader *> * getL_Obj_Trader();

	/// �Ƴ�Ԫ��
	void removeFromLTrader(string trader);

	/// �����û��ڻ��˻�
	void addFuturesToTrader(string traderid, User *user);

	/// ��ȡ�ڻ��˻�map
	map<string, list<User *> *> getTraderMap();

	/// �����û��б�
	list<User *> *getL_User();

	/// �õ�strategy_list
	list<Strategy *> *getListStrategy();

	/// �õ�strategy_list
	list<Strategy *> *getListStrategyYesterday();

	/// ����strategy_list
	void setListStrategy(list<Strategy *> *l_strategys);

	/// ����strategy_list
	void saveStrategy();

	/// ����mdspi
	void setMdSpi(MdSpi *mdspi);

	/// ���mdspi
	MdSpi *getMdSpi();

	/// ��ʼ��
	bool init(bool is_online = true);

	/// ���ÿ���
	int getOn_Off();
	void setOn_Off(int on_off);

	/// ����ͻ��˷�������Ϣ
	static void HandleMessage(int fd, char *msg, CTP_Manager *ctp_m);

	/// ���ý�����
	void setTradingDay(string trading_day);

	/// ��ý�����
	string getTradingDay();

	/// ��ʼ�����
	bool initYesterdayPosition();

	/// ��ʼ�������ϸ
	bool initYesterdayPositionDetail();

private:
	Login *login;
	list<string> *l_instrument;
	list<string > *l_unsubinstrument;
	list<string> *l_trader;
	list<User *> *l_user;
	list<Trader *> *l_obj_trader;
	map<string, list<User *> *> m_trader;
	DBManager *dbm;
	list<Strategy *> *l_strategys;
	list<Strategy *> *l_strategys_yesterday;
	MdSpi *mdspi;
	int on_off; //����
	string trading_day;
	bool isClosingSaved;
	list<Session *> *l_sessions;
	list<PositionDetail *> *l_posdetail;
};
#endif