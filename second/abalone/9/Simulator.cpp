#include <iostream>
#include <queue>
#include <cstdlib>

using namespace std;

void play(size_t n) {
	queue<int> cards;
	for (int i=1; i<=n; i++)
		cards.push(i);

	while (cards.size() > 1) {
		cout << cards.front() << " ";
		cards.pop();
		int topCard = cards.front();
		cards.pop();
		cards.push(topCard);
	}
	cout << cards.front() << endl;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " cards' number." << endl;
		exit(1);
	}
	play(atoi(argv[1]));

	return 0;
}
