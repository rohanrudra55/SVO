cmake_minimum_required(VERSION 2.8.12)
project(Stereo )
find_package( OpenCV REQUIRED )
include_directories((include))
set(CMAKE_INCLUDE_CURRENT_DIR ON)
file(GLOB SOURCES "src/*.cpp")
add_executable(output  ${SOURCES} )
target_link_libraries( output ${OpenCV_LIBS})
message(
    "
                                             @@@        @   @@@                                 
                                              @@@      @@@ @@@                                  
                                               (@@    @@@@@@@                                   
                                                 @@  @@@ @@@                                    
                                                  @@@@@ @@@@@                                   
                                                   @@@ @@@ @@@                                  
                                                  @@@@@@@   @@@                                 
                                                 @@@ @@%     *@@                                


                                     @@@  @ @   @  @ @@@    @        %@    @                    
                                      @   &  @ @   @ @ @   @ @      @& @   @                    
                                      @   &   @    @   @  @   @    @,   @  @                    

                                                  TiVRA AI     
    "
)
