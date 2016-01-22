
//#ifndef _FACE_BASE_H_
//#define _FACE_BASE_H_

// include files

// os include files
#include <windows.h>
#include <windowsx.h>
#include <stddef.h>
#include <tchar.h>
#include <memory.h>
#include <intrin.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <sstream>
#include <Shlwapi.h>
#include <list>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <memory>
#include <mutex>
#include <utility>    
#include <regex>       
#include <tuple>       
#include <type_traits> 
#include <cstddef>  


// face include files
#include "match.hpp"

#include "utils/Define.h"
#include "utils/Object.h"
#include "utils/Utils.h"

#include "base/Type.h"
#include "base/Template.h"

#include "base/Pointer.h"
#include "base/Function.h"
#include "base/Event.h"
#include "base/Lazy.h"
#include "base/Singleton.h"

#include "utils/Strings.h"
#include "utils/FileSystem.h"
#include "utils/Lock.h"

#include "app/Application.h"

#include "uibase/FontObject.h"
#include "uibase/FontsManager.h"

#include "uibase/WindowObject.h"
#include "uibase/WindowsManager.h"

#include "core/Window.h"
#include "core/WindowImpl.h"
#include "core/MessgaeListener.h"
//#endif