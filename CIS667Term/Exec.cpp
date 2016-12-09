#include <iostream>
#include <memory>
#include "Deck.h"
#include "Table.h"
#include "Game.h"
#include "ComputerPlayer.h"
#include "UserPlayer.h"

class Executive
{
public:
	Executive();
	Executive(const Executive& ex) = delete;
	Executive& operator=(const Executive& ex) = delete;
	~Executive();
	void processCommand();
private:
	std::unique_ptr<Deck> deck_ = nullptr;
	std::unique_ptr<Table> table_ = nullptr;
	std::unique_ptr<Game> game_ = nullptr;
	std::unique_ptr<ComputerPlayer> comp1_ = nullptr;
	std::unique_ptr<ComputerPlayer> comp2_ = nullptr;
	std::unique_ptr<ComputerPlayer> comp3_ = nullptr;
	std::unique_ptr<UserPlayer> user_ = nullptr;
};

Executive::Executive()
{
	deck_ = std::unique_ptr<Deck>(new Deck());
	table_ = std::unique_ptr<Table>(new Table());
	comp1_ = std::unique_ptr<ComputerPlayer>(new ComputerPlayer());
	comp2_ = std::unique_ptr<ComputerPlayer>(new ComputerPlayer());
	comp3_ = std::unique_ptr<ComputerPlayer>(new ComputerPlayer());
	user_ = std::unique_ptr<UserPlayer>(new UserPlayer());
	game_ = std::unique_ptr<Game>(new Game(*deck_, *table_, *comp1_, *comp2_, *comp3_, *user_));
}


Executive::~Executive()
{
}

void Executive::processCommand()
{
	game_->playGame();
}

void main()
{
	Executive exec;
	exec.processCommand();

}