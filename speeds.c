#include "speeds.h"
#include "servo.h"
#include "stepper.h"
int currspeed = 9;
//names must be 
void init_speed(speed* s, char front, char back, char* name){
    s->front = front;
    s->back = back;
    s->name[0] = name[0];
    s->name[1] = name[1];
    s->name[3] = '\0';
}

//initialize speeds in an order based on gear ratio
__attribute__((constructor)) void init_speeds(){
/*[[[cog
def speedname(i):
    out = str(i)
    if (len(out) == 1):
        out = " " + out
    return out

frontteeth = [28.0, 38.0, 48.0]
backteeth = [14.0, 16.0, 18.0, 20.0, 24.0, 28.0]
sets = []

#front gear number, back gear number, ratio
for i in range(0, len(frontteeth)):
    for j in range(0, len(backteeth)):
        sets.append((i, j, frontteeth[i]/backteeth[j]))
sets.sort(key=lambda x: x[2])

v = 0;
for i in sets:
    cog.outl('init_speed(&(speeds[' + str(v) +']), ' + str(i[0]) + ', ' + str(i[1]) + ', "' + speedname(v) + '"); //ratio=' + str(i[2]))
    v += 1

]]]*/
init_speed(&(speeds[0]), 0, 5, " 0"); //ratio=1.0
init_speed(&(speeds[1]), 0, 4, " 1"); //ratio=1.1666666666666667
init_speed(&(speeds[2]), 1, 5, " 2"); //ratio=1.3571428571428572
init_speed(&(speeds[3]), 0, 3, " 3"); //ratio=1.4
init_speed(&(speeds[4]), 0, 2, " 4"); //ratio=1.5555555555555556
init_speed(&(speeds[5]), 1, 4, " 5"); //ratio=1.5833333333333333
init_speed(&(speeds[6]), 2, 5, " 6"); //ratio=1.7142857142857142
init_speed(&(speeds[7]), 0, 1, " 7"); //ratio=1.75
init_speed(&(speeds[8]), 1, 3, " 8"); //ratio=1.9
init_speed(&(speeds[9]), 0, 0, " 9"); //ratio=2.0
init_speed(&(speeds[10]), 2, 4, "10"); //ratio=2.0
init_speed(&(speeds[11]), 1, 2, "11"); //ratio=2.111111111111111
init_speed(&(speeds[12]), 1, 1, "12"); //ratio=2.375
init_speed(&(speeds[13]), 2, 3, "13"); //ratio=2.4
init_speed(&(speeds[14]), 2, 2, "14"); //ratio=2.6666666666666665
init_speed(&(speeds[15]), 1, 0, "15"); //ratio=2.7142857142857144
init_speed(&(speeds[16]), 2, 1, "16"); //ratio=3.0
init_speed(&(speeds[17]), 2, 0, "17"); //ratio=3.4285714285714284
//[[[end]]]

//Home both servo and stepper to 0 positions
    home();
    setservopos(0);
    displayText(speeds[9].name);
}

void setspeed(int speedindex){
    if (speedindex < 0 || speedindex > 17){
        return;
    }
    displayText(speeds[speedindex].name);
    for (int i = 0; i < 100000; i++){} //waste some time while screen sets
    int delta = speeds[speedindex].back - speeds[currspeed].back;
    step(200 * delta);
    setservopos(speeds[speedindex].front);
    currspeed = speedindex;
}

void shiftHarder(){
    setspeed(currspeed + 1);
}

void shiftEasier(){
    setspeed(currspeed - 1);
}
