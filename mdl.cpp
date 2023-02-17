#include <string>
#include <iostream>
#include <iterator>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>

namespace po = boost::program_options;

using namespace std;

const string MDL_CMD_BASE              = "yt-dlp";
const string MDL_FILE_TEMPLATE         = "'./%(title)s__%(id)s__%(webpage_url_domain)s.%(ext)s'";
const string MDL_PLAYLIST_TEMPLATE     = "'./%(playlist)s/%(playlist_index)s_%(title)s.%(ext)s'";
const string MDL_AUDIO                 = "audio";
const string MDL_VIDEO                 = "video";
const string MDL_VIDEO_PLAYLIST        = "videoplaylist";
const string MDL_AUDIO_PLAYLIST        = "audioplaylist";
const string MDL_MP3                   = "mp3";
const string MDL_M4A                   = "m4a";
const string MDL_WAV                   = "wav";
const string MDL_MEDIATYPE_DESCRIPTION = "media type [" + MDL_AUDIO + ", " + MDL_AUDIO_PLAYLIST + ", " + MDL_VIDEO + ", " + MDL_VIDEO_PLAYLIST + "]";
const string MDL_DEFAULT_MANIFEST      = "manifest";

bool dry_run;
int closest_video_resolution;
string
  final_command
  ,media_type
  ,media_type_to_lower
  ,audio_format
  ,audio_format_to_lower
  ,format_id
  ,manifest_file_path
  ,rate
  ,filter
  ;

void command_add_flag(string _flag)
{
  final_command += " " + _flag;
}

void command_init()
{
  command_add_flag(MDL_CMD_BASE);
  command_add_flag("--restrict-filenames");
  command_add_flag("--no-overwrites");
  command_add_flag("--ignore-errors");
}

void command_call()
{
  command_add_flag("--batch-file " + manifest_file_path);

  cout << "\e[33mCommand:\e[m " << final_command << endl;

  if(dry_run) return;

  cout << "Download initiated..." << endl;

  system(final_command.c_str());
}

bool is_playlist(string _media_type)
{
  return MDL_AUDIO_PLAYLIST == _media_type || MDL_VIDEO_PLAYLIST == _media_type;
}

bool is_audio(string _media_type)
{
  return MDL_AUDIO == _media_type || MDL_AUDIO_PLAYLIST == _media_type;
}

bool is_video(string _media_type)
{
  return MDL_VIDEO == _media_type || MDL_VIDEO_PLAYLIST == _media_type;
}

int main(int argc, char* argv[])
{
  command_init();

  try
  {
    po::options_description options("Options");
    options.add_options()
      ("help,h", "display help info")
      ("type,t", po::value<string>(&media_type)->value_name("TYPE")->default_value(MDL_VIDEO_PLAYLIST), MDL_MEDIATYPE_DESCRIPTION.c_str())
      ("list-formats,F", "List available download formats")
      ("format,f", po::value<string>(&audio_format)->value_name("FORMAT")->default_value(MDL_MP3), "audio format")
      ("format-id,i", po::value<string>(&format_id)->value_name("REGEX"), "download video whose format id matches specified regex (eg, \"^480[pP]$\")")
      ("closest-video-resolution,c", po::value<int>(&closest_video_resolution)->value_name("RESOLUTION"), "download video with resolution closest to value specified (eg, 480)")
      ("rate,r", po::value<string>(&rate)->value_name("RATE"), "download rate (eg, 420k, 4.2M, etc)")
      ("filter,q", po::value<string>(&filter)->value_name("FILTER"), "quality filter (eg, 22, 135, 136, best, worst, bestvideo, worstaudio, etc)")
      ("subtitles,s", "Include subtitles")
      ("manifest-file,m", po::value<string>(&manifest_file_path)->value_name("FILE")->default_value(MDL_DEFAULT_MANIFEST), "manifest file")
      ("dry-run,N", "show command line instead of downloading")
      ;

    po::positional_options_description p;
    p.add("manifest-file", -1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(options).positional(p).run(), vm);
    po::notify(vm);

    if(vm.count("help"))
    {
      cout << options << endl;

      return 0;
    }

    if(vm.count("list-formats"))
    {
      command_add_flag("--list-formats");
    }

    media_type_to_lower = media_type;
    boost::to_lower(media_type_to_lower);
    audio_format_to_lower = audio_format;
    boost::to_lower(audio_format_to_lower);

    if(is_audio(media_type_to_lower))
    {
      if(
        audio_format_to_lower == MDL_MP3
        || audio_format_to_lower == MDL_M4A
        || audio_format == MDL_WAV
      )
      {
        command_add_flag("--extract-audio");
        command_add_flag("--audio-format " + audio_format_to_lower);
      }else
      {
        cout << "Invalid audio format: " << audio_format << endl;

        return 1;
      }
    }

    if(vm.count("format-id"))
    {
      command_add_flag("--format '[format_id~=\"" + format_id + "\"]'");
    }

    if(closest_video_resolution)
    {
      command_add_flag("--format-sort 'res~" + std::to_string(closest_video_resolution) + "'");
    }

    if(!rate.empty()) command_add_flag("--rate " + rate);

    if(!filter.empty()) command_add_flag("--format " + filter);

    if(vm.count("subtitles"))
    {
      command_add_flag("--write-auto-sub");
      command_add_flag("--sub-format srt/vtt/ttml/best");
      command_add_flag("--sub-lang en");
      command_add_flag("--embed-subs");
      command_add_flag("--convert-subs srt");
    }

    command_add_flag("--output " + (is_playlist(media_type_to_lower) ? MDL_PLAYLIST_TEMPLATE : MDL_FILE_TEMPLATE));

    if(vm.count("dry-run")) dry_run = true;

    command_call();
  }
  catch(exception& error)
  {
    cerr << "error: " << error.what() << endl;

    return 1;
  }
  catch(...)
  {
    cerr << "Unknown exception!" << endl;
  }

  return 0;
}

