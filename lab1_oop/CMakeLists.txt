# CMakeList.txt: проект CMake для lab1_oop; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (lab1_oop
"lab1_oop.cpp"
#"lab1_oop.h"
"distribution.cpp"
"mix_distribution.cpp"
"empiric_distribution.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET lab1_oop PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
