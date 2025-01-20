#pragma once
#include <optional>
#include <vector>
#include <pqxx/pqxx>
#include "quark/models/channel/mail.hpp"

class MailService {
public:
    MailService();

    ~MailService();

    std::optional<std::vector<MTMailModel>> selectMails(int limit);

    int insertMail(const MTMailModel &model);

    int updateMail(const MTMailModel &model);

    int deleteMail(const std::string &pk);

    std::optional<MTMailModel> findMail(const std::string &pk);

    long count();

private:
    pqxx::connection connection;
};
