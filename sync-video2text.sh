#!/usr/bin/env bash

set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source_dir="${VIDEO2TEXT_TRANSCRIPTS_DIR:-/nfs/home/gongkaichen/learning/video-summary/transcripts}"
target_dir="$repo_root/docs/notes/video2text"

if [[ ! -d "$source_dir" ]]; then
  echo "Transcript directory not found: $source_dir" >&2
  exit 1
fi

mkdir -p "$target_dir"
rsync --archive --delete "$source_dir/" "$target_dir/"

echo "Mirrored $source_dir to $target_dir"
