#!/bin/bash
git_add="
Android.mk
gralloc_drm.cpp
gralloc_drm_handle.h
gralloc_drm_priv.h
gralloc_drm_rockchip.c
format_chooser.cpp
format_chooser.h
format_chooser_blockinit.cpp
formatdef_files/
git_add.sh
gralloc_buffer_priv.cpp
"

for i in $git_add;
do
git add   $i
done
