#include "Time.h"
#include <Windows.h>

//Class Time

void Time::execut(string& argument, string& option, string& filepath) {
	SYSTEMTIME st;
	GetLocalTime(&st);

	string time = "";
	// hour
	if (st.wHour < 10) time = "0" + to_string(st.wHour) + ":";
	else time = to_string(st.wHour) + ":";
	// minute
	if (st.wMinute < 10) time += "0" + to_string(st.wMinute) + ":";
	else time += to_string(st.wMinute) + ":";
	// secund
	if (st.wSecond < 10) time += "0" + to_string(st.wSecond);
	else time += to_string(st.wSecond);

	time.push_back('"');
	time.insert(0, "\"");

	print(filepath, time);
}