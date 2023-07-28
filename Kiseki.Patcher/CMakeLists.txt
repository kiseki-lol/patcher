list(APPEND SOURCE
    Source/main.cpp
    Source/Patcher.cpp
    Source/Helpers.cpp

    # Hooks
    Source/Hooks/Crypt.cpp
    Source/Hooks/Http.cpp
)

list(APPEND HEADER
    Header/Patcher.hpp
    Header/Helpers.hpp

    # Hooks
    Header/Hooks/Crypt.hpp
    Header/Hooks/Http.hpp

    # Win32 resources
    Resource/Information.h
    Resource/Script.rc
)

if(COMPILE_PLAYER OR COMPILE_SERVER)
    # Hook CRoblox
    list(APPEND SOURCE Source/Hooks/CRoblox.cpp)
    list(APPEND HEADER Header/Hooks/CRoblox.hpp)

    if(COMPILE_PLAYER)
        # Discord Rich Presence integration
        list(APPEND SOURCE Source/Discord.cpp)
        list(APPEND HEADER Header/Discord.hpp)
    endif()

    if(COMPILE_SERVER)
        # Hook DataModel, ServerReplicator, and StandardOut as well as include our custom server interface
        list(APPEND SOURCE
            Source/Server.cpp

            Source/Hooks/DataModel.cpp
            Source/Hooks/ServerReplicator.cpp
            Source/Hooks/StandardOut.cpp
        )

        list(APPEND HEADER
            Header/Server.hpp

            Header/Hooks/DataModel.hpp
            Header/Hooks/ServerReplicator.hpp
            Header/Hooks/StandardOut.hpp
        )
    endif()
endif()

add_library(Kiseki.Patcher SHARED ${SOURCE} ${HEADER})

# Packages
find_package(CURL CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(pugixml CONFIG REQUIRED)
find_package(RapidJSON CONFIG REQUIRED)

find_path(DETOURS_INCLUDE_DIRS "detours/detours.h")
find_library(DETOURS_LIBRARY detours REQUIRED)

target_include_directories(Kiseki.Patcher PRIVATE Header ${DETOURS_INCLUDE_DIRS})
target_link_libraries(Kiseki.Patcher PRIVATE CURL::libcurl ${DETOURS_LIBRARY} OpenSSL::SSL OpenSSL::Crypto pugixml::static pugixml::pugixml rapidjson)

# Target-specific linking and compile options
if(COMPILE_PLAYER)
    find_path(DISCORD_RPC_INCLUDE_DIRS "discord_rpc.h")
    find_library(DISCORD_RPC_LIBRARY discord-rpc REQUIRED)

    target_include_directories(Kiseki.Patcher PRIVATE ${DISCORD_RPC_INCLUDE_DIRS})
    target_link_libraries(Kiseki.Patcher PRIVATE ${DISCORD_RPC_LIBRARY})
    target_compile_definitions(Kiseki.Patcher PRIVATE PLAYER)
endif()

if(COMPILE_SERVER)
    target_compile_definitions(Kiseki.Patcher PRIVATE SERVER)
endif()