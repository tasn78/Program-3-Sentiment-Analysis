#include "sentiment.h"

void readFile(string file, vector<sentInfo>& wordV, vector<sentInfo>& posV, vector<sentInfo>& negV) {
	ifstream inFile;
	inFile.open(file);
	if (!inFile.is_open()) {
		cout << "Input file invalid\n";
		return;
	}
	string inStr, wordStr, valueStr;
	sentInfo tempInfo;
	int commaPos;
	while (inFile >> inStr) {                     // Read file into a string
		commaPos = inStr.find(',');                 // Find location of comma
		wordStr = inStr.substr(0, commaPos);       // set wordStr to inStr up to the comma
		valueStr = inStr.substr(commaPos + 1);      // set valueStr to the end of inStr
		if (isValid(valueStr)) {                    // check valueStr has valid numbers
			tempInfo.word = wordStr;                  // load a sentInfo type with this data
			tempInfo.value = stof(valueStr);
			wordV.push_back(tempInfo);                // push it onto the vector
			if (tempInfo.value > 0)
				posV.push_back(tempInfo);
			else if (tempInfo.value < 0)
				negV.push_back(tempInfo);
		}
		else {
			cout << "Input value not valid\n";
			continue;
		}
	}
	inFile.close();
}

bool isValid(string str) {
	return str.find_first_not_of("0123456789.-") == string::npos;
}

void printVector(vector<sentInfo> v1) {
	for (int i = 0; i < v1.size(); i++) {
		cout << v1[i].word << " " << v1[i].value << endl;
	}
}

vector<string> originalText(string userfile, vector<sentInfo>& wordV) {
	ifstream File;
	string text;
	vector<string> textWithSentiment;
	while (true) {
		File.open(userfile);
		if (!File.is_open()) {
			cout << "Input file invalid\n";
			continue;
		}
		else {
			while (File.good()) {
				File >> text;
				cout << text << " ";
				textWithSentiment.push_back(text);
			}
		}
		cout << endl;
		return textWithSentiment;
	}
}

bool hasTheWord(vector<sentInfo>& wordV, string word) {
	int low = 0;
	int high = wordV.size() - 1;
	while (high >= low) {
		int mid = (high + low) / 2;  // low + (high - low) / 2
		if (wordV[mid].word < word) {
			low = mid + 1;
		}
		else if (wordV[mid].word > word) {
			high = mid - 1;
		}
		else {
			return true;
		}
	}
	return false;
}

vector<string> textWithSentiment(vector<string> textWithSentiment, vector<sentInfo>& wordV) {
	vector<string> textSentiment;
	for (int i = 0; i < textWithSentiment.size(); i++) {			//  https://stackoverflow.com/questions/19138983/c-remove-punctuation-from-string
		textWithSentiment[i].erase(std::remove_if(textWithSentiment[i].begin(), textWithSentiment[i].end(), ispunct), textWithSentiment[i].end());
		if (hasTheWord(wordV, textWithSentiment[i]) == true) {
			textSentiment.push_back(textWithSentiment[i]);
		}
	}
	return textSentiment;
}


vector<punctuation> getPunctuation(vector<string> onlySentimentWords) {
	vector<punctuation> punctuationUsed;
	char punctInString;
	int index;
	for (int i = 0; i < onlySentimentWords.size() - 1; i++) {
		string str = onlySentimentWords[i];
		for (int j = 0; j < str.size(); j++)
			if (str.at(j).ispunct()) {
				
		}
	}
}
// https://stackoverflow.com/questions/49294428/find-punctuation-in-string-c


sentInfo wordAndSentiment(vector<sentInfo>& wordV, string &word) {
	int low = 0;
	int high = wordV.size() - 1;

	for (int i = 0, len = word.size(); i < len; i++) {				//https://www.geeksforgeeks.org/removing-punctuations-given-string/
		if (ispunct(word[i])) {
			word.erase(i--, 1);
			len = word.size();
		}
	}
	while (high >= low) {
		int mid = (high + low) / 2;  // low + (high - low) / 2
		if (wordV[mid].word < word) {
			low = mid + 1;
		}
		else if (wordV[mid].word > word) {
			high = mid - 1;
		}
		else {
			return wordV[mid];
		}
	}
}

void posAndNegWordSeparator(vector<string> &reviewToChange, vector<sentInfo>& posReviewWords, vector<sentInfo>& negReviewWords, vector<sentInfo>& wordV) {
	for (int i = 0; i < reviewToChange.size(); ++i) {
		sentInfo sentimentWord = wordAndSentiment(wordV, reviewToChange[i]);
		if (sentimentWord.value > 0) {
			posReviewWords.push_back(sentimentWord);
		}
		else if (sentimentWord.value < 0) {
			negReviewWords.push_back(sentimentWord);
		}
	}
}

float sumOfSentiment(vector<sentInfo>& v2) {
	float sentimentSum = 0;
	for (int i = 0; i < v2.size(); ++i) {
		sentimentSum += v2[i].value;
	}
	return sentimentSum;
}

string userChangeToReview() {
	string optionChoice;
	while (true) {
		cout << "What would you like to do?" << endl << endl;
		cout << "P - Change from Negative to Positive" << endl;
		cout << "N - Change from Positive to Negative" << endl;
		cout << "Q - Quit" << endl;
		cin >> optionChoice;
		if (optionChoice == "p" || optionChoice == "P") {
			return "P";
		}
		else if (optionChoice == "n" || optionChoice == "N") {
			return "N";
		}
		else if (optionChoice == "q" || optionChoice == "Q") {
			return "Q";
		}
		else {
			cout << "Please enter P, N, or Q." << endl;
				continue;
		}
	}
}

void positiveSentimentChange(vector<string>& reviewToChange, vector<string>& onlySentimentWords, vector<sentInfo>& negWords) {
	vector<sentInfo> negToReplace;
	vector<int> indexToSwitch;
	srand(time(NULL));
	char punct;
	for (auto i = 0; i < negWords.size(); ++i) {
		if (negWords[i].value < -1) {
			negToReplace.push_back(negWords[i]);
		}
	}

	indexToSwitch = indexToChange(reviewToChange, negWords);

	for (auto i = 0; i < indexToSwitch.size(); ++i) {
		int k = indexToSwitch[i];
		for (int y; y < reviewToChange[k].length(); ++y) {
			if (ispunct(reviewToChange[k][y])) {
				punct = reviewToChange[k][y];
			}
		}
		reviewToChange[k] = negWords[rand() % negWords.size() - 1].word;
	}
}

void negativeSentimentChange(vector<string>& reviewToChange, vector<string>& onlySentimentWords, vector<sentInfo> posWords) {

}

vector<int> indexToChange(vector<string> reviewToChange, vector<sentInfo> posOrNegV) {
	int low = 0;
	int high = posOrNegV.size() - 1;
	vector<int> indexToChange;

	for (int i; i < reviewToChange.size(); ++i) {
		for (int c = 0, len = reviewToChange[i].size(); c < len; c++) {				//https://www.geeksforgeeks.org/removing-punctuations-given-string/
			if (ispunct(reviewToChange[i][c])) {
				reviewToChange[c].erase(c--, 1);
				len = reviewToChange[i].size();
			}
		}
	}
	for (int x; x < reviewToChange.size(); ++x) {
		for (int k; k < posOrNegV.size(); k++) {
			if (posOrNegV[k].word == reviewToChange[x]) {
				indexToChange.push_back(x);
			}
		}
	}
	return indexToChange;
}

void readReviewVector(vector<string> review) {
	for (auto i = 0; i < review.size(); ++i) {
		cout << review[i] << " ";
	}
}
