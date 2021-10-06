#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd "/Users/music/Documents/Max 8/Packages/max-sdk/source/basics/modal_change"
  make -f /Users/music/Documents/Max\ 8/Packages/max-sdk/source/basics/modal_change/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd "/Users/music/Documents/Max 8/Packages/max-sdk/source/basics/modal_change"
  make -f /Users/music/Documents/Max\ 8/Packages/max-sdk/source/basics/modal_change/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd "/Users/music/Documents/Max 8/Packages/max-sdk/source/basics/modal_change"
  make -f /Users/music/Documents/Max\ 8/Packages/max-sdk/source/basics/modal_change/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd "/Users/music/Documents/Max 8/Packages/max-sdk/source/basics/modal_change"
  make -f /Users/music/Documents/Max\ 8/Packages/max-sdk/source/basics/modal_change/CMakeScripts/ReRunCMake.make
fi

