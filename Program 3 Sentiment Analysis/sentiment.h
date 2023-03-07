
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <string>

using namespace std;

struct sentInfo {
	string word;
	float value;
};

struct punctuation {
	char punct;
	int index;
};


void readFile(string file, vector<sentInfo>& wordV, vector<sentInfo>& posV, vector<sentInfo>& negV);
bool isValid(string str);
void printVector(vector<sentInfo> v1);
vector<string> originalText(string userfile, vector<sentInfo>& wordV);
bool hasTheWord(vector<sentInfo>& wordV, string word);
vector<string> textWithSentiment(vector<string> textWithSentiment, vector<sentInfo>& wordV);
vector<string> sentimentWords(vector<int> reviewIndexToChange, vector<string> reviewToChange);
sentInfo wordAndSentiment(vector<sentInfo>& wordV, string& word);
void posAndNegWordSeparator(vector<string>& reviewToChange, vector<sentInfo>& posReviewWords, vector<sentInfo>& negReviewWords, vector<sentInfo>& wordV);
float sumOfSentiment(vector<sentInfo>& v2);
