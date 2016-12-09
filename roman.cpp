/*
 * roman.cpp
 *
 *  Created on: 8 déc. 2016
 *      Author: hnnguyen
 */

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <map>
#include <algorithm>

std::map<char, int> Numerals;
std::vector<char> Digits {'I','V','X','L','C','D','M'};
std::vector<char> key { 'I', 'IV', 'V', 'IX', 'X', 'L', 'C', 'D', 'M' };
std::vector<int> value { 1, 4, 5, 9, 10, 50, 100, 500, 1000 };
std::vector<std::string> ignoreCases { "IL", "IC", "ID", "IM", "VC", "VX", "VD",
		"VM", "VL", "XD", "XM", "LC", "LD", "LM", "LL", "VV", "DD" };

bool checkValidRomanNumber(std::string strNum) {
	int len = strNum.length();
	int count = 0;
	//check all character are valid
	for (int var = 0; var < len; ++var) {
		auto resultFind = std::find(std::begin(Digits),std::end(Digits),strNum[var]);
		if (resultFind == std::end(Digits)) {
			std::cout << "There is invalid input";
			return false;
		}
	}

	for (int var = 0; var < len; ++var) {
		//Verify that there is no IIII or XXXX or CCCC
		if (len >= 4) {
			std::string subStrConsecutiveFourDigits = strNum.substr(var,
					var + 3);
			if ((subStrConsecutiveFourDigits.compare("IIII") == 0)
					|| (subStrConsecutiveFourDigits.compare("CCCC") == 0)
					|| (subStrConsecutiveFourDigits.compare("XXXX") == 0)) {
				std::cout << "There is IIII or XXXX or CCCC\n";
				return false;
			}
		}
//		//Verify that there is no LLL or VVV or DDD
//		std::string subStrConsecutiveThreeDigits = strNum.substr(var, var + 2);
//		if ((subStrConsecutiveThreeDigits.compare("LLL") != 0)
//				|| (subStrConsecutiveThreeDigits.compare("VVV") != 0)
//				|| (subStrConsecutiveThreeDigits.compare("DDD") != 0)) {
//			std::cout << "There is IIII or LLL or ";
//			return false;
//		}

		//Verify that there is no ignore case
		std::string subStrConsecutiveTwoDigits = strNum.substr(var, var + 1);
		auto resultFind = std::find(std::begin(ignoreCases),
				std::end(ignoreCases), subStrConsecutiveTwoDigits);
		if (resultFind != std::end(ignoreCases)) {
			std::cout << "There is an ignore case\n"  << std::endl;
			return false;
		}

		//Verify that after C there is at most one M or D
		if (strNum[var] == 'C') {
			count = 0;
			for (int i = var + 1; i < len; ++i) {
				if ((strNum[i] == 'D') || (strNum[i] == 'M')) {
					count += 1;
				}
				if (count >= 2) {
					std::cout << "There is more than one M or D after C\n";
					return false;
				}
			}
		}

		//Verify that after X there is no M or D
		if (strNum[var] == 'X') {
			for (int i = var + 1; i < len; ++i) {
				if ((strNum[i] == 'D') || (strNum[i] == 'M')) {
					std::cout << "There is M or D after X\n";
					return false;
				}
			}
		}

		//Verify that after X there is at most ome C or L
		if (strNum[var] == 'X') {
			count = 0;
			for (int i = var + 1; i < len; ++i) {
				if ((strNum[i] == 'C') || (strNum[i] == 'L')) {
					count++;
				}
				if (count >= 2) {
					std::cout << "There is more than one C or L after X\n";
					return false;
				}
			}
		}

		//Verify that after I there is no M or D or C or L
		if (strNum[var] == 'I') {
			for (int i = var + 1; i < len; ++i) {
				if ((strNum[i] == 'D') || (strNum[i] == 'M')
						|| (strNum[i] == 'C') || (strNum[i] == 'L')) {
					std::cout << "There is M or D or C or L after I\n";
					return false;
				}
			}
		}

		//Verify that after I there is at most ome X or V
		if (strNum[var] == 'I') {
			count = 0;
			for (int i = var + 1; i < len; ++i) {
				if ((strNum[i] == 'V') || (strNum[i] == 'X')) {
					count++;
				}
				if (count >= 2) {
					return false;
				}
			}
		}

		//Verify that after D there is no M
		if (strNum[var] == 'D') {
			for (int i = var + 1; i < len; ++i) {
				if (strNum[i] == 'M') {
					return false;
				}
			}
		}

		//Verify that after C there is at most one M or D
		if (strNum[var] == 'C') {
			count = 0;
			for (int i = var + 1; i < len; ++i) {
				if ((strNum[i] == 'D') || (strNum[i] == 'M')) {
					count += 1;
				}
				if (count >= 2) {
					return false;
				}
			}
		}

		//Verify that after L there is no M or D or C
		if (strNum[var] == 'L') {
			for (int i = var + 1; i < len; ++i) {
				if ((strNum[i] == 'C') || (strNum[i] == 'D')
						|| (strNum[i] == 'M')) {
					return false;
				}
			}
		}

		//Verify that after V there is no M or D or C or L or X
		if (strNum[var] == 'V') {
			for (int i = var + 1; i < len; ++i) {
				if ((strNum[i] == 'X') || (strNum[i] == 'L')
						|| (strNum[i] == 'C') || (strNum[i] == 'D')
						|| (strNum[i] == 'M')) {
					return false;
				}
			}
		}
	}

	return true;
}
int convertRomanToArabic(std::string strNumRoman) {
	int retVal = 0;
	if (!checkValidRomanNumber(strNumRoman)) {
		std::cout << "Invalid input" << std::endl;
	} else {
		int len = strNumRoman.length();
		int i = 0;
		while (i < len) {
			if (strNumRoman[i] == 'M') {
				retVal += 1000;
				i++;
				std::cout << "Current Value is " << retVal << " Position " << i << std::endl;
			} else if (strNumRoman[i] == 'C') {
				if (i < len) {
					if (strNumRoman[i + 1] == 'M') {
						retVal += 900;
						i += 2;
						std::cout << "Current Value is " << retVal << " Position " << i << std::endl;
					} else if (strNumRoman[i + 1] == 'D') {
						retVal += 400;
						i += 2;
						std::cout << "Current Value is " << retVal << " Position " << i << std::endl;
					} else {
						retVal += 100;
						i++;
						std::cout << "Current Value is " << retVal << " Position " << i << std::endl;
					}
				} else {
					retVal += 100;
					i++;
					std::cout << "Current Value is " << retVal << " Position " << i << std::endl;
				}
			} else if (strNumRoman[i] == 'D') {
				retVal += 500;
				i++;
				std::cout << "Current Value is " << retVal << " Position " << i << std::endl;
			} else if (strNumRoman[i] == 'C') {
				if (i < len-1) {
					if (strNumRoman[i + 1] == 'D') {
						retVal += 400;
						i += 2;
						std::cout << "Current Value is " << retVal << " Position " << i << std::endl;
					} else if (strNumRoman[i + 1] == 'M') {
						retVal += 900;
						i += 2;
						std::cout << "Current Value is " << retVal << " Position " << i << std::endl;
					} else {
						retVal += 100;
						i++;
						std::cout << "Current Value is " << retVal << " Position " << i << std::endl;
					}
				} else {
					retVal += 100;
					i++;
					std::cout << "Current Value is " << retVal << " Position " << i << std::endl;
				}
			} else if (strNumRoman[i] == 'L') {
				retVal += 50;
				i++;
				std::cout << "Current Value is " << retVal << " Position " << i << std::endl;
			} else if (strNumRoman[i] == 'X') {
				if (i < len) {
					if (strNumRoman[i + 1] == 'C') {
						retVal += 90;
						i += 2;
						std::cout << "Current Value is " << retVal << " Position " << i << std::endl;
					} else if (strNumRoman[i + 1] == 'L') {
						retVal += 40;
						i += 2;
						std::cout << "Current Value is " << retVal << " Position " << i << std::endl;
					} else {
						retVal += 10;
						i++;
						std::cout << "Current Value is " << retVal << " Position " << i << std::endl;
					}
				} else {
					retVal += 10;
					i++;
					std::cout << "Current Value is " << retVal << " Position " << i << std::endl;
				}
			} else if (strNumRoman[i] == 'V') {
				retVal += 5;
				i++;
				std::cout << "Current Value is " << retVal << " Position " << i << std::endl;
			} else if (strNumRoman[i] == 'I') {
				if (i < len) {
					if (strNumRoman[i + 1] == 'X') {
						retVal += 9;
						i += 2;
						std::cout << "Current Value is " << retVal << " Position " << i << std::endl;
					} else if (strNumRoman[i + 1] == 'V') {
						retVal += 4;
						i += 2;
						std::cout << "Current Value is " << retVal << " Position " << i << std::endl;
					} else {
						retVal += 1;
						i++;
						std::cout << "Current Value is " << retVal << " Position " << i << std::endl;
					}
				} else {
					retVal += 1;
					i++;
					std::cout << "Current Value is " << retVal << " Position " << i << std::endl;
				}
			}
		}
	}

	return retVal;
}

