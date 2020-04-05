#include <string>
#include <iostream>
#include <iterator>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>

namespace po = boost::program_options;

using namespace std;

const string MDL_CMD_BASE              = "youtube-dl";
const string MDL_TEMPLATE              = "'./%(playlist)s/%(playlist_index)s_%(title)s.%(ext)s'";
const string MDL_AUDIO                 = "audio";
const string MDL_VIDEO                 = "video";
const string MDL_VIDEO_PLAYLIST        = "videoplaylist";
const string MDL_AUDIO_PLAYLIST        = "audioplaylist";
const string MDL_MP3                   = "mp3";
const string MDL_M4A                   = "m4a";
const string MDL_WAV                   = "wav";
const string MDL_MEDIATYPE_DESCRIPTION = "media type [" + MDL_AUDIO + ", " + MDL_AUDIO_PLAYLIST + ", " + MDL_VIDEO + ", " + MDL_VIDEO_PLAYLIST + "]";
const string MDL_DEFAULT_MANIFEST      = "manifest";

string
  final_command
  ,media_type
  ,media_type_to_lower
  ,audio_format
  ,audio_format_to_lower
  ,manifest_file_path
  ,rate
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
  cout << "Download initiated..." << endl;

  system(final_command.c_str());
}

int main(int argc, char* argv[])
{
  command_init();

  try
  {
    po::options_description generalOptions("Options");
    generalOptions.add_options()
      ("help,h", "command options")
      ("type,t", po::value<string>(&media_type)->default_value(MDL_VIDEO_PLAYLIST), MDL_MEDIATYPE_DESCRIPTION.c_str())
      ("format,f", po::value<string>(&audio_format)->default_value(MDL_MP3), "audio format")
      ("rate,r", po::value<string>(&rate), "download rate (eg, 50K, 4.2M, etc)")
      ("manifest-file,m", po::value<string>(&manifest_file_path)->default_value(MDL_DEFAULT_MANIFEST), "manifest file")
      ;

    po::positional_options_description p;
    p.add("manifest-file", -1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(generalOptions).positional(p).run(), vm);
    po::notify(vm);

    if(vm.count("help"))
    {
      cout << generalOptions << endl;

      return 0;
    }

    media_type_to_lower = media_type;
    boost::to_lower(media_type_to_lower);
    audio_format_to_lower = audio_format;
    boost::to_lower(audio_format_to_lower);

    if(!rate.empty()) command_add_flag("--rate " + rate);

    if(
      media_type_to_lower == MDL_AUDIO
      || media_type_to_lower == MDL_AUDIO_PLAYLIST
    )
    {
      if(
        audio_format_to_lower == MDL_MP3
        || audio_format_to_lower == MDL_M4A
        || audio_format == MDL_WAV
      )
      {
        command_add_flag("-x");
        command_add_flag("--audio-format " + audio_format_to_lower);
        command_call();

        return 0;
      }else
      {
        cout << "Invalid audio format: " << audio_format << endl;

        return 1;
      }
    }

    if(
      media_type_to_lower == MDL_VIDEO
      || media_type_to_lower == MDL_VIDEO_PLAYLIST
    )
    {
      command_add_flag("--write-auto-sub");
      command_add_flag("--sub-format srt/vtt/ttml/best");
      command_add_flag("--sub-lang en");
      command_add_flag("--embed-subs");
      command_add_flag("--convert-subs srt");
      command_add_flag("-o " + MDL_TEMPLATE);
      command_call();

      return 0;
    }

    command_call();

    return 0;

  } catch(exception& error)
  {
    cerr << "error: " << error.what() << endl;

    return 1;
  } catch(...)
  {
    cerr << "Unknown exception!" << endl;
  }

  return 0;
}

