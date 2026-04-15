#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "C:\Users\com316\Desktop\hello cpp\6-cpp-library-algorithms-2026-whwkfyd\Chp 6\split_str.h"

using namespace std;

map<string, vector<int> > xref(
	istream& in,
	vector<string> find_words(const string&) = lib_split)

{
	string line;
	int line_num = 0;
	map <string, vector<int> > ret;

	while (getline(in, line)) {
		++line_num;

		//입력한 행을 단어로 나눔
		vector<string> words = find_words(line);

		for (vector<string>::const_iterator it = words.begin();
			it != words.end(); ++it) {
				if (ret[*it].empty() || ret[*it].back() != line_num) {
					ret[*it].push_back(line_num);
				}
		}
	}
	return ret;
}

/*
  7-7(한 행 번호만 출력) 한 줄에 단어가 두 번 이상 나타나면
  줄 번호를 여러 번 츌력하지 않고 한 번만 출력하세요
*/
int main()
{
	map<string, vector<int> > ret = xref(cin);

	for (map<string, vector<int> >::const_iterator it = ret.begin();
		it != ret.end(); ++it) {

		cout << "\"" << it->first << "\" is on line(s): ";

		vector<int>::const_iterator line_it = it->second.begin();

		cout << *line_it;
		++line_it;

		//행 번호가 더있으면 마저 출력
		while (line_it != it->second.end()) {
			cout << ", " << *line_it;
			++line_it;
		}
		//각 단어를 다음 단어와 구분하려고 새로운 행을 출력
		cout << endl;
	}
	return 0;
}
