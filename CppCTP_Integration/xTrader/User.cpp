#include <sstream>
#include "User.h"
#include "DBManager.h"
#include "Debug.h"
#include "Utils.h"

/// Order��صļ���
#define DB_ORDERINSERT_COLLECTION         "CTP.orderinsert"
#define DB_ONRTNORDER_COLLECTION          "CTP.onrtnorder"
#define DB_ONRTNTRADE_COLLECTION          "CTP.onrtntrade"
#define DB_ORDERACTION_COLLECTION         "CTP.orderaction"
#define DB_ORDERCOMBINE_COLLECTION        "CTP.ordercombine"
#define DB_ONRSPORDERACTION_COLLECTION    "CTP.onrsporderaction"
#define DB_ONERRRTNORDERACTION_COLLECTION "CTP.onerrrtnorderaction"
#define DB_ONRSPORDERINSERT_COLLECTION    "CTP.onrsporderinsert"
#define DB_ONERRRTNORDERINSERT_COLLECTION "CTP.onerrrtnorderinsert"
#define DB_ONRSPQRYINVESTORPOSITION       "CTP.onrspqryinvestorposition"


//ת������
char codeDst_2[90] = { 0 };

User::User(string frontAddress, string BrokerID, string UserID, string Password, string nRequestID, int on_off, string TraderID, string stg_order_ref_base) {
	this->on_off = on_off;
	this->BrokerID = BrokerID;
	this->UserID = UserID;
	this->Password = Password;
	this->frontAddress = frontAddress;
	this->nRequestID = atoi(UserID.c_str());
	this->isConfirmSettlement = false;
	this->TradeConn = DBManager::getDBConnection();
	this->PositionConn = DBManager::getDBConnection();
	this->OrderConn = DBManager::getDBConnection();
	this->OrderRefConn = DBManager::getDBConnection();
	this->OrderActionConn = DBManager::getDBConnection();
	this->TraderID = TraderID;
	this->l_strategys = new list<Strategy *>();
	this->l_sessions = new list<Session *>();
	this->stg_map_instrument_action_counter = new map<string, int>();
	this->stg_order_ref_base = Utils::strtolonglong(stg_order_ref_base);
	this->isLogged = true;
	this->isConnected = true;
	this->isLoggedError = false;
	USER_PRINT(this->stg_order_ref_base);
}

User::User(string BrokerID, string UserID, int nRequestID, string stg_order_ref_base) {
	this->on_off = 0;
	this->BrokerID = BrokerID;
	this->UserID = UserID;
	this->nRequestID = atoi(UserID.c_str());
	this->isConfirmSettlement = false;
	this->TradeConn = DBManager::getDBConnection();
	this->PositionConn = DBManager::getDBConnection();
	this->OrderConn = DBManager::getDBConnection();
	this->OrderRefConn = DBManager::getDBConnection();
	this->OrderActionConn = DBManager::getDBConnection();
	this->l_strategys = new list<Strategy *>();
	this->l_sessions = new list<Session *>();
	this->stg_map_instrument_action_counter = new map<string, int>();
	this->stg_order_ref_base = Utils::strtolonglong(stg_order_ref_base);
	this->isLogged = true;
	this->isConnected = true;
	this->isLoggedError = false;
}

User::~User() {

}

string User::getBrokerID() {
	return this->BrokerID;
}
string User::getUserID() {
	return this->UserID;
}
string User::getPassword() {
	return this->Password;
}

int User::getRequestID() {
	return this->nRequestID;
}
bool User::getIsLogged() {
	return this->isLogged;
}

bool User::getIsLoggedError() {
	return this->isLoggedError;
}

bool User::getIsConnected() {
	return this->isConnected;
}

bool User::getIsFirstTimeLogged() {
	return this->isFirstTimeLogged;
}
bool User::getIsConfirmSettlement() {
	return this->isConfirmSettlement;
}
int User::getLoginRequestID() {
	return this->loginRequestID;
}

CThostFtdcTraderApi * User::getUserTradeAPI() {
	return this->UserTradeAPI;
}

TdSpi * User::getUserTradeSPI() {
	return this->UserTradeSPI;
}

string User::getFrontAddress() {
	return this->frontAddress;
}

void User::setBrokerID(string BrokerID) {
	this->BrokerID = BrokerID;
}
void User::setUserID(string UserID) {
	this->UserID = UserID;
}
void User::setPassword(string Password) {
	this->Password = Password;
}

void User::setRequestID(int nRequestID) {
	this->nRequestID = nRequestID;
}
void User::setIsLogged(bool isLogged) {
	this->isLogged = isLogged;
}

void User::setIsLoggedError(bool isLoggedError) {
	this->isLoggedError = isLoggedError;
}

void User::setIsConnected(bool isConnected) {
	this->isConnected = isConnected;
}

void User::setIsFirstTimeLogged(bool isFirstTimeLogged) {
	this->isFirstTimeLogged = isFirstTimeLogged;
}
void User::setIsConfirmSettlement(bool isConfirmSettlement) {
	this->isConfirmSettlement = isConfirmSettlement;
}
void User::setLoginRequestID(int loginRequestID) {
	this->loginRequestID = loginRequestID;
}

void User::setUserTradeAPI(CThostFtdcTraderApi *UserTradeAPI) {
	this->UserTradeAPI = UserTradeAPI;
}

void User::setUserTradeSPI(TdSpi *UserTradeSPI) {
	this->UserTradeSPI = UserTradeSPI;
}

void User::setFrontAddress(string frontAddress) {
	this->frontAddress = frontAddress;
}

Trader * User::GetTrader() {
	return this->trader;
}
void User::setTrader(Trader *trader) {
	this->trader = trader;
}

string User::getTraderID() {
	return this->TraderID;
}


void User::setTraderID(string TraderID) {
	this->TraderID = TraderID;
}

/// �õ�strategy_list
list<Strategy *> * User::getListStrategy() {
	return this->l_strategys;
}

/// ����strategy_list
void User::setListStrategy(list<Strategy *> * l_strategys) {
	this->l_strategys = l_strategys;
}

/// ���strategy��list
void User::addStrategyToList(Strategy *stg) {
	this->l_strategys->push_back(stg);
}

/// ��ʼ����Լ��������,����"cu1601":0 "cu1701":0
void User::init_instrument_id_action_counter(string instrument_id) {
	//��ʼ��Ϊ0
	//this->stg_map_instrument_action_counter->insert(map < string, int >::value_type(instrument_id, 0)); ��һ��map���뷽��
	this->stg_map_instrument_action_counter->insert(pair<string, int>(instrument_id, 0)); //�ڶ���map���뷽��
}

