#include "../inc/repository.h"


repository::repository(std::string repo_name):
    repo_file_name(repo_name)
{

}

int32_t repository::open_file()
{
    int32_t fret = 0;

    repo_file = std::ofstream(repo_file_name, std::ios::out | std::ios::app);
    repo_file_read = std::ifstream(repo_file_name, std::ios::in);
    if(!repo_file.is_open())
    {
        std::clog<<"Error Opening file"<<std::endl;
        fret = -1;
    }
    repo_file.seekp(std::ios_base::beg);

    return fret;

}

int32_t repository::close_file()
{
    int32_t fret = 0;
    repo_file.close();
    repo_file_read.close();

    return fret;

}

int32_t repository::set_data(std::string key, std::string value, bool sync)
{
    int32_t fret = -1; //TODO: Define proper err code
    std::string data;
    std::map<std::string, std::string>::iterator it;

    if(key.empty() || value.empty())
    {
        return -1;
    }

    fret = this->get_data(key, data, &it);
    if(-1 == fret)  // Data is not in the database, insert it
    {
        fprintf(stderr,"Data is not in DB, put it\n");
        repo_data.insert(std::make_pair(key, value));


    }
    else
    {
        fprintf(stderr, "Data Already Exists. Updating...\n");
        repo_data.erase(it);
        repo_data.insert(std::make_pair(key, value));

    }
    if(sync)// Sync on disk?
    {
        this->update_file();
    }
    return fret;

}

int32_t repository::del_data(const std::string key)
{
    int32_t fret = -1;
    std::string value;
    std::map<std::string, std::string>::iterator it;
    it = repo_data.find(key);
    if( it != repo_data.end())
    {
        fprintf(stderr,"Item %s found, gonna erase it\n", key.c_str());
        repo_data.erase(it);

        this->update_file();
        fret = 0;
    }


    return fret;
}

int32_t repository::get_data(const std::string key,
                             std::string &value,
                             std::map<std::string, std::string>::iterator* oit)
{
    int32_t fret = -1;
    std::map<std::string, std::string>::iterator it;
    if(nullptr == oit)
        return -1;
    if(false == is_db_loaded)
    {
        fprintf(stderr,"Load DB\n");
        this->load_file_data();
    }

    it = repo_data.find(key);

    if( it != repo_data.end())
    {
        value = it->second;
        fprintf(stderr,"Dump: %s-->%s\n",key.c_str(), value.c_str());
        *oit = it;
        return 0;
    }
    else {
        return fret;
    }

}

int32_t repository::load_file_data()
{
    std::string key, value;

    repo_file_read.seekg(std::ios::beg);


    while(!repo_file_read.eof())
    {
        repo_file_read >> key >> value;
        if(!key.empty() && !value.empty())
        {
            repo_data.insert(std::make_pair(key,value));
            fprintf(stderr,"[load_file_data]: %s --> %s\n", key.c_str(), value.c_str());
        }
    }
    this->close_file();
    is_db_loaded = true;

    return 0;

}

int32_t repository::update_file()
{
    int32_t fret = 0;
    remove(repo_file_name.c_str());
    this->open_file();
    repo_file.seekp(std::ios_base::beg);
    std::map<std::string, std::string>::iterator it = repo_data.begin();
    while (it != repo_data.end()) {
        if(!it->first.empty() && !it->second.empty())
        repo_file << it->first<<' '<<it->second<<std::endl;
        it++;

    }

    repo_file.flush();
    this->close_file();
    return fret;

}

int32_t repository::show_data()
{
    for(auto item:repo_data)
    {
        fprintf(stderr," ITEM: %s ----> %s\n", item.first.c_str(), item.second.c_str());
    }

    return 0;
}
