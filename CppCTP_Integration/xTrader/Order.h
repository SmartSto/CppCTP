#ifndef QUANT_CTP_ORDER_H
#define QUANT_CTP_ORDER_H

#include <string>

using namespace std;
using std::string;

class Order {
public:
	Order();
	~Order();

	string getBrokerID();
	void setBrokerID(string brokerID);
	string getInvestorID();
	void setInvestorID(string investorID);
	string getInstrumentID();
	void setInstrumentID(string instrumentID);
	string getOrderRef();
	void setOrderRef(string orderRef);
	string getUserID();
	void setUserID(string userID);
	char getOrderPriceType();
	void setOrderPriceType(char orderPriceType);
	char getDirection();
	void setDirection(char direction);
	string getCombOffsetFlag();
	void setCombOffsetFlag(string combOffsetFlag);
	string getCombHedgeFlag();
	void setCombHedgeFlag(string combHedgeFlag);
	double getLimitPrice();
	void setLimitPrice(double limitPrice);
	int getVolumeTotalOriginal();
	void setVolumeTotalOriginal(int volumeTotalOriginal);
	char getTimeCondition();
	void setTimeCondition(char timeCondition);
	string getGTDDate();
	void setGTDDate(string gTDDate);
	char getVolumeCondition();
	void setVolumeCondition(char volumeCondition);
	int getMinVolume();
	void setMinVolume(int minVolume);
	char getContingentCondition();
	void setContingentCondition(char contingentCondition);
	double getStopPrice();
	void setStopPrice(double stopPrice);
	char getForceCloseReason();
	void setForceCloseReason(char forceCloseReason);
	int getIsAutoSuspend();
	void setIsAutoSuspend(int isAutoSuspend);
	string getBusinessUnit();
	void setBusinessUnit(string businessUnit);
	int getRequestID();
	void setRequestID(int requestID);
	string getOrderLocalID();
	void setOrderLocalID(string orderLocalID);
	string getExchangeID();
	void setExchangeID(string exchangeID);
	string getParticipantID();
	void setParticipantID(string participantID);
	string getClientID();
	void setClientID(string clientID);
	string getExchangeInstID();
	void setExchangeInstID(string exchangeInstID);
	string getTraderID();
	void setTraderID(string traderID);
	int getInstallID();
	void setInstallID(int installID);
	char getOrderSubmitStatus();
	void setOrderSubmitStatus(char orderSubmitStatus);
	int getNotifySequence();
	void setNotifySequence(int notifySequence);
	string getTradingDay();
	void setTradingDay(string tradingDay);
	int getSettlementID();
	void setSettlementID(int settlementID);
	string getOrderSysID();
	void setOrderSysID(string orderSysID);
	char getOrderSource();
	void setOrderSource(char orderSource);
	char getOrderStatus();
	void setOrderStatus(char orderStatus);
	char getOrderType();
	void setOrderType(char orderType);
	int getVolumeTraded();
	void setVolumeTraded(int volumeTraded);
	int getVolumeTotal();
	void setVolumeTotal(int volumeTotal);
	string getInsertDate();
	void setInsertDate(string insertDate);
	string getInsertTime();
	void setInsertTime(string insertTime);
	string getActiveTime();
	void setActiveTime(string activeTime);
	string getSuspendTime();
	void setSuspendTime(string suspendTime);
	string getUpdateTime();
	void setUpdateTime(string updateTime);
	string getCancelTime();
	void setCancelTime(string cancelTime);
	string getActiveTraderID();
	void setActiveTraderID(string activeTraderID);
	string getClearingPartID();
	void setClearingPartID(string clearingPartID);
	int getSequenceNo();
	void setSequenceNo(int sequenceNo);
	int getFrontID();
	void setFrontID(int frontID);
	int getSessionID();
	void setSessionID(int sessionID);
	string getUserProductInfo();
	void setUserProductInfo(string userProductInfo);
	string getStatusMsg();
	void setStatusMsg(string statusMsg);
	int getUserForceClose();
	void setUserForceClose(int userForceClose);
	string getActiveUserID();
	void setActiveUserID(string activeUserID);
	int getBrokerOrderSeq();
	void setBrokerOrderSeq(int brokerOrderSeq);
	string getRelativeOrderSysID();
	void setRelativeOrderSysID(string relativeOrderSysID);
	int getZCETotalTradedVolume();
	void setZCETotalTradedVolume(int zCETotalTradedVolume);
	int getIsSwapOrder();
	void setIsSwapOrder(int isSwapOrder);
	string getBranchID();
	void setBranchID(string branchID);
	string getInvestUnitID();
	void setInvestUnitID(string investUnitID);
	string getAccountID();
	void setAccountID(string accountID);
	string getCurrencyID();
	void setCurrencyID(string currencyID);
	string getIPAddress();
	void setIPAddress(string iPAddress);
	string getMacAddress();
	void setMacAddress(string macAddress);
	string getSendOrderTime();
	void setSendOrderTime(string sendOrderTime);
	string getSendOrderMicrosecond();
	void setSendOrderMicrosecond(string sendOrderMicrosecond);
	string getCtpRtnOrderTime();
	void setCtpRtnOrderTime(string ctpRtnOrderTime);
	string getCtpRtnOrderMicrosecond();
	void setCtpRtnOrderMicrosecond(string ctpRtnOrderMicrosecond);
	string getExchRtnOrderTime();
	void setExchRtnOrderTime(string exchRtnOrderTime);
	string getExchRtnOrderMicrosecond();
	void setExchRtnOrderMicrosecond(string exchRtnOrderMicrosecond);
	string getOperatorID();
	void setOperatorID(string operatorID);
	string getStrategyID();
	void setStrategyID(string strategyID);

private:
	///���͹�˾����
	string BrokerID;
	///Ͷ���ߴ���
	string InvestorID;
	///��Լ����
	string InstrumentID;
	///��������
	string OrderRef;
	///�û�����
	string	UserID;
	///�����۸�����
	char OrderPriceType;
	///��������
	char Direction;
	///��Ͽ�ƽ��־
	string	CombOffsetFlag;
	///���Ͷ���ױ���־
	string	CombHedgeFlag;
	///�۸�
	double	LimitPrice;
	///����
	int VolumeTotalOriginal;
	///��Ч������
	char TimeCondition;
	///GTD����
	string GTDDate;
	///�ɽ�������
	char VolumeCondition;
	///��С�ɽ���
	int MinVolume;
	///��������
	char ContingentCondition;
	///ֹ���
	double StopPrice;
	///ǿƽԭ��
	char ForceCloseReason;
	///�Զ������־
	int IsAutoSuspend;
	///ҵ��Ԫ
	string BusinessUnit;
	///������
	int	RequestID;
	///���ر������
	string OrderLocalID;
	///����������
	string ExchangeID;
	///��Ա����
	string ParticipantID;
	///�ͻ�����
	string ClientID;
	///��Լ�ڽ������Ĵ���
	string ExchangeInstID;
	///����������Ա����
	string TraderID;
	///��װ���
	int InstallID;
	///�����ύ״̬
	char OrderSubmitStatus;
	///������ʾ���
	int NotifySequence;
	///������
	string TradingDay;
	///������
	int SettlementID;
	///�������
	string OrderSysID;
	///������Դ
	char OrderSource;
	///����״̬
	char OrderStatus;
	///��������
	char OrderType;
	///��ɽ�����
	int VolumeTraded;
	///ʣ������
	int VolumeTotal;
	///��������
	string InsertDate;
	///ί��ʱ��
	string InsertTime;
	///����ʱ��
	string ActiveTime;
	///����ʱ��
	string SuspendTime;
	///����޸�ʱ��
	string UpdateTime;
	///����ʱ��
	string CancelTime;
	///����޸Ľ���������Ա����
	string ActiveTraderID;
	///�����Ա���
	string ClearingPartID;
	///���
	int SequenceNo;
	///ǰ�ñ��
	int FrontID;
	///�Ự���
	int SessionID;
	///�û��˲�Ʒ��Ϣ
	string UserProductInfo;
	///״̬��Ϣ
	string StatusMsg;
	///�û�ǿ����־
	int UserForceClose;
	///�����û�����
	string ActiveUserID;
	///���͹�˾�������
	int BrokerOrderSeq;
	///��ر���
	string RelativeOrderSysID;
	///֣�����ɽ�����
	int ZCETotalTradedVolume;
	///��������־
	int IsSwapOrder;
	///Ӫҵ�����
	string BranchID;
	///Ͷ�ʵ�Ԫ����
	string InvestUnitID;
	///�ʽ��˺�
	string AccountID;
	///���ִ���
	string CurrencyID;
	///IP��ַ
	string IPAddress;
	///Mac��ַ
	string MacAddress;
	///����orderʱ��
	string SendOrderTime;
	///����order΢��
	string SendOrderMicrosecond;
	///CTP��Ӧʱ��
	string CtpRtnOrderTime;
	///CTP��Ӧʱ��΢��
	string CtpRtnOrderMicrosecond;
	///��������Ӧʱ��
	string ExchRtnOrderTime;
	///��������Ӧʱ��΢��
	string ExchRtnOrderMicrosecond;
	///�ͻ����˺�
	string OperatorID;
	///���Ժ�
	string StrategyID;
};

#endif