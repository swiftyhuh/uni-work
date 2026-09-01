  cmake_minimum_required(VERSION 3.16)

  project(Lecture9DemoWidgets)

  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)

  find_package(Qt5 REQUIRED COMPONENTS Widgets)

  add_executable(Lecture9DemoWidgets
      main.cpp
  )

  target_link_libraries(Lecture9DemoWidgets PRIVATE Qt5::Widgets)
