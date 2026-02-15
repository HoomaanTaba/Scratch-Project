cmake_minimum_required(VERSION 3.26)
project(14041016)

set(CMAKE_CXX_STANDARD 17)

add_executable(14041016 main.cpp
        UI_Objects.h
        CodeTab.h
        CustomTab.h
        SoundTab.h
        File.h
        Edit.h
        Motion.h
        Looks.h
        Sound.h
        Events.h
        Control.h
        Sensing.h
        Operators.h
        Variables.h)

target_link_libraries(${PROJECT_NAME} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer)