std::string convertArabicToRoman(int iNum) {
	std::string retVal = "";
	std::cout << iNum << std::endl;

	while (iNum > 0) {
		if (iNum > 5000) {
			std::cout << "Invalid Input";
			break;
		} else if (iNum >= 1000) {
			retVal += "M";
			iNum -= 1000;
		} else if (iNum >= 900) {
			retVal += "CM";
			iNum -= 900;
		} else if (iNum >= 500) {
			retVal += "D";
			iNum -= 500;
		} else if (iNum >= 400) {
			retVal += "CD";
			iNum -= 400;
		} else if (iNum >= 100) {
			retVal += "C";
			iNum -= 100;
		} else if (iNum >= 90) {
			retVal += "XC";
			iNum -= 90;
		} else if (iNum >= 50) {
			retVal += "L";
			iNum -= 50;
		} else if (iNum >= 40) {
			retVal += "XL";
			iNum -= 40;
		} else if (iNum >= 10) {
			retVal += "X";
			iNum -= 10;
		} else if (iNum >= 9) {
			retVal += "IX";
			iNum -= 9;
		} else if (iNum >= 5) {
			retVal += "V";
			iNum -= 5;
		} else if (iNum >= 4) {
			retVal += "IV";
			iNum -= 4;
		} else if (iNum >= 1) {
			retVal += "I";
			iNum -= 1;
		}
	}

	return retVal;
}