/// ��ú�Լ��������,����"cu1710":0
int User::get_instrument_id_action_counter(string instrument_id) {
	USER_PRINT("User::get_instrument_id_action_counter");
	//��ĳ����Լ���м�1����
	map<string, int>::iterator m_itor;
	m_itor = this->stg_map_instrument_action_counter->find(instrument_id);
	if (m_itor == (this->stg_map_instrument_action_counter->end())) {
		cout << "�����б��ﲻ���ڸú�Լ = " << instrument_id << endl;
		// this->stg_map_instrument_action_counter->insert(pair<string, int>(instrument_id, 0));
		// this->init_instrument_id_action_counter(string(pOrder->InstrumentID));
		return 0;
	}
	else {
		cout << "�����б����ҵ��ú�Լ = " << instrument_id << endl;
		return m_itor->second;
	}
}

/// ��Ӷ�Ӧ��Լ��������������,����"cu1602":1 "cu1701":1
void User::add_instrument_id_action_counter(CThostFtdcOrderField *pOrder) {
	USER_PRINT("User::add_instrument_id_action_counter");

	if (strlen(pOrder->OrderSysID) == 0) { //ֻͳ����Խ����������order
		return;
	}
	if (pOrder->OrderStatus != '5') { //����
		return;
	}

	if (pOrder->OrderStatus == '5') { // ���յ�����
		//��ĳ����Լ���м�1����
		map<string, int>::iterator m_itor;
		m_itor = this->stg_map_instrument_action_counter->find(string(pOrder->InstrumentID));
		if (m_itor == (this->stg_map_instrument_action_counter->end())) {
			cout << "�����б��ﲻ���ڸú�Լ = " << pOrder->InstrumentID << endl;
			cout << "��� " << pOrder->InstrumentID << " ��Լ���б���..." << endl;
			//this->stg_map_instrument_action_counter->insert(pair<string, int>(instrument_id, 0));
			this->init_instrument_id_action_counter(string(pOrder->InstrumentID));
		}
		else {
			cout << "�����б����ҵ��ú�Լ = " << pOrder->InstrumentID << endl;
			m_itor->second += 1;
		}

		// ����������������˻������еĲ���
		list<Strategy *>::iterator stg_itor;
		for (stg_itor = this->l_strategys->begin(); stg_itor != this->l_strategys->end(); stg_itor++) { // ����Strategy

			USER_PRINT((*stg_itor)->getStgInstrumentIdA());
			USER_PRINT((*stg_itor)->getStgInstrumentIdB());
			USER_PRINT(pOrder->InstrumentID);

			if (!strcmp((*stg_itor)->getStgInstrumentIdA().c_str(), pOrder->InstrumentID)) {
				(*stg_itor)->setStgAOrderActionCount(this->get_instrument_id_action_counter(string(pOrder->InstrumentID)));
			}

			if (!(strcmp((*stg_itor)->getStgInstrumentIdB().c_str(), pOrder->InstrumentID))) {
				(*stg_itor)->setStgBOrderActionCount(this->get_instrument_id_action_counter(string(pOrder->InstrumentID)));
			}
		}

	}
}

void User::setStgOrderRefBase(long long stg_order_ref_base) {
	this->stg_order_ref_base = stg_order_ref_base;
}

long long User::getStgOrderRefBase() {
	return this->stg_order_ref_base;
}

/// ���ò����ں�Լ��С���۸�
void User::setStgInstrumnetPriceTick() {
	USER_PRINT("User::setStgInstrumnetPriceTick");
	//1:����strategy list
	list<Strategy *>::iterator stg_itor;
	list<CThostFtdcInstrumentField *>::iterator instrument_info_itor;
	for (stg_itor = this->l_strategys->begin(); stg_itor != this->l_strategys->end(); stg_itor++) {
		//2:������Լ��Ϣ�б�,�ҵ���Ӧ��Լ����С��
		for (instrument_info_itor = this->getUserTradeSPI()->getL_Instruments_Info()->begin();
			instrument_info_itor != this->getUserTradeSPI()->getL_Instruments_Info()->end();
			instrument_info_itor++) {
			if (!strcmp((*stg_itor)->getStgInstrumentIdA().c_str(), (*instrument_info_itor)->InstrumentID)) {
				USER_PRINT("(*stg_itor)->getStgInstrumentIdA()");
				USER_PRINT((*stg_itor)->getStgInstrumentIdA());
				(*stg_itor)->setStgAPriceTick((*instrument_info_itor)->PriceTick);
			}
			if (!strcmp((*stg_itor)->getStgInstrumentIdB().c_str(), (*instrument_info_itor)->InstrumentID)) {
				USER_PRINT("(*stg_itor)->getStgInstrumentIdB()");
				USER_PRINT((*stg_itor)->getStgInstrumentIdB());
				(*stg_itor)->setStgBPriceTick((*instrument_info_itor)->PriceTick);
			}
		}
	}
}

/************************************************************************/
/* ��ȡ���ݿ�����                                                         */
/************************************************************************/
mongo::DBClientConnection * User::GetPositionConn() {
	return this->PositionConn;
}
mongo::DBClientConnection * User::GetTradeConn() {
	return this->TradeConn;
}
mongo::DBClientConnection * User::GetOrderConn() {
	return this->OrderConn;
}
mongo::DBClientConnection * User::GetOrderActionConn() {
	return this->OrderActionConn;
}

