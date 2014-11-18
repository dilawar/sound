#!/usr/bin/env bash
aiffs=`find . -type f -name '*.aif'`
for aiff in $aiffs; do
    echo "Converting $aiff to wav file"
    ffmpeg -i "$aiff" "${aiff%.aif}.wav"
done

