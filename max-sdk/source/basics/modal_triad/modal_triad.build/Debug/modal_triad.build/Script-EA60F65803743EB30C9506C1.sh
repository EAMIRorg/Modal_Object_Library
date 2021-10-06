#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd "/Users/music/Documents/Max 8/Packages/max-sdk/source/basics/modal_triad"
  cp /Users/music/Documents/Max\ 8/Packages/max-sdk/source/max-sdk-base/script/PkgInfo /Users/music/Documents/Max\ 8/Packages/max-sdk/source/basics/modal_triad/../../../externals/modal_triad.mxo/Contents/PkgInfo
fi
if test "$CONFIGURATION" = "Release"; then :
  cd "/Users/music/Documents/Max 8/Packages/max-sdk/source/basics/modal_triad"
  cp /Users/music/Documents/Max\ 8/Packages/max-sdk/source/max-sdk-base/script/PkgInfo /Users/music/Documents/Max\ 8/Packages/max-sdk/source/basics/modal_triad/../../../externals/modal_triad.mxo/Contents/PkgInfo
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd "/Users/music/Documents/Max 8/Packages/max-sdk/source/basics/modal_triad"
  cp /Users/music/Documents/Max\ 8/Packages/max-sdk/source/max-sdk-base/script/PkgInfo /Users/music/Documents/Max\ 8/Packages/max-sdk/source/basics/modal_triad/../../../externals/modal_triad.mxo/Contents/PkgInfo
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd "/Users/music/Documents/Max 8/Packages/max-sdk/source/basics/modal_triad"
  cp /Users/music/Documents/Max\ 8/Packages/max-sdk/source/max-sdk-base/script/PkgInfo /Users/music/Documents/Max\ 8/Packages/max-sdk/source/basics/modal_triad/../../../externals/modal_triad.mxo/Contents/PkgInfo
fi

