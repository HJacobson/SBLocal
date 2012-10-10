// Henry Jacobson, 9/2012

#include "DRC_Util.h"

#include <tchar.h>
#include <exception>
#include <string>
#include <windows.h>

static const char *CookieDirName = "Cookies";

// Remove blanks from the right-side of a string
std::string RTrim(const std::string &str)
{
	std::string RTrimStr = "";

	if(str.empty())
	{
		return(RTrimStr);
	}
	else
	{
		int pos = str.length() - 1;

		while(pos >= 0)
		{
			if(!isspace(str[pos]))
			{
				break;
			}
			else
			{
				--pos;
			}
		}

		for(int ix = 0; ix <= pos; ++ix)
		{
			RTrimStr += str[ix];
		}
	}

	return(RTrimStr);
}

// Remove blanks from the left-side of a string
std::string LTrim(const std::string &str)
{
	std::string LTrimStr = "";

	if(str.empty())
	{
		return(LTrimStr);
	}
	else
	{
		int pos = 0;
		int len = str.length();

		while (pos < len)
		{
			if(!isspace(str[pos]))
				break;
			else
			{
				++pos;
			}
		}

		while (pos < len)
		{
			LTrimStr += str[pos];
			++pos;
		}

		return(LTrimStr);
	}
}

// Remove blanks from the left-side and right-side of a string
std::string Trim(const std::string &str)
{
	std::string TrimStr = LTrim(RTrim(str));

	return(TrimStr);
}

void DeleteCookiesDirectory(void)
{
	std::string CookieDirPath = GetCookieDirPath();

	if(CookieDirPath != "")
	{
		std::string RemoveCookieDirCmd = "RMDIR /Q /S \"" + CookieDirPath + "\"";
		const char *buff =  + RemoveCookieDirCmd.c_str();

		int RetVal = system(buff);
	}
}

bool CreateCookiesDirectory(std::string &CookieDirPath)
{
	CookieDirPath = GetCookieDirPath();

	if(CookieDirPath == "")
	{
		return(false);
	}
	else
	{
		bool RetVal = CreateDir(CookieDirPath);
		return(RetVal);
	}
}

// Get the name of the cookie directory
std::string GetCookieDirPath()
{
	std::string ExeDirPath = GetExecutingDir();
	std::string CookieDirPath = "";

	if(ExeDirPath != "")
	{
		CookieDirPath = ExeDirPath + "\\" + CookieDirName;
	}

	return(CookieDirPath);
}

// Get the full path of the executing directory
std::string GetExecutingDir()
{
	std::string ExeDirPath = "";
	char buff[MAX_PATH];

	try
	{
		HINSTANCE hInstance = GetModuleHandle(NULL);
		int RetVal = ::GetModuleFileNameA(hInstance, buff, MAX_PATH);

		if(RetVal == 0)
		{
			MessageBoxA(NULL, "Unable to get exe path.  Cookies and browser information will be cached to memory instead of disk.", "DRC Error", MB_OK);
		}
		else
		{
			ExeDirPath = buff;
			std::size_t pos;
			pos = ExeDirPath.find_last_of("\\/");

			if(pos > 0)
				ExeDirPath = ExeDirPath.substr(0, pos);
		}
	}
	catch (std::exception &ex)
	{
		ExeDirPath = "";

		if(ex.what() != "") {} // Do nothing
	}

	return(ExeDirPath);
}

bool CreateDir(const std::string &DirPath)
{
	const char *buff = DirPath.c_str();
	BOOL CreateDirResult = CreateDirectoryA(buff, NULL);

	if(!CreateDirResult)
	{
		DWORD Err = ::GetLastError();

		if(Err == ERROR_ALREADY_EXISTS)
			return(true);
		else
			return(false);
	}

	return(true);
}
