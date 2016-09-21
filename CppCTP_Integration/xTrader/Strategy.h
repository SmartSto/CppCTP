#ifndef QUANT_STRATEGY_H
#define QUANT_STRATEGY_H
#include <list>
#include "Trader.h"
#include "Algorithm.h"
#include "Debug.h"
#include "DBManager.h"

using std::list;
class DBManager;

#define ALGORITHM_ONE	"01"
#define ALGORITHM_TWO	"02"
#define ALGORITHM_THREE "03"
#define ALGORITHM_FOUR	"04"

class Strategy {

public:

	Strategy();

	void get_tick(CThostFtdcDepthMarketDataField *pDepthMarketData);

	void setTrader(Trader *trader);
	Trader *getTrader();

	void setUser(User *user);
	User *getUser();

	void setStrategyId(string strategyid);
	string getStrategyId();

	void setAlgorithm(Algorithm *alg);
	Algorithm *getAlgorithm();

	void addInstrumentToList(string instrument);
	list<string> *getListInstruments();

	void setTraderID(string traderid);
	string getTraderID();

	void setUserID(string userid);
	string getUserID();

	CThostFtdcInputOrderField* getStgAOrderInsertArgs();
	void setStgAOrderInsertArgs(
		CThostFtdcInputOrderField* stgAOrderInsertArgs);

	double getStgAPriceTick();
	void setStgAPriceTick(double stgAPriceTick);

	double getStgAWaitPriceTick();
	void setStgAWaitPriceTick(double stgAWaitPriceTick);

	CThostFtdcInputOrderField* getStgBOrderInsertArgs();
	void setStgBOrderInsertArgs(
		CThostFtdcInputOrderField* stgBOrderInsertArgs);

	double getStgBPriceTick();
	void setStgBPriceTick(double stgBPriceTick);

	double getStgBWaitPriceTick();
	void setStgBWaitPriceTick(double stgBWaitPriceTick);

	double getStgBuyClose();
	void setStgBuyClose(double stgBuyClose);

	double getStgBuyOpen();
	void setStgBuyOpen(double stgBuyOpen);

	DBManager* getStgDbm();
	void setStgDbm(DBManager* stgDbm);

	CThostFtdcDepthMarketDataField* getStgInstrumentATick();
	void setStgInstrumentATick(
		CThostFtdcDepthMarketDataField* stgInstrumentATick);

	CThostFtdcDepthMarketDataField* getStgInstrumentBTick();
	void setStgInstrumentBTick(
		CThostFtdcDepthMarketDataField* stgInstrumentBTick);

	string getStgInstrumentIdA();
	void setStgInstrumentIdA(string stgInstrumentIdA);

	string getStgInstrumentIdB();
	void setStgInstrumentIdB(string stgInstrumentIdB);

	bool isStgIsActive();
	void setStgIsActive(bool stgIsActive);

	list<CThostFtdcOrderField *> *getStgListOrderPending();
	void setStgListOrderPending(list<CThostFtdcOrderField *> *stgListOrderPending);

	int getStgLots();
	void setStgLots(int stgLots);

	int getStgLotsBatch();
	void setStgLotsBatch(int stgLotsBatch);

	bool isStgOnlyClose();
	void setStgOnlyClose(bool stgOnlyClose);

	int getStgOrderActionTiresLimit();
	void setStgOrderActionTiresLimit(int stgOrderActionTiresLimit);

	string getStgOrderAlgorithm();
	void setStgOrderAlgorithm(string stgOrderAlgorithm);

	string getStgOrderRefA();
	void setStgOrderRefA(string stgOrderRefA);

	string getStgOrderRefB();
	void setStgOrderRefB(string stgOrderRefB);

	string getStgOrderRefLast();
	void setStgOrderRefLast(string stgOrderRefLast);

	int getStgPositionABuy();
	void setStgPositionABuy(int stgPositionABuy);

	int getStgPositionABuyToday();
	void setStgPositionABuyToday(int stgPositionABuyToday);

	int getStgPositionABuyYesterday();
	void setStgPositionABuyYesterday(int stgPositionABuyYesterday);

	int getStgPositionASell();
	void setStgPositionASell(int stgPositionASell);

	int getStgPositionASellToday();
	void setStgPositionASellToday(int stgPositionASellToday);

	int getStgPositionASellYesterday();
	void setStgPositionASellYesterday(int stgPositionASellYesterday);

	int getStgPositionBBuy();
	void setStgPositionBBuy(int stgPositionBBuy);

	int getStgPositionBBuyToday();
	void setStgPositionBBuyToday(int stgPositionBBuyToday);

	int getStgPositionBBuyYesterday();
	void setStgPositionBBuyYesterday(int stgPositionBBuyYesterday);

	int getStgPositionBSell();
	void setStgPositionBSell(int stgPositionBSell);

	int getStgPositionBSellToday();
	void setStgPositionBSellToday(int stgPositionBSellToday);

	int getStgPositionBSellYesterday();
	void setStgPositionBSellYesterday(int stgPositionBSellYesterday);

	double getStgSellClose();
	void setStgSellClose(double stgSellClose);

	double getStgSellOpen();
	void setStgSellOpen(double stgSellOpen);

	double getStgSpread();
	void setStgSpread(double stgSpread);

	double getStgSpreadLong();
	void setStgSpreadLong(double stgSpreadLong);

	int getStgSpreadLongVolume();
	void setStgSpreadLongVolume(int stgSpreadLongVolume);

	double getStgSpreadShift();
	void setStgSpreadShift(double stgSpreadShift);

