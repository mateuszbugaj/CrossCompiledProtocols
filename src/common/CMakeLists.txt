if(TARGET_PLATFORM STREQUAL "DESKTOP")
  add_library(Console SHARED console.c SPI_console.c)
  target_include_directories(Console PUBLIC .)
  target_link_libraries(Console PUBLIC GenericI2C GenericSPI)
elseif(TARGET_PLATFORM STREQUAL "AVR")
  add_avr_library(Console console.c)
  avr_target_include_directories(Console PUBLIC .)
  avr_target_link_libraries(Console GenericI2C)
elseif(TARGET_PLATFORM STREQUAL "STM32")
  add_library(Console SHARED console.c)
  target_include_directories(Console PUBLIC .)
  target_link_libraries(Console PUBLIC GenericI2C)
else()
  message(FATAL_ERROR "Invalid TARGET_PLATFORM: ${TARGET_PLATFORM}")
endif()
