#!/bin/bash
# Process the original assets, performing:
# 1. Mapping the same folder structure for all the target resolutions.
# 2. Resizes the images to the target resolutions on the game assets folder.
# 3. Create pvr versions within one folder in two modes.
#   a. One pvr per png
#   b. A batched pvr and a descriptive plist file if a "batch" file was present in the folder.
# 4. Creates a "design" folder containing the same output just keeping the images on png and
#    using the design resolution.

BASE_ASSETS_PATH=/home/waldemar/Projects/cal/assets
GAME_ASSETS_PATH=/home/waldemar/Projects/Calaveras/Resources

PVRTEXTOOL=/opt/Imagination/PowerVR/GraphicsSDK/PVRTexTool/CLI/Linux_x86_64/PVRTexToolCLI

SOURCE_BASE_HEIGHT=1800
SOURCE_BASE_WIDTH=3200

#TARGET_HEIGHTS="320 640 800 1080 1200 1600"
TARGET_HEIGHTS="320 640 800 1080"

FOLDER_HEIGHT[320]='small'
FOLDER_HEIGHT[640]='medium'
FOLDER_HEIGHT[800]='large'
FOLDER_HEIGHT[1080]='design'
#FOLDER_HEIGHT[1200]='fullhd'
#FOLDER_HEIGHT[1600]='xfullhd'

# Resizes all images in dir.
# $1 Folder full path.
# $2 Target height.
# $3 Percentage for image resizing.
# $4 Original Base folder full path.
# $5 Control for recursive function, adds 1 for within calls.
process_dir() {
    echo "enter process_dir $1 $2 $3 $4 $5"
    base_folder=$4
    base_folder_filename=$(basename "$base_folder")
    dest_base_path=$GAME_ASSETS_PATH/${FOLDER_HEIGHT[$2]}/$base_folder_filename
    if [ ! -d $dest_base_path ]; then
        echo "Creating folder $dest_base_path"
        mkdir -p $dest_base_path
    fi
    if [ -z "$5" ]; then
        dest_path=$dest_base_path
    else
        empty_string='';
        dest_path="${1/$base_folder/$empty_string}"
        dest_path=$dest_base_path$dest_path
    fi
    if [ ! -d $dest_path ]; then
        mkdir -p $dest_path
    fi
    folder=$1
    target_height=$2
    reduction_ratio=$3
    png_only=0
    batch=0
    if [ -f $folder/batch ]; then
      png_only=1
      batch=1
    fi
    if [ "${FOLDER_HEIGHT[$2]}" == "design" ]; then
      png_only=1
    fi
    for file in $folder/*; do
        if [ -f $file ]; then
            filename=$(basename "$file")
            extension="${filename##*.}"
            filename="${filename%.*}"
            if [ "$extension" == "png" ]; then
                process_image $file $dest_path/$filename.$extension $3 $png_only
            fi
        fi
    done
    if [ $batch == 1 ]; then
      batch_filename=$(basename $dest_path)
      #convert $dest_path/frame* -append $dest_path/$batch_filename.png
      if [ "${FOLDER_HEIGHT[$2]}" == "design" ]; then
        rm $dest_path/$batch_filename.png
        TexturePacker --sheet $dest_path/$batch_filename.png --texture-format png --format cocos2d --opt RGBA4444 --dither-fs-alpha $dest_path/*.png
      else
        rm $dest_path/$batch_filename.pvr
        TexturePacker --sheet $dest_path/$batch_filename.pvr --texture-format pvr2 --format cocos2d --opt RGBA4444 --dither-fs-alpha $dest_path/*.png
        rm $dest_path/*.png
      fi
      mv out.plist $dest_path/$batch_filename.plist
      #sed -i 's/\.png//g' $dest_path/$batch_filename.plist
    fi
    for file in $folder/*; do
        if [ -d $file ]; then
            process_dir $file $target_height $reduction_ratio $base_folder 1
        fi
    done
}

# Resizes an image.
# $1 Source full path to the image.
# $2 Destination full path to the image.
# $3 Percentage for reduction.
# $4 Format: 0 PVR, 1 PNG
process_image() {
    src_file=$1
    dst_file=$2
    resize_pct=$3
    pngOnly=$4
    echo "Processing image: $src_file"
    echo "saving to: $dst_file"
    convert -resize $resize_pct% $src_file $dst_file
    if [ $pngOnly == 0 ]; then
      $PVRTEXTOOL -i $dst_file -dither -f r4g4b4a4
      rm $dst_file
    fi
}

for target_height in $TARGET_HEIGHTS; do
    reduction_ratio=`expr $target_height \* 100 / $SOURCE_BASE_HEIGHT `
    echo "Processing images for target $target_height with a reduction to $reduction_ratio%";
    for _file in $BASE_ASSETS_PATH/*; do
        echo "Processing $_file"
        if [ -d $_file ]; then
            process_dir $_file $target_height $reduction_ratio $_file
        fi 
        if [ -f $_file ]; then
          filename=$(basename "$_file")
          extension="${filename##*.}"
          filename="${filename%.*}"
          if [ "$extension" == "png" ]; then
            dest_file=$GAME_ASSETS_PATH/${FOLDER_HEIGHT[$target_height]}/$filename.png
            dir_dest_file=$(dirname $dest_file)
            if [ ! -d $dir_dest_file ]; then
              mkdir -p $dir_dest_file
            fi
            process_image $_file $dest_file $reduction_ratio
          fi
        fi
    done
done
