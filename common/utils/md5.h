//
// Created by linyangz on 2021/12/11.
//

#ifndef PL_MD5_H
#define PL_MD5_H

#include <string>

#include <iostream>
#include <algorithm>
#include <iterator>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>

using boost::uuids::detail::md5;

std::string toString(const md5::digest_type &digest);

std::string calcMd5(const std::string& content);

#endif //PL_MD5_H
