/*
 * ofxMidiConstants.h
 *
 *  Created on: 29-may-2009
 *      Author: art
 */

#ifndef OFXMIDICONSTANTS_H_
#define OFXMIDICONSTANTS_H_

#include "ofConstants.h"

#ifdef TARGET_LINUX
	#define __LINUX_ALSASEQ__
#elif defined(TARGET_WIN32)
	#define __WINDOWS_MM__
#elif defined(TARGET_MACOSX)
	#define __MACOSX_CORE__
#endif

#endif /* OFXMIDICONSTANTS_H_ */
