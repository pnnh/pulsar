#pragma once

#include <vector>
#include "quark/models/articles/Article.h"

std::vector<quark::PSArticleModel> selectArticles();
quark::PSArticleModel queryArticle(std::string pk);