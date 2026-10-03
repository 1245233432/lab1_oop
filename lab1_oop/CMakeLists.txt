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

# при сборке из CMake (в т.ч. из Visual Studio "Открыть папку") рабочая папка
# программы - это папка сборки (out/build/...), а не папка с исходниками, где
# лежат plot.py и plot_empiric.py; копируем их рядом с .exe после каждой
# сборки, чтобы построение графиков работало без ручного копирования файлов
add_custom_command(TARGET lab1_oop POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${CMAKE_CURRENT_SOURCE_DIR}/plot.py"
		"${CMAKE_CURRENT_SOURCE_DIR}/plot_empiric.py"
		"$<TARGET_FILE_DIR:lab1_oop>"
)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
