# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html
cmake_minimum_required(VERSION 3.4.1)

add_library(native-lib SHARED src/main/cpp/native-lib.cpp )

find_library(log-lib log )

SET(STASM_BASE_DIR "src/main/cpp")

SET(OBJ_STASM
${STASM_BASE_DIR}/stasm/asm.cpp
${STASM_BASE_DIR}/stasm/classicdesc.cpp
${STASM_BASE_DIR}/stasm/convshape.cpp
${STASM_BASE_DIR}/stasm/err.cpp
${STASM_BASE_DIR}/stasm/eyedet.cpp
${STASM_BASE_DIR}/stasm/eyedist.cpp
${STASM_BASE_DIR}/stasm/faceroi.cpp
${STASM_BASE_DIR}/stasm/hat.cpp
${STASM_BASE_DIR}/stasm/hatdesc.cpp
${STASM_BASE_DIR}/stasm/landmarks.cpp
${STASM_BASE_DIR}/stasm/misc.cpp
${STASM_BASE_DIR}/stasm/pinstart.cpp
${STASM_BASE_DIR}/stasm/print.cpp
${STASM_BASE_DIR}/stasm/shape17.cpp
${STASM_BASE_DIR}/stasm/shapehacks.cpp
${STASM_BASE_DIR}/stasm/shapemod.cpp
${STASM_BASE_DIR}/stasm/startshape.cpp
${STASM_BASE_DIR}/stasm/stasm.cpp
${STASM_BASE_DIR}/stasm/stasm_lib.cpp
)

SET(OBJ_MOD1
${STASM_BASE_DIR}/stasm/MOD_1/facedet.cpp
${STASM_BASE_DIR}/stasm/MOD_1/initasm.cpp
)

add_library(opencv SHARED IMPORTED)
include_directories(src/main/cpp src/main/cpp/opencv src/main/cpp/opencv2 src/main/cpp/stasm)
set_target_properties(opencv PROPERTIES IMPORTED_LOCATION  ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libopencv_java3.so)

add_library(stasm SHARED ${OBJ_MOD1} ${OBJ_STASM})
target_link_libraries(stasm opencv)

target_link_libraries(native-lib stasm opencv ${log-lib})
