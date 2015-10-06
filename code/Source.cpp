#define WINVER 0x0502
#define _WIN32_WINNT 0x0502

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <cwchar>
#include <map>
#include <vector>

using namespace std;

int changeRegKeyValueStr(wchar_t* Key, wchar_t* KeyName, wchar_t* Value) {

	HKEY hKey = 0;

	if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, Key, 0, KEY_READ | KEY_WRITE, &hKey)) {

		BYTE oldKeyValue[MAX_PATH];
		DWORD bufferSize = MAX_PATH;

		if (ERROR_SUCCESS == RegQueryValueEx(hKey, KeyName, 0, NULL, oldKeyValue, &bufferSize)) {

			if (ERROR_SUCCESS == RegSetValueEx(hKey, KeyName, 0, REG_SZ, (BYTE*)Value, wcslen(Value)*2)) {

				cout << "Key " << KeyName << " written successfully!" << endl;
				cout << "Length : " << wcslen(Value) << endl;
				RegCloseKey(hKey);
			}
			else
				cout << "Error in RegSetValueEx()." << endl;
		}
		else
			cout << "Error in RegQueryValueEx()." << endl;
	}
	else
		cout << "Error in RegOpenKeyEx()." << endl;


	return 0;

}


int changeRegKeyValueInt(wchar_t* Key, wchar_t* KeyName, int Value) {

	HKEY hKey = 0;

	int success = RegOpenKeyEx(HKEY_LOCAL_MACHINE, Key, 0, KEY_READ | KEY_WRITE, &hKey);

	if (ERROR_SUCCESS == success) {

		BYTE oldKeyValue[MAX_PATH];
		DWORD bufferSize = MAX_PATH;

		if (ERROR_SUCCESS == RegQueryValueEx(hKey, KeyName, 0, NULL, oldKeyValue, &bufferSize)) {

			if (ERROR_SUCCESS == RegSetValueEx(hKey, KeyName, 0, REG_DWORD, (BYTE*)&Value, sizeof(Value))) {

				cout << "Key " << KeyName << " written successfully!" << endl;
				RegCloseKey(hKey);
			}
			else
				cout << "Error in RegSetValueEx()." << endl;
		}
		else
			cout << "Error in RegQueryValueEx()." << endl;
	}
	else
		cout << "Error in RegOpenKeyEx()." << endl;


	return 0;

}

int createFile(string path, string content) {

	ofstream ecriture(path, ios::out);
	ecriture << content.c_str();
	ecriture.close();

	return 0;
}

