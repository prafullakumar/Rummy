#include "WinLogic.h"
#include <iostream>
using namespace std;

//brutally inefficient win check
int winCheck(Hand h)
{
	//DEBUG
	cout << "\nBeginning WinCheck\n";

	Card cards[7];
	int remain_index[3];

	for (int i = 0; i < 7; i++) {
		cards[i] = h.get(i);
	}


	for (int j = 0; j < 7; j++) {

		//DEBUG
		cout << "\nChecking Card " << j << ", ";
		cards[j].print();
		cout << endl;

		int of_a_kind = 0;

		for (int k = 0; k < 7; k++) {
			if (cards[j].getValue() == cards[k].getValue()) {
				of_a_kind++;
			}
		}

		//check remaining for 3 straight or 3 of a kind
		if (of_a_kind == 4) {

			int index = 0;
			for (int k = 0; k < 7; k++) {
				if (cards[j].getValue() != cards[k].getValue()) {
					remain_index[index++] = k;
				}
			}

			//DEBUG
			cout << "\nHand has 4 " << cards[j].getValue() << "'s\n";
			cout << "\nRemaining cards are: " << remain_index[0] << " " << remain_index[1] << " " << remain_index[2] << endl;

			int v0 = cards[remain_index[0]].getValue();
			int s0 = cards[remain_index[0]].getSuit();
			int v1 = cards[remain_index[1]].getValue();
			int s1 = cards[remain_index[1]].getSuit();
			int v2 = cards[remain_index[2]].getValue();
			int s2 = cards[remain_index[2]].getSuit();

			if (v0 == v1 && v0 == v2) {

				//DEBUG
				cout << "\nHand also has 3 " << v0 << "'s\n\nRUMMY\n\n";

				return 1;
			}

			if (s0 == s1 && s0 == s2) {

				//DEBUG
				cout << "\nRemaining 3 have the same suit\n\n";

				int sorted[3];

				if (v0 > v1) {
					if (v0 > v2) {
						if (v1 > v2) {
							sorted[0] = v2;
							sorted[1] = v1;
							sorted[2] = v0;
						}
						else {
							sorted[0] = v1;
							sorted[1] = v2;
							sorted[2] = v0;
						}

					}
					else {
						sorted[0] = v1;
						sorted[1] = v0;
						sorted[2] = v2;
					}

				}
				else {
					if (v1 > v2) {
						if (v0 > v2) {
							sorted[0] = v2;
							sorted[1] = v0;
							sorted[2] = v1;
						}
						else {
							sorted[0] = v0;
							sorted[1] = v2;
							sorted[2] = v1;
						}
					}
					else {
						sorted[0] = v0;
						sorted[1] = v1;
						sorted[2] = v2;
					}
				}


				if ((sorted[0] + 1 == sorted[1] && sorted[0] + 2 == sorted[2]) || (sorted[0] + 1 == sorted[1] && sorted[0] + 12 == sorted[2])) {

					//DEBUG
					cout << "\nHand also has a 3 card straight\n\nRUMMY\n\n";

					return 1;
				}
			}
		}//end 4OfAkind
	}

	//DEBUG
	cout << "\nHand couldn't make a Rummy with 4 of a kind, checking 4 in a row...\n\n";
	//check 4 in a row
	for (int i = 0; i < 7; i++) {

		//DEBUG
		cout << "\nChecking Card " << i << ", ";
		cards[i].print();
		cout << endl;

		int curr_val = cards[i].getValue();
		int curr_suit = cards[i].getSuit();
		int in_a_row = 1;

		for (int j = 0; j < 7; j++) {

			if ((cards[j].getSuit() == curr_suit) && ((cards[j].getValue() == curr_val + 1) || (cards[j].getValue() == curr_val - 12))) {

				curr_val = cards[j].getValue();
				in_a_row++;
				j = -1;
			}
		}

		cout << "\n In a Row: " << in_a_row << endl;
		int index = 0;
		if (in_a_row >= 4) {

			//DEBUG
			cout << "\nGot 4 in a row, finding remaining 3 cards...\n";

			if (cards[i].getValue() == 14) {
				curr_val = 1;
			}
			else {
				curr_val = cards[i].getValue();
			}

			for (int k = 0; k < 7; k++) {
				if (k == i) {
					continue;
				}

				else if (cards[k].getSuit() != curr_suit) {
					remain_index[index++] = k;
				}

				else if ((cards[k].getValue() < curr_val) || (cards[k].getValue() > curr_val + 3)) {
					remain_index[index++] = k;
				}
			}

			cout << "\n Remaining Cards: " << remain_index[0] << " " << remain_index[1] << " " << remain_index[2] << "\n";

			int v0 = cards[remain_index[0]].getValue();
			int s0 = cards[remain_index[0]].getSuit();
			int v1 = cards[remain_index[1]].getValue();
			int s1 = cards[remain_index[1]].getSuit();
			int v2 = cards[remain_index[2]].getValue();
			int s2 = cards[remain_index[2]].getSuit();

			if (v0 == v1 && v0 == v2) {

				//DEBUG
				cout << "\nHand also has 3 " << v0 << "'s\n\nRUMMY\n\n";

				return 1;
			}

			if (s0 == s1 && s0 == s2) {

				//DEBUG
				cout << "\nRemaining 3 have the same suit\n\n";

				int sorted[3];

				if (v0 > v1) {
					if (v0 > v2) {
						if (v1 > v2) {
							sorted[0] = v2;
							sorted[1] = v1;
							sorted[2] = v0;
						}
						else {
							sorted[0] = v1;
							sorted[1] = v2;
							sorted[2] = v0;
						}

					}
					else {
						sorted[0] = v1;
						sorted[1] = v0;
						sorted[2] = v2;
					}

				}
				else {
					if (v1 > v2) {
						if (v0 > v2) {
							sorted[0] = v2;
							sorted[1] = v0;
							sorted[2] = v1;
						}
						else {
							sorted[0] = v0;
							sorted[1] = v2;
							sorted[2] = v1;
						}
					}
					else {
						sorted[0] = v0;
						sorted[1] = v1;
						sorted[2] = v2;
					}
				}


				if ((sorted[0] + 1 == sorted[1] && sorted[0] + 2 == sorted[2]) || (sorted[0] + 1 == sorted[1] && sorted[0] + 12 == sorted[2])) {

					//DEBUG
					cout << "\nHand also has a 3 card straight\n\nRUMMY\n\n";

					return 1;
				}
			}

		}
	}//end 4 in a row

	return 0;
}

