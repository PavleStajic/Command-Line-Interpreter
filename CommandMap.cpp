#include "CommandMap.h"

CommandMap::CommandMap() {
	m_map["echo"] = { &m_echo };
	m_map["time"] = { &m_time };
	m_map["date"] = { &m_date };
	m_map["wc"] = { &m_wc };
	m_map["touch"] = { &m_touch };
	m_map["prompt"] = { &m_prompt };
	m_map["truncate"] = { &m_truncate };
	m_map["rm"] = { &m_rm };
	m_map["head"] = { &m_head };
	m_map["tr"] = { &m_tr };
	m_map["batch"] = { &m_batch };
	m_map["exit"] = { &m_exit };
}

Command* CommandMap::getCom(const string& command) {
	return m_map[command];
}