int main(int argc, char *argv[]) {

	// ComputerName changed to WORKSTATION
	

	wchar_t* activeComputerNameKey = L"SYSTEM\\ControlSet001\\Control\\ComputerName\\ActiveComputerName";
	wchar_t* activeComputerNameKeyName = L"ComputerName";
	wchar_t* activeComputerNameValue = L"WORKSTATION";

	changeRegKeyValueStr(activeComputerNameKey, activeComputerNameKeyName, activeComputerNameValue);

	//Change the hostname

	wchar_t* Key = L"SYSTEM\\ControlSet001\\Services\\Tcpip\\Parameters";
	wchar_t* KeyName = L"Hostname";
	wchar_t* Value = L"ABHI-PC";

	changeRegKeyValueStr(Key, KeyName, Value);

	 Key = L"HKEY_USERS\\S-1-5-21-854245398-287218729-839522115-500\\Volatile Environment";
	 KeyName = L"LOGONSERVER";
	 Value = L"DEFENSE-MINISTRY";

	// changeRegKeyValueStr(Key, KeyName, Value); // Seems to impact VMware Tools

	 //Change the registered owner

	 Key = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData\\S-1-5-18\\Products\\0B79C053C7D38EE4AB9A00CB3B5D2472\\InstallProperties";
	 KeyName = L"RegOwner";
	 Value = L"ABHI";

	changeRegKeyValueStr(Key, KeyName, Value);
	
	//Change the registered owner

	 Key = L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion";
	 KeyName = L"RegisteredOwner";
	 Value = L"ABHI";

	changeRegKeyValueStr(Key, KeyName, Value);

	//Change the install date

	 Key = L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion";
	 KeyName = L"InstallDate";
	 int ValueInt = 1037061927;

	changeRegKeyValueInt(Key, KeyName, ValueInt);

	// Change the network adapter name.

	 Key = L"SYSTEM\\ControlSet001\\Control\\Class\\{4D36E972-E325-11CE-BFC1-08002bE10318}\\0001";
	 KeyName = L"DriverDesc";
	 Value = L"AMD PCNet Adapter";

	changeRegKeyValueStr(Key, KeyName, Value);

	// Create directories 

	CreateDirectory(L"C:\\Documents and Settings\\All Users\\My Documents\\", NULL);
	CreateDirectory(L"C:\\Documents and Settings\\All Users\\Recent\\", NULL);
	CreateDirectory(L"C:\\Documents and Settings\\All Users\\My Documents\\Confidential\\", NULL);
	CreateDirectory(L"C:\\Documents and Settings\\All Users\\My Documents\\Confidential\\VPN Access\\", NULL);
	CreateDirectory(L"C:\\Documents and Settings\\All Users\\My Documents\\Confidential\\Email Access\\", NULL);
	CreateDirectory(L"C:\\Documents and Settings\\All Users\\My Documents\\Confidential\\Projects\\", NULL);
	CreateDirectory(L"C:\\Documents and Settings\\All Users\\My Documents\\Confidential\\Projects\\Current\\", NULL);
	CreateDirectory(L"C:\\Documents and Settings\\All Users\\My Documents\\Confidential\\Projects\\Past\\", NULL);
	CreateDirectory(L"C:\\Documents and Settings\\All Users\\My Documents\\Confidential\\Contracts\\2014\\", NULL);
	CreateDirectory(L"C:\\Documents and Settings\\All Users\\My Documents\\Confidential\\Contracts\\2015\\", NULL);
	CreateDirectory(L"C:\\Documents and Settings\\All Users\\My Documents\\Personnal Accounts\\", NULL);
	CreateDirectory(L"C:\\Documents and Settings\\All Users\\My Documents\\Personnal Accounts\\Banking\\", NULL);
	CreateDirectory(L"C:\\Documents and Settings\\All Users\\My Documents\\Personnal Accounts\\Facebook\\", NULL);
	CreateDirectory(L"C:\\Documents and Settings\\All Users\\My Documents\\Personnal Accounts\\Email\\", NULL);

	// Create files to identify purpose
	
	createFile("C:\\Documents and Settings\\All Users\\My Documents\\Confidential\\VPN Access\\Passwords.txt", "Please check the Web Portal for info.");
	createFile("C:\\Documents and Settings\\All Users\\My Documents\\Confidential\\VPN Access\\Instructions.txt", "Please check the Web Portal for info.");
	createFile("C:\\Documents and Settings\\All Users\\My Documents\\Confidential\\Email Access\\Passwords.txt", "Please check the Web Portal for info.");
	createFile("C:\\Documents and Settings\\All Users\\My Documents\\Confidential\\Email Access\\Instructions.txt", "Please check the Web Portal for info.");
	createFile("C:\\Documents and Settings\\All Users\\My Documents\\Confidential\\Projects\\Past\\list.txt", "Please check the Web Portal for info.");
	createFile("C:\\Documents and Settings\\All Users\\My Documents\\Confidential\\Projects\\Current\\list.txt", "Please check the Web Portal for info.");
	createFile("C:\\Documents and Settings\\All Users\\My Documents\\Confidential\\Contracts\\2014\\list.txt", "Please check the Web Portal for info.");
	createFile("C:\\Documents and Settings\\All Users\\My Documents\\Confidential\\Contracts\\2015\\list.txt", "Please check the Web Portal for info.");
	createFile("C:\\Documents and Settings\\All Users\\My Documents\\Personnal Accounts\\Banking\\pass.txt", "PleaseGiveMeMoney1234");
	createFile("C:\\Documents and Settings\\All Users\\My Documents\\Personnal Accounts\\Facebook\\pass.txt", "PleaseLetMeIn1234");
	createFile("C:\\Documents and Settings\\All Users\\My Documents\\Personnal Accounts\\Email\\pass.txt", "PleaseGiveMeMail1234");

	// Create shortcuts

	createFile("C:\\Documents and Settings\\All Users\\Start Menu\\Programs\\Word.lnk", "Invalid LNK.");
	createFile("C:\\Documents and Settings\\All Users\\Start Menu\\Programs\\MinistryWebPortal.lnk", "Invalid LNK.");
	createFile("C:\\Documents and Settings\\All Users\\Start Menu\\Programs\\Chrome.lnk", "Invalid LNK");
	createFile("C:\\Documents and Settings\\All Users\\Recent\\MoD_India_contract.docx", "NEED TO CHANGE");

	system("pause");

	return 0;
}

// HKEY_LOCAL_MACHINE\\SYSTEM\\ControlSet001\\Services\\Tcpip\\Parameters Hostname ABHI-6y8a06lapx
// HKEY_USERS\\S-1-5-21-854245398-287218729-839522115-500\\Volatile Environment LOGONSERVER 
//HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Installer\\UserData\\S-1-5-18\\Products\\0B79C053C7D38EE4AB9A00CB3B5D2472\\InstallProperties RegOwner
// HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion RegisteredOwner and InstallDate
// HKEY_LOCAL_MACHINE\\SYSTEM\\ControlSet001\\Control\\Class\\{4D36E972-E325-11CE-BFC1-08002bE10318}\\0001 DriverDesc AMD PCNet Adapter
