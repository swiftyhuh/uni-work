
    cmake_minimum_required(VERSION 3.16)
    project(assignment8)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTORCC ON)

    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    find_package(Qt6 REQUIRED COMPONENTS Widgets)
    add_executable(invatqt_app
           main.cpp
           gui.cpp
           gui.h
           Repository.cpp
           Repository.h
           Services.cpp
           Services.h
           Tutorial.cpp
           Tutorial.h
           TutorialValidator.cpp
           TutorialValidator.h
           WatchList.cpp
           WatchList.h
           Exceptions.h
           gui.ui # Your UI file
       )
    target_link_libraries(invatqt_app PRIVATE Qt6::Widgets)
