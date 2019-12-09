#pragma once

#ifdef _WIN64
	#pragma comment(lib,"..\\external\\glfw-3.3\\libs\\x64\\glfw3.lib")
#else
	#pragma comment(lib,"..\\external\\glfw-3.3\\libs\\x86\\glfw3.lib")
#endif // WIN64

#ifdef _WIN64
	#pragma comment(lib,"..\\external\\glew-2.1.0\\lib\\Release\\x64\\glew32.lib")
#else
	#pragma comment(lib,"..\\external\\glew-2.1.0\\lib\\Release\\Win32\\glew32.lib")
#endif // WIN64

#ifdef _WIN64
	#pragma comment(lib,"..\\external\\Assimp\\libs\\x64\\assimp-vc140-mt.lib")
#else
	#pragma comment(lib,"..\\external\\Assimp\\libs\\x86\\assimp-vc140-mt.lib")
#endif // WIN64

#ifdef _WIN64
	#pragma comment(lib,"..\\external\\PhysX-4.1\\libs\\x64\\PhysX_64.lib")
	#pragma comment(lib,"..\\external\\PhysX-4.1\\libs\\x64\\PhysXCommon_64.lib")
	#pragma comment(lib,"..\\external\\PhysX-4.1\\libs\\x64\\PhysXCooking_64.lib")
	#pragma comment(lib,"..\\external\\PhysX-4.1\\libs\\x64\\PhysXExtensions_static_64.lib")
	#pragma comment(lib,"..\\external\\PhysX-4.1\\libs\\x64\\PhysXFoundation_64.lib")

	#pragma comment(lib,"..\\external\\SOIL\\lib\\x64\\SOIL.lib")
#endif // _WIN64


#pragma comment(lib,"opengl32.lib")

#pragma comment(lib,"glu32.lib")

#pragma comment(lib,"assimp-vc140-mt.lib")