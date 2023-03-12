#include "sentiment.h"

void readFile(string file, vector<sentInfo>& wordV, vector<sentInfo>& posV, vector<sentInfo>& negV) { // Given in class 201R
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
			wordV.push_back(tempInfo);                // push values onto the vector that are greater than 1.5 or less than 1.5
			if (tempInfo.value > 1.5)
				posV.push_back(tempInfo);
			else if (tempInfo.value < -1.5)
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

void lowerCaseNoPunctV(vector<string>& lowerCaseReview) {
	for (int i = 0; i < lowerCaseReview.size(); i++) {			//  https://stackoverflow.com/questions/19138983/c-remove-punctuation-from-string
		lowerCaseReview[i].erase(std::remove_if(lowerCaseReview[i].begin(), lowerCaseReview[i].end(), ispunct), lowerCaseReview[i].end());  // removes all punctuation
		transform(lowerCaseReview[i].begin(), lowerCaseReview[i].end(), lowerCaseReview[i].begin(),      // https://stackoverflow.com/questions/313970/how-to-convert-an-instance-of-stdstring-to-lower-case
			[](unsigned char c) { return std::tolower(c); });									//Converts all chars to lower case
	}
}

vector<string> textWithSentiment(vector<string> textWithSentiment, vector<sentInfo>& wordV) {
	vector<string> textSentiment;
	for (int i = 0; i < textWithSentiment.size(); i++) {
		if (hasTheWord(wordV, textWithSentiment[i]) == true) {
			textSentiment.push_back(textWithSentiment[i]);
		}
	}
	return textSentiment;
}

sentInfo wordAndSentiment(vector<sentInfo>& wordV, string& word) {
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
			return wordV[mid];
		}
	}
}

void posAndNegWordSeparator(vector<string>& reviewToChange, vector<sentInfo>& posReviewWords, vector<sentInfo>& negReviewWords, vector<sentInfo>& wordV) {
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

void positiveSentimentChange(vector<string>& reviewToChange, vector<string>& lowerCaseReview, vector<sentInfo>& negToReplace, vector<sentInfo>& negToPosV) {
	vector<int> indexToSwitch;
	srand(time(NULL));
	char punct;

	for (auto k = 0; k < lowerCaseReview.size(); ++k) {
		if (indexToChange(lowerCaseReview[k], negToReplace)) {
			indexToSwitch.push_back(k);
		}
	}

	for (auto i = 0; i < indexToSwitch.size(); ++i) {
		int k = indexToSwitch[i];
		for (int y = 0; y < reviewToChange[k].length(); ++y) {
			if (ispunct(reviewToChange[k][y])) {
				punct = reviewToChange[k][y];
				reviewToChange[k] = negToPosV[i].word + punct;
			}
			else {
				reviewToChange[k] = negToPosV[i].word;
			}
		}
		
	}
}

void negativeSentimentChange(vector<string>& reviewToChange, vector<string>& lowerCaseReview, vector<sentInfo>& posWords, vector<sentInfo>& posToNegV) {
	vector<sentInfo> posToReplace;
	vector<int> indexToSwitch;
	char punct;

	for (auto k = 0; k < lowerCaseReview.size(); ++k) {
		if (indexToChange(lowerCaseReview[k], posWords) == true) {
			indexToSwitch.push_back(k);
		}
	}

	for (auto i = 0; i < indexToSwitch.size(); ++i) {
		int k = indexToSwitch[i];
		for (int y = 0; y < reviewToChange[k].length(); ++y) {
			if (ispunct(reviewToChange[k][y])) {
				punct = reviewToChange[k][y];
				reviewToChange[k] = posToNegV[i].word + punct;
			}
			else {
				reviewToChange[k] = posToNegV[i].word;
			}
		}
	}
}


bool indexToChange(string word, vector<sentInfo> posOrNegV) {
	for (int z = 0; z < posOrNegV.size(); ++z) {
		if (posOrNegV[z].word == word) {
			return true;
		}
	}
	return false;
}

void readReviewVector(vector<string> review) {
	int count = 0;
	for (auto i = 0; i < review.size(); ++i) {
		cout << review[i] << " ";
		count += review[i].size() + 1;
		if (count >= 80) {
			cout << endl;
			count = 0;
		}
	}
	cout << endl;
}

vector<sentInfo> underNegOne(vector<sentInfo>& negReviewWords) {
	vector<sentInfo> negChange;
	for (auto i = 0; i < negReviewWords.size(); ++i) {
		if (negReviewWords[i].value < -1) {
			negChange.push_back(negReviewWords[i]);
		}
	}
	return negChange;
}
vector<sentInfo> overPosOne(vector<sentInfo>& posReviewWords) {
	vector<sentInfo> posChange;
	for (auto i = 0; i < posReviewWords.size(); ++i) {
		if (posReviewWords[i].value > 1) {
			posChange.push_back(posReviewWords[i]);
		}
	}
	return posChange;
}

vector<sentInfo> positiveReplacement(vector<sentInfo>& posToChange, vector<sentInfo>& posV) {
	srand(time(NULL));
	vector<sentInfo> negToPosV;
	for (auto i = 0; i < posToChange.size(); i++) {
		negToPosV.push_back(posV[rand() % posV.size() - 1]);
	}
	return negToPosV;
}
vector<sentInfo> negativeReplacement(vector<sentInfo>& negToChange, vector<sentInfo>& negV) {
	vector<sentInfo> posToNegV;
	srand(time(NULL));
	for (auto i = 0; i < negToChange.size(); i++) {
		posToNegV.push_back(negV[rand() % negV.size() - 1]);
	}
	return posToNegV;
}

void printWordstoChange(vector<sentInfo>& before, vector<sentInfo>& after) {
	for (auto i = 0; i < before.size(); i++) {
		cout << setw(15) << before[i].word << setw(10) << before[i].value;
		cout << setw(15) << after[i].word << setw(10) << after[i].value << endl;
	}
	cout << endl;
}