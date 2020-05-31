#include "Invoker.h"
#include "CmdValidator.h"
#include "OpenCommand.h"
#include "SaveCommand.h"
#include "SaveAsCommand.h"
#include "CloseCommand.h"
#include "HelpCommand.h"
#include "ExitCommand.h"
#include "BookCommand.h"
#include "UnbookCommand.h"
#include "AgendaCommand.h"
#include "FindCommand.h"
#include "HolidayCommand.h"
#include "BusydaysCommand.h"
#include "FindslotCommand.h"
#include "FindslotWithCommand.h"
#include "MergeCommand.h"
#include "ChangeCommand.h"
#include <iostream>

Invoker::Invoker(ISchedule* _s)
{
	commands.push_back(new OpenCommand(_s));// , new HelpCommand(_s));
	commands.push_back(new SaveCommand(_s));
	commands.push_back(new SaveAsCommand(_s));
	commands.push_back(new CloseCommand(_s));
	commands.push_back(new HelpCommand(_s));
	commands.push_back(new ExitCommand(_s));
	commands.push_back(new BookCommand(_s));
	commands.push_back(new UnbookCommand(_s));
	commands.push_back(new AgendaCommand(_s));
	commands.push_back(new FindCommand(_s));
	commands.push_back(new HolidayCommand(_s));
	commands.push_back(new BusydaysCommand(_s));
	commands.push_back(new FindslotCommand(_s));
	commands.push_back(new FindslotwithCommand(_s));
	commands.push_back(new MergeCommand(_s));
	commands.push_back(new ChangeCommand(_s));
}

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