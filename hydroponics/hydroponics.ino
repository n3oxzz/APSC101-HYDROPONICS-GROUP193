#include <Arduino.h>

#include "src/hardware.h"
#include "src/settings.h"

#include "src/interface.h"
#include "src/sensing.h"
#include "src/nutrient.h"
#include "src/ph.h"
#include "src/mixing.h"
#include "src/transfer.h"

static enum class State { IDLE, CONTROL_NUTRIENT, CONTROL_PH, TRANSFER_PLANT, TRANSFER_EXCESS, STOPPED }
static State state = State::IDLE;

void setup()
{
    // Project init code
    initInterface();
    initSensing();
    initNutrient();
    initPH();
    initMixing();
    initTransfer();
}

void loop()
{
    // Project loop code
    updateInterface();
    updateSensing();
    updateNutrient();
    updatePH();
    updateMixing();
    updateTransfer();
    
    if (state == State::IDLE) {
    
    }
    if (state == State::CONTROL_NUTRIENT) {
      if (!isNutrientActive()) {
        double tds = getCurrentTDS();
        
        if (tds < TARGET_TDS) {
          double amount = calculateRequiredNutrients(tds);
        
          bool success = dispenseNutrients(amount);

          runMixer(250*0.75, )
        }
        else if (!isMixingActive()) {
            state = State::CONTROL_PH;
        }
      }
    }
    if (state == State::CONTROL_PH) {
      if (!isPHActive()) {
        double ph = getCurrentPH();
        
        if (ph < TARGET_PH) {
          double amount = calculateRequiredPH(ph);
          
          bool success = dispensePH(amount);
        }
        else {
          state = State::TRANSFER_PLANT;
        }
      }
    }
    if (state == State::TRANSFER_PLANT) {

    }
    if (state == State::TRANSFER_EXCESS) {

    }
    if (state == State::STOPPED) {

    }
}
