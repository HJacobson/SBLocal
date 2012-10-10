// Henry Jacobson, 9/2012

#ifndef DRC_UTIL_H_
#define DRC_UTIL_H_
#pragma once

#include <string>

bool CreateCookiesDirectory(std::string &CookieDirPath);
bool CreateDir(const std::string &DirPath);
void DeleteCookiesDirectory(void);

std::string GetCookieDirPath();
std::string GetExecutingDir();
std::string LTrim(const std::string &str);
std::string RTrim(const std::string &str);
std::string Trim(const std::string &str);
#endif
