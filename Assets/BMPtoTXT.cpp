#include <iostream>
#include <fstream>


using namespace std;


int main() {
	string fileName;
	cin >> fileName;
	string command ="xxd -c 3 -b "+(fileName+".bmp ")+(fileName+".txt");
	system(command.c_str());
	fstream file;
	file.open(fileName+".txt");
	int sprite[16][16];
	string pixel;
	for(int i=0; i<18; i++){
		getline(file, pixel);
	}
	for(int i=0; i<16;i++) {
		for (int j=0; j<16;j++) {
			getline(file,pixel);
			sprite[15-i][j] = ( (pixel[11]) == '0');
		}
	}
	file.seekp(ios::beg);
	for(int i=0; i<16;i++) {
		file << " .db    %";
		for (int j=0; j<8;j++) {
			file << sprite[i][j];
		}
		file << endl;
	}
	file << endl;
	for(int i=0; i<16;i++) {
		file << " .db    %";
		for (int j=0; j<8;j++) {
			file << sprite[i][8+j];
		}
		file << endl;
	}
	file << endl;

	file.close();
	return 0;
}
