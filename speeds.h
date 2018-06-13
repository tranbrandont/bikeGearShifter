typedef struct {
    char front;
    char back;
    char name[3];
} speed;

speed speeds[18];
 
void setspeed(int speedindex);
void shiftHarder();
void shiftEasier();
