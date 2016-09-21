#include "CTP_Manager.h"
#include "User.h"
#include "Utils.h"
#include "Debug.h"


CTP_Manager::CTP_Manager() {
	this->dbm = new DBManager();
	this->l_user = new list<User *>();
	this->l_trader = new list<string>();
	this->l_obj_trader = new list<Trader *>();
	this->l_strategys = new list<Strategy *>();
	this->l_instrument = new list<string>();
	this->l_unsubinstrument = new list<string>();
}

bool CTP_Manager::CheckIn(Login *login) {
	
}

/// trader login
bool CTP_Manager::TraderLogin(string traderid, string password) {
	return this->dbm->FindTraderByTraderIdAndPassword(traderid, password);
}

/// admin login
bool CTP_Manager::AdminLogin(string adminid, string password) {
	return this->dbm->FindAdminByAdminIdAndPassword(adminid, password);
}

User * CTP_Manager::CreateAccount(User *user) {
	USER_PRINT("CTP_Manager::CreateAccount");
	//tcp://180.168.146.187:10030 //24H
	//tcp://180.168.146.187:10000 //ʵ�̷���

	if (user != NULL) {
		TdSpi *tdspi = new TdSpi();

		//User *user = new User(td_frontAddress, td_broker, td_user, td_pass, td_user, TraderID);

		/*����api*/
		string flowpath = "conn/td/" + user->getUserID() + "/";
		int flag = Utils::CreateFolder(flowpath.c_str());
		if (flag != 0) {
			cout << "�޷������û����ļ�!" << endl;
			return NULL;
		}
		else {
			CThostFtdcTraderApi *tdapi = CThostFtdcTraderApi::CreateFtdcTraderApi(flowpath.c_str());
			cout << tdapi << endl;
			if (!tdapi) {
				return NULL;
			}
			else {
				user->setUserTradeAPI(tdapi);
				user->setUserTradeSPI(tdspi);
			}
		}

		sleep(1);
		user->getUserTradeSPI()->Connect(user);
		sleep(1);
		user->getUserTradeSPI()->Login(user);
		sleep(1);
		user->getUserTradeSPI()->QrySettlementInfoConfirm(user);

		
		//tdspi->QrySettlementInfo(user);
		//sleep(6);
		//string instrument = "cu1609";
		//user->getUserTradeSPI()->OrderInsert(user, const_cast<char *>(instrument.c_str()), '0', '0', 20, 39000, "1");
	}

	return user;
}

MdSpi * CTP_Manager::CreateMd(string md_frontAddress, string md_broker, string md_user, string md_pass) {
	MdSpi *mdspi = NULL;
	CThostFtdcMdApi *mdapi = NULL;
	string conn_md_frontAddress = md_frontAddress;
	md_frontAddress = md_frontAddress.substr(6, md_frontAddress.length() - 1);
	int pos = md_frontAddress.find_first_of(':', 0);
	md_frontAddress.replace(pos, 1, "_");

	/*����api*/
	string flowpath = "conn/md/" + md_frontAddress + "/";
	int flag = Utils::CreateFolder(flowpath.c_str());
	if (flag != 0) {
		cout << "�޷������������ļ�!" << endl;
		return NULL;
	} else {
		mdapi = CThostFtdcMdApi::CreateFtdcMdApi(flowpath.c_str());
		mdspi = new MdSpi(mdapi);
	}
	USER_PRINT(const_cast<char *>(conn_md_frontAddress.c_str()));
	mdspi->Connect(const_cast<char *>(conn_md_frontAddress.c_str()));
	sleep(1);
	mdspi->Login(const_cast<char *>(md_broker.c_str()), const_cast<char *>(md_user.c_str()), const_cast<char *>(md_pass.c_str()));

	return mdspi;
}

/// �ͷ�
void CTP_Manager::ReleaseAccount(User *user) {
	if (user) {
		// �ͷ�UserApi
		if (user->getUserTradeAPI())
		{
			user->getUserTradeAPI()->RegisterSpi(NULL);
			user->getUserTradeAPI()->Release();
			user->setUserTradeAPI(NULL);
		}
		// �ͷ�UserSpiʵ��   
		if (user->getUserTradeSPI())
		{
			delete user->getUserTradeSPI();
			user->setUserTradeSPI(NULL);
		}
	}
}

