#!/bin/bash
#
# This script converts images for displaying with TFT_eSPI
#
# Deps: ffmpeg and xxd
#
# Usage: ./convert-image.sh inputfile.png [arrayname] [size]
# inputfile.png    required, needs to be .png format
# arrayname        optional, default: image the name of the char_array
# size             optional, default: none. Resize image if specified, in format WxH or W:H
#
# Example usage:
# ./convert-image spycher.png spycher 128x128 > spycher.h
#
# Afer that, you can use the struct like this:
# #include "spycher.h"
# tft.pushImage(0, 0, 128, 128, (uint16_t *)spycher);
#

if [ -z $1 ]; then
  echo "Usage: $0 input.png [structname] [size]"
fi

if [ -z $2 ]; then
  CNAME="image"
else
  CNAME="$2"
fi

if [ -z $3 ]; then
  SIZE=""
else
  SC=$(echo $3 | sed 's/x/:/g')
  SIZE="-vf scale=${SC}"
fi


ffmpeg -hide_banner -loglevel error -vcodec png -i $1 -vcodec rawvideo -f rawvideo -pix_fmt rgb565 $SIZE - | xxd --include -n ${CNAME} 