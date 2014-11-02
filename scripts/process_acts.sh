#!/bin/bash
# Process the act's json files preparing them to be included in the game.
# Path for acts
# <calaveras_path>/Resources/conf/act/<id>/<layer_id>.json

LINUX_ACT_JSON=/home/waldemar/Projects/Calaveras/Resources/conf/act

echo "Replacing png to pvr in Acts..."
sed -i 's/\.png/\.pvr/g' $LINUX_ACT_JSON/*/*.json
echo "Done."
