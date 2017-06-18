#pragma once
#ifndef _DV_H_
#define _DV_H_
#include <string>
#include <vector>
#include <map>
using namespace std;

#define DV_MAX 999
struct RouterTab {
	string dst;
	string hop;
	double cost;
	RouterTab() {
		dst = "Undefined";
		hop = "Undefined";
		cost = DV_MAX;
	}
	RouterTab(const char* tdst, const char* thop, double tcost) :dst(tdst), hop(thop), cost(tcost) {};
};
struct Host {
	string name;
	int vectorNum;
	int index;
	string IP;
	int Port;
	Host() {
		name = "Undefined";
		vectorNum = -1;
		index = -1;
		IP = "127.0.0.1";
		Port = -1;
	}
	Host(string tName, int tVectorNum, int tIndex, string tIP, int tPort) :name(tName), vectorNum(tVectorNum), index(tIndex), IP(tIP), Port(tPort) {};
};
void dvInit(vector<vector<int> > &costs, map<int, string> &NumToHost, map<string, struct RouterTab> &Table, struct Host &host);
void dvSend(string &content, map<string, struct RouterTab> &table, struct Host &host);
void dvReceive(string &content, map<string, struct RouterTab> &srcTab, struct Host &from);
void dvUpdate(struct Host from, map<string, struct RouterTab> &srcTab, map<string, struct RouterTab> &adjTable, map<string, struct RouterTab> &routeTable, struct Host &host);
void dvDelete(map<string, struct RouterTab> &table, map<string, struct RouterTab> &adjTable, string HostName, Host &host);
void dvDisable(map<string, struct RouterTab> &table, map<string, struct RouterTab> &adjTable, string HostName);
#endif