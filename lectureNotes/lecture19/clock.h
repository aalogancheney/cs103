class Clock {
  public:
    Clock(int hour, int minute, int second);
    Clock(); // This is the default constructor. 
             // It is good practice to have this in every class for now. 
    void SetAlarmTime(int hour, int minute, int second);
    void TurnAlarmOff();
    void printTime();
    void tickTock();
  
  private:
    int currentHour;
    int currentMinute;
    int currentSecond;
    int alarmHour;
    int alarmMinute;
    int alarmSecond;
    bool alarmOn;
};
