# MDL
tiny command line tool (built on top of [youtube-dl][ytdl]) to download videos from popular sites and optionally extract audio

# Notes
* this tool does not add any functionality that does not exist in [youtube-dl][ytdl]; it simply contains shortcuts for common download tasks with [youtube-dl][ytdl]
* mdl will not overwrite existing files of the same name as the file in question
* this has only been tested on OS X Mountain Lion
* if you want more control than mdl offers, check out [youtube-dl][ytdl]

# Dependencies
* [youtube-dl][ytdl]
* [GNU Make][make]

# Building MDL
`$ make` creates an executable (mdl)

# Synopsis
`mdl [-t,--type <downloadType>] [-f,--format <audioFormat>] [-m,--manifest-file <manifestFile>]`

# Options
* `-t,--type` download type (video, videoPlaylist, audio, audioPlaylist)
* `-f,--format` audio format (accepts formats specified by [youtube-dl][ytdl])
* `-m,--manifest-file` path to manifest file
* `-h,--help` display help info

# Option Defaults
* -t: videoPlaylist
* -f: mp3
* -m: manifest

Running `mdl` will, by default, look for a line-delimited text file named `manifest` from which to download video files

// my_manifest.txt
```
https://www.youtube.com/watch?v=G3lAM_L3jR0
https://www.youtube.com/watch?v=cfOa1a8hYP8
https://www.youtube.com/watch?v=9YDmYMDEAPY
https://www.youtube.com/watch?v=Sszc5oMvq60
```

The following command will download and extract the audio as mp3s (default audio format) from the youtube videos in `my_manifest.txt`...
`$ mdl -t audio -m my_manifest.txt`

[ytdl]: https://github.com/rg3/youtube-dl/ "youtube-dl"
[make]: http://www.gnu.org/software/make/ "GNU Make"
