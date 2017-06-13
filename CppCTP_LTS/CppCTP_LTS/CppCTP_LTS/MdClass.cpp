
#include <string>
#include <iostream>
#include "Include/MdClass.h"
using namespace std;
using std::cout;
using std::endl;

MdClass::MdClass(char *front_address, char *broker_id, char *user_id, char *password, const char *pszFlowPath)
{
	std::cout << "MdClass::MdClass()" << std::endl;

	//����API��ʼ��
	pMD = CSecurityFtdcMdApi::CreateFtdcMdApi(pszFlowPath);

	//��������api
	pMD->RegisterSpi(this);

	//ע������ӿ�
	pMD->RegisterFront(front_address);

	//������½��Ϣ
	strcpy_s(LoginInfo.BrokerID, broker_id);
	strcpy_s(LoginInfo.UserID, user_id);
	strcpy_s(LoginInfo.Password, password);

	//cout<<"ע������ǰ�û���ַ:"<<FRONT_ADDR_MD<<endl;
	pMD->Init();
}


void MdClass::OnFrontConnected()
{
	std::cout << "MdClass::OnFrontConnected!" << std::endl;
	this->Login();
}

void MdClass::OnFrontDisconnected(int nReason)
{
	std::cout << "MdClass::OnFrontDisconnected()" << endl;
}

//��½
void MdClass::Login() {
	std::cout << "MdClass::Login()" << std::endl;
	int ReqCode = 0;
	ReqCode = pMD->ReqUserLogin(&LoginInfo, 1);
	// �������
	if (ReqCode != 0) {
		std::cout << "\tMdClass::Login() ReqUserLogin Failed!" << std::endl;
	}
}

//����
void MdClass::OnHeartBeatWarning(int nTimeLapse) {

}

//��������
void MdClass::SubMarketData(list<string> list_instrumentid, char* pExchageID) {
	std::cout << "MdClass::SubMarketData()" << std::endl;
	list<string>::iterator itor;
	char **instrumentID = new char *[list_instrumentid.size()];
	int size = list_instrumentid.size();
	int i = 0;
	const char *charResult;
	for (itor = list_instrumentid.begin(), i = 0; itor != list_instrumentid.end(); itor++, i++) {
		charResult = (*itor).c_str();
		instrumentID[i] = new char[strlen(charResult) + 1];
		strcpy(instrumentID[i], charResult);
		std::cout << "\tinstrumentID[i] = " << instrumentID[i] << std::endl;
	}
	std::cout << "\tsize = " << size << std::endl;
	std::cout << "\tpExchageID = " << pExchageID << std::endl;
	this->pMD->SubscribeMarketData(instrumentID, size, pExchageID);
}

//ȡ����������
void MdClass::UnSubMarketData(list<string> list_instrumentid, char* pExchageID) {
	std::cout << "MdClass::UnSubMarketData()" << std::endl;
	list<string>::iterator itor;
	char **instrumentID = new char *[list_instrumentid.size()];
	int size = list_instrumentid.size();
	int i = 0;
	const char *charResult;
	for (itor = list_instrumentid.begin(), i = 0; itor != list_instrumentid.end(); itor++, i++) {
		charResult = (*itor).c_str();
		instrumentID[i] = new char[strlen(charResult) + 1];
		strcpy(instrumentID[i], charResult);
	}
	this->pMD->UnSubscribeMarketData(instrumentID, size, pExchageID);
}

void MdClass::OnRspError(CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::cout << "MdClass::OnRspError()" << std::endl;
}

// ��½�ص�
void MdClass::OnRspUserLogin(CSecurityFtdcRspUserLoginField *pRspUserLogin, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::cout << "MdClass::OnRspUserLogin()" << std::endl;
	if (!IsErrorRspInfo(pRspInfo) && pRspUserLogin) {
		std::cout << "\tMdClass::OnRspUserLogin() Success!" << std::endl;
		list<string> list_instrumentid;
		string instrument_id = "000001";
		list_instrumentid.push_back(instrument_id);
		char* pExchageID = "SSE";
		this->SubMarketData(list_instrumentid, pExchageID);
	}
	else {
		std::cout << "\tMdClass::OnRspUserLogin() Failed!" << std::endl;
	}
}


void MdClass::OnRspUserLogout(CSecurityFtdcUserLogoutField *pUserLogout, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::cout << "MdClass::OnRspUserLogout()" << std::endl;
}

void MdClass::OnRspSubMarketData(CSecurityFtdcSpecificInstrumentField *pSpecificInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::cout << "MdClass::OnRspSubMarketData()" << std::endl;
	if (!IsErrorRspInfo(pRspInfo) && pSpecificInstrument) {
		std::cout << "\t[" << pSpecificInstrument->InstrumentID << "]" << std::endl;
		std::cout << "\t[" << pSpecificInstrument->ExchangeID << "] ���� �ɹ�!" << std::endl;
	}
}

void MdClass::OnRspUnSubMarketData(CSecurityFtdcSpecificInstrumentField *pSpecificInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	std::cout << "MdClass::OnRspUnSubMarketData()" << std::endl;
	if (!IsErrorRspInfo(pRspInfo) && pSpecificInstrument) {
		std::cout << "\t[" << pSpecificInstrument->InstrumentID << "] ȡ������ �ɹ�!" << std::endl;
	}
}




void MdClass::OnRtnDepthMarketData(CSecurityFtdcDepthMarketDataField *pDepthMarketData)
{
	std::cout << "������Ϣ:" << std::endl;
	if (pDepthMarketData != NULL) {
		///������
		std::cout << "\t������ = " << pDepthMarketData->TradingDay << std::endl;
		///��Լ����
		std::cout << "\t��Լ���� = " << pDepthMarketData->InstrumentID << std::endl;
		///����������
		std::cout << "\t���������� = " << pDepthMarketData->ExchangeID << std::endl;
		///��Լ�ڽ������Ĵ���
		std::cout << "\t��Լ�ڽ������Ĵ��� = " << pDepthMarketData->ExchangeInstID << std::endl;
		///���¼�
		std::cout << "\t���¼� = " << pDepthMarketData->LastPrice << std::endl;
		//����޸�ʱ��
		std::cout << "\t����޸�ʱ�� = " << pDepthMarketData->UpdateTime << std::endl;
		///����޸ĺ���
		std::cout << "\t����޸ĺ��� = " << pDepthMarketData->UpdateMillisec << std::endl;
	}
}

//���������Ƿ񱨴�
bool MdClass::IsErrorRspInfo(CSecurityFtdcRspInfoField *pRspInfo) {
	// ���ErrorID != 0, ˵���յ��˴������Ӧ
	bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (bResult) {
		cerr << "\t--->>> ErrorID = " << pRspInfo->ErrorID << ", ErrorMsg = " << pRspInfo->ErrorMsg << endl;
	}
	return bResult;
}

MdClass::~MdClass() {
	pMD->Release();
}