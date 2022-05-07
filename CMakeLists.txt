 
set(MCP23017_SOURCES MCP23017.cpp) 
add_library(MCP23017.cpp STATIC ${MCP23017_SOURCES})
target_link_libraries( mbed_MCP23017 mbed-os)

set(MCP23017_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
target_include_directories(mbed_MCP23017 PUBLIC ${MCP23017_HEADER_DIR})