/// ��������
void CTP_Manager::SubmarketData(MdSpi *mdspi, list<string> *l_instrument) {
	if (mdspi && (l_instrument->size() > 0)) {
		mdspi->SubMarket(l_instrument);
	}
}

/// �˶���Լ
void CTP_Manager::UnSubmarketData(MdSpi *mdspi, string instrumentID, list<string > *l_unsubinstrument) {
	if (mdspi && (this->l_instrument->size() > 0)) {
		/// �Ӻ�Լ�б���ɾ��һ��
		this->delSubInstrument(instrumentID, this->l_instrument);
		/// ͳ�ƺ�Լ�ĸ���
		int count = this->calInstrument(instrumentID, this->l_instrument);
		/// �����Լ����Ϊ0,�����˶�
		if (count == 0) {
			this->l_unsubinstrument->push_back(instrumentID);
			mdspi->UnSubMarket(this->l_unsubinstrument);
		}
		
	}
}

/// ��Ӷ��ĺ�Լ
list<string> * CTP_Manager::addSubInstrument(string instrumentID, list<string > *l_instrument) {
	l_instrument->push_back(instrumentID);
	USER_PRINT(l_instrument->size());
	return l_instrument;
}

/// ɾ�����ĺ�Լ
list<string> * CTP_Manager::delSubInstrument(string instrumentID, list<string > *l_instrument) {
	USER_PRINT(l_instrument->size());
	if (l_instrument->size() > 0) {
		list<string>::iterator itor;
		for (itor = l_instrument->begin(); itor != l_instrument->end();) {
			cout << *itor << endl;
			if (*itor == instrumentID) {
				itor = l_instrument->erase(itor);
				USER_PRINT("Remove OK");
				//break;
				USER_PRINT(l_instrument->size());
				USER_PRINT("CTP_Manager::delInstrument finish");
				return l_instrument;
			}
			else {
				itor++;
			}
		}
	}
	USER_PRINT(l_instrument->size());
	USER_PRINT("CTP_Manager::delInstrument finish");
	return l_instrument;
}

/// ͳ�ƺ�Լ����
int CTP_Manager::calInstrument(string instrumentID, list<string> *l_instrument) {
	int count = 0;
	if (l_instrument->size() > 0) {
		list<string>::iterator itor;
		for (itor = l_instrument->begin(); itor != l_instrument->end(); itor++) {
			cout << *itor << endl;
			if ((*itor) == instrumentID) {
				count++;
			}
		}
	}
	else {
		count = 0;
	}
	return count;
}

/// �˶���Լ����
list<string> CTP_Manager::addUnSubInstrument(string instrumentID, list<string> l_instrument) {
	if (l_instrument.size() > 0) {
		l_instrument.clear();
	}
	l_instrument.push_back(instrumentID);
	return l_instrument;
}

/// �õ�l_instrument
list<string> * CTP_Manager::getL_Instrument() {
	return this->l_instrument;
}

/// �õ����ݿ��������
DBManager * CTP_Manager::getDBManager() {
	return this->dbm;
}

/// ����l_trader
void CTP_Manager::addTraderToLTrader(string trader) {
	this->l_trader->push_back(trader);
}

/// ��ȡtrader�Ƿ���l_trader��
bool CTP_Manager::checkInLTrader(string trader) {
	bool flag = false;
	list<string>::iterator Itor;
	for (Itor = this->l_trader->begin(); Itor != this->l_trader->end(); Itor++) {
		if (*Itor == trader) {
			flag = true;
		}
	}
	return flag;
}

/// �õ�l_trader
list<string> *CTP_Manager::getL_Trader() {
	return this->l_trader;
}

/// �õ�l_obj_trader
list<Trader *> * CTP_Manager::getL_Obj_Trader() {
	return this->l_obj_trader;
}

/// �Ƴ�Ԫ��
void CTP_Manager::removeFromLTrader(string trader) {
	list<string>::iterator Itor;
	for (Itor = this->l_trader->begin(); Itor != this->l_trader->end();) {
		if (*Itor == trader) {
			Itor = this->l_trader->erase(Itor);
		}
		else {
			Itor++;
		}
	}
}