/************************************************************************/
/* ���Order��MongoDB����                                                 */
/************************************************************************/
void User::DB_OrderInsert(mongo::DBClientConnection *conn, CThostFtdcInputOrderField *pInputOrder) {
	USER_PRINT("User::DB_OrderInsert DB Connection!");
	USER_PRINT(conn);
	BSONObjBuilder b;

	/// ����Աid
	b.append("OperatorID", this->getTraderID());

	///���͹�˾����
	b.append("BrokerID", pInputOrder->BrokerID);
	///Ͷ���ߴ���
	b.append("InvestorID", pInputOrder->InvestorID);
	///��Լ����
	b.append("InstrumentID", pInputOrder->InstrumentID);
	///��������
	b.append("OrderRef", pInputOrder->OrderRef);
	///�û�����
	b.append("UserID", pInputOrder->UserID);
	///�����۸�����
	b.append("OrderPriceType", pInputOrder->OrderPriceType);
	///��������
	b.append("Direction", pInputOrder->Direction);
	///��Ͽ�ƽ��־
	b.append("CombOffsetFlag", pInputOrder->CombOffsetFlag);
	///���Ͷ���ױ���־
	b.append("CombHedgeFlag", pInputOrder->CombHedgeFlag);
	///�۸�
	b.append("LimitPrice", pInputOrder->LimitPrice);
	///����
	b.append("VolumeTotalOriginal", pInputOrder->VolumeTotalOriginal);
	///��Ч������
	b.append("TimeCondition", pInputOrder->TimeCondition);
	///GTD����
	b.append("GTDDate", pInputOrder->GTDDate);
	///�ɽ�������
	b.append("VolumeCondition", pInputOrder->VolumeCondition);
	///��С�ɽ���
	b.append("MinVolume", pInputOrder->MinVolume);
	///��������
	b.append("ContingentCondition", pInputOrder->ContingentCondition);
	///ֹ���
	b.append("StopPrice", pInputOrder->StopPrice);
	///ǿƽԭ��
	b.append("ForceCloseReason", pInputOrder->ForceCloseReason);
	///�Զ������־
	b.append("IsAutoSuspend", pInputOrder->IsAutoSuspend);
	///ҵ��Ԫ
	b.append("BusinessUnit", pInputOrder->BusinessUnit);
	///������
	b.append("RequestID", pInputOrder->RequestID);
	///�û�ǿ����־
	b.append("UserForceClose", pInputOrder->UserForceClose);
	///��������־
	b.append("IsSwapOrder", pInputOrder->IsSwapOrder);
	///����������
	b.append("ExchangeID", pInputOrder->ExchangeID);
	///Ͷ�ʵ�Ԫ����
	b.append("InvestUnitID", pInputOrder->InvestUnitID);
	///�ʽ��˺�
	b.append("AccountID", pInputOrder->AccountID);
	///���ִ���
	b.append("CurrencyID", pInputOrder->CurrencyID);
	///���ױ���
	b.append("ClientID", pInputOrder->ClientID);
	///IP��ַ
	b.append("IPAddress", pInputOrder->IPAddress);
	///Mac��ַ
	b.append("MacAddress", pInputOrder->MacAddress);

	string time_str = string(Utils::getNowTimeMs());
	int pos1 = time_str.find_first_of('_');
	int pos = time_str.find_last_of('_');
	USER_PRINT(time_str);
	USER_PRINT(time_str.length());
	USER_PRINT(pos1);
	USER_PRINT(pos);
	//std::cout << pos1 << '\n';
	//std::cout << pos << '\n';
	string SendOrderTime = time_str.substr(pos1 + 1, pos - 1);
	string SendOrderMicrosecond = time_str.substr(pos + 1);
	/// ����ʱ��
	b.append("SendOrderTime", SendOrderTime);
	/// ����ʱ��΢��
	b.append("SendOrderMicrosecond", SendOrderMicrosecond);

	/// �ͻ����˺ţ�Ҳ�������û���ݻ���Ա��ݣ�:OperatorID
	b.append("OperatorID", this->getTraderID());

	string temp(pInputOrder->OrderRef);
	int len_order_ref = temp.length();
	string result = temp.substr(len_order_ref - 2, 2);
	/// ���ײ��Ա�ţ�StrategyID
	b.append("StrategyID", result);

	BSONObj p = b.obj();
	//conn->insert(DB_ORDERINSERT_COLLECTION, p);
	USER_PRINT("Begin Insert!");

	this->dbm->getConn()->insert(DB_ORDERINSERT_COLLECTION, p);

	/*string temp_order_ref_base = temp.substr(0, 10);
	USER_PRINT(temp_order_ref_base);
	this->DB_UpdateOrderRef(temp_order_ref_base);*/

	USER_PRINT("DBManager::DB_OrderInsert ok");
}

// ���±�������
void User::DB_UpdateOrderRef(string order_ref_base) {
	USER_PRINT("User::DB_UpdateOrderRef!");
	int len_order_ref_base = order_ref_base.length();
	USER_PRINT(order_ref_base);
	USER_PRINT(len_order_ref_base);
	this->dbm->UpdateFutureAccountOrderRef(this->OrderRefConn, this, order_ref_base);
}

