#include "PositionDetail.h"

void PositionDetail::setInstrumentID(string	InstrumentID){
	this->InstrumentID = InstrumentID;
}
string PositionDetail::getInstrumentID(){
	return this->InstrumentID;
}

void PositionDetail::setOrderRef(string OrderRef){
	this->OrderRef = OrderRef;
}
string PositionDetail::getOrderRef(){
	return this->OrderRef;
}

void PositionDetail::setUserID(string UserID){
	this->UserID = UserID;
}
string PositionDetail::getUserID(){
	return this->UserID;
}

void PositionDetail::setDirection(int Direction){
	this->Direction = Direction;
}
int PositionDetail::getDirection(){
	return this->Direction;
}

///��Ͽ�ƽ��־
void PositionDetail::setCombOffsetFlag(string CombOffsetFlag){
	this->CombOffsetFlag = CombOffsetFlag;
}
string	PositionDetail::getCombOffsetFlag(){
	return this->CombOffsetFlag;
}

///���Ͷ���ױ���־
void PositionDetail::setCombHedgeFlag(string CombHedgeFlag){
	this->CombHedgeFlag = CombHedgeFlag;
}
string	PositionDetail::getCombHedgeFlag() {
	return this->CombHedgeFlag;
}

///�۸�
void PositionDetail::setLimitPrice(double LimitPrice) {
	this->LimitPrice = LimitPrice;
}

double PositionDetail::getLimitPrice() {
	return this->getLimitPrice();
}

///����
void PositionDetail::setVolumeTotalOriginal(int	VolumeTotalOriginal){
	this->VolumeTotalOriginal = VolumeTotalOriginal;
}
int	PositionDetail::getVolumeTotalOriginal(){
	return this->VolumeTotalOriginal;
}

///������
void PositionDetail::setTradingDay(string TradingDay){
	this->TradingDay = TradingDay;
}
string	PositionDetail::getTradingDay(){
	return this->TradingDay;
}

///����״̬
void PositionDetail::setOrderStatus(int OrderStatus){
	this->OrderStatus = OrderStatus;
}

int PositionDetail::getOrderStatus(){
	return this->OrderStatus;
}

///��ɽ�����
void PositionDetail::setVolumeTraded(int VolumeTraded){
	this->VolumeTraded = VolumeTraded;
}
int	PositionDetail::getVolumeTraded(){
	return this->VolumeTraded;
}

///ʣ������
void PositionDetail::setVolumeTotal(int VolumeTotal){
	this->VolumeTotal = VolumeTotal;
}

int	PositionDetail::getVolumeTotal() {
	return this->VolumeTotal;
}

///��������
void PositionDetail::setInsertDate(string InsertDate){
	this->InsertDate = InsertDate;
}

string PositionDetail::getInsertDate() {
	return this->InsertDate;
}

///ί��ʱ��
void PositionDetail::setInsertTime(string InsertTime){
	this->InsertTime = InsertTime;
}

string PositionDetail::getInsertTime(){
	return this->InsertTime;
}

///���Ա��(�������)
void PositionDetail::setStrategyID(string StrategyID){
	this->StrategyID = StrategyID;
}

string PositionDetail::getStrategyID(){
	return this->StrategyID;
}

///һ���ɽ���
void PositionDetail::setVolumeTradedBatch(int VolumeTradedBatch){
	this->VolumeTradedBatch = VolumeTradedBatch;
}

int PositionDetail::getVolumeTradedBatch(){
	return this->VolumeTradedBatch;
}