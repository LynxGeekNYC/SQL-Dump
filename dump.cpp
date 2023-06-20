#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cstdio>

bool isDumpingDetected(const std::string& logFilePath, std::string& ipAddress) {
    std::ifstream logFile(logFilePath);
    std::string line;

    while (std::getline(logFile, line)) {
        if (line.find("mysqldump") != std::string::npos) {
            std::size_t found = line.find("Host:");
            if (found != std::string::npos) {
                std::size_t ipStart = found + 6; // Skip "Host: "
                std::size_t ipEnd = line.find(" ", ipStart);
                ipAddress = line.substr(ipStart, ipEnd - ipStart);
            }
            return true;
        }
    }

    return false;
}

std::string getCurrentDateTime() {
    std::time_t currentTime = std::time(nullptr);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&currentTime), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void sendEmail(const std::string& subject, const std::string& body) {
    std::string emailAddress = "your_email@example.com"; // Email address to send the notification
    std::string emailCommand = "echo \"" + body + "\" | mail -s \"" + subject + "\" " + emailAddress;
    std::system(emailCommand.c_str());
}

int main() {
    std::string logFilePath = "/var/log/mysql/error.log"; // Path to MySQL/MariaDB error log file

    std::string ipAddress;
    if (isDumpingDetected(logFilePath, ipAddress)) {
        std::string dateTime = getCurrentDateTime();
        std::string subject = "SQL data dumping detected!";
        std::string body = "Dump occurred at " + dateTime + " from IP address: " + ipAddress;

        std::cout << body << std::endl;
        sendEmail(subject, body);

        // Take appropriate action here, such as sending notifications or terminating the process.
    } else {
        std::cout << "No SQL data dumping detected." << std::endl;
    }

    return 0;
}
