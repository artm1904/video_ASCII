cmake_minimum_required(VERSION 3.10)


set(EXE_NAME executable)


add_executable(${EXE_NAME}
    source/main.cpp
)


target_include_directories(${EXE_NAME}
    PRIVATE
    include/
)


# Применяем флаги компиляции, которые мы определили в родительском CMakeLists.txt
target_compile_options(${EXE_NAME} PRIVATE ${PROJECT_COMPILE_OPTIONS})

# Линкуем наш проект с OpenCV. Использование целей с `OpenCV::` - это современный
# подход, который работает как с find_package, так и с add_subdirectory (CPM).
target_link_libraries(${EXE_NAME}
    PRIVATE
    
    OpenCV::core OpenCV::imgproc OpenCV::highgui OpenCV::videoio
)




