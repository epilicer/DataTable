#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

class RandomDateGenerator {
public:
    RandomDateGenerator(const std::string& start_date, const std::string& end_date)
        : m_startDate(start_date), m_endDate(end_date) {}

    std::vector<std::string> generateDates(int num_dates) {
        /*
        The generateDates() function takes an integer argument num_dates, 
        which specifies how many random dates to generate. 
        It returns a std::vector<std::string> containing the randomly generated dates.
        */
        std::vector<std::string> dates;
        time_t start_time = convertToDate(m_startDate);
        time_t end_time = convertToDate(m_endDate);
        
        for (int i = 0; i < num_dates; i++) {
            time_t random_time = getRandomTime(start_time, end_time);
            std::string random_date = convertToDateString(random_time);
            dates.push_back(random_date);
        }
        
        return dates;
    }

private:
    std::string m_startDate;
    std::string m_endDate;
    
    time_t convertToDate(const std::string& date_str) {
        /*
        The convertToDate() function converts a date string to a time_t value, 
        which is the number of seconds since the UNIX epoch (January 1, 1970).
        */
        struct tm tm = {};
        strptime(date_str.c_str(), "%Y-%m-%d", &tm);
        return mktime(&tm);
    }
    
    std::string convertToDateString(time_t time) {
        /*
        The convertToDateString() function converts a time_t value to a date string in the format "YYYY-MM-DD".
        */
        char buffer[11];
        strftime(buffer, 11, "%Y-%m-%d", localtime(&time));
        return std::string(buffer);
    }
    

    time_t getRandomTime(time_t start_time, time_t end_time) {
        /*
        The getRandomTime() function generates a random time_t value between the start and end times by generating
        a random number of seconds between 0 and the difference between the two times, and adding that number of seconds to the start time.
        */        
        double random_seconds = std::rand() / (double)RAND_MAX * (end_time - start_time);
        return start_time + random_seconds;
    }
};
