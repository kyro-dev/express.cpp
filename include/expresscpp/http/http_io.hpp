#ifndef HTTP_IO_HPP
#define HTTP_IO_HPP

#include <map>
#include <string>
#include <sstream>
#include <optional>
#include "expresscpp/http/raw_parsed.hpp"

namespace express {
	namespace http {
		struct http_io
		{
		public:
			static std::optional<raw_request> deserialize(const std::string &);

			static std::string serialize(const raw_response&);
		};
	}
}

#endif