void User::DB_OnRtnOrder(mongo::DBClientConnection *conn, CThostFtdcOrderField *pOrder){
	USER_PRINT("User::DB_OnRtnOrder DB Connection!");
	USER_PRINT(conn);
	BSONObjBuilder b;
	/// ����Աid
	b.append("OperatorID", this->getTraderID());
	///���͹�˾����
	b.append("BrokerID", pOrder->BrokerID);
	///Ͷ���ߴ���
	b.append("InvestorID", pOrder->InvestorID);
	///��Լ����
	b.append("InstrumentID", pOrder->InstrumentID);
	///��������
	b.append("OrderRef", pOrder->OrderRef);
	///�û�����
	b.append("UserID", pOrder->UserID);
	///�����۸�����
	b.append("OrderPriceType", pOrder->OrderPriceType);
	///��������
	b.append("Direction", pOrder->Direction);
	///��Ͽ�ƽ��־
	b.append("CombOffsetFlag", pOrder->CombOffsetFlag);
	///���Ͷ���ױ���־
	b.append("CombHedgeFlag", pOrder->CombHedgeFlag);
	///�۸�
	b.append("LimitPrice", pOrder->LimitPrice);
	///����
	b.append("VolumeTotalOriginal", pOrder->VolumeTotalOriginal);
	///��Ч������
	b.append("TimeCondition", pOrder->TimeCondition);
	///GTD����
	b.append("GTDDate", pOrder->GTDDate);
	///�ɽ�������
	b.append("VolumeCondition", pOrder->VolumeCondition);
	///��С�ɽ���
	b.append("MinVolume", pOrder->MinVolume);
	///��������
	b.append("ContingentCondition", pOrder->ContingentCondition);
	///ֹ���
	b.append("StopPrice", pOrder->StopPrice);
	///ǿƽԭ��
	b.append("ForceCloseReason", pOrder->ForceCloseReason);
	///�Զ������־
	b.append("IsAutoSuspend", pOrder->IsAutoSuspend);
	///ҵ��Ԫ
	b.append("BusinessUnit", pOrder->BusinessUnit);
	///������
	b.append("RequestID", pOrder->RequestID);
	///���ر������
	b.append("OrderLocalID", pOrder->OrderLocalID);
	///����������
	b.append("ExchangeID", pOrder->ExchangeID);
	///��Ա����
	b.append("ParticipantID", pOrder->ParticipantID);
	///�ͻ�����
	b.append("ClientID", pOrder->ClientID);
	///��Լ�ڽ������Ĵ���
	b.append("ExchangeInstID", pOrder->ExchangeInstID);
	///����������Ա����
	b.append("TraderID", pOrder->TraderID);
	///��װ���
	b.append("InstallID", pOrder->InstallID);
	///�����ύ״̬
	b.append("OrderSubmitStatus", pOrder->OrderSubmitStatus);
	///������ʾ���
	b.append("NotifySequence", pOrder->NotifySequence);
	///������
	b.append("TradingDay", pOrder->TradingDay);
	///������
	b.append("SettlementID", pOrder->SettlementID);
	///�������
	b.append("OrderSysID", pOrder->OrderSysID);
	///������Դ
	b.append("OrderSource", pOrder->OrderSource);
	///����״̬
	stringstream ss;
	string OrderStatus;
	ss << pOrder->OrderStatus;
	ss >> OrderStatus;
	b.append("OrderStatus", OrderStatus);
	///��������
	b.append("OrderType", pOrder->OrderType);
	///��ɽ�����
	b.append("VolumeTraded", pOrder->VolumeTraded);
	///ʣ������
	b.append("VolumeTotal", pOrder->VolumeTotal);
	///��������
	b.append("InsertDate", pOrder->InsertDate);
	///ί��ʱ��
	b.append("InsertTime", pOrder->InsertTime);
	///����ʱ��
	b.append("ActiveTime", pOrder->ActiveTime);
	///����ʱ��
	b.append("SuspendTime", pOrder->SuspendTime);
	///����޸�ʱ��
	b.append("UpdateTime", pOrder->UpdateTime);
	///����ʱ��
	b.append("CancelTime", pOrder->CancelTime);
	///����޸Ľ���������Ա����
	b.append("ActiveTraderID", pOrder->ActiveTraderID);
	///�����Ա���
	b.append("ClearingPartID", pOrder->ClearingPartID);
	///���
	b.append("SequenceNo", pOrder->SequenceNo);
	///ǰ�ñ��
	b.append("FrontID", pOrder->FrontID);
	///�Ự���
	b.append("SessionID", pOrder->SessionID);
	///�û��˲�Ʒ��Ϣ
	b.append("UserProductInfo", pOrder->UserProductInfo);
	///״̬��Ϣ
	///״̬��Ϣ
	codeDst_2[90] = { 0 };
	Utils::Gb2312ToUtf8(codeDst_2, 90, pOrder->StatusMsg, strlen(pOrder->StatusMsg)); // Gb2312ToUtf8
	b.append("StatusMsg", codeDst_2);
	///�û�ǿ����־
	b.append("UserForceClose", pOrder->UserForceClose);
	///�����û�����
	b.append("ActiveUserID", pOrder->ActiveUserID);
	///���͹�˾�������
	b.append("BrokerOrderSeq", pOrder->BrokerOrderSeq);
	///��ر���
	b.append("RelativeOrderSysID", pOrder->RelativeOrderSysID);
	///֣�����ɽ�����
	b.append("ZCETotalTradedVolume", pOrder->ZCETotalTradedVolume);
	///��������־
	b.append("IsSwapOrder", pOrder->IsSwapOrder);
	///Ӫҵ�����
	b.append("BranchID", pOrder->BranchID);
	///Ͷ�ʵ�Ԫ����
	b.append("InvestUnitID", pOrder->InvestUnitID);
	///�ʽ��˺�
	b.append("AccountID", pOrder->AccountID);
	///���ִ���
	b.append("CurrencyID", pOrder->CurrencyID);
	///IP��ַ
	b.append("IPAddress", pOrder->IPAddress);
	///Mac��ַ
	b.append("MacAddress", pOrder->MacAddress);

	string time_str = Utils::getNowTimeMs();
	int pos1 = time_str.find_first_of('_');
	int pos = time_str.find_last_of('_');
	//std::cout << pos1 << '\n';
	//std::cout << pos << '\n';
	string CtpRtnOrderTime = time_str.substr(pos1 + 1, pos - 1);
	string CtpRtnOrderMicrosecond = time_str.substr(pos + 1);
	/// ����ʱ��
	b.append("CtpRtnOrderTime", CtpRtnOrderTime);
	/// ����ʱ��΢��
	b.append("CtpRtnOrderMicrosecond", CtpRtnOrderMicrosecond);

	/// ����ʱ��
	b.append("ExchRtnOrderTime", CtpRtnOrderTime);
	/// ����ʱ��΢��
	b.append("ExchRtnOrderMicrosecond", CtpRtnOrderMicrosecond);

	/// �ͻ����˺ţ�Ҳ�������û���ݻ���Ա��ݣ�:OperatorID
	b.append("OperatorID", this->getTraderID());

	string temp(pOrder->OrderRef);
	USER_PRINT(temp);
	int len_order_ref = temp.length();
	string result = temp.substr(len_order_ref - 2, 2);
	/// ���ײ��Ա�ţ�StrategyID
	b.append("StrategyID", result);

	BSONObj p = b.obj();
	//conn->insert(DB_ONRTNORDER_COLLECTION, p);
	USER_PRINT("Begin Insert!");

	//this->dbm->getConn()->insert(DB_ONRTNORDER_COLLECTION, p);
	this->OrderConn->insert(DB_ONRTNORDER_COLLECTION, p);

	/*string temp_order_ref_base = temp.substr(0, 10);
	USER_PRINT(temp_order_ref_base);
	this->DB_UpdateOrderRef(temp_order_ref_base);*/
	USER_PRINT("DBManager::DB_OnRtnOrder ok");
	
}

void User::DB_OnRtnTrade(mongo::DBClientConnection *conn, CThostFtdcTradeField *pTrade){
	USER_PRINT(DB_ONRTNORDER_COLLECTION"User::DB_OnRtnTrade DB Connection!");
	BSONObjBuilder b;
	/// ����Աid
	b.append("OperatorID", this->getTraderID());
	///���͹�˾����
	b.append("BrokerID", pTrade->BrokerID);
	///Ͷ���ߴ���
	b.append("InvestorID", pTrade->InvestorID);
	///��Լ����
	b.append("InstrumentID", pTrade->InstrumentID);
	///��������
	b.append("OrderRef", pTrade->OrderRef);
	///�û�����
	b.append("UserID", pTrade->UserID);
	///����������
	b.append("ExchangeID", pTrade->ExchangeID);
	///�ɽ����
	b.append("TradeID", pTrade->TradeID);
	///��������
	b.append("Direction", pTrade->Direction);
	///�������
	b.append("OrderSysID", pTrade->OrderSysID);
	///��Ա����
	b.append("ParticipantID", pTrade->ParticipantID);
	///�ͻ�����
	b.append("ClientID", pTrade->ClientID);
	///���׽�ɫ
	b.append("TradingRole", pTrade->TradingRole);
	///��Լ�ڽ������Ĵ���
	b.append("ExchangeInstID", pTrade->ExchangeInstID);
	///��ƽ��־
	b.append("OffsetFlag", pTrade->OffsetFlag);
	///Ͷ���ױ���־
	b.append("HedgeFlag", pTrade->HedgeFlag);
	///�۸�
	b.append("Price", pTrade->Price);
	///����
	b.append("Volume", pTrade->Volume);
	///�ɽ�ʱ��
	b.append("TradeDate", pTrade->TradeDate);
	///�ɽ�ʱ��
	b.append("TradeTime", pTrade->TradeTime);
	///�ɽ�����
	b.append("TradeType", pTrade->TradeType);
	///�ɽ�����Դ
	b.append("PriceSource", pTrade->PriceSource);
	///����������Ա����
	b.append("TraderID", pTrade->TraderID);
	///���ر������
	b.append("OrderLocalID", pTrade->OrderLocalID);
	///�����Ա���
	b.append("ClearingPartID", pTrade->ClearingPartID);
	///ҵ��Ԫ
	b.append("BusinessUnit", pTrade->BusinessUnit);
	///���
	b.append("SequenceNo", pTrade->SequenceNo);
	///������
	b.append("TradingDay", pTrade->TradingDay);
	///������
	b.append("SettlementID", pTrade->SettlementID);
	///���͹�˾�������
	b.append("BrokerOrderSeq", pTrade->BrokerOrderSeq);
	///�ɽ���Դ
	b.append("TradeSource", pTrade->TradeSource);


	string time_str = string(Utils::getNowTimeMs());
	int pos1 = time_str.find_first_of('_');
	int pos = time_str.find_last_of('_');
	//std::cout << "pos1" << pos1 << '\n';
	//std::cout << "pos" << pos << '\n';
	USER_PRINT(time_str);
	USER_PRINT(time_str.length());
	USER_PRINT(pos1);
	USER_PRINT(pos);
	string RecTradeTime = time_str.substr(pos1 + 1, pos - 1);
	USER_PRINT(RecTradeTime);
	USER_PRINT(time_str);
	string RecTradeMicrosecond = time_str.substr(21);
	USER_PRINT(RecTradeMicrosecond);
	/// ����ʱ��
	b.append("RecTradeTime", RecTradeTime);
	/// ����ʱ��΢��
	b.append("RecTradeMicrosecond", RecTradeMicrosecond);

	/// �ͻ����˺ţ�Ҳ�������û���ݻ���Ա��ݣ�:OperatorID
	b.append("OperatorID", this->getTraderID());

	string temp(pTrade->OrderRef);
	USER_PRINT(pTrade->OrderRef);
	USER_PRINT(temp);
	USER_PRINT(temp.length());
	int len_order_ref = temp.length();
	string result = temp.substr(len_order_ref - 2, 2);
	USER_PRINT(result);
	/// ���ײ��Ա�ţ�StrategyID
	b.append("StrategyID", result);

	BSONObj p = b.obj();
	//conn->insert(DB_ONRTNTRADE_COLLECTION, p);

	//this->dbm->getConn()->insert(DB_ONRTNTRADE_COLLECTION, p);
	this->TradeConn->insert(DB_ONRTNTRADE_COLLECTION, p);
	
	USER_PRINT("DBManager::DB_OnRtnTrade ok");
}

