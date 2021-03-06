#include "expresscpp/http/request.hpp"

namespace express {
	namespace http {
		request::request(raw_request& request, asio::ip::address addr)
			:raw(&request), address(addr)
		{
			parseRequest();
		}

		void request::parseRequest()
		{
			// Parsing status string
			const std::string& head = raw->reqLine;

			size_t pathBegin = head.find(" /");
			size_t pathEnd = head.find(" HTTP/", pathBegin + 1);

			if (pathBegin == std::string::npos || pathEnd == std::string::npos)
				return;

			this->path = head.substr(pathBegin + 1, pathEnd - 4);

			// Getting query info
			size_t queryStart = path.find('?');

			if (queryStart != std::string::npos)
			{
				this->queries = query(this->path.substr(queryStart + 1, this->path.length()));

				this->path = this->path.substr(0, queryStart);
			}

			this->requestMethod = method(head.substr(0, pathBegin));
			this->reqVersion = version(head.substr(pathEnd + 1, head.length()));

			// Parsing headers
			this->headers = raw->headers;

			// Parsing body
			this->body = raw->body;
			
		}
	}
}