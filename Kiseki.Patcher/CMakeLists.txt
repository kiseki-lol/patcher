list(APPEND SOURCE
    Source/main.cpp
    Source/Patcher.cpp
    Source/Helpers.cpp

    Source/Hooks/Crypt.cpp
    Source/Hooks/Http.cpp
)

list(APPEND HEADER
    Header/Patcher.hpp
    Header/Helpers.hpp

    Header/Hooks/Crypt.hpp
    Header/Hooks/Http.hpp

    Resource/Information.h
    Resource/Script.rc
)

if(COMPILE_PLAYER)
    list(APPEND SOURCE
        Source/Discord.cpp
        Source/Hooks/CRoblox.cpp
    )

    list(APPEND HEADER
        Header/Discord.cpp
        Header/Hooks/CRoblox.hpp
    )
endif()

if(COMPILE_SERVER)
    list(APPEND SOURCE
        Source/Server.cpp

        Source/Hooks/DataModel.cpp
        Source/Hooks/ServerReplicator.cpp
        Source/Hooks/StandardOut.cpp
    )

    list(APPEND HEADER
        Header/Server.cpp

        Header/Hooks/DataModel.cpp
        Header/Hooks/ServerReplicator.cpp
        Header/Hooks/StandardOut.cpp
    )
endif()

add_library(Kiseki.Patcher SHARED ${SOURCE} ${HEADER})

# Packages
find_package(CURL CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(pugixml CONFIG REQUIRED)
find_package(RapidJSON CONFIG REQUIRED)

find_path(DETOURS_INCLUDE_DIRS "detours/detours.h")
find_library(DETOURS_LIBRARY detours REQUIRED)

find_path(DISCORD_RPC_INCLUDE_DIRS "discord_rpc.h")
find_library(DISCORD_RPC_LIBRARY discord-rpc REQUIRED)

target_include_directories(Kiseki.Patcher PRIVATE Header ${DETOURS_INCLUDE_DIRS})
target_link_libraries(Kiseki.Patcher PRIVATE CURL::libcurl ${DETOURS_LIBRARY} OpenSSL::SSL OpenSSL::Crypto pugixml::static pugixml::pugixml rapidjson)

if(COMPILE_PLAYER)
    target_include_directories(Kiseki.Patcher PRIVATE ${DISCORD_RPC_INCLUDE_DIRS})
    target_link_libraries(Kiseki.Patcher PRIVATE ${DISCORD_RPC_LIBRARY})
    target_compile_definitions(Kiseki.Patcher PRIVATE PLAYER)
endif()

if(COMPILE_SERVER)
    target_compile_definitions(Kiseki.Patcher PRIVATE SERVER)
endif()