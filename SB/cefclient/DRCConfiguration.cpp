// Henry Jacobson, 9/2012

#include "DRCConfiguration.h"
#include "DRC_Util.h"

#define ConfigFileName "DRCConfiguration.txt"

#include <exception>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

bool AllowAltTab = false;
bool AllowMouseRightClick = false;
bool ClearClipboardOnBegin = true;
bool ClearClipboardOnExit = true;
bool HideTaskBar = true;
bool ShowWinMaximized = true;
bool CacheBrowserToMemory = true;

std::string StartupURL = "";

DRCConfiguration::DRCConfiguration(void)
{
}

DRCConfiguration::~DRCConfiguration(void)
{
}

void DRCConfiguration::Init(void)
{
	static bool ConfigFileProcessed = false;

	if(!ConfigFileProcessed)
	{
		StartupURL = "";
		IsSecureMode = false;

		DRCConfiguration::GetConfigurationSettings();

		ConfigFileProcessed = true;
	}
}

void DRCConfiguration::GetConfigurationSettings(void)
{
	std::string InData;
	std::ifstream ConfigFile (ConfigFileName);

	try
	{
		if(ConfigFile.is_open())
		{
			std::string key, val;
			unsigned int ColonPos;

			while(ConfigFile.good())
			{
				std::getline(ConfigFile, InData);

				if(!InData.empty() && InData.length() > 2 && InData.substr(0, 2) != "//")
				{
					ColonPos = InData.find(":");

					if(ColonPos > 0)
					{
						key = InData.substr(0, ColonPos);
						
						if(ColonPos < InData.length() - 1)
						{
							val = InData.substr(ColonPos + 1);
							val = Trim(val);

							SaveConfigurationSettings(key, val);
						}
					}
				}
			}
		}
	}
	catch (exception &ex)
	{
		// Do nothing
		if(ex.what() == "") {}
	}

	try
	{
		ConfigFile.close();
	}
	catch (exception &ex)
	{
		// Do nothing
		if(ex.what() == "") {}
	}
}

void DRCConfiguration::SaveConfigurationSettings(std::string key, std::string val)
{
	if(key == "StartupURL")
	{
		StartupURL = val;
	}
	else if(key == "IsSecureMode")
	{
		(val == "true") ? IsSecureMode = true : false;
	}
	else if(key == "AllowMouseRightClick")
	{
		(val == "true") ? AllowMouseRightClick = true : false;
	}
	else if(key == "ShowWindowMaximized")
	{
		if(val == "true")
			ShowWinMaximized = true;
		else
			ShowWinMaximized = false;

			// I cannot get the line below to work.  Don't know why.  Henry
			//(val == "true") ? ShowWinMaximized = true : false;
	}
	else if(key == "AllowAltTab")
	{
		(val == "true") ? AllowAltTab = true : false;
	}
	else if(key == "HideTaskBar")
	{
		if(val == "true")
			HideTaskBar = true;
		else
			HideTaskBar = false;
	}
	else if(key == "ClearClipboardOnBegin")
	{
		if(val == "true")
			ClearClipboardOnBegin = true;
		else
			ClearClipboardOnBegin = false;
	}
	else if(key == "ClearClipboardOnExit")
	{
		if(val == "true")
			ClearClipboardOnExit = true;
		else
			ClearClipboardOnExit = false;
	}
	else if(key == "CacheBrowserToMemory")
	{
		if(val == "true")
			CacheBrowserToMemory = true;
		else
			CacheBrowserToMemory = false;
	}
}
