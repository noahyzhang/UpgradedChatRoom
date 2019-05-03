#pragma once

#include<iostream>
#include<string>

//日志级别
#define NORMAL 0    //
#define WARNING 1   
#define ERROR 2

const char* log_level[] = {
	"Normal",
	"Warning",
	"Error",
    NULL,
};

void Log(const std::string msg,int level,std::string file,int line)  //日志的级别
{
	std::cout << '[' << msg << ']' << '[' << log_level[level] << ']' << " : "  \
		<< file << " : " << line << std::endl;
}

#define LOG(msg,level) Log(msg,level,__FILE__,__LINE__)
