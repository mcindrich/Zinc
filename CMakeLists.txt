cmake_minimum_required(VERSION 3.0.0)
project(Zinc VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)

include_directories(
  "src"
  "deps/argparse/include"
)

# for settings and intellisense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(
  zinc_lang

  # basic files
  "src/Utils.cpp"
  "src/Compiler.cpp"
  "src/Parser.cpp"
  "src/Tokenizer.cpp"
  "src/Token.cpp"

  # pattern files

  "src/pattern/Pattern.cpp"
  "src/pattern/ExpressionPattern.cpp"
  "src/pattern/FunctionCallPattern.cpp"
  "src/pattern/TokenPattern.cpp"
  "src/pattern/PatternList.cpp"

  # AST files
  "src/ast/AST.cpp"
  "src/ast/OperatorAST.cpp"
  "src/ast/OperandAST.cpp"
)

add_executable(
  zinc
  "app/zinc.cpp"
  "src/Program.cpp"
)

target_link_libraries(zinc zinc_lang)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
