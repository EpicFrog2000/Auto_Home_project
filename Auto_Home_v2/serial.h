#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <vector>
#include <poll.h>
#include <unordered_map>

int open_serial(const char* portname, int opt) {
    int fd = open(portname, opt);
    return fd;
}

int close_serial(int fd) {
    int result = close(fd);
    return result;
}

ssize_t write_serial(int fd, const void* buffer, size_t count) {
    ssize_t result = write(fd, buffer, count);
    return result;
}

ssize_t read_serial(int fd, void* buffer, size_t count) {
    ssize_t result = read(fd, buffer, count);
    return result;
}

int readSerialData() {
    const char* portname = "/dev/ttyACM0";
    int fd = open_serial(portname, O_RDWR); // Open the serial port for both read and write

    struct termios options;
    tcgetattr(fd, &options);
    cfmakeraw(&options); // Set raw mode
    cfsetispeed(&options, B9600); // Set input baud rate
    cfsetospeed(&options, B9600); // Set output baud rate
    tcsetattr(fd, TCSANOW, &options); // Apply the new settings

    // Write to the serial port
    const char* message = "Hello, Serial!";
    size_t messageLength = strlen(message);
    ssize_t bytesWritten = write_serial(fd, message, messageLength);

    // Set up poll structure
    struct pollfd fds[1];
    fds[0].fd = fd;
    fds[0].events = POLLIN;

    // Wait for input
    int timeout = 1000; // Timeout in milliseconds
    int pollResult = poll(fds, 1, timeout);

    if (pollResult > 0) {
        // Check if the serial port has data available
        if (fds[0].revents & POLLIN) {
            // Read from the serial port
            char buffer[256];
            ssize_t bytesRead = read_serial(fd, buffer, sizeof(buffer));
            buffer[bytesRead] = '\0'; // Null-terminate the buffer

            std::vector<int> numbers;

            // Read 20 input numbers to make it more precise
            for (int i = 0; i < 50; ++i) {
                ssize_t bytesRead = read_serial(fd, buffer, sizeof(buffer));
                buffer[bytesRead] = '\0'; // Null-terminate the buffer
                int number = atoi(buffer); // Convert the received data to an integer
                numbers.push_back(number);
            }

            // Count the occurrences of each number
            std::unordered_map<int, int> counts;
            for (int number : numbers) {
                counts[number]++;
            }

            // Find the number with the highest count
            int mostCommonNumber = -1;
            int highestCount = 0;
            for (const auto& pair : counts) {
                if (pair.second > highestCount) {
                    mostCommonNumber = pair.first;
                    highestCount = pair.second;
                }
            }

            // Close the serial port
            close_serial(fd);
            return mostCommonNumber;
        }
    }
    // Close the serial port
    close_serial(fd);
}
