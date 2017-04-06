/////////////////////////////////////////////////////////////////////////
///@system ��һ��������ϵͳ
///@company Alex Capital Manager Co.LTD
///@file ThostFtdcTraderApi.h
///@brief �����˿ͻ��˽ӿ�
///@history 
///20060106	�Ժ��		�������ļ�
/////////////////////////////////////////////////////////////////////////

#if !defined(THOST_FTDCTRADERAPI_H)
#define THOST_FTDCTRADERAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ThostFtdcUserApiStruct.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_TRADER_API_EXPORT
#define TRADER_API_EXPORT __declspec(dllexport)
#else
#define TRADER_API_EXPORT __declspec(dllimport)
#endif
#else
#define TRADER_API_EXPORT 
#endif

class CThostFtdcTraderSpi
{
public:
	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected(){};
	
	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	///@param nReason ����ԭ��
	///        0x1001 �����ʧ��
	///        0x1002 ����дʧ��
	///        0x2001 ����������ʱ
	///        0x2002 ��������ʧ��
	///        0x2003 �յ�������
	virtual void OnFrontDisconnected(int nReason){};
		
	///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
	virtual void OnHeartBeatWarning(int nTimeLapse){};
	
	///�ͻ�����֤��Ӧ
	virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///�����������
	virtual void OnRspDataDump(CThostFtdcSettlementRefField *pSettlementRef, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��¼������Ӧ
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�ǳ�������Ӧ
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�û��������������Ӧ
	virtual void OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�ʽ��˻��������������Ӧ
	virtual void OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����¼��������Ӧ
	virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��������������Ӧ
	virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��ѯ��󱨵�������Ӧ
	virtual void OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///Ͷ���߽�����ȷ����Ӧ
	virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�������ӽ���Ա��Ӧ
	virtual void OnRspInsTrader(CThostFtdcTraderField *pTrader, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����޸Ľ���Ա��Ӧ
	virtual void OnRspUpdTrader(CThostFtdcTraderField *pTrader, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��������Ͷ������Ӧ
	virtual void OnRspInsInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����޸�Ͷ������Ӧ
	virtual void OnRspUpdInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�������ӽ��ױ�����Ӧ
	virtual void OnRspInsTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����޸Ľ��ױ�����Ӧ
	virtual void OnRspUpdTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����ɾ�����ױ�����Ӧ
	virtual void OnRspDelTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ������Ӧ
	virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ�ɽ���Ӧ
	virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯͶ���ֲ߳���Ӧ
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ�ʽ��˻���Ӧ
	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯͶ������Ӧ
	virtual void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ���ױ�����Ӧ
	virtual void OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ��Լ��֤������Ӧ
	virtual void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ��Լ����������Ӧ
	virtual void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ����Ա��Ӧ
	virtual void OnRspQryTrader(CThostFtdcTraderField *pTrader, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ��������Ӧ
	virtual void OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ��Լ��Ӧ
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ������Ӧ
	virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯͶ���߽�������Ӧ
	virtual void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯͶ���ֲ߳���ϸ��Ӧ
	virtual void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ�ͻ�֪ͨ��Ӧ
	virtual void OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ������Ϣȷ����Ӧ
	virtual void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ��Ӧ
	virtual void OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ�ֵ��۵���Ϣ��Ӧ
	virtual void OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ����ǩԼ��ϵ��Ӧ
	virtual void OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����Ӧ��
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����֪ͨ
	virtual void OnRtnOrder(CThostFtdcOrderField *pOrder) {};

	///�ɽ�֪ͨ
	virtual void OnRtnTrade(CThostFtdcTradeField *pTrade) {};

	///����¼�����ر�
	virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) {};

	///������������ر�
	virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo) {};

	///��Լ����״̬֪ͨ
	virtual void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus) {};

	///����֪ͨ
	virtual void OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo) {};