void User::DB_OrderAction(mongo::DBClientConnection *conn, CThostFtdcInputOrderActionField *pOrderAction){
	USER_PRINT("User::DB_OrderAction DB Connection!");
	USER_PRINT(conn);
	BSONObjBuilder b;
	/// ����Աid
	b.append("OperatorID", this->getTraderID());
	///���͹�˾����
	b.append("BrokerID", pOrderAction->BrokerID);
	///Ͷ���ߴ���
	b.append("InvestorID", pOrderAction->InvestorID);
	///������������
	b.append("OrderActionRef", pOrderAction->OrderActionRef);
	///��������
	b.append("OrderRef", pOrderAction->OrderRef);
	///������
	b.append("RequestID", pOrderAction->RequestID);
	///ǰ�ñ��
	b.append("FrontID", pOrderAction->FrontID);
	///�Ự���
	b.append("SessionID", pOrderAction->SessionID);
	///����������
	b.append("ExchangeID", pOrderAction->ExchangeID);
	///�������
	b.append("OrderSysID", pOrderAction->OrderSysID);
	///������־
	b.append("ActionFlag", pOrderAction->ActionFlag);
	///�۸�
	b.append("LimitPrice", pOrderAction->LimitPrice);
	///�����仯
	b.append("VolumeChange", pOrderAction->VolumeChange);
	///�û�����
	b.append("UserID", pOrderAction->UserID);
	///��Լ����
	b.append("InstrumentID", pOrderAction->InstrumentID);
	///Ͷ�ʵ�Ԫ����
	b.append("InvestUnitID", pOrderAction->InvestUnitID);
	///IP��ַ
	b.append("IPAddress", pOrderAction->IPAddress);
	///Mac��ַ
	b.append("MacAddress", pOrderAction->MacAddress);
	BSONObj p = b.obj();
	this->OrderActionConn->insert(DB_ORDERACTION_COLLECTION, p);

	USER_PRINT("DBManager::DB_OrderAction ok");
}

void User::DB_OrderCombine(mongo::DBClientConnection *conn, CThostFtdcOrderField *pOrder){
	USER_PRINT("User::DB_OrderCombine DB Connection!");
	USER_PRINT(conn);
	BSONObjBuilder b;
	/// ����Աid
	b.append("OperatorID", this->getTraderID());
	///���͹�˾����
	b.append("BrokerID", pOrder->BrokerID);
	///Ͷ���ߴ���
	b.append("InvestorID", pOrder->InvestorID);
	///��Լ����
	b.append("InstrumentID", pOrder->InstrumentID);
	///��������
	b.append("OrderRef", pOrder->OrderRef);
	///�û�����
	b.append("UserID", pOrder->UserID);
	///�����۸�����
	b.append("OrderPriceType", pOrder->OrderPriceType);
	///��������
	b.append("Direction", pOrder->Direction);
	///��Ͽ�ƽ��־
	b.append("CombOffsetFlag", pOrder->CombOffsetFlag);
	///���Ͷ���ױ���־
	b.append("CombHedgeFlag", pOrder->CombHedgeFlag);
	///�۸�
	b.append("LimitPrice", pOrder->LimitPrice);
	///����
	b.append("VolumeTotalOriginal", pOrder->VolumeTotalOriginal);
	///��Ч������
	b.append("TimeCondition", pOrder->TimeCondition);
	///GTD����
	b.append("GTDDate", pOrder->GTDDate);
	///�ɽ�������
	b.append("VolumeCondition", pOrder->VolumeCondition);
	///��С�ɽ���
	b.append("MinVolume", pOrder->MinVolume);
	///��������
	b.append("ContingentCondition", pOrder->ContingentCondition);
	///ֹ���
	b.append("StopPrice", pOrder->StopPrice);
	///ǿƽԭ��
	b.append("ForceCloseReason", pOrder->ForceCloseReason);
	///�Զ������־
	b.append("IsAutoSuspend", pOrder->IsAutoSuspend);
	///ҵ��Ԫ
	b.append("BusinessUnit", pOrder->BusinessUnit);
	///������
	b.append("RequestID", pOrder->RequestID);
	///���ر������
	b.append("OrderLocalID", pOrder->OrderLocalID);
	///����������
	b.append("ExchangeID", pOrder->ExchangeID);
	///��Ա����
	b.append("ParticipantID", pOrder->ParticipantID);
	///�ͻ�����
	b.append("ClientID", pOrder->ClientID);
	///��Լ�ڽ������Ĵ���
	b.append("ExchangeInstID", pOrder->ExchangeInstID);
	///����������Ա����
	b.append("TraderID", pOrder->TraderID);
	///��װ���
	b.append("InstallID", pOrder->InstallID);
	///�����ύ״̬
	b.append("OrderSubmitStatus", pOrder->OrderSubmitStatus);
	///������ʾ���
	b.append("NotifySequence", pOrder->NotifySequence);
	///������
	b.append("TradingDay", pOrder->TradingDay);
	///������
	b.append("SettlementID", pOrder->SettlementID);
	///�������
	b.append("OrderSysID", pOrder->OrderSysID);
	///������Դ
	b.append("OrderSource", pOrder->OrderSource);
	///����״̬
	stringstream ss;
	string OrderStatus;
	ss << pOrder->OrderStatus;
	ss >> OrderStatus;
	b.append("OrderStatus", OrderStatus);
	///��������
	b.append("OrderType", pOrder->OrderType);
	///��ɽ�����
	b.append("VolumeTraded", pOrder->VolumeTraded);
	///ʣ������
	b.append("VolumeTotal", pOrder->VolumeTotal);
	///��������
	b.append("InsertDate", pOrder->InsertDate);
	///ί��ʱ��
	b.append("InsertTime", pOrder->InsertTime);
	///����ʱ��
	b.append("ActiveTime", pOrder->ActiveTime);
	///����ʱ��
	b.append("SuspendTime", pOrder->SuspendTime);
	///����޸�ʱ��
	b.append("UpdateTime", pOrder->UpdateTime);
	///����ʱ��
	b.append("CancelTime", pOrder->CancelTime);
	///����޸Ľ���������Ա����
	b.append("ActiveTraderID", pOrder->ActiveTraderID);
	///�����Ա���
	b.append("ClearingPartID", pOrder->ClearingPartID);
	///���
	b.append("SequenceNo", pOrder->SequenceNo);
	///ǰ�ñ��
	b.append("FrontID", pOrder->FrontID);
	///�Ự���
	b.append("SessionID", pOrder->SessionID);
	///�û��˲�Ʒ��Ϣ
	b.append("UserProductInfo", pOrder->UserProductInfo);
	///״̬��Ϣ
	b.append("StatusMsg", pOrder->StatusMsg);
	///�û�ǿ����־
	b.append("UserForceClose", pOrder->UserForceClose);
	///�����û�����
	b.append("ActiveUserID", pOrder->ActiveUserID);
	///���͹�˾�������
	b.append("BrokerOrderSeq", pOrder->BrokerOrderSeq);
	///��ر���
	b.append("RelativeOrderSysID", pOrder->RelativeOrderSysID);
	///֣�����ɽ�����
	b.append("ZCETotalTradedVolume", pOrder->ZCETotalTradedVolume);
	///��������־
	b.append("IsSwapOrder", pOrder->IsSwapOrder);
	///Ӫҵ�����
	b.append("BranchID", pOrder->BranchID);
	///Ͷ�ʵ�Ԫ����
	b.append("InvestUnitID", pOrder->InvestUnitID);
	///�ʽ��˺�
	b.append("AccountID", pOrder->AccountID);
	///���ִ���
	b.append("CurrencyID", pOrder->CurrencyID);
	///IP��ַ
	b.append("IPAddress", pOrder->IPAddress);
	///Mac��ַ
	b.append("MacAddress", pOrder->MacAddress);
	BSONObj p = b.obj();
	conn->insert(DB_ORDERCOMBINE_COLLECTION, p);
	USER_PRINT("DBManager::DB_OrderCombine ok");
}

