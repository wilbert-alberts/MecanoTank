cmake_minimum_required(VERSION 3.13)

# Set these environment variables accordingly!
#set(FREERTOS_KERNEL_PATH /home/ben/Projects/pico-freertos/FreeRTOS-SMP-Demos/FreeRTOS/Source)
set(FREERTOS_KERNEL_PATH /home/wilbert/diskstation/Project/Pico/FreeRTOS-SMP-Demos/FreeRTOS/Source)
# set(PICO_SDK_PATH )

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

# Pull in FreeRTOS
include(FreeRTOS_Kernel_import.cmake)

project(MecanumTank C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

#add_compile_options(-v)

add_subdirectory(ruckig)

add_executable(mecanumtank

        main.cpp
        ErrorHandling.cpp

        BL.cpp
        BL_ABDecoder.cpp
        BL_Composite.cpp
        BL_Differentiator.cpp
        BL_ErrorDifference.cpp
        BL_Leaf.cpp
        BL_MotorInterface.cpp
        BL_PID.cpp
        BL_SignalGenerator.cpp
        BL_Sum.cpp
        BL_Analog.cpp

        PeriodicTask.cpp
        ServoGroupExecutor.cpp

        SG.cpp
        SG_Debug.cpp

        T.cpp
        T_Composite.cpp
        T_Factory.cpp
        T_ID.cpp
      )

target_compile_definitions(mecanumtank PRIVATE
        )

target_include_directories(mecanumtank PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/../../Common/include
      )

target_link_libraries(mecanumtank ruckig pico_stdlib hardware_adc hardware_pwm hardware_gpio FreeRTOS-Kernel FreeRTOS-Kernel-Heap1)

pico_add_extra_outputs(mecanumtank)

pico_enable_stdio_usb(mecanumtank 1)
pico_enable_stdio_uart(mecanumtank 0)
