#include "expresscpp/http/response.hpp"

namespace express {
	namespace http {
		response::response(version v)
			:statusCode(status::OK), resVersion(v)
		{
			setHeader("Connection", "close");
			setHeader("Server", "Express.cpp");
		}

		raw_response response::construct()
		{
			std::string data = body.str();

			setHeader("Content-Length", data.length());

			std::string head = static_cast<std::string>(resVersion) + " " + std::to_string(statusCode) + " " + static_cast<std::string>(statusCode);
			return raw_response{head, headers, data};
		}

		void response::setStatus(uint16_t status)
		{
			statusCode = static_cast<http::status>(status);
		}

		void response::setCookie(const char* key, const char* value)
		{
			cookies[key] = value;
		}

		void response::setHeader(std::string key, std::string value)
		{
			headers[key] = { value };
		}

		void response::setHeader(std::string key, int value)
		{
			setHeader(key, std::to_string(value));
		}

		void response::send(const std::string data)
		{
			setHeader("Content-Type", "text/html");
			body.str(data);
		}
		
		void response::sendFile(const std::string filename)
		{
			const auto getContentType = [](const std::string* name) {
				const auto iequals = [](const std::string& ext, const char* type) {
					if (ext.compare(type) == 0)
						return true;
					return false;
				};

				const size_t pos = name->find_last_of('.');

				if (pos == std::string::npos)
					return "INVALID";

				const std::string ext = name->substr(pos, name->length());

				if (iequals(ext, ".htm"))  return "text/html";
				if (iequals(ext, ".html")) return "text/html";
				if (iequals(ext, ".php"))  return "text/html";
				if (iequals(ext, ".css"))  return "text/css";
				if (iequals(ext, ".txt"))  return "text/plain";
				if (iequals(ext, ".js"))   return "application/javascript";
				if (iequals(ext, ".json")) return "application/json";
				if (iequals(ext, ".xml"))  return "application/xml";
				if (iequals(ext, ".swf"))  return "application/x-shockwave-flash";
				if (iequals(ext, ".flv"))  return "video/x-flv";
				if (iequals(ext, ".png"))  return "image/png";
				if (iequals(ext, ".jpe"))  return "image/jpeg";
				if (iequals(ext, ".jpeg")) return "image/jpeg";
				if (iequals(ext, ".jpg"))  return "image/jpeg";
				if (iequals(ext, ".gif"))  return "image/gif";
				if (iequals(ext, ".bmp"))  return "image/bmp";
				if (iequals(ext, ".ico"))  return "image/vnd.microsoft.icon";
				if (iequals(ext, ".tiff")) return "image/tiff";
				if (iequals(ext, ".tif"))  return "image/tiff";
				if (iequals(ext, ".svg"))  return "image/svg+xml";
				if (iequals(ext, ".svgz")) return "image/svg+xml";
				return "application/text";
			};

			std::ifstream ifs(filename, std::ios::in | std::ios::binary);

			if (ifs)
			{
				std::string file((std::istreambuf_iterator<char>(ifs)), {});

				setStatus(status::Accepted);

				body.str(file);
				setHeader("Content-Type", getContentType(&filename));
				return;
			}

			throw std::ifstream::failure("File " + filename + "not found");
		}
	}
}