void User::DB_OnRspOrderAction(mongo::DBClientConnection *conn, CThostFtdcInputOrderActionField *pInputOrderAction){
	USER_PRINT("User::DB_OnRspOrderAction DB Connection!");
	USER_PRINT(conn);
	BSONObjBuilder b;
	/// ����Աid
	b.append("OperatorID", this->getTraderID());
	///���͹�˾����
	b.append("BrokerID", pInputOrderAction->BrokerID);
	///Ͷ���ߴ���
	b.append("InvestorID", pInputOrderAction->InvestorID);
	///������������
	b.append("OrderActionRef", pInputOrderAction->OrderActionRef);
	///��������
	b.append("OrderRef", pInputOrderAction->OrderRef);
	///������
	b.append("RequestID", pInputOrderAction->RequestID);
	///ǰ�ñ��
	b.append("FrontID", pInputOrderAction->FrontID);
	///�Ự���
	b.append("SessionID", pInputOrderAction->SessionID);
	///����������
	b.append("ExchangeID", pInputOrderAction->ExchangeID);
	///�������
	b.append("OrderSysID", pInputOrderAction->OrderSysID);
	///������־
	b.append("ActionFlag", pInputOrderAction->ActionFlag);
	///�۸�
	b.append("LimitPrice", pInputOrderAction->LimitPrice);
	///�����仯
	b.append("VolumeChange", pInputOrderAction->VolumeChange);
	///�û�����
	b.append("UserID", pInputOrderAction->UserID);
	///��Լ����
	b.append("InstrumentID", pInputOrderAction->InstrumentID);
	///Ͷ�ʵ�Ԫ����
	b.append("InvestUnitID", pInputOrderAction->InvestUnitID);
	///IP��ַ
	b.append("IPAddress", pInputOrderAction->IPAddress);
	///Mac��ַ
	b.append("MacAddress", pInputOrderAction->MacAddress);
	BSONObj p = b.obj();
	conn->insert(DB_ONRSPORDERACTION_COLLECTION, p);
	USER_PRINT("DBManager::DB_OnRspOrderAction ok");
} // CTP��Ϊ������������

void User::DB_OnErrRtnOrderAction(mongo::DBClientConnection *conn, CThostFtdcOrderActionField *pOrderAction){
	USER_PRINT("User::DB_OnErrRtnOrderAction DB Connection!");
	USER_PRINT(conn);
	BSONObjBuilder b;
	/// ����Աid
	b.append("OperatorID", this->getTraderID());
	///���͹�˾����
	b.append("BrokerID", pOrderAction->BrokerID);
	///Ͷ���ߴ���
	b.append("InvestorID", pOrderAction->InvestorID);
	///������������
	b.append("OrderActionRef", pOrderAction->OrderActionRef);
	///��������
	b.append("OrderRef", pOrderAction->OrderRef);
	///������
	b.append("RequestID", pOrderAction->RequestID);
	///ǰ�ñ��
	b.append("FrontID", pOrderAction->FrontID);
	///�Ự���
	b.append("SessionID", pOrderAction->SessionID);
	///����������
	b.append("ExchangeID", pOrderAction->ExchangeID);
	///�������
	b.append("OrderSysID", pOrderAction->OrderSysID);
	///������־
	b.append("ActionFlag", pOrderAction->ActionFlag);
	///�۸�
	b.append("LimitPrice", pOrderAction->LimitPrice);
	///�����仯
	b.append("VolumeChange", pOrderAction->VolumeChange);
	///��������
	b.append("ActionDate", pOrderAction->ActionDate);
	///����ʱ��
	b.append("ActionTime", pOrderAction->ActionTime);
	///����������Ա����
	b.append("TraderID", pOrderAction->TraderID);
	///��װ���
	b.append("InstallID", pOrderAction->InstallID);
	///���ر������
	b.append("OrderLocalID", pOrderAction->OrderLocalID);
	///�������ر��
	b.append("ActionLocalID", pOrderAction->ActionLocalID);
	///��Ա����
	b.append("ParticipantID", pOrderAction->ParticipantID);
	///�ͻ�����
	b.append("ClientID", pOrderAction->ClientID);
	///ҵ��Ԫ
	b.append("BusinessUnit", pOrderAction->BusinessUnit);
	///��������״̬
	b.append("OrderActionStatus", pOrderAction->OrderActionStatus);
	///�û�����
	b.append("UserID", pOrderAction->UserID);
	///״̬��Ϣ
	b.append("StatusMsg", pOrderAction->StatusMsg);
	///��Լ����
	b.append("InstrumentID", pOrderAction->InstrumentID);
	///Ӫҵ�����
	b.append("BranchID", pOrderAction->BranchID);
	///Ͷ�ʵ�Ԫ����
	b.append("InvestUnitID", pOrderAction->InvestUnitID);
	///IP��ַ
	b.append("IPAddress", pOrderAction->IPAddress);
	///Mac��ַ
	b.append("MacAddress", pOrderAction->MacAddress);
	BSONObj p = b.obj();
	conn->insert(DB_ONERRRTNORDERACTION_COLLECTION, p);
	USER_PRINT("DBManager::DB_OnErrRtnOrderAction ok");
} // ��������Ϊ��������

