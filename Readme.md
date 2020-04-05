mdl is a tiny UNIX command line wrapper for [youtube-dl][ytdl]) to download
video/audio from popular sites.


# Notes

* This tool does not add any functionality that does not exist in
  [youtube-dl][ytdl]; it simply contains shortcuts for common download tasks
  with [youtube-dl][ytdl]
* mdl will not overwrite existing files of the same name as the file in question
* This has only been tested on OS X Mountain Lion and macOS Sierra 10.12.6 and
  will not work on a non-Unix machine
* If you want more control than mdl offers, use [youtube-dl][ytdl] directly


# Dependencies

* [youtube-dl][ytdl]
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

`mdl [-t,--type <downloadType>] [-f,--format <audioFormat>] [-m,--manifest-file <manifestFile>]`


# Options

Option               | Default         | Description
-------------------- | --------------- | ------------------------------------------------------------
`-t,--type`          | `videoPlaylist` | download type (`video`, `videoPlaylist`, `audio`, `audioPlaylist`)
`-f,--format`        | `mp3`           | audio format (accepts formats specified by [youtube-dl][ytdl])
`-r,--rate`          | unmetered       | download rate (eg, `420k`, `4.2M`, etc)
`-m,--manifest-file` | `./manifest`    | path to manifest file
`-h,--help`          | N/A             | display help info


# Examples

Running `mdl` will, by default, look for a line-delimited text file in the
current directory named `manifest` from which to download video files. The
files will be downloaded into the current directory

Contents of an example manifest file…

```
https://www.youtube.com/watch?v=Z4GzetzGg4U
https://www.youtube.com/watch?v=G3lAM_L3jR0
https://www.youtube.com/watch?v=cfOa1a8hYP8
https://www.youtube.com/watch?v=9YDmYMDEAPY
```

The following command line will download and extract the audio as mp3s (default
audio format) from the youtube videos specified in a file named
`my_songs.txt`...

`$ mdl -t audio -m my_songs.txt`

If the manifest file is the last argument, there is no need to specify `-m` or
`--manifest-file=<manifest_file>`…

`$ mdl -t audio my_songs.txt`

If the manifest file is named `manifest`, the following shorter command line
can be used…

`$ mdl -t audio`


[ytdl]: https://github.com/rg3/youtube-dl/
[boost]: http://www.boost.org/
[make]: http://www.gnu.org/software/make/

## Changelog

* v0.2.0
  * Add `-r, --rate` command line option
* v0.1.0
  * lowercase `mediaType` variable instead of testing for variations in case
  (eg `mediaType == "audioPlaylist" || mediaType == "audioplaylist"`)
	* convert common strings to `const`
* Initial build

