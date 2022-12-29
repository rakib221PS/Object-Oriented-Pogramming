#include <iostream>
#include <stdexcept>
#include <vector>
#include <ctime>

class Error
{
    void HourError()
    {
        throw std::runtime_error("Hour is not valid");
    }
    void MinuteError()
    {
        throw std::runtime_error("Minute is not valid");
    }

    void SecondError()
    {
        throw std::runtime_error("Second is not valid");
    }
};

class Clock
{
    int hour, minute, second;

public:
    Clock(int, int, int);
    void setHours(int);
    int getHours();
    friend std::ostream &operator<<(std::ostream &, const Clock &);
};

Clock::Clock(int hour = 0, int minute = 0, int second = 0) : hour(hour), minute(minute), second(second)
{
}

void Clock::setHours(int hour)
{
    hour = hour;
}

int Clock::getHours()
{
    return hour;
}

std::ostream &operator<<(std::ostream &os, const Clock &content)
{
    os<<content.hour << " " <<content.minute << " " <<content.second << std::endl;
    return os;
}

class ClassAlarm : public Clock
{
    int capacity;
    int alarm_len;
    std::vector<std::vector<int>> alarm_times;

public:
    ClassAlarm(int, int, int);
    void addAlarm(int, int, int);
    void eraseAlarm();
    void size();
    friend std::ostream &operator<<(std::ostream &, const Clock &);
};

ClassAlarm::ClassAlarm(int hour = 0, int minute = 0, int second = 0) : Clock(hour, minute, second), capacity(2), alarm_len(0), alarm_times(capacity)
{
    for (int i = 0; i < capacity; i++)
    {
        alarm_times[i] = std::vector<int>(4);
    }
}

void ClassAlarm::addAlarm(int hour, int minute, int second)
{
    if (alarm_len == capacity)
    {
        int new_capacity = capacity * 2;
        std::vector<std::vector<int>> tmp(new_capacity);
        for (int i = 0; i < new_capacity; i++)
        {
            tmp[i] = std::vector<int>(4);
        }

        for (int i = 0; i < capacity; i++)
        {
            tmp[i][0] = alarm_times[i][0];
            tmp[i][1] = alarm_times[i][1];
            tmp[i][2] = alarm_times[i][2];
            tmp[i][3] = alarm_times[i][3];
        }

        for (int i = 0; i < capacity; i++)
        {
            alarm_times[i].clear();
        }
        alarm_times.clear();
        alarm_times = tmp;
        capacity = new_capacity;
    }

    alarm_times[alarm_len][0] = hour;
    alarm_times[alarm_len][1] = minute;
    alarm_times[alarm_len][2] = second;
    alarm_times[alarm_len][3] = 1;
    alarm_len++;
}

std::ostream &operator<<(std::ostream &os, const ClassAlarm &content)
{
    time_t curr_time;
    curr_time = time(NULL);
    tm *tm_local = localtime(&curr_time);
    std::cout<< tm_local->tm_hour << ":" << tm_local->tm_min << ":" << tm_local->tm_sec;
    return os;
}

void ClassAlarm::size()
{
    alarm_times[3].clear();
    std::cout << alarm_times[3].size() << std::endl;
    alarm_times.clear();
    std::cout << alarm_times.size();
}

int main()
{
    Clock c1;
    Clock c2(3, 4, 5);
    std::cout << c2;
    ClassAlarm cA;
    cA.addAlarm(3, 4, 55);
    cA.addAlarm(3, 4, 55);
    cA.addAlarm(3, 4, 55);
    cA.addAlarm(3, 4, 55);
    cA.addAlarm(3, 4, 55);
    std::cout << cA;
    return 0;
}