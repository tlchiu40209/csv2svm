/**C++ Library**/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

/** C Library **/
#include <stdio.h>
#include <stdlib.h>

using namespace std;

vector<string> split(const string &source, const char &delim);
bool containsAlphabet(string check);
template <class T> void convertFromString(T &value, const string &s);

int main(int argc, char ** argv)
{
	string *csvFileName;
	string *desiredLabel;
	string *svmFileName;

	string csvFileSingleLine;
	vector<string> csvFileSLElements;
	int csvFileSLElementCounts;

	ifstream csvRead;
	ofstream svmWrite;

	if (argc < 4)
	{
		cout << "Usage : csv2svm <CSV File> <Desired Label> <Output SVM File>" << endl;
		cout << "Example : csv2svm foo.csv +20 foo.svm" << endl;
		cout << endl;
		cout << "\tfoo.csv\t\tfoo.svm" << endl;
		cout << "\t20,30\t\t+20 1:20 2:30" << endl;
		cout << endl;
		exit(1);
	}

	if (argc == 4)
	{
		csvFileName = new string(argv[1]);
		desiredLabel = new string(argv[2]);
		svmFileName = new string(argv[3]);
	}


	csvRead.open(csvFileName->c_str());
	svmWrite.open(svmFileName->c_str());

    int lineCounter = 0;
	while(!csvRead.eof())
    {
        lineCounter++;
        float temp = 0;
        getline(csvRead, csvFileSingleLine);
        csvFileSLElements = split(csvFileSingleLine, ',');
        if (lineCounter == 1)
        {
            csvFileSLElementCounts = csvFileSLElements.size();
        }
        else
        {
            if (csvFileSLElementCounts != csvFileSLElements.size())
            {
                cout << "Line " << lineCounter << " has different attribute quantity than last line." << endl;
                csvFileSLElementCounts = csvFileSLElements.size();
            }
            else
            {
                csvFileSLElementCounts = csvFileSLElements.size();
            }
        }
        svmWrite << *desiredLabel;
        for (int i = 0; i < csvFileSLElementCounts; i++)
        {
            if (containsAlphabet(csvFileSLElements[i]))
            {
                cout << "Line " << lineCounter << " attribute " << i+1 << " contains non-numerical characters." << endl;
            }
            convertFromString(temp, csvFileSLElements[i]);
            svmWrite << " " << i << ":" << temp;
        }
        svmWrite << endl;
    }
    svmWrite.flush();
    svmWrite.close();

    csvRead.close();
}

vector<string> split(const string &source, const char &delim)
{
	stringstream ss(source);
	string token;
	vector<string> ans;
	while(getline(ss, token, delim))
	{
		ans.push_back(token);
	}
	return ans;
}

template <class T> void convertFromString(T &value, const string &s)
{
    stringstream ss(s);
    ss >> value;
}

bool containsAlphabet(string check)
{
    bool verify = true;
    for (int i = 0; i < check.length(); i++)
	{
		if (check[i] >= 'a' && check[i] <= 'z' || check[i] >= 'A' && check[i] <= 'Z')
			verify = true;
		else
		{
			verify = false;
			break;
		}
	}
	return verify;
}
