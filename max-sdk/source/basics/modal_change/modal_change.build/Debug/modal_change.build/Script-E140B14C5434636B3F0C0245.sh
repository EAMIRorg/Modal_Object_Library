#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd "/Users/music/Documents/Max 8/Packages/max-sdk/source/basics/modal_change"
  cp /Users/music/Documents/Max\ 8/Packages/max-sdk/source/max-sdk-base/script/PkgInfo /Users/music/Documents/Max\ 8/Packages/max-sdk/source/basics/modal_change/../../../externals/modal_change.mxo/Contents/PkgInfo
fi
if test "$CONFIGURATION" = "Release"; then :
  cd "/Users/music/Documents/Max 8/Packages/max-sdk/source/basics/modal_change"
  cp /Users/music/Documents/Max\ 8/Packages/max-sdk/source/max-sdk-base/script/PkgInfo /Users/music/Documents/Max\ 8/Packages/max-sdk/source/basics/modal_change/../../../externals/modal_change.mxo/Contents/PkgInfo
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd "/Users/music/Documents/Max 8/Packages/max-sdk/source/basics/modal_change"
  cp /Users/music/Documents/Max\ 8/Packages/max-sdk/source/max-sdk-base/script/PkgInfo /Users/music/Documents/Max\ 8/Packages/max-sdk/source/basics/modal_change/../../../externals/modal_change.mxo/Contents/PkgInfo
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd "/Users/music/Documents/Max 8/Packages/max-sdk/source/basics/modal_change"
  cp /Users/music/Documents/Max\ 8/Packages/max-sdk/source/max-sdk-base/script/PkgInfo /Users/music/Documents/Max\ 8/Packages/max-sdk/source/basics/modal_change/../../../externals/modal_change.mxo/Contents/PkgInfo
fi

