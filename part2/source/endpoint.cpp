#include "endpoint.hpp"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <sstream>

namespace
{
  std::string build_full_url(const std::string &baseUrl, const std::vector<std::string> &parameters)
  {
    std::string fullUrl{baseUrl};
    for (auto i{0}; i < parameters.size(); i++)
    {
      const auto parameter{parameters[i]};
      if (i == 0)
      {
        fullUrl += '?';
      }
      else
      {
        fullUrl += '&';
      }
      fullUrl += parameter;
    }
    return fullUrl;
  }
}

Endpoint::Endpoint(const std::string baseUrl) : m_baseUrl(baseUrl)
{
}

/*
(Comment)
parameters could use pair instead of string
*/
std::string Endpoint::get(const std::vector<std::string> &parameters)
{
  const std::string fullUrl{build_full_url(m_baseUrl, parameters)};

  curlpp::Cleanup myCleanup;

  std::ostringstream os;
  os << curlpp::options::Url(fullUrl);

  return os.str();
}