#define WINVER 0x502
#define _WIN32_WINNT 0x502

#include <Windows.h>
#include <iostream>
#include <fstream>                                                                           
#include <cwchar>                                                                             
#include <map>                 
#include <vector>
#include <string>

using namespace std;

class Profile {

public:
	//Constructors, destructor
	Profile() {}
	Profile(map<string, vector<string> settings){settings_ = settings;}
	~Profile() {}

	//Getters
	map<string, vector<string>> getSettings() {return settings_;}	
	
	//Setters
	void setSettings(map<string, vector<string>>settings) {settings_ = settings;}

	//Operations
	int changeRegKeyValue(wchar_t* key, wchar_t* keyName, wchar_t* value);
	int changeRegKeyValue(wchar_t* key, wchar_t* keyName, int value);
	int createFile(string path, string content);
private:

	map<string, vector<string>> settings_;

}; 
