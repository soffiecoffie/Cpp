#include "Database.h"

void Database::del()
{
	for (size_t i = 0; i < tables.size(); ++i)
	{
		delete tables[i];
	}
}

//проверява дали дадена таблица е вече заредена
bool Database::isImported(std::string filename) const
{
	std::ifstream in(filename);
	if (!in) return false;
	Table t;
	t.read(in);

	for (size_t i = 0; i < tables.size(); ++i)
	{
		if (t.getName() == tables[i]->getName()) return true;
	}
	return false;
}

//конструктор по подразбиране
Database::Database() : tables({}), tableInfo({})
{
}

//конструктор с параметри
Database::Database(std::vector<ITable*> arr, std::string c, std::vector<std::string> tInfo) : tables(arr), tableInfo(tInfo),
																							catalog(c)
{
}

//деструктор
Database::~Database()
{
	del();
}

void Database::setCatalogName(std::string str)
{
	catalog = str;
}

void Database::open(std::string input)
{
	std::ifstream in(input, std::ios::in);
	if (!in) {
		std::ofstream out(input);
		if (!out) {
			std::cout << "Can't open file " << input << "!\n Command was unsuccessful!\n";
			return;
		}
		write(out);
	}
	else {
		read(in);
	}
	setCatalogName(input);
	isOpen = 1;

	std::cout << "Successfully opened file " << input << "!\n";
}

void Database::close()
{
	del();
	isDone = 0;
	isOpen = 0;
	std::cout << "No changes were made to your calendar.\n";
	std::cout << "Successfully closed catalog " << catalog << std::endl;
}

void Database::save()
{
	std::ofstream out(catalog);
	if (!out) {
		std::cout << "Can't open file " << catalog << std::endl;
	}
	else {
		write(out);
		std::cout << "Successfully saved " << catalog << std::endl;
	}
}

void Database::saveas(std::string input)
{
	std::ofstream out(input);
	if (!out) {
		std::cout << "Can't save file as" << input << std::endl;
	}
	else {
		write(out);
		std::cout << "Successfully saved " << input << "!\n";
	}
}

void Database::exit()
{
	std::cout << "Exiting the program...";
	isDone = 1;
}

//зарежда нова таблица
void Database::import(std::string filename)
{
	if (isImported(filename)) {
		std::cout << "Error! " << filename << " has already been imported!\n";
		return;
	}
	else {
		std::ifstream in(filename);
		if (!in) {
			std::cout << "Can't open file " << filename << "!\nCommand was unsuccessful!\n";
		}
		else {
			tables.push_back(new Table);

			size_t lastInd = tables.size() - 1;

			tables[lastInd]->read(in);
			tables[lastInd]->setFileName(filename);

			in.close();
			std::string tabInfo = filename + " "+ tables[tables.size() - 1]->getName();
			tableInfo.push_back(tabInfo);

			std::cout << filename << " has successfully been imported!\n";
		}
	}


}

/*показва списък с имената на всички заредени таблици*/
void Database::showtables() const
{
	std::cout << std::endl;
	if (tables.size() > 0) std::cout << "All tables:\n";
	for (size_t i = 0; i < tables.size(); ++i)
	{
		std::cout << tables[i]->getName() << std::endl;
	}
	if (tables.size() == 0) std::cout << "There are no tables.\n";
	std::cout << "Successfully executed command!\n";
}

void Database::describe(std::string name) const
{
	ITable* t = getTableByName(name);
	size_t size = t->getSize();
	IColumn** cols = t->getCols();

	if (size > 0) std::cout << "Column types for table \"" << name << "\":\n";
	for (size_t i = 0; i < size; ++i)
	{
		std::cout << "Column \"" << cols[i]->getTitle() << "\": " << cols[i]->getType()<<std::endl;
	}
	if (size == 0) std::cout << "There are no tables.\n";
	std::cout << "\nSuccessfully executed command!\n";
}

void Database::myExport(std::string name, std::string filename) const
{
	ITable* t = getTableByName(name);
	std::ofstream out(filename);
	if (!out) {
		std::cout << "Command unsuccessful!\n";
	}
	else {
		t->write(out);
		std::cout << "\nSuccessfully executed command!\n";
	}
}