	///�����ѯǩԼ������Ӧ
	virtual void OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ����֪ͨ��Ӧ
	virtual void OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ���͹�˾���ײ�����Ӧ
	virtual void OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ���͹�˾�����㷨��Ӧ
	virtual void OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯ���ײ�����Ӧ
	virtual void OnRspQryTradingStrategy(CThostFtdcTradingStrategyField *pTradingStrategy, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�������ӽ��ײ�����Ӧ
	virtual void OnRspInsTradingStrategy(CThostFtdcTradingStrategyField *pTradingStrategy, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����޸Ľ��ײ�����Ӧ
	virtual void OnRspUpdTradingStrategy(CThostFtdcTradingStrategyField *pTradingStrategy, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����ɾ�����ײ�����Ӧ
	virtual void OnRspDelTradingStrategy(CThostFtdcTradingStrategyField *pTradingStrategy, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��������Ͷ���ֲ߳���Ӧ
	virtual void OnRspSetInvestorPosition(CThostFtdcTradingStrategyField *pTradingStrategy, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯͶ���߷�ز�����Ӧ
	virtual void OnRspQryInvestorRiskParam(CThostFtdcInvestorRiskParamField *pInvestorRiskParam, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��������Ͷ���߷�ز�����Ӧ
	virtual void OnRspInsInvestorRiskParam(CThostFtdcInvestorRiskParamField *pInvestorRiskParam, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����޸�Ͷ���߷�ز�����Ӧ
	virtual void OnRspUpdInvestorRiskParam(CThostFtdcInvestorRiskParamField *pInvestorRiskParam, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����ɾ��Ͷ���߷�ز�����Ӧ
	virtual void OnRspDelInvestorRiskParam(CThostFtdcInvestorRiskParamField *pInvestorRiskParam, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///��������Ͷ���߳�����������Ӧ
	virtual void OnRspInsInvestorOrderActionCount(CThostFtdcInvestorOrderActionCountField *pInvestorOrderActionCount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����޸�Ͷ���߳�����������Ӧ
	virtual void OnRspUpdInvestorOrderActionCount(CThostFtdcInvestorOrderActionCountField *pInvestorOrderActionCount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����ɾ��Ͷ���߳�����������Ӧ
	virtual void OnRspDelInvestorOrderActionCount(CThostFtdcInvestorOrderActionCountField *pInvestorOrderActionCount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ѯͶ���߳�����������Ӧ
	virtual void OnRspQryInvestorOrderActionCount(CThostFtdcInvestorOrderActionCountField *pInvestorOrderActionCount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ύ����Ӧ��
	virtual void OnRspSubmitFunction(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///�����ύ��ʽӦ��
	virtual void OnRspSubmitFormula(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����������Ӧ��
	virtual void OnRspCompileCode(CThostFtdcCompileCodeField *pCompileCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///����ִ�й�ʽӦ��
	virtual void OnRspExecuteFormula(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
};

class TRADER_API_EXPORT CThostFtdcTraderApi
{
public:
	///����TraderApi
	///@param pszFlowPath ����������Ϣ�ļ���Ŀ¼��Ĭ��Ϊ��ǰĿ¼
	///@return ��������UserApi
	//modify for udp marketdata
	static CThostFtdcTraderApi *CreateFtdcTraderApi(const char *pszFlowPath = "", const bool bIsUsingUdp=false);
	
	///ɾ���ӿڶ�����
	///@remark ����ʹ�ñ��ӿڶ���ʱ,���øú���ɾ���ӿڶ���
	virtual void Release() = 0;
	
	///��ʼ��
	///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
	virtual void Init() = 0;
	
	///�ȴ��ӿ��߳̽�������
	///@return �߳��˳�����
	virtual int Join() = 0;
	
	///��ȡ��ǰ������
	///@retrun ��ȡ���Ľ�����
	///@remark ֻ�е�¼�ɹ���,���ܵõ���ȷ�Ľ�����
	virtual const char *GetTradingDay() = 0;
	
	///ע��ǰ�û������ַ
	///@param pszFrontAddress��ǰ�û������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:17001���� 
	///@remark ��tcp��������Э�飬��127.0.0.1�������������ַ����17001������������˿ںš�
	virtual void RegisterFront(char *pszFrontAddress) = 0;
	
	///ע��ص��ӿ�
	///@param pSpi �����Իص��ӿ����ʵ��
	virtual void RegisterSpi(CThostFtdcTraderSpi *pSpi) = 0;
	
	///����˽������
	///@param nResumeType ˽�����ش���ʽ  
	///        THOST_TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        THOST_TERT_RESUME:���ϴ��յ�������
	///        THOST_TERT_QUICK:ֻ���͵�¼��˽����������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ�˽���������ݡ�
	virtual void SubscribePrivateTopic(THOST_TE_RESUME_TYPE nResumeType) = 0;
	
	///���Ĺ�������
	///@param nResumeType �������ش���ʽ  
	///        THOST_TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        THOST_TERT_RESUME:���ϴ��յ�������
	///        THOST_TERT_QUICK:ֻ���͵�¼�󹫹���������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ������������ݡ�
	virtual void SubscribePublicTopic(THOST_TE_RESUME_TYPE nResumeType) = 0;

	///�ͻ�����֤����
	virtual int ReqAuthenticate(CThostFtdcReqAuthenticateField *pReqAuthenticateField, int nRequestID) = 0;

	///�û���¼����
	virtual int ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLoginField, int nRequestID) = 0;
	

	///�����������
	virtual int ReqDataDump(CThostFtdcSettlementRefField *pSettlementRef, int nRequestID) = 0;

	///�ǳ�����
	virtual int ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID) = 0;

	///�û������������
	virtual int ReqUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID) = 0;

	///�ʽ��˻������������
	virtual int ReqTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, int nRequestID) = 0;

	///����¼������
	virtual int ReqOrderInsert(CThostFtdcInputOrderField *pInputOrder, int nRequestID) = 0;

	///������������
	virtual int ReqOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, int nRequestID) = 0;

	///��ѯ��󱨵���������
	virtual int ReqQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, int nRequestID) = 0;

	///Ͷ���߽�����ȷ��
	virtual int ReqSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, int nRequestID) = 0;

	///�������ӽ���Ա
	virtual int ReqInsTrader(CThostFtdcTraderField *pTrader, int nRequestID) = 0;

	///�����޸Ľ���Ա
	virtual int ReqUpdTrader(CThostFtdcTraderField *pTrader, int nRequestID) = 0;

	///��������Ͷ����
	virtual int ReqInsInvestor(CThostFtdcInvestorField *pInvestor, int nRequestID) = 0;

	///�����޸�Ͷ����
	virtual int ReqUpdInvestor(CThostFtdcInvestorField *pInvestor, int nRequestID) = 0;

	///�������ӽ��ױ���
	virtual int ReqInsTradingCode(CThostFtdcTradingCodeField *pTradingCode, int nRequestID) = 0;

	///�����޸Ľ��ױ���
	virtual int ReqUpdTradingCode(CThostFtdcTradingCodeField *pTradingCode, int nRequestID) = 0;

	///����ɾ�����ױ���
	virtual int ReqDelTradingCode(CThostFtdcTradingCodeField *pTradingCode, int nRequestID) = 0;

	///�����ѯ����
	virtual int ReqQryOrder(CThostFtdcQryOrderField *pQryOrder, int nRequestID) = 0;

	///�����ѯ�ɽ�
	virtual int ReqQryTrade(CThostFtdcQryTradeField *pQryTrade, int nRequestID) = 0;

	///�����ѯͶ���ֲ߳�
	virtual int ReqQryInvestorPosition(CThostFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID) = 0;

	///�����ѯ�ʽ��˻�
	virtual int ReqQryTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID) = 0;

	///�����ѯͶ����
	virtual int ReqQryInvestor(CThostFtdcQryInvestorField *pQryInvestor, int nRequestID) = 0;

	///�����ѯ���ױ���
	virtual int ReqQryTradingCode(CThostFtdcQryTradingCodeField *pQryTradingCode, int nRequestID) = 0;

	///�����ѯ��Լ��֤����
	virtual int ReqQryInstrumentMarginRate(CThostFtdcQryInstrumentMarginRateField *pQryInstrumentMarginRate, int nRequestID) = 0;

	///�����ѯ��Լ��������
	virtual int ReqQryInstrumentCommissionRate(CThostFtdcQryInstrumentCommissionRateField *pQryInstrumentCommissionRate, int nRequestID) = 0;

	///�����ѯ����Ա
	virtual int ReqQryTrader(CThostFtdcQryTraderField *pQryTrader, int nRequestID) = 0;

	///�����ѯ������
	virtual int ReqQryExchange(CThostFtdcQryExchangeField *pQryExchange, int nRequestID) = 0;

	///�����ѯ��Լ
	virtual int ReqQryInstrument(CThostFtdcQryInstrumentField *pQryInstrument, int nRequestID) = 0;

	///�����ѯ����
	virtual int ReqQryDepthMarketData(CThostFtdcQryDepthMarketDataField *pQryDepthMarketData, int nRequestID) = 0;

	///�����ѯͶ���߽�����
	virtual int ReqQrySettlementInfo(CThostFtdcQrySettlementInfoField *pQrySettlementInfo, int nRequestID) = 0;

	///�����ѯͶ���ֲ߳���ϸ
	virtual int ReqQryInvestorPositionDetail(CThostFtdcQryInvestorPositionDetailField *pQryInvestorPositionDetail, int nRequestID) = 0;

	///�����ѯ�ͻ�֪ͨ
	virtual int ReqQryNotice(CThostFtdcQryNoticeField *pQryNotice, int nRequestID) = 0;

	///�����ѯ������Ϣȷ��
	virtual int ReqQrySettlementInfoConfirm(CThostFtdcQrySettlementInfoConfirmField *pQrySettlementInfoConfirm, int nRequestID) = 0;

	///�����ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ
	virtual int ReqQryCFMMCTradingAccountKey(CThostFtdcQryCFMMCTradingAccountKeyField *pQryCFMMCTradingAccountKey, int nRequestID) = 0;

	///�����ѯ�ֵ��۵���Ϣ
	virtual int ReqQryEWarrantOffset(CThostFtdcQryEWarrantOffsetField *pQryEWarrantOffset, int nRequestID) = 0;

	///�����ѯ����ǩԼ��ϵ
	virtual int ReqQryAccountregister(CThostFtdcQryAccountregisterField *pQryAccountregister, int nRequestID) = 0;

	///�����ѯǩԼ����
	virtual int ReqQryContractBank(CThostFtdcQryContractBankField *pQryContractBank, int nRequestID) = 0;

	///�����ѯ����֪ͨ
	virtual int ReqQryTradingNotice(CThostFtdcQryTradingNoticeField *pQryTradingNotice, int nRequestID) = 0;

	///�����ѯ���͹�˾���ײ���
	virtual int ReqQryBrokerTradingParams(CThostFtdcQryBrokerTradingParamsField *pQryBrokerTradingParams, int nRequestID) = 0;

	///�����ѯ���͹�˾�����㷨
	virtual int ReqQryBrokerTradingAlgos(CThostFtdcQryBrokerTradingAlgosField *pQryBrokerTradingAlgos, int nRequestID) = 0;

	///�����ѯ���ײ���
	virtual int ReqQryTradingStrategy(CThostFtdcQryTradingStrategyField *pQryTradingStrategy, int nRequestID) = 0;

	///�������ӽ��ײ���
	virtual int ReqInsTradingStrategy(CThostFtdcTradingStrategyField *pTradingStrategy, int nRequestID) = 0;

	///�����޸Ľ��ײ���
	virtual int ReqUpdTradingStrategy(CThostFtdcTradingStrategyField *pTradingStrategy, int nRequestID) = 0;

	///����ɾ�����ײ���
	virtual int ReqDelTradingStrategy(CThostFtdcTradingStrategyField *pTradingStrategy, int nRequestID) = 0;

	///��������Ͷ���ֲ߳�
	virtual int ReqSetInvestorPosition(CThostFtdcTradingStrategyField *pTradingStrategy, int nRequestID) = 0;

	///�����ѯͶ���߷�ز���
	virtual int ReqQryInvestorRiskParam(CThostFtdcQryInvestorRiskParamField *pQryInvestorRiskParam, int nRequestID) = 0;

	///��������Ͷ���߷�ز���
	virtual int ReqInsInvestorRiskParam(CThostFtdcInvestorRiskParamField *pInvestorRiskParam, int nRequestID) = 0;

	///�����޸�Ͷ���߷�ز���
	virtual int ReqUpdInvestorRiskParam(CThostFtdcInvestorRiskParamField *pInvestorRiskParam, int nRequestID) = 0;

	///����ɾ��Ͷ���߷�ز���
	virtual int ReqDelInvestorRiskParam(CThostFtdcInvestorRiskParamField *pInvestorRiskParam, int nRequestID) = 0;

	///��������Ͷ���߳���������
	virtual int ReqInsInvestorOrderActionCount(CThostFtdcInvestorOrderActionCountField *pInvestorOrderActionCount, int nRequestID) = 0;

	///�����޸�Ͷ���߳���������
	virtual int ReqUpdInvestorOrderActionCount(CThostFtdcInvestorOrderActionCountField *pInvestorOrderActionCount, int nRequestID) = 0;

	///����ɾ��Ͷ���߳���������
	virtual int ReqDelInvestorOrderActionCount(CThostFtdcInvestorOrderActionCountField *pInvestorOrderActionCount, int nRequestID) = 0;

	///�����ѯͶ���߳���������
	virtual int ReqQryInvestorOrderActionCount(CThostFtdcQryInvestorOrderActionCountField *pQryInvestorOrderActionCount, int nRequestID) = 0;

	///�����ύ����
	virtual int ReqSubmitFunction(CThostFtdcSubmitFunctionField *pSubmitFunction, int nRequestID) = 0;

	///�����ύ��ʽ
	virtual int ReqSubmitFormula(CThostFtdcSubmitFormulaField *pSubmitFormula, int nRequestID) = 0;

	///����������
	virtual int ReqCompileCode(CThostFtdcCompileCodeField *pCompileCode, int nRequestID) = 0;

	///����ִ�й�ʽ
	virtual int ReqExecuteFormula(CThostFtdcExecuteFormulaField *pExecuteFormula, int nRequestID) = 0;
protected:
	~CThostFtdcTraderApi(){};
};

#endif
