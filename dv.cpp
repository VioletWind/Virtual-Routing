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
	content = "Router\n" +oss.str();	// s_str()
}
void dvReceive(string &content, map<string, struct RouterTab> &srcTab, struct Host &from) {
	istringstream iss(content);
	string r;
	iss >> r >> from.vectorNum >> from.index >> from.IP >> from.Port;
	int length = from.vectorNum;
	while (length--) {
		RouterTab tmp;
		iss >> tmp.dst >> tmp.hop >> tmp.cost;
		srcTab[tmp.dst] = tmp;
	}
}
void dvUpdate(struct Host from, map<string, struct RouterTab> &srcTab, map<string, struct RouterTab> &adjTable, map<string, struct RouterTab> &routeTable, struct Host &host) {
	// d(v) = min{c(u, v), c(u, x) + c(x, v)}
	map<string, struct RouterTab>::iterator it;
	map<string, struct RouterTab>::iterator it2;
	double fromCost = (routeTable.find(from.name)->second).cost;	// c(u,x)
	for (it2 = srcTab.begin(); it2 != srcTab.end(); it2++) {
		string name = (it2->second).dst;	// v
		string hop = (it2->second).hop;
		it = routeTable.find(name);

		//route back to host
		if (name.compare(host.name) == 0)	// x = v
			continue;

		//it's a new route
		if (it == routeTable.end()) {	// old c(u,v) = DV_MAX
			RouterTab temp;
			temp.dst = name;			// new node can be reachable
			temp.hop = from.name;		// through the srcRouter
			double newCost = fromCost + (it2->second).cost;
			newCost = (newCost > DV_MAX) ? DV_MAX : newCost;
			temp.cost = newCost;

			routeTable[name] = temp;
			host.vectorNum++;
		}

		//the route is existed
		else {
			//ignore the route which pass by it self
			if (hop.compare(host.name) == 0)
				continue;

			else {
				double oldCost = (it->second).cost;
				double newCost = fromCost + (it2->second).cost;
				newCost = (newCost > oldCost) ? oldCost : newCost;

				//hop route don't change, just update the cost
				if (((it->second).hop).compare(from.name) == 0) {
					(it->second).cost = newCost;
				}

				//new path is better
				if (newCost < oldCost) {
					(it->second).cost = newCost;
					//check if host to from route directly
					string hopHtoF = (routeTable.find(from.name)->second).hop;
					if (hopHtoF.compare(from.name) == 0) {
						(it->second).hop = from.name;
					}
					else
						(it->second).hop = hopHtoF;
				}
			}
		}
	}
}
void dvDelete(map<string, struct RouterTab> &table, map<string, struct RouterTab> &adjTable, string HostName, Host &host) {
	map<string, struct RouterTab>::iterator it = table.begin();
	for (; it != table.end(); it++) {
		if (it->first == HostName) {
			table.erase(it);
			break;
		}
	}host.vectorNum--;
}
void dvDisable(map<string, struct RouterTab> &table, map<string, struct RouterTab> &adjTable, string HostName) {
	table[HostName].cost = DV_MAX;
}