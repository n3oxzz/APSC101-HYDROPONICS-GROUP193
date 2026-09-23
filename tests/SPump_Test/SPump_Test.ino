 /* 
 * APSC 101 Example Sketch
 *
 * M.Malik for APSC 101, 2024.06.30
 * Everything is identical to other pump/motors. Nothing special
 *
 * Submersible Pumps are NOT REVERSIBLE. 
 * They will pump in the same direction irrespective of run() direction.
 * This pump has a very high flow, so you might need to run it slower
 */


#include <AFMotor.h>

AF_DCMotor spump(2);

void setup() {}

void loop() {  
  spump.setSpeed(150); // Just check how the pump works. You can increase or decrease the speed same as other motors/pumps.
  spump.run(FORWARD);
}
