#include <iostream>
#include <string>
#include <vector>

using namespace std;


string split(string str, string delim) {
	
	string result="";
	size_t pos_start =0, pos_end, delimlen = delim.length();
	string token;
	string work = str;
	
	while ((pos_end = work.find(delim, 0)) != string::npos) {
		token = work.substr(0, pos_end);
		result = result+token;
		work = work.substr(pos_end + delimlen);
	}
	return result;
}


int depthFirstParse(string str, int *level , vector<string> &len) {
	size_t  pos_end, word_end;
	string delim = "\t";
	string enddelim = ".";
	if (str.length() == 0)
		return 0;
	int clevel = *level;
	pos_end = str.find(delim, 0);
	word_end = str.find(enddelim, 0);
	string token = str.substr(0, pos_end);
	
	if (word_end < pos_end) {
		// Found the dotfile
		len.push_back(token + "/");
		return 1;
	}
	else if (token.length() == 0) {
		(*level)++;
	}
	else {
		(*level)++;
		if (depthFirstParse(str.substr(pos_end + 1), level, len)) {
			string add = len.back() + token + "/";
			len.pop_back();
			len.push_back(add);
			return 1;
		}
	}
	return 0;
}


int main() {
	string str = "user\n\ttmustafa\n\t\tkitap\n\t\t\tzibar.txt\n\tmert\n\t\tpictures\n\t\t\tresim.jpg";
	string delim = "\t";
	delim = delim + delim;
	string parsed = split(str, "\n");
	string parsed2 = split(parsed, "\t");
	string parsed3 = split(parsed, "\t\t");
	string parsed4 = split(parsed, "\t\t\t");
	//cout << str << endl;
	cout << parsed << endl;
	cout << parsed2 << endl;
	cout << parsed3 << endl;
	cout << parsed4 << endl;

	for (auto c : str)
		cout << c - 'A' << " ";
	vector<string> path;
	int level = 0;
	depthFirstParse(parsed, &level , path);
	for (auto x : path)
		cout << x << endl;
	return 0;
}
