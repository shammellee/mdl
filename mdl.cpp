#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <iostream>
#include <iterator>
using namespace std;

int main(int ac, char* av[])
{
	try
	{
		const string MDL_CMD      = "youtube-dl --max-quality 37 --restrict-filenames -wi";
		const string MDL_TEMPLATE = "'./%(playlist)s/%(playlist_index)s_%(title)s.%(ext)s'";

		string
			finalCommand = MDL_CMD
			,mediaType
			,audioFormat
			,manifestFilePath
		;

		po::options_description generalOptions("Options");
		generalOptions.add_options()
			("help,h", "command options")
			("type,t", po::value<string>(&mediaType)->default_value("videoPlaylist"),"media type [audio, audioPlaylist, video, videoPlaylist]")
			("format,f",po::value<string>(&audioFormat)->default_value("mp3"),"audio format")
			("manifest-file,m",po::value<string>(&manifestFilePath)->default_value("manifest"),"manifest file")
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

		if(mediaType == "audio" || mediaType == "audioPlaylist" || mediaType == "audioplaylist")
		{
			if(audioFormat == "mp3" || audioFormat == "m4a" || audioFormat == "wav")
			{
				finalCommand += " -x --audio-format " + audioFormat;
			}else
			{
				cout << "Invalid audio format: " << audioFormat << endl;
				return 1;
			}
		}

		if(mediaType == "videoPlaylist" || mediaType == "videoplaylist" || mediaType == "audioPlaylist" || mediaType == "audioplaylist") finalCommand += " -o " + MDL_TEMPLATE;

		finalCommand += " -a " + manifestFilePath;
		cout << "Download initiated..." << endl;
		system(finalCommand.c_str());
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