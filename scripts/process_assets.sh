#!/bin/bash
# Move and rename files from game_art to their respective Resource folder.

BASE_ASSETS_PATH=/home/waldemar/Projects/Calaveras/spine
GAME_ASSETS_PATH=/home/waldemar/Projects/Calaveras/Resources

TARGET_FOLDERS="4k xfhd fhd lg md"

proc_dir() {
  base_folder=$1
  rec_folder=$2
  base_folder_filename=$(basename "$base_folder")
  echo "Processing $base_folder"

  if [ -f $base_folder/skeleton.json ]; then
    skeleton_target_folder=$GAME_ASSETS_PATH/skeletons/$rec_folder
    if [ ! -d $skeleton_target_folder ]; then
      mkdir -p $skeleton_target_folder
    fi
    cp $base_folder/skeleton.json $skeleton_target_folder/skeleton.json
  fi

  # Duplicate structure in resources folder
  for target_folder in $TARGET_FOLDERS; do
    resource_target_folder=$GAME_ASSETS_PATH/$target_folder/$rec_folder
    if [ ! -d $resource_target_folder ]; then
      mkdir -p $resource_target_folder
    fi
    if [ -f $base_folder/skeleton.$target_folder.atlas ]; then
      cp $base_folder/skeleton.$target_folder.atlas $resource_target_folder/skeleton.atlas
    fi
    if [ -f $base_folder/skeleton.$target_folder.png ]; then
      cp $base_folder/skeleton.$target_folder.png $resource_target_folder/skeleton.$target_folder.png
    fi
  done

  for __file in $base_folder/*; do
    if [ -d $__file ]; then
      proc_dir $__file $rec_folder/$(basename "$__file")
    fi
  done
}

for _file in $BASE_ASSETS_PATH/*; do
  if [ -d $_file ]; then
    proc_dir $_file $(basename "$_file")
  fi
done
