#pragma once

#include<iostream>
#include<string>
#include<unordered_map>
#include<pthread.h>

class User{
	private:
		std::string nick_name;  //昵称
		std::string school;
		std::string passwd;
	public:
		User()
		{}
		User(const std::string& n_, const std::string& s_, \
				const std::string pwd_)
			: nick_name(n_)
			, school(s_)
			, passwd(pwd_)
		{}
		bool IsPasswdOk(const std::string &passwd_)
		{
			return passwd == passwd_ ? true : false;
		}
		std::string &GetNickName()
		{
			return nick_name;
		}
		std::string &GetSchool()
		{
			return school;
		}
		~User()
		{}
};

class UserManager{
	private:
		unsigned int assgin_id; //分配的ID
		std::unordered_map<unsigned int,User> users;  //所有的已注册用户
		std::unordered_map<unsigned int,struct sockaddr_in> online_users;  //在线用户链表
		pthread_mutex_t lock;

		void Lock()
		{
			pthread_mutex_lock(&lock);
		}
		void Unlock()
		{
			pthread_mutex_unlock(&lock);
		}

	public:
		UserManager()
			: assgin_id(10000)
		{
			pthread_mutex_init(&lock,NULL);
		}
		unsigned int Insert(const std::string& n_,const std::string &s_, const std::string &p_)
		{
			Lock(); //有可能多个人同时注册
			unsigned int id = assgin_id++; //最大的数量时42亿多，因此不会出现满的情况
			User u(n_,s_,p_);
			if(users.find(id) == users.end())
			{
				//users.insert(make_pair(id,u));
				users.insert({id,u});
				Unlock();
				
				for(auto &e : users)
					std::cout << "register users: "<< e.first << std::endl;
				
				return id;
			}
			Unlock();

			for(auto &e : users)
				std::cout << "register users: "<< e.first << std::endl;

			return 1;  //注册错误
		}
		unsigned int Check(const unsigned int &id,const std::string &passwd)
		{
			std::cout<<"Check id : "<<id<<std::endl;
			Lock();  //查的时候可能有人在注册
			auto it = users.find(id);
			
			if(it != users.end()) //找到了
			{
				std::cout << "Found it user" <<std::endl;
				User &u = it->second;
				if(u.IsPasswdOk(passwd))
				{
					std::cout<<"Password verification correct"<<std::endl;
					Unlock();
					return id;
				}
				else
					std::cout<<"Password validation error"<<std::endl;
			}
			else if(it == users.end())
				std::cout<<"Not Found" <<std::endl;
			Unlock();
			return 2;
		}
		void AddOnlineUser(unsigned int id,struct sockaddr_in &peer)
		{
			Lock();
			auto it = online_users.find(id);
			if(it == online_users.end())
			{
				online_users.insert({id,peer});
			}
			Unlock();
		}
		void GetUserInfo(const unsigned int &id,std::string& name_,std::string& school_)
		{
			Lock();
			name_ = users[id].GetNickName();
			school_ = users[id].GetSchool();
			Unlock();
		}
		std::unordered_map<unsigned int,struct sockaddr_in> OnlineUser()
		{
			Lock();
			auto online = online_users;
			Unlock();
			return online;
		}
		~UserManager()
		{
			pthread_mutex_destroy(&lock);
		}
};




