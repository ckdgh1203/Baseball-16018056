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
		else if (is2Strike0Ball(guessNumber)) {
			return { false, 2, 0 };
		}
		else if (is1Strike2Ball(guessNumber)) {
			return { false, 1, 2 };
		}

		return { false, 0, 0 };
	}

	bool is1Strike2Ball(const std::string& guessNumber)
	{
		return (guessNumber[0] == question[0] && guessNumber[1] == question[2] && guessNumber[2] == question[1])
			|| (guessNumber[1] == question[1] && guessNumber[0] == question[2] && guessNumber[2] == question[0])
			|| (guessNumber[2] == question[2] && guessNumber[0] == question[1] && guessNumber[1] == question[0]);
	}

	bool is2Strike0Ball(const std::string& guessNumber)
	{
		return (guessNumber[0] == question[0] && guessNumber[1] == question[1])
			|| (guessNumber[0] == question[0] && guessNumber[2] == question[2])
			|| (guessNumber[0] == question[0] && guessNumber[2] == question[2]);
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