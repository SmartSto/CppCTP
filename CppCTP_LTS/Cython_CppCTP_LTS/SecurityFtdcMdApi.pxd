# distutils: language=c++
from SecurityFtdcMdApi cimport *
from SecurityFtdcUserApiStruct cimport *

cdef extern from "SecurityFtdcMdApi.h":
    cdef cppclass CMDSpi "CSecurityFtdcMdSpi":
        ###当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
        void OnFrontConnected()

        ###当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
        ###@param nReason 错误原因
        ###        0x1001 网络读失败
        ###        0x1002 网络写失败
        ###        0x2001 接收心跳超时
        ###        0x2002 发送心跳失败
        ###        0x2003 收到错误报文
        void OnFrontDisconnected(int nReason)

        ###心跳超时警告。当长时间未收到报文时，该方法被调用。
        ###@param nTimeLapse 距离上次接收报文的时间
        void OnHeartBeatWarning(int nTimeLapse)

        ###错误应答
        void OnRspError(CSecurityFtdcRspInfoField *pRspInfo, int nRequestID,  bint bIsLast)

        ###登录请求响应
        void OnRspUserLogin(CSecurityFtdcRspUserLoginField *pRspUserLogin, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bint bIsLast)

        ###登出请求响应
        void OnRspUserLogout(CSecurityFtdcUserLogoutField *pUserLogout, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bint bIsLast)

        ###订阅行情应答
        void OnRspSubMarketData(CSecurityFtdcSpecificInstrumentField *pSpecificInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bint bIsLast)

        ###取消订阅行情应答
        void OnRspUnSubMarketData(CSecurityFtdcSpecificInstrumentField *pSpecificInstrument, CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bint bIsLast)

        ###深度行情通知
        void OnRtnDepthMarketData(CSecurityFtdcDepthMarketDataField *pDepthMarketData)

cdef extern from "SecurityFtdcMdApi.h":
    cdef cppclass CMDApi "CSecurityFtdcMdApi":
        ###删除接口对象本身
        ###@remark 不再使用本接口对象时,调用该函数删除接口对象
        void Release() nogil

        ###初始化
        ###@remark 初始化运行环境,只有调用后,接口才开始工作
        void Init() nogil

        ###等待接口线程结束运行
        ###@return 线程退出代码
        int Join() nogil

        ###获取当前交易日
        ###@retrun 获取到的交易日
        ###@remark 只有登录成功后,才能得到正确的交易日
        const char *GetTradingDay() nogil

        ###注册前置机网络地址
        ###@param pszFrontAddress：前置机网络地址。
        ###@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。
        ###@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
        void RegisterFront(char *pszFrontAddress) nogil

        ###注册回调接口
        ###@param pSpi 派生自回调接口类的实例
        void RegisterSpi(CMDSpi *pSpi) nogil

        ###订阅行情。
        ###@param ppInstrumentID 合约ID
        ###@param nCount 要订阅/退订行情的合约个数
        ###@remark
        int SubscribeMarketData(char *ppInstrumentID[], int nCount, char* pExchageID) nogil

        ###退订行情。
        ###@param ppInstrumentID 合约ID
        ###@param nCount 要订阅/退订行情的合约个数
        ###@remark
        int UnSubscribeMarketData(char *ppInstrumentID[], int nCount, char* pExchageID) nogil

        ###用户登录请求
        int ReqUserLogin(CSecurityFtdcReqUserLoginField *pReqUserLoginField, int nRequestID) nogil

        ###登出请求
        int ReqUserLogout(CSecurityFtdcUserLogoutField *pUserLogout, int nRequestID) nogil

cdef extern from "SecurityFtdcMdApi.h" namespace "CSecurityFtdcMdApi":
    ###创建MdApi
    ###@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
    ###@return 创建出的UserApi
    ###modify for udp marketdata
    CMDApi *CreateFtdcMdApi(const char *pszFlowPath)  nogil except +