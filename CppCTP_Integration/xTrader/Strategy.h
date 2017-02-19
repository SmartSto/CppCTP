#ifndef QUANT_STRATEGY_H
#define QUANT_STRATEGY_H
#include <list>
#include "Trader.h"
#include "Algorithm.h"
#include "Debug.h"
#include "DBManager.h"
#include "xTradeStruct.h"

using std::list;
class DBManager;

#define ALGORITHM_ONE	"01"
#define ALGORITHM_TWO	"02"
#define ALGORITHM_THREE "03"
#define ALGORITHM_FOUR	"04"

class Strategy {

public:

	Strategy(User *stg_user=NULL);

	void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

	bool CompareTickData(CThostFtdcDepthMarketDataField *last_tick_data, CThostFtdcDepthMarketDataField *pDepthMarketData);

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

	CThostFtdcDepthMarketDataField* getStgInstrumentATickLast();
	void setStgInstrumentATickLast(
		CThostFtdcDepthMarketDataField* stgInstrumentATick);

	CThostFtdcDepthMarketDataField* getStgInstrumentBTickLast();
	void setStgInstrumentBTickLast(
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

	int isStgOnlyClose();
	void setStgOnlyClose(int stgOnlyClose);

	int getStgAOrderActionTiresLimit();
	void setStgAOrderActionTiresLimit(int stgOrderActionTiresLimit);

	int getStgBOrderActionTiresLimit();
	void setStgBOrderActionTiresLimit(int stgOrderActionTiresLimit);

	int getStgAOrderActionCount();
	void setStgAOrderActionCount(int stg_a_order_action_count);

	int getStgBOrderActionCount();
	void setStgBOrderActionCount(int stg_b_order_action_count);

	int getStgALimitPriceShift(); // A��Լ����ƫ��
	void setStgALimitPriceShift(int stg_a_limit_price_shift);
	
	int getStgBLimitPriceShift(); // B��Լ����ƫ��
	void setStgBLimitPriceShift(int stg_b_limit_price_shift);


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

	
	int getStgPendingAOpen();
	void setStgPendingAOpen(int stg_pending_a_open);

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

	void setStgOrderRefBase(long long stg_order_ref_base);
	long long getStgOrderRefBase();

	void setStgTradingDay(string stg_trading_day);
	string getStgTradingDay();

	void setStgSelectOrderAlgorithmFlag(string msg, bool stg_select_order_algorithm_flag);
	bool getStgSelectOrderAlgorithmFlag();

	void setStgLockOrderRef(string stg_lock_order_ref);
	string getStgLockOrderRef();

	void setStgSaveStrategyConn(mongo::DBClientConnection *stg_save_strategy_conn);
	mongo::DBClientConnection *getStgSaveStrategyConn();


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
	void Select_Order_Algorithm(string stg_order_algorithm);


	//�µ��㷨1
	void Order_Algorithm_One();
	//�µ��㷨2
	void Order_Algorithm_Two();
	//�µ��㷨3
	void Order_Algorithm_Three();

	/// ���ɱ�������
	string Generate_Order_Ref();

	/// ִ��������
	void Exec_OrderInsert(CThostFtdcInputOrderField *insert_order);			// ����
	void Exec_OnRspOrderInsert();		// ����¼������
	void Exec_OnRspOrderAction();		// ��������������Ӧ
	void Exec_OnRtnOrder(CThostFtdcOrderField *pOrder);				// �����ر�
	void ExEc_OnRtnTrade(CThostFtdcTradeField *pTrade);				// �ɽ��ر�
	void Exec_OnErrRtnOrderInsert();	// ����¼�����ر�
	void Exec_OnErrRtnOrderAction();	// ������������ر�
	void Exec_OnTickComing(CThostFtdcDepthMarketDataField *pDepthMarketData);			// ����ص�,ִ�н�������

	/// ���¹ҵ�list
	void update_pending_order_list(CThostFtdcOrderField *pOrder);

	/// ���³ֲ���(Order)
	void update_position(CThostFtdcOrderField *pOrder);

	/// ���³ֲ���(UserOrder)
	void update_position(USER_CThostFtdcOrderField *pOrder);
	
	/// ���³ֲ���(Trade)
	void update_position(CThostFtdcTradeField *pTrade);

	/// ���³ֲ���ϸ(Trade)
	void update_position_detail(CThostFtdcTradeField *pTrade);

	/// ���³ֲ���ϸ(Order)
	void update_position_detail(USER_CThostFtdcOrderField *pOrder);

	/// ���½���״̬
	void update_task_status();

	/// ����tick��
	void update_tick_lock_status(USER_CThostFtdcOrderField *order);

	/// ����ֶα��γɽ�����order������
	void add_VolumeTradedBatch(CThostFtdcOrderField *pOrder, USER_CThostFtdcOrderField *new_Order);

	


	/// �õ���������Сֵ
	int getMinNum(int num1, int num2, int num3);

	/// ��ʼ��
	void InitStrategy();

	/// �����ṹ��CThostFtdcDepthMarketDataField
	void CopyTickData(CThostFtdcDepthMarketDataField *dst, CThostFtdcDepthMarketDataField *src);

	/// �����ṹ��CThostFtdcOrderField
	void CopyOrderData(CThostFtdcOrderField *dst, CThostFtdcOrderField *src);

	void CopyOrderDataToNew(USER_CThostFtdcOrderField *dst, CThostFtdcOrderField *src);

	/// �����ṹ��USER_CThostFtdcOrderField
	void CopyNewOrderData(USER_CThostFtdcOrderField *dst, USER_CThostFtdcOrderField *src);

	/// �����ṹ��CThostFtdcTradeField
	void CopyTradeData(CThostFtdcTradeField *dst, CThostFtdcTradeField *src);

	/// ���̱�������
	void DropPositionDetail();

	/// ���²���
	void UpdateStrategy(Strategy *stg);

	/// �����ֲ���ϸ
	void CreatePositionDetail(USER_CThostFtdcOrderField *posd);

	/// ���ݿ���²��Գֲ���ϸ
	void Update_Position_Detail_To_DB(USER_CThostFtdcOrderField *posd);

	/// ���ÿ���
	int getOn_Off();
	void setOn_Off(int on_off);

	void setStgSellOpenOnOff(int sell_open_on_off);				//����-����
	int getStgSellOpenOnOff();

	void setStgBuyCloseOnOff(int buy_close_on_off);				//��ƽ-����
	int getStgBuyCloseOnOff();

	void setStgBuyOpenOnOff(int buy_open_on_off);				//��-����
	int getStgBuyOpenOnOff();

	void setStgSellCloseOnOff(int sell_close_on_off);			//��ƽ-����
	int getStgSellCloseOnOff();

	

	/// ����ģ��
	void setStgTradeModel(string stg_trade_model);

	string getStgTradeModel();

	string getStgOrderAlgorithm();			// �µ��㷨

	void setStgOrderAlgorithm(string stg_order_algorithm);

	double getStgHoldProfit();				// �ֲ�ӯ��

	void setStgHoldProfit(double stg_hold_profit);

	double getStgCloseProfit();			// ƽ��ӯ��

	void setStgCloseProfit(double stg_close_profit);

	double getStgCommission();				// ������

	void setStgCommisstion(double stg_commission);

	int getStgPosition();					// �ֲܳ�

	void setStgPosition(int stg_position);

	int getStgPositionBuy();				// ��ֲ�

	void setStgPositionBuy(int stg_position_buy);

	int getStgPositionSell();				// ���ֲ�
	
	int setStgPositionSell(int stg_position_sell);

	int getStgTradeVolume();				// �ɽ���

	int setStgTradeVolume(int stg_trade_volume);

	double getStgAmount();					// �ɽ����

	void setStgAmount(double stg_amount);

	double getStgAverageShift();			// ƽ������

	void setStgAverageShift(double stg_average_shift);

	void setInit_Finished(bool init_finished);

	bool getInit_Finished();

	void init_today_position();

	void setL_query_trade(list<CThostFtdcTradeField *> *l_query_trade);
	void addOrderToListQueryOrder(CThostFtdcOrderField *order);
	void setL_query_order(list<CThostFtdcOrderField *> *l_query_order);

	void add_position_detail(USER_CThostFtdcOrderField *posd);

	//void CopyPositionData(PositionDetail *posd, USER_CThostFtdcOrderField *order);

	list<USER_CThostFtdcOrderField *> * getStg_List_Position_Detail_From_Order(); // �ֲ���ϸ

	void printStrategyInfo(string message); //�������
	void printStrategyInfoPosition();

private:
	Trader *trader;
	User *user;
	string strategyid;
	string userid;
	string traderid;
	Algorithm *alg;
	list<string> *l_instruments;

	DBManager *stg_DBM;			// ���ݿ�����ʵ��
	mongo::DBClientConnection *stg_save_strategy_conn; //�������ڱ�����Ե����ݿ�����
	User *stg_user;				// userʵ��
	string stg_trader_id;		// ����Ա�˻�id
	string stg_user_id;			// user_id
	string stg_strategy_id;		// ����id
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
	int stg_a_order_action_tires_limit;	// A��Լ������������
	int stg_b_order_action_tires_limit;	// B��Լ������������
	int stg_a_order_action_count;		// A��Լ��������
	int stg_b_order_action_count;		// B��Լ��������
	
	/*�����ֶ�*/
	string stg_trade_model;				// ����ģ��
	string stg_order_algorithm;			// �µ��㷨
	double stg_hold_profit;				// �ֲ�ӯ��
	double stg_close_profit;			// ƽ��ӯ��
	double stg_commission;				// ������
	int stg_position;					// �ֲܳ�
	int stg_position_buy;				// ��ֲ�
	int stg_position_sell;				// ���ֲ�
	int stg_trade_volume;				// �ɽ���
	double stg_amount;					// �ɽ����
	double stg_average_shift;			// ƽ������
	string stg_trading_day;				// ������

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
	int stg_pending_a_open;				// A��Լ�ҵ��򿪲���
	bool stg_select_order_algorithm_flag;	// �µ��㷨����־λ
	string stg_lock_order_ref;			// ѡ���µ��㷨�����в�����order_ref
	string stg_tick_systime_record;		// �յ�tick��ϵͳʱ��

	CThostFtdcDepthMarketDataField *stg_instrument_Last_tick;	// A��Լtick����һ�ȣ�
	CThostFtdcDepthMarketDataField *stg_instrument_A_tick;	// A��Լtick����һ�ȣ�
	CThostFtdcDepthMarketDataField *stg_instrument_B_tick;	// B��Լtick���ڶ��ȣ�
	CThostFtdcDepthMarketDataField *stg_instrument_A_tick_last;	// A��Լtick����һ�ȣ�����ǰ���һ��
	CThostFtdcDepthMarketDataField *stg_instrument_B_tick_last;	// B��Լtick���ڶ��ȣ�����ǰ���һ��
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
	int stg_a_limit_price_shift; // A��Լ����ƫ��
	int stg_b_limit_price_shift; // B��Լ����ƫ��

	bool stg_trade_tasking;		// �������������
	CThostFtdcInputOrderField *stg_a_order_insert_args;		// a��Լ��������
	CThostFtdcInputOrderField *stg_b_order_insert_args;		// b��Լ��������
	list<CThostFtdcOrderField *> *stg_list_order_pending;	// �ҵ��б��������ɽ��������ر�
	list<CThostFtdcTradeField *> *stg_list_position_detail; // �ֲ���ϸ
	list<USER_CThostFtdcOrderField *> *stg_list_position_detail_from_order; // �ֲ���ϸ
	list<CThostFtdcTradeField *> *l_query_trade;
	list<USER_CThostFtdcOrderField *> *l_query_order;

	long long stg_order_ref_base; // �������ü���

	int on_off;							//����
	int stg_only_close;					//ֻ��ƽ��
	int sell_open_on_off;				//����-����
	int buy_close_on_off;				//��ƽ-����
	int buy_open_on_off;				//��-����
	int sell_close_on_off;				//��ƽ-����
	
	bool init_finished;

};

#endif