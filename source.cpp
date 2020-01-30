#include<string>
#include<vector>
#include<map>
#include<iostream>
#include<armadillo>
#include<iomanip>
using namespace std;

/* started this project in vanilla C++, but decided to use a linear algebra library
encoding would've been fairly simple without this library, however decoding would have been much more difficult without it
Citation:
Conrad Sanderson and Ryan Curtin.
Armadillo: a template-based C++ library for linear algebra.
Journal of Open Source Software, Vol. 1, pp. 26, 2016.

Conrad Sanderson and Ryan Curtin.
Practical sparse matrices in C++ with hybrid storage and template-based expression optimisation.
Mathematical and Computational Applications, Vol. 24, No. 3, 2019.

//returns true if the matrix is invertible, checks by calculating the determinant, only accepts 3x3 matrices
bool isInvertible(vector<vector<double>> matrix);

*/
int main() {
	string keyString;
	bool keyMake = true;
	//using a character space that'll have a prime mod number of 41
	map<char, int> alpha;
	alpha['a'] = 0;
	alpha['b'] = 1;
	alpha['c'] = 2;
	alpha['d'] = 3;
	alpha['e'] = 4;
	alpha['f'] = 5;
	alpha['g'] = 6;
	alpha['h'] = 7;
	alpha['i'] = 8;
	alpha['j'] = 9;
	alpha['k'] = 10;
	alpha['l'] = 11;
	alpha['m'] = 12;
	alpha['n'] = 13;
	alpha['o'] = 14;
	alpha['p'] = 15;
	alpha['q'] = 16;
	alpha['r'] = 17;
	alpha['s'] = 18;
	alpha['t'] = 19;
	alpha['u'] = 20;
	alpha['v'] = 21;
	alpha['w'] = 22;
	alpha['x'] = 23;
	alpha['y'] = 24;
	alpha['z'] = 25;
	alpha['0'] = 26;
	alpha['1'] = 27;
	alpha['2'] = 28;
	alpha['3'] = 29;
	alpha['4'] = 30;
	alpha['5'] = 31;
	alpha['6'] = 32;
	alpha['7'] = 33;
	alpha['8'] = 34;
	alpha['9'] = 35;
	alpha['.'] = 36;
	alpha[','] = 37;
	alpha['!'] = 38;
	alpha['?'] = 39;
	alpha[' '] = 40;

	int choice;
	cout << "Select a menu option\n[1] Encode a message\n[2] Decode a message with a given key" << endl;
	cin >> choice;
	switch (choice) {
	case(1): {
		arma::mat key(3, 3);
		while (keyMake) {
			cout << "Please enter a 9 character string to be used as a key." << endl;
			cin >> keyString;
			bool validChars = true;
			if (keyString.length() == 9) {
				
				for (int i = 0; i < keyString.length(); ++i) {
					//convert string to lower case
					keyString.at(i) = tolower(keyString.at(i));
				if(!(alpha[keyString.at(i)]+1)){
					validChars = false;
					cout << "One or more of the characters in your key is not accepted by this program\nThis program accepts alphanumeric characters as well as . , ! ? and  spaces" << endl;
					i = keyString.length();
				}
				else {
					key(i) = alpha[keyString.at(i)];
				}
				

			}
			}
			else {
				cout << "The string you entered was not 9 characters, please try again." << endl;
			}
			if (validChars = true && arma::det(key)!=0 && keyString.length()==9) {
				keyMake = false;
			}
			if (arma::det(key) == 0) {
				cout << "This string mapped to a non-invertible matrix, please try again." << endl;

			}
		}



		string msg;
		bool msgLegal = true;
		do {
			msgLegal = true;
			msg = "";
			cout << "Enter a message to be encoded: ";
			while (msg == "") {
				getline(cin, msg, '\n');

			}
			//checking for illegal characters
			for (int i = 0; i < msg.length(); ++i) {
				if (!(alpha[tolower(msg.at(i))]) && tolower(msg.at(i))!='a') {
					msgLegal = false;
					
				}
			}
			if (!msgLegal) {
				cout << "One or more of the characters in your key is not accepted by this program\nThis program accepts alphanumeric characters as well as . , ! ? and  spaces" << endl;
			}
		} while (!msgLegal);
		
		//padding message if it is not divisble by 3
		while (msg.length() % 3 != 0) {
			msg += "0";
			
		}
		string codedMsg = "";
		
		for (int i = 0; i < msg.length()-1; i += 3) {
			//putting 3 character chunks into a vector 
			double one = alpha[tolower(msg.at(i))];
			double two = alpha[tolower(msg.at(i + 1))];
			double three = alpha[tolower(msg.at(i + 2))];
			arma::vec *tri = new arma::vec{ one,two,three };
			//encoding via matrix multiplication
			*tri = key * *tri;
			//elements of arma::vectors curiously cannot be operated on by modulo, so this conversion was necessary to do first
			typedef std::vector<long> stdvec;
			vector<long> x = arma::conv_to<stdvec>::from(*tri);
			for (int j = 0; j < 3; ++j) {
				//keeping vector elements within the character space
				x[j] %= 41;
				for (map<char, int>::iterator it = alpha.begin(); it != alpha.end(); ++it) {
					if (it->second == x[j]) {
						codedMsg += it->first;
						//exit loop
						it = alpha.end();
					}
						//cout << "Stuck 144" << endl;
					
				}
				//cout << "Stuck 147" << endl;
			}

		}
		cout << "Encoded message: " << codedMsg << endl;
	}
	break;
	case(2): {
		arma::mat key(3, 3);
		int choice;
		cout << "Will you be providing\n[1] The key string\n[2] The actual matrix" << endl;
		cin >> choice;


		if (choice == 1) {
			while (keyMake) {
				cout << "Please enter the 9 character key string" << endl;
				cin >> keyString;
				if (keyString.length() == 9) {
					bool validChars = true;
					for (int i = 0; i < keyString.length(); ++i) {
						//convert string to lower case
						keyString.at(i) = tolower(keyString.at(i));
						if (!(alpha[keyString.at(i)] + 1)) {
							validChars = false;
							cout << "One or more of the characters in your key is not accepted by this program\nThis program accepts alphanumeric characters as well as . , ! ? and  spaces" << endl;
							i = keyString.length();
						}
						else {
							key(i) = alpha[keyString.at(i)];
						}
						//exit outer loop if a key has succesfully been made
						if (i == keyString.length() - 1 && validChars && arma::det(key) != 0) {
							keyMake = false;
						}
					}
				}

			}
		}else if (choice == 2) {
			cout << "Enter the 3x3 matrix key that was used to encode the message(seperate your numbers by spaces)\nRow 1: ";
			cin >> key(0);
			cin >> key(1);
			cin >> key(2);
			cout << "\nRow 2: ";
			cin >> key(3);
			cin >> key(4);
			cin >> key(5);
			cout << "\nRow 3: ";
			cin >> key(6);
			cin >> key(7);
			cin >> key(8);
			}

			
			//inverse matrix
			arma::mat invKey = (key.i());
			int det = arma::det(key);
			//multiplying every element by the determinant of the original matrix to make it the cofactor matrix
			for (int i = 0; i < invKey.size(); ++i) {
				invKey.at(i) = (int)(invKey.at(i)*det);
			}
			int modInverse;
			
			cout << det << endl;
			//looping to find mod inverse (slow, brute force method, but the character space is small enough to make it viable)
			for (int i = 0; i <= 41; ++i) {
				int result = det * i;
				
				if (result % 41 == 1) {
					modInverse = i;
					i = 42;
				}
			}
			//multiplying the cofactor matrix by the modular inverse determinant, then taking mod 41 to find the modular inverse matrix
			for (int i = 0; i < invKey.size(); ++i) {
				invKey.at(i) = invKey.at(i)*modInverse;
				if (invKey.at(i) > 0) { 
					invKey.at(i) = (int)invKey.at(i) % 41;
				} //The % operator doesn't behave as modulus with negative numbers
				else {
					int num = invKey.at(i);
					while (num < 0) {
						num += 41;
					}
					invKey.at(i) = num;

				}
			}
			// cout <<"Inverse: " << invKey << endl;
			string msg= "";
			cout << "Enter your encoded message: ";
			while (msg == "") {
				getline(cin, msg, '\n');
			}
			
			string decodedMsg = "";
			for (int i = 0; i < msg.length(); i += 3) {
				//putting 3 character chunks into a vector 
				double one = alpha[msg.at(i)];
				double two = alpha[msg.at(i + 1)];
				double three = alpha[msg.at(i + 2)];
				arma::vec *tri = new arma::vec{ one,two,three };
				//encoding via matrix multiplication
				*tri = invKey * *tri;
				//elements of arma::vectors curiously cannot be operated on by modulo, so this conversion was necessary to do first
				typedef std::vector<long> stdvec;
				vector<long> x = arma::conv_to<stdvec>::from(*tri);
				for (int j = 0; j < 3; ++j) {
					//keeping vector elements within the character space
					x[j] = x[j] % 41;
					for (map<char, int>::iterator it = alpha.begin(); it != alpha.end(); ++it) {
						if (it->second == x[j]) {
							decodedMsg += it->first;
							//exit loop
							it = alpha.end();
						}
					}

				}

			}
			cout << "Your message decoded to: " << decodedMsg << endl;
	}
		break;
	default:
		cout << "Invalid menu option" << endl;
				
	}
	
	system("PAUSE");
	return 0;
}
/*
bool isInvertible(vector<vector<double>> matrix) {
	bool is3Col = true;
	bool isInvertible = false;
	for (int i = 0; i < matrix.size(); ++i) {
		if (matrix[i].size() != 3) {
			is3Col = false;
			i = matrix.size();
		}
	}

	if (matrix.size() != 3 || !is3Col) {
		throw "this function can only check 3x3 matrices!!\n";
		return false;
	}

	double det = matrix[0][0] * ((matrix[1][1] * matrix[2][2]) - (matrix[1][2] * matrix[2][1]));

	det -= matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]);
	det += matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
	cout << det << endl;
	if (det != 0) {
		isInvertible = true;
	}
	return isInvertible;
};
*/