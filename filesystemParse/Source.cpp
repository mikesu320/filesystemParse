#include <iostream>
#include <string>
#include <vector>

using namespace std;


vector<string> split(string str, string delim) {
	
	vector<string> result;
	size_t pos_start =0, pos_end, delimlen = delim.length();
	string token;
	string work = str;
	do {
		pos_end = work.find(delim, 0);
		token = work.substr(0, pos_end);
		auto excludeSpac = token.find_first_not_of(' ');
		token = token.substr(excludeSpac);
		result.push_back(token);
		if (pos_end != string::npos)
			work = work.substr(pos_end + delimlen);
		else
			work = "";
	}
	while (work.length() > 0);
	
	return result;
}

int LengthOfLongPath(string fsys) {
	if (fsys.length() == 0)
		return 0;
	vector<string> tokens;
	tokens = split(fsys, "\f");
	vector<int> dirs(tokens.size());
	int maxGlob = 0;

	for (auto str : tokens) {
		auto level = str.find_first_not_of('\t');
		str=str.substr(level);
		if (str.find('.', 0) != string::npos) {
			int cleng = str.length();
			if (cleng != 0) {
				if (level > 0)
					cleng = dirs[level - 1] + str.length();
				else
					cleng = dirs[0] + str.length();
			}
			maxGlob = max(maxGlob, cleng);
		}
		else {
			dirs[level] = str.length() + 1;
			if (level != 0)
				dirs[level] += dirs[level - 1];
		}
	}

	return maxGlob;
 }

int depthParse(string str, vector<vector<string>> &len, int index) {

	if (str.length() == 0)
		return 0;
	int clevel = 0;
	string delim = "\f";
	size_t pos_end = str.find(delim, 0);
	string token = str.substr(0, pos_end);

	if (pos_end == string::npos)
		str = "";
	else
		str = str.substr(pos_end + 1);
	size_t tok_end = token.find("\t", 0);
	auto tabSize = token.find_first_not_of('\t');
	while (tok_end < string::npos) {
		clevel++;
		token = token.substr(tok_end + 1);
		tok_end = token.find("\t", 0);
	}
	if (len.size() < clevel + 1)
		len.push_back({});
	int sze = len[clevel].size();
	if (sze < index)
		len[clevel].assign(index, {});

	auto excludeSpac = token.find_first_not_of(' ');
	token = token.substr(excludeSpac);
	len[clevel].push_back(token);


	for (int i = 0; i < clevel; i++) {
		while (len[i].size() < len[clevel].size())
			len[i].push_back(len[i][len[i].size()-1]);
	}
	depthParse(str, len, len[clevel].size() - 1);
	return 0;

}



string tr0 = "aaaaa\fonbpkrpstgrfdgrvpqewxhjooewswpyksri";
string tl1 = "\f\tizqntvlaojkzpzkqzkmfblohpnybrgvlhisdhwwsaadxmlmysjrxwcghjoskgaubikfthtiexzkwkwkvhgamjigksguoqjzhldrgjgufrdj";
string tr2 = "\f\t\tkschoevfbpovzlecpktkkdshpzvckrlyrubduqpkrszqzfeptqwegaptsarcmiaenbuueyfszzbpcaacpxmgs";
string tr4 = "\f\t\t\tflrhsztlpfxjzwywtwewelnowgtimeflklocjsrewqmhqmtrprzizbzxsehxpmdrewmpodqudtmxpsujzqgzcjaskspupkikoxcc";
string tr5 = "\f\t\t\t\tcwyforrbvrdlrdkrfbxbrmxaeetu.nwrsumqsjqrujaztrwpdsytyihyepmakzxpoejtxburkhesbqvjfowxmqmvdgsrlqfmsqqvykcpggkwxn";
string tr6 = tr0 + tl1 + tr2 + tr4 + tr5;

int main() {
	string str = "user\n\tmustafa\n\t\tkitap\n\t\t\tzibar.txt\n\tmert2\n\t\tpictures2\n\tmert\n\t\tpictures\n\t\t\tdrive\n\t\t\t\tresim.jpg";
	string delim = "\t";
	delim = delim + delim;
	
	string fsys0 = "a.txt";
	string fsys3= "dir\f    file.txt";
	string fsys = "user\f\tpictures\f\tdocuments\f\t\tnotes.txt";
	string fsys2 = "user\f\tpictures\f\t\tphoto.png\f\t\tcamera\f\tdocuments\f\t\tlectures\f\t\t\tnotes.txt";
	string fsys5 = "dir\f\tfile.txt\f\tfile2.txt";
	string fsys6 = "a\f\tb.txt\fa2\f\tb2.txt";
	string fsys7 = "a\f\taa\f\t\taaa\f\t\t\tfile1.txt\faaaaaaaaaaaaaaaaaaaaa\f\tsth.png";

	
	vector<vector<string>> path;
	depthParse(fsys3, path,-1);
	cout << "func " << LengthOfLongPath(fsys3) << endl;
	string enddelim = ".";
	size_t maxPathGlob = 0;

	vector<size_t> maxPath(path[0].size(), 0);
	size_t maxpathlen = 0;
	
   	for (size_t col = 0; col < path[0].size(); col++) {
		for (size_t row = 0; row < path.size(); row++) {
			if (path[row].size() < col + 1) continue;
			string st = path[row][col];
			maxPath[col] += (st.length()) ? st.length() + ((row > 0) ? 1 : 0) : 0;
			size_t	word_end = st.find(enddelim, 0);
			if (word_end != string::npos) {
				if (row == 0 && col !=0)
					maxPath[col] += path[0][0].length()+1;
				maxPathGlob = max(maxPathGlob, maxPath[col]);
			}
			cout << path[row][col] << " " << maxPath[col] << endl;
		}
		cout << " " << maxPathGlob << endl;
	}
	cout << " " << maxPathGlob << endl;
	return 0;
 }


