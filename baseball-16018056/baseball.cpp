﻿#include <stdexcept>

using namespace std;

struct GuessResult {
	bool solved;
	int strikes;
	int balls;
};

class Baseball {
public:
	explicit Baseball(const string& question)
		: question(question) {

	}

	GuessResult guess(const string& guessNumber) {
		assertIllegalArgument(guessNumber);
		if (guessNumber == question) {
			return { true, 3, 0 };
		}
		int strikes = 0;
		int balls = 0;
		countStrikesAndBalls(guessNumber, strikes, balls);
		return { false, strikes, balls };
	}

	void countStrikesAndBalls(const std::string& guessNumber, int& strikes, int& balls)
	{
		for (int i = 0; i < guessNumber.length(); i++) {
			for (int j = 0; j < question.length(); j++) {
				if (guessNumber[i] != question[j])
					continue;
				if (i == j)
					strikes++;
				else
					balls++;
				break;
			}
		}
	}

	void assertIllegalArgument(const std::string& guessNumber)
	{
		if (guessNumber.length() != 3) {
			throw length_error("Must be three letters.");
		}

		for (char ch : guessNumber) {
			if ('0' <= ch && ch <= '9') continue;
			throw invalid_argument("Must be number");
		}

		if (isDuplicatedNumber(guessNumber)) {
			throw invalid_argument("Must not have the same number");
		}
	}

	bool isDuplicatedNumber(const std::string& guessNumber)
	{
		return guessNumber[0] == guessNumber[1]
			|| guessNumber[0] == guessNumber[2]
			|| guessNumber[1] == guessNumber[2];
	}

private:
	string question;
};