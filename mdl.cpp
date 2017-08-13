#include <string>
#include <iostream>
#include <iterator>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
namespace po = boost::program_options;

using namespace std;

const string MDL_CMD_BASE              = "youtube-dl --restrict-filenames --no-overwrites --ignore-errors --write-auto-sub --sub-format srt/vtt/ttml/best --sub-lang en --embed-subs --convert-subs srt";
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
  finalCommand = MDL_CMD_BASE
  ,mediaType
  ,mediaType__to_lower
  ,audioFormat
  ,audioFormat__to_lower
  ,manifestFilePath
;

void callCommand()
{
  finalCommand += " -a " + manifestFilePath;
  cout << "\e[33mCommand:\e[m " << finalCommand << endl;
  cout << "Download initiated..." << endl;
  system(finalCommand.c_str());
}

int main(int ac, char* av[])
{

  try
  {
    po::options_description generalOptions("Options");
    generalOptions.add_options()
      ("help,h", "command options")
      ("type,t", po::value<string>(&mediaType)->default_value(MDL_VIDEO_PLAYLIST),MDL_MEDIATYPE_DESCRIPTION.c_str())
      ("format,f",po::value<string>(&audioFormat)->default_value(MDL_MP3),"audio format")
      ("manifest-file,m",po::value<string>(&manifestFilePath)->default_value(MDL_DEFAULT_MANIFEST),"manifest file")
    ;

    po::positional_options_description p;
    p.add("manifest-file", -1);

    po::variables_map vm;
    po::store(po::command_line_parser(ac, av).options(generalOptions).positional(p).run(), vm);
    po::notify(vm);

    if(vm.count("help"))
    {
      cout << generalOptions << endl;
      return 0;
    }

    mediaType__to_lower = mediaType;
    boost::to_lower(mediaType__to_lower);
    audioFormat__to_lower = audioFormat;
    boost::to_lower(audioFormat__to_lower);

    if(mediaType__to_lower == MDL_AUDIO || mediaType__to_lower == MDL_AUDIO_PLAYLIST)
    {
      if(audioFormat__to_lower == MDL_MP3 || audioFormat__to_lower == MDL_M4A || audioFormat == MDL_WAV)
      {
        finalCommand += " -x --audio-format " + audioFormat__to_lower;
        callCommand();
        return 0;
      }else
      {
        cout << "Invalid audio format: " << audioFormat << endl;
        return 1;
      }
    }

    if(mediaType__to_lower == MDL_VIDEO_PLAYLIST || mediaType__to_lower == MDL_AUDIO_PLAYLIST)
    {
      finalCommand += " -o " + MDL_TEMPLATE;
      callCommand();
      return 0;
    }

    callCommand();
    return 0;

  }catch(exception& e)
  {
    cerr << "error: " << e.what() << endl;
    return 1;
  }catch(...)
  {
    cerr << "Unknown exception!" << endl;
  }

  return 0;
}
