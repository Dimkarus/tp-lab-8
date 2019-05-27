#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <deque>
#include <string>
#include <ctime>

using namespace std;

void createNewText() {
	typedef deque<string> prefix;
	map<prefix, vector<string>> table;
	const int NPREF = 2;
	const int MAXGEN = 1000;
	string word;
	prefix pref;
	vector<string> postfInput;
	ifstream stream("input.txt");
	map<prefix, vector<string>>::iterator mapIter;
	vector<string>::iterator vecIter;
	vector<string> firstTwo;

	//stream >> word;

	for (int i = 0; i < NPREF; i++)
	{
		stream >> word;
		firstTwo.push_back(word);
		pref.push_back(word);
	}

	while (stream >> word) {
		
		mapIter = table.find(pref);

		if (mapIter != table.end()) {
			vecIter = find(mapIter->second.begin(), mapIter->second.end(), word);
			if (vecIter == mapIter->second.end())
			{
				mapIter->second.push_back(word);
			}
		}
		else {
			postfInput.push_back(word);
			table.emplace(pref, postfInput);
			postfInput.clear();
		}

		pref.pop_front();
		pref.push_back(word);

	
	}
	stream.close();
	pref.clear();

	ofstream out("output.txt");
	

	for (int i = 0; i < NPREF; i++) {
		out << firstTwo[i] << ' ';
		pref.push_back(firstTwo[i]);
	}
	int n;
	int NCycle;

	if (table.size() > MAXGEN)
		NCycle = MAXGEN;
	else
		NCycle = table.size();

	srand(time(NULL));

	for (int i = 0; i < MAXGEN; i++)
	{
		mapIter = table.find(pref); // ������� �������� �� ������ �������
		if (mapIter!=table.end()) {
		//��������� ������ ��������� � ����� ��������� ����� �� 0 ����������
			n = rand() % mapIter->second.size(); 
		//�.�. second � ������ ������ - vector, ����� ���������� � ��� �������� ����� []
			out << mapIter->second[n] << ' '; //������� � ����� (�� ���� ������� � ����) second[n]
			pref.pop_front();
			pref.push_back(mapIter->second[n]);
		}

	}
	out.close();

}


int main() {

	createNewText();
	   	  
	return 0;

}