/// �����û��ڻ��˻�
void CTP_Manager::addFuturesToTrader(string traderid, User *user) {
	map<string, list<User *> *>::iterator m_itor;
	m_itor = this->m_trader.find(traderid);
	if (m_itor == (this->m_trader.end())) {
		cout << "we do not find" << traderid << endl;
		list<User *> *l_user = new list<User *>();
		this->m_trader.insert(pair<string, list<User *> *>(traderid, l_user));
	}
	else {
		cout << "we find " << traderid << endl;
		this->m_trader[traderid]->push_back(user);
	}
		
}

/// ��ȡ�ڻ��˻�map
map<string, list<User *> *> CTP_Manager::getTraderMap() {
	return this->m_trader;
}

/// �����û��б�
list<User *> *CTP_Manager::getL_User() {
	return this->l_user;
}

/// �õ�strategy_list
list<Strategy *> * CTP_Manager::getListStrategy() {
	return this->l_strategys;
}

/// ����strategy_list
void CTP_Manager::setListStrategy(list<Strategy *> *l_strategys) {
	this->l_strategys = l_strategys;
}

/// ����mdspi
void CTP_Manager::setMdSpi(MdSpi *mdspi) {
	this->mdspi = mdspi;
}

/// ���mdspi
MdSpi * CTP_Manager::getMdSpi() {
	return this->mdspi;
}

/// ��ʼ��
void CTP_Manager::init() {
	/// ���ݿ��ѯ���е�Trader
	this->dbm->getAllTrader(this->l_trader);

	/// ��ѯ���еĲ���
	this->dbm->getAllStragegy(this->l_strategys);

	/// ��ѯ���е��ڻ��˻�
	this->dbm->getAllFutureAccount(this->l_user);

	/// �󶨲���,���԰󶨵���Ӧ�ڻ��˻���
	list<User *>::iterator user_itor;
	list<Strategy *>::iterator stg_itor;
	for (user_itor = this->l_user->begin(); user_itor != this->l_user->end(); user_itor++) { // ����User
		USER_PRINT((*user_itor)->getUserID());
		for (stg_itor = this->l_strategys->begin(); stg_itor != this->l_strategys->end(); stg_itor++) { // ����Strategy
			USER_PRINT((*stg_itor)->getUserID());
			if ((*stg_itor)->getUserID() == (*user_itor)->getUserID()) {
				USER_PRINT("Strategy Bind To User");
				(*user_itor)->addStrategyToList((*stg_itor));
			}
		}
		/// ������ֵ�����TD��ʼ��
		this->CreateAccount((*user_itor));
	}

	/// ����User,��TdSpi����Strategy_List��ֵ
	for (user_itor = this->l_user->begin(); user_itor != this->l_user->end(); user_itor++) { // ����User
		USER_PRINT((*user_itor)->getUserID());
		(*user_itor)->getUserTradeSPI()->setListStrategy(this->l_strategys);
	}

	/// �����ʼ��
	MarketConfig *mc = this->dbm->getOneMarketConfig();
	if (mc != NULL) {
		this->mdspi = this->CreateMd(mc->getMarketFrontAddr(), mc->getBrokerID(), mc->getUserID(), mc->getPassword());
		if (this->mdspi != NULL) {
			/// ��mdspi��ֵstrategys
			this->mdspi->setListStrategy(this->l_strategys);
			/// ���ĺ�Լ
			for (stg_itor = this->l_strategys->begin(); stg_itor != this->l_strategys->end(); stg_itor++) { // ����Strategy
				USER_PRINT((*stg_itor)->getStgInstrumentIdA());
				USER_PRINT((*stg_itor)->getStgInstrumentIdB());
				/// ��Ӳ��Եĺ�Լ��l_instrument
				this->addSubInstrument((*stg_itor)->getStgInstrumentIdA(), this->l_instrument);
				this->addSubInstrument((*stg_itor)->getStgInstrumentIdB(), this->l_instrument);
			}
			/// ���ĺ�Լ
			this->SubmarketData(this->mdspi, this->l_instrument);
		}
	}
}