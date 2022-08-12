# Tadah.DLL
DLL used for extending game client/server functionality 

Fork of [ProjectPolygon/PolygonDLL](https://github.com/ProjectPolygon/PolygonDLL), which is based off of [ndoesstuff/JoinScriptUrlImpl](https://github.com/ndoesstuff/JoinScriptUrlImpl) as per the MIT license

## CI/CD
Tadah.DLL is available on the Tadah CI. All builds are compiled as release, and a build occurs per push.

- [player-win-x86](https://ci.tadah.sipr/buildConfiguration/Tadah_DLL_PlayerWinX86)
- [studio-win-x86](https://ci.tadah.sipr/buildConfiguration/Tadah_DLL_StudioWinX86)
- [server-win-x86](https://ci.tadah.sipr/buildConfiguration/Tadah_DLL_ServerWinX86)

## Build
Tadah.DLL requires [vcpkg](https://github.com/microsoft/vcpkg) to manage package installation such with libcurl, detours, and rapidjson. Here's a quick way to install vcpkg;

```
> cd <path where vcpkg should be kept; such as C:\vcpkg>
> git clone https://github.com/microsoft/vcpkg
> .\vcpkg\bootstrap-vcpkg.bat
> .\vcpkg\vcpkg integrate install
> .\vcpkg\vcpkg integrate project
```

Tadah.DLL only builds under Win32 for x86 architecture.

## Usage
The DLL is imported with StudPE under the `import` function name for server builds. Otherwise, the DLL should be imported into the executable via VMProtect.

Several preprocessor flags are available that modify how the DLL operates. They are specific to the executable being compiled for. You may read the code for further information.

## Testing
Test trust check:  
1. Insert a new brick with decal  
2. Try setting decal ID to `http://tadah.rocks` - Should succeed  
3. Try setting decal ID to `http://tadah.rocks@example.com` - Should fail  

Test extended signature check:  
- Run `loadfile("rbxasset://invalid-signature.txt")()` - Should throw an exception  
- Run `loadfile("rbxasset://overflow-signature.txt")()` - Should throw an exception  
- Run `loadfile("https://polygon.pizzaboxer.xyz/Game/Visit.ashx")()` - Should succeed (if compiled with the Project Polygon public key)

Test command line parameter reimplementation:  
- `> RobloxApp.exe -a http://polygondev.pizzaboxer.xyz/Login/Negotiate.ashx -t 0 -j http://polygondev.pizzaboxer.xyz/Game/Visit.ashx`

Test asset redirection:
- Run `game:Load("https://www.roblox.com/Asset?id=1818&version=1")` - Should succeed
1. Insert a new brick with decal  
2. Try setting decal ID to `https://www.roblox.com/Thumbs/Asset.ashx?id=1818&x=768&y=432` - Should succeed  
3. Try setting decal ID to `https://www.roblox.com/Thumbs/Avatar.ashx?id=1&x=768&y=432` - Should succeed  

## License
Copyright (c) Tadah and Project Polygon 2022. All rights reserved. Not for public use.