void Database::print(std::string tableName)
{
	ITable* t = getTableByName(tableName);
	if (t == nullptr) {
		std::cout << "There isn't a table with this name!\n";
		return;
	}
	size_t max = t->getMaxRowSize();

	if (max <= 13) {
		t->print(std::cout);
	}
	else {
		next(tableName);
		isPageCmdOn = 1;

		Invoker invoker(this);

		std::string input;
		while (isPageCmdOn)
		{
			std::cout << "\nInput \"next\" for next page, \"previous\" for previous page, \"out\" to leave page mode:\n";
			std::cout << "> ";
			std::getline(std::cin, input);
			input = input + " " + tableName;

			invoker.executeCmd(input);
		}
		std::cout << std::endl;
	}
}

void Database::rename(std::string oldName, std::string newName)
{
	ITable* t = getTableByName(oldName);
	if (t == nullptr) {
		std::cout << "There is no table called " << oldName << "!\n";
		std::cout << "No renaming done!\n";
		return;
	}
	if (oldName == newName) {
		std::cout << "The table is already called " << newName << "!\n";
		std::cout << "No renaming done!\n";
		return;
	}
	for (size_t i = 0; i < tables.size(); ++i)
	{
		if (newName == tables[i]->getName()) {
			std::cout << "A table with the name " << newName << " already exists!\n";
			std::cout << "No renaming done!\n";
			return;
		}
	}
	t->setName(newName);
	std::cout << "Successfully renamed table " << oldName << " to " << newName << "!\n";
}

void Database::out()
{
	isPageCmdOn = 0;
	start = 0;
	end = 0;
	std::cout << "Successfully left page mode!\n";
}

void Database::next(std::string tableName)
{
	ITable* t = getTableByName(tableName);
	size_t max = t->getMaxRowSize();
	if (end == max) {
		std::cout << "This is the last page!\n";
	}
	else {
		if (end == 0) {
			end = 12;
		}
		else {
			start = end;
			end = end + 12;
			if (end > max) end = max;
		}

		t->printFromTo(start, end);
	}
}

void Database::previous(std::string tableName)
{
	ITable* t = getTableByName(tableName);
	if (end == 12) {
		std::cout << "This is the first page!\n";
	}
	else {
		end = start;
		start = end - 12;
		if (start < 0) start = 0;

		t->printFromTo(start, end);
	}
}

void Database::addColumn(std::string tableName, std::string colName, std::string type)
{
	ITable* t = getTableByName(tableName);
	if (t == nullptr) {
		std::cout << "No table called " << tableName << " exists!\n";;
		return;
	}
	t->addCol(colName, type);
	std::cout << "Successfully added a column!\n";
}

std::istream& Database::read(std::istream& in)
{
	size_t tableInfoSize;
	std::string temp;

	in.ignore(9);
	in >> tableInfoSize;
	in.ignore(100, '\n');
	in.ignore(1, '\n');

	for (size_t i = 0; i < tableInfoSize; ++i)
	{
		getline(in, temp, '\n');
		tableInfo.push_back(temp);

		std::string filename = getWord(1, temp);
		std::ifstream in(filename);

		tables.push_back(new Table);

		size_t lastInd = tables.size() - 1;
		
		tables[lastInd]->read(in);
		tables[lastInd]->setFileName(filename);
		
		in.close();
		//tables[i]->print(std::cout);
		//std::cout << std::endl;
	}

	return in;
}

std::ostream& Database::write(std::ostream& out) const
{
	size_t tableInfoSize = tableInfo.size();

	out << "There are " << tableInfoSize << " tables in this database:\n\n";

	for (size_t i = 0; i < tableInfoSize; ++i)
	{
		out << tableInfo[i] << '\n';
		std::ofstream out(tables[i]->getFileName());
		if (!out) {
			std::cout << "Can't save table " << tables[i]->getName() << "'s changes!\n";
		}
		else {
			tables[i]->write(out);
			out.close();
		}
	}
	return out;
}

ITable* Database::getTableByName(std::string name) const
{
	for (size_t i = 0; i < tables.size(); ++i)
	{
		if (tables[i]->getName() == name) return tables[i];
	}
	return nullptr;
}

bool Database::getIsOpen() const
{
	return isOpen;
}

bool Database::getIsDone() const
{
	return isDone;
}

bool Database::getIsPageCmdOn() const
{
	return isPageCmdOn;
}
