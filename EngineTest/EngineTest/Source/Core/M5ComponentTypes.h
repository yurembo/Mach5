/******************************************************************************/ 
/*! 
\file   M5ComponentTypes.h 
\author UserPreBuild.bat 
\par    email: lazersquad\@gmail.com 
\par    Mach5 Game Engine 
 
This file gets auto generated based on the names of the Components in the 
current project.  UserPreBuild.bat looks for files of the type *Component.h 
and creates an enumeration value of CT_*Component. 
*/ 
/******************************************************************************/ 
#ifndef M5COMPONENT_TYPE_H 
#define M5COMPONENT_TYPE_H 
#include <string> 
 
 
enum M5ComponentTypes {  
CT_GfxComponent, 
CT_PlayerInputComponent, 
CT_INVALID 
}; 
 
 
inline M5ComponentTypes StringToComponent(const std::string& string) { 
if(string == "GfxComponent") return CT_GfxComponent; 
if(string == "PlayerInputComponent") return CT_PlayerInputComponent; 
return CT_INVALID; 
} 
#endif //M5COMPONENT_TYPE_H 
