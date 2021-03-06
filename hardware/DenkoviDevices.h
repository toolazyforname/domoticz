#pragma once

#include "DomoticzHardware.h"
#include <iosfwd>

enum _eDenkoviDevice
{
	DDEV_DAEnet_IP4 = 0,							//0
	DDEV_SmartDEN_IP_16_Relays,						//1
	DDEV_SmartDEN_IP_32_In,							//2
	DDEV_SmartDEN_IP_Maxi,							//3
	DDEV_SmartDEN_IP_Watchdog,						//4
	DDEV_SmartDEN_Logger,							//5
	DDEV_SmartDEN_Notifier							//6
};

class CDenkoviDevices :
	public CDomoticzHardwareBase
{
public:
	CDenkoviDevices(const int ID, const std::string &IPAddress, const unsigned short usIPPort, const std::string &password, const int pollInterval, const int model);
	~CDenkoviDevices(void);

	bool WriteToHardware(const char *pdata, const unsigned char length);
private:
	std::string m_szIPAddress;
	unsigned short m_usIPPort;
	std::string m_Password;
	int m_pollInterval;
	volatile bool m_stoprequested;
	int m_iModel;
	boost::shared_ptr<boost::thread> m_thread;

	void Init();
	bool StartHardware();
	bool StopHardware();
	void Do_Work();
	void GetMeterDetails();

	int DenkoviGetIntParameter(std::string tmpstr, std::string tmpParameter);
	std::string DenkoviGetStrParameter(std::string tmpstr, std::string tmpParameter);
	float DenkoviGetFloatParameter(std::string tmpstr, std::string tmpParameter);
	int DenkoviCheckForIO(std::string tmpstr, std::string tmpIoType);
};
