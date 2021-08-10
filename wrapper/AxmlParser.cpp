#include "AxmlParser.hpp"
#include "AxmlParser.h"
#include <cstdlib>


AxmlParser::AxmlParser(const std::vector<char>&  axml) :
		axml_(axml) {
	c_ctx_ = open(axml_.data(), axml_.size());
}

AxmlParser::AxmlParser(const std::vector<char>&& axml) :
		axml_(std::move(axml)) {
	c_ctx_ = open(axml_.data(), axml_.size());
}

AxmlParser::~AxmlParser() {
	close();
}

void* AxmlParser::open(char *buffer, size_t size) {
	return AxmlOpen(buffer, size);
}

void AxmlParser::close() {
	if (c_ctx_) {
		AxmlClose(c_ctx_);
	}
}

AxmlParser::AxmlEvent AxmlParser::next() {
	return c_ctx_ ? static_cast<AxmlEvent>(AxmlNext(c_ctx_)) : AE_ERROR;
}

std::string AxmlParser::getTagPrefix() {
	return c_ctx_ ? std::string(AxmlGetTagPrefix(c_ctx_)) : "";
}

// TODO: get sure to free ALL the c-style allocated c-strings

std::string AxmlParser::getTagName() {
    return c_ctx_ ? std::string(AxmlGetTagName(c_ctx_)) : "";
}

int AxmlParser::newNamespace() {
    return c_ctx_ ? AxmlNewNamespace(c_ctx_) : -1;
}

std::string AxmlParser::getNsPrefix() {
	return c_ctx_ ? std::string(AxmlGetNsPrefix(c_ctx_)) : "";
}

std::string AxmlParser::getNsUri() {
	return c_ctx_ ? std::string(AxmlGetNsUri(c_ctx_)) : "";
}

uint32_t AxmlParser::getAttrCount() {
	return c_ctx_ ? AxmlGetAttrCount(c_ctx_) : 0;
}

std::string AxmlParser::getAttrPrefix(uint32_t i) {
	return c_ctx_ ? std::string(AxmlGetAttrPrefix(c_ctx_, i)) : "";
}

std::string AxmlParser::getAttrName(uint32_t i) {
	return c_ctx_ ? std::string(AxmlGetAttrName(c_ctx_, i)) : "";
}

std::string AxmlParser::getAttrValue(uint32_t i) {
	if (c_ctx_) {
		char* const c_value = AxmlGetAttrValue(c_ctx_, i);
		if (c_value) {
			const auto retval = std::string(c_value);
			std::free(c_value);
			return retval;
		}
	}
	return "";
}

std::string AxmlParser::getText() {
	return c_ctx_ ? std::string(AxmlGetText(c_ctx_)) : "";
}

std::string AxmlParser::axmlToXml(std::vector<char>&  axml) {
	char* c_xml = nullptr;
	size_t c_xml_len = 0;
	AxmlToXml(&c_xml, &c_xml_len, axml.data(), axml.size());
	const auto retval = std::string(c_xml);
	if (c_xml && c_xml_len > 0) {
		const auto retval = std::string(c_xml);
		std::free(c_xml);
		return retval;
	}
	return "";
}
