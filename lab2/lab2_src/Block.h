#pragma once
#include <vector>
#include <string>

#ifndef BLOCK_H
#define BLOCK_H

namespace WorkBlock
{

	class Block
	{
	private:
		std::string name;
		std::vector<std::string> args;
	public:
		Block(const std::string name_  = "no_name", const std::vector<std::string>& content = {}) :
			name(name_), args(content) {};
		void SetArgs(const std::vector<std::string>& args) { this->args = std::vector<std::string>(args); };
		void setName(const std::string& name_) { this->name = name_; };

		void AddArgument(const std::string& content) { this->args.push_back(content); };

		static size_t ArgSize(const std::string name);

		const std::string getBlockName() const { return name; };
		const std::vector<std::string>& getArgs() const { return args; };
	};
}

#endif // !BLOCK_H