void User::DB_OnRspOrderInsert(mongo::DBClientConnection *conn, CThostFtdcInputOrderField *pInputOrder){
	USER_PRINT("User::DB_OnRspOrderInsert DB Connection!");
	USER_PRINT(conn);
	BSONObjBuilder b;
	/// ����Աid
	b.append("OperatorID", this->getTraderID());
	///���͹�˾����
	b.append("BrokerID", pInputOrder->BrokerID);
	///Ͷ���ߴ���
	b.append("InvestorID", pInputOrder->InvestorID);
	///��Լ����
	b.append("InstrumentID", pInputOrder->InstrumentID);
	///��������
	b.append("OrderRef", pInputOrder->OrderRef);
	///�û�����
	b.append("UserID", pInputOrder->UserID);
	///�����۸�����
	b.append("OrderPriceType", pInputOrder->OrderPriceType);
	///��������
	b.append("Direction", pInputOrder->Direction);
	///��Ͽ�ƽ��־
	b.append("CombOffsetFlag", pInputOrder->CombOffsetFlag);
	///���Ͷ���ױ���־
	b.append("CombHedgeFlag", pInputOrder->CombHedgeFlag);
	///�۸�
	b.append("LimitPrice", pInputOrder->LimitPrice);
	///����
	b.append("VolumeTotalOriginal", pInputOrder->VolumeTotalOriginal);
	///��Ч������
	b.append("TimeCondition", pInputOrder->TimeCondition);
	///GTD����
	b.append("GTDDate", pInputOrder->GTDDate);
	///�ɽ�������
	b.append("VolumeCondition", pInputOrder->VolumeCondition);
	///��С�ɽ���
	b.append("MinVolume", pInputOrder->MinVolume);
	///��������
	b.append("ContingentCondition", pInputOrder->ContingentCondition);
	///ֹ���
	b.append("StopPrice", pInputOrder->StopPrice);
	///ǿƽԭ��
	b.append("ForceCloseReason", pInputOrder->ForceCloseReason);
	///�Զ������־
	b.append("IsAutoSuspend", pInputOrder->IsAutoSuspend);
	///ҵ��Ԫ
	b.append("BusinessUnit", pInputOrder->BusinessUnit);
	///������
	b.append("RequestID", pInputOrder->RequestID);
	///�û�ǿ����־
	b.append("UserForceClose", pInputOrder->UserForceClose);
	///��������־
	b.append("IsSwapOrder", pInputOrder->IsSwapOrder);
	///����������
	b.append("ExchangeID", pInputOrder->ExchangeID);
	///Ͷ�ʵ�Ԫ����
	b.append("InvestUnitID", pInputOrder->InvestUnitID);
	///�ʽ��˺�
	b.append("AccountID", pInputOrder->AccountID);
	///���ִ���
	b.append("CurrencyID", pInputOrder->CurrencyID);
	///���ױ���
	b.append("ClientID", pInputOrder->ClientID);
	///IP��ַ
	b.append("IPAddress", pInputOrder->IPAddress);
	///Mac��ַ
	b.append("MacAddress", pInputOrder->MacAddress);
	
	BSONObj p = b.obj();
	conn->insert(DB_ONRSPORDERINSERT_COLLECTION, p);
	USER_PRINT("DBManager::DB_OnRspOrderInsert ok");
} // CTP��Ϊ������������


void User::DB_OnErrRtnOrderInsert(mongo::DBClientConnection *conn, CThostFtdcInputOrderField *pInputOrder){
	USER_PRINT("User::DB_OnErrRtnOrderInsert DB Connection!");
	USER_PRINT(conn);
	BSONObjBuilder b;
	/// ����Աid
	b.append("OperatorID", this->getTraderID());
	///���͹�˾����
	b.append("BrokerID", pInputOrder->BrokerID);
	///Ͷ���ߴ���
	b.append("InvestorID", pInputOrder->InvestorID);
	///��Լ����
	b.append("InstrumentID", pInputOrder->InstrumentID);
	///��������
	b.append("OrderRef", pInputOrder->OrderRef);
	///�û�����
	b.append("UserID", pInputOrder->UserID);
	///�����۸�����
	b.append("OrderPriceType", pInputOrder->OrderPriceType);
	///��������
	b.append("Direction", pInputOrder->Direction);
	///��Ͽ�ƽ��־
	b.append("CombOffsetFlag", pInputOrder->CombOffsetFlag);
	///���Ͷ���ױ���־
	b.append("CombHedgeFlag", pInputOrder->CombHedgeFlag);
	///�۸�
	b.append("LimitPrice", pInputOrder->LimitPrice);
	///����
	b.append("VolumeTotalOriginal", pInputOrder->VolumeTotalOriginal);
	///��Ч������
	b.append("TimeCondition", pInputOrder->TimeCondition);
	///GTD����
	b.append("GTDDate", pInputOrder->GTDDate);
	///�ɽ�������
	b.append("VolumeCondition", pInputOrder->VolumeCondition);
	///��С�ɽ���
	b.append("MinVolume", pInputOrder->MinVolume);
	///��������
	b.append("ContingentCondition", pInputOrder->ContingentCondition);
	///ֹ���
	b.append("StopPrice", pInputOrder->StopPrice);
	///ǿƽԭ��
	b.append("ForceCloseReason", pInputOrder->ForceCloseReason);
	///�Զ������־
	b.append("IsAutoSuspend", pInputOrder->IsAutoSuspend);
	///ҵ��Ԫ
	b.append("BusinessUnit", pInputOrder->BusinessUnit);
	///������
	b.append("RequestID", pInputOrder->RequestID);
	///�û�ǿ����־
	b.append("UserForceClose", pInputOrder->UserForceClose);
	///��������־
	b.append("IsSwapOrder", pInputOrder->IsSwapOrder);
	///����������
	b.append("ExchangeID", pInputOrder->ExchangeID);
	///Ͷ�ʵ�Ԫ����
	b.append("InvestUnitID", pInputOrder->InvestUnitID);
	///�ʽ��˺�
	b.append("AccountID", pInputOrder->AccountID);
	///���ִ���
	b.append("CurrencyID", pInputOrder->CurrencyID);
	///���ױ���
	b.append("ClientID", pInputOrder->ClientID);
	///IP��ַ
	b.append("IPAddress", pInputOrder->IPAddress);
	///Mac��ַ
	b.append("MacAddress", pInputOrder->MacAddress);
	BSONObj p = b.obj();
	conn->insert(DB_ONERRRTNORDERINSERT_COLLECTION, p);
	USER_PRINT("DBManager::DB_OnErrRtnOrderInsert ok");
} // ��������Ϊ��������

