/*	Copyright 2018 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_TETHYS_PROTOCOL_LINC_IMPL
#	define ENTROPY_TETHYS_PROTOCOL_LINC_IMPL

#	include "Line.hh"

	namespace Entropy
	{
		namespace Tethys
		{
			namespace Protocol
			{
				template<typename App, typename Sock, typename charT, typename traits, typename Alloc>
				Line<App, Sock, charT, traits, Alloc>::Line(App &app, const std::basic_string<charT, traits, Alloc> &delim)
					: Application<App, Sock>(app), _delim(delim)
				{}

				template<typename App, typename Sock, typename charT, typename traits, typename Alloc>
				Line<App, Sock, charT, traits, Alloc>::Line(const Line<App, Sock, charT, traits, Alloc> &) = default;

				template<typename App, typename Sock, typename charT, typename traits, typename Alloc>
				Line<App, Sock, charT, traits, Alloc>::Line(Line<App, Sock, charT, traits, Alloc> &&) = default;

				template<typename App, typename Sock, typename charT, typename traits, typename Alloc>
				Line<App, Sock, charT, traits, Alloc>::~Line() = default;

				template<typename App, typename Sock, typename charT, typename traits, typename Alloc>
				void Line<App, Sock, charT, traits, Alloc>::onData(Sock &s)
				{
					using std::basic_string;

					std::streamsize pos = findLine(s);

					while(pos) {
						basic_string<charT> line(pos, 0);
						s.read(line.data(), pos);

						line = line.substr(0, line.size() - _delim.size());
						this->getApplication().onLine(s, line);

						pos = findLine(s);
					}
				}

				template<typename App, typename Sock, typename charT, typename traits, typename Alloc>
				std::streamsize Line<App, Sock, charT, traits, Alloc>::findLine(Sock &s)
				{
					auto x = 0u;
					auto y = 0u;

					auto start = s.tellg();

					while(s.peek() != Sock::traits_type::eof()) {
						if(s.peek() == _delim[y]) {
							if(y++ == _delim.size() - 1) {
								s.seekg(start);
								return ++x;
							}
						} else {
							y = 0;
						}

						s.seekg(1, std::ios_base::cur);
						x++;
					}

					s.clear();
					s.seekg(start);
					return 0;
				}
			}
		}
	}


#endif