const std::string ROMAN_TO_ARABIC = "-r2a";
const std::string ARABIC_TO_ROMAN = "-a2r";

int main(int argc, char **argv) {
	if (argc != 3) {
		std::cout << "wrong arguments\n";
		return -1;
	}

	//init map of numeral
	for (int i = 0; i < 7; ++i) {
		Numerals[key.at(i)] = value.at(i);
	}

	std::string command = argv[1];
	std::string numberNeedToConvert = argv[2];

	if (command.compare(ROMAN_TO_ARABIC) == 0) {
		std::cout << "convert to arabic number\n";
		std::cout << "\033[1;33m" << convertRomanToArabic(numberNeedToConvert)
				<< "\033[0m\n";
	} else if (command.compare(ARABIC_TO_ROMAN) == 0) {
		std::cout << "convert to roman number\n";
		try {
			int numArabic = std::stoi(numberNeedToConvert);
			std::cout << "\033[1;31m" << convertArabicToRoman(numArabic)
					<< "\033[0m\n" << std::endl;
		} catch (std::invalid_argument &e) {
			std::cout << "Not the arabic number\n";
		}
	} else {
		std::cout << "unknown parameter\n";
	}

//	if (not checkValidationRomanNumber(romanNumeral)) {
//		std::cout << "wrong format" << std::endl;
//		return -1;
//	} else {
//		std::cout << convertRomanToArabic(romanNumeral);
//	}

	return 0;
}

