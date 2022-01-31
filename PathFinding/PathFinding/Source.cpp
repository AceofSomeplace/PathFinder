#include <iostream>
#include <map>
#include <vector>
#include <utility>
using namespace std;


struct nodes {
	char debug;
	vector<pair<nodes*, int> > edges;
};

void pathFinder(vector<pair<nodes*, int>>&path, nodes * node, nodes * destNode, int& weight, int mode);
char inpCheck();

pair<vector<pair<nodes*, int>>, int> bestPath;



int main() {
	int mode = 1;
	nodes A;
	nodes B;
	nodes C;
	nodes D;
	nodes E;
	nodes F;
	nodes G;
	nodes H;
	A.debug = 'A';
	B.debug = 'B';
	C.debug = 'C';
	D.debug = 'D';
	E.debug = 'E';
	F.debug = 'F';
	G.debug = 'G';
	H.debug = 'H';
	A.edges.insert(A.edges.end(), { { &B, 10 }, { &D, 12 }, { &G, 11 }, { &H, 4 } });
	B.edges.insert(B.edges.end(), { { &A, 10 }, { &D, 8 }, { &H, 20 } });
	C.edges.insert(C.edges.end(), { { &D, 17 }, { &E, 8 }, { &G, 13 }, { &H, 10 } });
	D.edges.insert(D.edges.end(), { { &A, 12 }, { &B, 8 }, { &C, 17 }, { &F, 16 }, { &G, 24 }, { &H, 14 } });
	E.edges.insert(E.edges.end(), { { &C, 8 }, { &F, 8 }, { &G, 11 }, { &H, 5 } });
	F.edges.insert(F.edges.end(), { { &D, 16 }, { &E, 8 }, { &G, 18 }, { &H, 21 } });
	G.edges.insert(G.edges.end(), { { &A, 11 }, { &C, 13 }, { &D, 24 }, { &E, 11 }, { &F, 18 }, { &H, 30 } });
	H.edges.insert(H.edges.end(), { { &A, 4 }, { &B, 20 }, { &C, 10 }, { &D, 14 }, { &E, 5 }, { &F, 21 }, { &G, 30 } });


	cout << "Enter a starting node: ";
	char firstInp = inpCheck();
	nodes* first = &A;
	nodes* second = &B;
	switch (firstInp) {
	case 'A':
		first = &A;
		break;
	case 'B':
		first = &B;
		break;
	case 'C':
		first = &C;
		break;
	case 'D':
		first = &D;
		break;
	case 'E':
		first = &E;
		break;
	case 'F':
		first = &F;
		break;
	case 'G':
		first = &G;
		break;
	case 'H':
		first = &H;
		break;
	}
	cout << "Enter a destinantion node: ";
	char secondInp = inpCheck();
	switch (secondInp) {
	case 'A':
		second = &A;
		break;
	case 'B':
		second = &B;
		break;
	case 'C':
		second = &C;
		break;
	case 'D':
		second = &D;
		break;
	case 'E':
		second = &E;
		break;
	case 'F':
		second = &F;
		break;
	case 'G':
		second = &G;
		break;
	case 'H':
		second = &H;
		break;
	}
	cout << "What mode would you like to use (enter a number) ?\n1. Quick search: Outputs a single valid path\n2. Low-cost search: Outputs path with lowest weight\n3. Full search: Outputs all possible paths" << endl;
	cin >> mode;
	while (mode != 1 && mode != 2 && mode != 3) {
		cout << "Invalid mode. Please enter a mode number: ";
	}

	vector<pair<nodes*, int>> nodePath = { { &A, 0 } };
	int weight = 0;
	pathFinder(nodePath, first, second, weight, mode);
	if (mode == 2) {
		cout << "Path found: ";
		for (const auto& j : bestPath.first) {
			cout << (*j.first).debug << ", ";
		}
		cout << "\nTotal weight: " << bestPath.second << "\n" << endl;
	}

	return 0;
}

//Accepts and checks user input node
char inpCheck() {
	char inp;
	cin >> inp;
	toupper(inp);
	while (cin.fail() || (inp != 'A' && inp != 'B' && inp != 'C' && inp != 'D' && inp != 'E' && inp != 'F' && inp != 'G' && inp != 'H')) {
		cout << "Invalid node. Please enter a node: ";
		cin >> inp;
	}
	return inp;
}


//Finds and prints possible paths
void pathFinder(vector<pair<nodes*, int>>&path, nodes * node, nodes * destNode, int& weight, int mode) {

	//Check if destination node has been found in node's connections
	if (node == destNode) {
		if (mode == 1 || mode == 3) {
			cout << "Path found: ";
			for (const auto& j : path) {
				cout << (*j.first).debug << ", ";
			}
			cout << "\nTotal weight: " << weight << "\n" << endl;
		}
		//If mode = quick search, end path finding
		if (mode == 1) {
			return;
		}
		//If mode = cost-effective path and current path has lower weight, update bestPath
		else if (mode == 2) {
			if (weight < bestPath.second || bestPath.second == 0) {
				bestPath.first.clear();
				bestPath.second = weight;
				for (const auto& j : path) {
					bestPath.first.push_back({ j });
				}
			}
		}
		weight -= (path.back()).second;
		path.pop_back();
	}
	else {
		for (const auto& i : (*node).edges) { //Go through edges list of current nodes

			//Check if connecting node is already present in path
			bool added = false;
			for (const auto& j : path) { //Go through path vector until/if node is found
				if (j.first == i.first) {
					added = true;
					break;
				}
			}
			//If node is not present in path, add it
			if (!added) {
				weight += i.second;
				path.push_back({ i.first, i.second });
				pathFinder(path, i.first, destNode, weight, mode);
			}
		}
		if (mode == 1) {
			return;
		}
		weight -= (path.back()).second;
		path.pop_back();
	}
}