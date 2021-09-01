#include "ataristate.h"
#include <iostream>
#include "ale_interface.hpp"
//#include "3rdparty/

#ifdef __USE_SDL
#include <SDL.h>
#endif

using namespace ale;

AtariState::AtariState():
    totalReward(0)
{
    ale = new ale::ALEInterface();
    //            ale = std::make_unique<ale::ALEInterface>();
    ale->setInt("random_seed", 123);
    //The default is already 0.25, this is just an example
    ale->setFloat("repeat_action_probability", 0.25);

    //        #ifdef __USE_SDL
    //            ale->setBool("display_screen", true);
    //            ale->setBool("sound", true);
    //        #endif

    ale->loadROM("/home/chooga/uni/ROMS/aleroms/pong.bin");


}

AtariState::AtariState(bool)
{

};

//AtariState::AtariState(const AtariState &atariState):
//{
//    spielGame(strategoState.spielGame->shared_from_this()),
//    spielState(strategoState.spielState->Clone())
//}


std::vector<stateInterface::Action> AtariState::legal_actions() const
{
    ActionVect a = ale->getLegalActionSet();
    std::vector<stateInterface::Action> returnActionVect;
    returnActionVect.resize(a.size());
    std::copy(a.begin(),a.end(),returnActionVect.begin());
    return returnActionVect;

}

void AtariState::set(const std::string &fenStr, bool isChess960, int variant)
{

}

void AtariState::get_state_planes(bool normalize, float *inputPlanes, Version version) const
{
    std::vector<unsigned char> outputRgbBuffer;
    ale->getScreenRGB(outputRgbBuffer);
    std::copy(outputRgbBuffer.begin(),outputRgbBuffer.end(),inputPlanes);
    if(normalize){
        for(int i=0;i<outputRgbBuffer.size();i++){
            inputPlanes[i]/=255;
        }
    }
}

float AtariState::getTotalReward() const
{
    return totalReward;
}

unsigned int AtariState::steps_from_null() const
{
    return ale->getFrameNumber();
}

bool AtariState::is_chess960() const
{
    return false;
}

std::string AtariState::fen() const
{
    return "";
}

void AtariState::do_action(stateInterface::Action action)
{
    totalReward += ale->act(ale::Action(action));
//    printf("%d, ", action);
}

void AtariState::undo_action(stateInterface::Action action)
{
}

void AtariState::prepare_action()
{

}

unsigned int AtariState::number_repetitions() const
{
    return 0;
}

int AtariState::side_to_move() const
{
    return 0;
}

Key AtariState::hash_key() const
{
    return Key();
}

void AtariState::flip()
{

}

stateInterface::Action AtariState::uci_to_action(std::string &uciStr) const
{

}

std::string AtariState::action_to_san(stateInterface::Action action, const std::vector<stateInterface::Action> &legalActions, bool leadsToWin, bool bookMove) const
{
    return std::to_string(action);
}

std::string AtariState::action_to_string(stateInterface::Action action) const
{
    //    using std::cout; using std::cin;
    //    using std::endl; using std::string;

    //    enum Fruit { PLAYER_A_NOOP, PLAYER_A_FIRE ,PLAYER_A_UP ,PLAYER_A_RIGHT ,PLAYER_A_LEFT ,PLAYER_A_DOWN ,PLAYER_A_UPRIGHT ,PLAYER_A_UPLEFT ,PLAYER_A_DOWNRIGHT    ,PLAYER_A_DOWNLEFT     ,PLAYER_A_UPFIRE       ,PLAYER_A_RIGHTFIRE    ,PLAYER_A_LEFTFIRE     ,PLAYER_A_DOWNFIRE     ,PLAYER_A_UPRIGHTFIRE  ,PLAYER_A_UPLEFTFIRE   ,PLAYER_A_DOWNRIGHTFIRE,PLAYER_A_DOWNLEFTFIRE ,PLAYER_B_NOOP         ,PLAYER_B_FIRE         ,PLAYER_B_UP           ,PLAYER_B_RIGHT        ,PLAYER_B_LEFT         ,PLAYER_B_DOWN         ,PLAYER_B_UPRIGHT      ,PLAYER_B_UPLEFT       ,PLAYER_B_DOWNRIGHT    ,PLAYER_B_DOWNLEFT     ,PLAYER_B_UPFIRE       ,PLAYER_B_RIGHTFIRE    ,PLAYER_B_LEFTFIRE     ,PLAYER_B_DOWNFIRE     ,PLAYER_B_UPRIGHTFIRE  ,PLAYER_B_UPLEFTFIRE   ,PLAYER_B_DOWNRIGHTFIRE,PLAYER_B_DOWNLEFTFIRE ,RESET                 ,UNDEFINED             ,RANDOM                ,SAVE_STATE            ,LOAD_STATE            ,SYSTEM_RESET          ,LAST_ACTION_INDEX       };
    //    static const char *enum_str[] =
    //            { "Banana Pie", "Coconut Tart", "Mango Cookie", "Carambola Crumble" };

    //    string getStringForEnum( int enum_val )
    //    {
    //        string tmp(enum_str[enum_val]);
    //        return tmp;
    //    }
}

TerminalType AtariState::is_terminal(size_t numberLegalMoves, float &customTerminalValue) const
{
    if(ale->game_over()){
        customTerminalValue = totalReward;
        return TERMINAL_CUSTOM;
    }
    return TERMINAL_NONE;
    //return ale->game_over()
}

bool AtariState::gives_check(stateInterface::Action action) const
{
    return false;
}

void AtariState::print(std::ostream &os) const
{

}

Tablebase::WDLScore AtariState::check_for_tablebase_wdl(Tablebase::ProbeState &result)
{

}

void AtariState::set_auxiliary_outputs(const float *auxiliaryOutputs)
{

}

AtariState *AtariState::openBoard() const
{

}

void AtariState::init(int variant, bool isChess960)
{
    //    ale->setInt("random_seed", 123);
    //    //The default is already 0.25, this is just an example
    //    ale->setFloat("repeat_action_probability", 0.25);

#ifdef __USE_SDL
    //    ale->setBool("display_screen", true);
    //    ale->setBool("sound", true);
#endif

    ale->loadROM("/home/chooga/uni/ROMS/aleroms/pong.bin", false);
}

AtariState *AtariState::clone() const
{
    AtariState* atariState = new AtariState(true);
    //    atariState- >init(0, false);
    atariState->ale = this->ale;
    atariState->ale->environment->restoreState(this->ale->cloneState());
    atariState->totalReward = this->totalReward;
    return atariState;
}

void AtariState::set_screen()
{
            #ifdef __USE_SDL
                ale->setBool("display_screen", false);
//                ale->setBool("sound", true);
            #endif
}


