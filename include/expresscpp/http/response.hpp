#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <fstream>
#include <streambuf>
#include "expresscpp/commons/pch.hpp"
#include "expresscpp/http/cookies.hpp"
#include "expresscpp/http/headers.hpp"
#include "expresscpp/http/raw_parsed.hpp"

namespace express {
	namespace http {
		struct http_connection;

		class response
		{
			friend struct http_connection;
		
		private:
			version resVersion;

			raw_response construct();

		public:
			status statusCode;
			const char* clientIP;
			http::cookies cookies;
			std::ostringstream body;
			http::headers headers;

			response(version);

			// Set status of response
			void setStatus(uint16_t);

			// Set cookies
			void setCookie(const char*, const char*);
			
			// Set header (Will override existing header with same name)
			void setHeader(std::string, std::string);

			void setHeader(std::string, int);

			// Sets stream data
			void send(const std::string);

			// Sends data from file
			void sendFile(const std::string);
		};
	}
}

#endif