	double getStgSpreadShort();
	void setStgSpreadShort(double stgSpreadShort);

	int getStgSpreadShortVolume();
	void setStgSpreadShortVolume(int stgSpreadShortVolume);

	double getStgStopLoss();
	void setStgStopLoss(double stgStopLoss);

	string getStgStrategyId();
	void setStgStrategyId(string stgStrategyId);

	bool isStgTradeTasking();
	void setStgTradeTasking(bool stgTradeTasking);

	string getStgTraderId();
	void setStgTraderId(string stgTraderId);

	User* getStgUser();
	void setStgUser(User* stgUser);

	string getStgUserId();
	void setStgUserId(string stgUserId);

	/************************************************************************/
	/* ������صĻر�����                                                      */
	/************************************************************************/
	//�µ�
	void OrderInsert(User *user, char *InstrumentID, char CombOffsetFlag, char Direction, int Volume, double Price, string OrderRef);

	//�µ���Ӧ
	void OnRtnOrder(CThostFtdcOrderField *pOrder);

	//�ɽ�֪ͨ
	void OnRtnTrade(CThostFtdcTradeField *pTrade);

	//�µ�������Ӧ
	void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder);

	///����¼��������Ӧ
	void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder);

	//����
	void OrderAction(string ExchangeID, string OrderRef, string OrderSysID);

	//����������Ӧ
	void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction);

	//��������
	void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction);

	//ѡ���µ��㷨
	int Select_Order_Algorithm(string stg_order_algorithm);

	//�µ��㷨1
	void Order_Algorithm_One();
	//�µ��㷨2
	void Order_Algorithm_Two();
	//�µ��㷨3
	void Order_Algorithm_Three();


private:
	Trader *trader;
	User *user;
	string strategyid;
	string userid;
	string traderid;
	Algorithm *alg;
	list<string> *l_instruments;

	DBManager *stg_DBM;			// ���ݿ�����ʵ��
	User *stg_user;				// userʵ��
	string stg_trader_id;		// ����Ա�˻�id
	string stg_user_id;			// user_id
	string stg_strategy_id;		// ����id
	string stg_order_algorithm;	// �µ��㷨ѡ���־λ
	string stg_instrument_id_A;	// ��ԼA
	string stg_instrument_id_B;	// ��ԼB

	double stg_buy_open;				// �����򿪣����൥��
	double stg_sell_close;				// ������ƽ��ƽ�൥��
	double stg_sell_open;				// �������������յ���
	double stg_buy_close;				// ������ƽ��ƽ�յ���
	double stg_spread_shift;			// �۲��ü�
	double stg_a_wait_price_tick;		// A��Լ�ҵ��ȴ���С����
	double stg_b_wait_price_tick;		// B��Լ�ҵ��ȴ���С����
	double stg_stop_loss;				// ֹ�𣬵�λΪ��С����
	int stg_lots;						// ����
	int stg_lots_batch;					// ÿ���µ�����
	bool stg_is_active;					// ���Կ���״̬
	int stg_order_action_tires_limit;	// ������������
	bool stg_only_close;				// ֻ��ƽ��

	int stg_position_a_buy_today;		// A��Լ��ֲֽ��
	int stg_position_a_buy_yesterday;	// A��Լ��ֲ����
	int stg_position_a_buy;				// A��Լ��ֲ��ܲ�λ
	int stg_position_a_sell_today;		// A��Լ���ֲֽ��
	int stg_position_a_sell_yesterday;	// A��Լ���ֲ����
	int stg_position_a_sell;			// A��Լ���ֲ��ܲ�λ
	int stg_position_b_buy_today;		// B��Լ��ֲֽ��
	int stg_position_b_buy_yesterday;	// B��Լ��ֲ����
	int stg_position_b_buy;				// B��Լ��ֲ��ܲ�λ
	int stg_position_b_sell_today;		// B��Լ���ֲֽ��
	int stg_position_b_sell_yesterday;	// B��Լ���ֲ����
	int stg_position_b_sell;			// B��Լ���ֲ��ܲ�λ

	CThostFtdcDepthMarketDataField *stg_instrument_A_tick;	// A��Լtick����һ�ȣ�
	CThostFtdcDepthMarketDataField *stg_instrument_B_tick;	// B��Լtick���ڶ��ȣ�
	double stg_spread_long;									// �г���ͷ�۲A��Լ��һ�� - B��Լ��һ��
	int stg_spread_long_volume;								// �г���ͷ�۲��̿ڹҵ���min(A��Լ��һ�� - B��Լ��һ��)
	double stg_spread_short;								// �г���ͷ�۲A��Լ��һ�� - B��Լ��һ��
	int stg_spread_short_volume;							// �г���ͷ�۲��̿ڹҵ�����min(A��Լ��һ�� - B��Լ��һ��)
	double stg_spread;										// �г����¼ۼ۲�

	string stg_order_ref_last;	// ���һ��ʵ��ʹ�õı�������
	string stg_order_ref_a;		// A��Լ��������
	string stg_order_ref_b;		// B��Լ��������
	double stg_a_price_tick;	// A��Լ��С����
	double stg_b_price_tick;	// B��Լ��С����

	bool stg_trade_tasking;		// �������������
	CThostFtdcInputOrderField *stg_a_order_insert_args;		// a��Լ��������
	CThostFtdcInputOrderField *stg_b_order_insert_args;		// b��Լ��������
	list<CThostFtdcOrderField *> *stg_list_order_pending;	// �ҵ��б��������ɽ��������ر�

};

#endif