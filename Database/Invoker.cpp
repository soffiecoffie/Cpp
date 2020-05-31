#include "Invoker.h"
#include "CmdValidator.h"
#include "OpenCommand.h"
#include "SaveCommand.h"
#include "SaveAsCommand.h"
#include "CloseCommand.h"
#include "HelpCommand.h"
#include "ExitCommand.h"
#include "DescribeCommand.h"
#include "ExportCommand.h"
#include "ImportCommand.h"
#include "ShowtablesCommand.h"
#include "PrintCommand.h"
#include "PreviousPageCommand.h"
#include "NextPageCommand.h"
#include "OutCommand.h"
#include "RenameCommand.h"
#include "AddColumnCommand.h"

#include <iostream>

/** @brief конструктор с параметър*/
Invoker::Invoker(IDatabase* db)
{
	commands.push_back(new OpenCommand(db));
	commands.push_back(new SaveCommand(db));
	commands.push_back(new SaveAsCommand(db));
	commands.push_back(new CloseCommand(db));
	commands.push_back(new HelpCommand(db));
	commands.push_back(new ExitCommand(db));
	commands.push_back(new ImportCommand(db));
	commands.push_back(new ExportCommand(db));
	commands.push_back(new ShowtablesCommand(db));
	commands.push_back(new DescribeCommand(db));
	commands.push_back(new PrintCommand(db));
	commands.push_back(new NextPageCommand(db));
	commands.push_back(new PreviousPageCommand(db));
	commands.push_back(new OutCommand(db));
	commands.push_back(new RenameCommand(db));
	commands.push_back(new AddColumnCommand(db));
}

/** @brief деструктор */
Invoker::~Invoker()
{
	for (size_t i = 0; i < commands.size(); ++i)
	{
		delete commands[i];
	}
}

/** @brief извиква желаната команда от подаден низ */
void Invoker::executeCmd(std::string input)
{
	for (ICommand* cmd : commands) {
		if (CmdValidator::validateCommand(cmd, input)) {
			cmd->execute(input);
			return;
		}
	}
	std::cout << "Invalid command!\n";
}