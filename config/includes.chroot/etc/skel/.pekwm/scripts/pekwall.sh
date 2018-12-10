#!/bin/sh
# Auteur :      thuban <thuban@yeuxdelibad.net>
# licence :     MIT

# set wallpaper

WALLDIR=/usr/share/backgrounds/
WALLSET="feh --bg-fill"

echo "Dynamic {"
for W in $(ls $WALLDIR); do
	echo "Entry = \"$W\" { Actions = \"Exec $WALLSET $WALLDIR/$W\" }"
done
echo "}"
exit

