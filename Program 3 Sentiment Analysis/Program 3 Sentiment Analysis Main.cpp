//Tom Steinman
//CS201R-0005
//Program 3 - Sentiment

#include "sentiment.h"

string userfile;
string file = "sentiment.txt";
vector<sentInfo> wordV, posV, negV, posReviewWords, negReviewWords, posToChange, negToChange, negToPosV, posToNegV;
vector<string> wordsWithSentiment, reviewToChange, lowerCaseReview, onlySentimentWords, finalReview;
bool again = true;
string changeOption, playAgain;

int main() {
	while (again) {
		float reviewSentimentSum = 0, posSum = 0, negSum = 0, finalSentimentSum = 0, finalPosSum = 0, finalNegSum = 0;
		cout << "Please enter the input file you would like to use: ";
		cin >> userfile;
		cout << endl;
		readFile(file, wordV, posV, negV);
		reviewToChange = originalText(userfile, wordV);
		lowerCaseReview = reviewToChange;
		lowerCaseNoPunctV(lowerCaseReview);
		onlySentimentWords = textWithSentiment(lowerCaseReview, wordV);
		posAndNegWordSeparator(onlySentimentWords, posReviewWords, negReviewWords, wordV);
		posSum = sumOfSentiment(posReviewWords);
		negSum = sumOfSentiment(negReviewWords);
		reviewSentimentSum = posSum + negSum;
		cout << "The original sentiment of this file is: " << setprecision(4) << reviewSentimentSum << "." << endl << endl;

		changeOption = userChangeToReview();
		if (changeOption == "P") {
			cout << endl << "Okay! I will edit file: " << userfile << " to be more positive!" << endl << endl;
			negToChange = underNegOne(negReviewWords);
			if (negToChange.size() == 0) {
				cout << "This review has 0 significant negative words. It is already positive." << endl << endl;
					continue;
			}
			negToPosV = negativeReplacement(negToChange, posV);
			printWordstoChange(negToChange, negToPosV);
			positiveSentimentChange(reviewToChange,lowerCaseReview, negToChange, negToPosV);
			lowerCaseReview.clear();
			lowerCaseReview = reviewToChange;
			lowerCaseNoPunctV(lowerCaseReview);
			onlySentimentWords.clear();
			posReviewWords.clear();
			negReviewWords.clear();
			onlySentimentWords = textWithSentiment(lowerCaseReview, wordV);
			posAndNegWordSeparator(onlySentimentWords, posReviewWords, negReviewWords, wordV);
			finalPosSum = sumOfSentiment(posReviewWords);
			finalNegSum = sumOfSentiment(negReviewWords);
			finalSentimentSum = finalPosSum + finalNegSum;
			cout << endl << "After this change the new file is:" << endl << endl;
			readReviewVector(reviewToChange);
			cout << endl << "New sentiment value: " << setprecision(4) << finalSentimentSum << "." << endl << endl;
		}
		else if (changeOption == "N") {
			cout << endl << "Okay! I will edit file: " << userfile << " to be more negative!" << endl << endl;
			posToChange = overPosOne(posReviewWords);
			if (posToChange.size() == 0) {
				cout << "This review has 0 significant positive words. It is already negative." << endl << endl;
				continue;
			}
			posToNegV = positiveReplacement(posReviewWords, negV);
			printWordstoChange(posToChange, posToNegV);
			negativeSentimentChange(reviewToChange, lowerCaseReview, posToChange, posToNegV);
			lowerCaseReview.clear();
			lowerCaseReview = reviewToChange;
			lowerCaseNoPunctV(lowerCaseReview);
			onlySentimentWords.clear();
			posReviewWords.clear();
			negReviewWords.clear();
			onlySentimentWords = textWithSentiment(lowerCaseReview, wordV);
			posAndNegWordSeparator(onlySentimentWords, posReviewWords, negReviewWords, wordV);
			finalPosSum = sumOfSentiment(posReviewWords);
			finalNegSum = sumOfSentiment(negReviewWords);
			finalSentimentSum = finalPosSum + finalNegSum;
			cout << endl << "After this change the new file is:" << endl << endl;
			readReviewVector(reviewToChange);
			cout << endl << "New sentiment value: " << setprecision(4) << finalSentimentSum << "." << endl << endl;

		}
		cout << endl << "Input Q to quit. Input any key you like to view and/or edit another file" << endl;
		cin >> playAgain;
		if (playAgain == "Q" || playAgain == "q" || playAgain == "quit") {
			again = false;
		}
		else {
			lowerCaseReview.clear();
			onlySentimentWords.clear();
			posToChange.clear();
			posToNegV.clear();
			reviewToChange.clear();
			negReviewWords.clear();
			posReviewWords.clear();
			again = true;
		}
	}
}

