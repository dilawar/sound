#!/usr/bin/env bash
aiffs=`find . -type f -name '*.aif'`
FFMPEG=`which ffmpeg`
if [[ ! $FFMPEG ]]; then
    echo "ffmpeg not found. May avconv is available"
    FFMPEG=avconv
fi
for aiff in $aiffs; do
    echo "Converting $aiff to wav file"
    $FFMPEG -i "$aiff" "${aiff%.aif}.wav"
done

