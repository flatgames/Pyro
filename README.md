### What is this repository for? ###

This is a library for cocos2d-x 3.x applications. It provides UI elements in Material Design, such as *Paper*, *InkButton*, *PaperDialog*, etc. In additional, it has a set of animation utilities to simplify the use of cocos2d-x actions, such as *SequenceBuilder*, *AnimationUtils*, etc.

### How do I get set up? ###

This library depends on cocos2d-x version 3.0 and over.

* Put the library directory in the same parent directory of *cocos2dx* library, along with *Classes*, *proj.android*, etc.
* Copy all files in library Resources directory to application Resources directory. These files are used to create UI elements.
* In `AppDelegate.cpp`, include the following file:
```
#!c++
#include <Pyro/Common.h>
```
* In `AppDelegate::applicationDidFinishLaunching`, put the following line before creating the scene:
```
#!c++
Pyro::Common::initResources();
```