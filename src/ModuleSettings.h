/**********************************************************************

  ReeeKorder: A Digital Audio Editor

  @file ModuleSettings.h

  Paul Licameli split from ModulePrefs.h

**********************************************************************/

#ifndef __AUDACITY_MODULE_SETTINGS__
#define __AUDACITY_MODULE_SETTINGS__

#include "Identifier.h"

enum {
   kModuleDisabled = 0,
   kModuleEnabled = 1,
   kModuleAsk = 2,     // Will ask, each time, when audacity starts.
   kModuleFailed = 3,  // ReeeKorder thinks this is a bad module.
   kModuleNew = 4      // ReeeKorder will ask once, and remember the answer.
};

namespace ModuleSettings {

int GetModuleStatus( const FilePath &fname );
void SetModuleStatus( const FilePath &fname, int iStatus );

}

#endif
