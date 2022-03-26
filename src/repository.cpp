#include "../inc/repository.h"


repository::repository(std::string repo_name):
    repo_file_name(repo_name)
{

}

int32_t repository::open_file()
{
    int32_t fret = 0;

    repo_file = std::fstream(repo_file_name, std::ios::out | std::ios::app);
    repo_file_read = std::ifstream(repo_file_name, std::ios::in);
    if(!repo_file.is_open())
    {
        std::clog<<"Error Opening file"<<std::endl;
        fret = -1;
    }
    repo_file.seekg(std::ios_base::beg);
//    fret = this->load_file_data();
    return fret;

}

int32_t repository::close_file()
{
    int32_t fret = 0;
    repo_file.sync();
    repo_file.close();
    repo_file_read.close();
    return fret;

}

int32_t repository::set_data(std::string key, std::string value)
{
    int32_t fret = -1; //TODO: Define proper err code
    std::string data;
    fret = this->get_data(key, data);
    if(-1 == fret)  // Data is not in the database, insert it
    {
        fprintf(stderr,"Data is not in DB, put it\n");
        repo_data.insert(std::make_pair(key, value));

        repo_file.seekp(std::ios_base::end);

        repo_file << key<<' '<<value<<std::endl;
        repo_file.sync();

        repo_file.flush();

        fret = 0;
    }
    else
    {
        fprintf(stderr, "Daya Already Exists!\n");
        fret = -1;
    }

    return fret;

}

int32_t repository::del_data(const std::string key)
{
    int32_t fret = -1;


    return fret;
}

int32_t repository::get_data(const std::string key, std::string &value)
{
    int32_t fret = -1;
    std::map<std::string, std::string>::iterator it;

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

    is_db_loaded = true;

    return 0;

}
