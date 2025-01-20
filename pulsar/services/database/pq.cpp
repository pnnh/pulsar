#include "pq.h"
#include <iostream>
#include <pqxx/pqxx>
#include <quark/models/articles/Article.h>

std::vector<quark::PSArticleModel> selectArticles() {
  std::vector<quark::PSArticleModel> articlesList;
  auto pqDsn = "todo";//GetConfigItem("DSN");
  // std::cout << "pqDsn is: " << pqDsn << std::endl;
  try {
    pqxx::connection conn(pqDsn);
    if (conn.is_open()) {
      std::cout << "Opened database successfully: " << conn.dbname()
                << std::endl;
      const char *sqlText =
          "select pk, title, body, create_time, update_time, creator, "
          "keywords, description from articles order by update_time desc limit "
          "100;";
      pqxx::nontransaction N(conn);
      pqxx::result R(N.exec(sqlText));

      for (pqxx::result::const_iterator itr = R.begin(); itr != R.end();
           ++itr) {
        // std::cout << "Pk = " << itr[0].as<std::string>() << std::endl;
        // std::cout << "Title = " << itr[1].as<std::string>() << std::endl;
        auto model =
            quark::PSArticleModel{
              // .pk = itr[0].as<std::string>(),
              //            .title = itr[1].as<std::string>(),
              //            .body = itr[2].as<std::string>(),
              //            .create_time = quark::makeTimePoint(itr[3].as<std::string>()),
              //            .update_time = quark::makeTimePoint(itr[4].as<std::string>()),
              //            .creator = itr[5].as<std::string>()
            };
        if (!itr[6].is_null()) {
          model.Keywords = itr[6].as<std::string>();
        }
        if (!itr[7].is_null()) {
          model.Description = itr[7].as<std::string>();
        }

        articlesList.push_back(model);
      }
      std::cout << "Operation done successfully" << std::endl;
    } else {
      std::cout << "Can't open database" << std::endl;
      return articlesList;
    }
    // todo 需要关闭链接，因为构建错误所以暂时注释。不确定是调用disconnect还是close
    // conn.disconnect();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return articlesList;
  }
  return articlesList;
}

quark::PSArticleModel queryArticle(std::string pk) {
  auto pqDsn = "todo";//GetConfigItem("DSN");
  //std::cout << "pqDsn is: " << pqDsn << std::endl;

  pqxx::connection conn(pqDsn);
  if (conn.is_open()) {
    std::cout << "Opened database successfully: " << conn.dbname() << std::endl;
    const char *sqlText =
        "select pk, title, body, create_time, update_time, creator, "
        "keywords, description, mark_lang, status, mark_text from articles "
        "where pk = $1 or uri = $1;";
    pqxx::nontransaction N(conn);
    pqxx::result R(N.exec_params(sqlText, pk));

    for (pqxx::result::const_iterator itr = R.begin(); itr != R.end(); ++itr) {
      std::cout << "Pk = " << itr[0].as<std::string>() << std::endl;
      std::cout << "Title = " << itr[1].as<std::string>() << std::endl;
      auto model = quark::PSArticleModel{
          // .pk = itr[0].as<std::string>(),
          // .title = itr[1].as<std::string>(),
          // .body = itr[2].as<std::string>(),
          // .create_time = quark::makeTimePoint(itr[3].as<std::string>()),
          // .update_time = quark::makeTimePoint(itr[4].as<std::string>()),
          // .creator = itr[5].as<std::string>(),
          // //          .keywords = itr[6].as<std::string>(),
          // //          .description = itr[7].as<std::string>(),
          // .mark_lang = itr[8].as<int>(),
          // .mark_text = itr[10].as<std::string>(),
          // .status = itr[9].as<int>(),
      };
      if (!itr[6].is_null()) {
        model.Keywords = itr[6].as<std::string>();
      }
      if (!itr[7].is_null()) {
        model.Description = itr[7].as<std::string>();
      }
      std::cout << "Operation done successfully" << std::endl;
      // todo 需要关闭链接，因为构建错误所以暂时注释。不确定是调用disconnect还是close
      // conn.disconnect();
      return model;
    }
  }
  throw std::string{"Can't open database"};
}