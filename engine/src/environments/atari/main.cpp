/* *****************************************************************************
 * A.L.E (Arcade Learning Environment)
 * Copyright (c) 2009-2013 by Yavar Naddaf, Joel Veness, Marc G. Bellemare,
 *  Matthew Hausknecht, and the Reinforcement Learning and Artificial Intelligence
 *  Laboratory
 * Released under the GNU General Public License; see License.txt for details.
 *
 * Based on: Stella  --  "An Atari 2600 VCS Emulator"
 * Copyright (c) 1995-2007 by Bradford W. Mott and the Stella team
 *
 * *****************************************************************************
 *  sharedLibraryInterfaceExample.cpp
 *
 *  Sample code for running an agent with the shared library interface.
 **************************************************************************** */

#include <iostream>
#include <ale_interface.hpp>
#include <filesystem>
#include "ataristate.h"
#include "agents/rawnetagent.h"
#include "agents/mctsagent.h"
#include "nn/tensorrtapi.h"
#include "uci/optionsuci.h"
#ifdef __USE_SDL
#include <SDL.h>
#endif



int main(int argc, char** argv) {

    SearchSettings ss;
    ss.useMCGS = false;
    ss.multiPV = 1 ;
    ss.threads = 1;
    SearchLimits sl;
    sl.nodes = 10;
    PlaySettings ps;
    EvalInfo ei;
    AtariState atariState;
    atariState.set_screen();
    atariState.init(0, false);
    float customReward;




//    srand(123);
//    AtariState state;
//    state.init(0, false);
//    for(int i = 0; i <= 100; i++) {
//        state.do_action((rand()%17+1));
//    }
//    unique_ptr<AtariState> state2 = unique_ptr<AtariState>(state.clone());
//    if(state2->getTotalReward() == state.getTotalReward())
//        printf("clone working!\n");
//    else
//        printf("new state: %e, old state: %e \n",state2->getTotalReward(), state.getTotalReward());



    TensorrtAPI nn(0, 1, "../model", "float32");
//    RawNetAgent rna(&nn,&ps,true);
    vector<unique_ptr<NeuralNetAPI>> netBatches;
    for (int deviceId = 0; deviceId <= 0; ++deviceId) {
        for (size_t i = 0; i < ss.threads; ++i) {
            netBatches.push_back(make_unique<TensorrtAPI>(deviceId, ss.batchSize, "../model", "float32"));
        }
    }
    MCTSAgent rna(&nn, netBatches ,&ss, &ps);
    rna.set_search_settings(&atariState,&sl,&ei);
    while (atariState.is_terminal(0,customReward) == TERMINAL_NONE) {
        rna.perform_action();
        cout << ei.bestMove << endl;
        atariState.do_action(ei.bestMove);
//        cout << "NEWEPISODE\n\n\n\n\n" << endl;
    }

//  if (argc < 2) {
//    std::cerr << "Usage: " << argv[0] << " rom_file" << std::endl;
//    return 1;
//  }

//  ale::ALEInterface ale;

//  // Get & Set the desired settings
//  ale.setInt("random_seed", 123);
//  //The default is already 0.25, this is just an example
//  ale.setFloat("repeat_action_probability", 0.25);

//#ifdef __USE_SDL
//  ale.setBool("display_screen", true);
//  ale.setBool("sound", true);
//#endif

//  // Load the ROM file. (Also resets the system for new settings to
//  // take effect.)
//  ale.loadROM(argv[1]);

//  // Get the vector of legal actions
//  ale::ActionVect legal_actions = ale.getLegalActionSet();

//  // Play 10 episodes
//  for (int episode = 0; episode < 10; episode++) {
//    float totalReward = 0;
//    while (!ale.game_over()) {
//      ale::Action a = legal_actions[rand() % legal_actions.size()];
//      // Apply the action and get the resulting reward
//      float reward = ale.act(a);
//      totalReward += reward;
//    }
//    cout << "Episode " << episode << " ended with score: " << totalReward
//         << endl;
//    ale.reset_game();
//  }
  return 0;
}


//Things to test:
//    assert(theOSystem.get());
//    if (rom_file.empty()) {
//      rom_file = theOSystem->romFile();
//    }

//    // Load all settings corresponding to the ROM file and create a new game
//    // console, with attached devices, capable of emulating the ROM.
//    loadSettings(rom_file, theOSystem);

//    const Properties properties = theOSystem->console().properties();
//    const std::string md5 = properties.get(Cartridge_MD5);
//    const std::string name = properties.get(Cartridge_Name);

//    RomSettings* wrapper = buildRomRLWrapper(rom_file, md5);

//    romSettings.reset(wrapper);

//    // Custom environment settings required for a specific ROM must be added
//    // before the StellaEnvironment is constructed.
//    romSettings->modifyEnvironmentSettings(theOSystem->settings());

//    environment.reset(new StellaEnvironment(theOSystem.get(), romSettings.get()));
//    max_num_frames = theOSystem->settings().getInt("max_num_frames_per_episode");
//    environment->reset();
