#ifndef QUANT_CTP_DEBUG_H
#define QUANT_CTP_DEBUG_H

#define DEBUG
#ifdef DEBUG
#define USER_PRINT(x) std::cout << "[DEBUG] - " << __DATE__ << ", " << __TIME__<< ", " << __FILE__ << ", Line - " << __LINE__ << endl; std::cout << #x << " = " << x << std::endl;
#else
#define USER_PRINT(x)
#endif

using namespace std;
using std::string;

#endif