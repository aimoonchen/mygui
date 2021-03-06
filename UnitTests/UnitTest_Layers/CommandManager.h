/*!
	@file
	@author		Albert Semenov
	@date		11/2009
*/
#ifndef COMMAND_MANAGER_H_
#define COMMAND_MANAGER_H_

#include <MyGUI.h>

namespace demo
{

	class CommandManager
	{
	public:
		typedef MyGUI::delegates::CDelegate2<const std::string&, MyGUI::Any> CommandDelegate;

	public:
		CommandManager();
		virtual ~CommandManager();

		static CommandManager& getInstance()
		{
			return *msCommandManager;
		}

		void execiteCommand(const std::string& _name, MyGUI::Any _data);

		void registerCommand(const std::string& _name, CommandDelegate::IDelegate* _delegate);
		void unregisterCommand(const std::string& _name);

	private:
		static CommandManager* msCommandManager;
		typedef std::map<std::string, CommandDelegate> MapDelegate;
		MapDelegate mDelegates;
	};

} // namespace demo

#endif // COMMAND_MANAGER_H_
