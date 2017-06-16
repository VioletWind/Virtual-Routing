#include "stdafx.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "dv.h"

using namespace std;

void dvInit(vector<vector<int> > &costs, map<int, string> &NumToHost, map<string, struct RouterTab> &Table, struct Host host) {
	for (int i = 0; i < costs[host.index].size(); i++) {
		RouterTab tab = {};
		string dst = "";
		double cost = 0;
		dst = NumToHost[i];
		cost = costs[host.index][i];
		tab.dst = dst;
		if (cost == DV_MAX) {
			continue;
		}
		else
			tab.cost = cost;
		tab.hop = dst;
		Table[dst] = tab;
	}
}
void dvSend(string &content, map<string, struct RouterTab> &table, struct Host &host) {
	ostringstream oss;
	oss << host.vectorNum << endl << host.index << endl << host.IP << endl << host.Port << endl;
	map<string, struct RouterTab>::iterator it = table.begin();
	for (; it != table.end(); it++) {
		oss << (it->second).dst << ' ' << (it->second).hop << ' ' << (it->second).cost << '\n';
	}
	content = oss.str();	// s_str()
}
void dvReceive(string &content, map<string, struct RouterTab> &srcTab, struct Host &from) {
	istringstream iss(content);
	iss >> from.vectorNum >> from.index >> from.IP >> from.Port;
	int length = from.vectorNum;
	while (length--) {
		RouterTab tmp;
		iss >> tmp.dst >> tmp.hop >> tmp.cost;
		srcTab[tmp.dst] = tmp;
	}
}
void dvUpdate(struct Host from, map<string, struct RouterTab> &srcTab, map<string, struct RouterTab> &adjTable, map<string, struct RouterTab> &routeTable, struct Host &host) {

}
void dvDelete(map<string, struct RouterTab> &table, map<string, struct RouterTab> &adjTable, string HostName) {
	map<string, struct RouterTab>::iterator it = table.begin();
	for (; it != table.end(); it++) {
		if (it->first == HostName) {
			table.erase(it);
			break;
		}
	}
}
void dvDisable(map<string, struct RouterTab> &table, map<string, struct RouterTab> &adjTable, string HostName) {
	table[HostName].cost = DV_MAX;
}