
  cmake_minimum_required(VERSION 3.16)
  project(bill)

  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)

  set(CMAKE_AUTOMOC ON)
  set(CMAKE_AUTOUIC ON)
  set(CMAKE_AUTORCC ON)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

  find_package(Qt6 REQUIRED COMPONENTS Widgets)

  add_executable(bill
      main.cpp
      gui.cpp
      gui.h
      gui.ui
      bill.cpp
      bill.h
      Repository.cpp
      Repository.h
      Service.cpp
      Service.h
  )

  target_link_libraries(bill PRIVATE Qt6::Widgets)
