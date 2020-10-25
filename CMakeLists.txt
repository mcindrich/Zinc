cmake_minimum_required(VERSION 3.0.0)
project(Zinc VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)

include_directories(
  "include"
  "argparse/include"
)

# for settings and intellisense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(
  ZincVM
  "src/vm/VirtualMachine.cpp"
  "src/vm/CPU.cpp"
  "src/vm/Instruction.cpp"
  "src/vm/Memory.cpp"
  "src/vm/Register.cpp"
)

add_library(
  ZincLang
  "src/lang/Utils.cpp"
  "src/lang/Compiler.cpp"
  "src/lang/Parser.cpp"
  "src/lang/Tokenizer.cpp"
  "src/lang/AST.cpp"
  "src/lang/Token.cpp"
)

add_executable(
  Zinc
  "src/main.cpp"
)

target_link_libraries(Zinc ZincVM ZincLang)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
