#include "stdafx.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "ls.h"

using namespace std;

void lsInit(vector<vector<int> > &costs, map<int, string> &NumToHost, map<string, struct RouterTab> &Table, struct Host &host) {
	int len = costs.size();
	for (int i = 0; i < len; i++) {
		RouterTab tab = {};
		string dst = "";
		double cost = 0;
		dst = NumToHost[i];
		cost = costs[host.index][i];
		tab.dst = dst;
		if (cost == LS_MAX || cost == 0) {
			continue;
		}
		else
			tab.cost = cost;
		tab.hop = dst;
		Table[dst] = tab;
	}host.vectorNum = Table.size();
}

void lsSendHello(map<string, struct RouterTab> &adjTable, string &hostname, string &content) {
	ostringstream oss;
	oss << "Hello" << endl;
	oss << hostname << endl;
	oss << adjTable.size() << endl;
	for (auto it : adjTable) {
		oss << it.second.dst << endl;
	}content = oss.str();
}
void lsReceiveHello(string &content, string &hostname, map<string, struct RouterTab> &adjTable) {
	istringstream iss(content);
	string temp;
	int vnum;
	iss >> temp;
	iss >> hostname;
	iss >> vnum;
	while (vnum--) {
		RouterTab tab;
		iss >> tab.dst;
		tab.hop = tab.dst;
		adjTable[tab.dst] = tab;
	}

}
void lsSend(map<string, struct RouterTab> &adjTable, string &content, int &seqNum, struct Host &host) {
	ostringstream oss;
	oss << "Link State" << endl;
	oss << host.name << endl;
	oss << adjTable.size() << endl;
	oss << seqNum << endl;
	oss << 16 << endl;
	map<string, struct RouterTab>::iterator it = adjTable.begin();
	for (; it != adjTable.end(); it++) {
		oss << (it->second).dst << ' ' << (it->second).hop << ' ' << (it->second).cost << '\n';
	}
	content = oss.str();
	seqNum++;
}


void lsReceive(string &content, struct BufEntry &srcEntry) {
	istringstream iss(content);
	string tmp1, tmp2;
	int vectorNum;
	iss >> tmp1 >> tmp2;
	iss >> srcEntry.src;
	iss >> vectorNum;
	iss >> srcEntry.seq >> srcEntry.age;
	while (vectorNum--) {
		RouterTab tab;
		iss >> tab.dst >> tab.hop >> tab.cost;
		srcEntry.Neighbors[tab.dst] = tab;
	}
}


void lsUpdate(vector<vector<int> > &costs, struct BufEntry &entry, map<string, struct Host> &vHost) {
	int neighbor_index = vHost[entry.src].index;
	// merge neighbor's router_table into cost;
	costs[neighbor_index] = vector<int>(costs.size(), LS_MAX);
	int s = costs.size();
	for (int i = 0; i < s; ++i) {
		costs[i][neighbor_index] = LS_MAX;
	}costs[neighbor_index][neighbor_index] = 0;
	for (auto it : entry.Neighbors) {
		costs[neighbor_index][vHost[it.first].index] = (it.second).cost;
		costs[vHost[it.first].index][neighbor_index] = costs[neighbor_index][vHost[it.first].index];
	}
}


void lsDijkstra(vector<vector<int> > &costs, map<string, RouterTab> &table, int srcIndex, map<int, string> &NumToHost) {
	int VSIZE = costs.size();
	int* dist = new int[VSIZE];
	int* prev = new int[VSIZE];
	bool* S = new bool[VSIZE];
	for (int i = 0; i < VSIZE; i++) {
		dist[i] = costs[srcIndex][i];
		S[i] = false;
		if (dist[i] == LS_MAX)
			prev[i] = -1;
		else
			prev[i] = srcIndex;
	}

	dist[srcIndex] = 0;
	S[srcIndex] = true;

	for (int i = 2; i <= VSIZE; i++) {
		int mindist = LS_MAX;
		int u = srcIndex;
		for (int j = 0; j < VSIZE; j++) {
			if ((!S[j]) && dist[j] < mindist) {
				u = j;
				mindist = dist[j];
			}
		}
		S[u] = true;
		for (int j = 0; j < VSIZE; j++) {
			if ((!S[j]) && costs[u][j] < LS_MAX) {
				if (dist[u] + costs[u][j] < dist[j]) {
					dist[j] = dist[u] + costs[u][j];
					prev[j] = u;
				}
			}
		}
	}
	table.clear();
	for (int i = 0; i < VSIZE; i++) {
		if (prev[i] != -1) {
			int u = i;
			while (prev[u] != srcIndex)
				u = prev[u];

			string dst = NumToHost[i];
			string hop = NumToHost[u];
			int newCost = dist[i];
			table[dst].dst = dst;
			table[dst].hop = hop;
			table[dst].cost = newCost;
		}
	}

	delete[] dist;
	delete[] S;
	delete[] prev;
}