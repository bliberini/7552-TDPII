#include "CreateUserEvent.h"

CreateUserEvent::CreateUserEvent() {
}

CreateUserEvent::CreateUserEvent(struct mg_connection* nco, struct http_message* hme) {
	this->nc = nco;	
	this->hm = hme;
	this->methodType = "POST";
}

CreateUserEvent::~CreateUserEvent() {

}

bool CreateUserEvent::validateInput() {
	bool parentValidation = EventHandler::validateInput();
	if(!parentValidation) return parentValidation;
	// TODO: Validate content type header is application/json

	Json::Reader r = Json::Reader();
	Json::Value val = Json::Value();
	r.parse(hm->body.p,val);
	//std::cout << val.get("password", "").asString() << std::endl;
	if(val.get("username", "").asString().compare("") == 0) {
		this->response(2, "Missing parameters", (Json::Value)0);
		return false;
	}
	if(val.get("name", "").asString().compare("") == 0) {
		this->response(2, "Missing parameters", (Json::Value)0);
		return false;
	}
	if(val.get("password", "").asString().compare("") == 0) {
		this->response(2, "Missing parameters", (Json::Value)0);
		return false;
	}

	return true;
}

void CreateUserEvent::handle(Manager* manager) {
	bool validation = this->validateInput();
	if(validation) {
		bool userWasCreated = manager->createUser(hm->body.p);
		if(userWasCreated) {
			this->response(0, "Registered", (Json::Value)0);
		} else {
			this->response(1, "Already Registered", (Json::Value)0);
		}
	}
}