#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include "AxmlParser.h"

class AxmlParser {
public:
	enum AxmlEvent {
		AE_STARTDOC = 0,
		AE_ENDDOC,
		AE_STARTTAG,
		AE_ENDTAG,
		AE_TEXT,
		AE_ERROR,
	};

	AxmlParser(const std::vector<char>&  axml);
	AxmlParser(const std::vector<char>&& axml);
	~AxmlParser();

	AxmlEvent next();

	std::string getTagPrefix();
	std::string getTagName();

	int newNamespace();
	std::string getNsPrefix();
	std::string getNsUri();

	uint32_t getAttrCount();
	std::string getAttrPrefix(uint32_t i);
	std::string getAttrName(uint32_t i);
	std::string getAttrValue(uint32_t i);

	std::string getText();
	
	static std::string axmlToXml(std::vector<char>&  axml);

private:
	void* open(char *buffer, size_t size);
	void close();

	void* c_ctx_;
	std::vector<char> axml_;
	AxmlEvent_t event = static_cast<AxmlEvent_t>(-1);
};
