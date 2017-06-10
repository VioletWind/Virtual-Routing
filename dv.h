#pragma once
#ifndef _DV_H_
#define _DV_H_
#include <string>
#include <vector>
#include <map>
using namespace std;

struct RouterTab {
	string dst;
	string hop;
	double cost;
};
struct Host {
	string name;
	int vectorNum;
	string IP;
	string Port;
};
void dvInit(vector<vector<int> > &costs, map<int, string> &NumToHost, map<string, struct RouterTab> &Table);
void dvSend(string &content, map<string, struct RouterTab> &table, struct Host &host);
void dvReceive(string &content, map<string, struct RouterTab> &srcTab, struct Host &from);
void dvUpdate(struct Host from, map<string, struct RouterTab> &srcTab, map<string, struct RouterTab> &adjTable, map<string, struct RouterTab> &routeTable, struct Host &host);
void dvDelete(map<string, struct RouterTab> &table, map<string, struct RouterTab> &adjTable, string HostName);
void dvDisable(map<string, struct RouterTab> &table, map<string, struct RouterTab> &adjTable, string HostName);
#endif