#ifndef QUANT_XTRADESTRUCT_H
#define QUANT_XTRADESTRUCT_H
#include <iostream>
#include "ThostFtdcUserApiDataType.h"

using namespace std;
using std::string;

///����
struct USER_CThostFtdcOrderField
{
	///���͹�˾����
	TThostFtdcBrokerIDType	BrokerID;
	///Ͷ���ߴ���
	TThostFtdcInvestorIDType	InvestorID;
	///��Լ����
	TThostFtdcInstrumentIDType	InstrumentID;
	///��������
	TThostFtdcOrderRefType	OrderRef;
	/*///���Ա��
	string StrategyID;*/
	///���Ա��
	char StrategyID[2];
	///�û�����
	TThostFtdcUserIDType	UserID;
	///�����۸�����
	TThostFtdcOrderPriceTypeType	OrderPriceType;
	///��������
	TThostFtdcDirectionType	Direction;
	///��Ͽ�ƽ��־
	TThostFtdcCombOffsetFlagType	CombOffsetFlag;
	///���Ͷ���ױ���־
	TThostFtdcCombHedgeFlagType	CombHedgeFlag;
	///�۸�
	TThostFtdcPriceType	LimitPrice;
	///����
	TThostFtdcVolumeType	VolumeTotalOriginal;
	///��Ч������
	TThostFtdcTimeConditionType	TimeCondition;
	///GTD����
	TThostFtdcDateType	GTDDate;
	///�ɽ�������
	TThostFtdcVolumeConditionType	VolumeCondition;
	///��С�ɽ���
	TThostFtdcVolumeType	MinVolume;
	///��������
	TThostFtdcContingentConditionType	ContingentCondition;
	///ֹ���
	TThostFtdcPriceType	StopPrice;
	///ǿƽԭ��
	TThostFtdcForceCloseReasonType	ForceCloseReason;
	///�Զ������־
	TThostFtdcBoolType	IsAutoSuspend;
	///ҵ��Ԫ
	TThostFtdcBusinessUnitType	BusinessUnit;
	///������
	TThostFtdcRequestIDType	RequestID;
	///���ر������
	TThostFtdcOrderLocalIDType	OrderLocalID;
	///����������
	TThostFtdcExchangeIDType	ExchangeID;
	///��Ա����
	TThostFtdcParticipantIDType	ParticipantID;
	///�ͻ�����
	TThostFtdcClientIDType	ClientID;
	///��Լ�ڽ������Ĵ���
	TThostFtdcExchangeInstIDType	ExchangeInstID;
	///����������Ա����
	TThostFtdcTraderIDType	TraderID;
	///��װ���
	TThostFtdcInstallIDType	InstallID;
	///�����ύ״̬
	TThostFtdcOrderSubmitStatusType	OrderSubmitStatus;
	///������ʾ���
	TThostFtdcSequenceNoType	NotifySequence;
	///������
	TThostFtdcDateType	TradingDay;
	///��¼��������
	TThostFtdcDateType	TradingDayRecord;
	///������
	TThostFtdcSettlementIDType	SettlementID;
	///�������
	TThostFtdcOrderSysIDType	OrderSysID;
	///������Դ
	TThostFtdcOrderSourceType	OrderSource;
	///����״̬
	TThostFtdcOrderStatusType	OrderStatus;
	///��������
	TThostFtdcOrderTypeType	OrderType;
	///��ɽ�����
	TThostFtdcVolumeType	VolumeTraded;
	///���γɽ���
	TThostFtdcVolumeType	VolumeTradedBatch;
	///ʣ������
	TThostFtdcVolumeType	VolumeTotal;
	///��������
	TThostFtdcDateType	InsertDate;
	///ί��ʱ��
	TThostFtdcTimeType	InsertTime;
	///����ʱ��
	TThostFtdcTimeType	ActiveTime;
	///����ʱ��
	TThostFtdcTimeType	SuspendTime;
	///����޸�ʱ��
	TThostFtdcTimeType	UpdateTime;
	///����ʱ��
	TThostFtdcTimeType	CancelTime;
	///����޸Ľ���������Ա����
	TThostFtdcTraderIDType	ActiveTraderID;
	///�����Ա���
	TThostFtdcParticipantIDType	ClearingPartID;
	///���
	TThostFtdcSequenceNoType	SequenceNo;
	///ǰ�ñ��
	TThostFtdcFrontIDType	FrontID;
	///�Ự���
	TThostFtdcSessionIDType	SessionID;
	///�û��˲�Ʒ��Ϣ
	TThostFtdcProductInfoType	UserProductInfo;
	///״̬��Ϣ
	TThostFtdcErrorMsgType	StatusMsg;
	///�û�ǿ����־
	TThostFtdcBoolType	UserForceClose;
	///�����û�����
	TThostFtdcUserIDType	ActiveUserID;
	///���͹�˾�������
	TThostFtdcSequenceNoType	BrokerOrderSeq;
	///��ر���
	TThostFtdcOrderSysIDType	RelativeOrderSysID;
	///֣�����ɽ�����
	TThostFtdcVolumeType	ZCETotalTradedVolume;
	///��������־
	TThostFtdcBoolType	IsSwapOrder;
	///Ӫҵ�����
	TThostFtdcBranchIDType	BranchID;
	///Ͷ�ʵ�Ԫ����
	TThostFtdcInvestUnitIDType	InvestUnitID;
	///�ʽ��˺�
	TThostFtdcAccountIDType	AccountID;
	///���ִ���
	TThostFtdcCurrencyIDType	CurrencyID;
	///IP��ַ
	TThostFtdcIPAddressType	IPAddress;
	///Mac��ַ
	TThostFtdcMacAddressType	MacAddress;

	//USER_CThostFtdcOrderField(){}
	//~USER_CThostFtdcOrderField(){}

};

#endif