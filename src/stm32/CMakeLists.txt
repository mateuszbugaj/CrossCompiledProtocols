add_executable(
  Stm32Demo
  Stm32Demo.cpp
)
add_dependencies(
  Stm32Demo
  libopencm3
)
add_library(USART USART.cpp USART.hpp)
target_link_libraries(
  Stm32Demo
  USART
  GenericI2C
  Console
  ${LIBOPENCM3_BLUEPILL_LIBRARIES}
)
add_bin_from_elf(
  Stm32Demo.bin
  Stm32Demo
)
add_stlink_upload_target(Stm32Demo.bin)