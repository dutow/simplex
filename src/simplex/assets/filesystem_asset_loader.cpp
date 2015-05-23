
#include "filesystem_asset_loader.hpp"

#include <fstream>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include "simplex/error/system_error.hpp"
#include "simplex/error/asset_not_found_error.hpp"

namespace fs = boost::filesystem;

namespace simplex {

filesystem_asset_loader::filesystem_asset_loader(boost::filesystem::path root_path) : root_path(root_path) {
    LOG(INFO) << "Initializing filesystem asset loader with path: " << root_path.string();
    if (!fs::exists(root_path)) {
        auto exc = new system_error("Asset root doesn't exists: " + root_path.string());
        LOG(FATAL) << *exc;
        throw exc;
    }

    if (!fs::is_directory(root_path)) {
        auto exc = new system_error("Asset root isn't a directory: " + root_path.string());
        LOG(FATAL) << *exc;
        throw exc;
    }
}

bool filesystem_asset_loader::asset_exists(fs::path asset_name) const {
    fs::path full_path = root_path / asset_name;
    return fs::exists(full_path) && fs::is_regular_file(full_path);
}

std::string filesystem_asset_loader::load_asset(fs::path asset_name, std::ios_base::openmode mode) const {
    if (!asset_exists(asset_name)) {
        auto exc = new asset_not_found_error(asset_name.string());
        LOG(FATAL) << *exc;
        throw exc;
    }
    fs::path full_path = root_path / asset_name;

    std::ifstream t(full_path.string());
    std::string str;

    t.seekg(0, std::ios::end);
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

    return str;
}

std::vector<uint8_t> filesystem_asset_loader::load_binary_asset(boost::filesystem::path asset_name) const {
    if (!asset_exists(asset_name)) {
        auto exc = new asset_not_found_error(asset_name.string());
        LOG(FATAL) << *exc;
        throw exc;
    }
    fs::path full_path = root_path / asset_name;

    std::ifstream t(full_path.string(), std::ios::binary);

    t.unsetf(std::ios::skipws);

    std::vector<uint8_t> vec;

    t.seekg(0, std::ios::end);
    vec.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    vec.insert(vec.begin(), std::istream_iterator<uint8_t>(t), std::istream_iterator<uint8_t>());

    return vec;
}
}
