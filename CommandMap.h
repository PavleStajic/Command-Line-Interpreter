#ifndef COMMANDMAP_H
#define COMMANDMAP_H

#include "Echo.h"
#include "Time.h"
#include "Date.h"
#include "Wc.h"
#include "Touch.h"
#include "Prompt.h"
#include "Truncate.h"
#include "Rm.h"
#include "Head.h"
#include "Tr.h"
#include "Batch.h"
#include "Exit.h"

#include<unordered_map>

//CommandMap class manages a mapping between command strings and their corresponding Command objects.
 //It provides functionality to retrieve a Command object based on a given command string.*
class CommandMap {
public:
	//Constructor. 
	//Initializes the command map and allocates memory for the command objects.
	CommandMap();

	// Retrieves the corresponding Command object for the given command string.
	Command* getCom(const string& command);

private:
	// An unordered map that stores the relationship between 
	// command strings and their corresponding Command objects.
	unordered_map<string, Command*> m_map;

	// Instances of specific command objects.

	Echo m_echo;
	Time m_time;
	Date m_date;
	Wc m_wc;
	Touch m_touch;
	Prompt m_prompt;
	Truncate m_truncate;
	Rm m_rm;
	Head m_head;
	Tr m_tr;
	Batch m_batch;
	Exit m_exit;
};


#endif 

