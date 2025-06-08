#include "RedirectorRequestHandler.h"
#include <boost/beast/http.hpp>
#include <boost/beast/core.hpp>
#include "../logger/ILogger.h"
#include "../core/IoCContainer/IoCCore/IoC.h"
#include "../third_party/json.hpp"
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;
using json = nlohmann::json;

RedirectorRequestHandler::RedirectorRequestHandler(std::shared_ptr<IRuleEngine> engine) : rule_engine(engine)
{
}

json httpRequestToJson(const http::request<http::string_body>& req) {
    json result;

    // 1. Метод (GET, POST, PUT и т. д.)
    result["method"] = std::string(req.method_string());

    // 2. Целевой URL (target)
    result["target"] = std::string(req.target());

    // 3. Версия HTTP (например, "HTTP/1.1")
    result["version"] = req.version();

    // 4. Заголовки (headers)
    json headers_json;
    for (const auto& header : req) {
        headers_json[std::string(header.name_string())] = std::string(header.value());
    }
    result["headers"] = headers_json;

    // 5. Тело запроса (body)
    result["body"] = req.body();

    return result;
}


void RedirectorRequestHandler::handleRequest(tcp::socket socket)
{
    try {

        beast::flat_buffer buffer;
        http::request<http::string_body> req;
        boost::system::error_code ec; // Для обработки ошибок без исключений
    
        http::read(socket, buffer, req, ec);

        // Обработка ошибок чтения
        if (ec) {
            if (ec == beast::http::error::end_of_stream) {
                IoC::Resolve<ILogger*>("Logger")->log("Client disconnected before sending full request \n");
                return; 
            }
            else if (ec == beast::error::timeout) {
                IoC::Resolve<ILogger*>("Logger")->log("Read socket timeout \n");
                http::response<http::string_body> res{ http::status::request_timeout, 11 };
                res.set(http::field::server, "SmartRedirector");
                res.set(http::field::content_type, "text/plain");
                res.body() = "Request Timeout";
                res.prepare_payload();
                http::write(socket, res);
                return;
            }
            else {
                // Другие ошибки
                throw beast::system_error(ec);
            }
        }      

        // Логирование
        IoC::Resolve<ILogger*>("Logger")->log("===== Redirection =====\n"
            "      Processing request:\n"
            "      Method: " + std::string(req.method_string()) + "\n" +
            "      Target: " + std::string(req.target()) + "\n" +
            "      User-Agent: " + std::string(req[http::field::user_agent]) + "\n");
    
        // Обработка запроса
        std::string targetURL;
        try {
            json jReq = httpRequestToJson(req);
            targetURL = rule_engine->evaluate(jReq);
        }
        catch (const std::exception& e) {
            IoC::Resolve<ILogger*>("Logger")->log(std::format("Redirect FAILED!   Error request processing: {} \n", e.what()));
            std::string error = e.what();
            http::status status = http::status::internal_server_error;

            // Определяем тип ошибки
            if (error.find("not redirection rule for path") != std::string::npos) {
                status = http::status::not_found;
            }

            http::response<http::string_body> res{ status, req.version() };
            res.set(http::field::server, "SmartRedirector");
            res.set(http::field::content_type, "text/plain");
            res.body() = "Error: " + error;
            res.prepare_payload();
            http::write(socket, res);
            return;
        }

        // Успешное перенаправление
        http::response<http::string_body> res{ http::status::found, req.version() };
        res.set(http::field::server, "SmartRedirector");
        res.set(http::field::location, targetURL);
        res.set(http::field::content_type, "text/html");
        res.body() = "Redirecting to <a href=\"" + targetURL + "\">" + targetURL + "</a>";
        res.prepare_payload();

        http::write(socket, res);
        IoC::Resolve<ILogger*>("Logger")->log(std::format("----- Redirect to:  {}  COMPLITED ----- \n", targetURL));

    }
    catch (const std::exception& e) {
        IoC::Resolve<ILogger*>("Logger")->log(std::format("Unhandled exception: {} \n", e.what()));
        try {
            http::response<http::string_body> res{ http::status::internal_server_error, 11 };
            res.set(http::field::server, "SmartRedirector");
            res.set(http::field::content_type, "text/plain");
            res.body() = "Internal Server Error: " + std::string(e.what());
            res.prepare_payload();
            http::write(socket, res);
        }
        catch (...) {
            // Подавление ошибок при отправке
        }
    }
}
