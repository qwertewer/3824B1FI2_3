#include <iostream>
#include <vector>
#include "TStack.h"
#include "TPostfix.h"

using namespace std;
int main() {
	try {
		//TPostfix tst("((cos(x) + 5.2 * 2)* (a - -b) / 5 + 1)");
		TPostfix tst("cos(cos(cos(1)))");
		vector<string> ops(tst.GetOperands());
		vector<double> vals;
		cout << tst.GetInfix() << '\n';
		for (auto& op : ops) {
			cout << "Enter " << op << ' ';
			double e;
			cin >> e;
			vals.push_back(e);
		}
		vector<pair<string, double>> clc;
		for (int i = 0; i < ops.size(); ++i) {
			clc.push_back(make_pair(ops[i], vals[i]));
		}
		cout << tst.GetPostfix() << '\n';
		cout << tst.Calculate(clc) << '\n';
		cout << tst.Calculate() << '\n';
	}
	catch (std::exception err) {
		cerr << err.what();
	}
}