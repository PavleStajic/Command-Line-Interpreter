#include "Date.h"
#include <Windows.h>

void Date::execut(string& argument, string& option, string& filepath) {
	SYSTEMTIME st;
	GetSystemTime(&st);

	string date = "";
	if (st.wDay < 10) date = "0" + to_string(st.wDay) + ".";
	else date = to_string(st.wDay) + ".";
	if (st.wMonth < 10) date += "0" + to_string(st.wMonth) + "." + to_string(st.wYear);
	else date += to_string(st.wMonth) + "." + to_string(st.wYear);
	date.push_back('.');

	date.push_back('"');
	date.insert(0, "\"");

	print(filepath, date);
}