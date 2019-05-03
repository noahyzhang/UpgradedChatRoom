#include<iostream>
#include"/home/zy/project/ChatSystem/json/include/json/json.h"

int main()
{
	std::string nick_name = "zhangsan";
	std::string school = "sust"; 
	std::string passwd = "1234";
	
	Json::Value root;
	
	root["name"] = nick_name;
	root["school"] = school;
	root["passwd"] = passwd;

	Json::FastWriter w;
	std::string s =	w.write(root);

	std::cout << s <<std::endl;
	return 0;
}
