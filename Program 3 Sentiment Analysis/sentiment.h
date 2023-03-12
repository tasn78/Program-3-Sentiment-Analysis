
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <string>
#include <time.h>

using namespace std;

struct sentInfo {
	string word;
	float value;
};

struct punctuation {
	char punct;
	int index;
};


void readFile(string file, vector<sentInfo>& wordV, vector<sentInfo>& posV, vector<sentInfo>& negV); // Given in class 201R
bool isValid(string str);																			 // Given in class 201R
void printVector(vector<sentInfo> v1);																 // Given in class 201R
vector<string> originalText(string userfile, vector<sentInfo>& wordV);								 // Given in class 201R
void lowerCaseNoPunctV(vector<string>& lowerCaseReview);
bool hasTheWord(vector<sentInfo>& wordV, string word);
vector<string> textWithSentiment(vector<string> textWithSentiment, vector<sentInfo>& wordV);

sentInfo wordAndSentiment(vector<sentInfo>& wordV, string& word);
void posAndNegWordSeparator(vector<string>& reviewToChange, vector<sentInfo>& posReviewWords, vector<sentInfo>& negReviewWords, vector<sentInfo>& wordV);
float sumOfSentiment(vector<sentInfo>& v2);
string userChangeToReview();
void positiveSentimentChange(vector<string>& reviewToChange, vector<string>& lowerCaseReview, vector<sentInfo>& negReviewWords, vector<sentInfo>&);
void negativeSentimentChange(vector<string>& reviewToChange, vector<string>& lowerCaseReview, vector<sentInfo>& posReviewWords, vector<sentInfo>&);

bool indexToChange(string word, vector<sentInfo> posOrNegV);
void readReviewVector(vector<string> review);

vector<sentInfo> underNegOne(vector<sentInfo>& negReviewWords);
vector<sentInfo> overPosOne(vector<sentInfo>& posReviewWords);

vector<sentInfo> positiveReplacement(vector<sentInfo>& negReviewWords, vector<sentInfo>& posV);
vector<sentInfo> negativeReplacement(vector<sentInfo>& negReviewWords, vector<sentInfo>& negV);

void printWordstoChange(vector<sentInfo>&, vector<sentInfo>&);
