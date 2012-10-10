// Henry Jacobson, 9/2012

#ifndef DRCCONFIGURATION_H_
#define DRCCONFIGURATION_H_
#pragma once

#include <string>

class DRCConfiguration
{
public:
	DRCConfiguration(void);
	~DRCConfiguration(void);

	std::string GetStartupURL(void);
	void Init(void);
private:
	void GetConfigurationSettings(void);
	void SaveConfigurationSettings(std::string, std::string);
	bool IsSecureMode;
};

#endif
