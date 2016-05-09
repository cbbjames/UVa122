#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<sstream>
#include<queue>
using namespace std;
struct Node {
	int par ;
	int left;
	int right;
	int val;
};
vector<Node>nodes;
int root=0;
vector<pair<int, string> >level[300];
int total;
int maketree(int i, string s,int par) {
	//for(int i=0;i<257;i++){
	if (level[i].size() == 0) return -1;
	if (i == 0) {//root
		Node roott;
		string L = "L", R = "R";
		roott.par = root;
		roott.val = level[0][0].first;
		nodes.push_back(roott);
		nodes[0].left = maketree(i + 1, L,root);
		nodes[0].right = maketree(i + 1, R,root);
		return 0;
	}
	for (int j = 0; j<level[i].size(); j++) {
		if (level[i][j].second == s) {
			Node anode;
			anode.val = level[i][j].first;
			anode.par = par;
			nodes.push_back(anode);
			int x = nodes.size() - 1;
			//Node* pass = &nodes[nodes.size() - 1];

			string L, R;
			L = level[i][j].second + "L";
			R = level[i][j].second + "R";
			nodes[x].left = maketree(i + 1, L,x);
			nodes[x].right = maketree(i + 1, R,x);

			return x;
		}
	}
	//cout << "zz" << endl;
	return -1;//not found
}

void clear() {
	for (int i = 0; i<257; i++) {
		level[i].clear();
	}
	nodes.clear();
	total = 0;
}
void deal(string s) {
	total++;
	pair<int, string> node;
	int key, i = 0, cnt = 0;
	string pos;
	stringstream ss(&s[1]);
	ss >> key;
	while (s[i++] != ',') {}
	while (s[i] != ')') { pos = pos + s[i++]; cnt++; }
	node.first = key;
	node.second = pos;
	level[cnt].push_back(node);
}
void print() {
	if (total != nodes.size()) {
		cout << "not complete" << endl;
		return;
	}
	queue<int>q;
	q.push(0);
	bool first=true;
	while (!q.empty()) {//tras level-order
		int u = q.front(); q.pop();
		if (first) first = false; 
		else cout << ' ';
		cout << nodes[u].val;
		if (nodes[u].left >= 0) q.push(nodes[u].left);
		if (nodes[u].right >= 0) q.push(nodes[u].right);
	}cout << endl;
}
int main() {
	string s;
	nodes.reserve(1000);
	while (cin>> s) {
			if (s[1]==')') {
				//string sec=s.substr(2,s.size()-2);
				maketree(0, "", 0);
				print();
				clear();
				nodes.reserve(1000);
				//deal(sec);
			}
			else deal(s);
		}
	
	//system("PAUSE");
	return 0;
}