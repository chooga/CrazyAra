#include "ataristate.h"
#include <iostream>
#include "ale_interface.hpp"
//#include "3rdparty/

#ifdef __USE_SDL
#include <SDL.h>
#endif

using namespace ale;

AtariState::AtariState():
    totalReward(0),
    steps(0)
{
//    ale.setInt("random_seed", 123);
//    //The default is already 0.25, this is just an example
//    ale.setFloat("repeat_action_probability", 0.25);

//#ifdef __USE_SDL
//    ale.setBool("display_screen", true);
//    ale.setBool("sound", true);
//#endif

//    ale.loadROM("/home/chooga/uni/ROMS/aleroms/pong.bin");

};

//AtariState::AtariState(const AtariState &atariState):
//{
//    spielGame(strategoState.spielGame->shared_from_this()),
//    spielState(strategoState.spielState->Clone())
//}


std::vector<stateInterface::Action> AtariState::legal_actions() const
{
    ActionVect a = ale.getLegalActionSet();
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
    ale.getScreenRGB(outputRgbBuffer);
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
    return ale.getFrameNumber();
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
    totalReward += ale.act(ale::Action(action));
    printf("%d, ", action);
}

void AtariState::undo_action(stateInterface::Action action)
{

}

void AtariState::prepare_action()
{

}

unsigned int AtariState::number_repetitions() const
{

}

int AtariState::side_to_move() const
{

}

Key AtariState::hash_key() const
{

}

void AtariState::flip()
{

}

stateInterface::Action AtariState::uci_to_action(std::string &uciStr) const
{

}

std::string AtariState::action_to_san(stateInterface::Action action, const std::vector<stateInterface::Action> &legalActions, bool leadsToWin, bool bookMove) const
{

}

std::string AtariState::action_to_string(stateInterface::Action action) const
{

}

TerminalType AtariState::is_terminal(size_t numberLegalMoves, float &customTerminalValue) const
{
    if(ale.game_over()){
           customTerminalValue = totalReward;
        return TERMINAL_CUSTOM;
    }
    return TERMINAL_NONE;
    //return ale.game_over()
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
//    ale.setInt("random_seed", 123);
//    //The default is already 0.25, this is just an example
//    ale.setFloat("repeat_action_probability", 0.25);

#ifdef __USE_SDL
//    ale.setBool("display_screen", true);
//    ale.setBool("sound", true);
#endif

    ale.loadROM("/home/chooga/uni/ROMS/aleroms/pong.bin");
}

AtariState *AtariState::clone() const
{
    AtariState* atariState = new AtariState();
    atariState->init(0, false);
    atariState->ale.environment->setState(this->ale.cloneState());
    atariState->totalReward = this->totalReward;
    return atariState;
}


