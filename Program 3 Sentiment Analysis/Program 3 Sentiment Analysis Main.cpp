#include "sentiment.h"


string userfile;
string file = "sentiment.txt";
vector<sentInfo> wordV, posV, negV, posReviewWords, negReviewWords;
vector<string> wordsWithSentiment, reviewToChange, onlySentimentWords;
vector<int> reviewIndexToChange;
float reviewSentimentSum, posSum, negSum;
bool again = true;


int main() {
	while (again) {
		cout << "Please enter the input file you would like to use: ";
		cin >> userfile;
		cout << endl;
		readFile(file, wordV, posV, negV);
		reviewToChange = originalText(userfile, wordV);
		onlySentimentWords = textWithSentiment(reviewToChange, wordV);
		posAndNegWordSeparator(onlySentimentWords, posReviewWords, negReviewWords, wordV);
		printVector(posReviewWords);
		printVector(negReviewWords);
		posSum = sumOfSentiment(posReviewWords);
		negSum = sumOfSentiment(negReviewWords);
		cout << "The original sentiment of this file is: " << setprecision(3) << reviewSentimentSum << "." << endl;
		if (posSum > negSum) {

		}
		else {

		}

		
		
		
	}
}