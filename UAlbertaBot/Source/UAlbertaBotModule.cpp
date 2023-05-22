/* 
 +----------------------------------------------------------------------+
 | UAlbertaBot                                                          |
 +----------------------------------------------------------------------+
 | University of Alberta - AIIDE StarCraft Competition                  |
 +----------------------------------------------------------------------+
 |                                                                      |
 +----------------------------------------------------------------------+
 | Author: David Churchill <dave.churchill@gmail.com>                   |
 +----------------------------------------------------------------------+
*/

#include "Common.h"
#include "UAlbertaBotModule.h"
#include "JSONTools.h"
#include "ParseUtils.h"
#include "UnitUtil.h"
#include "Global.h"
#include "StrategyManager.h"
#include "MapTools.h"


#include <iostream>
#include <fstream>
#include <string>

using namespace UAlbertaBot;
size_t game_num = 110;
UAlbertaBotModule::UAlbertaBotModule()
{
    Global::GameStart();
}

// This gets called when the bot starts!
void UAlbertaBotModule::onStart()
{
    // Parse the bot's configuration file if it has one, change this file path to where your config file is
    // Any relative path name will be relative to Starcraft installation folder
    ParseUtils::ParseConfigFile(Config::ConfigFile::ConfigFileLocation);

    // Set our BWAPI options here    
	BWAPI::Broodwar->setLocalSpeed(Config::BWAPIOptions::SetLocalSpeed);
	BWAPI::Broodwar->setFrameSkip(Config::BWAPIOptions::SetFrameSkip);
    
    if (Config::BWAPIOptions::EnableCompleteMapInformation)
    {
        BWAPI::Broodwar->enableFlag(BWAPI::Flag::CompleteMapInformation);
    }

    if (Config::BWAPIOptions::EnableUserInput)
    {
        BWAPI::Broodwar->enableFlag(BWAPI::Flag::UserInput);
    }

    if (Config::BotInfo::PrintInfoOnStart)
    {
        BWAPI::Broodwar->printf("Hello! I am %s, written by %s", Config::BotInfo::BotName.c_str(), Config::BotInfo::Authors.c_str());
    }

    // Call BWTA to read and analyze the current map
    if (Config::Modules::UsingGameCommander)
	{
        if (Config::Modules::UsingStrategyIO)
        {
            Global::Strategy().readResults();
            Global::Strategy().setLearnedStrategy();
        }
	}

    //Global::Map().saveMapToFile("map.txt");
}

