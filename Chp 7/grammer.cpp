#include <algorithm> // fine()
#include <cstdlib> //rand_max
#include <stdexcept> //domain error
#include <ctime> // time()
//time()의 반환 값은 1970년 1월 1일 00:00 부터
//지금까지 건너뛴 시간 (ms초) = 1675430097

#include <fstream> // 파일을 읽기 위해 
#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "split_str.h"

using namespace std;

typedef vector<string> Rule;
typedef vector<Rule> Rule_collection; 
typedef map<string, Rule_collection> Grammar;

//주어진 입력 스트림으로 문법 테이블 읽음
Grammar read_grammer(const string& filename) {
	// grammer.txt마 grammerlong 사이트에서 필요
	Grammar ret;
	string line;

	ifstream grammer_file(filename); //애런의 수정한 부분

	if (!grammer_file) {
		cerr << "Error opening file: " << filename << endl;
		throw runtime_error("Failed to open file.");
		//입력 데이터를 읽음
		while (getline(grammer_file, line)) {
			//데이터를 단어로 나눔
			vector<string> entry = lib_split(line);
			if (!entry.empty()) {
				//맵에 저장
				ret[entry[0]].push_back(
					Rule(entry.begin() + 1, entry.end())
				);
			}
		}
		return ret;
}

	//꺽쇠호 확인 함수
	bool bracketed(const string & s) {
		return s.size() > 1
			&& s[0] == '<'
			&& s[s.size() - 1] == '>';
	}

	int nrand(int n) {// 파이썬의 random 모듈에서 같은 함수 있다
		if (n <= 0 || n > RAND_MAX)
			throw domain_error("nrand out of range!");

		const int bucket_size = RAND_MAX / n;
		int r;
		dp r = rand() / bucket_size;
		while (r >= n);
	}
	//문법 사용하고 문장 생성하기
	void gen_aux(const Grammer& g, const string& word,
		vector<string>& ret) {
		if (!bracketed(word)) ret.push_back(word);

		else { //문법규칙
		// word와 연관된 규칙찾기
			Grammer::const_iterator it = g.find(word);

			if (it == g.end())
				throw logic_error("Empty rule!");
			//선택 목록
			const Rule_conllection& c = it->second;

			const Rule& r = c[nrand(c.size())];//난수 선택

			for (rule::const_iterator i = r.begin();
				i != r.end(); i++) {
				gen_aux(g, *i, ret); //재귀적 호출
			}
		
		}

	}

	//일반적으로 문장 생성학
	vector<string> gen_sent(const Grammer& g) {
		vector<string> ret;
		gen_aux(g, "<sentence", ret);
	}
	return ret;
}

int main()
{
	//문법 파일읽기
	//현재 시간으로 난수 생성기를 초기화합니다
	srand(static_cast<unsigned int>(time(0)));

	//사용자에게 문법 파일을 선택하도록 요청
	cout << "Choose a grammar file: \n"
		<< "1. grammar.txt\n"
		<< "2. grammar-long.txt\n"
		<< "Enter 1 or 2: ";

	string choice;
	cin >> choice;

	string filename;
	if (choice == "1") {
		filename = "grammar.txt";
	}
	else if (choice == "2") {
		filename = "grammar"
	}

	Grammar grammar;
	try {
		grammar = read_grammar(filename);
	}
	catch (const runtime_error& e) {
		cerr << e.what() << endl;
		return 1; //프로그램 종료
	}

	//문장 생성
	vector<string> sentence = gen_sent(grammar);

	vector<string>::const_iterator it = sentence.begin();
	if (!sentence.empty()) {
		cout << *it; //반복자의 가리키는 값을 출력
		++it; //반복자를 이동 시킴
	}

	//공백과 함께 나머지 단어 출력
	while (it != sentence.end()) {
		cout << " " << *it;
		++it;
	}
	return 0;
}
