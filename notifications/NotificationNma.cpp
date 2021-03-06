#include "stdafx.h"
#include "NotificationNma.h"
#include "../httpclient/HTTPClient.h"
#include "../main/Logger.h"

/*
Notify my Android is shut down
With great sadness, and after 8 years of operation, NMA will shutdown on May 24th.
Due to unacceptably high risks introduced by the GDPR European regulation, and the majority of our users been Europeans, we can't justify operations anymore.
*/

CNotificationNma::CNotificationNma() : CNotificationBase(std::string("nma"), OPTIONS_URL_SUBJECT | OPTIONS_URL_BODY | OPTIONS_URL_PARAMS)
{
	SetupConfig(std::string("NMAEnabled"), &m_IsEnabled);
	SetupConfig(std::string("NMAAPI"), _apikey);
}

CNotificationNma::~CNotificationNma()
{
}

bool CNotificationNma::SendMessageImplementation(
	const uint64_t Idx,
	const std::string &Name,
	const std::string &Subject,
	const std::string &Text,
	const std::string &ExtraData,
	const int Priority,
	const std::string &Sound,
	const bool bFromNotification)
{
	//send message to NMA
	bool bRet;
	std::stringstream sPostData;
	std::string sResult;
	sPostData
		<< "apikey=" << _apikey
		<< "&application=Domoticz"
		<< "&event=" << Subject
		<< "&description=" << Text
		<< "&priority=" << Priority;
		std::vector<std::string> ExtraHeaders;
	bRet = HTTPClient::POST("https://notifymyandroid.appspot.com/publicapi/notify",sPostData.str(),ExtraHeaders,sResult);
	bool bSuccess = (sResult.find("success code=\"200\"") != std::string::npos);
	if (!bSuccess)
		_log.Log(LOG_ERROR, "NMA: %s", sResult.c_str());
	return (bRet && bSuccess);
}

bool CNotificationNma::IsConfigured()
{
	return _apikey != "";
}
