
#include "asset_shader_source.hpp"

#include <vector>
#include <set>
#include <map>
#include <queue>
#include <sstream>
#include <boost/regex.hpp>
#include <boost/range/adaptor/reversed.hpp>


#include "simplex/error/asset_not_found_error.hpp"
#include "simplex/error/cyclic_dependeny_error.hpp"

namespace simplex {

  asset_shader_source::asset_shader_source(asset_loader const& assets, asset_loader::path parent_path) : assets(assets), parent_path(parent_path) {
    if (!assets.asset_exists(parent_path / "vertex.glsl")) {
      auto exc = new asset_not_found_error((parent_path / "vertex.glsl").string());
      LOG(FATAL) << *exc;
      throw exc;
    }
    if (!assets.asset_exists(parent_path / "fragment.glsl")) {
      auto exc = new asset_not_found_error((parent_path / "vertex.glsl").string());
      LOG(FATAL) << *exc;
      throw exc;
    }
  }

  asset_shader_source::~asset_shader_source()
  {

  }

  std::string asset_shader_source::name()
  {
    return parent_path.string();
  }

  std::string asset_shader_source::vertex_shader()
  {
    return process_file(parent_path / "vertex.glsl");
  }

  std::string asset_shader_source::fragment_shader()
  {
    return process_file(parent_path / "fragment.glsl");
  }

  std::string asset_shader_source::process_file(asset_loader::path asset_path) const
  {
    // NOTE: this probably could be improved
    // Also, it is a useful function for development, but production shaders should be preprocessed in the build process

    struct processing_info {
      asset_loader::path path;
      std::string content;
      std::set<asset_loader::path> includes;
    };

    std::vector<processing_info> processed;
    std::queue<asset_loader::path> queue;
    queue.push(asset_path);

    // #include "..." regex
    static const boost::regex re("^[ ]*#[ ]*include[ ]+[\"<](.*)[\">].*");

    while (!queue.empty()) {
      asset_loader::path p = queue.front();
      queue.pop();

      if (std::find_if(processed.begin(), processed.end(), [p](processing_info const& i) { return i.path == p; }) != processed.end()) {
        auto exc = new cyclic_dependency_error(asset_path.string(), p.string());
        LOG(FATAL) << *exc;
        throw exc;
      }

      if (!assets.asset_exists(p)) {
        auto exc = new asset_not_found_error(p.string());
        LOG(FATAL) << *exc;
        throw exc;
      }

      processing_info info;
      info.path = p;
      info.content = assets.load_asset(p);
      
      std::stringstream input;
      input << info.content;
      
      boost::smatch matches;
      std::string line;
      while (std::getline(input, line))
      {
        if (boost::regex_search(line, matches, re))
        {
          std::string include_file = matches[1];
          asset_loader::path new_path = lookup_file(p, include_file);
          info.includes.insert(new_path);
          queue.push(new_path);
        }
      }

      processed.push_back(info);
    }

    // process them backwards and apply includes
    std::map<asset_loader::path, std::string> processedContent;
    for (auto& info : boost::adaptors::reverse(processed)) {
      // duplicated processing :( use recursion?

      std::stringstream input;
      std::stringstream output;
      input << info.content;

      boost::smatch matches;
      std::string line;
      while (std::getline(input, line))
      {
        if (boost::regex_search(line, matches, re))
        {
          std::string include_file = matches[1];
          asset_loader::path new_path = lookup_file(info.path, include_file);
          
          if (processedContent.count(new_path) == 0) {
            LOG(FATAL) << "Internal error while processing includes, content not found for " << new_path.string();
          }

          output << processedContent[new_path] << std::endl;
        }
        else {
          output << line << std::endl;
        }
      }

      processedContent[info.path] = output.str();
    }

    return processedContent[asset_path];
  }

  asset_loader::path asset_shader_source::lookup_file(asset_loader::path source, std::string name) const
  {
    if (name.empty()) {
      auto exc = new asset_not_found_error(name);
      LOG(FATAL) << *exc;
      throw exc;
    }

    // no existence check, the loop will find out if it doesn't exists

    if (name[0] == '/') { // absolute filename
      return name.substr(1);
    }
    else { // relative name
      return source.parent_path() / name;
    }
  }



}