void UAlbertaBotModule::onEnd(bool isWinner) 
{
    std::ofstream myfile;
    myfile.open("D://Everything School//BP//Testing//m" + std::to_string(game_num) + ".txt", std::ios_base::app);


	if (Config::Modules::UsingGameCommander)
	{
		Global::Strategy().onEnd(isWinner);
	}

    std::cout <<  std::to_string(game_num) << std::endl;
    //myfile << "==================== Game number " + std::to_string(game_num++)  + " ====================" << std::endl;

    if (isWinner) {
        std::cout << "Win\n";
        myfile << "Win\n";
    }
    else {
        std::cout << "Lose\n";
        myfile << "Lose\n";
    }
    std::cout << "frameCount: " + std::to_string(BWAPI::Broodwar->getFrameCount()) << std::endl;
    myfile << "frameCount: " + std::to_string(BWAPI::Broodwar->getFrameCount()) << std::endl;

    std::cout << "map: " + BWAPI::Broodwar->mapFileName() << std::endl;
    myfile << "map: " + BWAPI::Broodwar->mapFileName() << std::endl;

    std::cout << Config::Strategy::StrategyName << std::endl;
    myfile << Config::Strategy::StrategyName << std::endl;

    

    std::cout << "------------UAlbertaBot stats: -------------------\n";
    std::cout << "Number of units: " + std::to_string(BWAPI::Broodwar->self()->allUnitCount()) << std::endl;
    std::cout << "gatheredMinerals: " + std::to_string(BWAPI::Broodwar->self()->gatheredMinerals()) << std::endl;
    std::cout << "gatheredGas: " + std::to_string(BWAPI::Broodwar->self()->gatheredGas()) << std::endl;
    std::cout << "getUnitScore: " + std::to_string(BWAPI::Broodwar->self()->getUnitScore()) << std::endl;
    std::cout << "getBuildingScore: " + std::to_string(BWAPI::Broodwar->self()->getBuildingScore()) << std::endl;

    myfile << "------------UAlbertaBot stats: -------------------\n";
    myfile << "Number of units: " + std::to_string(BWAPI::Broodwar->self()->allUnitCount()) << std::endl;
    myfile << "gatheredMinerals: " + std::to_string(BWAPI::Broodwar->self()->gatheredMinerals()) << std::endl;
    myfile << "gatheredGas: " + std::to_string(BWAPI::Broodwar->self()->gatheredGas()) << std::endl;
    myfile << "getUnitScore: " + std::to_string(BWAPI::Broodwar->self()->getUnitScore()) << std::endl;
    myfile << "getBuildingScore: " + std::to_string(BWAPI::Broodwar->self()->   getBuildingScore()) << std::endl;

    auto opponent = BWAPI::Broodwar->enemy();

    

    std::cout << "------------Opponent stats: -------------------\n";
    std::cout << "Number of units: " + std::to_string(opponent->allUnitCount()) << std::endl;
    std::cout << "gatheredMinerals: " + std::to_string(opponent->gatheredMinerals()) << std::endl;
    std::cout << "gatheredGas: " + std::to_string(opponent->gatheredGas()) << std::endl;
    std::cout << "getUnitScore: " + std::to_string(opponent->getUnitScore()) << std::endl;
    std::cout << "getBuildingScore: " + std::to_string(opponent->getBuildingScore()) << std::endl;

    

    myfile << "------------Opponent stats: -------------------\n";
    myfile << "Number of units: " + std::to_string(opponent->allUnitCount()) << std::endl;
    myfile << "gatheredMinerals: " + std::to_string(opponent->gatheredMinerals()) << std::endl;
    myfile << "gatheredGas: " + std::to_string(opponent->gatheredGas()) << std::endl;
    myfile << "getUnitScore: " + std::to_string(opponent->getUnitScore()) << std::endl;
    myfile << "getBuildingScore: " + std::to_string(opponent->getBuildingScore()) << std::endl;


    std::cout << "Game Over\n";
       
    myfile << "Game Over\n"; 

    auto race = opponent->getRace();
    if (race == BWAPI::Races::Zerg) {
        std::cout << "Zerg" << std::endl;
        myfile << "Zerg\n";
    }
    else if (race == BWAPI::Races::Terran) {
        std::cout << "Terran" << std::endl;
        myfile << "Terran\n";
    }else if (race == BWAPI::Races::Protoss) {
        std::cout << "Protoss" << std::endl;
        myfile << "Protoss\n";
    }
    else {
        std::cout << "Unknown" << std::endl;
        myfile << "Unknown\n";
    }

    std::cout << opponent->getRace() << std::endl;
    myfile << opponent->getRace() + "\n";

    myfile << "numofNexus: " + std::to_string(BWAPI::Broodwar->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Nexus)) + "\n";
    myfile << "numofDetectors: " + std::to_string(BWAPI::Broodwar->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Observer)) + "\n";

    myfile.close();
    game_num++;
}