//optimized win check
int winCheck2(Hand h)
{
	//init variables
	int i, j;
	int index_mult;
	int remain_int;
	int curr_suit, curr_val;
	Card remain_array[3];

	//convert hand to 7 card array
	Card c[7];
	for (int i = 0; i < 7; i++) {
		c[i] = h.get(i);
	}


	//check 4 of a kind
	for (i = 0; i < 7; i++) {

		remain_int = 0;
		index_mult = 1;

		for (j = 0; j < 7; j++) {
			if (c[i].getValue() != c[j].getValue()) {
				remain_int += j*index_mult;
				index_mult *= 10;
			}
		}

		//check remaining cards for 3 of a kind/in a row
		if (remain_int < 1000) {
			remain_array[0] = c[remain_int % 10];
			remain_array[1] = c[(remain_int / 10) % 10];
			remain_array[2] = c[remain_int / 100];

			if (check3Match(remain_array)) {
				return 1;
			}

			if (check3Straight(remain_array)) {
				return 2;
			}
		}
	}//end 4 of a kind check

	 //check 4 in a row
	for (i = 0; i < 7; i++) {

		remain_int = 0;
		index_mult = 1;
		curr_suit = c[i].getSuit();
		curr_val = c[i].getValue();

		if (curr_val == 14) {
			curr_val = 1;
		}

		for (j = 0; j < 7; j++) {
			if (j == i) {
				continue;
			}
			else if (c[j].getSuit() != curr_suit) {
				remain_int += j*index_mult;
				index_mult *= 10;
			}
			else if ( (c[j].getValue() > curr_val + 3) || (c[j].getValue() < curr_val) ){
				remain_int += j*index_mult;
				index_mult *= 10;
			}
		}

		//check remaining cards for 3 of a kind/in a row
		if (remain_int < 1000) {
			remain_array[0] = c[remain_int % 10];
			remain_array[1] = c[(remain_int / 10) % 10];
			remain_array[2] = c[remain_int / 100];

			if (check3Match(remain_array)) {
				return 3;
			}

			if (check3Straight(remain_array)) {
				return 4;
			}
		}
	}//end 4 in a row check

	return 0;
}

void sortRemains(Card r[3]) 
{

	int num_swaps;
	Card temp;
	do {
		num_swaps = 0;
		for (int i = 0; i < 2; i++) {
			if (r[i].getValue() > r[i + 1].getValue()) {
				temp = r[i + 1];
				r[i + 1] = r[i];
				r[i] = temp;
				num_swaps++;
			}
		}
	} while (num_swaps > 0);
}

bool check3Match(Card c[3])
{
	if ((c[0].getValue() == c[1].getValue()) &&
		(c[1].getValue() == c[2].getValue())) {

		return true;
	} 
	
	return false;
}

bool check3Straight(Card c[3])
{
	sortRemains(c);

	if ( (c[0].getSuit() == c[1].getSuit()) &&
		 (c[1].getSuit() == c[2].getSuit()) ) {

		if ((c[0].getValue() + 1 == c[1].getValue()) &&
			((c[0].getValue() + 2 == c[2].getValue()) ||
				(c[0].getValue() + 12 == c[2].getValue()))) {
			return true;
		}
	}

	return false;
}