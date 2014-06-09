#include <iostream>
#include <vector>

using namespace std;

class Deck {
public:
	Deck();
	void print() const;
private:
	vector<string> _cards;
};