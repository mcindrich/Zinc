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
  zinc_vm
  
  "src/vm/Instruction.cpp"
)

add_library(
  zinc_lang

  # basic files
  "src/lang/Utils.cpp"
  "src/lang/Compiler.cpp"
  "src/lang/Parser.cpp"
  "src/lang/Tokenizer.cpp"
  "src/lang/Token.cpp"

  # pattern files

  "src/lang/pattern/Pattern.cpp"
  "src/lang/pattern/ExpressionPattern.cpp"
  "src/lang/pattern/FunctionCallPattern.cpp"
  "src/lang/pattern/TokenPattern.cpp"
  "src/lang/pattern/PatternList.cpp"

  # AST files
  "src/lang/ast/AST.cpp"
  "src/lang/ast/OperatorAST.cpp"
  "src/lang/ast/OperandAST.cpp"
)

add_executable(
  zinc
  "src/main.cpp"
  "src/Program.cpp"
)

target_link_libraries(zinc zinc_vm zinc_lang)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
