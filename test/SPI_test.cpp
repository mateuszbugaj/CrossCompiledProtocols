#include <gtest/gtest.h>

#include <SPIDevice.hpp>

extern "C" {
  #include <SPI.h>
  #include <SPI_HAL.h>
}
#include <SPI_HAL_DESKTOP.hpp>

class SPI_Test : public testing::Test {
  protected:
    SPI_HAL_PinManager pinManager;
    SPIDevice* transmitterDevice;
    SPIDevice* receiverDevice;

    void clearFile(std::string file){
      std::ofstream ofs(file, std::ios::trunc);
      ofs.close();
    }

    void SetUp() override {
      clearFile(TRANSMITTER_LOG_FILE);
      clearFile(RECEIVER_LOG_FILE);
      clearFile(PIN_STATE_FILE);
      SPI_HAL_setPinManager(&pinManager);

      transmitterDevice = new SPIDevice("transmitter", SPI_Role::SPI_MASTER, &pinManager);
      receiverDevice = new SPIDevice("receiver", SPI_Role::SPI_SLAVE, &pinManager);

      transmitterDevice->addSlaveDevice(receiverDevice);
    }

    void TearDown() override {
      delete transmitterDevice;
      delete receiverDevice;
    }
};

int getBit(int byte, int bit){
  return (byte & (1 << bit)) >> bit;
}

TEST_F(SPI_Test, basicConfigurationTest){
  SPI_Config* config = transmitterDevice->getConfig();

  EXPECT_EQ(config->role, SPI_Role::SPI_MASTER);
}

TEST_F(SPI_Test, sendByteTest){
  EXPECT_EQ(getBit(receiverDevice->getConfig()->SPISR, SPI_SPIF), 0);
  EXPECT_EQ(getBit(transmitterDevice->getConfig()->SPISR, SPI_SPIF), 0);

  uint8_t receiverPayload = 55;
  uint8_t transmitterPayload = 22;

  receiverDevice->sendByte(receiverPayload, "");
  transmitterDevice->sendByte(transmitterPayload, receiverDevice->getName());

  EXPECT_EQ(getBit(receiverDevice->getConfig()->SPISR, SPI_SPIF), 1);
  EXPECT_EQ(getBit(transmitterDevice->getConfig()->SPISR, SPI_SPIF), 1);

  EXPECT_EQ((int) receiverDevice->getConfig()->SPIDR, transmitterPayload);
  EXPECT_EQ((int) transmitterDevice->getConfig()->SPIDR, receiverPayload);
}