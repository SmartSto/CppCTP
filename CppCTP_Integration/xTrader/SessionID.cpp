#include "SessionID.h"

void SessionID::setUserID(string userid) {
	this->userid = userid;
}

string SessionID::getUserID() {
	return this->userid;
}

void SessionID::setSessionID(int sessionid) {
	this->sessionid = sessionid;
}

int SessionID::getSessionID() {
	return this->sessionid;
}

void SessionID::setFrontID(int frontid) {
	this->frontid = frontid;
}

int SessionID::getFrontID() {
	return this->frontid;
}