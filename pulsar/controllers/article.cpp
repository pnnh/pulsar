#include "pulsar/controllers/article.h"
#include "quark/business/articles/article.h"
#include <boost/uuid/uuid_io.hpp>
#include <nlohmann/json.hpp>
#include <pulsar/router.h>
#include <pulsar/services/business/article.hpp>
#include <quark/services/filesystem/filesystem.hpp>
#include <workflow/HttpMessage.h>

#include <quark/types/query.h>

using json = nlohmann::json;

void pulsar::HandleArticleGet(WFHttpTask *httpTask,
                              std::shared_ptr<PLRouteContext> routeContext) {
  protocol::HttpRequest *request = httpTask->get_req();
  protocol::HttpResponse *response = httpTask->get_resp();

  response->set_http_version("HTTP/1.1");
  response->add_header_pair("Content-Type", "application/json; charset=utf-8");
  response->add_header_pair("Access-Control-Allow-Origin", "*");

  auto uid = routeContext->getParams("uid");
  if (uid.empty()) {
    response->set_status_code("400");
    return;
  }

  auto request_uri = request->get_request_uri();

  quark::MTQueryString queryParam{std::string(request_uri)};

  std::ostringstream oss;
  // auto database_path =
  //     quark::JoinFilePath({"PROJECT_BINARY_DIR", "polaris.sqlite"});
  //
  // auto articleServer =
  //     std::make_shared<quark::ArticleSqliteService>(database_path);
  // auto model = articleServer->getArticle(uid);
  auto queryResult = pulsar::queryArticle(uid);
  if (!queryResult.has_value()) {
    response->set_status_code("404");
    return;
  }
  auto model = queryResult.value();
  json data = json::object({
      {"code", 200},
      {"message", "Hello, World!"},
      {"data", json::object({
                   {"uid", model.Uid},
                   {"title", model.Title},
                   {"header", model.Header},
                   {"body", model.Body},
                   {"keywords", model.Keywords},
                   {"description", model.Description},
                   {"create_time", model.CreateTime.toString()},
                   {"update_time", model.UpdateTime.toString()},
               })},
  });

  oss << data;

  auto bodyStr = oss.str();
  auto bodySize = bodyStr.size();

  response->append_output_body(bodyStr.c_str(), bodySize);

  response->set_status_code("200");
}

void pulsar::HandleArticles(WFHttpTask *httpTask,
                            std::shared_ptr<PLRouteContext> routeContext) {
  protocol::HttpRequest *request = httpTask->get_req();
  protocol::HttpResponse *response = httpTask->get_resp();

  response->set_http_version("HTTP/1.1");
  response->add_header_pair("Content-Type", "application/json; charset=utf-8");
  response->add_header_pair("Access-Control-Allow-Origin", "*");

  auto request_uri = request->get_request_uri();

  quark::MTQueryString queryParam{std::string(request_uri)};

  auto chanURN = queryParam.getString("chan");

  std::ostringstream oss;

  // auto database_path = quark::JoinFilePath({"PROJECT_BINARY_DIR",
  // "polaris.sqlite"}); auto articleServer =
  // std::make_shared<quark::ArticleSqliteService>(database_path);
  auto articlePtr = pulsar::selectArticles();
  json range = json::array();
  for (const auto &model : articlePtr) {
    // quark::Logger::LogInfo({model.URN, model.Title, model.Title});
    json item = {
        {"urn", model.Uid},
        {"title", model.Title},
        {"header", model.Header},
        {"body", model.Body},
        {"description", model.Description},
    };
    range.push_back(item);
  }
  auto count = articlePtr.size();

  json data = json::object({
      {"code", 200},
      {"message", "Hello, World!"},
      {"data",
       {{"count", count},
        {
            "range",
            range,
        }}},
  });

  oss << data;

  auto bodyStr = oss.str();
  auto bodySize = bodyStr.size();

  response->append_output_body(bodyStr.c_str(), bodySize);

  response->set_status_code("200");
}

// void
// MessageController::HandleDelete(boost::beast::http::request<boost::beast::http::dynamic_body>
// &request,
//                                      boost::beast::http::response<boost::beast::http::dynamic_body>
//                                      &response) {
//     response.result(boost::beast::http::status::ok);
//     response.keep_alive(false);
//     response.set(boost::beast::http::field::server, "Beast");

//     auto fullUrl = "http://localhost" + std::string(request.target());
//     auto url = boost::urls::parse_uri(fullUrl);
//     if (url.has_error()) {
//         spdlog::error("url parse error: {}", url.error().message());
//         response.result(boost::beast::http::status::internal_server_error);
//         return;
//     }

//     std::string msgPk = "";
//     for (auto p: url->params()) {
//         if (p.key == "pk") {
//             msgPk = p.value;
//         }
//     }
//     if (msgPk.empty()) {
//         spdlog::error("pk is empty");
//         response.result(boost::beast::http::status::bad_request);
//         return;
//     }

//     auto result = MessageService().deleteMessage(msgPk);
//     if (result != 0) {
//         response.result(boost::beast::http::status::internal_server_error);
//         return;
//     }

//     json data = {
//             {"code", Codes::Ok},
//     };

//     boost::beast::ostream(response.body()) << data;
// }

// void
// MessageController::HandleInsert(boost::beast::http::request<boost::beast::http::dynamic_body>
// &request,
//                                      boost::beast::http::response<boost::beast::http::dynamic_body>
//                                      &response) {

//     auto fullUrl = "http://localhost" + std::string(request.target());
//     auto url = boost::urls::parse_uri(fullUrl);
//     if (url.has_error()) {
//         spdlog::error("url parse error: {}", url.error().message());
//         response.result(boost::beast::http::status::internal_server_error);
//         return;
//     }

//     std::string title;
//     for (auto p: url->params()) {
//         if (p.key == "title") {
//             title = p.value;
//         }
//     }
//     if (title.empty()) {
//         spdlog::error("title is empty");
//         response.result(boost::beast::http::status::bad_request);
//         return;
//     }
//     boost::uuids::uuid a_uuid = boost::uuids::random_generator()(); //
//     这里是两个() ，因为这里是调用的 () 的运算符重载 const std::string pk =
//     boost::uuids::to_string(a_uuid);

//     auto model = ArticleModel{
//             .pk = pk,
//             .title = title,
//             .content = "content",
//             .create_time = std::chrono::system_clock::now(),
//             .update_time = std::chrono::system_clock::now(),
//             .creator = "creator",
//             .sender = "sender",
//             .receiver = "receiver",
//     };

//     auto result = MessageService().insertMessage(model);
//     if (result != 0) {
//         response.result(boost::beast::http::status::internal_server_error);
//         return;
//     }

//     json data = {
//             {"code", Codes::Ok},
//     };
//     boost::beast::ostream(response.body()) << data;

// }

// void
// MessageController::HandleUpdate(boost::beast::http::request<boost::beast::http::dynamic_body>
// &request,
//                                      boost::beast::http::response<boost::beast::http::dynamic_body>
//                                      &response) {
//     response.result(boost::beast::http::status::ok);
//     response.keep_alive(false);
//     response.set(boost::beast::http::field::server, "Beast");
// }
