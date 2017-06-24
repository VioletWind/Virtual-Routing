#pragma once
#ifndef _LS_H_
#define _LS_H_
#include <string>
#include <vector>
#include <map>
using namespace std;

#define LS_MAX 999
struct RouterTab {
	string dst;
	string hop;
	double cost;
	RouterTab() {
		dst = "Undefined";
		hop = "Undefined";
		cost = LS_MAX;
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

struct BufEntry {
	string src;
	int seq, age;
	map<string, bool> sendFlags, ackFlags;
	map<string, struct RouterTab> Neighbors;
	bool first, change;
};
void lsInit(vector<vector<int> > &costs, map<int, string> &NumToHost, map<string, struct RouterTab> &Table, struct Host &host);
void lsSendHello(map<string, struct RouterTab> &adjTable, string &hostname, string &content);
void lsReceiveHello(string &content, string &hostname, map<string, struct RouterTab> &adjTable);
void lsSend(map<string, struct RouterTab> &adjTable, string &content, int &seqNum, struct Host &host);
void lsReceive(string &content, struct BufEntry &srcEntry);
void lsUpdate(vector<vector<int> > &costs, struct BufEntry &entry, map<string, struct Host> &vHost);
void lsDijkstra(vector<vector<int> > &costs, map<string, RouterTab> &table, int srcIndex, map<int, string> &NumToHost);


#endif