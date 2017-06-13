#ifndef QUANT_POSITION_DETAIL_H
#define QUANT_POSITION_DETAIL_H

#include <iostream>

using namespace std;
using std::string;

class PositionDetail
{
public:
	
	void setInstrumentID(string	InstrumentID);
	string getInstrumentID();

	void setOrderRef(string OrderRef);
	string getOrderRef();

	void setUserID(string UserID);
	string getUserID();

	void setDirection(int Direction);
	int getDirection();

	///��Ͽ�ƽ��־
	void setCombOffsetFlag(string CombOffsetFlag);
	string	getCombOffsetFlag();

	///���Ͷ���ױ���־
	void setCombHedgeFlag(string CombHedgeFlag);
	string	getCombHedgeFlag();

	///�۸�
	void setLimitPrice(double LimitPrice);
	double getLimitPrice();

	///����
	void setVolumeTotalOriginal(int	VolumeTotalOriginal);
	int	getVolumeTotalOriginal();

	///������
	void setTradingDay(string TradingDay);
	string	getTradingDay();

	///����״̬
	void	setOrderStatus(int OrderStatus);
	int	getOrderStatus();

	///��ɽ�����
	void	setVolumeTraded(int VolumeTraded);
	int	getVolumeTraded();

	///ʣ������
	void	setVolumeTotal(int VolumeTotal);
	int	getVolumeTotal();

	///��������
	void setInsertDate(string InsertDate);
	string	getInsertDate();

	///ί��ʱ��
	void setInsertTime(string InsertTime);
	string	getInsertTime();

	///���Ա��(�������)
	void setStrategyID(string StrategyID);
	string getStrategyID();

	///һ���ɽ���
	void setVolumeTradedBatch(int VolumeTradedBatch);
	int getVolumeTradedBatch();

	void setIsActive(string isActive);
	string getIsActive();

private:
	///��Լ����
	string	InstrumentID;
	///��������
	string	OrderRef;
	///�û�����
	string	UserID;
	///��������
	int	Direction;
	///��Ͽ�ƽ��־
	string	CombOffsetFlag;
	///���Ͷ���ױ���־
	string	CombHedgeFlag;
	///�۸�
	double	LimitPrice;
	///����
	int	VolumeTotalOriginal;
	///������
	string	TradingDay;
	///����״̬
	int	OrderStatus;
	///��ɽ�����
	int	VolumeTraded;
	///ʣ������
	int	VolumeTotal;
	///��������
	string	InsertDate;
	///ί��ʱ��
	string	InsertTime;
	///���Ա��(�������)
	string StrategyID;
	///һ���ɽ���
	int VolumeTradedBatch;
	///�Ƿ񼤻�
	string isActive;
};

#endif