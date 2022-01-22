# PolygonDLLUtilities
Manages DLLs for extending game client/server functionality 

Based off [ndoesstuff/JoinScriptUrlImpl](https://github.com/ndoesstuff/JoinScriptUrlImpl) as per the MIT license

Test command line parameter reimplementation (2010/2011 only):  
> RobloxApp.exe -a http://polygondev.pizzaboxer.xyz/login/negotiate.ashx -t 0 -j http://polygondev.pizzaboxer.xyz/game/visit.ashx

Test trust check:  
> Insert a new brick with decal  
> Try setting decal ID to http://tadah.rocks - Should succeed  
> Try setting decal ID to http://tadah.rocks@example.com - Should fail  

Test signature check:  
> Run loadfile("rbxasset://signatureinvalid.txt")() - Should throw an exception  
> Run loadfile("rbxasset://signatureoverflow.txt")() - Should throw an exception  

Test output and jobId (Arbiter builds only):  
> RobloxApp.exe -jobId ExampleJobId - Should open an output console  
> Run print(game.jobId) - Should print "ExampleJobId" in the console  