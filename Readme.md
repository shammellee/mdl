mdl is a tiny UNIX command line wrapper for [yt-dlp][yt-dlp]) to download
video/audio from popular sites.


# Notes

* This tool does not add any functionality that does not exist in
  [yt-dlp][yt-dlp]; it simply contains shortcuts for common download tasks
  with [yt-dlp][yt-dlp]
* mdl will not overwrite existing files of the same name as the file in question
* This has only been tested on OS X Mountain Lion and macOS Sierra 10.12.6 and
  will not work on a non-Unix machine
* If you want more control than mdl offers, use [yt-dlp][yt-dlp] directly


# Dependencies

* [yt-dlp][yt-dlp]
* [Boost][boost]: The following files must exist after installation…
  * `<header_include_directory>/boost/algorithm/string.hpp`
    * eg, `/usr/local/include/boost/algorithm/string.hpp`
  * `<header_include_directory>/boost/program_options.hpp`
    * eg, `/usr/local/include/boost/program_options.hpp`
  * `<library_directory>/libboost_program_options.a`
    * eg, `/usr/local/lib/libboost_program_options.a`
* Xcode Command Line Tools
* [GNU Make][make]


# Building mdl

* Run `$ make` (creates the mdl executable in the root of this project)
* Add the path to the mdl executable to your `PATH` environment variable or run
  mdl directly


# Synopsis

`mdl [options] <manifestFile>`


# Options


Option                          | Default         | Description
------------------------------- | --------------- | ------------------------------------------------------------
`-h,--help`                     | N/A             | Display help info
`-t,--type`                     | `videoplaylist` | Media type (`audio`|`audioplaylist`|`video`|`videoplaylist`)
`-F,--list-formats`             | N/A             | List available download formats
`-f,--format`                   | `mp3`           | Audio format (accepts formats specified by [yt-dlp][yt-dlp])
`-i,--format-id`                | N/A             | Download video whose format id matches specified regex (eg, "^480[pP]$")
`-c,--closest-video-resolution` | N/A             | Download video with resolution closest to value specified (eg, 480)
`-r,--rate`                     | Unlimited       | Download rate (eg, 420k, 4.2M, etc)
`-q,--filter`                   | `best`          | Quality filter (eg, `22`, `135`, `136`, `best`, `worst`, `bestvideo`, `worstaudio`, etc)
`-s,--subtitles`                | Disabled        | Include subtitles
`-m,--manifest-file`            | `manifest`      | Manifest file
`-N,--dry-run`                  | N/A             | Show command line instead of downloading


# Examples

Running `mdl` will, by default, look for a line-delimited text file in the
current directory named `manifest` from which to download files. The files will
be downloaded into the current directory

Contents of an example manifest file…

```
https://www.youtube.com/watch?v=Z4GzetzGg4U
https://www.youtube.com/watch?v=G3lAM_L3jR0
https://www.youtube.com/watch?v=cfOa1a8hYP8
https://www.youtube.com/watch?v=9YDmYMDEAPY
```

The following command line will download and extract the audio as mp3s (the
default audio format) from the videos specified in a file named
`my_songs.txt`...

`$ mdl -t audio -m my_songs.txt`

If the manifest file is the last argument, there is no need to specify `-m` or
`--manifest-file=<manifest_file>`…

`$ mdl -t audio my_songs.txt`

Since mdl looks for a manifest file named `manifest` by default, the command
line can be shortened to…

`$ mdl -t audio`


# Changelog

* v0.3.0
  * Add "format id" option
  * Add argument names to options
  * Add "list formats" option
  * Add "closest video resolution" option
  * Add "dry-run" option
  * Update output template to make output file more unique to avoid file name clashes
  * Switch from "youtube-dl" to "yt-dlp"
  * Add empty database
  * Add "subtitle" option
  * Add "filter" option
* v0.2.0
  * Add `-r, --rate` command line option
* v0.1.0
  * lowercase `mediaType` variable instead of testing for variations in case
    (eg `mediaType == "audioPlaylist" || mediaType == "audioplaylist"`)
	* convert common strings to `const`
* Initial build

[yt-dlp]: https://github.com/yt-dlp/yt-dlp
[boost]: http://www.boost.org/
[make]: http://www.gnu.org/software/make/

