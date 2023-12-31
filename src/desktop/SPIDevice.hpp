#pragma once

#include <map>
#include <Device.hpp>

extern "C" {
  #include <SPI.h>
  #include <SPI_HAL.h>

    #include <SPI_console.h>
}

#include <SPI_HAL_DESKTOP.hpp>

class SPIDevice : public Device {
  private:
    SPI_Config SPI_config;
    bool isRunning = true;
    std::map<std::string, SPIDevice*> slaveDevices;

  public:
    SPIDevice(std::string name, SPI_Role role, SPI_HAL_PinManager* pinManager);
    ~SPIDevice();
    void executionThreadFunction();
    SPI_Config* getConfig();
    void addSlaveDevice(SPIDevice* device);
    void sendByte(uint8_t byte, std::string receiverName);
};