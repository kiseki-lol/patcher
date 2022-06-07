# PolygonDLL
DLL used for extending game client/server functionality 

Based off [ndoesstuff/JoinScriptUrlImpl](https://github.com/ndoesstuff/JoinScriptUrlImpl) as per the MIT license

Test trust check:  
1. Insert a new brick with decal  
2. Try setting decal ID to http://tadah.rocks - Should succeed  
3. Try setting decal ID to http://tadah.rocks@example.com - Should fail  

Test extended signature check:  
- Run `loadfile("rbxasset://signatureinvalid.txt")()` - Should throw an exception  
- Run `loadfile("rbxasset://signatureoverflow.txt")()` - Should throw an exception  
- Run `loadfile("https://tadah.rocks/test/sha256succ")()` - Should succeed (if compiled with the Tadah public key)
- Run `loadfile("https://polygon.pizzaboxer.xyz/Game/Visit.ashx")()` - Should succeed (if compiled with the Project Polygon public key)

Test command line parameter reimplementation (2010/2011 builds only):  
- `> RobloxApp.exe -a http://polygondev.pizzaboxer.xyz/login/negotiate.ashx -t 0 -j http://polygondev.pizzaboxer.xyz/game/visit.ashx`

Test DataModel creation (Arbiter builds only):  
- Run `print("NewGame")` - Should create a new DataModel with an executed script  

Test asset redirection:
- Run `game:Load("https://www.roblox.com/Asset?id=1818&version=1")` - Should succeed
1. Insert a new brick with decal  
2. Try setting decal ID to `https://www.roblox.com/Thumbs/Asset.ashx?id=1818&x=768&y=432` - Should succeed  
3. Try setting decal ID to `https://www.roblox.com/Thumbs/Avatar.ashx?id=1&x=768&y=432` - Should succeed  

## Build
PolygonDLL requires [vcpkg](https://github.com/microsoft/vcpkg) to manage package installation such with libcurl, detours, and rapidjson. Here's a quick way to install vcpkg;

```
> cd <path where vcpkg should be kept; such as C:\vcpkg>
> git clone https://github.com/microsoft/vcpkg
> .\vcpkg\bootstrap-vcpkg.bat
> .\vcpkg\vcpkg integrate install
> .\vcpkg\vcpkg integrate project
```

PolygonDLL only builds under Win32 for x86 architecture.

## Usage
The DLL is imported with StudPE under the `import` function name. Otherwise, the DLL should be imported into the executable via VMProtect.

Several preprocessor flags are available that modify how the DLL operates. They are specific to the executable being compiled for.
- `ARBITERBUILD`
- `MFC2010`
- `MFC2011`
- `PLAYER2012`
- `STUDIO2012`

You may read the code for further information.

## License
Copyright (c) Project Polygon and Tadah 2022. All rights reserved. Not for public use.
