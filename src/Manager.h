/*
 * Manager.h
 *
 *  Created on: Mar 31, 2016
 *      Author: juanma
 */

#ifndef MANAGER_H_
#define MANAGER_H_


#include <iostream>
#include "Conversation.h"


class Database;

using namespace std;

class Manager {
public:
	Manager();
	virtual ~Manager();
	Database* getDatabase();
	void setDatabase(Database* db);
	bool createUser(string json);
	User* getUser(std::string);
	Conversation* getConversation(std::string, std::string);
	vector<Message*> getMessages(string user1, string user2);
	bool saveMessage(string json);


private:
	Database* db;

};

#endif /* MANAGER_H_ */
