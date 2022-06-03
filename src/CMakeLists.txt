FILE(GLOB_RECURSE SOURCES "*.cpp")
FILE(GLOB_RECURSE HEADERS "*.h")

IF(CMAKE_GENERATOR MATCHES "Xcode")
  add_executable(SimpleSemanticAnalyzer ${SOURCES} ${HEADERS})
ELSE()
  add_executable(SimpleSemanticAnalyzer ${SOURCES})
ENDIF()

target_link_libraries(SimpleSemanticAnalyzer PRIVATE ${llvm_libs})
