#include <iostream>
#include "Stack.h"

bool check_breckets(std::string sentence) {
	int len = sentence.length();
	Stack<char> p(len);
	if (len == 0) {
		return true;
	}
	else {
		for (int i = 0; i < len; i++) {
			if (sentence[i] == '{' || sentence[i] == '[' || sentence[i] == '(') {
				p.push(sentence[i]);
			}
			else if (sentence[i] == '}' || sentence[i] == ']' || sentence[i] == ')') {
				if (p.is_empty()) {
					return false;
				}
				char tmp = p.head();
				if ((sentence[i] == '}' && tmp == '{') || (sentence[i] == ']' && tmp == '[') || (sentence[i] == ')' && tmp == '(')) {
					p.pop();
				}
				else {
					return false;
				}
			}

		}
		if (p.is_empty()) {
			return true;
		}
		else {
			return false;
		}
	}
}

