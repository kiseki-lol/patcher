find_package(curl CONFIG REQUIRED)
find_package(detours CONFIG REQUIRED)
find_package(discord-rpc CONFIG REQUIRED)
find_package(openssl CONFIG REQUIRED)
find_package(pugixml CONFIG REQUIRED)
find_package(rapidjson CONFIG REQUIRED)

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

add_library(Kiseki.Patcher ${SOURCE} ${HEADER})

target_include_directories(Kiseki.Patcher PRIVATE Header)
target_link_libraries(Kiseki.Patcher PRIVATE)

if(COMPILE_PLAYER)
    target_compile_definitions(Kiseki.Patcher PRIVATE PLAYER)
endif()

if(COMPILE_SERVER)
    target_compile_definitions(Kiseki.Patcher PRIVATE SERVER)
endif()