void UAlbertaBotModule::onFrame()
{
    if (BWAPI::Broodwar->getFrameCount() > 100000)
    {
        BWAPI::Broodwar->restartGame();
    }

    const char red = '\x08';
    const char green = '\x07';
    const char white = '\x04';

    if (!Config::ConfigFile::ConfigFileFound)
    {
        BWAPI::Broodwar->drawBoxScreen(0,0,450,100, BWAPI::Colors::Black, true);
        BWAPI::Broodwar->setTextSize(BWAPI::Text::Size::Huge);
        BWAPI::Broodwar->drawTextScreen(10, 5, "%c%s Config File Not Found", red, Config::BotInfo::BotName.c_str());
        BWAPI::Broodwar->setTextSize(BWAPI::Text::Size::Default);
        BWAPI::Broodwar->drawTextScreen(10, 30, "%c%s will not run without its configuration file", white, Config::BotInfo::BotName.c_str());
        BWAPI::Broodwar->drawTextScreen(10, 45, "%cCheck that the file below exists. Incomplete paths are relative to Starcraft directory", white);
        BWAPI::Broodwar->drawTextScreen(10, 60, "%cYou can change this file location in Config::ConfigFile::ConfigFileLocation", white);
        BWAPI::Broodwar->drawTextScreen(10, 75, "%cFile Not Found (or is empty): %c %s", white, green, Config::ConfigFile::ConfigFileLocation.c_str());
        return;
    }
    else if (!Config::ConfigFile::ConfigFileParsed)
    {
        BWAPI::Broodwar->drawBoxScreen(0,0,450,100, BWAPI::Colors::Black, true);
        BWAPI::Broodwar->setTextSize(BWAPI::Text::Size::Huge);
        BWAPI::Broodwar->drawTextScreen(10, 5, "%c%s Config File Parse Error", red, Config::BotInfo::BotName.c_str());
        BWAPI::Broodwar->setTextSize(BWAPI::Text::Size::Default);
        BWAPI::Broodwar->drawTextScreen(10, 30, "%c%s will not run without a properly formatted configuration file", white, Config::BotInfo::BotName.c_str());
        BWAPI::Broodwar->drawTextScreen(10, 45, "%cThe configuration file was found, but could not be parsed. Check that it is valid JSON", white);
        BWAPI::Broodwar->drawTextScreen(10, 60, "%cFile Not Parsed: %c %s", white, green, Config::ConfigFile::ConfigFileLocation.c_str());
        return;
    }

	if (Config::Modules::UsingGameCommander) 
	{ 
		m_gameCommander.update(); 
	}

    if (Config::Modules::UsingAutoObserver)
    {
        m_autoObserver.onFrame();
    }
}

void UAlbertaBotModule::onUnitDestroy(BWAPI::Unit unit)
{
	if (Config::Modules::UsingGameCommander) { m_gameCommander.onUnitDestroy(unit); }
}

void UAlbertaBotModule::onUnitMorph(BWAPI::Unit unit)
{
	if (Config::Modules::UsingGameCommander) { m_gameCommander.onUnitMorph(unit); }
}

void UAlbertaBotModule::onSendText(std::string text) 
{ 
	ParseUtils::ParseTextCommand(text);
}

void UAlbertaBotModule::onUnitCreate(BWAPI::Unit unit)
{ 
	if (Config::Modules::UsingGameCommander) { m_gameCommander.onUnitCreate(unit); }
}

void UAlbertaBotModule::onUnitComplete(BWAPI::Unit unit)
{
	if (Config::Modules::UsingGameCommander) { m_gameCommander.onUnitComplete(unit); }
}

void UAlbertaBotModule::onUnitShow(BWAPI::Unit unit)
{ 
	if (Config::Modules::UsingGameCommander) { m_gameCommander.onUnitShow(unit); }
}

void UAlbertaBotModule::onUnitHide(BWAPI::Unit unit)
{ 
	if (Config::Modules::UsingGameCommander) { m_gameCommander.onUnitHide(unit); }
}

void UAlbertaBotModule::onUnitRenegade(BWAPI::Unit unit)
{ 
	if (Config::Modules::UsingGameCommander) { m_gameCommander.onUnitRenegade(unit); }
}