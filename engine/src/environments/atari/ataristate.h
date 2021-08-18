#ifndef ATARISTATE_H
#define ATARISTATE_H

#include "state.h"
#include <iostream>
#include "ale_interface.hpp"
#include "ale_state.hpp"

#ifdef __USE_SDL
#include <SDL.h>
#endif

class StateConstantsAtari : public StateConstantsInterface<StateConstantsAtari>
{
public:
    static uint BOARD_WIDTH() {
        return 210 ;
    }
    static uint BOARD_HEIGHT() {
        return  160;
    }
    static uint NB_CHANNELS_TOTAL() {
        return 3;
    }
    static uint NB_LABELS() {
        return 43;  //43 enum action
    }
    static uint NB_LABELS_POLICY_MAP() {
        return NB_LABELS();  // TODO
    }
    static uint NB_PLAYERS() {
        return  1;
    }
     static uint NB_AUXILIARY_OUTPUTS() {
        return 0;
    }
    static std::string action_to_uci(stateInterface::Action action, bool is960) {
        // TODO use actual uci for this
        return std::to_string(action);
    }
    template<PolicyType p = normal, MirrorType m = notMirrored>
    static stateInterface::MoveIdx action_to_index(stateInterface::Action action) {
        return action;  // TODO
    }
    static void init(bool isPolicyMap) {
        return; // pass
    }
};

class AtariState : public State
{
private:
    //std::unique_ptr<const ale::ALEInterface> spielState;
    ale::ALEInterface ale;
    float totalReward;
    uint steps;

public:
    AtariState();
    AtariState(const AtariState& atarstate);
    std::vector<stateInterface::Action> legal_actions() const;
    void set(const std::string &fenStr, bool isChess960, int variant);
    void get_state_planes(bool normalize, float *inputPlanes,  Version version) const;
    float getTotalReward() const;
    unsigned int steps_from_null() const;
    bool is_chess960() const;
    std::string fen() const;
    void do_action(stateInterface::Action action);
    void undo_action(stateInterface::Action action);
    void prepare_action();
    unsigned int number_repetitions() const;
    int side_to_move() const;
    Key hash_key() const;
    void flip();
    stateInterface::Action uci_to_action(std::string &uciStr) const;
    std::string action_to_san(stateInterface::Action action, const std::vector<stateInterface::Action> &legalActions, bool leadsToWin, bool bookMove) const;
    std::string action_to_string(stateInterface::Action action) const;
    TerminalType is_terminal(size_t numberLegalMoves, float &customTerminalValue) const;
    bool gives_check(stateInterface::Action action) const;
    void print(std::ostream &os) const;
    Tablebase::WDLScore check_for_tablebase_wdl(Tablebase::ProbeState &result);
    void set_auxiliary_outputs(const float* auxiliaryOutputs);
    AtariState *openBoard() const;
    void init(int variant, bool isChess960) override;
    AtariState *clone() const;
};

#endif // ATARISTATE_H