void User::DB_OnRspQryInvestorPosition(mongo::DBClientConnection *conn, CThostFtdcInvestorPositionField *pInvestorPosition){
	USER_PRINT("User::DB_OnRspQryInvestorPosition DB Connection!");
	USER_PRINT(conn);
	BSONObjBuilder b;
	/// ����Աid
	b.append("OperatorID", this->getTraderID());
	///��Լ����
	b.append("InstrumentID", pInvestorPosition->InstrumentID);
	///���͹�˾����
	b.append("BrokerID", pInvestorPosition->BrokerID);
	///Ͷ���ߴ���
	b.append("InvestorID", pInvestorPosition->InvestorID);
	///�ֲֶ�շ���
	b.append("PosiDirection", pInvestorPosition->PosiDirection);
	///Ͷ���ױ���־
	b.append("HedgeFlag", pInvestorPosition->HedgeFlag);
	///�ֲ�����
	b.append("PositionDate", pInvestorPosition->PositionDate);
	///���ճֲ�
	b.append("YdPosition", pInvestorPosition->YdPosition);
	///���ճֲ�
	b.append("Position", pInvestorPosition->Position);
	///��ͷ����
	b.append("LongFrozen", pInvestorPosition->LongFrozen);
	///��ͷ����
	b.append("ShortFrozen", pInvestorPosition->ShortFrozen);
	///���ֶ�����
	b.append("LongFrozenAmount", pInvestorPosition->LongFrozenAmount);
	///���ֶ�����
	b.append("ShortFrozenAmount", pInvestorPosition->ShortFrozenAmount);
	///������
	b.append("OpenVolume", pInvestorPosition->OpenVolume);
	///ƽ����
	b.append("CloseVolume", pInvestorPosition->CloseVolume);
	///���ֽ��
	b.append("OpenAmount", pInvestorPosition->OpenAmount);
	///ƽ�ֽ��
	b.append("CloseAmount", pInvestorPosition->CloseAmount);
	///�ֲֳɱ�
	b.append("PositionCost", pInvestorPosition->PositionCost);
	///�ϴ�ռ�õı�֤��
	b.append("PreMargin", pInvestorPosition->PreMargin);
	///ռ�õı�֤��
	b.append("UseMargin", pInvestorPosition->UseMargin);
	///����ı�֤��
	b.append("FrozenMargin", pInvestorPosition->FrozenMargin);
	///������ʽ�
	b.append("FrozenCash", pInvestorPosition->FrozenCash);
	///�����������
	b.append("FrozenCommission", pInvestorPosition->FrozenCommission);
	///�ʽ���
	b.append("CashIn", pInvestorPosition->CashIn);
	///������
	b.append("Commission", pInvestorPosition->Commission);
	///ƽ��ӯ��
	b.append("CloseProfit", pInvestorPosition->CloseProfit);
	///�ֲ�ӯ��
	b.append("PositionProfit", pInvestorPosition->PositionProfit);
	///�ϴν����
	b.append("PreSettlementPrice", pInvestorPosition->PreSettlementPrice);
	///���ν����
	b.append("SettlementPrice", pInvestorPosition->SettlementPrice);
	///������
	b.append("TradingDay", pInvestorPosition->TradingDay);
	///������
	b.append("SettlementID", pInvestorPosition->SettlementID);
	///���ֳɱ�
	b.append("OpenCost", pInvestorPosition->OpenCost);
	///��������֤��
	b.append("ExchangeMargin", pInvestorPosition->ExchangeMargin);
	///��ϳɽ��γɵĳֲ�
	b.append("CombPosition", pInvestorPosition->CombPosition);
	///��϶�ͷ����
	b.append("CombLongFrozen", pInvestorPosition->CombLongFrozen);
	///��Ͽ�ͷ����
	b.append("CombShortFrozen", pInvestorPosition->CombShortFrozen);
	///���ն���ƽ��ӯ��
	b.append("CloseProfitByDate", pInvestorPosition->CloseProfitByDate);
	///��ʶԳ�ƽ��ӯ��
	b.append("CloseProfitByTrade", pInvestorPosition->CloseProfitByTrade);
	///���ճֲ�
	b.append("TodayPosition", pInvestorPosition->TodayPosition);
	///��֤����
	b.append("MarginRateByMoney", pInvestorPosition->MarginRateByMoney);
	///��֤����(������)
	b.append("MarginRateByVolume", pInvestorPosition->MarginRateByVolume);
	///ִ�ж���
	b.append("StrikeFrozen", pInvestorPosition->StrikeFrozen);
	///ִ�ж�����
	b.append("StrikeFrozenAmount", pInvestorPosition->StrikeFrozenAmount);
	///����ִ�ж���
	b.append("AbandonFrozen", pInvestorPosition->AbandonFrozen);
	BSONObj p = b.obj();
	conn->insert(DB_ONRSPQRYINVESTORPOSITION, p);
	USER_PRINT("DBManager::DB_OnRspQryInvestorPosition ok");
} // �ֲ���Ϣ

/// ���ÿ���
int User::getOn_Off() {
	return this->on_off;
}
void User::setOn_Off(int on_off) {
	this->on_off = on_off;
}

/// ����CTP_Manager
void User::setCTP_Manager(CTP_Manager *o_ctp) {
	this->o_ctp = o_ctp;
}
CTP_Manager * User::getCTP_Manager() {
	return this->o_ctp;
}

void User::setIsActive(string isActive) {
	this->isActive = isActive;
}
string User::getIsActive() {
	return this->isActive;
}

void User::setTradingDay(string stg_trading_day) {
	this->trading_day = stg_trading_day;
}

string User::getTradingDay() {
	return this->trading_day;
}

void User::QueryTrade() {
	this->UserTradeSPI->QryTrade();
}

void User::QueryOrder() {
	this->UserTradeSPI->QryOrder();
}

/// �õ����ݿ��������
DBManager * User::getDBManager() {
	return this->dbm;
}

void User::setDBManager(DBManager *dbm) {
	this->dbm = dbm;
}

int User::getSessionID() {
	return this->sid;
}

void User::setSessionID(int SessionID) {
	this->sid = SessionID;
}

list<Session *> * User::getL_Sessions() {
	return this->l_sessions;
}

void User::setL_Sessions(list<Session *> *l_sessions) {
	this->l_sessions = l_sessions;
}